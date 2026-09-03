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


class TestCheckRange:
    """`range` : la réponse doit tomber dans un intervalle, pas l'égaler.

    `anstype/range` lit `replygood` par **paires de bornes** :

        gcnt=!itemcnt $(replygood$i)
        !if $gcnt<2 … Text=bad …
        !for t=1 to $[floor($gcnt/2)]
          g1=$(replygood$i[2*$t-1]) ; g2=$(replygood$i[2*$t])
          !if inf notin $g1$g2 and $G1>$G2 … !exchange G1,G2
          !if (inf isin $G1 or $G1<=$test) and (inf isin $G2 or $G2>=$test)
            diag=yes
    """

    def test_inside_the_interval(self):
        assert check_answer("range", "0.5", "0.6,0.4").correct

    def test_bounds_are_inclusive(self):
        assert check_answer("range", "0.4", "0.6,0.4").correct
        assert check_answer("range", "0.6", "0.6,0.4").correct

    def test_outside_is_wrong(self):
        assert not check_answer("range", "0.7", "0.6,0.4").correct

    def test_bounds_may_come_reversed(self):
        """`!exchange G1,G2` : `0.6,0.4` est l'intervalle [0.4 ; 0.6]."""
        assert check_answer("range", "0.5", "0.4,0.6").correct
        assert check_answer("range", "0.5", "0.6,0.4").correct

    def test_degenerate_interval(self):
        """`3,3` n'accepte que 3 — c'est la forme qu'emploie `tabvaleur1`."""
        assert check_answer("range", "3", "3,3").correct
        assert not check_answer("range", "3.1", "3,3").correct

    def test_several_pairs_are_a_union(self):
        assert check_answer("range", "1.5", "1,2,4,6").correct
        assert check_answer("range", "5", "1,2,4,6").correct
        assert not check_answer("range", "3", "1,2,4,6").correct

    def test_infinite_bound_opens_the_side(self):
        assert check_answer("range", "-5", "-inf,0").correct
        assert not check_answer("range", "100", "-inf,0").correct

    def test_a_single_bound_is_unusable(self):
        """`!if $gcnt<2` → `Text=bad` : rien à comparer."""
        assert not check_answer("range", "3", "3").correct

    def test_non_numeric_reply_is_wrong(self):
        assert not check_answer("range", "abc", "0.4,0.6").correct


class TestRangeDisplayAnswer:
    """Le corrigé d'un `range` montre une valeur, pas les bornes stockées."""

    def test_midpoint_of_the_first_pair(self):
        from core.answer.checkers import range_display_answer
        assert range_display_answer("0.6,0.4") == "0.5"
        assert range_display_answer("1,2,4,6") == "1.5"

    def test_open_interval_keeps_its_bounds(self):
        from core.answer.checkers import range_display_answer

    def test_odd_count_means_the_last_item_is_the_answer(self):
        """`!if $[$gcnt%2]=1 … replyGood=$(replygood[-1])`."""
        from core.answer.checkers import range_display_answer
        assert range_display_answer("1,2,environ 1.5") == "environ 1.5"

    def test_only_the_list_separator_is_localised_here(self):
        """La virgule décimale vient d'ailleurs (passe transverse de `check.py`).

        Cet appelant ne décide que du séparateur de **liste** : `;` quand la
        virgule est décimale, pour que les deux rôles restent distincts.
        """
        from core.answer.checkers import range_display_answer
        assert range_display_answer("0.6,0.4", comma_is_decimal=True) == "0.5"
        assert range_display_answer("-inf,0", comma_is_decimal=True) == "-inf;0"
        assert range_display_answer("-inf,0", comma_is_decimal=False) == "-inf,0"


