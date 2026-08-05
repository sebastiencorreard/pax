import os
import sys
import pytest

sys.path.insert(
    0,
    os.path.dirname(
        os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
    ),
)
from core.answer.checkers import (
    check_answer,
    check_clickfill,
    check_correspond,
    check_default,
    check_fset,
    check_jsxgraph,
    _polexpand_diagnostic,
)


def test_polexpand_diagnostic_shows_reduced_coefficients():
    """Le diagnostic « non réduite » affiche le coefficient réduit (-4),
    pas la forme brute non évaluée (-1*4). Régression distribuer3."""
    msg = _polexpand_diagnostic("-1*4+2+3a")
    assert "-4 et 2" in msg
    assert "-1*4" not in msg


def test_polexpand_diagnostic_drops_explicit_times():
    """Les monômes s'écrivent sans `*` : « 7a et -9a », pas « 7*a et -9*a »."""
    msg = _polexpand_diagnostic("7a-9a+2")
    assert "7a et -9a" in msg
    assert "*" not in msg


class TestCheckJsxgraph:
    def test_single_coordinate_match(self):
        # quizz 0420: reply is "<x>;", expected the target abscissa.
        assert check_jsxgraph("7;", "7").correct
        assert check_jsxgraph("7", "7").correct

    def test_within_tolerance(self):
        # Default WIMS precision 10 → tolerance 0.1.
        assert check_jsxgraph("7.05;", "7").correct
        assert not check_jsxgraph("7.5;", "7").correct

    def test_wrong_and_empty(self):
        assert not check_jsxgraph("6;", "7").correct
        assert not check_jsxgraph("", "7").correct

    def test_2d_point(self):
        assert check_jsxgraph("3,5;", "3,5").correct
        assert not check_jsxgraph("3,4;", "3,5").correct

    def test_partial_score(self):
        r = check_jsxgraph("3,9;", "3,5")
        assert not r.correct and r.score == 0.5

    def test_custom_precision(self):
        # precision=2 → tolerance 0.5, so 7.4 passes.
        assert check_jsxgraph("7.4;", "7", {"option": "precision=2"}).correct

    def test_dispatch_routes_to_jsxgraph(self):
        r = check_answer("jsxgraph", "7;", "7", {"option": "noanalyzeprint"})
        assert r.correct and r.method == "jsxgraph"


class TestCheckClickfill:
    def test_ordered_sequence_match(self):
        # repgraphint: ]−2;20[ composed across slots, comma-joined.
        seq = "&#93;,\\(-2\\),&#59;,\\(20\\),&#91;"
        assert check_clickfill(seq, seq).correct

    def test_order_matters(self):
        assert not check_clickfill("a,b,c", "a,c,b").correct

    def test_ignores_empty_and_whitespace(self):
        assert check_clickfill(" a , b ,, c ", "a,b,c").correct

    def test_wrong_sequence(self):
        assert not check_clickfill("a,b", "a,b,c").correct

    def test_single_slot_still_works(self):
        assert check_clickfill("x<-3", "x<-3").correct
        assert not check_clickfill("x>-3", "x<-3").correct


# Bug fix : type "fset" tombait dans le case "text" (comparaison de chaînes),
# donc -4 ne matchait pas -8/2.


def test_fset_dispatcher_routes_to_fset():
    """fset doit être dispatché vers check_fset, pas vers check_text."""
    result = check_answer("fset", "-4", "-8/2")
    assert result.method == "fset"
    assert result.correct is True
    assert result.score == 1.0


def test_fset_single_value_equivalent_forms():
    """Un seul élément exprimé sous différentes formes équivalentes."""
    assert check_fset("-4", "-8/2").correct
    assert check_fset("-4.0", "-8/2").correct
    assert check_fset("-4", "-4").correct
    assert check_fset("0.5", "1/2").correct


def test_fset_multiple_values_order_independent():
    """L'ordre des éléments n'a pas d'importance."""
    assert check_fset("-6/5,-9/8", "-9/8,-6/5").correct
    assert check_fset("-9/8,-4", "-8/2,-9/8").correct


def test_fset_mixed_decimal_and_fraction():
    """Forme décimale et fractionnaire mélangées des deux côtés."""
    assert check_fset("-1.125,-4", "-9/8,-8/2").correct


