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
    # A bare number or simple fraction ("-23/5", "3/4") is atomic: wrapping it
    # as "(-23/5)" changes nothing arithmetically but breaks the `issamecase`/
    # `issametext` string comparisons (the parens make it differ from the
    # stored answer) — e.g. cant's irreducible-fraction check.
    if re.fullmatch(r"[+-]?\d+(?:\.\d+)?(?:\s*/\s*[+-]?\d+(?:\.\d+)?)?", stripped):
        return stripped
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

def champs_par_condition(test_instructions: list) -> dict[str, set[int]]:
    """Les réponses que chaque `condtest<k>` éprouve, relevées sur `:test`.

    Une condition ne juge pas tout l'exercice : `oefresolalg/fill2deg` en pose
    deux, dont la première ne regarde que `$m_reply4` (« le second membre est
    négatif, donc pas de solution ») et la seconde `$m_reply7`, `8` et `9`.
    Sans ce rattachement, un champ dont la condition passe se voyait peint de
    la note d'ensemble — rouge dès qu'une **autre** condition échouait, et
    l'élève ne pouvait pas savoir laquelle reprendre.

    Le relevé est textuel : on descend les `!if`/`!ifval` de `:test`, et toute
    condition dont le corps pose un `condtest<k>` livre les `$m_reply<n>`,
    `$reply<n>` et `$val<N>` qu'elle mentionne. Les `val<N>` sont ramenés au
    numéro de la réponse par la table `var_par_reponse`.

    Une condition dont on ne tire aucun champ n'est rattachée à rien : elle
    vaut alors pour tout l'exercice, ce qui est le repli sûr.
    """
    from ..def_parser import Assign, IfBlock  # noqa: PLC0415

    trouve: dict[str, set[str]] = {}

    def pose_condtest(corps: list) -> set[str]:
        noms = set()
        for instr in corps:
            if isinstance(instr, Assign) and instr.name.startswith("condtest"):
                noms.add(instr.name)
            elif isinstance(instr, IfBlock):
                noms |= pose_condtest(instr.then_body) | pose_condtest(instr.else_body)
        return noms

    def descendre(corps: list) -> None:
        for instr in corps:
            if not isinstance(instr, IfBlock):
                continue
            noms = pose_condtest(instr.then_body) | pose_condtest(instr.else_body)
            if noms:
                refs = set(re.findall(r"\$\(?\s*(?:m_)?reply(\d+)", instr.condition))
                refs |= {f"val{n}" for n in re.findall(r"\$\(?\s*val(\d+)\b", instr.condition)}
                for nom in noms:
                    trouve.setdefault(nom, set()).update(refs)
            descendre(instr.then_body)
            descendre(instr.else_body)

    descendre(test_instructions)
    return {k: v for k, v in trouve.items() if v}


def check_analyze(
    ev_ctx: dict,
    postdef_instructions: list,
    test_instructions: list,
    analyze_replies: dict,
    seed: int,
    replies_by_number: dict | None = None,
    def_path: str | None = None,
) -> tuple[dict, dict]:
    """Exécute :postdef puis :test avec les réponses élève.

    Retourne ``(condtest, weights)`` : les ``condtestN`` (0/1) et leur poids
    ``condweightN`` (défaut 1) pour un score pondéré.

    Deux jeux de variables, et il faut les deux :

    - ``val<N>`` pour un ``?analyze N``, entouré de parenthèses au besoin
      (`_analyze_wrap`) puisqu'il entre dans un calcul ;
    - ``m_reply<n>`` et ``reply<n>``, **bruts**, que WIMS rend disponibles à la
      correction pour toute réponse. `_apply_prev_replies` pose déjà le même
      couple pour les étapes d'un exercice `course`.

    Les seconds manquaient. `OEFevalwimsgrph/ineqalghyper1` en dépend
    entièrement : son `:postdef` cherche le rang de la réponse dans la liste
    des choix (`!positionof item $val115 in $val111`, où `val115` vient de
    `$m_reply1`), et son `:test` compare ce rang au bon. Sans `m_reply1`, le
    rang sortait vide et **aucune réponse ne pouvait être juste**. 121 `.def`
    lisent `$m_reply` dans leur `:postdef` ou leur `:test`, dont 47 avec un
    `?analyze`.
    """
    from . import DefEngine  # import différé — évite la circularité

    # `def_path` n'est pas un confort : `_run_slib` en deduit le repertoire du
    # module, et sans lui **tout `!readproc slib/...` d'un `:postdef` retourne
    # sans rien faire**. Les variables que le script devait poser gardent alors
    # la valeur heritee du rendu, les deux cotes d'une comparaison se retrouvent
    # egaux, et l'exercice note 1 quoi qu'on lui soumette. Releve le 2026-09-05
    # sur `numeration/compter`, ou `slib/char2item` rendait `fr` -- la langue du
    # module -- pour toute entree.
    engine = DefEngine(seed=seed, def_path=def_path)
    # On note, on n'affiche pas : un `$[…]` que le moteur ne sait pas calculer
    # vaut `NaN` et ne doit rien valider. Cf. `_eval_arith`.
    engine._strict_arith = True
    engine.ctx.update(ev_ctx)
    for var_n, value in analyze_replies.items():
        engine.ctx[f"val{var_n}"] = _analyze_wrap(value)
    for n, value in (replies_by_number or {}).items():
        engine.ctx[f"m_reply{n}"] = value
        engine.ctx[f"reply{n}"] = value
    engine._exec(postdef_instructions, output_buf=None)
    engine._exec(test_instructions, output_buf=None)
    condtest = {
        k: int(v)
        for k, v in engine.ctx.items()
        if k.startswith("condtest") and str(v).strip() in ("0", "1")
    }
    # condweightN sets the relative weight of conditionN (default 1). WIMS
    # scores `sum(testN*weightN) / sum(weightN)` — e.g. cant weights the
    # numeric value 3 and the irreducible form 1.
    weights: dict[str, float] = {}
    for k in condtest:
        wn = "condweight" + k[len("condtest"):]
        try:
            weights[k] = float(str(engine.ctx.get(wn, 1)).strip() or 1)
        except (ValueError, TypeError):
            weights[k] = 1.0
    return condtest, weights


