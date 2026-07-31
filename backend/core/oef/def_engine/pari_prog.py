"""Mini-interpréteur PARI/GP impératif.

``cas._call_pari`` n'évalue qu'une **expression** unique (``gcd(...)``,
``polcoeff(...)``, ``print(expr)``). Or WIMS passe régulièrement de vrais
petits *programmes* à ``!exec pari`` :

    i = 3 ; l = [4,-2,7,1] ; for (j = 1, 4, if(j != i, print(l[j]), print(-6)));

Sans exécution, la source brute fuitait dans la valeur calculée (mêmes
symptômes que le bug GCD) — d'où les `expected` numexp malformés de
``oefpython.fr/liste_portee1-2`` et de la branche pondérée de
``slib/stat/variance``.

Périmètre couvert (suffisant pour le corpus) :

* séquence d'instructions séparées par ``;`` (et sauts de ligne) ;
* affectations scalaires ``v = e``, indexées ``v[i] = e`` / ``v[i,j] = e`` ;
* ``for(v = a, b, corps)``, ``while(cond, corps)`` (bornées, cf. ``_MAX_STEPS``) ;
* ``if(cond, alors, sinon)`` en position d'instruction **et** d'expression ;
* ``print``/``print1`` accumulant la sortie (une ligne par ``print``, comme GP) ;
* ``sum(v = a, b, e)`` et ``prod(v = a, b, e)`` ;
* vecteurs/matrices **1-indexés** (``l[j]``, ``m[i,j]``) et transposée ``x~``.

Tout le reste (définitions de fonctions ``f(x) = …``, ``local()``, ``List()``)
sort du périmètre : l'interpréteur lève alors ``PariProgramError`` et
``_call_pari`` retombe sur son évaluation d'expression d'origine.
"""

from __future__ import annotations

import re
from typing import Any

# Garde-fou : un programme WIMS reste minuscule ; au-delà, on considère que la
# boucle ne termine pas plutôt que de bloquer le rendu de l'exercice.
_MAX_STEPS = 100_000


class PariProgramError(Exception):
    """Construction hors périmètre — l'appelant doit retomber sur l'évaluation
    d'expression."""


# --------------------------------------------------------------------------- #
# Valeurs : vecteurs / matrices 1-indexés
# --------------------------------------------------------------------------- #


class PVec:
    """Vecteur PARI — indexation **1-based**, arithmétique élémentwise.

    PARI distingue vecteur ligne et vecteur colonne ; seule la transposée
    (``~``) les échange, et le seul usage corpus est le produit scalaire
    ``[data]*[weight]~``. On garde donc juste un drapeau ``col``.
    """

    __slots__ = ("items", "col")

    def __init__(self, items, col: bool = False):
        self.items = list(items)
        self.col = col

    def __len__(self):
        return len(self.items)

    def __iter__(self):
        return iter(self.items)

    def __getitem__(self, idx):
        if isinstance(idx, tuple):
            raise PariProgramError("indexation 2D sur un vecteur")
        return self.items[_one_based(idx, len(self.items))]

    def __setitem__(self, idx, value):
        self.items[_one_based(idx, len(self.items))] = value

    def _binary(self, other, op):
        if isinstance(other, PVec):
            if len(other) != len(self):
                raise PariProgramError("vecteurs de tailles différentes")
            return PVec([op(a, b) for a, b in zip(self.items, other.items)], self.col)
        return PVec([op(a, other) for a in self.items], self.col)

    def __add__(self, other):
        return self._binary(other, lambda a, b: a + b)

    def __radd__(self, other):
        return self._binary(other, lambda a, b: b + a)

    def __sub__(self, other):
        return self._binary(other, lambda a, b: a - b)

    def __rsub__(self, other):
        return self._binary(other, lambda a, b: b - a)

    def __neg__(self):
        return PVec([-a for a in self.items], self.col)

    def __mul__(self, other):
        # `ligne * colonne` = produit scalaire (le cas `[data]*[weight]~` de
        # slib/stat/variance) ; sinon multiplication par un scalaire.
        if isinstance(other, PVec):
            if not self.col and other.col:
                if len(self) != len(other):
                    raise PariProgramError("produit scalaire de tailles différentes")
                total = None
                for a, b in zip(self.items, other.items):
                    term = a * b
                    total = term if total is None else total + term
                return total if total is not None else 0
            raise PariProgramError("produit de vecteurs non conforme")
        return PVec([a * other for a in self.items], self.col)

    def __rmul__(self, other):
        return self.__mul__(other)

    def __truediv__(self, other):
        if isinstance(other, PVec):
            raise PariProgramError("division par un vecteur")
        return PVec([a / other for a in self.items], self.col)

    def __invert__(self):  # `~x` — transposée
        return PVec(self.items, not self.col)

    def __eq__(self, other):
        return isinstance(other, PVec) and self.items == other.items

    def __repr__(self):
        return f"PVec({self.items!r}, col={self.col})"