def test_fset_separator_semicolon():
    """Séparateur ; accepté en plus de ,."""
    assert check_fset("-4;-9/8", "-8/2;-9/8").correct


def test_fset_wrong_value():
    """Valeur incorrecte → faux."""
    r = check_fset("-4", "-3/2")
    assert r.correct is False
    assert r.score == 0.0


def test_fset_cardinality_mismatch():
    """Pas le bon nombre d'éléments → faux, score 0."""
    r = check_fset("1", "1,2")
    assert r.correct is False
    assert r.score == 0.0


def test_fset_partial_credit():
    """Un élément correct sur deux → score = 0.5, mais correct=False."""
    r = check_fset("-4,99", "-8/2,-9/8")
    assert r.correct is False
    assert r.score == pytest.approx(0.5)


def test_fset_empty_reply_against_non_empty_expected():
    """Réponse vide contre attendue non vide → faux."""
    r = check_fset("", "-8/2,-9/8")
    assert r.correct is False
    assert r.score == 0.0


def test_fset_duplicate_in_reply_does_not_double_count():
    """Une même valeur dupliquée ne doit pas matcher deux éléments distincts."""
    r = check_fset("-4,-4", "-8/2,-9/8")
    assert r.correct is False
    # Un -4 matche -8/2, l'autre ne matche pas -9/8
    assert r.score == pytest.approx(0.5)


def test_fset_falls_back_to_symbolic():
    """Quand le parseur numérique échoue, sympy doit prendre le relais."""
    # 2*x equivaut à x+x (forme symbolique, pas numérique)
    assert check_fset("2*x", "x+x").correct


# Bug fix : type "default" tombait dans le case "text", donc une réponse
# algébriquement équivalente mais formatée différemment était rejetée.


def test_default_dispatcher_uses_algexp():
    r = check_answer("default", "-x^2+8x+20", "-x**2 + 8*x + 20")
    assert r.correct is True


def test_default_implicit_multiplication():
    assert check_default("-n^2-5n-6", "-n**2 - 5*n - 6").correct


def test_default_unicode_superscripts():
    assert check_default("-x²+8x+20", "-x**2 + 8*x + 20").correct


def test_default_falls_back_to_text_for_non_math():
    """Quand l'expected n'est pas mathématique, comparaison texte."""
    assert check_default("Paris", "Paris").correct
    assert check_default("paris", "Paris").correct  # case-insensitive text


def test_default_wrong_answer():
    r = check_default("x^2 + 1", "-x**2 + 8*x + 20")
    assert r.correct is False
    assert r.score == 0.0


# correspond — bijection between two columns
def test_correspond_dispatcher():
    options = {"partial": False}
    r = check_answer("correspond", "a,b,c,d", "a,b,c,d", options)
    assert r.correct
    assert r.score == 1.0
    assert r.method == "correspond"


def test_correspond_all_correct():
    r = check_correspond("a,b,c", "a,b,c")
    assert r.correct
    assert r.score == 1.0


def test_correspond_wrong_no_partial():
    # 2 out of 4 correct, partial disabled → 0
    r = check_correspond("a,X,c,Y", "a,b,c,d", partial=False)
    assert not r.correct
    assert r.score == 0.0


def test_correspond_wrong_with_partial():
    r = check_correspond("a,X,c,Y", "a,b,c,d", partial=True)
    assert not r.correct
    assert r.score == 0.5
    assert r.method == "correspond_partial"


def test_correspond_length_mismatch():
    r = check_correspond("a,b", "a,b,c,d", partial=True)
    assert not r.correct
    assert r.score == 0.0


def test_correspond_whitespace_normalised():
    # Spaces around items shouldn't matter
    r = check_correspond("  a  ,  b  ", "a,b")
    assert r.correct


def test_correspond_options_partial_true():
    options = {"partial": True}
    r = check_answer("correspond", "a,X,c,Y", "a,b,c,d", options)
    assert r.score == 0.5


# bad_variable — case-only mismatch warns (retry), genuinely wrong
# variable still rejects as a wrong answer.
def test_case_mismatch_warns():
    """Z+15 expected, user typed z+15 (lower-case) → soft warning."""
    r = check_answer("litexp", "z+15", "Z+15", {})
    assert not r.correct
    assert r.method == "bad_variable"
    assert r.status == "invalid_format"
    assert "réécrire" in (r.detail or "")


