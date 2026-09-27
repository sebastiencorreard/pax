"""`!rawmath` — port de `wims/src/rawmath.c` (`rawmath()`).

La routine « tolérante aux erreurs » de WIMS : elle rend exploitable une
expression tapée à la main — `2x` → `2*x`, `3(x+1)` → `3*(x+1)`,
`sin x` → `sin(x)`, `sinx^2` → `sin(x)^2`, `|x-1|` → `abs(x-1)`, `.5` →
`0.5` — et ne touche à rien de ce qui ressemble à du TeX (`\\` ou `{`).

Le C est suivi pas à pas, pointeurs compris : ses règles tiennent à l'ordre des
opérations plus qu'à une grammaire, et c'est cet ordre qui décide du résultat
dans les cas ambigus (`xy` → `x*y`, `abc` → inchangé). Il a été confronté au
vrai `rawmath()`, compilé depuis l'arbre, sur toutes les entrées que le corpus
lui soumet.

Non repris : les noms déclarés par `wims_rawmath_variables` /
`wims_rawmath_functions` (aucun exercice OEF ne les pose), et `rawmath_easy`,
qui ne sert qu'à `insmath`.
"""

from __future__ import annotations

MAX_LINELEN = 45000

# `evalname` de `Lib/evalue.c` : nom → type (0 constante, > 0 fonction).
_EVALNAME: dict[str, int] = {
    "Argch": 1, "Argsh": 1, "Argth": 1, "E": 0, "EULER": 0,
    "EVLS": 0, "EVLT": 0, "EVLX": 0, "EVLY": 0,
    "Euler": 0, "Inf": 0, "NaN": 0, "PI": 0, "Pi": 0,
    "abs": 1, "acos": 1, "acosh": 1, "arccos": 1, "arcsin": 1, "arctan": 1,
    "arctg": 1, "argch": 1, "argsh": 1, "argth": 1, "asin": 1, "asinh": 1,
    "atan": 1, "atanh": 1, "binomial": 2, "ceil": 1, "ch": 1, "cos": 1,
    "cosh": 1, "cot": 1, "cotan": 1, "cotanh": 1, "coth": 1, "csc": 1,
    "ctg": 1, "cth": 1, "drand": 1, "e": 0, "erf": 1, "erfc": 1, "euler": 0,
    "exp": 1, "factorial": 1, "floor": 1, "gcd": 2, "irand": 1, "lcm": 2,
    "lg": 1, "lgamma": 1, "ln": 1, "log": 1, "log10": 1, "log2": 1, "max": 2,
    "min": 2, "pi": 0, "pow": 2, "rand": 1, "randdouble": 1, "randfloat": 1,
    "randint": 1, "random": 1, "randreal": 1, "rint": 1, "round": 1, "sec": 1,
    "sgn": 1, "sh": 1, "sign": 1, "sin": 1, "sinh": 1, "sqrt": 1, "tan": 1,
    "tanh": 1, "tg": 1, "th": 1,
}
# L'ordre de la table compte pour `mathname_split`, qui parcourt depuis la fin.
_EVALNAME_ORDRE = list(_EVALNAME)

_FN, _VAR, _PREFIX = 1, 2, 3
# `mathname` de `rawmath.c` : nom → (style, remplacement).
_MATHNAME: dict[str, tuple[int, str]] = {
    "Arc": (_PREFIX, "arc"), "Arg": (_PREFIX, "arg"), "Ci": (_FN, ""),
    "E": (_VAR, ""), "Euler": (_VAR, ""), "I": (_VAR, ""), "Int": (_FN, ""),
    "PI": (_VAR, ""), "Pi": (_VAR, ""), "Prod": (_FN, ""), "Si": (_FN, ""),
    "Sum": (_FN, ""), "arc": (_PREFIX, ""), "arg": (_PREFIX, ""),
    "binomial": (_FN, ""), "diff": (_FN, ""), "e": (_VAR, ""),
    "erf": (_FN, ""), "euler": (_VAR, ""), "i": (_VAR, ""),
    "infinity": (_VAR, ""), "int": (_FN, ""), "integrate": (_FN, ""),
    "neq": (_VAR, ""), "pi": (_VAR, ""), "prod": (_FN, ""),
    "product": (_FN, ""), "psi": (_FN, ""), "sum": (_FN, ""),
    "theta": (_FN, ""), "x": (_VAR, ""), "y": (_VAR, ""), "z": (_VAR, ""),
    "zeta": (_FN, ""),
}
_MATHNAME_ORDRE = list(_MATHNAME)

