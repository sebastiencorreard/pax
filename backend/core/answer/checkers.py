"""
Vérificateurs de réponses par type OEF.
Chaque checker reçoit la réponse de l'élève et la valeur attendue,
et retourne un CheckResult.
"""
from __future__ import annotations
from dataclasses import dataclass
from fractions import Fraction
import re


@dataclass
class CheckResult:
    correct: bool
    score: float          # 0.0 à 1.0
    method: str           # "numeric", "sympy", "exact", ...
    detail: str = ""      # message optionnel pour le feedback


# ------------------------------------------------------------------ #
# Numérique                                                            #
# ------------------------------------------------------------------ #

def check_numeric(reply: str, expected: str, precision: float = 1e-4) -> CheckResult:
    """
    Compare deux nombres avec tolérance relative + absolue.
    Accepte les fractions (1/2), les expressions simples (2*3).
    """
    try:
        r = _parse_number(reply.strip())
        e = _parse_number(expected.strip())
    except (ValueError, ZeroDivisionError, SyntaxError):
        return CheckResult(correct=False, score=0.0, method="numeric",
                           detail="Réponse non reconnue comme un nombre")

    abs_err = abs(r - e)
    rel_err = abs_err / (abs(e) + 1e-12)
    correct = abs_err <= precision or rel_err <= precision

    return CheckResult(correct=correct, score=1.0 if correct else 0.0, method="numeric")


def _parse_number(s: str) -> float:
    """Parse un nombre : entier, décimal, fraction, expression simple."""
    s = s.replace(",", ".").replace("^", "**").strip()
    # Fraction explicite ex: 3/4
    if re.fullmatch(r'-?\d+\s*/\s*-?\d+', s):
        return float(Fraction(s.replace(" ", "")))
    # Expression arithmétique simple (pas d'appel de fonction)
    if re.fullmatch(r'[\d\s\+\-\*\/\.\(\)\^]+', s):
        return float(eval(s, {"__builtins__": {}}))
    raise ValueError(f"Impossible de parser: {s!r}")


# ------------------------------------------------------------------ #
# Expression algébrique — SymPy                                        #
# ------------------------------------------------------------------ #

def check_algexp(reply: str, expected: str) -> CheckResult:
    """
    Compare deux expressions algébriques via SymPy.
    Correct si la différence se simplifie à 0.
    """
    try:
        import sympy
        from sympy.parsing.sympy_parser import (
            parse_expr, standard_transformations, implicit_multiplication_application
        )
        transformations = standard_transformations + (implicit_multiplication_application,)

        local_dict = {"expand": sympy.expand, "factor": sympy.factor,
                      "simplify": sympy.simplify}
        r_expr = parse_expr(_normalize_expr(reply), transformations=transformations,
                            local_dict=local_dict)
        e_expr = parse_expr(_normalize_expr(expected), transformations=transformations,
                            local_dict=local_dict)

        diff = sympy.simplify(sympy.expand(r_expr) - sympy.expand(e_expr))
        correct = diff == 0

        return CheckResult(correct=correct, score=1.0 if correct else 0.0, method="sympy")

    except Exception as ex:
        # Fallback : comparaison numérique en plusieurs points
        return _check_algexp_numeric(reply, expected)


def _normalize_expr(expr: str) -> str:
    """Normalise une expression OEF/élève pour SymPy."""
    expr = expr.strip()
    # Exposants Unicode → notation ^
    superscripts = {'⁰':'0','¹':'1','²':'2','³':'3','⁴':'4',
                    '⁵':'5','⁶':'6','⁷':'7','⁸':'8','⁹':'9'}
    for sup, digit in superscripts.items():
        expr = expr.replace(sup, f'^{digit}')
    expr = expr.replace("^", "**")
    expr = expr.replace("\\times", "*")
    expr = expr.replace("\\cdot", "*")
    # Supprime les espaces autour des opérateurs
    expr = re.sub(r'\s+', '', expr)
    return expr