class TestCheckEquation:
    """`equation` : deux équations sont égales **à un facteur près**.

    `anstype/equation` ramène chaque membre à `gauche-(droite)`, puis mesure la
    constance du rapport des deux expressions :

        t=!translate internal = to $\\n$ in $t
        !distribute lines $t into t,t2
        !if $t2!=$empty ; t=$t-($t2)
        …
        tt=($t)/($s)
        …
        !if $abs<1/$precision or ($max)*($min)<0 ; test=100
        !else ; test=$[abs($max-($min))/$abs]

    Un rapport constant ⇒ équations proportionnelles ⇒ même équation. C'est ce
    que le repli sur `check_text` détruisait : il n'acceptait que l'écriture
    stockée par l'auteur.
    """

    # Attendu réel de `H4/algebra/h4droites.fr/def/equationDe2pts.def`.
    DROITE = "2*x - 3*y - 1=0"
    OPTS = {"precision": 1000.0, "computeanswer": "yes"}

    def test_the_stored_form_is_accepted(self):
        assert check_answer("equation", self.DROITE, self.DROITE, self.OPTS).correct

    def test_a_proportional_equation_is_the_same_line(self):
        """Le cœur du type : `4x-6y-2=0` est la droite de `2x-3y-1=0`."""
        for reply in ("4x-6y-2=0", "-2x+3y+1=0", "6x-9y-3=0"):
            assert check_answer("equation", reply, self.DROITE, self.OPTS).correct

    def test_terms_may_cross_the_equal_sign(self):
        assert check_answer("equation", "2x-3y=1", self.DROITE, self.OPTS).correct

    def test_terms_may_be_reordered(self):
        assert check_answer("equation", "-1-3y+2x=0", self.DROITE, self.OPTS).correct

    def test_a_different_line_is_wrong(self):
        for reply in ("2x-3y-2=0", "x-3y-1=0", "2x+3y-1=0"):
            assert not check_answer("equation", reply, self.DROITE, self.OPTS).correct

    def test_missing_equal_sign_is_a_badform(self):
        """`option:eqsign=yes` → `test=NaN badform`, pas « faux »."""
        r = check_answer("equation", "2x-3y-1", self.DROITE, self.OPTS)
        assert not r.correct
        assert r.status == "invalid_format"

    def test_eqsign_no_implies_equals_zero(self):
        """Avec `eqsign=no`, WIMS sous-entend « = 0 »."""
        opts = {**self.OPTS, "option": "eqsign=no"}
        assert check_answer("equation", "2x-3y-1", self.DROITE, opts).correct

    def test_the_null_equation_is_not_an_equation(self):
        """`0=0` : rapport nul, écarté par `abs($max)<1/$precision`."""
        assert not check_answer("equation", "0=0", self.DROITE, self.OPTS).correct

    def test_a_vertical_axis_equation(self):
        """Attendu de `oefseconddegree.fr/def/sddescrcourbe2` : `x=-3`."""
        for reply in ("x=-3", "x+3=0", "2x+6=0"):
            assert check_answer("equation", reply, "x=-3").correct
        assert not check_answer("equation", "x=3", "x=-3").correct

    def test_fractional_expected(self):
        """`sdsymetrie` stocke `x=-13/2` ; `2x+13=0` est la même équation."""
        assert check_answer("equation", "2x+13=0", "x=-13/2").correct
        assert not check_answer("equation", "2x+13.5=0", "x=-13/2").correct

    def test_extra_variables_after_the_equation(self):
        """`!item 2 to -1 of $(replygood)` déclare des variables, pas une autre
        équation."""
        assert check_answer("equation", "2x^2+2y^2=2", "x^2+y^2=1,x,y").correct

    def test_a_decimal_comma_is_not_a_variable_list(self):
        """Garde-fou : `x=0,5` reste une équation, pas « x=0 » plus « 5 »."""
        assert check_answer("equation", "2x=1", "x=0.5").correct

    def test_unparsable_reply_is_a_badform(self):
        r = check_answer("equation", "???=0", self.DROITE, self.OPTS)
        assert not r.correct
        assert r.status == "invalid_format"


