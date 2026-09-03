"""`geogebra` — la figure que l'élève construit ou déplace.

Le type ne compare pas une valeur : la réponse est un **état de figure**, que
le navigateur compose (`composables/useGeogebra.ts`, port de
`geogebra2wims()`), et l'attendu une liste de **conditions**. La bonne réponse
est donc un ensemble de figures, pas une figure — « CB colinéaire à FH » se
satisfait d'une infinité de placements.

Dix-sept exercices : les sept d'`oefvectdirnorm` (vecteurs du plan, conditions
numériques) et les dix d'`OEFevalwimsgespa1` (un point de l'espace à placer,
conditions numériques et formelles), ces derniers n'exposant leur champ que
sous `confparm1=2`.
"""
from core.answer.checkers import check_answer, check_geogebra


def etat(bx: float, by: float) -> str:
    """L'état que l'applet renvoie pour `01colineaire` (graine 42), B en (bx,by).

    F=(0,0) et H=(-3,-2) sont fixes, C=(-5,-3) aussi ; B est le point mobile.
    Les vecteurs suivent : u = FH, v = CB.
    """
    ux, uy = -3, -2
    vx, vy = bx + 5, by + 3
    return (
        f"F=point,0,0&&H=point,-3,-2&&C=point,-5,-3&&B=point,{bx},{by}"
        f"&&u=vector,{ux},{uy}&&v=vector,{vx},{vy};"
        f"F=(0, 0)&&H=(-3, -2)&&C=(-5, -3)&&B=({bx}, {by})"
        f"&&u=Vector[F, H]&&v=Vector[C, B]"
    )


class TestDispatch:
    def test_geogebra_ne_retombe_plus_sur_check_text(self):
        res = check_answer("geogebra", etat(-8, -5), "n,x_u-x_v==0,hiden", {}, "fr")
        assert res.method == "geogebra"


class TestConditionsNumeriques:
    """`04egaux` : les deux vecteurs sont égaux, coordonnée par coordonnée."""

    EGAUX = "n,x_u - x_v ==0 & y_u - y_v ==0 ,hiden;"

    def test_la_figure_attendue_vaut_un(self):
        assert check_geogebra(etat(-8, -5), self.EGAUX).correct

    def test_un_cran_de_travers_ne_passe_pas(self):
        assert not check_geogebra(etat(-4, -3), self.EGAUX).correct

    def test_le_point_confondu_ne_passe_pas(self):
        assert not check_geogebra(etat(-5, -3), self.EGAUX).correct


class TestArithmetiqueExacte:
    """Les conditions sont pleines d'égalités à zéro : le bruit binaire d'un
    flottant y déciderait à la place de la géométrie. WIMS évalue par Pari, en
    exact ; `Fraction` tient la même promesse."""

    def test_des_decimales_qui_se_compensent(self):
        # 0.1 + 0.2 - 0.3 vaut 5.5e-17 en binaire, et zéro en exact.
        assert check_geogebra(
            "A=point,0.1,0.2&&B=point,0.3,0", "n,x_A+y_A-x_B==0,hiden"
        ).correct

    def test_la_puissance_reste_exacte(self):
        assert check_geogebra(
            "u=vector,0.5,0&&v=vector,0.25,0", "n,(x_u)^2-x_v==0,hiden"
        ).correct


class TestOperateurs:
    """La condition est écrite en syntaxe Pari, que WIMS lui passe telle
    quelle : `&&`/`&` pour l'et, `||` pour le ou, `^` pour la puissance."""

    def test_le_ou_suffit_d_un_membre(self):
        assert check_geogebra(etat(-4, -3), "n,x_u==0||y_u==-2,hiden").correct

    def test_l_et_exige_les_deux(self):
        assert not check_geogebra(etat(-4, -3), "n,x_u==0&y_u==-2,hiden").correct

    def test_l_et_lie_plus_fort_que_le_ou(self):
        """Priorité du C, celle de Pari — `A || B & C` se lit `A || (B & C)`.
        `01colineaire` en dépend, à son insu : sa condition
        `(x_B-x_C)!=0||(y_B-y_C)!=0 & det==0` accepte toute figure où B et C
        diffèrent en abscisse, le déterminant ne pesant que sur la branche
        droite. Défaut de l'exercice, que WIMS partage ; le porter fidèlement
        veut dire le reproduire."""
        colineaire = "n,(x_B-x_C)!=0||(y_B-y_C)!=0 & (x_u)*(y_v)-(y_u)*(x_v)==0 ,hiden;"
        assert check_geogebra(etat(-4, -3), colineaire).correct
        assert not check_geogebra(etat(-5, -3), colineaire).correct

    def test_abs_est_disponible(self):
        assert check_geogebra("A=point,3.1,0", "n,abs(x_A-(3))<0.2,hiden").correct
        assert not check_geogebra("A=point,3.5,0", "n,abs(x_A-(3))<0.2,hiden").correct


