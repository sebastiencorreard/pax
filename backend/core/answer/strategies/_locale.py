"""Normalisation de la virgule décimale des réponses, selon la langue.

Partagé par les stratégies ``condition`` et ``analyze`` : toutes deux injectent
la réponse élève verbatim dans le moteur WIMS, qui ne sait pas qu'en locale à
virgule (fr/nl) ``0,7`` veut dire ``0.7``. Le comparateur WIMS fait ``eval()``
sur l'opérande, et ``eval("0,7")`` produit le tuple Python ``(0, 7)`` au lieu
d'un nombre — la comparaison numérique échoue alors silencieusement.
"""

from __future__ import annotations

import unicodedata

from core.oef.i18n import uses_comma_decimal

# Types de réponse où la virgule est SANS ambiguïté un séparateur décimal (une
# seule valeur numérique, jamais une liste). Pour ceux-là on normalise `,`→`.`
# en locale à virgule. Les types ensemblistes/textuels (set, fset, radio,
# text…) en sont exclus : la virgule peut y être un séparateur de liste.
NUMERIC_REPLY_TYPES = frozenset({"numeric", "numexp", "unit", "units", "sigunits"})

# `auto` n'est pas un type : `oef/replytype.proc` l'aliase vers `default`
# (première entrée de `rt_names`, première de `rt_types`).
_DEFAULT_ALIASES = frozenset({"default", "auto"})


def _default_is_numeric(expected: str) -> bool:
    """Vrai si un `default` se comporterait en `numeric` — cf. `anstype/default` :

        eq==
        !if $eq isin $(replygood$i) … !changeto anstype/equation
        accent=!deaccent $(replygood$i)
        !if $accent!=$(replygood$i) … !changeto anstype/atext
        nn=$[$(replygood$i)]
        !if NaN notin $nn
          !changeto anstype/numeric

    L'attendu qui s'évalue en nombre fait donc de la réponse un nombre, et de
    sa virgule une décimale. Les deux branches qui précèdent sont reprises
    telles quelles : un `=` en fait une équation, un accent un texte.
    """
    from core.answer.checkers import _parse_number  # noqa: PLC0415

    s = (expected or "").strip()
    if not s or "=" in s:
        return False
    if any(unicodedata.combining(c) for c in unicodedata.normalize("NFD", s)):
        return False
    try:
        _parse_number(s, comma_is_decimal=False)
    except (ValueError, ZeroDivisionError, SyntaxError, TypeError):
        return False
    return True


def _effective_type(ans) -> str:
    """Type WIMS d'origine de la réponse.

    Une réponse ``numeric`` vérifiée via ``?analyze`` est exposée avec
    ``answer_type == "analyze"`` ; le type de l'auteur est alors préservé dans
    ``options["analyze_input_type"]`` (cf. def_engine). On le lit pour décider
    si la virgule est décimale.
    """
    if ans.answer_type == "analyze":
        return str(ans.options.get("analyze_input_type", "analyze"))
    return ans.answer_type


def normalize_decimal_reply(val: str, ans, lang: str | None) -> str:
    """Remplace la virgule décimale par un point pour les réponses numériques.

    Sans effet sur ``0.7`` (pas de virgule), sur les types non numériques, ni
    hors locale à virgule.

    Un ``default``/``auto`` en fait partie **quand son attendu est un nombre** :
    `anstype/default` bascule alors sur `anstype/numeric` (cf.
    :func:`_default_is_numeric`), et la virgule y est décimale au même titre.
    Sans cela `quizz/pourappl` refusait ``9,41`` en français tout en acceptant
    ``9.41``.
    """
    if not uses_comma_decimal(lang):
        return val
    t = _effective_type(ans).lower()
    if t in NUMERIC_REPLY_TYPES:
        return val.replace(",", ".")
    if t in _DEFAULT_ALIASES and _default_is_numeric(getattr(ans, "expected", "")):
        return val.replace(",", ".")
    return val