class PMat:
    """Matrice PARI — ``m[i,j]`` 1-based, ``m[,j]`` / ``m[i,]`` pour les
    colonnes / lignes entières (``length(n[,1])`` du corpus)."""

    __slots__ = ("rows",)

    def __init__(self, rows):
        self.rows = [list(r) for r in rows]

    def __len__(self):
        # PARI : `length(matrice)` = nombre de colonnes.
        return len(self.rows[0]) if self.rows else 0

    def __getitem__(self, idx):
        if not isinstance(idx, tuple):
            raise PariProgramError("indexation 1D sur une matrice")
        i, j = idx
        if i is None and j is None:
            raise PariProgramError("indexation matricielle vide")
        if i is None:  # colonne entière
            col = _one_based(j, len(self.rows[0]) if self.rows else 0)
            return PVec([r[col] for r in self.rows], col=True)
        if j is None:  # ligne entière
            return PVec(self.rows[_one_based(i, len(self.rows))])
        row = self.rows[_one_based(i, len(self.rows))]
        return row[_one_based(j, len(row))]

    def __setitem__(self, idx, value):
        if not isinstance(idx, tuple):
            raise PariProgramError("indexation 1D sur une matrice")
        i, j = idx
        if i is None or j is None:
            raise PariProgramError("affectation de ligne/colonne entière")
        row = self.rows[_one_based(i, len(self.rows))]
        row[_one_based(j, len(row))] = value

    def __invert__(self):
        return PMat([list(c) for c in zip(*self.rows)])

    def __eq__(self, other):
        return isinstance(other, PMat) and self.rows == other.rows

    def __repr__(self):
        return f"PMat({self.rows!r})"


def _one_based(idx, length: int) -> int:
    """Convertit un index PARI (1-based) en index Python, avec contrôle."""
    try:
        i = int(idx)
    except (TypeError, ValueError):
        raise PariProgramError(f"index non entier : {idx!r}") from None
    if i < 1 or i > length:
        raise PariProgramError(f"index {i} hors bornes (1..{length})")
    return i - 1


# --------------------------------------------------------------------------- #
# Découpage lexical
# --------------------------------------------------------------------------- #

_STRING_RE = re.compile(r'"[^"]*"')
_STASH_KEY_RE = re.compile(r"(\x00S\d+\x00)")


def _stash_strings(src: str) -> tuple[str, dict[str, str]]:
    """Remplace les littéraux chaîne par des jetons opaques (le découpage aux
    ``;``/``,`` ne doit pas voir leur contenu)."""
    cache: dict[str, str] = {}

    def _repl(m):
        key = f"\x00S{len(cache)}\x00"
        cache[key] = m.group(0)
        return key

    return _STRING_RE.sub(_repl, src), cache


def _unstash(src: str, cache: dict[str, str]) -> str:
    for key, val in cache.items():
        src = src.replace(key, val)
    return src


