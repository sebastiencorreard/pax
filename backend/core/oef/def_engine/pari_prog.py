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
* vecteurs/matrices **1-indexés** (``l[j]``, ``m[i,j]``) et transposée ``x~`` ;
* fonctions définies par le programme (``f(x) = corps``, éventuellement
  entourées de parenthèses), ``local()``, et le type mutable ``List`` avec
  ``listinsert``/``Vec``/``vecsort`` — ce dont ``slib/function/tabsignes`` a
  besoin pour trier ses positions de réponses.

Tout le reste sort du périmètre : l'interpréteur lève alors
``PariProgramError`` et ``_call_pari`` retombe sur son évaluation d'expression
d'origine.
"""

from __future__ import annotations

import ast
import math
import re
from typing import Any

# Constructions PARI à **variable liée** : (nombre d'arguments avant les
# variables, nombre de variables). `vector(n, X, expr)` évalue `expr` une fois
# par indice, `matrix(m, n, I, J, expr)` une fois par case.
_PARI_LIEES: dict[str, tuple[int, int]] = {
    "vector": (1, 1),
    "matrix": (2, 2),
}


class _LierVariables(ast.NodeTransformer):
    """Transforme le corps d'une construction PARI liée en lambda.

    C'est une question d'**ordre d'évaluation**, pas de syntaxe : PARI évalue
    le corps une fois par indice, quand `eval()` de Python l'évalue une seule
    fois, avant l'appel. La différence ne se voit pas sur `vector(3,k,k^2)` —
    `k` reste un symbole et la substitution rattrape le coup — mais elle est
    fatale dès que le corps se réduit sans le symbole : `vector(2,x,(x==2))`
    devient `False` avant même d'entrer dans la fonction, et le vecteur
    indicateur de `slib/triplerelation/tabular` sort nul.

    Passer par une lambda rend la sémantique de PARI telle quelle, pour les
    quelque 190 `matrix(` et `vector(` du corpus et des slib partagés.
    """

    def visit_Call(self, node: ast.Call) -> ast.Call:
        self.generic_visit(node)
        if not isinstance(node.func, ast.Name):
            return node
        spec = _PARI_LIEES.get(node.func.id)
        if spec is None:
            return node
        avant, nb_vars = spec
        if len(node.args) != avant + nb_vars + 1:
            return node  # forme courte : `vector(n)`, `matrix(m,n)`
        variables = node.args[avant : avant + nb_vars]
        if not all(isinstance(v, ast.Name) for v in variables):
            return node
        lam = ast.Lambda(
            args=ast.arguments(
                posonlyargs=[], args=[ast.arg(arg=v.id) for v in variables],
                kwonlyargs=[], kw_defaults=[], defaults=[],
            ),
            body=node.args[-1],
        )
        node.args = node.args[:avant] + [lam]
        return ast.fix_missing_locations(node)


def _lier_variables(code: str) -> str:
    """Réécrit `code` pour que les corps liés deviennent des lambdas.

    Rend le code inchangé si l'AST ne se relit pas — l'évaluation se fera
    comme avant, plutôt que d'échouer sur une transformation.
    """
    try:
        arbre = ast.parse(code, mode="eval")
    except SyntaxError:
        return code
    try:
        return ast.unparse(_LierVariables().visit(arbre))
    except Exception:  # noqa: BLE001
        return code

# Garde-fou : un programme WIMS reste minuscule ; au-delà, on considère que la
# boucle ne termine pas plutôt que de bloquer le rendu de l'exercice.
_MAX_STEPS = 100_000

# WIMS tient une session `gp` **ouverte** pour la durée d'un exercice : ce qu'un
# `!exec pari` y dépose, le suivant le retrouve. Les variables l'étaient déjà ;
# ne l'étaient pas les deux autres choses qu'une session porte — les fonctions
# qu'on y définit et le format de sortie qu'on y fixe. D'où le cas typique de
# `oefpytha` et d'`oefalgopython`, une définition inline suivie de son appel
# dans un second `!exec` :
#
#     !exec pari f(t)=(t+e/t)*0.5;      ← posée ici…
#     !exec pari default(format,"f.8"); u=f(3,\rac); …
#     !exec pari print(u)               ← …et attendue ici
#
# Elles vivent donc dans le même dictionnaire que les variables, sous des clés
# qu'aucun identifiant PARI ne peut porter (`_IDENT_RE` exige une lettre ou un
# `_` en tête). Elles traversent l'`eval` sans effet : le résolveur de noms de
# Python ne peut nommer une clé qui n'est pas un identifiant.
_SESSION_FUNCS = "\x00funcs"
_SESSION_FORMAT = "\x00format"

# `default(format, "<style>.<chiffres>")` — le style vaut `e` (toujours
# scientifique), `f` (jamais d'exposant) ou `g` (au choix), et le nombre est
# celui des chiffres **significatifs** affichés, non des décimales.
_FORMAT_RE = re.compile(r"([efg])\.(\d+)", re.I)


class PariProgramError(Exception):
    """Construction hors périmètre — l'appelant doit retomber sur l'évaluation
    d'expression."""