# `hmname` : seuls les noms servent ici (la table sert aussi à `htmlmath`).
_HMNAME = frozenset((
    "CC", "Delta", "Gamma", "Inf", "Lambda", "NN", "Omega", "Phi", "Pi",
    "Psi", "QQ", "RR", "Sigma", "Xi", "ZZ", "alpha", "beta", "cap", "chi",
    "cup", "delta", "div", "divide", "epsilon", "eta", "exist", "exists",
    "forall", "gamma", "in", "inf", "infinity", "infty", "intersect",
    "intersection", "iota", "kappa", "lambda", "mu", "nabla", "neq", "nu",
    "omega", "pi", "pm", "psi", "rho", "sigma", "subset", "subseteq", "tau",
    "theta", "times", "union", "varepsilon", "varphi", "x", "xi", "y", "z",
    "zeta",
))


def _alnum(c: str) -> bool:
    """`isalnum` de la libc en locale C : l'ASCII seul."""
    return c.isascii() and c.isalnum()


def _alpha(c: str) -> bool:
    return c.isascii() and c.isalpha()


def _digit(c: str) -> bool:
    return "0" <= c <= "9" and len(c) == 1


def _cspace(c: str) -> bool:
    """`isspace` de la libc."""
    return c in (" ", "\t", "\n", "\v", "\f", "\r") and c != ""


def _myspace(c: str) -> bool:
    """`myisspace` de `libwims.h`."""
    return c in (" ", "\t", "\n", "\r") and c != ""


class _Chaine:
    """Le tampon du C : une liste de caractères, `\\0` au-delà de la fin."""

    def __init__(self, s: str):
        self.s = list(s)

    def __len__(self) -> int:
        return len(self.s)

    def c(self, k: int) -> str:
        return self.s[k] if 0 <= k < len(self.s) else ""

    def modifier(self, debut: int, fin: int, texte: str) -> None:
        """`string_modify(p, debut, fin, texte)`."""
        self.s[debut:fin] = list(texte)

    def word_start(self, k: int) -> int:
        while _myspace(self.c(k)):
            k += 1
        return k

    def find_matching(self, k: int, fermant: str) -> int | None:
        """`find_matching` de `Lib/liblines.c`, entrée après l'ouvrant."""
        if fermant == "|":
            while k < len(self.s):
                ch = self.s[k]
                if ch == "|":
                    return k
                if ch in "([{":
                    k = self.find_matching(k + 1, {"(": ")", "[": "]", "{": "}"}[ch])
                    if k is None:
                        return None
                elif ch in ")]}":
                    return None
                k += 1
            return None
        paren = brak = brace = 0
        while k < len(self.s):
            ch = self.s[k]
            if ch == "[":
                brak += 1
            elif ch == "]":
                brak -= 1
            elif ch == "(":
                paren += 1
            elif ch == ")":
                paren -= 1
            elif ch == "{":
                brace += 1
            elif ch == "}":
                brace -= 1
            else:
                k += 1
                continue
            if paren < 0 or brak < 0 or brace < 0:
                if ch != fermant or paren > 0 or brak > 0 or brace > 0:
                    return None
                break
            k += 1
        if self.c(k) != fermant:
            return None
        return k

    def mathvar_end(self, k: int) -> int:
        """`find_mathvar_end` de `Lib/math.c`."""
        c = self.c(k)
        if not (_alnum(c) or c == "."):
            return k
        if _alpha(c):
            while _alnum(self.c(k)) or self.c(k) in (".", "'") and self.c(k):
                k += 1
            return k
        t = False
        while True:
            while _digit(self.c(k)) or self.c(k) == ".":
                k += 1
            pp = k
            if t:
                return pp
            while _cspace(self.c(k)):
                k += 1
            if self.c(k) in ("e", "E"):
                t = True
                k += 1
                while _cspace(self.c(k)):
                    k += 1
                if _digit(self.c(k)):
                    continue
                if self.c(k) in ("-", "+") and _digit(self.c(k + 1)):
                    k += 1
                    continue
            return pp