def _split_top_level(src: str, sep: str) -> list[str]:
    """Découpe aux occurrences de ``sep`` situées à profondeur 0."""
    parts: list[str] = []
    depth = 0
    current: list[str] = []
    for ch in src:
        if ch in "([{":
            depth += 1
        elif ch in ")]}":
            depth -= 1
        if ch == sep and depth == 0:
            parts.append("".join(current))
            current = []
        else:
            current.append(ch)
    parts.append("".join(current))
    return parts


def _match_call(stmt: str, name: str) -> str | None:
    """Si ``stmt`` est exactement ``name(...)``, renvoie le contenu des
    parenthèses ; sinon ``None``."""
    s = stmt.strip()
    m = re.match(rf"^{name}\s*\(", s, re.I)
    if not m or not s.endswith(")"):
        return None
    inner = s[m.end() : -1]
    # Vérifie que la parenthèse ouvrante se referme bien à la fin (et pas au
    # milieu, comme dans `if(a,b,c) + f(x)`).
    depth = 1
    for ch in inner:
        if ch in "([{":
            depth += 1
        elif ch in ")]}":
            depth -= 1
            if depth == 0:
                return None
    return inner if depth == 1 else None


# Affectation : un `=` de profondeur 0 qui n'est ni `==`, ni `<=`, `>=`, `!=`, `<>`.
def _split_assignment(stmt: str) -> tuple[str, str] | None:
    depth = 0
    for i, ch in enumerate(stmt):
        if ch in "([{":
            depth += 1
        elif ch in ")]}":
            depth -= 1
        elif ch == "=" and depth == 0:
            if stmt[i + 1 : i + 2] == "=":
                return None
            if stmt[i - 1 : i] in ("=", "<", ">", "!"):
                return None
            return stmt[:i].strip(), stmt[i + 1 :].strip()
    return None


# --------------------------------------------------------------------------- #
# Traduction d'expression PARI → Python
# --------------------------------------------------------------------------- #

_INT_LITERAL_RE = re.compile(r"(?<![\w.])(\d+)(?!\.\d?|\w)")
_IDENT_RE = re.compile(r"[A-Za-z_]\w*")


def _translate_expr(expr: str) -> str:
    """Réécrit une expression PARI en source Python évaluable."""
    src, strings = _stash_strings(expr)

    src = src.replace("<>", "!=").replace("&&", " and ").replace("||", " or ")
    src = src.replace("^", "**")

    src = _translate_brackets(src)
    src = _translate_tilde(src)
    src = _INT_LITERAL_RE.sub(r"_I(\1)", src)

    return _unstash(src, strings)


def _translate_brackets(src: str) -> str:
    """``[a,b]`` → ``_V(a,b)``, ``[a,b;c,d]`` → ``_M([[a,b],[c,d]])``, en
    laissant intactes les indexations ``x[i]`` (repérées au caractère qui
    précède). ``m[i,]`` / ``m[,j]`` deviennent ``m[i,None]`` / ``m[None,j]``."""
    out: list[str] = []
    i = 0
    n = len(src)
    while i < n:
        ch = src[i]
        if ch != "[":
            out.append(ch)
            i += 1
            continue

        # Indexation si le crochet suit un identifiant / une parenthèse fermante
        # (`v[i]`, `f(x)[i]`, et le `[1,1,4][x]` de slib/stat/variance, où le
        # littéral vient d'être réécrit en `_V(…)`).
        emitted = "".join(out).rstrip()
        prev = emitted[-1] if emitted else ""
        is_index = bool(prev) and (prev.isalnum() or prev in "_)]")

        depth = 1
        j = i + 1
        while j < n and depth:
            if src[j] in "([{":
                depth += 1
            elif src[j] in ")]}":
                depth -= 1
            if depth:
                j += 1
        if depth:
            raise PariProgramError("crochet non fermé")
        inner = _translate_brackets(src[i + 1 : j])

        if is_index:
            parts = [p.strip() for p in _split_top_level(inner, ",")]
            if len(parts) > 1:
                parts = [p if p else "None" for p in parts]
                out.append("[(" + ",".join(parts) + ")]")
            else:
                out.append(f"[{inner}]")
        else:
            rows = _split_top_level(inner, ";")
            if len(rows) > 1:
                body = ",".join(
                    "[" + ",".join(_split_top_level(r, ",")) + "]" for r in rows
                )
                out.append(f"_M([{body}])")
            else:
                out.append(f"_V({inner})")
        i = j + 1
    return "".join(out)