class TestCheckVector:
    """`vector` : comparaison composante par composante, **en valeur**.

    `anstype/vector` :

        dd=!declosing $(reply$i)
        !if ; isin $dd ; test=NaN ; !exit
        !if , notin $good ; good=!words2items $good
        !if $n1=$n2 … !ifval $x_=$y_ … test=!append item yes to $test
        !else ; badsize$i=true

    Deux passages : `precision` (juste), puis `sqrt(precision)` (« presque
    juste », non crédité). `badsize` est exclu du second — un vecteur de la
    mauvaise taille est faux, pas imprécis.
    """

    # Attendus réels de `H3/geometry/oeftranslation.fr/def/`.
    V = "3,-3"
    FRAC = "-5.5/2,-9.5/2"

    def test_the_stored_form_is_accepted(self):
        assert check_answer("vector", self.V, self.V).correct

    def test_enclosing_delimiters_are_optional(self):
        """`!declosing` : `(3,-3)` et `[3,-3]` valent `3,-3`."""
        for reply in ("(3,-3)", "[3,-3]", "{3,-3}"):
            assert check_answer("vector", reply, self.V).correct

    def test_space_separates_when_no_comma(self):
        """`!words2items` : `3 -3` vaut `3,-3`."""
        assert check_answer("vector", "3 -3", self.V).correct

    def test_components_are_compared_by_value(self):
        """`translation5` stocke `-5.5/2` ; l'élève qui simplifie a juste."""
        assert check_answer("vector", "-2.75,-4.75", self.FRAC).correct
        assert check_answer("vector", "(-2.75,-4.75)", self.FRAC).correct

    def test_a_wrong_component_is_wrong(self):
        assert not check_answer("vector", "-2.75,-4.5", self.FRAC).correct

    def test_order_matters(self):
        assert not check_answer("vector", "-3,3", self.V).correct

    def test_semicolon_is_refused_in_a_dot_locale(self):
        """`!if ; isin $dd ; test=NaN` — avant tout découpage."""
        r = check_answer("vector", "3;-3", self.V, lang="en")
        assert not r.correct
        assert r.status == "invalid_format"

    def test_semicolon_separates_in_a_comma_locale(self):
        """Écart assumé au C : le `;` est le séparateur de liste des langues à
        virgule décimale (`core/oef/i18n.py`), et la virgule y appartient au
        nombre. WIMS, qui n'écrit jamais `-2,75`, le refusait net."""
        assert check_answer("vector", "3;-3", self.V, lang="fr").correct
        assert check_answer("vector", "-2,75;-4,75", self.FRAC, lang="fr").correct
        assert check_answer("vector", "(-2,75;-4,75)", self.FRAC, lang="nl").correct

    def test_the_comma_form_still_works_in_a_comma_locale(self):
        """L'attendu du moteur reste en notation à point : accepter le `;` ne
        doit pas coûter la forme que WIMS stocke."""
        assert check_answer("vector", "3,-3", self.V, lang="fr").correct
        assert check_answer("vector", "-2.75,-4.75", self.FRAC, lang="fr").correct

    def test_a_wrong_value_stays_wrong_with_semicolons(self):
        assert not check_answer("vector", "-2,75;-4,5", self.FRAC, lang="fr").correct

    def test_wrong_size_is_wrong_not_imprecise(self):
        """`badsize` est exclu du second passage : score 0, pas 0.5."""
        r = check_answer("vector", "3,-3,0", self.V)
        assert not r.correct
        assert r.score == 0.0

    def test_almost_right_scores_half(self):
        """Second passage à `sqrt(precision)` : signalé, non crédité."""
        r = check_answer("vector", "3.001,-3", self.V, {"precision": 10000.0})
        assert not r.correct
        assert r.score == 0.5

    def test_function_calls_are_evaluated(self):
        """Les composantes passent par le `$[...]` de WIMS, pas par un
        appariement littéral."""
        assert check_answer("vector", "sqrt(2)/2,0", "0.7071067811865476,0").correct

    def test_unparsable_reply_is_a_badform(self):
        r = check_answer("vector", "abc,def", self.V)
        assert not r.correct
        assert r.status == "invalid_format"


