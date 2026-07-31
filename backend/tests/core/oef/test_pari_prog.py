"""
Mini-interpréteur PARI/GP impératif (`core/oef/def_engine/pari_prog.py`).

`_call_pari` n'évaluait qu'une expression unique ; les programmes que WIMS
passe à `!exec pari` (affectations, `for`, `print` multiples) fuyaient en
source brute dans la valeur calculée. Ces tests couvrent les formes réellement
présentes dans le corpus.
"""

import pytest

from core.oef.def_engine import _call_pari
from core.oef.def_engine.pari_prog import (
    PariProgramError,
    looks_like_program,
    run_pari_program,
)


class TestProgramDetection:
    @pytest.mark.parametrize(
        "src",
        [
            "i = 3 ; l = [1,2] ; print(l[1])",
            "for(j=1,3,print(j))",
            "n=0",
            "{ a=1; print(a) }",
            "print(sum(t=1,4,t^2))",
            "print([1,2]*[3,4]~)",
        ],
    )
    def test_programs(self, src):
        assert looks_like_program(src)

    @pytest.mark.parametrize(
        "src",
        ["gcd(12,18)", "print(3/4)", "polcoeff(x^2+3*x+2,1)", "matdet([1,2;3,4])"],
    )
    def test_plain_expressions_are_not_programs(self, src):
        assert not looks_like_program(src)


class TestControlFlow:
    def test_for_loop_with_if_and_print(self):
        """oefpython.fr/liste_portee1 : une ligne par `print`, branche `if`
        seule évaluée."""
        src = "i = 3 ; l = [4,-2,7,1] ; for (j = 1, 4,if(j != i, print(l[j]),print(-6)));"
        assert _call_pari(src) == "4\n-2\n-6\n1"

    def test_accumulator_loop(self):
        assert _call_pari("n=0; for(i=1,3, n=n+i^2); print(n)") == "14"

    def test_loop_variable_is_restored_after_loop(self):
        assert _call_pari("i=42; for(i=1,3, i); print(i)") == "42"

    def test_while_loop(self):
        assert _call_pari("n=1; while(n<10, n=n*2); print(n)") == "16"

    def test_if_as_final_expression_without_semicolon(self):
        """oefline.it/sys3 : sans `print`, GP affiche la dernière valeur."""
        src = "x=10;y=100;A=x+y;B=110;if( abs(A - B) < 10^(-15),1,0)"
        assert _call_pari(src) == "1"

    def test_trailing_semicolon_prints_nothing(self):
        """`l=vector(n);for(…);` ne produit rien sur stdout — surtout pas sa
        propre source."""
        assert _call_pari("l=vector(3); for(x=1,3,l[x]=x);") == ""

    def test_runaway_loop_is_refused(self):
        with pytest.raises(PariProgramError):
            run_pari_program("n=0; while(1, n=n+1); print(n)", {})


class TestVectorsAndMatrices:
    def test_vector_indexing_is_one_based(self):
        assert _call_pari("l=[7,8,9]; print(l[1])") == "7"

    def test_indexed_assignment(self):
        assert _call_pari("l=[1,2,3]; l[2]=9; print(l)") == "1, 9, 3"

    def test_out_of_range_index_falls_back_instead_of_raising(self):
        """Hors périmètre → l'appelant récupère la source, jamais une exception."""
        src = "l=[1,2]; print(l[5])"
        assert _call_pari(src) == src

    def test_matrix_indexing(self):
        assert _call_pari("A=[1,2;3,4]; print(A[2,1])") == "3"

    def test_scalar_product_via_transpose(self):
        """slib/stat/variance : `[data]*[weight]~`."""
        assert _call_pari("print(([2,-7,6]*[1,1,4]~)/6)") == "19/6"

    def test_elementwise_addition(self):
        assert _call_pari("v=[1,2]+[10,20]; print(v)") == "11, 22"

    def test_vector_builtin_returns_one_based_vector(self):
        assert _call_pari("l=vector(3); for(x=1,3,l[x]=x^2); print(l)") == "1, 4, 9"