# `x~` / `)~` / `]~` — transposée postfixe. Traduit en `~x` (Python `__invert__`).
_TILDE_RE = re.compile(r"([A-Za-z_]\w*|\)|\])\s*~")


def _translate_tilde(src: str) -> str:
    """Réécrit la transposée postfixe ``expr~`` en ``(~expr)``."""
    while True:
        m = _TILDE_RE.search(src)
        if not m:
            return src
        end = m.end(1)
        start = _operand_start(src, end)
        src = src[:start] + "(~" + src[start:end] + ")" + src[m.end() :]


def _operand_start(src: str, end: int) -> int:
    """Remonte au début de l'opérande qui se termine en ``end`` (exclu)."""
    i = end - 1
    if src[i] in ")]":
        closing, opening = src[i], "(" if src[i] == ")" else "["
        depth = 0
        while i >= 0:
            if src[i] == closing:
                depth += 1
            elif src[i] == opening:
                depth -= 1
                if depth == 0:
                    break
            i -= 1
        # Un appel `f(...)` / une indexation `v[...]` : englobe le nom qui précède.
        j = i - 1
        while j >= 0 and (src[j].isalnum() or src[j] == "_"):
            j -= 1
        return j + 1
    while i >= 0 and (src[i].isalnum() or src[i] == "_"):
        i -= 1
    return i + 1


# --------------------------------------------------------------------------- #
# Interpréteur
# --------------------------------------------------------------------------- #


