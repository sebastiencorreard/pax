"""`redox1` — cinq défauts en chaîne sous un seul énoncé.

Signalé le 2026-09-23 (seed 1690461820) : « Couple oxydant (,dioxyde de plomb
/ plomb II) », puis `, shuffle` à la place des boutons d'aide. Sous ces deux
symptômes, cinq maillons cassés, qu'aucun ne signalait :

1. `$(v[;3])` gardait la ligne vide de tête d'un `!record` (virgule parasite) ;
2. `!distribute … into a b` ne coupait les noms qu'à la virgule ;
3. `chemeq` ignorait l'électron et l'algèbre d'équations (`#`, `~`, `*`) ;
4. `!for … step 2` ne tournait pas dans une slib ;
5. `^` au milieu d'un motif sed était lu comme une ancre.

Les attendus des étapes 1 et 3 en dépendaient : ils valaient `H -> H`.
"""

import os

import pytest

from core.oef.appendinput import port_appendinput
from core.oef.def_engine import DefEngine, _bre_vers_python, load_and_render


def engine() -> DefEngine:
    return DefEngine(seed=1)


class TestColonneIndexee:
    def test_la_ligne_vide_de_tete_ne_fait_pas_de_colonne(self):
        # `!record` rend l'enregistrement précédé du `\n` qui clôt la ligne
        # `:`. `calc_columnof` élague la matrice déjà substituée.
        e = engine()
        e.ctx["v"] = "\nZn, -0.76 V, zinc II / zinc"
        assert e._subst("$(v[;3])") == "zinc II / zinc"
        assert e._subst("$(v[;1])") == "Zn"

    def test_les_autres_selecteurs_gardent_la_ligne_vide(self):
        # `[1;3]` passe par `calc_rowof`, qui n'élague pas : la ligne 1 est
        # vide chez WIMS aussi.
        e = engine()
        e.ctx["v"] = "\nZn, -0.76 V, zinc"
        assert e._subst("$(v[1;3])") == ""
        assert e._subst("$(v[2;])") == "Zn, -0.76 V, zinc"


def test_distribute_coupe_les_noms_aux_blancs():
    # `items2words` puis `cutwords` (`exec_distribute`).
    e = engine()
    e._cmd_distribute("words htmlbuttons 1 into slib_html slib_n")
    assert (e.ctx["slib_html"], e.ctx["slib_n"]) == ("htmlbuttons", "1")
    e._cmd_distribute("items a,b,c into x, y z")
    assert (e.ctx["x"], e.ctx["y"], e.ctx["z"]) == ("a", "b", "c")


class TestBre:
    def test_accent_circonflexe_au_milieu_est_litteral(self):
        assert _bre_vers_python(r".*e^-|\([^*]*\)\*.*") == r".*e\^-\|([^*]*)\*.*"

    def test_les_ancres_restent_des_ancres(self):
        assert _bre_vers_python("^abc$") == "^abc$"
        assert _bre_vers_python(r"\(^x\)") == "(^x)"
        assert _bre_vers_python("a$b") == r"a\$b"

    def test_nombre_d_electrons_de_chemeq_el(self):
        e = engine()
        e.ctx["x"] = "PbO2_(s)|1*0, 4 H^+_(aq)|4*1, 2 e^-|2*-1; Pb^2+_(aq)|1*2"
        assert e._eval_value(r"!replace .*e^-|\([^*]*\)\*.* by \1 in $x") == "2"


def test_for_step_dans_une_slib():
    # `chemeq_add` parcourt ses arguments deux à deux.
    e = DefEngine(seed=1, def_path="/ressources/H5/chemistry/redox.fr/def/redox1.def")
    e._run_script_lines(["s=", "!for i=1 to 7 step 2", "s=$s$i", "!next i"])
    assert e.ctx["s"] == "1357"


class TestBoutonsAppendToInput:
    _SCRIPT = (
        '<script type="text/javascript">\nfunction getInput(n){\n'
        "  f=window.document.forms[0];\n"
        "  for(i=0; i<f.elements.length; i=i+1){\n"
        '    if (f.elements[i].name=="reply"+n) { \n      return f.elements[i];\n    }\n  }\n'
        "  return null;\n}\nfunction appendToInput(n,msg){\n  var i=getInput(n);\n"
        "  i.value=i.value+msg+' ';\n  i.focus();\n}\n</script>"
    )
    _BOUTON = """<input type="button" value="H2O" onclick="appendToInput(1,' H2O ')">"""

    def test_le_script_de_la_slib_est_reconnu(self):
        out = port_appendinput(self._SCRIPT + self._BOUTON)
        assert "<script" not in out
        assert out == ('<button type="button" class="pax-append" data-reply="reply1" '
                       'data-text=" H2O  ">H2O</button>')

    def test_un_autre_script_laisse_tout_intact(self):
        html = self._SCRIPT.replace("i.focus();", "alert(1);") + self._BOUTON
        assert port_appendinput(html) == html


_REDOX1 = "/ressources/H5/chemistry/redox.fr/def/redox1.def"


@pytest.mark.skipif(not os.path.isfile(_REDOX1), reason="corpus absent")
def test_redox1_de_bout_en_bout():
    etape1 = load_and_render(_REDOX1, seed=1690461820, m_step=1)
    html = etape1.statement_html
    assert "(,"  not in html and ", shuffle" not in html
    assert "dioxyde de plomb / plomb II" in html
    assert html.count('class="pax-append"') == 8
    assert [a.expected for a in etape1.answers] == ["Zn_(s) -> Zn^2+_(aq) + 2 e^-"]

    etape3 = load_and_render(_REDOX1, seed=1690461820, m_step=3)
    attendus = {a.input_name: a.expected for a in etape3.answers}
    assert attendus["reply4"] == (
        "4 H^+_(aq) + O2Pb_(s) + Zn_(s) -> 2 H2O_(l) + Pb^2+_(aq) + Zn^2+_(aq)"
    )
