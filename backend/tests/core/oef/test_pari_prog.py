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
        assert _call_pari("l=[1,2,3]; l[2]=9; print(l)") == "1,9,3"

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
        assert _call_pari("v=[1,2]+[10,20]; print(v)") == "11,22"

    def test_vector_builtin_returns_one_based_vector(self):
        assert _call_pari("l=vector(3); for(x=1,3,l[x]=x^2); print(l)") == "1,4,9"


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
        assert _call_pari("print(l);", session=session) == "0,1,2,3,4,5,6,7,8,9"

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
        """Une syntaxe que l'interpréteur ne sait pas lire ressort intacte."""
        src = "f(x)=x^^2; print(f(3"
        assert _call_pari(src) == src


class TestUserFunctions:
    """Fonctions définies par le programme, `List` et `vecsort` — ce dont
    `slib/function/tabsignes` a besoin pour trier ses positions de réponses."""

    def test_simple_definition_and_call(self):
        assert _call_pari("f(x)=x^2; print(f(3))") == "9"

    def test_definition_wrapped_in_parentheses(self):
        """`slib/stat/histo` isole ainsi sa fonction d'arrondi avant l'appel."""
        src = "(f(r,n)= l=if(r != 0, 1,1) ; s=r*10 ; s*10^(l-n+1) ); print(f(2,1))"
        assert _call_pari(src) == "200"

    def test_parameters_do_not_leak(self):
        assert _call_pari("x=7; f(x)=x*2; f(3); print(x)") == "7"

    def test_list_insert_and_vec(self):
        assert _call_pari("L=List([]); listinsert(L,5,1); listinsert(L,3,1); print(Vec(L))") == "3,5"

    def test_vecsort(self):
        assert _call_pari("print(vecsort([3,1,2]))") == "1,2,3"

    def test_matsort_sorts_matrix_rows(self):
        """Le `matsort` de tabsignes : lignes triées dans l'ordre lexicographique."""
        src = (
            "(matsort(mat)=A=[mat];L=List([]);for(i=1,3,listinsert(L,mat[i,],i));"
            "V=Vec(L);N=vecsort(V);N);matsort([2,9;1,4;1,2])"
        )
        assert _call_pari(src) == "[1,2],[1,4],[2,9]"


class TestWimsOutputFilter:
    """WIMS post-traite chaque ligne de `gp` (`wims/src/Interfaces/pari.c`) :
    les crochets englobants sautent, pour que la sortie soit une liste WIMS.

    Et il n'y a **aucun espace** à retirer : l'interface ouvre `gp` sur
    `default(output,0)` (l'en-tête `.gprc` du même fichier), le mode brut, qui
    imprime `[1,2]` et non `[1, 2]`. Les attendus de ce fichier suivent ce
    mode : un `, ` y serait une invention de PAX, et il en coûtait une
    normalisation d'espaces chez tous les consommateurs — `itemchr` compris.
    """

    def test_outer_brackets_are_stripped(self):
        assert _call_pari("v=[1,2,3]; print(v)") == "1,2,3"

    def test_nested_brackets_are_kept(self):
        assert _call_pari("m=[1,2;3,4]; print(m)") == "1,2;3,4"

    def test_scalar_output_is_untouched(self):
        assert _call_pari("n=5; print(n)") == "5"


class TestConcat:
    """`concat` construit un **vecteur** ; le repli textuel ne sert que si un
    argument est déjà une chaîne. Tous les usages du corpus accumulent des
    listes (`xl=concat(xl,xi)` des balayages de oefalgopython.fr)."""

    def test_concat_of_scalars_builds_a_vector(self):
        assert _call_pari("v=concat(5,1); print(v)") == "5,1"

    def test_concat_of_vectors_flattens_one_level(self):
        assert _call_pari("v=concat([1,2],[3,4]); print(v)") == "1,2,3,4"

    def test_accumulation_in_a_loop(self):
        assert _call_pari("xl=[]; for(i=1,3, xl=concat(xl,i*10)); print(xl)") == "10,20,30"

    def test_boolean_constants(self):
        assert _call_pari("b=true; print(concat(3,b))") == "3,1"

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


class TestHelperValueConversion:
    """Les helpers de `cas` raisonnent sur des listes Python. Sans conversion
    *entrante*, `matsize` ne reconnaissait pas un `PMat` et retombait sur son
    `[1, 1]` par défaut : `slib/function/tabsignes` lisait alors une seule
    position de réponse au lieu de six."""

    def test_matsize_of_a_program_built_matrix(self):
        assert _call_pari("E=[1,2;1,4;1,6];matsize(E)[1]") == "3"

    def test_matsize_columns(self):
        assert _call_pari("E=[1,2;1,4;1,6];matsize(E)[2]") == "2"

    def test_matdet_still_works(self):
        assert _call_pari("M=[1,2;3,4];matdet(M)") == "-2"


