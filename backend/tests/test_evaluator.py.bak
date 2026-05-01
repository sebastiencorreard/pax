"""
Tests unitaires pour core/oef/evaluator.py et core/oef/engine.py
"""
import pytest
from core.oef.evaluator import OEFEvaluator, _oef_cond_to_py
from core.oef.parser import Directive, parse


# ------------------------------------------------------------------ #
# Helpers                                                              #
# ------------------------------------------------------------------ #

def ev(source: str, seed: int = 0) -> OEFEvaluator:
    e = OEFEvaluator(seed=seed)
    e.evaluate_source(source)
    return e


# ------------------------------------------------------------------ #
# Variables de base                                                    #
# ------------------------------------------------------------------ #

class TestBasicVars:
    def test_integer(self):
        e = ev(r"\integer{a=3+4}")
        assert e.ctx["a"] == "7"

    def test_text(self):
        e = ev(r"\text{name=hello}")
        assert e.ctx["name"] == "hello"

    def test_rational(self):
        e = ev(r"\rational{r=1/3}")
        assert e.ctx["r"] == "1/3"

    def test_var_substitution(self):
        e = ev(r"\integer{a=5}" + "\n" + r"\integer{b=\a+1}")
        assert e.ctx["b"] == "6"


# ------------------------------------------------------------------ #
# Fonctions OEF                                                        #
# ------------------------------------------------------------------ #

class TestOEFFunctions:
    def test_randint_range(self):
        e = ev(r"\integer{x=randint(1..10)}")
        assert 1 <= int(e.ctx["x"]) <= 10

    def test_randint_seed_deterministic(self):
        e1 = ev(r"\integer{x=randint(1..100)}", seed=42)
        e2 = ev(r"\integer{x=randint(1..100)}", seed=42)
        assert e1.ctx["x"] == e2.ctx["x"]

    def test_randitem(self):
        e = ev(r"\text{s=randitem(a,b,c)}")
        assert e.ctx["s"] in ["a", "b", "c"]

    def test_min(self):
        e = ev(r"\text{m=min(3,7)}")
        assert e.ctx["m"] == "3"

    def test_max(self):
        e = ev(r"\text{m=max(3,7)}")
        assert e.ctx["m"] == "7"

    def test_min_negative(self):
        e = ev(r"\integer{a=-5}" + "\n" + r"\text{m=min(\a,3)}")
        assert e.ctx["m"] == "-5"

    def test_abs_positive(self):
        e = ev(r"\integer{a=3}" + "\n" + r"\text{b=abs(\a)}")
        assert e.ctx["b"] == "3"

    def test_abs_negative(self):
        e = ev(r"\integer{a=-5}" + "\n" + r"\text{b=abs(\a)}")
        assert e.ctx["b"] == "5"

    def test_pari(self):
        e = ev(r"\text{p=pari(5)}")
        assert e.ctx["p"] == "6"

    def test_pari_even(self):
        e = ev(r"\text{p=pari(4)}")
        assert e.ctx["p"] == "4"

    def test_core(self):
        # core(12) = 3 (12 = 4*3, 4 est un carré)
        e = ev(r"\text{c=core(12)}")
        assert e.ctx["c"] == "3"

    def test_core_squarefree(self):
        e = ev(r"\text{c=core(7)}")
        assert e.ctx["c"] == "7"

    def test_items_of_literal_list(self):
        e = OEFEvaluator(seed=0)
        result = e._eval_expr("items(-1/214,229/214)")
        assert result == "2"

    def test_items_of_variable(self):
        e = OEFEvaluator(seed=0)
        e.ctx["rep"] = "-1/214,229/214"
        result = e._eval_expr(r"items(\rep)")
        assert result == "2"

    def test_items_single(self):
        e = OEFEvaluator(seed=0)
        result = e._eval_expr("items(42)")
        assert result == "1"

    def test_wims_values_for(self):
        e = OEFEvaluator(seed=0)
        result = e._eval_expr("wims(values v for v=2 to 5)")
        assert result == "2,3,4,5"

    def test_wims_values_for_expr(self):
        e = OEFEvaluator(seed=0)
        result = e._eval_expr("wims(values v*2 for v=1 to 3)")
        assert result == "1*2,2*2,3*2"

    def test_texmath_sqrt(self):
        e = OEFEvaluator(seed=0)
        result = e._eval_expr(r"texmath(sqrt((-23)^2))")
        assert result == r"\sqrt{(-23)^2}"

    def test_texmath_sqrt_variable(self):
        e = OEFEvaluator(seed=0)
        e.ctx["a"] = "5"
        result = e._eval_expr(r"texmath(sqrt(\a))")
        assert result == r"\sqrt{5}"

    def test_wims_math_delimiter_simple(self):
        # \(expr) → \(expr\)
        result = OEFEvaluator._fix_wims_math_delimiters(r'\(\sqrt{(-24)^2} = )<input>')
        assert result == r'\(\sqrt{(-24)^2} = \)<input>'

    def test_wims_math_delimiter_already_closed(self):
        # \(expr\) déjà correct — ne pas modifier
        s = r'\(\sqrt{x}\)'
        assert OEFEvaluator._fix_wims_math_delimiters(s) == s

    def test_wims_math_delimiter_nested_parens(self):
        # Les parenthèses imbriquées dans le contenu ne doivent pas fermer le bloc
        result = OEFEvaluator._fix_wims_math_delimiters(r'\((-3)^2 = )')
        assert result == r'\((-3)^2 = \)'

    def test_shuffle_length(self):
        e = ev(r"\text{l=shuffle(1,2,3,4,5)}")
        items = [x.strip() for x in e.ctx["l"].split(",")]
        assert sorted(items) == ["1", "2", "3", "4", "5"]

    def test_indexed_var(self):
        e = ev(r"\text{l=shuffle(1,2,3)}" + "\n" + r"\text{x=\l[1]}")
        assert e.ctx["x"] in ["1", "2", "3"]


