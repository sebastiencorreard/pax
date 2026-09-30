"""La réponse de l'élève, telle que la section `:test` l'attend.

Un exercice noté par analyse fait tourner son propre `:postdef` puis son
`:test` sur la réponse. Encore faut-il la lui donner sous la forme qu'il range
dans ses variables — et deux maillons y manquaient.
"""

import html

from core.answer.strategies.analyze import _forme_brute


class _Def:
    """Le minimum d'une `AnswerDef` pour `_forme_brute`."""

    def __init__(self, options):
        self.options = options


class TestFormeBrute:
    """Ce que le front renvoie est la forme **affichée** : math refermé pour
    KaTeX, entité HTML restée en clair. `OEFevalwimsgrph/ineqalghyper1` cherche
    le rang de la réponse dans sa propre liste (`!positionof item $m_reply1 in
    $val111`) — il ne l'y retrouvait jamais, et **aucune réponse ne pouvait
    être juste**.
    """

    @staticmethod
    def _ans():
        return _Def({
            "choices": [r"\(a\) &#59; \(b\)", r"\(c\) &#59; \(d\)"],
            "choices_raw": [r"\(a) &#59; \(b)", r"\(c) &#59; \(d)"],
        })

    def test_retrouve_la_forme_rangee(self):
        """Le rang du choix affiché désigne l'item de même rang dans la liste
        d'origine — exact par construction, sans défaire les transformations
        à l'aveugle."""
        out = _forme_brute(r"\(c\) &#59; \(d\)", self._ans())
        # Math rouvert…
        assert r"\(c)" in out
        # …et entité décodée : c'est le `;` que le navigateur soumet, et que le
        # `:postdef` ré-échappe juste après en `&#59;`. Lui rendre l'entité
        # produirait `&#59&#59;`, introuvable dans la liste.
        assert "&#59;" not in out
        assert ";" in out

    def test_une_reponse_hors_palette_passe_telle_quelle(self):
        assert _forme_brute("autre chose", self._ans()) == "autre chose"

    def test_sans_palette_brute_on_ne_touche_a_rien(self):
        ans = _Def({"choices": ["a", "b"]})
        assert _forme_brute("a", ans) == "a"

    def test_sans_reponse_declaree(self):
        assert _forme_brute("x", None) == "x"

    def test_palettes_de_tailles_differentes_sont_ignorees(self):
        """Garde-fou : sans correspondance rang à rang, on ne devine pas."""
        ans = _Def({"choices": ["a", "b", "c"], "choices_raw": ["a", "b"]})
        assert _forme_brute("a", ans) == "a"


class TestMReplyEstPose:
    """`check_analyze` ne posait que `val<N>` pour un `?analyze N`. WIMS rend
    aussi `m_reply<n>` et `reply<n>`, **bruts**, à toute réponse soumise — et
    121 `.def` du corpus les lisent dans leur `:postdef` ou leur `:test`, dont
    47 avec un `?analyze`."""

    def test_les_deux_variables_arrivent(self):
        from core.oef.def_engine import check_analyze
        from core.oef.def_parser import Assign

        condtest, _ = check_analyze(
            ev_ctx={},
            postdef_instructions=[
                Assign(name="val9", value="$m_reply1"),
                Assign(name="val8", value="$reply1"),
            ],
            test_instructions=[
                Assign(name="condtest1", value="1"),
            ],
            analyze_replies={},
            seed=1,
            replies_by_number={1: "42"},
        )
        assert condtest == {"condtest1": 1}

    def test_sans_replies_by_number_rien_ne_change(self):
        """Le paramètre est optionnel : les appels existants restent valides."""
        from core.oef.def_engine import check_analyze
        from core.oef.def_parser import Assign

        condtest, _ = check_analyze(
            ev_ctx={},
            postdef_instructions=[],
            test_instructions=[Assign(name="condtest1", value="0")],
            analyze_replies={},
            seed=1,
        )
        assert condtest == {"condtest1": 0}


class TestCasesEnTextes:
    """Une case cochée, WIMS l'envoie par son **texte** (`anstype/checkbox.input`,
    `value="$menuitem"`) ; PAX par son rang. Pour une case notée par `?analyze`,
    le `:postdef` de l'auteur compare des textes : le modèle QCM d'`uniteadn`
    jugeait fausse la réponse exacte."""

    PALETTE = ["noyau", "cytoplasme", "mitochondries"]

    def test_rangs_traduits(self):
        from core.oef.def_engine import cases_en_textes
        assert cases_en_textes("1,3", self.PALETTE) == "noyau,mitochondries"

    def test_autre_valeur_intacte(self):
        from core.oef.def_engine import cases_en_textes
        assert cases_en_textes("noyau", self.PALETTE) == "noyau"
        assert cases_en_textes("4", self.PALETTE) == "4"
        assert cases_en_textes("1", []) == "1"

    def test_un_radio_envoie_son_texte(self):
        from core.oef.def_engine import cases_en_textes
        palette = ["répondre", "géométrie", "tableaux"]
        assert cases_en_textes("1", palette) == "répondre"

    def test_une_valeur_de_la_palette_reste_elle_meme(self):
        # Palette numérique : « 2 » est un choix, non le rang 2.
        from core.oef.def_engine import cases_en_textes
        assert cases_en_textes("2", ["1", "2", "3"]) == "2"
        assert cases_en_textes("2", ["5", "2", "7"]) == "2"

    def test_palette_de_replygood(self):
        from core.oef.def_engine import palette_de_replygood
        assert palette_de_replygood("?analyze 80;a,\\(f(x,y)\\),c") == ["a", "\\(f(x,y)\\)", "c"]


