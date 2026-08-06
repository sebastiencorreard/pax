"""Séparateur décimal piloté par la locale : config, affichage, saisie.

Couvre les trois couches du correctif :
  1. ``core/oef/i18n.py`` — config (décimale/liste par locale).
  2. ``presentation._normalize_math_content`` — affichage math sûr (pas de tuple)
     + virgule décimale en locale à virgule.
  3. ``checkers`` — saisie locale-aware (virgule décimale seulement où pertinent ;
     listes multi-valeurs tolérantes).
Et le bout-en-bout : rendu de ``0615.def`` sans bruit flottant ni tuple.
"""

from __future__ import annotations

import os

import pytest

from core.oef.i18n import decimal_separator, list_separator, uses_comma_decimal
from core.oef.numfmt import format_wims_float
from core.oef.def_engine.presentation import _normalize_math_content as N
from core.oef.def_engine.presentation import localize_decimals
from core.answer.checkers import check_answer, check_fset, check_numeric, _parse_number


# ── 1. Config locale ──────────────────────────────────────────────────────────

def test_decimal_separator_by_locale():
    assert decimal_separator("fr") == ","
    assert decimal_separator("nl") == ","
    assert decimal_separator("fr-BE") == ","      # sous-tag ignoré
    assert decimal_separator("en") == "."
    assert decimal_separator("de") == "."         # langue non configurée → point
    assert decimal_separator(None) == ","         # défaut français


def test_list_separator_pairs_with_decimal():
    assert list_separator("fr") == ";"
    assert list_separator("en") == ","
    # décimale et séparateur de liste toujours distincts dans une locale
    for lang in ("fr", "nl", "en", "de"):
        assert decimal_separator(lang) != list_separator(lang)


def test_uses_comma_decimal():
    assert uses_comma_decimal("fr") is True
    assert uses_comma_decimal("en") is False


# ── 2bis. Anti-bruit flottant ────────────────────────────────────────────────

def test_format_wims_float_strips_binary_noise():
    assert format_wims_float(2 + 0.9 + 0.05) == "2.95"
    assert format_wims_float(3.9299999999999997) == "3.93"
    assert format_wims_float(7.0) == "7"           # entier → sans décimale
    assert format_wims_float(1 / 3) == "0.333333333333"


# ── 2. Affichage math ────────────────────────────────────────────────────────

def test_standalone_decimal_not_turned_into_tuple():
    # Le bug d'origine : sympify("3,93") → \left( 3, \  93\right).
    out = N("3,93", "fr")
    assert out == "3,93"
    assert "\\left(" not in out


def test_decimal_uses_locale_separator():
    assert N("3.93", "fr") == "3,93"      # point → virgule (auteur sans !replace)
    assert N("3,93", "fr") == "3,93"
    assert N("-2.5", "fr") == "-2,5"
    assert N("3.93", "en") == "3.93"      # locale à point : inchangé
    assert N("3,93", "en") == "3,93"      # locale à point : laissé tel quel


def test_scientific_notation_space_becomes_times():
    # WIMS juxtaposes mantissa and power of ten with a bare space (`5 10^2`,
    # from `\c4 10^\m4`); KaTeX would collapse it to `510^2`. Make the product
    # explicit so it reads `5 × 10²` (quizz 1104).
    assert N("5 10^2", "fr") == r"5 \times 10^2"
    assert N("4 10^2+2+5 10^-1", "fr") == r"4 \times 10^2+2+5 \times 10^{-1}"
    # A multi-digit mantissa keeps its digits together.
    assert N("12 10^3", "fr") == r"12 \times 10^3"


def test_localize_decimals_text_and_math_not_tags():
    # Bare numbers (table cells / labels) and dots inside \(…\) math are
    # localised; HTML tag attributes are left untouched.
    assert localize_decimals("<td>1.21</td>", "fr") == "<td>1,21</td>"
    assert localize_decimals(r"\(\sqrt{0.3}\)", "fr") == r"\(\sqrt{0,3}\)"
    assert localize_decimals('<img src="a/0.5.png">', "fr") == '<img src="a/0.5.png">'
    # A math "<" is not an HTML tag → text around it still localised.
    assert localize_decimals(r"\(x<2.5\)", "fr") == r"\(x<2,5\)"
    # Dot locale: unchanged.
    assert localize_decimals("<td>1.21</td>", "en") == "<td>1.21</td>"