class TestReductions:
    def test_sum_with_bound_variable(self):
        assert _call_pari("print(sum(t=1,4,t^2))") == "30"

    def test_sum_over_indexed_vectors(self):
        """slib/stat/covariance."""
        src = "print(sum(t=1,3,([1,2,3][t]-2)*([4,5,6][t]-5)));"
        assert _call_pari(src) == "2"

    def test_prod(self):
        assert _call_pari("print(prod(t=1,4,t))") == "24"


class TestPrint:
    def test_string_juxtaposition_concatenates(self):
        """oefbin.nl/binary : `print(n","nbin)`."""
        assert _call_pari('n=14; nbin=222; print(n","nbin)') == "14,222"

    def test_multiple_arguments_are_concatenated(self):
        assert _call_pari('a=1; b=2; print(a,"-",b)') == "1-2"

    def test_print1_stays_on_one_line(self):
        assert _call_pari("for(i=1,3, print1(i)); print()") == "123"


class TestSession:
    def test_variables_persist_across_calls(self):
        """WIMS pilote un unique `gp` : oefforpython.fr définit la liste dans un
        `!exec pari` et l'affiche dans le suivant."""
        session: dict = {}
        _call_pari("l=vector(10); for(x=1,10,l[x]=0+1*(x-1));", session=session)
        assert _call_pari("print(l);", session=session) == "0, 1, 2, 3, 4, 5, 6, 7, 8, 9"

    def test_session_is_not_shared_without_one(self):
        """Sans session, rien ne survit d'un appel à l'autre : `zz` retombe sur
        le symbole libre de l'évaluation d'expression, pas sur 5."""
        _call_pari("zz=5;")
        assert _call_pari("print(zz)") == "zz"


class TestFallback:
    """Le contrat : hors périmètre, `_call_pari` garde son comportement d'avant."""

    def test_plain_expression_unchanged(self):
        assert _call_pari("gcd(12,18)") == "6"

    def test_polynomial_expression_unchanged(self):
        assert _call_pari("polcoeff(x^2+3*x+2,1)") == "3"

    def test_unsupported_construct_returns_source(self):
        src = "f(x)=x^2; print(f(3))"
        assert _call_pari(src) == src


class TestWimsOutputFilter:
    """WIMS post-traite chaque ligne de `gp` (`wims/src/Interfaces/pari.c`) :
    les crochets englobants sautent, pour que la sortie soit une liste WIMS."""

    def test_outer_brackets_are_stripped(self):
        assert _call_pari("v=[1,2,3]; print(v)") == "1, 2, 3"

    def test_nested_brackets_are_kept(self):
        assert _call_pari("m=[1,2;3,4]; print(m)") == "1, 2; 3, 4"

    def test_scalar_output_is_untouched(self):
        assert _call_pari("n=5; print(n)") == "5"


class TestConcat:
    """`concat` construit un **vecteur** ; le repli textuel ne sert que si un
    argument est déjà une chaîne. Tous les usages du corpus accumulent des
    listes (`xl=concat(xl,xi)` des balayages de oefalgopython.fr)."""

    def test_concat_of_scalars_builds_a_vector(self):
        assert _call_pari("v=concat(5,1); print(v)") == "5, 1"

    def test_concat_of_vectors_flattens_one_level(self):
        assert _call_pari("v=concat([1,2],[3,4]); print(v)") == "1, 2, 3, 4"

    def test_accumulation_in_a_loop(self):
        assert _call_pari("xl=[]; for(i=1,3, xl=concat(xl,i*10)); print(xl)") == "10, 20, 30"

    def test_boolean_constants(self):
        assert _call_pari("b=true; print(concat(3,b))") == "3, 1"

    def test_string_argument_still_concatenates_textually(self):
        assert _call_pari('s=concat("a","b"); print(s)') == "ab"


class TestVarianceBranch:
    def test_weighted_variance_block(self):
        """slib/stat/variance, branche pondérée (bloc `{…}` multi-lignes)."""
        src = (
            "{ slib_mean=([2,-7,6]*[1,1,4]~)/6;"
            " slib_dev=sum(x=1,3,[1,1,4][x]*[2,-7,6][x]^2)-6*(slib_mean)^2;"
            " print([1.*slib_dev/6,1.*slib_dev/(6-1)])}"
        )
        out = _call_pari(src)
        assert out.startswith("22.80")
        assert "27.36" in out
