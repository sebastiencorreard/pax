"""
Port Python fidèle de WIMS compare.c (WIMS 4.28).

Exporte uniquement _wims_compare(), le point d'entrée public utilisé par
DefEngine._eval_condition() et _cmd_select().

Toutes les fonctions ici sont pures (pas de dépendance à DefEngine).
"""

from __future__ import annotations

import re
from typing import Callable, Optional

from . import wims_lists as wl
from .cas import _MATH_NS


# Type for the optional variable-substitution callback. Mirrors WIMS' compare.c
# behaviour: substitution happens AFTER the operator is identified, on each
# operand separately — so `<` and `>` characters inside a substituted value
# (e.g. HTML in $val6) can't be mistaken for relational operators.
_Subst = Optional[Callable[[str], str]]


def _apply_subst(subst: _Subst, s: str) -> str:
    return subst(s) if subst is not None else s


# ── Tables sémantiques (compare.c relation_type[]) ───────────────────────────

_WIMS_RELATION_TYPES = [
    "sametext", "samecase",
    "in", "wordof", "itemof", "lineof", "varof", "variableof",
]
_WIMS_PREFIX_CHARS = frozenset("siwlv")


# ── Normalisation ─────────────────────────────────────────────────────────────

def _wims_bufprep(s: str) -> str:
    """Collapse whitespace (bufprep in compare.c)."""
    return " ".join(s.split())


def _wims_strip_all_parens(s: str) -> str:
    """Strip every layer of balanced outer parens (while loop in compare.c)."""
    while True:
        s = s.strip()
        if len(s) < 2 or s[0] != "(" or s[-1] != ")":
            break
        depth = 0
        fully_wrapped = True
        for i, ch in enumerate(s):
            if ch == "(":
                depth += 1
            elif ch == ")":
                depth -= 1
            if depth == 0 and i < len(s) - 1:
                fully_wrapped = False
                break
        if not fully_wrapped:
            break
        s = s[1:-1]
    return s.strip()


# ── Logique / opérateurs ──────────────────────────────────────────────────────

def _wims_find_top_logic(s: str, op: str) -> tuple[str, str] | None:
    """Retourne (lhs, rhs) pour la 1ère occurrence de *op* au niveau 0, ou None."""
    n = len(s)
    depth = 0
    op_len = len(op)
    i = 0
    while i < n:
        ch = s[i]
        if ch == "(":
            depth += 1; i += 1; continue
        elif ch == ")":
            depth -= 1; i += 1; continue
        if depth != 0:
            i += 1; continue
        if ch.isspace():
            j = i + 1
            while j < n and s[j].isspace():
                j += 1
            if s[j:j + op_len].lower() == op:
                end = j + op_len
                if end >= n or not (s[end].isalnum() or s[end] == "_"):
                    k = end
                    while k < n and s[k].isspace():
                        k += 1
                    return s[:i].strip(), s[k:].strip()
        i += 1
    return None


# ── Comparaison numérique ─────────────────────────────────────────────────────

def _wims_numeric_eq(d1: float, d2: float, prec: float = 10000.0) -> bool:
    """Formule de précision WIMS : |d1-d2|*prec <= |d1+d2| + 1/prec."""
    diff = abs(d1 - d2) * prec
    total = abs(d1 + d2)
    if 0 < prec < 1e10:
        total += 1.0 / prec
    return total >= diff


def _wims_eval_num(expr: str) -> float | None:
    """Évalue expr en float; None si impossible.

    **Une chaîne vide vaut zéro**, comme chez WIMS : l'évaluateur y sort dès le
    premier caractère (`Lib/evalue.c:324`, `if(*evalue_pt==0) return 0;`). Sans
    cela `_wims_relational` ne trouvait pas de nombre et retombait sur une
    comparaison *textuelle*, où `"" == "0"` est faux.

    Le cas n'est pas théorique : un `.def` teste couramment le résultat d'un
    calcul qui a pu ne rien rendre, pour se rabattre sur une autre voie —
    `oefpytha/etagere2` cherche un triplet pythagoricien par `!exec pari`, et
    sur `pyth(522,124,25)` il n'en existe aucun. Son `!ifval $(val18[1])==0`
    devait déclencher une seconde recherche, plus large, qui aboutit
    (`(672,754,1010)`). Le test étant faux, le repli ne partait pas : `val14`
    restait vide, et l'énoncé sortait `[-1,,+2,-3]/10.` — l'expression PARI
    elle-même, avec son trou, en guise de palette.

    Mesuré sur le corpus : 4406 comparaisons portent un opérande vide sans que
    le verdict change, 1002 ont l'autre opérande inévaluable (rien ne bouge non
    plus), et **246, sur 14 exercices, avaient le verdict inversé**.
    """
    s = expr.strip()
    if not s:
        return 0.0
    try:
        result = eval(s.replace("^", "**"), {"__builtins__": {}}, _MATH_NS)
        return float(result)
    except Exception:
        return None