def test_function_call_comma_is_not_a_decimal():
    # f(a,b) n'est pas un nombre décimal isolé → la virgule reste un séparateur.
    out = N("f(a,b)", "fr")
    assert not out.startswith("3")  # sanity
    assert "a" in out and "b" in out


# ── 3. Saisie locale-aware ───────────────────────────────────────────────────

def test_numeric_comma_accepted_in_comma_locale():
    assert check_answer("numeric", "3,93", "3.93", lang="fr").correct
    assert check_answer("numeric", "3.93", "3.93", lang="fr").correct  # point aussi


def test_numeric_comma_rejected_in_dot_locale():
    # En locale à point, la virgule n'est PAS un séparateur décimal.
    assert not check_answer("numeric", "3,5", "3.5", lang="en").correct
    assert check_answer("numeric", "3.5", "3.5", lang="en").correct


def test_parse_number_respects_comma_flag():
    assert _parse_number("3,5", comma_is_decimal=True) == 3.5
    assert _parse_number("3.5", comma_is_decimal=True) == 3.5
    with pytest.raises(ValueError):
        _parse_number("3,5", comma_is_decimal=False)


def test_fset_single_decimal_in_comma_locale():
    assert check_fset("2,5", "2.5", comma_is_decimal=True).correct


def test_fset_semicolon_separated_decimals():
    assert check_fset("2,5;3,7", "2.5;3.7", comma_is_decimal=True).correct


def test_fset_tolerant_comma_list():
    # Sans ';', '2,5' accepté comme liste {2;5} si ça colle mieux à l'attendu.
    assert check_fset("2,5", "2;5", comma_is_decimal=True).correct


def test_fset_backward_compatible_comma_list_dot_decimal():
    # Convention historique : virgule = liste, point = décimale (toujours OK).
    assert check_fset("-1.125,-4", "-9/8,-8/2").correct
    assert check_fset("-6/5,-9/8", "-9/8,-6/5").correct


# ── Bout-en-bout ─────────────────────────────────────────────────────────────

_DEF_0615 = "/ressources/H3/math/quizz.fr/def/0615.def"


@pytest.mark.skipif(not os.path.exists(_DEF_0615), reason="corpus absent")
def test_render_0615_clean_decimal():
    from core.oef.def_engine import load_and_render

    r = load_and_render(_DEF_0615, seed=722630044)
    html = " ".join(s["content"] for s in r.statement_segments if s.get("type") == "html")
    assert "\\left(" not in html               # pas de tuple
    assert "9999999" not in html               # pas de bruit flottant
    assert "2,95" in html                       # décimale française correcte


# ── Corrigé : localisation transverse (PAX_LOCALIZE_FEEDBACK) ────────────────


class TestLocalizeDecimals:
    """`i18n.localize_decimals` — la virgule décimale du corrigé.

    Confort d'affichage posé en une passe sur les corrigés numériques
    (`api/routes/check.py`), pas une règle du moteur : la notation accepte les
    deux écritures dans tous les cas.
    """

    def test_decimal_point_becomes_a_comma(self):
        from core.oef.i18n import localize_decimals
        assert localize_decimals("4.76", "fr") == "4,76"
        assert localize_decimals("0.5", "nl") == "0,5"

    def test_dot_decimal_languages_are_untouched(self):
        from core.oef.i18n import localize_decimals
        assert localize_decimals("4.76", "en") == "4.76"

    def test_only_between_two_digits(self):
        """Un point de nom de fichier, de version ou de phrase ne bouge pas."""
        from core.oef.i18n import localize_decimals
        assert localize_decimals("x2.png", "fr") == "x2.png"
        assert localize_decimals("fig.2", "fr") == "fig.2"
        assert localize_decimals("Fin de phrase.", "fr") == "Fin de phrase."
        assert localize_decimals("/api/static/a/b2.jpg", "fr") == "/api/static/a/b2.jpg"

    def test_several_numbers_in_one_string(self):
        from core.oef.i18n import localize_decimals
        assert localize_decimals("1.5 et 2.25", "fr") == "1,5 et 2,25"

    def test_is_idempotent(self):
        from core.oef.i18n import localize_decimals
        once = localize_decimals("4.76", "fr")
        assert localize_decimals(once, "fr") == once

    def test_empty_and_none_survive(self):
        from core.oef.i18n import localize_decimals
        assert localize_decimals("", "fr") == ""
        assert localize_decimals("abc", "fr") == "abc"

    def test_list_separator_is_left_alone(self):
        """Une fois la virgule posée, on ne peut plus la distinguer d'un
        séparateur : la fonction n'y touche donc jamais."""
        from core.oef.i18n import localize_decimals
        assert localize_decimals("1,2", "fr") == "1,2"