class PariInterpreter:
    def __init__(
        self,
        base_ns: dict[str, Any],
        strings: dict[str, str] | None = None,
        session: dict[str, Any] | None = None,
    ):
        import sympy  # noqa: PLC0415

        self.sympy = sympy
        # Les variables *sont* la session quand l'appelant en fournit une, pour
        # que les affectations restent visibles au `!exec pari` suivant.
        self.vars: dict[str, Any] = session if session is not None else {}
        self.out: list[str] = []
        self.steps = 0
        # Littéraux chaîne mis de côté en amont : le découpage aux `;`/`,` ne
        # doit pas voir leur contenu (`print(n","nbin)` de oefbin.nl/binary).
        self.strings: dict[str, str] = strings or {}
        # Les helpers de `cas` renvoient des listes/matrices sympy ; on les
        # enveloppe pour que l'indexation reste 1-based côté programme.
        self.base_ns = {k: _wrap_helper(v) for k, v in base_ns.items()}
        self.base_ns.update(
            {
                "_I": sympy.Integer,
                "_V": lambda *a: PVec(a),
                "_M": PMat,
                "_if": lambda c, a, b=0: a if _truth(c) else b,
                "length": _pari_length,
                "Vec": _pari_vec,
                "concat": _pari_concat,
                "abs": abs,
                # Constantes GP — sans elles, `boo=true` liait un symbole libre
                # et `concat(n, boo)` produisait une juxtaposition illisible
                # (oefpythonfunction.fr/BoucleWhile).
                "true": sympy.Integer(1),
                "false": sympy.Integer(0),
            }
        )

    # -- exécution ---------------------------------------------------------- #

    def run(self, src: str) -> tuple[str, Any]:
        """Exécute le programme ; renvoie (sortie des `print`, dernière valeur)."""
        last = self.exec_block(src)
        lines = "".join(self.out).strip("\n").split("\n")
        return "\n".join(_wims_line_filter(line) for line in lines), last

    def exec_block(self, src: str) -> Any:
        last = None
        for stmt in _split_top_level(src, ";"):
            stmt = stmt.strip()
            if stmt:
                last = self.exec_stmt(stmt)
        return last

    def exec_stmt(self, stmt: str) -> Any:
        self._tick()

        inner = _match_call(stmt, "for")
        if inner is not None:
            return self._exec_for(inner)

        inner = _match_call(stmt, "while")
        if inner is not None:
            return self._exec_while(inner)

        inner = _match_call(stmt, "if")
        if inner is not None:
            return self._exec_if(inner)

        for fn, newline in (("print1", False), ("print", True)):
            inner = _match_call(stmt, fn)
            if inner is not None:
                return self._exec_print(inner, newline)

        assign = _split_assignment(stmt)
        if assign is not None:
            return self._exec_assign(*assign)

        return self.eval_expr(stmt)

    def _exec_for(self, inner: str) -> None:
        args = _split_top_level(inner, ",")
        if len(args) < 3:
            raise PariProgramError("for() malformé")
        head = _split_assignment(args[0])
        if head is None:
            raise PariProgramError("for() sans variable de boucle")
        var, start = head[0], self.eval_expr(head[1])
        stop = self.eval_expr(args[1])
        body = ",".join(args[2:])
        saved = self.vars.get(var)
        try:
            for value in range(int(start), int(stop) + 1):
                self._tick()
                self.vars[var] = self.sympy.Integer(value)
                self.exec_block(body)
        finally:
            if saved is None:
                self.vars.pop(var, None)
            else:
                self.vars[var] = saved

    def _exec_while(self, inner: str) -> None:
        args = _split_top_level(inner, ",")
        if len(args) < 2:
            raise PariProgramError("while() malformé")
        cond, body = args[0], ",".join(args[1:])
        while _truth(self.eval_expr(cond)):
            self._tick()
            self.exec_block(body)

    def _exec_if(self, inner: str) -> Any:
        args = _split_top_level(inner, ",")
        if len(args) < 2:
            raise PariProgramError("if() malformé")
        # PARI évalue paresseusement : seule la branche retenue est exécutée
        # (elle peut contenir un `print`, cf. liste_portee1).
        branch = args[1] if _truth(self.eval_expr(args[0])) else ",".join(args[2:])
        branch = branch.strip()
        return self.exec_block(branch) if branch else None

    def _exec_print(self, inner: str, newline: bool) -> None:
        # GP concatène les arguments sans séparateur ; `print` termine la ligne,
        # `print1` la poursuit.
        for arg in _split_top_level(inner, ","):
            if arg.strip():
                self.out.append(self._render_print_arg(arg))
        if newline:
            self.out.append("\n")

    def _render_print_arg(self, arg: str) -> str:
        """Rend un argument de `print`, en gérant la **juxtaposition** de GP :
        dans un contexte chaîne, `n","nbin` concatène les trois morceaux."""
        pieces = _STASH_KEY_RE.split(arg)
        if len(pieces) == 1:
            return _format_value(self.eval_expr(arg))
        out: list[str] = []
        for piece in pieces:
            if piece in self.strings:
                out.append(self.strings[piece].strip('"'))
            elif piece.strip():
                out.append(_format_value(self.eval_expr(piece)))
        return "".join(out)

    def _exec_assign(self, target: str, rhs: str) -> Any:
        value = self.eval_expr(rhs)
        m = re.match(r"^([A-Za-z_]\w*)\s*\[(.+)\]$", target.strip(), re.DOTALL)
        if m:
            name, index_src = m.group(1), m.group(2)
            container = self.vars.get(name)
            if container is None:
                raise PariProgramError(f"indexation d'une variable inconnue : {name}")
            idx_parts = [p.strip() for p in _split_top_level(index_src, ",")]
            indices = tuple(
                None if not p else self.eval_expr(p) for p in idx_parts
            )
            container[indices[0] if len(indices) == 1 else indices] = value
            return value
        if not _IDENT_RE.fullmatch(target.strip()):
            raise PariProgramError(f"cible d'affectation non gérée : {target!r}")
        self.vars[target.strip()] = value
        return value

    # -- expressions -------------------------------------------------------- #

    def eval_expr(self, expr: str) -> Any:
        self._tick()
        expr = expr.strip()
        if not expr:
            raise PariProgramError("expression vide")

        expr = self._expand_reductions(expr)
        # Les chaînes reprennent leur forme littérale : `_translate_expr` les
        # remet de côté pour son propre compte.
        code = _translate_expr(_unstash(expr, self.strings))
        # `if(...)` en position d'expression : pas d'effet de bord possible ici,
        # une fonction suffit.
        code = re.sub(r"\bif\s*\(", "_if(", code)

        ns = dict(self.base_ns)
        ns.update(self.vars)
        for ident in set(_IDENT_RE.findall(code)):
            if ident not in ns and ident not in _PY_KEYWORDS:
                ns[ident] = self.sympy.Symbol(ident)
        try:
            return eval(code, {"__builtins__": {}}, ns)  # noqa: S307
        except PariProgramError:
            raise
        except Exception as exc:  # parse/exécution impossible → hors périmètre
            raise PariProgramError(f"expression non évaluable : {expr!r} ({exc})") from exc

    def _expand_reductions(self, expr: str) -> str:
        """Déroule ``sum(v = a, b, e)`` / ``prod(...)`` — variable liée, donc
        non exprimable directement en Python."""
        for name, init, combine in (
            ("sum", 0, lambda acc, x: acc + x),
            ("prod", 1, lambda acc, x: acc * x),
        ):
            while True:
                m = re.search(rf"\b{name}\s*\(", expr)
                if not m:
                    break
                start = m.start()
                open_paren = m.end() - 1
                depth = 1
                j = open_paren + 1
                while j < len(expr) and depth:
                    if expr[j] in "([{":
                        depth += 1
                    elif expr[j] in ")]}":
                        depth -= 1
                    if depth:
                        j += 1
                if depth:
                    raise PariProgramError(f"{name}() non fermé")
                args = _split_top_level(expr[open_paren + 1 : j], ",")
                head = _split_assignment(args[0]) if args else None
                if head is None or len(args) < 3:
                    raise PariProgramError(f"{name}() malformé")
                var = head[0].strip()
                lo = int(self.eval_expr(head[1]))
                hi = int(self.eval_expr(args[1]))
                body = ",".join(args[2:])
                saved = self.vars.get(var)
                acc: Any = init
                try:
                    for value in range(lo, hi + 1):
                        self._tick()
                        self.vars[var] = self.sympy.Integer(value)
                        acc = combine(acc, self.eval_expr(body))
                finally:
                    if saved is None:
                        self.vars.pop(var, None)
                    else:
                        self.vars[var] = saved
                # Réinjecte la valeur calculée sous forme littérale parenthésée.
                expr = expr[:start] + f"({_python_literal(acc)})" + expr[j + 1 :]
        return expr

    def _tick(self) -> None:
        self.steps += 1
        if self.steps > _MAX_STEPS:
            raise PariProgramError("programme trop long (boucle non bornée ?)")