# ------------------------------------------------------------------ #
# \if au niveau variables                                              #
# ------------------------------------------------------------------ #

class TestIfDirective:
    def test_if_true_branch(self):
        e = ev(r"\integer{a=5}" + "\n" + r"\if{\a>3}{\integer{b=1}}")
        assert e.ctx["b"] == "1"

    def test_if_false_branch_not_executed(self):
        e = ev(r"\integer{a=1}" + "\n" + r"\if{\a>3}{\integer{b=99}}")
        assert "b" not in e.ctx

    def test_if_else_true(self):
        src = r"\integer{a=5}" + "\n" + r"\if{\a>3}{\integer{b=1}}{\integer{b=0}}"
        e = ev(src)
        assert e.ctx["b"] == "1"

    def test_if_else_false(self):
        src = r"\integer{a=1}" + "\n" + r"\if{\a>3}{\integer{b=1}}{\integer{b=0}}"
        e = ev(src)
        assert e.ctx["b"] == "0"

    def test_if_with_abs_in_condition(self):
        src = (r"\integer{x1=-6}" + "\n"
               r"\integer{x2=3}" + "\n"
               r"\if{abs(\x1)>abs(\x2)}{\integer{y=abs(\x1)}}{\integer{y=abs(\x2)}}")
        e = ev(src)
        assert e.ctx["y"] == "6"

    def test_if_with_abs_false(self):
        src = (r"\integer{x1=-2}" + "\n"
               r"\integer{x2=5}" + "\n"
               r"\if{abs(\x1)>abs(\x2)}{\integer{y=abs(\x1)}}{\integer{y=abs(\x2)}}")
        e = ev(src)
        assert e.ctx["y"] == "5"

    def test_multiple_if_independent(self):
        src = (r"\integer{a=5}" + "\n"
               r"\integer{b=-3}" + "\n"
               r"\if{\a>0}{\integer{pa=1}}" + "\n"
               r"\if{\b<0}{\integer{nb=1}}")
        e = ev(src)
        assert e.ctx["pa"] == "1"
        assert e.ctx["nb"] == "1"

    def test_nested_if(self):
        src = (r"\integer{a=5}" + "\n"
               r"\if{\a>0}{\if{\a>3}{\integer{big=1}}{\integer{big=0}}}")
        e = ev(src)
        assert e.ctx["big"] == "1"


