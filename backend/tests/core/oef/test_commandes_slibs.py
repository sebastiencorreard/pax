"""Les commandes WIMS que le portage des slibs de H1, H2, H5 et H6 a demandées.

Copier une slib dans `ressources/wims-scripts/` ne suffisait pas : cinq défauts
du moteur l'empêchaient de rendre. Chacun est corrigé d'après la source WIMS, et
éprouvé ici — en isolation, puis sur les slibs vendorisées qui les emploient.
"""
import os
import re

import pytest

from core.oef.def_engine import DefEngine

RESSOURCES = os.path.abspath(
    os.path.join(os.path.dirname(__file__), "../../../../ressources")
)
# Un `.def` quelconque du corpus : il donne au moteur un module, donc un chemin
# vers `wims-scripts/`, où vivent les slibs.
NOMSYMBOL = os.path.join(RESSOURCES, "H2/physics/oefelec.fr/def/nomsymbol.def")
avec_corpus = pytest.mark.skipif(
    not os.path.isfile(NOMSYMBOL), reason="corpus absent"
)


def moteur(def_path=None) -> DefEngine:
    return DefEngine(seed=1, def_path=def_path)


class TestSort:
    """`!sort` pose `wims_sort_order` (`calc.c:133`) et connaît `nocase`."""

    def test_l_ordre_donne_les_rangs_d_origine(self):
        e = moteur()
        assert e._eval_cmd("sort", "numeric items 30,10,20") == "10,20,30"
        assert e.ctx["wims_sort_order"] == "2,3,1"

    def test_l_ordre_suit_le_tri_inverse(self):
        e = moteur()
        assert e._eval_cmd("sort", "reverse items b,a,c") == "c,b,a"
        assert e.ctx["wims_sort_order"] == "3,1,2"

    def test_nocase(self):
        e = moteur()
        assert e._eval_cmd("sort", "nocase items b,A,c") == "A,b,c"


class TestTextDelete:
    """`delete`, `drop` et `remove` sont une seule fonction, `text_remove`."""

    def test_ote_les_caracteres_du_jeu(self):
        e = moteur()
        assert e._eval_cmd("text", "delete R in resR") == "res"
        assert e._eval_cmd("text", "remove ab in abcab") == "c"
        assert e._eval_cmd("text", "drop x in xyx") == "y"


class TestDefault:
    """`exec_default` : si la variable est vide, un `!set` complet."""

    def test_une_commande_est_evaluee(self):
        e = moteur()
        e._eval_cmd("default", "n=!randint 1,1000")
        assert e.ctx["n"].isdigit()

    def test_rien_ne_se_passe_si_la_variable_a_une_valeur(self):
        e = moteur()
        e.ctx["n"] = "7"
        etat = e.rng.getstate()
        e._eval_cmd("default", "n=!randint 1,1000")
        assert e.ctx["n"] == "7"
        # Évaluée seulement quand elle servira : aucun tirage consommé.
        assert e.rng.getstate() == etat


class TestSlashsubst:
    """`\\nom` devient `$m_nom` quand `m_nom` existe (`lines.c:806`)."""

    def test_nom_connu_nom_inconnu_et_indice(self):
        e = moteur()
        e.ctx["m_times"] = "×"
        texte = r"a \times b \inconnu c \times[1] d"
        assert e._eval_cmd("slashsubst", texte) == r"a $m_times b \inconnu c $(m_times[1]) d"


@avec_corpus
class TestLectureDepuisUneSlib:
    """Un `!read` fait par une slib se résout sous `wims-scripts/`."""

    def test_une_slib_charge_ses_donnees(self):
        e = moteur(NOMSYMBOL)
        e._run_slib("slib/circuits/draw", "1/comph,80,black,motor")
        assert "comp_motor" in e.ctx
        assert "ellipse" in e.ctx["slib_out"]

    def test_un_def_ne_lit_toujours_pas_hors_des_chemins_connus(self):
        # La résolution est bornée aux lectures des slibs : un `.def` qui lit
        # un fichier inconnu reste ignoré (TODO I.3 h).
        e = moteur(NOMSYMBOL)
        e._cmd_readproc("data/circuits/compdata")
        assert "comp_motor" not in e.ctx


@avec_corpus
class TestSlibsPortees:
    def test_columnsort_trie_une_table_sur_une_colonne(self):
        e = moteur(NOMSYMBOL)
        e._run_slib("slib/data/columnsort", "1,numeric, 3,c\n1,a\n2,b")
        lignes = [l.replace(" ", "") for l in e.ctx["slib_out"].split("\n")]
        assert lignes == ["1,a", "2,b", "3,c"]

    def test_balloon_tire_son_identifiant(self):
        e = moteur(NOMSYMBOL)
        e._run_slib("slib/text/balloon", "[Bonjour],yellow,250,100,triangle")
        assert "!randint" not in e.ctx["slib_out"]
        assert re.search(r"#bubble_\d+", e.ctx["slib_out"])


class TestValuesEtMakelist:
    """`_values` et `cutfor` : bornes et pas réels, variable valant un nombre."""

    def test_values_evalue_la_variable_comme_un_nombre(self):
        # En texte, `-1*x^2` en `x=-2` devenait `-1*-2**2` = 4.
        e = moteur()
        assert e._eval_cmd("values", "-1*x^2 + 2*x for x=-2 to 1") == "-8,-3,0,1"

    def test_step_reel(self):
        e = moteur()
        assert e._eval_cmd("values", "x for x=0 to 1 step 0.25") == "0,0.25,0.5,0.75,1"

    def test_syntaxe_from(self):
        e = moteur()
        assert e._eval_cmd("makelist", "a x for x from 1 to 3") == "a 1,a 2,a 3"

    def test_une_valeur_latex_ne_fait_plus_planter(self):
        # Passée en chaîne de remplacement à `re.sub`, `\infty` levait
        # `re.PatternError: bad escape \i`.
        e = moteur()
        assert isinstance(e._eval_cmd("makelist", r"x for x in \infty,1"), str)


class TestListesEtRangees:
    def test_sort_sur_une_liste_vide(self):
        e = moteur()
        assert e._eval_cmd("sort", "numeric items ") == ""

    def test_lines2rows_et_rows2lines_passent_par_le_point_virgule(self):
        # `liblines.c` : `;` ↔ `\n`, jamais la tabulation.
        e = moteur()
        assert e._eval_cmd("lines2rows", "1,a\n2,b") == "1,a;2,b"
        assert e._eval_cmd("rows2lines", "1,a;2,b") == "1,a\n2,b"


class TestIntegraleDefinie:
    """`integrate(f, x, a, b)`, que `slib/function/integrate` demande à Maxima."""

    def test_valeur_exacte_d_une_integrale_definie(self):
        from core.oef.def_engine.cas import _call_maxima

        # ∫_{-2}^{1} (-x² + 2x + 9) dx = -3 - 3 + 27 = 21
        assert _call_maxima("integrate(-1*x^2 + 2*x +9,x,-2,1);") == "21"

    def test_l_integrale_sans_bornes_ne_change_pas(self):
        from core.oef.def_engine.cas import _call_maxima

        assert "integrate" not in _call_maxima("integrate(6*x^2,x)")