def _mathname_split(mot: str) -> str | None:
    """`mathname_split` : découper un mot en noms reconnus, ou `None`.

    Seule la **première** coupure reçoit une espace ; la boucle principale
    reprend ensuite le reste comme un nouveau mot.
    """
    b = list(mot)
    p = c = 0
    while True:
        reste = "".join(b[p:])
        i = next((n for n in reversed(_EVALNAME_ORDRE) if reste.startswith(n)), None)
        if i is not None and _EVALNAME[i] > 0:
            style, j = _FN, len(i)
        else:
            n = next((n for n in reversed(_MATHNAME_ORDRE)
                      if reste.startswith(n) and _MATHNAME[n][0] != _PREFIX), None)
            if n is None:
                return None
            style, j = _MATHNAME[n][0], len(n)
        if p + j >= len(b):
            return "".join(b)
        if _digit(b[p + j]) and style != _FN:
            return None
        if not c:
            b.insert(p + j, " ")
            p += j + 1
        else:
            p += j
        c += 1


def _replace_abs(s: _Chaine) -> int:
    """`|x|` → `abs(x)` ; 1 si une barre reste sans pendant."""
    while "|" in s.s:
        p1 = s.s.index("|")
        p2 = s.find_matching(p1 + 1, "|")
        if p2 is None:
            return 1
        s.s[p2] = ")"
        s.modifier(p1, p1 + 1, "abs(")
    return 0


def _replace_plusminus(s: _Chaine) -> None:
    """`++`, `+-`, `- -`… réduits à un signe, sauf devant `>` (une flèche)."""
    p1 = 0
    while p1 < len(s):
        if s.s[p1] not in "+-":
            p1 += 1
            continue
        signe = 1 if s.s[p1] == "+" else -1
        redondant = False
        p2 = s.word_start(p1 + 1)
        while s.c(p2) in ("+", "-") and s.c(p2):
            if s.c(p2) == "-":
                signe = -signe
            redondant = True
            p2 = s.word_start(p2 + 1)
        if redondant and s.c(p2) != ">" and "".join(s.s[p2:p2 + 4]) != "&gt;":
            s.s[p1] = "+" if signe == 1 else "-"
            del s.s[p1 + 1:p2]
        p1 += 1


def _replace_space(s: _Chaine) -> None:
    """Blancs et `\\` en espace simple ; `"` en `''`."""
    p1 = 0
    while p1 < len(s):
        if s.s[p1] == "\\" or _cspace(s.s[p1]):
            s.s[p1] = " "
        if s.s[p1] == '"':
            s.modifier(p1, p1 + 1, "''")
            p1 += 1
        p1 += 1


def _treat_decimal(s: _Chaine) -> None:
    """Points décimaux pendants : `4.` → `4.0`, `.5` → `0.5`, `x.y` → `xy`."""
    p1 = "".join(s.s).find(".")
    while p1 != -1:
        suivant = p1 + 1
        if s.c(p1 + 1) == ".":
            while s.c(p1) == ".":
                p1 += 1
            suivant = p1 + 1
        elif p1 > 0 and _digit(s.c(p1 - 1)) and _digit(s.c(p1 + 1)):
            pass
        elif (p1 <= 0 or not _digit(s.c(p1 - 1))) and not _digit(s.c(p1 + 1)):
            del s.s[p1]
            suivant = p1
        else:
            if p1 == 0 or not _digit(s.c(p1 - 1)):
                s.modifier(p1, p1, "0")
                p1 += 1
            if not _digit(s.c(p1 + 1)):
                s.modifier(p1 + 1, p1 + 1, "0")
            suivant = p1 + 1
        p1 = "".join(s.s).find(".", suivant) if suivant <= len(s) else -1