# ── Opérateurs sémantiques ────────────────────────────────────────────────────

def _wims_semantic_op(lhs: str, r: int, neg: bool, rhs: str) -> bool:
    """Évalue un opérateur sémantique (r = index+1 dans relation_type[] de compare.c)."""
    b1 = lhs.strip()
    b2 = rhs.strip()
    if r == 1:
        result = _wims_bufprep(b1).lower() == _wims_bufprep(b2).lower()
    elif r == 2:
        result = _wims_bufprep(b1) == _wims_bufprep(b2)
    elif r == 3:
        result = b1 in b2
    elif r == 4:
        words = [w.strip() for w in re.split(r"[\s,]+", b2) if w.strip()]
        result = b1 in words
    elif r == 5:
        # `itemchr(buf2,buf1)`, sans rien autour (compare.c:165). Ce n'est pas
        # une égalité item à item mais une recherche de sous-chaîne encadrée de
        # frontières — d'où le fait qu'un `[ligne,colonne]` s'y retrouve entier
        # dans une liste de couples (slib/function/tabsignes) sans qu'aucune
        # protection de crochets soit nécessaire.
        result = wl.itemchr(b2, b1)
    elif r == 6:
        result = b1 in [x.strip() for x in b2.splitlines()]
    elif r in (7, 8):
        result = b1 in [x.strip() for x in re.split(r"\s+", b2)]
    else:
        result = False
    return result ^ neg


# ── Comparaison relationnelle ─────────────────────────────────────────────────

def _wims_relational(lhs: str, rhs: str, op_code: int, neg: bool, numeric: bool) -> bool:
    """Évalue un opérateur relationnel (codes r de compare.c)."""
    if op_code == 0:
        return (lhs == rhs) ^ neg

    d1 = _wims_eval_num(lhs)
    d2 = _wims_eval_num(rhs)
    if d1 is None or d2 is None:
        if op_code == 101:
            return (lhs == rhs) ^ neg
        return False

    if op_code == 101:
        r = _wims_numeric_eq(d1, d2)
    elif op_code == 102:
        r = d1 < d2
    elif op_code == 103:
        r = d1 > d2
    else:
        return False
    return r ^ neg


# ── Comparaison atomique ──────────────────────────────────────────────────────