class TestLocalizedFeedbackTypes:
    """Le périmètre de la passe : les types dont la réponse est un nombre."""

    def test_text_types_are_excluded(self):
        """Un `atext` répond « 3.5 pouces », un `runcode` du Python : le point
        y a d'autres rôles que celui de décimale."""
        from api.routes.check import _LOCALIZED_FEEDBACK_TYPES
        for t in ("atext", "raw", "case", "nocase", "correspond", "runcode", "radio"):
            assert t not in _LOCALIZED_FEEDBACK_TYPES

    def test_multi_component_types_are_excluded(self):
        """Leur virgule sépare déjà les composantes : localiser les points d'un
        `coord` attendu `2.5,3.5` donnerait `2,5,3,5`, illisible."""
        from api.routes.check import _LOCALIZED_FEEDBACK_TYPES
        for t in ("coord", "vector", "jsxgraph", "set", "fset", "matrix"):
            assert t not in _LOCALIZED_FEEDBACK_TYPES

    def test_a_coord_expected_is_left_alone(self):
        from types import SimpleNamespace
        from api.routes.check import _localize_feedback
        r = [SimpleNamespace(input_name="r1", expected="2.5,3.5")]
        a = [SimpleNamespace(input_name="r1", answer_type="coord")]
        _localize_feedback(r, a, "fr", enabled=True)
        assert r[0].expected == "2.5,3.5"

    def test_scope_matches_the_input_side_plus_range(self):
        """Le périmètre d'affichage suit celui de la saisie, `range` en plus."""
        from api.routes.check import _LOCALIZED_FEEDBACK_TYPES
        from core.answer.strategies._locale import NUMERIC_REPLY_TYPES
        assert _LOCALIZED_FEEDBACK_TYPES == NUMERIC_REPLY_TYPES | {"range"}

    def test_numeric_types_are_included(self):
        from api.routes.check import _LOCALIZED_FEEDBACK_TYPES
        for t in ("numeric", "numexp", "range", "units"):
            assert t in _LOCALIZED_FEEDBACK_TYPES


class TestLocalizeFeedbackSetting:
    def test_setting_exists_and_defaults_to_on(self):
        from config import settings
        assert settings.pax_localize_feedback is True

    @staticmethod
    def _fixture():
        """Un corrigé numérique et un corrigé textuel, en français."""
        from types import SimpleNamespace
        results = [
            SimpleNamespace(input_name="reply1", expected="4.76"),
            SimpleNamespace(input_name="reply2", expected="3.5 pouces"),
        ]
        answers = [
            SimpleNamespace(input_name="reply1", answer_type="numeric"),
            SimpleNamespace(input_name="reply2", answer_type="atext"),
        ]
        return results, answers

    def test_enabled_rewrites_numeric_only(self):
        from api.routes.check import _localize_feedback
        results, answers = self._fixture()
        _localize_feedback(results, answers, "fr", enabled=True)
        assert results[0].expected == "4,76"
        assert results[1].expected == "3.5 pouces"   # atext : hors périmètre

    def test_disabled_changes_nothing(self):
        """`PAX_LOCALIZE_FEEDBACK=0` doit rendre la passe totalement inerte."""
        from api.routes.check import _localize_feedback
        results, answers = self._fixture()
        _localize_feedback(results, answers, "fr", enabled=False)
        assert results[0].expected == "4.76"
        assert results[1].expected == "3.5 pouces"

    def test_dot_decimal_language_is_inert_too(self):
        from api.routes.check import _localize_feedback
        results, answers = self._fixture()
        _localize_feedback(results, answers, "en", enabled=True)
        assert results[0].expected == "4.76"

    def test_reply_is_never_touched(self):
        """On rend à l'élève ce qu'il a tapé, sans le réécrire."""
        from types import SimpleNamespace
        from api.routes.check import _localize_feedback
        r = SimpleNamespace(input_name="reply1", expected="4.76", reply="4.7")
        a = SimpleNamespace(input_name="reply1", answer_type="numeric")
        _localize_feedback([r], [a], "fr", enabled=True)
        assert r.expected == "4,76" and r.reply == "4.7"