def test_case_mismatch_warns_with_multi_good():
    """Case warning still applies when expected lists alternatives."""
    r = check_answer("litexp", "z+15", "Z+15,15+Z", {})
    assert r.status == "invalid_format"
    assert r.method == "bad_variable"


def test_wrong_variable_letter_is_normal_wrong_answer():
    """X+15 against Z+15: a different letter, not a casing slip → wrong answer."""
    r = check_answer("algexp", "X+15", "Z+15", {})
    assert not r.correct
    assert r.status == "ok"  # NOT invalid_format — fail through to normal check
    assert r.method != "bad_variable"


def test_mixed_case_and_extra_var_is_wrong_answer():
    """z+y against Z: z is case-only, but y is genuinely unknown → wrong."""
    r = check_answer("algexp", "z+y", "Z", {})
    assert not r.correct
    assert r.status == "ok"
    assert r.method != "bad_variable"


def test_correct_reply_passes():
    """Sanity: correct casing still validates."""
    r = check_answer("litexp", "Z+15", "Z+15", {})
    assert r.correct
    assert r.status == "ok"


def test_constants_dont_trigger_bad_variable():
    """`pi*r` against expected `r` should not trigger — pi is a constant,
    not a free symbol."""
    r = check_answer("algexp", "pi*r", "pi*r", {})
    assert r.correct
    assert r.status == "ok"


# Term order is intentionally NOT enforced. WIMS' algexp/litexp pipe
# both sides through `print(maxima ...)` which canonicalises the order,
# so any equivalent ordering is accepted (develop.fr/bin3 etc.).
def test_term_order_is_accepted():
    """Same value, different term order → still correct (WIMS-aligned)."""
    r = check_answer("algexp", "54*x^2 + 36*x + 27*x^3 + 8",
                     "27*x^3 + 54*x^2 + 36*x + 8", {})
    assert r.correct


def test_algexp_accepts_comma_decimal_in_comma_locale():
    """algexp avec une réponse décimale à virgule (arrondie2) : `0,113` doit
    valoir `0.113` en locale virgule, et NE PAS être lue comme un tuple (0,113).
    En locale point, la virgule n'est pas décimale."""
    assert check_answer("algexp", "0,113", "0.113000000000000", {}, lang="fr").correct
    assert check_answer("algexp", "0.113", "0.113000000000000", {}, lang="fr").correct
    assert not check_answer("algexp", "0,114", "0.113000000000000", {}, lang="fr").correct
    assert not check_answer("algexp", "0,113", "0.113000000000000", {}, lang="en").correct


def test_plain_litexp_enforces_decreasing_power_order():
    """Plain litexp (no polexpand) = « réduire et ordonner suivant les puissances
    décroissantes » (reduire1p): a reordered-but-equal answer is rejected, the
    canonical order is accepted, a wrong value stays a normal wrong answer."""
    bad = check_answer("litexp", "8+11v", "11*v + 8", {})
    assert not bad.correct and bad.status == "invalid_format" and bad.method == "term_order"
    assert check_answer("litexp", "11v+8", "11*v + 8", {}).correct
    wrong = check_answer("litexp", "12v+8", "11*v + 8", {})
    assert not wrong.correct and wrong.status == "ok"


def test_litexp_polexpand_accepts_reordered_terms():
    """litexp + polexpand: an expanded answer in non-canonical power order is
    accepted (WIMS canonicalises order). Regression for developperA4:
    `72y-54y^2` for `-54y^2+72y`. The shape constraint still rejects the
    factored form."""
    opt = {"option": "polexpand"}
    assert check_answer("litexp", "72y-54y^2", "-54*y^2+72*y", opt).correct
    factored = check_answer("litexp", "-9y(6y-8)", "-54*y^2+72*y", opt)
    assert not factored.correct and factored.status == "invalid_format"


# Unified warning message — both form-mismatch warnings share the wording.
def test_all_warnings_use_same_message():
    """polexpand and bad_variable share the same generic 'réécrire' message."""
    a = check_answer("litexp", "5*(x+9)^2", "5*x^2 + 90*x + 405", {})
    c = check_answer("litexp", "z+15", "Z+15", {})
    assert a.detail == c.detail
    assert "réécrire" in (a.detail or "")