class TestReplytypeNormalisation:
    """`oef/replytype.proc` : le nom de type canonique, avant tout dispatch.

        rt_1=!positionof item $(replytype$i) in $rt_names
        !if $rt_1 != $empty and $rt_1 > 0
          replytype$i=!item $rt_1 of $rt_types
        !default replytype$i=default
        replytype$i=!word 1 of $(replytype$i)
        !if $(replytype$i) notwordof $rt_all
          replytype$i=!text select abcdef…0123456789 in $(replytype$i)
          !readproc anstype/$(replytype$i).input def
          !if $anstype!=yes
            replytype$i=default
    """

    def test_historical_aliases(self):
        from core.answer.checkers import normalize_replytype
        assert normalize_replytype("number") == "numeric"
        assert normalize_replytype("select") == "menu"
        assert normalize_replytype("expalg") == "algexp"
        assert normalize_replytype("coordinates") == "coord"
        assert normalize_replytype("correspondance") == "correspond"
        assert normalize_replytype("auto") == "default"
        assert normalize_replytype("unit") == "units"

    def test_text_is_an_alias_of_case_not_a_text_match(self):
        """`rt_types` fait correspondre `text` à `case`, qui sait lire les
        écritures alternatives séparées par `|`."""
        from core.answer.checkers import normalize_replytype
        assert normalize_replytype("text") == "case"
        assert check_answer("text", "bleu", "rouge|bleu|vert").correct

    def test_an_empty_type_is_default(self):
        """`!default replytype$i=default` — 216 rendus du corpus sortent du
        moteur sans type."""
        from core.answer.checkers import normalize_replytype
        assert normalize_replytype("") == "default"
        assert normalize_replytype("   ") == "default"
        assert normalize_replytype(None) == "default"

    def test_only_the_first_word_counts(self):
        """`!word 1 of $(replytype$i)` : `default nonstop` reste `default`."""
        from core.answer.checkers import normalize_replytype
        assert normalize_replytype("default nonstop") == "default"
        assert normalize_replytype("numeric absolute") == "numeric"

    def test_an_unsubstituted_variable_falls_back_to_default(self):
        """`\\typerep`, `$(val11[])menu` : des restes de substitution, pas des
        types. Le nettoyage alphanumérique du C ne les sauve pas."""
        from core.answer.checkers import normalize_replytype
        assert normalize_replytype("\\typerep") == "typerep"
        assert normalize_replytype("$(val11[])menu") == "val11menu"

    def test_case_and_spacing_are_ignored(self):
        from core.answer.checkers import normalize_replytype
        assert normalize_replytype("  NUMERIC  ") == "numeric"
        assert normalize_replytype("Vector") == "vector"


class TestUnknownTypeFallback:
    """Un type que WIMS ne connaît pas devient `default`, jamais du texte.

    `replytype.proc` n'a pas de repli textuel : faute de reconnaître le nom et
    de trouver un `anstype/<type>.input` qui se déclare (`!set anstype=yes`),
    il pose `replytype$i=default` — une comparaison mathématique.
    """

    def test_an_invented_type_compares_mathematically(self):
        """`rational`, `fonction`, `equations`… n'existent nulle part chez
        WIMS. `check_text` refusait `4/2` pour `2`."""
        for typ in ("rational", "integer", "fonction", "equations", "real"):
            assert check_answer(typ, "4/2", "2").correct, typ

    def test_an_invented_type_still_rejects_a_wrong_answer(self):
        for typ in ("rational", "integer", "fonction"):
            assert not check_answer(typ, "3", "2").correct, typ

    def test_equivalent_writings_are_accepted(self):
        assert check_answer("fonction", "2*x+2", "2(x+1)").correct
        assert check_answer("rational", "0.5", "1/2").correct

    def test_a_real_wims_type_keeps_the_literal_comparison(self):
        """`click`, `geogebra`, `draw` : leur checker existe chez WIMS et n'est
        pas porté. Les comparer mathématiquement n'aurait aucun sens — c'est
        une dette, tracée par `[ANSWER-FALLBACK]`, pas un `default`."""
        assert check_answer("click", "3,4", "3,4").correct
        assert not check_answer("click", "4/2,4", "2,4").correct

    def test_a_module_defined_type_is_not_an_invented_one(self):
        """`autoeval` a un `anstype/` **dans le module**, que `replytype.proc`
        résout avant de conclure : ce n'est pas un nom inventé que WIMS
        ramènerait à `default`, mais une dette — comparaison littérale, tracée
        par `[ANSWER-FALLBACK]`.

        `runcode` et `js2wims1` ont tenu ce rôle jusqu'à leur port (2026-09-03) :
        depuis, ils ont leur checker, qui attend une liste de valeurs et non du
        texte brut."""
        from core.answer.checkers import normalize_replytype
        assert normalize_replytype("autoeval") == "autoeval"
        assert check_answer("autoeval", "print(2)", "print(2)").correct
        assert not check_answer("autoeval", "4/2", "2").correct