class TestCondlist:
    """`var.proc` ne compte que les conditions de `condlist`, que `:test` peut
    restreindre."""

    @staticmethod
    def _test(*paires):
        from core.oef.def_parser import Assign
        return [Assign(name=n, value=v) for n, v in paires]

    def test_seules_les_conditions_retenues(self):
        from core.oef.def_engine import check_analyze

        test = self._test(("condlist", "1,3"), ("condtest1", "1"),
                          ("condtest2", "0"), ("condtest3", "0"))
        retenues: list = []
        condtest, _ = check_analyze({}, [], test, {}, seed=1, condlist_out=retenues)
        assert condtest == {"condtest1": 1, "condtest3": 0}
        assert retenues == [1, 3]

    def test_all_garde_tout(self):
        from core.oef.def_engine import check_analyze

        test = self._test(("condtest1", "1"), ("condtest2", "0"))
        retenues: list = []
        condtest, _ = check_analyze({}, [], test, {}, seed=1, condlist_out=retenues)
        assert condtest == {"condtest1": 1, "condtest2": 0}
        assert retenues == []


def test_attendu_function_sans_ses_variables():
    # `replygood` d'un `function` : `expression, variables` ; WIMS n'affiche
    # que l'expression (`anstype/function`, `!item 1`).
    from core.answer.strategies.standard import pretty_expected
    assert pretty_expected("-3*(x-8)^2+48,x", "function") == "-3*(x-8)^2+48"


def test_un_champ_hors_condlist_na_pas_de_verdict():
    """`fuseerep` : la condition de la formule de `g` n'est pas dans
    `condlist` (seule la 1 l'est). WIMS laisse la ligne du champ vide ; PAX la
    jugeait fausse. Aucun résultat n'est rendu pour ce champ."""
    from types import SimpleNamespace

    from core.answer.strategies.analyze import run_analyze
    from core.oef.def_parser import Assign, IfBlock

    test = [
        Assign(name="condlist", value="1"),
        Assign(name="condtest1", value="1"),
        IfBlock(kind="ifval", condition="$val80 = $val71",
                then_body=[Assign(name="condtest2", value="1")],
                else_body=[Assign(name="condtest2", value="0")]),
    ]
    rendu = SimpleNamespace(
        check_sections={"ctx": {}, "postdef": [], "test": test}, lang="fr")
    champ = SimpleNamespace(input_name="reply5", answer_type="radio", expected="",
                            weight=1.0, options={"analyze_var": "val80"})
    note, resultats = run_analyze(rendu, [champ], {"reply5": "3"}, seed=1)
    assert note == 1.0
    assert resultats == []


def test_insmath_integrale_en_latex():
    """`!insmath I=integrate(f,x=a,b)` : `texmath.c` (`_tex_sums`) le met en
    forme ; `oefinteg1/CalculintgralI` l'affichait en clair."""
    from core.oef.def_engine.presentation import texmath_sommes
    assert texmath_sommes("integrate(x^2+1,x=0,1)", "fr") == \
        "\\int _{0}^{1}\\left(x^{2} + 1\\right) \\,\\textrm{d}x"
    assert texmath_sommes("sum(1/n^2,n=1,N)", "fr") == "\\sum _{n=1}^{N}\\frac{1}{n^{2}}"
    assert texmath_sommes("x+1", "fr") == "x+1"


def test_signe_sorti_de_la_fraction():
    """Sans évaluation, `-pi/2` restait `(-1)·π/2` dans l'énoncé ; après un
    opérateur, il se parenthèse (`opertrigo` : `x - (-π/6)`)."""
    from core.oef.def_engine.presentation import _normalize_math_content as n
    assert n("-pi/2", "fr") == "-\\frac{\\pi}{2}"
    assert n("x - (-pi/6)", "fr") == "x - \\left(-\\frac{\\pi}{6}\\right)"
    assert n("print()", "fr") == "print()"


def test_defaut_confparm_hors_liste(tmp_path):
    """`!default confparm1=X` pour un `!formradio … list S,R` : aucun bouton
    coché, rien n'est envoyé, `confparm1` arrive vide (`oefintegrale.fr`, qui
    affichait `x ↦` en mode rigoureux). Un `!formselect` prend sa 1re option."""
    from core.oef.def_engine import _module_confparm_defaults
    (tmp_path / "def").mkdir()
    (tmp_path / "introhook.phtml").write_text(
        "!default confparm1=X\n!formradio confparm1 list S,R prompt a,b\n"
        "!default confparm2=Z\n!formselect confparm2 list 1,2\n"
        "!default confparm3=4\n!formselect confparm3 list $liste\n",
        encoding="latin-1")
    fn = getattr(_module_confparm_defaults, "__wrapped__", _module_confparm_defaults)
    assert dict(fn(str(tmp_path / "def" / "x.def"))) == {"confparm2": "1", "confparm3": "4"}


def test_dollar_final_garde_l_espace():
    """`slib_out=$slib_out$slib_W $` : chez WIMS le `$` final ne vaut rien et
    garde l'espace. Pris à la lettre, il se collait au mot suivant et
    `challenge2005b/Agedevin` affichait « L'âge de é » pour Chloé."""
    from core.oef.def_engine import DefEngine
    e = DefEngine(seed=1)
    e.ctx["a"] = "de"
    assert e._eval_value("$a $") == "de "
    assert e._eval_value("$ texte") == " texte"