# ─────────────────────────────────────────────────────────────────────────────
# Conformité WIMS I.3.a : précision `\precision{M}`, `absolute`,
# `\computeanswer{no}`, `option=default=X`.
# ─────────────────────────────────────────────────────────────────────────────
class TestWimsPrecision:
    def test_exact_reply_is_correct_at_default_precision(self):
        """Défaut 10000 : une réponse exacte reste juste."""
        r = check_answer("numeric", "0.3333333333", "1/3")
        assert r.correct and r.score == 1.0

    def test_poor_precision_gives_partial_credit(self):
        """0.333 pour 1/3 au défaut 10000 : juste « à la précision près » → 0.5."""
        r = check_answer("numeric", "0.333", "1/3")
        assert not r.correct
        assert r.score == pytest.approx(0.5)

    def test_loose_precision_accepts_rounded_reply(self):
        """`\\precision{100}` : 0.333 pour 1/3 devient pleinement juste."""
        r = check_answer("numeric", "0.333", "1/3", {"precision": 100.0})
        assert r.correct and r.score == 1.0

    def test_precision_flows_to_numexp_float_fallback(self):
        """numexp compare les rationnels exactement (0.333 ≠ 1/3), mais la
        précision gouverne le repli flottant quand l'attendu n'est pas un
        rationnel simple (ici composé `1/3+0` → repli)."""
        assert not check_answer("numexp", "0.333", "1/3", {"precision": 100.0}).correct
        assert check_answer("numexp", "0.333", "1/3+0", {"precision": 100.0}).correct

    def test_absolute_option_uses_absolute_difference(self):
        """Option `absolute` : |test-good|*prec < 1 → juste."""
        r = check_answer("numeric", "7.05", "7",
                         {"precision": 10.0, "option": "absolute"})
        assert r.correct
        r2 = check_answer("numeric", "7.5", "7",
                          {"precision": 10.0, "option": "absolute"})
        assert not r2.correct


class TestComputeAnswer:
    def test_expression_rejected_when_no(self):
        """`\\computeanswer{no}` (défaut) : `5*5` refusé pour `25`."""
        r = check_answer("numeric", "5*5", "25")
        assert not r.correct
        assert r.status == "invalid_format"

    def test_plain_value_accepted_when_no(self):
        assert check_answer("numeric", "25", "25").correct

    def test_simple_fraction_accepted_when_no(self):
        """Une fraction simple d'entiers reste acceptée."""
        assert check_answer("numeric", "3/4", "0.75").correct

    def test_leading_sign_allowed_when_no(self):
        assert check_answer("numeric", "-3", "-3").correct

    def test_expression_accepted_when_yes(self):
        r = check_answer("numeric", "5*5", "25", {"computeanswer": "yes"})
        assert r.correct


class TestDefaultOption:
    def test_empty_reply_substituted_by_default_value(self):
        assert check_answer("numeric", "", "0", {"option": "default=0"}).correct
        assert not check_answer("numeric", "", "5", {"option": "default=0"}).correct

    def test_default_vide_substitutes_empty_set(self):
        """`default=vide` (fset) : un champ laissé vide vaut la réponse « ∅ ».
        Correct si l'attendu est `vide`, faux sinon (substitution WIMS)."""
        assert check_answer("fset", "", "vide", {"option": "default=vide"}).correct
        assert not check_answer("fset", "", "13/5,-1", {"option": "default=vide"}).correct

    def test_non_empty_reply_ignores_default(self):
        assert check_answer("numeric", "5", "5", {"option": "default=0"}).correct


class TestNumexpFormal:
    """numexp WIMS : fraction irréductible + égalité rationnelle exacte."""

    def test_exact_fraction_accepted(self):
        assert check_answer("numexp", "1/4", "1/4").correct
        assert check_answer("numexp", "7/3", "7/3").correct

    def test_decimal_equal_to_fraction_accepted(self):
        """Un décimal exactement égal à la fraction attendue passe."""
        assert check_answer("numexp", "0.25", "1/4").correct
        assert check_answer("numexp", "0,25", "1/4", lang="fr").correct

    def test_unreduced_fraction_rejected(self):
        r = check_answer("numexp", "2/8", "1/4")
        assert not r.correct and r.status == "invalid_format"
        assert check_answer("numexp", "-12/2", "-6").correct is False

    def test_noreduction_accepts_unreduced(self):
        assert check_answer("numexp", "2/8", "1/4", {"option": "noreduction"}).correct

    def test_approx_decimal_rejected(self):
        """`0.333` n'est pas exactement `1/3` → refusé (pas de tolérance)."""
        assert not check_answer("numexp", "0.333", "1/3").correct

    def test_compound_expression_rejected(self):
        r = check_answer("numexp", "2+3", "5")
        assert not r.correct and r.status == "invalid_format"

    def test_fraction_and_decimal_mixed_rejected(self):
        r = check_answer("numexp", "1.5/2", "3/4")
        assert not r.correct and r.status == "invalid_format"

    def test_float_fallback_for_compound_expected(self):
        """Attendu composé non évalué (`5*3`) : repli flottant, `15` accepté."""
        assert check_answer("numexp", "15", "5*3").correct