def render_feedback(
    ev_ctx: dict,
    postdef_instructions: list,
    test_instructions: list,
    feedback_instructions: list,
    replies_by_name: dict,
    results: list,
    seed: int,
    analyze_replies: dict | None = None,
    lang: str = "fr",
    memo_replies: dict | None = None,
) -> str:
    """Exécute :postdef, :test puis :feedback ; retourne le HTML de feedback.

    `memo_replies` porte, pour les types qui la distinguent, la forme que WIMS
    **mémorise** dans `$m_reply<n>` — laquelle n'est pas toujours ce que le
    navigateur a envoyé. Un `geogebra` en est l'exemple : `$reply<n>` reste
    l'état brut de la figure, quand `$m_reply<n>` est la structure à trois
    blocs que le `:postdef` de l'exercice sait lire.
    """
    from . import DefEngine  # import différé
    from .presentation import _close_inline_math
    from ..flydraw import inline_svg_imgs

    engine = DefEngine(seed=seed)
    engine.lang = lang
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

    # Injecter les scores, dans l'écriture de WIMS.
    #
    # `str(1.0)` rend « 1.0 », et un `:postdef` qui teste `!if $m_sc_reply1=1`
    # compare des **chaînes** : « 1.0 » n'y vaut pas « 1 », si bien qu'une
    # réponse juste prenait la branche de l'échec. `oefvectdirnorm/06memenorme`
    # y félicitait l'élève d'un « Correct ! 100 % » suivi de « les vecteurs
    # n'ont pas la même norme ». `format_wims_float` écrit les nombres comme le
    # fait WIMS — « 1 », « 0.5 » —, ce que le reste du moteur emploie déjà.
    from ..numfmt import format_wims_float  # noqa: PLC0415

    for res in results:
        note = format_wims_float(res.score)
        engine.ctx[f"m_sc_{res.input_name}"] = note
        if m := re.match(r"^reply(\d+)$", res.input_name, re.I):
            engine.ctx[f"m_sc_r{m.group(1)}"] = note

    # La forme mémorisée, là où elle diffère de ce qui a été envoyé.
    for name, memo in (memo_replies or {}).items():
        engine.ctx[f"m_{name}"] = memo
        if m := re.match(r"^reply(\d+)$", name, re.I):
            engine.ctx[f"m_r{m.group(1)}"] = memo

    # Injecter les valN pour les exercices ?analyze
    if analyze_replies:
        for var_n, value in analyze_replies.items():
            engine.ctx[f"val{var_n}"] = _analyze_wrap(value)

    engine._exec(postdef_instructions, output_buf=None)
    engine._exec(test_instructions, output_buf=None)

    html = engine._render_section(feedback_instructions)
    html = _close_inline_math(html, lang)
    html = inline_svg_imgs(html)
    return html