def rawmath(texte: str) -> tuple[str, str]:
    """`rawmath()` : l'expression traduite, et l'avertissement de WIMS
    (`wims_warn_rawmath` : `ambiguous`, `unknown`, `flatpower`, `badprec`,
    `unmatched_parentheses`)."""
    if "\\" in texte or "{" in texte:
        return texte, ""
    flatpower = -1 if "^" not in texte else 0
    if len(texte) >= MAX_LINELEN:
        return "", ""
    s = _Chaine(texte)
    p1 = s.word_start(0)
    if p1 >= len(s):
        return texte, ""
    while s.c(p1) == "+":
        p1 += 1
    if p1 > 0:
        del s.s[:p1]
    texte = "".join(s.s).replace("**", "^").replace("\xa0", " ")
    if "\xb2" in texte:
        texte = texte.replace("\xb2", "^2 ")
        flatpower = 1
    if "\xb3" in texte:
        texte = texte.replace("\xb3", "^3 ")
        flatpower = 1
    s = _Chaine(texte)
    unmatch = _replace_abs(s)
    _replace_plusminus(s)
    _replace_space(s)
    _treat_decimal(s)

    ambiguous = unknown = badprec = 0
    if "^1/" in "".join(s.s):
        badprec = 1

    def add_star(a: int, b: int) -> int:
        """L'étiquette `add_star` : un `*` entre deux termes juxtaposés."""
        nonlocal ambiguous
        if _alnum(s.c(b)) or s.c(b) in ("(", "[") and s.c(b):
            if s.c(b) == "(" and s.c(a) == ")":
                ambiguous = 1
            if b > a:
                s.s[a] = "*"
            else:
                s.modifier(a, a, "*")
        return a

    def fnname(a: int, b: int, c: int) -> int:
        """L'étiquette `fnname1` : parenthéser l'argument d'une fonction."""
        nonlocal ambiguous, unmatch
        p1, p2 = b, c
        if s.c(p2) and s.c(p2) not in "(*/":
            hat = ")"
            if s.c(p2) == "^":
                p3 = p2 + 1
                while s.c(p3) in (" ", "+", "-") and s.c(p3):
                    p3 += 1
                if s.c(p3) == "(":
                    q = s.find_matching(p3 + 1, ")")
                    if q is None:
                        unmatch = 1
                        p3 = len(s)
                    else:
                        p3 = q + 1
                else:
                    p3 = s.mathvar_end(p3)
                hat = ")" + "".join(s.s[p2:p3])
                del s.s[p2:p3]
                while s.c(p2) == " ":
                    p2 += 1
                if s.c(p2) in ("*", "/") and s.c(p2):
                    return p1
                if s.c(p2) == "(":
                    q = s.find_matching(p2 + 1, ")")
                    if q is None:
                        unmatch = 1
                        p3 = len(s)
                    else:
                        p3 = q + 1
                    s.modifier(p3, p3, hat[1:])
                    ambiguous = 1
                    return p1
            p3 = p2
            if s.c(p3) in ("+", "-") and s.c(p3):
                p3 += 1
            while _alnum(s.c(p3)) or s.c(p3) in ("*", "/", ".") and s.c(p3):
                p3 += 1
            if not any(_alnum(s.c(k)) for k in range(p2, p3)):
                if hat[1:]:
                    s.modifier(p2, p2, hat[1:])
            else:
                s.modifier(p3, p3, hat)
                if p1 == p2:
                    s.modifier(p2, p2, "(")
                else:
                    s.s[p1] = "("
            ambiguous = 1
        return p1

    p1 = 0
    while p1 < len(s):
        c = s.s[p1]
        if not _alnum(c) and c not in (")", "]"):
            p1 += 1
            continue
        if c in (")", "]"):
            p1 += 1
            p1 = add_star(p1, s.word_start(p1))
            continue
        p2 = s.mathvar_end(p1)
        p3 = s.word_start(p2)
        if _digit(c):
            p1 = add_star(p2, p3)
            continue
        mot = "".join(s.s[p1:p2])
        if _EVALNAME.get(mot, 0) > 0:
            p1 = fnname(p1, p2, p3)
            continue
        if mot in _MATHNAME:
            style, remplace = _MATHNAME[mot]
            if remplace:
                s.modifier(p1, p2, remplace)
                p2 = p1 + len(remplace)
                p3 = s.word_start(p2)
            if style == _FN:
                p1 = fnname(p1, p2, p3)
                continue
            if style == _VAR:
                p1 = add_star(p2, p3)
                continue
            if s.c(p3) and s.c(p3) in "cstCST":
                ambiguous = 1
                del s.s[p2:p3]
                continue
        if mot in _HMNAME:
            p1 = add_star(p2, p3)
            continue
        if p2 - p1 <= 8:
            coupe = _mathname_split(mot)
            if coupe is not None:
                ambiguous = 1
                s.modifier(p1, p2, coupe)
                continue
        # Nom inconnu.
        a, b = p2, p3
        if len(mot) > 1:
            if any(_digit(x) for x in mot) and flatpower != 0:
                flatpower = 1
            else:
                unknown = 1
        elif s.c(b) == "(":
            ambiguous = 1
        if _alnum(s.c(b)):
            if b > a:
                s.s[a] = "*"
            else:
                s.modifier(a, a, "*")
        p1 = a

    avert = ""
    if ambiguous:
        avert += " ambiguous"
    if unknown:
        avert += " unknown"
    if flatpower > 0:
        avert += " flatpower"
    if badprec > 0:
        avert += " badprec"
    if unmatch > 0:
        avert += " unmatched_parentheses"
    return "".join(s.s), avert