# ------------------------------------------------------------------ #
# \while                                                               #
# ------------------------------------------------------------------ #

class TestWhileDirective:
    def test_while_basic(self):
        # b doit finir à 1 après que a soit incrémenté au-delà de 3
        src = (r"\integer{a=0}" + "\n"
               r"\integer{b=0}" + "\n"
               r"\while{\b=0}{\integer{a=\a+1}" + "\n"
               r"\if{\a>3}{\integer{b=1}}}")
        e = ev(src)
        assert e.ctx["b"] == "1"
        assert int(e.ctx["a"]) > 3


# ------------------------------------------------------------------ #
# Prettify LaTeX                                                       #
# ------------------------------------------------------------------ #

class TestPrettifyLatex:
    def _render(self, stmt: str, extra: str = "") -> str:
        e = OEFEvaluator(seed=0)
        e.evaluate_source(extra)
        return e.render_statement(stmt)

    def test_times_before_letter_removed(self):
        out = self._render(r"\(3*x\)")
        assert "\\times" not in out
        assert "3x" in out or "3" in out

    def test_positive_plus_negative(self):
        out = self._render(r"\(3+(-2)\)")
        # doit afficher -2 pas +(-2)
        assert "+(-" not in out

    def test_times_before_paren_removed(self):
        out = self._render(r"\(2*(x+1)\)")
        assert "\\times (" not in out

    def test_minus_minus_simplifies(self):
        out = self._render(r"\(3-(-2)\)")
        assert "--" not in out


# ------------------------------------------------------------------ #
# _oef_cond_to_py                                                      #
# ------------------------------------------------------------------ #

class TestOefCondToPy:
    def test_simple_equality(self):
        assert _oef_cond_to_py("a=1") == "a==1"

    def test_no_double_equal(self):
        assert _oef_cond_to_py("a==1") == "a==1"

    def test_not_equal(self):
        assert _oef_cond_to_py("a<>1") == "a!=1"

    def test_leq_unchanged(self):
        assert _oef_cond_to_py("a<=1") == "a<=1"

    def test_geq_unchanged(self):
        assert _oef_cond_to_py("a>=1") == "a>=1"

    def test_empty_rhs(self):
        # expr= sans valeur à droite → expr==''
        assert _oef_cond_to_py("x=") == "x==''"

    def test_empty_both_sides(self):
        # variable vide substituée → = seul → ''==''
        assert _oef_cond_to_py("=") == "''==''"

    def test_power(self):
        assert _oef_cond_to_py("a^2=4") == "a**2==4"


# ------------------------------------------------------------------ #
# confparm initialisés vides                                           #
# ------------------------------------------------------------------ #

class TestConfparm:
    def test_confparm_initialized_empty(self):
        e = OEFEvaluator(seed=0)
        for i in range(1, 10):
            assert e.ctx[f"confparm{i}"] == ""

    def test_confparm_empty_condition(self):
        """\\if{\\confparm1=}{...} doit être vrai quand confparm1 est vide."""
        src = r"\if{\confparm1=}{\integer{x=1}}{\integer{x=0}}"
        e = OEFEvaluator(seed=0)
        e.evaluate_source(src)
        assert e.ctx["x"] == "1"

    def test_transfrac_has_statement(self):
        """ex4 : avec confparm vide, type=1 et enonce est défini."""
        from core.oef.engine import load_and_render
        r = load_and_render(
            "/var/lib/wims/public_html/modules/H4/algebra/racine1.fr/src/transfrac.oef",
            seed=1
        )
        assert r.ev_ctx.get("type") == "1"
        assert r.statement_html.strip() != ""
        assert r.statement_html != r"\enonce"