_PY_KEYWORDS: set[str] = {
    "True",
    "False",
    "None",
    "and",
    "or",
    "not",
    "if",
    "else",
    "for",
    "in",
    "is",
    "lambda",
    "while",
}


def _truth(value: Any) -> bool:
    """Vérité PARI : 0 est faux, tout le reste vrai.

    Les comparaisons sympy (`n < 10`) renvoient un `BooleanTrue`/`BooleanFalse`,
    pas un `bool` — et `BooleanFalse != 0` vaut *True*, ce qui rendait toute
    condition vraie (boucle `while` infinie).
    """
    if isinstance(value, bool):
        return value
    if isinstance(value, (PVec, PMat)):
        return len(value) > 0
    if getattr(value, "is_Boolean", False) or getattr(value, "is_Relational", False):
        try:
            return bool(value)
        except TypeError:  # comparaison symbolique indécidable
            raise PariProgramError(f"condition non décidable : {value!r}") from None
    try:
        return bool(value != 0)
    except Exception:
        return bool(value)


def _to_pari_value(value: Any) -> Any:
    """Convertit une valeur renvoyée par un helper de `cas` en valeur PARI —
    listes → `PVec`, listes de listes → `PMat` (indexation 1-based)."""
    if isinstance(value, (list, tuple)):
        rows = list(value)
        if rows and all(isinstance(r, (list, tuple)) for r in rows):
            return PMat(rows)
        return PVec(rows)
    return value


