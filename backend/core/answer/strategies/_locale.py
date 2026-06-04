"""Normalisation de la virgule décimale des réponses, selon la langue.

Partagé par les stratégies ``condition`` et ``analyze`` : toutes deux injectent
la réponse élève verbatim dans le moteur WIMS, qui ne sait pas qu'en locale à
virgule (fr/nl) ``0,7`` veut dire ``0.7``. Le comparateur WIMS fait ``eval()``
sur l'opérande, et ``eval("0,7")`` produit le tuple Python ``(0, 7)`` au lieu
d'un nombre — la comparaison numérique échoue alors silencieusement.
"""

from __future__ import annotations

from core.oef.i18n import uses_comma_decimal

# Types de réponse où la virgule est SANS ambiguïté un séparateur décimal (une
# seule valeur numérique, jamais une liste). Pour ceux-là on normalise `,`→`.`
# en locale à virgule. Les types ensemblistes/textuels (set, fset, radio,
# text…) en sont exclus : la virgule peut y être un séparateur de liste.
NUMERIC_REPLY_TYPES = frozenset({"numeric", "numexp", "unit", "units", "sigunits"})


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
    """
    if uses_comma_decimal(lang) and _effective_type(ans).lower() in NUMERIC_REPLY_TYPES:
        return val.replace(",", ".")
    return val