class TestAtextReplygoodLines:
    """`atext` ne compare qu'à la **première ligne** de son `replygood`.

    Le checker WIMS (`anstype/atext`) ouvre sur :

        good=!singlespace $(replygood$i)
        good=!rows2lines $good
        good=!nonempty lines $good
        badwords=!line 2 to -1 of $good
        good=!line 1 of $good

    `rows2lines` fait des `;` des sauts de ligne. Ce qui suit n'est donc pas
    une alternative : `oefcountries` y range la liste des **autres** pays, dont
    WIMS ne se sert que pour son diagnostic `unknownword`.
    """

    def test_only_the_first_line_is_the_answer(self):
        expected = "Vatican;Algérie,Angola,Pologne,Suède"
        assert check_answer("atext", "Vatican", expected).correct

    def test_a_badword_is_not_accepted(self):
        """Un pays de la seconde ligne est une *mauvaise* réponse."""
        expected = "Vatican;Algérie,Angola,Pologne,Suède"
        assert not check_answer("atext", "Pologne", expected).correct

    def test_alternatives_still_split_on_pipe(self):
        """Le `|` reste le séparateur d'alternatives, dans la ligne 1."""
        expected = "Pays-Bas|Hollande;Belgique,Suisse"
        assert check_answer("atext", "Hollande", expected).correct
        assert check_answer("atext", "Pays-Bas", expected).correct
        assert not check_answer("atext", "Belgique", expected).correct

    def test_tolerance_still_applies_to_the_first_line(self):
        """Casse, accents et articles restent ignorés après le découpage."""
        expected = "Vatican;Algérie,Angola"
        assert check_answer("atext", "le vatican", expected).correct

    def test_html_entity_semicolon_is_not_a_separator(self):
        """`rows2lines` épargne le `;` qui ferme une entité : `caf&eacute;`
        reste d'un bloc en ligne 1, au lieu d'être coupé après `caf&eacute`.

        (WIMS ne décode pas l'entité pour autant — sa normalisation change `&`
        et `;` en espaces —, donc c'est bien `caf&eacute;` qu'on retrouve.)
        """
        assert check_answer("atext", "caf&eacute;", "caf&eacute;;Belgique").correct
        assert not check_answer("atext", "Belgique", "caf&eacute;;Belgique").correct

    def test_plain_expected_unchanged(self):
        """Sans `;`, rien ne change."""
        assert check_answer("atext", "triangle", "les triangles").correct


class TestAtextDisplayAnswer:
    """`replyGood` — la bonne réponse *affichée* — n'est pas `replygood`.

    Le checker WIMS la dérive juste après avoir isolé la ligne 1 :

        replyGood$i=!translate | to <NL> in $good
        replyGood$i=!nonempty lines $(replyGood$i)
        replyGood$i=!line 1 of $(replyGood$i)

    C'est donc la première alternative de la première ligne.
    """

    def test_first_alternative_of_first_line(self):
        from core.answer.checkers import atext_display_answer
        assert atext_display_answer("Pays-Bas|Hollande;Belgique,Suisse") == "Pays-Bas"

    def test_badwords_are_never_shown(self):
        """Le corrigé de `oefcountries` déroulait les deux cents pays."""
        from core.answer.checkers import atext_display_answer
        assert atext_display_answer("Vatican;Algérie,Angola,Pologne") == "Vatican"

    def test_plain_answer_unchanged(self):
        from core.answer.checkers import atext_display_answer
        assert atext_display_answer("triangle") == "triangle"

    def test_empty_stays_empty(self):
        from core.answer.checkers import atext_display_answer
        assert atext_display_answer("") == ""