class _Retour(Exception):
    """``return(x)`` — sortie anticipée d'une fonction GP.

    Une exception, parce que `return` traverse les boucles : le `pyth` d'
    `oefpytha` sort de deux `for` imbriqués dès qu'il tient son triplet
    pythagoricien. Interne à l'interpréteur ; jamais vue par l'appelant.
    """

    def __init__(self, valeur: Any = None):
        super().__init__("return")
        self.valeur = valeur


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


class PList:
    """`List` de GP — un vecteur *mutable*, distinct du vecteur immuable.

    Seul `listinsert` est utilisé par le corpus (`slib/function/tabsignes` et
    `slib/stat/binomial` construisent leurs lignes ainsi) ; `Vec` la reconvertit
    en vecteur ordinaire.
    """

    __slots__ = ("items",)

    def __init__(self, items=()):
        self.items = list(items)

    def __len__(self):
        return len(self.items)

    def __iter__(self):
        return iter(self.items)

    def __getitem__(self, idx):
        return self.items[_one_based(idx, len(self.items))]

    def __setitem__(self, idx, value):
        self.items[_one_based(idx, len(self.items))] = value

    def __repr__(self):
        return f"PList({self.items!r})"


def _pari_listinsert(lst, value, index):
    """`listinsert(L, x, i)` — insère `x` en position `i` (1-based) et renvoie
    la valeur insérée, comme GP."""
    if not isinstance(lst, PList):
        raise PariProgramError("listinsert attend une List")
    i = int(index)
    if i < 1 or i > len(lst.items) + 1:
        raise PariProgramError(f"listinsert : index {i} hors bornes")
    lst.items.insert(i - 1, value)
    return value


def _sort_key(value):
    """Clé de tri de `vecsort` : ordre lexicographique pour les vecteurs (les
    lignes d'une matrice), numérique sinon."""
    if isinstance(value, (PVec, PList)):
        return tuple(_sort_key(v) for v in value.items)
    try:
        return (0, float(value))
    except (TypeError, ValueError):
        return (1, str(value))