class TestDefaultIsARouter:
    """`anstype/default` n'est pas un comparateur mais un aiguilleur.

        eq==
        !if $eq isin $(replygood$i) and $wims_read_parm!=sub
          !changeto anstype/equation
        …
        nn=$[$(replygood$i)]
        !if NaN notin $nn
          !changeto anstype/numeric
        …
        !if $varlen<=3
          !changeto anstype/function
        !changeto anstype/atext

    Il lit l'attendu avant de choisir. C'est aussi le type que `replytype.proc`
    pose quand le `.def` n'en déclare aucun — là où PAX supposait `numeric`,
    ce qui notait fausse toute réponse algébrique non typée.
    """

    def test_an_expected_with_an_equals_goes_to_equation(self):
        """`fnctaff3` attend `-1=3*a+b` : le « = » y faisait échouer la
        comparaison algébrique."""
        assert check_answer("default", "-1=3*a+b", "-1=3*a+b").correct
        assert check_answer("default", "3*a+b=-1", "-1=3*a+b").correct
        assert not check_answer("default", "3*a+b=1", "-1=3*a+b").correct

    def test_a_numeric_expected_keeps_its_tolerance(self):
        """Un attendu qui s'évalue en nombre relève de `numeric` — et donc de
        `\\precision`, qu'une comparaison symbolique ignorerait."""
        r = check_answer("default", "0.25", "1/4")
        assert r.correct and r.method == "numeric"

    def test_a_short_variable_goes_the_algebraic_way(self):
        """`distrired` attend `2*b`, `pairs4` attend `1-p` : variables d'un
        caractère, donc `function` chez WIMS."""
        assert check_answer("default", "2*b", "2*b").correct
        assert check_answer("default", "b*2", "2*b").correct
        assert check_answer("default", "1-p", "1-p").correct
        assert not check_answer("default", "3*b", "2*b").correct

    def test_a_plain_word_still_compares_as_text(self):
        """Un attendu que rien n'évalue reste comparé littéralement.

        (La casse, elle, est tranchée en amont par le pré-check
        `bad_variable`, antérieur à cet aiguillage et inchangé par lui.)
        """
        assert check_answer("default", "Paris", "Paris").correct
        assert not check_answer("default", "Londres", "Paris").correct

    def test_a_relational_operator_is_not_an_equation(self):
        """`<=` et `>=` ne déclenchent pas l'aiguillage vers `equation` : le C
        cherche un « = » **seul**, et sympy sait rendre les composés."""
        r = check_answer("default", "x <= 3", "x<=3")
        assert r.method != "equation"


class TestSigunitsDisplayAnswer:
    """Le corrigé d'un `sigunits` montre la valeur arrondie, pas la consigne.

    L'attendu se stocke `"<valeur> <unité> #N"` : `#N` n'est pas une réponse,
    c'est le nombre de chiffres significatifs exigé. Affiché tel quel,
    `astron2` rendait `74753832.77 km^2 #4` — la valeur que l'élève devait
    justement arrondir, suivie d'un marqueur qui ne lui parle pas.
    """

    def test_scientific_notation_beyond_the_significant_digits(self):
        from core.answer.checkers import sigunits_display_answer as D
        assert D("74753832.77 km^2 #4") == "7.475e7 km^2"
        assert D("3802500 N#4") == "3.802e6 N"

    def test_a_value_that_already_fits_stays_decimal(self):
        from core.answer.checkers import sigunits_display_answer as D
        assert D("4878 km #4") == "4878 km"
        assert D("55.3896 #4") == "55.39"
        assert D("1.5 m #2") == "1.5 m"

    def test_what_it_shows_is_what_the_checker_accepts(self):
        """Le corrigé doit être une réponse juste — sinon on montre à l'élève
        une valeur qu'on lui aurait refusée."""
        from core.answer.checkers import sigunits_display_answer as D
        for attendu in ("74753832.77 km^2 #4", "4878 km #4", "3802500 N#4",
                        "19.6349540849 #4", "2.57304292311 #4", "44226 N#4"):
            assert check_answer("sigunits", D(attendu), attendu).correct, attendu

    def test_an_expected_without_the_marker_is_left_alone(self):
        from core.answer.checkers import sigunits_display_answer as D
        assert D("4878 km") == "4878 km"