def _wrap_helper(fn):
    if not callable(fn):
        return fn

    def wrapper(*args, **kwargs):
        return _to_pari_value(fn(*args, **kwargs))

    return wrapper


def _pari_concat(*args) -> Any:
    """`concat` de GP.

    Concatène des chaînes si l'un des arguments en est une ; sinon produit un
    **vecteur**, en aplatissant d'un niveau — y compris pour deux scalaires
    (`concat(5, 1)` vaut `[5, 1]`, pas `"51"`). C'est la différence avec le
    helper de `cas`, purement textuel, qui transformait les couples
    (valeur, booléen) de oefpythonfunction.fr/BoucleWhile en nombres collés.
    """
    if any(isinstance(a, str) for a in args):
        return "".join(str(a) for a in args)
    items: list[Any] = []
    for arg in args:
        if isinstance(arg, PVec):
            items.extend(arg.items)
        else:
            items.append(arg)
    return PVec(items)


def _pari_length(x) -> int:
    if isinstance(x, (PVec, PMat)):
        return len(x)
    if isinstance(x, (list, tuple, str)):
        return len(x)
    return 1


def _pari_vec(x):
    if isinstance(x, PVec):
        return PVec(x.items)
    if isinstance(x, PMat):
        return PVec([PVec(r) for r in x.rows])
    if isinstance(x, (list, tuple)):
        return PVec(x)
    return PVec([x])


def _python_literal(value: Any) -> str:
    """Rend une valeur calculée sous une forme re-parsable par `eval_expr`."""
    if isinstance(value, PVec):
        return "[" + ",".join(_python_literal(v) for v in value.items) + "]"
    if isinstance(value, PMat):
        return (
            "["
            + ";".join(
                ",".join(_python_literal(v) for v in row) for row in value.rows
            )
            + "]"
        )
    return f"({value})".replace("**", "^")


def _find_matching(src: str, start: int, closing: str) -> int:
    """Index du délimiteur fermant appariant celui ouvert en ``start-1``."""
    opening = {"]": "[", ")": "("}[closing]
    depth = 1
    for i in range(start, len(src)):
        if src[i] == opening:
            depth += 1
        elif src[i] == closing:
            depth -= 1
            if depth == 0:
                return i
    return -1


def _wims_line_filter(line: str) -> str:
    """Post-traitement que WIMS applique à chaque ligne de sortie de `gp`.

    Cf. ``wims/src/Interfaces/pari.c`` : espaces retirés, puis **crochets
    englobants supprimés** — c'est pourquoi `print(coord)` alimente une liste
    WIMS `10,21,43` et non `[10, 21, 43]`. Le retrait n'a lieu que si le
    délimiteur ouvrant s'apparie au tout dernier caractère, si bien qu'une
    structure imbriquée (`[1, [2,3]]`) garde ses crochets internes.
    """
    out = line.strip()
    for prefix in ("Mat(", "Vecsmall("):
        if out.startswith(prefix) and out.endswith(")"):
            if _find_matching(out, len(prefix), ")") == len(out) - 1:
                out = out[len(prefix) : -1].strip()
    if out.startswith("[") and out.endswith("]"):
        if _find_matching(out, 1, "]") == len(out) - 1:
            out = out[1:-1].strip()
    return out