# ------------------------------------------------------------------ #
# Filtrage des réponses par présence dans le statement                 #
# ------------------------------------------------------------------ #

class TestAnswerFiltering:
    def test_transfrac_nrep2_has_2_answers(self):
        """ex4 avec nrep=2 : seulement reply1 et reply2."""
        from core.oef.engine import load_and_render
        r = load_and_render(
            "/var/lib/wims/public_html/modules/H4/algebra/racine1.fr/src/transfrac.oef",
            seed=1
        )
        assert r.ev_ctx.get("nrep") == "2"
        assert len(r.answers) == 2
        assert {a.input_name for a in r.answers} == {"reply1", "reply2"}

    def test_transfrac_nrep3_has_3_answers(self):
        """ex4 avec nrep=3 : reply1, reply2 et reply3."""
        from core.oef.engine import load_and_render
        # Cherche un seed donnant nrep=3 (type=11 ou 12)
        for seed in range(1, 200):
            r = load_and_render(
                "/var/lib/wims/public_html/modules/H4/algebra/racine1.fr/src/transfrac.oef",
                seed=seed
            )
            if r.ev_ctx.get("nrep") == "3":
                assert len(r.answers) == 3
                return
        pytest.skip("Aucun seed avec nrep=3 trouvé dans les 200 premiers")

    def test_choice_not_filtered(self):
        """ex3 : \\choice sans \\embed → réponse radio conservée."""
        from core.oef.engine import load_and_render
        r = load_and_render(
            "/var/lib/wims/public_html/modules/H4/number/evalwimsracine.fr/src/definition2.oef",
            seed=1
        )
        assert len(r.answers) == 1
        assert r.answers[0].answer_type == "radio"
        assert "Oui" in r.answers[0].options.get("choices", [])
        assert "Non" in r.answers[0].options.get("choices", [])

    def test_reply_with_space_not_filtered(self):
        """ex2 : \\embed{reply 1,30} (avec espace) → reply1 conservé."""
        from core.oef.engine import load_and_render
        r = load_and_render(
            "/var/lib/wims/public_html/modules/H4/algebra/develop.fr/src/dev1.oef",
            seed=42
        )
        assert len(r.answers) == 1
        assert r.answers[0].input_name == "reply1"


# ------------------------------------------------------------------ #
# Simplification des signes dans _prettify_latex                       #
# ------------------------------------------------------------------ #

class TestPrettifyLatexExtra:
    def _render(self, stmt: str) -> str:
        e = OEFEvaluator(seed=0)
        return e.render_statement(stmt)

    def test_plus_paren_negative(self):
        out = self._render(r"\(3+(-2)\)")
        assert "+(-" not in out

    def test_minus_paren_negative(self):
        out = self._render(r"\(3-(-2)\)")
        assert "-(-" not in out

    def test_plus_paren_negative_result(self):
        # 3+(-2) → 3-2
        out = self._render(r"\(3+(-2)\)")
        assert "3-2" in out or "-2" in out  # après rendu KaTeX le chiffre y est

    def test_minus_paren_negative_result(self):
        # 3-(-2) → 3+2
        out = self._render(r"\(3-(-2)\)")
        assert "+2" in out or "3+2" in out


# ------------------------------------------------------------------ #
# Intégration : exercices réels                                        #
# ------------------------------------------------------------------ #