def _check_algexp_numeric(reply: str, expected: str) -> CheckResult:
    """
    Fallback : évalue les deux expressions en plusieurs points et compare.
    Fonctionne pour des polynômes en x, y.
    """
    try:
        import sympy
        x, y, z = sympy.symbols('x y z')
        test_points = [
            {x: 1, y: 2, z: 3},
            {x: -1, y: 3, z: -2},
            {x: 2, y: -1, z: 1},
            {x: 0.5, y: 1.5, z: -0.5},
        ]
        r_expr = sympy.sympify(_normalize_expr(reply))
        e_expr = sympy.sympify(_normalize_expr(expected))

        for pt in test_points:
            r_val = complex(r_expr.subs(pt))
            e_val = complex(e_expr.subs(pt))
            if abs(r_val - e_val) > 1e-6:
                return CheckResult(correct=False, score=0.0, method="numeric_fallback")

        return CheckResult(correct=True, score=1.0, method="numeric_fallback")
    except Exception:
        return CheckResult(correct=False, score=0.0, method="error",
                           detail="Impossible de vérifier l'expression")


# ------------------------------------------------------------------ #
# Expression numérique (numexp)                                        #
# ------------------------------------------------------------------ #

def check_numexp(reply: str, expected: str, precision: float = 1e-4) -> CheckResult:
    """
    Évalue les deux expressions numériquement et compare.
    Ex: reply="2+3", expected="5"
    """
    try:
        import sympy
        r_val = float(sympy.sympify(_normalize_expr(reply)))
        e_val = float(sympy.sympify(_normalize_expr(expected)))
        correct = abs(r_val - e_val) <= precision or abs(r_val - e_val) / (abs(e_val) + 1e-12) <= precision
        return CheckResult(correct=correct, score=1.0 if correct else 0.0, method="numexp")
    except Exception:
        return check_numeric(reply, expected, precision)


# ------------------------------------------------------------------ #
# Ensemble (set)                                                       #
# ------------------------------------------------------------------ #

def check_set(reply: str, expected: str) -> CheckResult:
    """
    Compare deux ensembles de valeurs (séparées par des virgules ou des ;).
    Ordre non significatif.
    """
    def parse_set(s: str) -> set:
        sep = ";" if ";" in s else ","
        return {x.strip().lower() for x in s.split(sep) if x.strip()}

    r_set = parse_set(reply)
    e_set = parse_set(expected)

    if r_set == e_set:
        return CheckResult(correct=True, score=1.0, method="set")

    # Score partiel : proportion d'éléments corrects
    intersection = r_set & e_set
    score = len(intersection) / max(len(e_set), 1) if e_set else 0.0
    return CheckResult(correct=False, score=score, method="set")


# ------------------------------------------------------------------ #
# Choix (radio, checkbox, clickfill)                                   #
# ------------------------------------------------------------------ #

def check_radio(reply: str, expected: str) -> CheckResult:
    """Comparaison exacte insensible à la casse et aux espaces."""
    correct = reply.strip().lower() == expected.strip().lower()
    return CheckResult(correct=correct, score=1.0 if correct else 0.0, method="exact")


def check_text(reply: str, expected: str) -> CheckResult:
    """Comparaison de texte insensible à la casse."""
    correct = reply.strip().lower() == expected.strip().lower()
    return CheckResult(correct=correct, score=1.0 if correct else 0.0, method="text")


# ------------------------------------------------------------------ #
# Dispatcher principal                                                  #
# ------------------------------------------------------------------ #

def check_answer(
    answer_type: str,
    reply: str,
    expected: str,
    options: dict | None = None,
) -> CheckResult:
    """
    Point d'entrée unique. Dispatch vers le bon checker selon le type.
    """
    options = options or {}
    precision = float(options.get("precision", 1e-4))

    match answer_type.lower():
        case "numeric":
            return check_numeric(reply, expected, precision)
        case "numexp":
            return check_numexp(reply, expected, precision)
        case "algexp" | "litexp" | "formal":
            return check_algexp(reply, expected)
        case "set":
            return check_set(reply, expected)
        case "radio" | "menu" | "clickfill":
            return check_radio(reply, expected)
        case "text" | "default" | _:
            return check_text(reply, expected)
