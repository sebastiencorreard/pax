"""
Fonctions publiques de vérification et feedback ?analyze.

Importées depuis core.oef.def_engine (re-exportées par __init__.py).

L'import de DefEngine est différé à l'intérieur des fonctions pour éviter
l'import circulaire : analyze.py ← __init__.py ← analyze.py.
"""

from __future__ import annotations

import re


# ── Helpers ───────────────────────────────────────────────────────────────────

def _analyze_wrap(value: str) -> str:
    """Entoure une réponse d'élève de parenthèses pour :postdef, mais seulement
    quand c'est nécessaire pour la précédence arithmétique (la valeur contient
    un opérateur top-level autre que parenthèses).

    Évite de wrapper :
    - une liste comma-séparée (réponse ensembliste comme "0,1") — wrapper "(0,1)"
      la transformerait en tuple Maxima, cassant is({A}={0,1}).
    - une chaîne plain text ("DB", "MQ") — wrapper "(DB)" casse les comparaisons
      ``issametext`` qui font une égalité de chaînes strict.
    - un nombre atomique ("3", "-5", "3/4") — pas besoin pour la précédence.
    """
    stripped = value.strip()
    if not stripped:
        return value
    depth = 0
    has_top_op = False
    for i, ch in enumerate(stripped):
        if ch in "([{":
            depth += 1
        elif ch in ")]}":
            depth -= 1
        elif depth == 0:
            if ch == ",":
                return value  # set-style, no wrap
            # Top-level + - * / ^ → arithmetic needs guarding.
            # Skip a leading "+" or "-" (unary sign, no op binding).
            if ch in "+-*/^" and i > 0:
                has_top_op = True
    return f"({stripped})" if has_top_op else stripped


def _parse_numeric(s: str) -> float:
    """Parse une chaîne numérique qui peut être une fraction comme '3/2'."""
    s = s.strip()
    if "/" in s:
        num, _, den = s.partition("/")
        return float(num) / float(den)
    return float(s)


# ── API publique ──────────────────────────────────────────────────────────────

def check_analyze(
    ev_ctx: dict,
    postdef_instructions: list,
    test_instructions: list,
    analyze_replies: dict,
    seed: int,
) -> dict:
    """Exécute :postdef puis :test avec les réponses élève ; retourne les condtestN."""
    from . import DefEngine  # import différé — évite la circularité

    engine = DefEngine(seed=seed)
    engine.ctx.update(ev_ctx)
    for var_n, value in analyze_replies.items():
        engine.ctx[f"val{var_n}"] = _analyze_wrap(value)
    engine._exec(postdef_instructions, output_buf=None)
    engine._exec(test_instructions, output_buf=None)
    return {
        k: int(v)
        for k, v in engine.ctx.items()
        if k.startswith("condtest") and str(v).strip() in ("0", "1")
    }


def render_feedback(
    ev_ctx: dict,
    postdef_instructions: list,
    test_instructions: list,
    feedback_instructions: list,
    replies_by_name: dict,
    results: list,
    seed: int,
    analyze_replies: dict | None = None,
) -> str:
    """Exécute :postdef, :test puis :feedback ; retourne le HTML de feedback."""
    from . import DefEngine  # import différé
    from .presentation import _close_inline_math
    from ..flydraw import inline_svg_imgs

    engine = DefEngine(seed=seed)
    engine.ctx.update(ev_ctx)

    # Vider les variables de réponse pré-existantes pour éviter les fuites
    keys_to_clear = [
        k for k in engine.ctx
        if re.match(r"^(m_)?(?:reply|r)\d+$", k, re.I)
        or re.match(r"^reply(good|name|type|option|weight)\d+$", k, re.I)
    ]
    for k in keys_to_clear:
        engine.ctx.pop(k)

    # Initialiser toutes les variables de réponse à vide
    for i in range(1, 101):
        engine.ctx[f"reply{i}"] = ""
        engine.ctx[f"m_reply{i}"] = ""
        engine.ctx[f"r{i}"] = ""
        engine.ctx[f"m_r{i}"] = ""

    # Injecter les réponses de l'élève
    for name, value in replies_by_name.items():
        engine.ctx[name] = value
        engine.ctx[f"m_{name}"] = value
        if m := re.match(r"^reply(\d+)$", name, re.I):
            engine.ctx[f"r{m.group(1)}"] = value
            engine.ctx[f"m_r{m.group(1)}"] = value

    # Injecter les scores
    for res in results:
        engine.ctx[f"m_sc_{res.input_name}"] = str(res.score)
        if m := re.match(r"^reply(\d+)$", res.input_name, re.I):
            engine.ctx[f"m_sc_r{m.group(1)}"] = str(res.score)

    # Injecter les valN pour les exercices ?analyze
    if analyze_replies:
        for var_n, value in analyze_replies.items():
            engine.ctx[f"val{var_n}"] = _analyze_wrap(value)

    engine._exec(postdef_instructions, output_buf=None)
    engine._exec(test_instructions, output_buf=None)

    html = engine._render_section(feedback_instructions)
    html = _close_inline_math(html)
    html = inline_svg_imgs(html)
    return html
