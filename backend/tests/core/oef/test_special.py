"""
`\\special{…}` — dispatch des specials OEF (`oef/special.phtml`).

Un special non géré rend une chaîne vide : c'est voulu pour ne pas laisser
fuir du balisage, mais cela *supprimait le texte de l'énoncé* pour ceux qui en
portent (`help`, `tooltip`). Ces tests couvrent les trois portés depuis
`wims/public_html/scripts/oef/special/`.
"""

import re

import pytest

from core.oef.def_engine import DefEngine, load_and_render


def engine() -> DefEngine:
    return DefEngine(seed=1)


class TestExpandlines:
    """`expandlines.phtml` : `<pre>` dont les tabulations sont des retours
    ligne."""

    def test_tabs_become_newlines_inside_pre(self):
        assert engine()._render_special("expandlines a\tb\tc") == "<pre>a\nb\nc</pre>"

    def test_plain_text_is_preserved(self):
        assert engine()._render_special("expandlines x = 1") == "<pre>x = 1</pre>"


class TestSpecialHelp:
    """`help.phtml` : lien vers l'aide du module. PAX n'a pas ces pages, mais
    le libellé fait partie de la phrase — il doit rester lisible."""

    def test_label_stays_visible(self):
        out = engine()._render_special("help fscient, format scientifique")
        assert "format scientifique" in out
        assert 'data-help="fscient"' in out

    def test_rendered_as_a_disabled_link_not_an_anchor(self):
        out = engine()._render_special("help fscient, format scientifique")
        assert "disabled_link" in out
        assert "<a " not in out

    def test_subject_without_label_renders_nothing(self):
        assert engine()._render_special("help fscient,") == ""


class TestTooltip:
    """`tooltip.phtml`, branche CSS : ancre + texte masqué."""

    def test_anchor_and_text(self):
        out = engine()._render_special("tooltip <b>survolez</b>,,[le détail]")
        assert 'class="wims_tooltip"' in out
        assert "<b>survolez</b>" in out
        assert 'class="wims_tooltiptext"' in out
        assert "le détail" in out

    def test_two_arguments_only_means_the_second_is_the_text(self):
        """`!if $text=$empty` → `!set text=!item 2 of $parms`."""
        out = engine()._render_special("tooltip ancre,[explication]")
        assert "explication" in out
        assert 'class="wims_tooltip"' in out

    def test_class_and_style_options(self):
        out = engine()._render_special(
            "tooltip ancre,[class=[maclasse] style=[color:red]],[texte]"
        )
        assert 'class="wims_tooltiptext maclasse"' in out
        assert 'style="color:red"' in out

    def test_markup_in_text_switches_span_to_div(self):
        """`!if $test_div=$text` : un texte balisé ne peut pas vivre dans un
        `span` (HTML invalide dès qu'il contient un bloc)."""
        out = engine()._render_special("tooltip ancre,,[<p>bloc</p>]")
        assert out.startswith('<div class="wims_tooltip">')
        assert "<span" not in out

    def test_duration_variant_degrades_to_css(self):
        """La variante `DURATION` s'appuie sur `wz_tooltip.js`, absent de PAX :
        on rend la structure CSS plutôt que du JavaScript mort."""
        out = engine()._render_special(
            "tooltip ancre,[CLICKCLOSE,true,DURATION,2000],[texte]"
        )
        assert 'class="wims_tooltip"' in out
        assert "onmouseover" not in out
        assert "texte" in out

    def test_html_entities_are_decoded_in_text(self):
        out = engine()._render_special("tooltip a,,[x&#44;y&#59;z]")
        assert "x,y;z" in out

    def test_missing_anchor_falls_back_to_the_text(self):
        """`!if $parm1 = $empty` : WIMS n'émet alors que le texte."""
        assert engine()._render_special("tooltip ,,juste du texte") == "juste du texte"


class TestUnhandled:
    @pytest.mark.parametrize("kind", ["glossary machin", "imagefill a,b", "drawinput x"])
    def test_still_render_nothing(self, kind):
        """Les specials adossés à une infra absente (base glossaire, widgets
        front) restent silencieux plutôt que de laisser fuir du balisage."""
        assert engine()._render_special(kind) == ""


class TestCorpus:
    def test_tooltip_reaches_the_statement(self):
        r = load_and_render("/ressources/H4/geometry/oefphotocopie.fr/def/ex01.def", seed=42)
        assert "wims_tooltip" in r.statement_html
        assert "Formats de papier disponibles" in r.statement_html

    def test_help_label_reaches_the_statement(self):
        """Avant, `\\special{help fscient, format scientifique}` rendait le vide
        au milieu d'une phrase."""
        r = load_and_render("/ressources/H4/physics/oefpression.fr/def/0704.def", seed=42)
        assert re.search(r"format scientifique", r.statement_html)
        assert "oef_specialhelp" in r.statement_html