def _pari_vecsort(vec, *_rest):
    """`vecsort(V)` — tri croissant. Les arguments de comparaison optionnels de
    GP ne sont pas utilisés par le corpus."""
    items = vec.items if isinstance(vec, (PVec, PList)) else list(vec)
    return PVec(sorted(items, key=_sort_key))


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
        # Fonctions définies par le programme : nom → (paramètres, corps). Le
        # dictionnaire est **celui de la session** quand il y en a une, pour
        # qu'une définition survive au `!exec pari` qui l'a posée.
        self.funcs: dict[str, tuple[list[str], str]] = self.vars.setdefault(
            _SESSION_FUNCS, {}
        )
        # Format de sortie courant, `(style, chiffres significatifs)` ou None
        # tant qu'aucun `default(format, …)` ne l'a fixé.
        self.fmt: tuple[str, int] | None = self.vars.get(_SESSION_FORMAT)
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
                "List": lambda x=(): PList(
                    x.items if isinstance(x, (PVec, PList)) else (x or ())
                ),
                "listinsert": _pari_listinsert,
                "vecsort": _pari_vecsort,
                # `local(a,b,…)` déclare des variables de fonction ; l'effet de
                # portée ne change rien ici puisque chaque appel restaure déjà
                # l'état qu'il a modifié.
                "local": lambda *a: sympy.Integer(0),
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
        try:
            last = self.exec_block(src)
        except _Retour as sortie:
            # `return` au niveau du programme : GP l'accepte et rend la valeur.
            last = sortie.valeur
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

        # `( … )` enveloppant toute l'instruction : GP l'autorise, et les slib
        # s'en servent pour isoler une définition de fonction avant de
        # l'appeler (`(f(r,n)= … ); f(2,1)` dans slib/stat/histo). Sans ce
        # déballage, le `=` de la définition reste à profondeur 1 et
        # l'instruction est prise pour une expression.
        stripped = stmt.strip()
        if stripped.startswith("(") and stripped.endswith(")"):
            inner = stripped[1:-1]
            depth = 0
            balanced = True
            for ch in inner:
                if ch == "(":
                    depth += 1
                elif ch == ")":
                    depth -= 1
                    if depth < 0:
                        balanced = False
                        break
            if balanced and depth == 0 and _split_assignment(inner) is not None:
                stmt = inner

        inner = _match_call(stmt, "for")
        if inner is not None:
            return self._exec_for(inner)

        inner = _match_call(stmt, "forstep")
        if inner is not None:
            return self._exec_forstep(inner)

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

        inner = _match_call(stmt, "default")
        if inner is not None:
            return self._exec_default(inner)

        inner = _match_call(stmt, "return")
        if inner is not None:
            raise _Retour(self.eval_expr(inner) if inner.strip() else None)
        if stmt.strip().lower() == "return":
            raise _Retour(None)

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

    def _exec_forstep(self, inner: str) -> None:
        """``forstep(v = a, b, pas, corps)`` — la boucle `for` à pas choisi.

        `_CONTROL_RE` la reconnaissait déjà comme structure de contrôle, mais
        rien ne l'exécutait : l'instruction partait en évaluation d'expression,
        et le `=` du `v = a` y devenait un argument nommé Python. L'erreur
        emportait le programme entier — les balayages d'`oefalgopython`
        n'obtenaient plus aucune de leurs listes, sans qu'aucun message ne le
        dise. Trente-six fichiers du corpus s'en servent.

        Le pas est le plus souvent fractionnaire (`1.0*10^(-p)`), d'où la
        boucle sur un accumulateur plutôt que sur `range`. GP compare la
        variable à la borne à chaque tour et s'arrête dès qu'elle la dépasse,
        dans le sens du pas ; un pas nul ne boucle pas.
        """
        args = _split_top_level(inner, ",")
        if len(args) < 4:
            raise PariProgramError("forstep() malformé")
        head = _split_assignment(args[0])
        if head is None:
            raise PariProgramError("forstep() sans variable de boucle")
        var = head[0]
        debut = self.eval_expr(head[1])
        fin = self.eval_expr(args[1])
        pas = self.eval_expr(args[2])
        body = ",".join(args[3:])
        try:
            pas_f = float(pas)
        except (TypeError, ValueError) as exc:
            # `forstep(x=a,b,[p,q])` — pas donné par un vecteur de résidus.
            # Aucun exercice du corpus n'y recourt ; hors périmètre.
            raise PariProgramError(f"forstep() à pas non scalaire : {pas!r}") from exc
        if pas_f == 0:
            raise PariProgramError("forstep() à pas nul")
        saved = self.vars.get(var)
        try:
            valeur = debut
            while (float(valeur) <= float(fin)) if pas_f > 0 else (
                float(valeur) >= float(fin)
            ):
                self._tick()
                self.vars[var] = valeur
                self.exec_block(body)
                valeur = valeur + pas
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

    def _exec_default(self, inner: str) -> None:
        """``default(clé, valeur)`` — un réglage de la session `gp`, pas un calcul.

        Rien ne l'évaluait, et l'échec ne restait pas local : il emportait le
        programme entier, qui repartait alors en **source brute** dans la
        variable WIMS. Or 89 fichiers du corpus — dont 36 `.def` — ouvrent sur
        ``default(format, "f.8")`` avant de poser leurs variables, si bien que
        tout ce qui suivait était perdu sans qu'aucune erreur ne le signale.

        Seul ``format`` change quelque chose d'observable ici : il fixe la
        notation des réels imprimés (cf. ``_format_value``). Les autres
        réglages — ``realprecision``, ``output``, ``seriesprecision`` — ne
        portent pas jusqu'à cette émulation ; les ignorer est fidèle à ce
        qu'elles produisent chez nous, c'est-à-dire rien.
        """
        args = _split_top_level(inner, ",")
        if len(args) < 2:
            # `default(cle)` lit un réglage au lieu d'en poser un. Aucun
            # exercice ne s'en sert, et rendre 0 vaut mieux qu'abandonner.
            return None
        cle = _unstash(args[0], self.strings).strip().strip('"').lower()
        val = _unstash(args[1], self.strings).strip().strip('"')
        if cle == "format":
            m = _FORMAT_RE.fullmatch(val.strip())
            if m:
                self.fmt = (m.group(1).lower(), int(m.group(2)))
                self.vars[_SESSION_FORMAT] = self.fmt
        return None

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
            return _format_value(self.eval_expr(arg), self.fmt)
        out: list[str] = []
        for piece in pieces:
            if piece in self.strings:
                out.append(self.strings[piece].strip('"'))
            elif piece.strip():
                out.append(_format_value(self.eval_expr(piece), self.fmt))
        return "".join(out)

    def _exec_assign(self, target: str, rhs: str) -> Any:
        # `nom(params) = corps` — définition de fonction GP. Le corps est une
        # séquence d'instructions dont la dernière donne la valeur de retour
        # (`slib/function/tabsignes` trie ainsi ses positions de réponses avec
        # `matsort(mat)=…;N`).
        fn = re.match(r"^([A-Za-z_]\w*)\s*\(([^)]*)\)$", target.strip())
        if fn:
            name = fn.group(1)
            params = [p.strip() for p in fn.group(2).split(",") if p.strip()]
            # GP autorise un corps entouré d'accolades, et c'est même la forme
            # usuelle dès qu'il tient sur plusieurs lignes (`pyth(A,B,lim)={…}`
            # d'`oefpytha`). Sans ce déballage, `exec_block` recevait `{for(…)}`
            # et n'y voyait pas une instruction.
            corps = rhs.strip()
            if corps.startswith("{") and corps.endswith("}"):
                corps = corps[1:-1]
            self.funcs[name] = (params, corps)
            self.vars.pop(name, None)
            return None

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
        for name in self.funcs:
            ns[name] = self._user_func(name)
        for ident in set(_IDENT_RE.findall(code)):
            if ident not in ns and ident not in _PY_KEYWORDS:
                ns[ident] = self.sympy.Symbol(ident)
        try:
            # Le namespace passe en **globals** : une lambda — celles que
            # `_lier_variables` introduit pour les corps liés — résout ses noms
            # dans les globals de sa définition, jamais dans les locals d'un
            # `eval`. Les helpers PARI y seraient invisibles au moment de
            # l'appel. `__builtins__` reste vide, comme avant.
            return eval(_lier_variables(code), {**ns, "__builtins__": {}})  # noqa: S307
        except PariProgramError:
            raise
        except Exception as exc:  # parse/exécution impossible → hors périmètre
            raise PariProgramError(f"expression non évaluable : {expr!r} ({exc})") from exc

    def _user_func(self, name: str):
        """Rend une fonction définie par le programme appelable depuis une
        expression. Les paramètres masquent les variables de même nom le temps
        de l'appel, et la dernière instruction du corps donne le résultat."""

        def call(*args):
            params, body = self.funcs[name]
            saved = {p: self.vars.get(p) for p in params}
            self.vars.update(dict(zip(params, args)))
            try:
                try:
                    return self.exec_block(body)
                except _Retour as sortie:
                    return sortie.valeur
            finally:
                for p, old in saved.items():
                    if old is None:
                        self.vars.pop(p, None)
                    else:
                        self.vars[p] = old

        return call

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
    if isinstance(value, (PVec, PMat, PList)):
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


