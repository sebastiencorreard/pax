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


class TestVariableDeBoucleDansLIndex:
    """Le **second** argument d'un `\\embed` porte lui aussi des variables de
    boucle, et seul le nom de la réponse était résolu.

    Le `.def` compilé garde la forme OEF `\\j` là où l'exécution pose `m_j` :

        !for m_j=1 to $val16
          !read oef/embed.phtml r1,\\j

    L'index restait `\\j`, aucun chiffre n'en sortait, et la branche `checkbox`
    retombait sur « pas d'index → toute la palette » : `patron1` affichait ses
    trois figures à chaque tour, soit neuf cases pour trois choix.
    """

    @staticmethod
    def _moteur(good: str) -> DefEngine:
        e = engine()
        e.ctx["replytype1"] = "checkbox"
        e.ctx["replygood1"] = good
        return e

    def test_index_de_boucle_rend_une_seule_case(self):
        e = self._moteur("1,3;alpha,beta,gamma")
        e.ctx["m_j"] = "2"
        out = e._render_embed(r"r1,\j")
        assert out.count('type="checkbox"') == 1
        assert 'value="2"' in out and "beta" in out

    def test_chaque_tour_rend_sa_case(self):
        e = self._moteur("1,3;alpha,beta,gamma")
        vus = []
        for tour in ("1", "2", "3"):
            e.ctx["m_j"] = tour
            vus.append(e._render_embed(r"r1,\j"))
        assert [v.count('type="checkbox"') for v in vus] == [1, 1, 1]
        assert ['value="%s"' % n in v for n, v in zip("123", vus)] == [True] * 3

    def test_sans_index_la_palette_entiere_sort(self):
        """Le repli de WIMS quand aucun index n'est donné."""
        e = self._moteur("1,3;alpha,beta,gamma")
        out = e._render_embed("r1")
        assert out.count('type="checkbox"') == 3

    def test_une_variable_inconnue_reste_intacte(self):
        """On ne mutile pas un second argument qu'on ne sait pas résoudre :
        sans `m_inconnue` au contexte, l'index n'existe pas et la palette
        entière sort — comme avant, plutôt qu'un index inventé."""
        e = self._moteur("1;alpha,beta")
        out = e._render_embed(r"r1,\inconnue")
        assert out.count('type="checkbox"') == 2


class TestRadioPoseParLAuteur:
    """`\\embed{reply{n},POS}` sans contenu : l'auteur place le choix lui-même.

    PAX le renvoyait dans la grille du bas dès que la palette portait du texte,
    et laissait sur place ce qui l'accompagnait. `OEFcone/patron00` fait suivre
    chaque choix de « : » et de sa figure : le « : » restait orphelin, la figure
    sans étiquette, et le « : » de l'énoncé se doublait de celui du premier
    choix escamoté.
    """

    @staticmethod
    def _moteur(good: str) -> DefEngine:
        e = engine()
        e.ctx["replytype1"] = "radio"
        e.ctx["replygood1"] = good
        return e

    def test_le_choix_se_pose_sur_place_avec_son_libelle(self):
        e = self._moteur("1;un secteur angulaire,un triangle")
        out = e._render_embed("r1,2")
        assert 'class="oef-radio-inline"' in out
        assert 'data-value="2"' in out
        assert "un triangle" in out

    def test_palette_numerique_garde_son_etiquette_vide(self):
        """`chgrhyper` : les choix *sont* les positions, la figure d'à côté
        porte déjà le numéro — un libellé « 2 » ferait doublon."""
        e = self._moteur("2;1,2,3,4")
        out = e._render_embed("r1,2")
        assert 'class="oef-radio-inline"' in out
        assert 'data-content=""' in out

    def test_un_second_argument_qui_n_est_pas_un_rang_reste_differe(self):
        """`ecrdecimal` écrit `reply \\h,\\s`, où le second argument est une
        taille : le radio doit rester dans la grille du bas."""
        e = self._moteur("1;alpha,beta")
        assert e._render_embed("r1,30") == ""
        assert e._render_embed("r1") == ""

    def test_le_libelle_ferme_son_math_en_ligne(self):
        r"""Un libellé peut porter du `\(…)` à la mode WIMS, que KaTeX ne lit
        pas tant qu'il n'est pas refermé."""
        e = self._moteur(r"1;0 \(\le \) \(x^{2}\) < 16,autre")
        out = e._render_embed("r1,1")
        assert out.count(r"\(") == out.count(r"\)")


class TestSecondArgumentAbsent:
    """`!read oef/embed.phtml reply1`, sans second argument.

    `size_str` vaut `"10"` par défaut, et les branches qui y lisent un rang
    (`checkbox`, `mark`) ne savaient pas distinguer ce défaut d'un index voulu.
    `oefarith/Critere4` a douze propositions : `10` tombant dans `1..12`, la
    garde d'intervalle ne voyait rien et une seule case s'affichait.
    """

    @staticmethod
    def _moteur(t: str, good: str) -> DefEngine:
        e = engine()
        e.ctx["replytype1"] = t
        e.ctx["replygood1"] = good
        return e

    def test_checkbox_sans_index_rend_toute_la_palette(self):
        e = self._moteur("checkbox", "2,4;" + ",".join(f"p{i}" for i in range(1, 13)))
        out = e._render_embed("reply1")
        assert out.count('type="checkbox"') == 12

    def test_checkbox_avec_index_rend_une_case(self):
        e = self._moteur("checkbox", "2,4;" + ",".join(f"p{i}" for i in range(1, 13)))
        out = e._render_embed("reply1,10")
        assert out.count('type="checkbox"') == 1
        assert 'value="10"' in out


class TestPaletteEtVariableDeBoucle:
    """Deux défauts que le détecteur d'« bonne réponse non affichée » a sortis."""

    @staticmethod
    def _radio(good: str) -> DefEngine:
        e = engine()
        e.ctx["replytype1"] = "radio"
        e.ctx["replygood1"] = good
        return e

    def test_la_branche_radio_lit_l_index_resolu(self):
        """Elle relisait `parts[1]`, non résolu, au lieu de `size_str`.
        `oeffonctgen/qcmensdef` boucle `!for m_t=2 to 4` sur `reply 1,\\t` :
        trois choix sur quatre s'évanouissaient, dont le bon."""
        e = self._radio("2;a,b,c,d")
        e.ctx["m_t"] = "3"
        out = e._render_embed(r"reply 1,\t")
        assert 'data-value="3"' in out
        assert 'data-content="c"' in out

    def test_une_virgule_dans_le_math_ne_coupe_pas_la_palette(self):
        r"""`qcmensdef` propose des intervalles — `\(\rbrack -\infty,3 \lbrack\)` —
        qu'un `split(",")` cassait en morceaux au math déséquilibré."""
        e = self._radio(r"1;\(\rbrack -\infty,3 \lbrack\),\(\mathbb{R}\)")
        assert e._inline_radio_choices("1") == [
            r"\(\rbrack -\infty,3 \lbrack\)",
            r"\(\mathbb{R}\)",
        ]

    def test_un_attendu_par_analyse_n_est_pas_ecrase(self):
        """`replygood1=?analyze 114;…` : la notation passe par l'analyse, qui a
        déjà résolu l'attendu. L'écraser par « ?analyze 114 » donnait une bonne
        réponse que rien ne peut satisfaire — et refuser d'inliner pour autant
        faisait disparaître les huit choix posés par l'auteur."""
        e = self._radio("?analyze 114;a,b,c")
        out = e._render_embed("reply1,2")
        assert 'class="oef-radio-inline"' in out
        assert 'data-value="2"' in out