class TestBibliothequeGP:
    """Les constructions d'une **bibliothèque** GP, par opposition au programme
    d'une ligne — `gp/spanning_tree.gp`, que `slib/geo2D/polynet` charge pour
    déplier un polyèdre. Aucune n'était couverte : la bibliothèque ne
    définissait pas une seule de ses vingt-trois fonctions.
    """

    def test_fonction_anonyme_affectee(self):
        """`nom = {params -> corps}` — six fonctions de la bibliothèque, dont
        tout le reste dépend, sont écrites ainsi."""
        assert _call_pari("carre={v->v*v}; carre(7)") == "49"
        assert _call_pari("prod2={(a,b)->a*b}; prod2(6,7)") == "42"

    def test_accolade_termine_l_instruction(self):
        """En GP un bloc `{…}` se passe de `;` final : deux définitions qui se
        suivent sans séparateur restent deux instructions."""
        src = "f={v->v+1}\ng(x)={x*2}\ng(f(3))"
        assert _call_pari(src) == "8"

    def test_commentaires(self):
        """`/* … */` et `\\\\ …` — une bibliothèque se documente, et le
        découpage sur `;` collait le commentaire à l'instruction suivante."""
        assert _call_pari("/* somme */ a=2; /* et */ b=3; a+b") == "5"
        assert _call_pari("a=2 \\\\ un commentaire\n; a*3") == "6"

    def test_cardinal(self):
        """`#v` — le nombre de composantes, opérateur unaire sans équivalent
        Python. `#f2[#f]` mesure bien `f2[#f]`, non `f2`."""
        assert _call_pari("v=[4,5,6]; #v") == "3"
        assert _call_pari("m=[[1,2],[3,4,5]]; #m[2]") == "3"

    def test_my_avec_initialisation(self):
        assert _call_pari("f(n)={my(a=n*2, b); b=a+1; b}; f(5)") == "11"

    def test_my_ne_fuit_pas_hors_de_l_appel(self):
        """Le défaut qui a coûté le plus cher : le `my(v=…)` de
        `deplacement_poly` écrasait le paramètre `v` d'`etale`, et l'arbre
        couvrant devenait un vecteur unitaire — sans que rien ne le signale."""
        src = "interne()={my(v=99); v}; externe(v)={interne(); v}; externe(7)"
        assert _call_pari(src) == "7"

    def test_until(self):
        """`until(cond, corps)` exécute le corps **avant** le premier test."""
        assert _call_pari("k=0; until(k>=3, k=k+1); k") == "3"
        assert _call_pari("k=9; until(1, k=k+1); k") == "10"

    def test_affectation_composee(self):
        assert _call_pari("k=5; k+=3; k") == "8"
        assert _call_pari("k=5; k-=3; k") == "2"
        assert _call_pari("v=[1,2]; v[2]*=10; v[2]") == "20"

    def test_affectation_en_chaine(self):
        assert _call_pari("v=[0,0]; v[1]=r=7; concat([v[1]],[r])") == "7,7"

    def test_affectation_multiple(self):
        assert _call_pari("f()={[3,4]}; [a,b]=f(); a*10+b") == "34"

    def test_tranche(self):
        """`v[a..b]` et `m[i, a..b]` — la restriction que `etale` applique à
        une ligne de `s2D` pour n'en garder que l'abscisse et l'ordonnée."""
        assert _call_pari("v=[10,20,30,40]; v[2..3]") == "20,30"
        assert _call_pari("m=[1,2,3;4,5,6]; m[2,1..2]") == "4,5"


class TestTypesPari:
    """`vector`, `matrix` et `Mat` construisent des types **distincts**, et
    l'indexation part de 1. Le contraire se voyait mal : `s2D[k,3]` sortait
    des bornes d'une matrice sympy 0-based, et `m[k,l]` lisait la case d'à
    côté sans rien signaler."""

    def test_matrix_est_indexee_a_partir_de_un(self):
        assert _call_pari("m=matrix(2,3); m[2,3]=7; m[2,3]") == "7"

    def test_matrix_avec_corps(self):
        assert _call_pari("m=matrix(2,2,i,j,i*10+j); m[2,1]") == "21"

    def test_vector_de_vecteurs_reste_un_vecteur(self):
        """`vector(n,i,[a,b])` est un vecteur de points, non une matrice :
        `f[i]` doit rendre le point, et non lever « indexation 1D sur une
        matrice »."""
        assert _call_pari("f=vector(2,i,[i,i*i]); f[2][2]") == "4"

    def test_mat_d_un_vecteur_ligne_donne_une_ligne(self):
        """`Mat([1,2,3])` est 1×3 : c'est ce qui fait de
        `Mat(a)*Mat(b)~` un produit scalaire, dont dépend `slib/stat/sum`."""
        assert _call_pari("Mat([1,2,3])*Mat([4,5,6])~") == "32"

    def test_matrix_et_mat_s_additionnent(self):
        """Les deux constructeurs se rencontrent dans une même expression —
        `slib/triplerelation/tabular` en vit."""
        src = "A=Mat([0,0;0,0]); B=matrix(2,2,i,j,(i==1)*(j==2)); A+B"
        assert _call_pari(src) == "0,1;0,0"

    def test_norml2_est_le_carre_de_la_norme(self):
        assert _call_pari("norml2([3,4])") == "25"


class TestAleaPari:
    """`random(n)` vient du générateur du **rendu** : à graine égale, le patron
    d'un polyèdre est reproductible comme le reste de l'exercice."""

    def test_random_suit_la_graine(self):
        from core.oef.def_engine import DefEngine

        a = DefEngine(42)._cmd_exec("pari v=vector(5,i,random(1000)); v")
        b = DefEngine(42)._cmd_exec("pari v=vector(5,i,random(1000)); v")
        c = DefEngine(43)._cmd_exec("pari v=vector(5,i,random(1000)); v")
        assert a == b
        assert a != c
        assert all(0 <= int(x) < 1000 for x in a.split(","))

    def test_random_sans_generateur_sort_du_perimetre(self):
        """Sans générateur, on n'invente pas un tirage que le rendu ne saurait
        reproduire : la construction sort du périmètre."""
        from core.oef.def_engine.cas import _MATH_NS, _PARI_HELPERS

        with pytest.raises(PariProgramError):
            run_pari_program("random(10)", {**_MATH_NS, **_PARI_HELPERS})