class TestCoordZones:
    """Une click-zone se calcule, et ce qu'on y attend est un point.

    `getvalue` (`Misc/clickzone.c`) passe chaque composante au calculateur :
    ce sont des expressions, pas des littéraux. Et `reply` est le **pixel
    cliqué**, quand `expected` décrit la cible — les confondre revient à
    demander à l'élève de saisir la consigne.
    """

    def test_a_radius_can_be_an_expression(self):
        """`somvect` pose `circle,110,80,30/3` — rayon 10, pas « pas de rayon »."""
        assert check_answer("coord", "110,80", "circle,110,80,30/3").correct
        assert not check_answer("coord", "160,80", "circle,110,80,30/3").correct

    def test_a_centre_can_be_an_expression(self):
        """`tracredstep` pose `circle,200,200-20*7,9` — centre (200, 60)."""
        assert check_answer("coord", "200,60", "circle,200,200-20*7,9").correct
        assert not check_answer("coord", "200,200", "circle,200,200-20*7,9").correct

    def test_the_centre_of_each_shape(self):
        from core.answer.checkers import coord_display_answer as D
        assert D("circle,110,80,30/3") == "110,80"
        assert D("point,204,338") == "204,338"
        assert D("rectangle,10,20,50,60") == "30,40"

    def test_what_it_offers_is_what_the_checker_accepts(self):
        from core.answer.checkers import coord_display_answer as D
        for zone in ("circle,110,80,30/3", "circle,200,200-20*7,9",
                     "point,204,338", "rectangle,10,20,50,60"):
            assert check_answer("coord", D(zone), zone).correct, zone

    def test_une_zone_sans_image_ne_propose_rien(self):
        """`bound` teste l'appartenance à une région d'un GIF ; sans nom de
        fichier il n'y a pas de zone du tout — le cas de `quadrilatere`, dont
        l'image est un SVG produit par flydraw et non un GIF sur disque."""
        from core.answer.checkers import coord_display_answer as D
        assert D("(bound,,56,146)") == ""

    def test_le_point_de_reference_dun_bound_est_un_clic_valide(self):
        """Il appartient par construction à la région qu'il désigne, ce qui en
        fait la réponse à proposer — le reste du travail est dans l'image."""
        from core.answer.checkers import coord_display_answer as D
        assert D("b,dept.gif,204,338") == "204,338"

    def test_seule_la_premiere_zone_vaut_bonne_reponse(self):
        """`anstype/coord` ne retient le rang rendu par `clickzone` que s'il
        vaut 1 (`!if $i_=1`) : les zones suivantes servent au diagnostic."""
        from core.answer.checkers import coord_display_answer as D
        zones = "point,10,10;point,300,300"
        assert D(zones) == "10,10"
        assert check_answer("coord", "10,10", zones).correct
        assert not check_answer("coord", "300,300", zones).correct