def _from_pari_value(value: Any) -> Any:
    """Inverse de `_to_pari_value` : les helpers de `cas` raisonnent sur des
    listes Python et ne connaissent pas `PVec`/`PMat`."""
    if isinstance(value, PMat):
        return [list(row) for row in value.rows]
    if isinstance(value, (PVec, PList)):
        return list(value.items)
    return value


def _wrap_helper(fn):
    """Adapte un helper de `cas` aux valeurs de l'interpréteur — dans les deux
    sens. Sans la conversion *entrante*, `matsize` ne reconnaissait pas un
    `PMat` et retombait sur son `[1, 1]` par défaut : `slib/function/tabsignes`
    lisait alors 1 seule position de réponse au lieu de 6."""
    if not callable(fn):
        return fn

    def wrapper(*args, **kwargs):
        args = tuple(_from_pari_value(a) for a in args)
        kwargs = {k: _from_pari_value(v) for k, v in kwargs.items()}
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
    if isinstance(x, (PVec, PMat, PList)):
        return len(x)
    if isinstance(x, (list, tuple, str)):
        return len(x)
    return 1


def _pari_vec(x):
    if isinstance(x, (PVec, PList)):
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


def _format_reel(x: float, fmt: tuple[str, int]) -> str | None:
    """Un réel selon ``default(format, …)``, ou None si la règle ne s'applique pas.

    Le style dicte la notation — `e` toujours un exposant, `f` jamais, `g` au
    choix — et le nombre compte les chiffres **significatifs**, non les
    décimales : `f.8` rend `0.33333333` comme `1.2345679`.

    Les entiers exacts restent hors de cette règle et gardent leur écriture
    courte (`2`, non `2.0000000`). GP, lui, affiche la précision complète ; mais
    la valeur ne traverse pas WIMS comme un affichage, elle y devient le contenu
    d'une variable qu'un `!ifval` compare ou qu'un attendu reprend. Le zéro de
    queue n'y apporterait rien et changerait 89 fichiers d'un coup.
    """
    style, chiffres = fmt
    if chiffres <= 0 or x != x or x in (float("inf"), float("-inf")):
        return None
    if x.is_integer():
        return None
    if style == "e":
        return f"{x:.{chiffres - 1}e}"
    if style == "g":
        return f"{x:.{chiffres}g}"
    # `f` : notation fixe, quelle que soit la grandeur. Le nombre de décimales
    # se déduit des chiffres significatifs demandés et de l'ordre de grandeur.
    exposant = math.floor(math.log10(abs(x)))
    decimales = max(0, chiffres - 1 - exposant)
    out = f"{x:.{decimales}f}"
    # Un arrondi peut vider la partie significative (`0.00000004` en `f.3`) ;
    # mieux vaut alors la notation courte que `0.000`.
    if float(out) == 0.0:
        return None
    return out.rstrip("0").rstrip(".") if "." in out else out