def _format_value(value: Any) -> str:
    """Rendu d'une valeur pour `print`, au format GP."""
    from .cas import _format_pari_result  # noqa: PLC0415

    if isinstance(value, str):
        return value.strip('"')
    if isinstance(value, PVec):
        return "[" + ", ".join(_format_value(v) for v in value.items) + "]"
    if isinstance(value, PMat):
        return "[" + "; ".join(
            ", ".join(_format_value(v) for v in row) for row in value.rows
        ) + "]"
    return _format_pari_result(value)


# --------------------------------------------------------------------------- #
# Point d'entrée
# --------------------------------------------------------------------------- #

# Un programme se reconnaît à une instruction séparée par `;`, une affectation,
# une structure de contrôle en tête, ou une construction que l'évaluation
# d'expression de `_call_pari` ne sait pas rendre (variable liée de `sum`/`prod`,
# transposée postfixe). Une expression seule (`gcd(4,6)`, `print(x)`) reste
# traitée par `_call_pari`.
_CONTROL_RE = re.compile(r"^\s*(for|while|forstep)\s*\(", re.I)
_BOUND_VAR_RE = re.compile(r"\b(sum|prod)\s*\(\s*[A-Za-z_]\w*\s*=")


def looks_like_program(src: str) -> bool:
    body, _ = _stash_strings(src.strip().rstrip(";").strip())
    if body.startswith("{") and body.endswith("}"):
        body = body[1:-1]
    if _CONTROL_RE.match(body) or _BOUND_VAR_RE.search(body):
        return True
    if _TILDE_RE.search(body):
        return True
    statements = [s for s in _split_top_level(body, ";") if s.strip()]
    if len(statements) > 1:
        return True
    return bool(statements) and _split_assignment(statements[0]) is not None


def _restore(session: dict[str, Any] | None, snapshot: dict[str, Any] | None) -> None:
    if session is not None and snapshot is not None:
        session.clear()
        session.update(snapshot)


def run_pari_program(
    src: str, base_ns: dict[str, Any], session: dict[str, Any] | None = None
) -> str:
    """Exécute un programme PARI et renvoie sa sortie (`print` accumulés).

    ``session`` (optionnel) est le dictionnaire de variables partagé entre les
    ``!exec pari`` d'un même exercice ; il est mis à jour en place.

    Lève ``PariProgramError`` dès qu'une construction sort du périmètre, pour
    que l'appelant retombe sur l'évaluation d'expression.
    """
    body = src.strip()
    # `!exec pari { … }` — les accolades délimitent un bloc en GP.
    if body.startswith("{") and body.endswith("}"):
        body = body[1:-1]
    # Les continuations WIMS (`\` en fin de ligne) sont déjà résolues en amont ;
    # les sauts de ligne restants sont de simples blancs (en GP le séparateur
    # d'instructions est `;`, y compris à travers les lignes).
    body = body.replace("\\\n", " ")

    body, strings = _stash_strings(body)
    interp = PariInterpreter(base_ns, strings, session)
    # L'exécution est atomique vis-à-vis de la session : un programme
    # abandonné en route ne doit pas y laisser de variables à moitié
    # calculées, que le `!exec pari` suivant lirait comme valides.
    snapshot = dict(session) if session is not None else None
    try:
        printed, last = interp.run(body)
    except PariProgramError:
        _restore(session, snapshot)
        raise
    except Exception as exc:
        # Contrat du module : *toute* construction hors périmètre doit renvoyer
        # la main à l'évaluation d'expression, jamais faire échouer le rendu.
        _restore(session, snapshot)
        raise PariProgramError(f"exécution impossible : {exc}") from exc
    if interp.out:
        return printed
    # Sans `print`, GP affiche la valeur de la dernière instruction — sauf si
    # elle est terminée par `;` (le `l=vector(n);for(…);` de oefforpython.fr
    # ne produit rien, alors que le `…;if(abs(A-B)<10^-15,1,0)` de
    # oefline.it/sys3 renvoie sa valeur).
    if last is None or src.rstrip().rstrip("}").rstrip().endswith(";"):
        return ""
    return _wims_line_filter(_format_value(last))