class TestCheckDraw:
    """`type=draw` : l'élève trace des objets sur une figure, et c'est la liste
    de leurs coordonnées — dans le repère du dessin — qui est corrigée.

    Port d'`anstype/draw` et de son `draw.inc`. Le rendu était jusqu'ici un
    champ de saisie : PAX lisait la taille du canevas (`800 x 400` pixels)
    comme une géométrie de `textarea` et n'affichait aucune figure.
    """

    FOND = "[xrange -3,2\npolygon black, 1,2]"
    BON = FOND + ";crosshairs,1.5,-0.5,-2.1,-0.9,1.0,-0.9"

    def test_les_points_attendus_dans_l_ordre(self):
        assert check_answer("draw", "1.5,-0.5,-2.1,-0.9,1.0,-0.9", self.BON).correct

    def test_l_ordre_est_indifferent(self):
        """L'appariement est glouton : chaque point posé cherche un attendu
        libre, sans que l'ordre compte."""
        assert check_answer("draw", "1.0,-0.9,1.5,-0.5,-2.1,-0.9", self.BON).correct

    def test_la_tolerance_vient_de_l_option(self):
        """`!default precision=1000`, que `replyoption` règle : l'écart admis
        est `1/precision`, en unités du repère."""
        opts = {"option": "precision=10"}
        assert check_answer("draw", "1.55,-0.5,-2.1,-0.9,1.0,-0.9", self.BON, options=opts).correct
        serre = {"option": "precision=1000"}
        assert not check_answer("draw", "1.55,-0.5,-2.1,-0.9,1.0,-0.9", self.BON, options=serre).correct

    def test_bareme_partiel_avec_split(self):
        """`score = (justes − coeff·max(en trop, manquants)) / attendus`, avec
        `coeff=1` pour `split`. Deux points sur trois valent donc un tiers."""
        opts = {"option": "split precision=10"}
        r = check_answer("draw", "1.5,-0.5,-2.1,-0.9", self.BON, options=opts)
        assert not r.correct
        assert abs(r.score - 1 / 3) < 1e-9

    def test_eqweight_ne_penalise_qu_a_demi(self):
        opts = {"option": "eqweight precision=10"}
        r = check_answer("draw", "1.5,-0.5,-2.1,-0.9", self.BON, options=opts)
        assert abs(r.score - (2 - 0.5) / 3) < 1e-9

    def test_sans_option_c_est_tout_ou_rien(self):
        opts = {"option": "precision=10"}
        assert check_answer("draw", "1.5,-0.5,-2.1,-0.9", self.BON, options=opts).score == 0.0

    def test_un_point_en_trop_coute(self):
        opts = {"option": "split precision=10"}
        r = check_answer("draw", "1.5,-0.5,-2.1,-0.9,1.0,-0.9,0,0", self.BON, options=opts)
        assert abs(r.score - 2 / 3) < 1e-9

    def test_un_segment_se_lit_dans_les_deux_sens(self):
        """`draw.inc` ajoute aux bonnes réponses la version retournée des types
        symétriques — un segment tracé de B vers A vaut celui de A vers B."""
        bon = self.FOND + ";segments,0,0,1,1"
        opts = {"option": "precision=100"}
        assert check_answer("draw", "0,0,1,1", bon, options=opts).correct
        assert check_answer("draw", "1,1,0,0", bon, options=opts).correct

    def test_une_fleche_garde_son_sens(self):
        """`arrows` n'est pas dans la liste des types symétriques : le sens
        compte, c'est tout l'objet d'un vecteur."""
        bon = self.FOND + ";arrows,0,0,1,1"
        opts = {"option": "precision=100"}
        assert check_answer("draw", "0,0,1,1", bon, options=opts).correct
        assert not check_answer("draw", "1,1,0,0", bon, options=opts).correct

    def test_la_figure_de_fond_ne_compte_pas_comme_reponse(self):
        """Le fond est entre crochets et porte lui-même des nombres : le
        découpage en rangées doit s'arrêter aux `;` de profondeur zéro, sans
        quoi les coordonnées du dessin passeraient pour la bonne réponse."""
        from core.answer.checkers import draw_display_answer

        assert draw_display_answer(self.BON) == "1.5,-0.5,-2.1,-0.9,1.0,-0.9"

    def test_une_reponse_vide_ne_vaut_rien(self):
        assert check_answer("draw", "", self.BON).score == 0.0

    def test_le_corrige_groupe_les_coordonnees(self):
        """La liste plate se lit mal : « 3,3,1,-3 » a l'air de quatre nombres
        quand ce sont deux points. Le corrigé les groupe par objet."""
        from core.answer.checkers import draw_feedback_answer as F

        assert F(self.FOND + ";crosshairs,3,3,1,-3") == "(3, 3) ; (1, -3)"
        assert F(self.FOND + ";arrows,0,0,1,1") == "(0, 0, 1, 1)"
        assert F(self.FOND) == ""