class TestConditionsFormelles:
    """`f,<nom>=<Commande>` regarde la **seconde** moitié de la réponse, celle
    des définitions : un point posé à la main et un point construit par
    intersection ont les mêmes coordonnées et des définitions différentes."""

    REPONSE = "U=point,1,2;U=Intersect[a,b]"

    def test_la_commande_attendue_passe(self):
        assert check_geogebra(self.REPONSE, "f,U=Intersect,construit").correct

    def test_une_autre_commande_ne_passe_pas(self):
        assert not check_geogebra(self.REPONSE, "f,U=Point,construit").correct

    def test_un_point_libre_repond_par_son_type(self):
        assert check_geogebra("U=point,1,2;U=point", "f,U=Point,construit").correct

    def test_un_objet_absent_ne_passe_pas(self):
        assert not check_geogebra(self.REPONSE, "f,V=Intersect,construit").correct


class TestNote:
    """`score = (w₁·formelles + w₂·noms + w₃·numériques) / Σw`, chaque terme
    étant la fraction des conditions de son genre qui passent et son poids
    ramené à zéro quand l'exercice n'en pose aucune."""

    DEUX = "n,x_u==-3,un;n,y_u==0,deux"

    def test_une_condition_sur_deux_vaut_un_demi(self):
        res = check_geogebra(etat(-8, -5), self.DEUX)
        assert res.score == 0.5
        assert not res.correct

    def test_bon_seulement_si_toutes_passent(self):
        res = check_geogebra(etat(-8, -5), "n,x_u==-3,un;n,y_u==-2,deux")
        assert res.score == 1.0
        assert res.correct

    def test_les_deux_genres_se_ponderent(self):
        """`weight` vaut `1,0.2,1` : les formelles et les numériques pèsent
        pareil, et le terme des noms s'annule faute de condition de ce genre."""
        res = check_geogebra(
            "U=point,1,2;U=Point", "f,U=Point,construit;n,x_U==99,placé"
        )
        assert res.score == 0.5

    def test_un_poids_explicite_est_suivi(self):
        res = check_geogebra(
            "U=point,1,2;U=Point",
            "f,U=Point,construit;n,x_U==99,placé",
            {"option": "weight=3,0.2,1"},
        )
        assert res.score == 0.75


class TestMessages:
    """Le message d'une condition manquée remonte en diagnostic ; `hiden` est
    précisément celui que l'auteur ne veut pas montrer."""

    def test_le_message_d_une_condition_manquee_remonte(self):
        res = check_geogebra(etat(-4, -3), "n,x_u==99,L'abscisse est fausse")
        assert "L'abscisse est fausse" in (res.detail or "")

    def test_hiden_ne_remonte_pas(self):
        assert check_geogebra(etat(-4, -3), "n,x_u==99,hiden").detail is None

    def test_une_condition_reussie_ne_dit_rien(self):
        assert check_geogebra(etat(-8, -5), "n,x_u==-3,message").detail is None


class TestFiguresIncompletes:
    def test_une_figure_vide_est_fausse(self):
        res = check_geogebra("", "n,x_A==0,hiden")
        assert not res.correct
        assert res.score == 0.0

    def test_un_objet_absent_rend_la_condition_fausse(self):
        """Le nom subsiste après substitution : WIMS y voit Pari rendre vide,
        qu'il ramène à 0 — la condition est fausse, non erronée."""
        assert not check_geogebra("A=point,1,2;A=point", "n,x_Z==0,hiden").correct

    def test_sans_condition_il_n_y_a_rien_a_noter(self):
        assert check_geogebra(etat(-8, -5), "").score == 0.0