def _format_value(value: Any, fmt: tuple[str, int] | None = None) -> str:
    """Rendu d'une valeur pour `print`, au format GP **brut**.

    L'interface PARI de WIMS ouvre `gp` sur `default(output,0)`
    (`wims/src/Interfaces/pari.c`, en-tête du `.gprc`) : le mode « raw », qui
    imprime `[1,6]` et non `[1, 6]`. L'espace de présentation du mode par
    défaut n'atteint donc jamais une variable WIMS — et c'est ce qui permet à
    `[$l,$c] isitemof $slib_repsort` (`slib/function/tabsignes`) de retrouver
    son couple par simple recherche de sous-chaîne. L'émettre ici obligeait
    tous les consommateurs à ignorer les espaces, `itemchr` compris.
    """
    from .cas import _format_pari_result  # noqa: PLC0415

    if isinstance(value, str):
        return value.strip('"')
    if isinstance(value, (PVec, PList)):
        return "[" + ",".join(_format_value(v, fmt) for v in value.items) + "]"
    if isinstance(value, PMat):
        return "[" + ";".join(
            ",".join(_format_value(v, fmt) for v in row) for row in value.rows
        ) + "]"
    # `format` ne régit que les réels — les t_REAL de GP. Un rationnel y reste
    # exact (`1/3` s'imprime `1/3`, jamais `0.33333333`) et un entier garde son
    # écriture ; les formater serait une perte d'information, pas une mise en
    # forme.
    if fmt is not None and isinstance(value, float):
        rendu = _format_reel(value, fmt)
        if rendu is not None:
            return rendu
    if fmt is not None and _est_flottant_sympy(value):
        rendu = _format_reel(float(value), fmt)
        if rendu is not None:
            return rendu
    return _format_pari_result(value)


