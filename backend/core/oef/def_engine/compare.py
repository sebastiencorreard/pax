"""
Port Python fidèle de WIMS compare.c (WIMS 4.28).

Exporte uniquement _wims_compare(), le point d'entrée public utilisé par
DefEngine._eval_condition() et _cmd_select().

Toutes les fonctions ici sont pures (pas de dépendance à DefEngine).
"""

from __future__ import annotations

import re

from .cas import _MATH_NS


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
    """Évalue expr en float; None si impossible."""
    try:
        result = eval(expr.strip().replace("^", "**"), {"__builtins__": {}}, _MATH_NS)
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
        result = b1 in [x.strip() for x in b2.split(",")]
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

def _wims_compare_atomic(s: str, numeric: bool) -> bool:
    """Évalue une condition atomique WIMS (sans and/or au niveau supérieur)."""
    n = len(s)
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
                        return _wims_semantic_op(s[:i].strip(), ri + 1, neg, word[k + rt_len:].strip())

        i += 1

    if rel is not None:
        lhs = s[:rel["lhs_end"]].strip()
        rhs = s[rel["rhs_start"]:].strip()
        return _wims_relational(lhs, rhs, rel["op"], rel["neg"], numeric)

    return False


# ── Point d'entrée public ─────────────────────────────────────────────────────

def _wims_compare(cond: str, numeric: bool) -> bool:
    """
    Port Python de compare() dans WIMS compare.c.

    numeric=True pour !ifval (= numérique avec précision),
    False pour !if (= comparaison de chaînes).
    """
    cond = _wims_strip_all_parens(cond)
    if not cond:
        return False

    split = _wims_find_top_logic(cond, "or") or _wims_find_top_logic(cond, "||")
    if split is not None:
        lhs, rhs = split
        return _wims_compare(lhs, numeric) or _wims_compare(rhs, numeric)

    split = _wims_find_top_logic(cond, "and") or _wims_find_top_logic(cond, "&&")
    if split is not None:
        lhs, rhs = split
        return _wims_compare(lhs, numeric) and _wims_compare(rhs, numeric)

    return _wims_compare_atomic(cond, numeric)
