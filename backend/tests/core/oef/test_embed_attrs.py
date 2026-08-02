"""Attributs HTML portés par le paramètre de taille d'un `\\embed`.

`anstype/inputcss.inc` découpe ce paramètre en lignes : la première est la
taille, les suivantes sont injectées verbatim dans le `<input>`
(`\\embed{reply 1,30 autofocus}` compile en `r1,30<TAB>autofocus`). Le corpus
n'utilise que `autofocus` (355) et `autocomplete="off"` (17), mais la liste
blanche protège d'un `on…` qui atteindrait le DOM.
"""

from core.oef.def_engine import DefEngine, _parse_input_attributes
from core.oef.engine import _segment_statement


def engine() -> DefEngine:
    return DefEngine(seed=1)


class TestParseInputAttributes:
    def test_bare_flag(self):
        assert _parse_input_attributes("autofocus") == {"autofocus": True}

    def test_quoted_value(self):
        assert _parse_input_attributes('   autocomplete="off" ') == {
            "autocomplete": "off"
        }

    def test_several_lines(self):
        assert _parse_input_attributes('autofocus\nmaxlength="5"') == {
            "autofocus": True,
            "maxlength": "5",
        }

    def test_unknown_names_are_dropped(self):
        # La queue d'un embed jsxgraph passe par un autre chemin, mais rien ne
        # garantit qu'aucune ne parvienne ici — et `onclick` doit sauter.
        assert _parse_input_attributes('onclick="x()" brd [responsive]') == {}

    def test_empty_tail(self):
        assert _parse_input_attributes("") == {}


class TestEmbedRendering:
    def test_size_line_is_kept_separate_from_attributes(self):
        html = engine()._render_embed("reply1,30\tautofocus")
        assert 'data-size="30"' in html
        assert "autofocus" in html

    def test_no_attributes_no_data_attrs(self):
        assert engine()._render_embed("reply1,30") == (
            '<span class="oef-input" name="reply1" data-size="30"></span>'
        )


class TestSegmentation:
    def test_attrs_reach_the_input_segment(self):
        html = (
            'a <span class="oef-input" name="r1" data-size="12" '
            'data-attrs="{&quot;autofocus&quot;: true}"></span> b'
        )
        seg = [s for s in _segment_statement(html) if s["type"] == "input"][0]
        assert seg == {
            "type": "input", "name": "reply1", "size": 12,
            "is_sup": False, "attrs": {"autofocus": True},
        }

    def test_attrs_reach_the_native_input_inside_a_table(self):
        # Dans une <table> le widget n'est pas segmenté : il est réécrit en
        # <input> natif, les attributs doivent l'accompagner.
        html = (
            '<table><tr><td><span class="oef-input" name="r1" data-size="12" '
            'data-attrs="{&quot;autofocus&quot;: true}"></span></td></tr></table>'
        )
        content = _segment_statement(html)[0]["content"]
        assert "autofocus" in content
        # `autocomplete` est déjà posé sans condition, comme sur les champs Vue.
        assert content.count("autocomplete") == 1