def _est_flottant_sympy(value: Any) -> bool:
    import sympy  # noqa: PLC0415

    return isinstance(value, sympy.Float)


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
# Constructions que l'évaluation d'expression ne sait pas rendre : types
# mutables et fonctions définies à la volée.
_GP_ONLY_RE = re.compile(
    r"\b(List|listinsert|listput|vecsort|local|default)\s*\(|\w+\([^)]*\)\s*=(?!=)"
)


def looks_like_program(src: str) -> bool:
    body, _ = _stash_strings(src.strip().rstrip(";").strip())
    if body.startswith("{") and body.endswith("}"):
        body = body[1:-1]
    if _CONTROL_RE.match(body) or _BOUND_VAR_RE.search(body) or _GP_ONLY_RE.search(body):
        return True
    if _TILDE_RE.search(body):
        return True
    statements = [s for s in _split_top_level(body, ";") if s.strip()]
    if len(statements) > 1:
        return True
    return bool(statements) and _split_assignment(statements[0]) is not None


def session_porte_un_etat(session: dict[str, Any] | None) -> bool:
    """Vrai si la session tient de quoi changer le sens d'une expression.

    Un simple `if session` ne suffit plus : l'interpréteur y installe sa table
    de fonctions dès qu'il s'exécute, fût-ce pour un programme abandonné en
    route. Une session ainsi peuplée d'un dictionnaire vide dirait « non
    vide », et tout `!exec pari` ultérieur serait routé vers l'interpréteur
    au lieu de l'évaluation d'expression — un changement de comportement pour
    tout exercice qui enchaîne plusieurs `!exec pari`, sans qu'aucun état
    réel le justifie.
    """
    if not session:
        return False
    for cle, valeur in session.items():
        if cle == _SESSION_FUNCS:
            if valeur:
                return True
        elif cle == _SESSION_FORMAT:
            return True
        else:
            # Une variable compte même quand elle vaut 0 : c'est bien une
            # valeur qu'une expression peut lire.
            return True
    return False


def _snapshot(session: dict[str, Any] | None) -> dict[str, Any] | None:
    """Copie de la session à restaurer si le programme est abandonné.

    Superficielle, à une exception près : la table des fonctions est un
    dictionnaire que l'interpréteur mute **en place**, si bien qu'une copie
    plate l'aurait laissée partagée — et une fonction définie juste avant
    l'abandon aurait survécu à la restauration.
    """
    if session is None:
        return None
    snap = dict(session)
    if _SESSION_FUNCS in snap:
        snap[_SESSION_FUNCS] = dict(snap[_SESSION_FUNCS])
    return snap


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
    snapshot = _snapshot(session)
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
    return _wims_line_filter(_format_value(last, interp.fmt))