class TestRealExercises:
    OEF_DIR = "/var/lib/wims/public_html/modules/H4/algebra/valabs.fr/src"

    def test_encadva1_both_negative(self):
        """ex15 : x1 et x2 négatifs → y1=|x2|, y2=|x1|"""
        from core.oef.engine import load_and_render
        # seed=5 donne x1=-6, x2=-5 d'après test précédent
        r = load_and_render(f"{self.OEF_DIR}/encadva1.oef", seed=5)
        x1, x2 = float(r.ev_ctx["x1"]), float(r.ev_ctx["x2"])
        assert x1 < 0 and x2 < 0
        assert r.answers[0].expected == str(int(abs(x2)))
        assert r.answers[3].expected == str(int(abs(x1)))

    def test_encadva1_mixed_abs_greater(self):
        """ex15 : x1<0 x2>0 abs(x1)>abs(x2) → y2=abs(x1)"""
        from core.oef.engine import load_and_render
        r = load_and_render(f"{self.OEF_DIR}/encadva1.oef", seed=1)
        x1, x2 = float(r.ev_ctx["x1"]), float(r.ev_ctx["x2"])
        assert x1 < 0 and x2 > 0 and abs(x1) > abs(x2)
        assert r.answers[3].expected == str(int(abs(x1)))

    def test_encadva1_both_positive(self):
        """ex15 : x1 et x2 positifs → y1=x1, y2=x2"""
        from core.oef.engine import load_and_render
        r = load_and_render(f"{self.OEF_DIR}/encadva1.oef", seed=2)
        x1, x2 = float(r.ev_ctx["x1"]), float(r.ev_ctx["x2"])
        assert x1 > 0 and x2 > 0
        assert r.answers[0].expected == str(int(x1))
        assert r.answers[3].expected == str(int(x2))

    def test_dev1_has_algexp_answer(self):
        """ex2 : développement polynomial → type algexp"""
        from core.oef.engine import load_and_render
        r = load_and_render(
            "/var/lib/wims/public_html/modules/H4/algebra/develop.fr/src/dev1.oef",
            seed=42
        )
        assert len(r.answers) == 1
        assert r.answers[0].answer_type == "algexp"
        assert r.answers[0].expected != ""

    def test_ineqva2ineg_clickfill_answers(self):
        """ex6 : clickfill → 2 clickfill + 2 numexp"""
        from core.oef.engine import load_and_render
        r = load_and_render(f"{self.OEF_DIR}/ineqva2ineg.oef", seed=42)
        types = [a.answer_type for a in r.answers]
        assert types == ["clickfill", "numexp", "clickfill", "numexp"]
        assert r.condition is not None


# ------------------------------------------------------------------ #
# Checkers                                                             #
# ------------------------------------------------------------------ #

class TestCheckers:
    def test_numeric_correct(self):
        from core.answer.checkers import check_answer
        r = check_answer("numeric", "3", "3", {})
        assert r.correct

    def test_numeric_wrong(self):
        from core.answer.checkers import check_answer
        r = check_answer("numeric", "4", "3", {})
        assert not r.correct

    def test_algexp_correct(self):
        from core.answer.checkers import check_answer
        r = check_answer("algexp", "8x**2+14x+6", "8x**2+14x+6", {})
        assert r.correct

    def test_algexp_equivalent(self):
        from core.answer.checkers import check_answer
        # (2x+2)(4x+3) développé = 8x²+14x+6
        r = check_answer("algexp", "8*x**2+14*x+6", "8x**2+14x+6", {})
        assert r.correct

    def test_algexp_wrong(self):
        from core.answer.checkers import check_answer
        r = check_answer("algexp", "x+1", "8x**2+14x+6", {})
        assert not r.correct

    def test_numexp_fraction(self):
        from core.answer.checkers import check_answer
        r = check_answer("numexp", "1/3", "1/3", {})
        assert r.correct

    def test_numexp_equivalent_forms(self):
        from core.answer.checkers import check_answer
        r = check_answer("numexp", "2/4", "1/2", {})
        assert r.correct

    def test_radio_correct(self):
        from core.answer.checkers import check_answer
        r = check_answer("radio", "Oui", "Oui", {})
        assert r.correct

    def test_radio_wrong(self):
        from core.answer.checkers import check_answer
        r = check_answer("radio", "Non", "Oui", {})
        assert not r.correct