def _wims_compare_atomic(s: str, numeric: bool, subst: _Subst = None) -> bool:
    """Évalue une condition atomique WIMS (sans and/or au niveau supérieur).

    Si ``subst`` est fourni, il est appliqué à LHS/RHS *après* l'identification
    de l'opérateur — comme WIMS compare.c qui appelle ``substitute(buf1)`` /
    ``substitute(buf2)`` sur chaque opérande extrait. C'est ce qui empêche les
    `<` et `>` à l'intérieur d'une valeur substituée (HTML d'un `$val6`)
    d'être pris pour des opérateurs relationnels.
    """
    n = len(s)
    # Cas LHS vide : si la condition commence directement par ``is…`` / ``not…``
    # (sans LHS), évaluer avec lhs="" — utile pour le pattern WIMS
    # ``!if $var notwordof a b c`` quand $var est vide.
    if n > 0 and not s[0].isspace():
        for prefix, neg, k_start in (("not", True, 3), ("is", False, 2)):
            if s[:k_start].lower() == prefix and k_start < n and s[k_start].lower() in _WIMS_PREFIX_CHARS:
                for ri, rt in enumerate(_WIMS_RELATION_TYPES):
                    rt_len = len(rt)
                    if s[k_start:k_start + rt_len].lower() == rt:
                        after = k_start + rt_len
                        if after >= n or not (s[after].isalnum() or s[after] == "_"):
                            return _wims_semantic_op("", ri + 1, neg, _apply_subst(subst, s[after:].strip()))
                break  # matched is/not but no relation type
    depth = 0
    i = 0
    rel: dict | None = None

    while i < n:
        ch = s[i]
        if ch == "(":
            depth += 1; i += 1; continue
        elif ch == ")":
            depth -= 1; i += 1; continue
        if depth != 0:
            i += 1; continue

        if not ch.isspace():
            if rel is None and ch in "<>=!":
                if ch == "<":
                    if not s[:i].strip():
                        i += 1; continue
                    if i + 1 < n and s[i + 1] == "=":
                        rel = {"lhs_end": i, "rhs_start": i + 2, "op": 103, "neg": True}
                        i += 2
                    elif i + 1 < n and s[i + 1] == ">":
                        op = 101 if numeric else 0
                        rel = {"lhs_end": i, "rhs_start": i + 2, "op": op, "neg": True}
                        i += 2
                    else:
                        rel = {"lhs_end": i, "rhs_start": i + 1, "op": 102, "neg": False}
                        i += 1
                    continue
                elif ch == ">":
                    if not s[:i].strip():
                        i += 1; continue
                    if i + 1 < n and s[i + 1] == "=":
                        rel = {"lhs_end": i, "rhs_start": i + 2, "op": 102, "neg": True}
                        i += 2
                    else:
                        rel = {"lhs_end": i, "rhs_start": i + 1, "op": 103, "neg": False}
                        i += 1
                    continue
                elif ch == "=":
                    end = i + 2 if (i + 1 < n and s[i + 1] == "=") else i + 1
                    op = 101 if numeric else 0
                    rel = {"lhs_end": i, "rhs_start": end, "op": op, "neg": False}
                    i = end
                    continue
                elif ch == "!" and i + 1 < n and s[i + 1] == "=":
                    op = 101 if numeric else 0
                    rel = {"lhs_end": i, "rhs_start": i + 2, "op": op, "neg": True}
                    i += 2
                    continue
            i += 1
            continue

        j = i + 1
        while j < n and s[j].isspace():
            j += 1
        if j >= n:
            i += 1; continue

        word = s[j:]

        if rel is None:
            # isnotreexpanded : pseudo-op WIMS interne, traité comme sametext
            _INR = "isnotreexpanded"
            if word[:15].lower() == _INR:
                after = 15
                if after >= len(word) or not (word[after].isalnum() or word[after] == "_"):
                    return _wims_semantic_op(s[:i].strip(), 1, False, word[15:].strip())

            if word[:2].lower() == "is":
                k, neg = 2, False
            elif word[:3].lower() == "not":
                k, neg = 3, True
            else:
                i += 1; continue

            if k >= len(word) or word[k].lower() not in _WIMS_PREFIX_CHARS:
                i += 1; continue

            for ri, rt in enumerate(_WIMS_RELATION_TYPES):
                rt_len = len(rt)
                if word[k:k + rt_len].lower() == rt:
                    after = k + rt_len
                    if after >= len(word) or not (word[after].isalnum() or word[after] == "_"):
                        return _wims_semantic_op(
                            _apply_subst(subst, s[:i].strip()),
                            ri + 1, neg,
                            _apply_subst(subst, word[k + rt_len:].strip()),
                        )

        i += 1

    if rel is not None:
        lhs = _apply_subst(subst, s[:rel["lhs_end"]].strip())
        rhs = _apply_subst(subst, s[rel["rhs_start"]:].strip())
        return _wims_relational(lhs, rhs, rel["op"], rel["neg"], numeric)

    return False


# ── Point d'entrée public ─────────────────────────────────────────────────────

def _wims_compare(cond: str, numeric: bool, subst: _Subst = None) -> bool:
    """
    Port Python de compare() dans WIMS compare.c.

    numeric=True pour !ifval (= numérique avec précision),
    False pour !if (= comparaison de chaînes).

    ``subst`` est appelé tardivement sur LHS/RHS, après identification de
    l'opérateur — appelants : passer ``self._subst`` au lieu de pré-substituer
    pour éviter qu'un ``<`` ou ``>`` HTML dans un opérande soit pris pour un
    opérateur relationnel (cf. compare.c qui appelle ``substitute(buf1/buf2)``
    seulement après avoir borné chaque côté).
    """
    cond = _wims_strip_all_parens(cond)
    if not cond:
        return False

    split = _wims_find_top_logic(cond, "or") or _wims_find_top_logic(cond, "||")
    if split is not None:
        lhs, rhs = split
        return _wims_compare(lhs, numeric, subst) or _wims_compare(rhs, numeric, subst)

    split = _wims_find_top_logic(cond, "and") or _wims_find_top_logic(cond, "&&")
    if split is not None:
        lhs, rhs = split
        return _wims_compare(lhs, numeric, subst) and _wims_compare(rhs, numeric, subst)

    return _wims_compare_atomic(cond, numeric, subst)