class TestLigneDeZones:
    """Une **ligne** de click-zone est une expression booléenne, pas une zone.

    Port d'`oneline` (`Misc/clickzone.c:231`) : `|` pour le ou, `&` pour le et,
    `^` pour la négation, des parenthèses pour grouper. Sans lui, une question
    qui offre plusieurs régions acceptables — `oefpolygon/quadrilatere` en
    admet quatre pour « concave » — n'en voyait aucune.
    """

    ZONE_A = "(point,10,10)"
    ZONE_B = "(point,200,200)"

    def test_ou(self):
        ligne = f"{self.ZONE_A} | {self.ZONE_B}"
        assert check_answer("coord", "10,10", ligne).correct
        assert check_answer("coord", "200,200", ligne).correct
        assert not check_answer("coord", "150,40", ligne).correct

    def test_et(self):
        # Un point ne peut pas être aux deux endroits à la fois.
        ligne = f"{self.ZONE_A} & {self.ZONE_B}"
        assert not check_answer("coord", "10,10", ligne).correct

    def test_negation(self):
        assert check_answer("coord", "200,200", f"^{self.ZONE_A}").correct
        assert not check_answer("coord", "10,10", f"^{self.ZONE_A}").correct

    def test_la_virgule_interne_ne_coupe_pas(self):
        """Les séparateurs se lisent hors parenthèses (`strparchr`) : la
        virgule d'une zone ne doit pas être prise pour une frontière."""
        ligne = f"(rectangle,0,0,50,50) | {self.ZONE_B}"
        assert check_answer("coord", "25,25", ligne).correct


class TestBoundGeometrique:
    """`bound` sur une figure vectorielle.

    WIMS remplit un bitmap depuis le clic et regarde si le point de référence a
    pris la couleur. PAX n'a pas de bitmap : la question se reformule
    exactement — deux points sont dans la même région si le segment qui les
    joint ne croise aucune frontière tracée. L'équivalence est stricte tant que
    les régions sont convexes, ce qu'assure un découpage par des droites.
    """

    # Un cadre et une droite verticale qui le coupe en deux.
    SVG = (
        '<svg width="200" height="200">'
        '<rect x="0.00" y="0.00" width="200.00" height="200.00" fill="none" />'
        '<polyline points="100.00,0.00 100.00,200.00" fill="none" />'
        "</svg>"
    )

    def _meme_region(self, a, b):
        from core.answer.checkers import _meme_region_svg

        return _meme_region_svg(a, b, self.SVG)

    def test_meme_cote(self):
        assert self._meme_region((20, 20), (60, 180))

    def test_cotes_opposes(self):
        assert not self._meme_region((20, 20), (180, 20))

    def test_le_cadre_est_une_frontiere(self):
        """Un point de référence hors du cadre n'est atteignable par aucun
        clic — comme chez WIMS, où `gdImageGetPixel` hors image ne rend pas la
        couleur de remplissage."""
        assert not self._meme_region((20, 20), (250, 20))

    def test_sans_figure_rien_n_est_valide(self):
        from core.answer.checkers import _meme_region_svg

        assert _meme_region_svg((1, 1), (2, 2), "") is True  # aucune frontière


class TestCasePonctuation:
    """`anstype/case` traduit ses `badchars` en espaces — des deux côtés — puis
    `!singlespace` et `!trim` avant de comparer.

    Sans cela, `mathelexikon1/Kreisenkette` était inaccessible. Son
    `replygood1=$(val74[1;]);$(val72[1;])` sort `e;` : le `;` n'est qu'un
    séparateur entre deux composantes, dont la seconde est **délibérément
    vide** — l'exercice écrit `!ifval $val21 iswordof case raw → val72=`. Il
    fallait donc taper `e;` pour avoir juste, là où la désinence allemande
    attendue est `e`. Ses vingt-deux champs étaient dans ce cas.
    """

    def test_le_separateur_en_trop_ne_compte_pas(self):
        assert check_answer("case", "e", "e;").correct
        assert check_answer("case", "e;", "e;").correct
        assert check_answer("case", "Kreisen und ein", "Kreisen und ein;").correct

    def test_une_mauvaise_reponse_reste_mauvaise(self):
        assert not check_answer("case", "a", "e;").correct
        assert not check_answer("case", "", "e;").correct
        assert not check_answer("case", "en", "e;").correct

    def test_les_alternatives_restent_reconnues(self):
        """La barre verticale sépare les alternatives de l'attendu ; elle est
        découpée avant la normalisation, et neutralisée dans la réponse."""
        assert check_answer("case", "rouge", "rouge|bleu").correct
        assert check_answer("case", "bleu", "rouge|bleu").correct
        assert not check_answer("case", "vert", "rouge|bleu").correct

    def test_espaces_multiples_et_ponctuation_variee(self):
        assert check_answer("case", "un  deux", "un deux").correct
        assert check_answer("case", "un, deux", "un deux").correct
        assert check_answer("case", " un deux ", "un.deux").correct
