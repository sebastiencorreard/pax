"""Le modèle de note de WIMS (`core/note_feuille.py`), sur des cas calculés à
la main ligne à ligne sur `wimslogdscore.c` et `score.c`."""
import pytest

from core.note_feuille import (
    EtatExercice,
    ExerciceDeFeuille,
    Pourcentages,
    note_feuille,
    note_globale,
    pourcentages,
    prerequis_atteint,
    resultat,
)


def _jouer(notes, requis=10, tirages=None):
    e = EtatExercice()
    for n in notes:
        e.tirer()
        e.noter(n, requis)
    for _ in range((tirages or len(notes)) - len(notes)):
        e.tirer()
    return e


class TestEtat:
    def test_une_note_parfaite(self):
        r = resultat(_jouer([10]), 10)
        assert (r.points, r.qualite, r.meilleur, r.niveau, r.essais) == (10, 10, 10, 10, 1)

    def test_qualite_amortie(self):
        # user2 = 6·0,85 + 10 = 15,1 ; ts = (1 − 0,85²)/0,15 = 1,85.
        r = resultat(_jouer([6, 10]), 10)
        assert r.points == 10  # 16, plafonné aux points requis
        assert r.qualite == pytest.approx(15.1 / 1.85)
        assert (r.meilleur, r.niveau) == (10, 10)

    def test_tirages_abandonnes(self):
        # 1 essai noté, 10 tirages : 10 ≥ 2·1 + 5, tt = (10 − 4)/2 = 3.
        r = resultat(_jouer([9], tirages=10), 10)
        assert r.qualite == pytest.approx(3.0)
        # 6 tirages < 7 : gratuits.
        assert resultat(_jouer([9], tirages=6), 10).qualite == pytest.approx(9.0)

    def test_n_meilleures(self):
        # Requis 20 : les 2 meilleures. 10 → [0,10] ; 4 → [4,10] ; 8 → [8,10].
        e = _jouer([10, 4, 8], requis=20)
        assert e.high == [8, 10]
        r = resultat(e, 20)
        assert (r.points, r.meilleur, r.niveau) == (20, 18, 8)

    def test_sans_essai(self):
        e = EtatExercice()
        e.tirer()
        assert resultat(e, 10).points == 0


class TestFeuille:
    def test_qualite_faible(self):
        ex = ExerciceDeFeuille(requis=10)
        bon = resultat(_jouer([10]), 10)
        # Qualité 1,5 (< 2) : points divisés par deux ; 0,5 (< 1) : ignoré.
        moyen = resultat(_jouer([1.5]), 10)
        nul = resultat(_jouer([0.5]), 10)
        p = pourcentages([(bon, ex), (moyen, ex), (nul, ex)])
        # cumul = 100·(10 + 0,75)/30 = 35,83 → 36
        assert p.cumul == 36
        assert p.qualite == pytest.approx((10 * 10 + 1.5 * 0.75) / 10.75)

    def test_poids_et_inactif(self):
        r = resultat(_jouer([10]), 10)
        zero = resultat(EtatExercice(), 10)
        p = pourcentages([(r, ExerciceDeFeuille(poids=3)), (zero, ExerciceDeFeuille()),
                          (r, ExerciceDeFeuille(actif=False))])
        assert p.cumul == 75  # 100·30/40

    def test_formules(self):
        p = Pourcentages(cumul=80, qualite=5, meilleur=60, niveau=40)
        # Défaut : formule 2, indicateur 1 (meilleur) — 10 · 0,6 · 0,5^0,3.
        assert note_feuille(p) == round(100 * 10 * 0.6 * 0.5 ** 0.3) / 100
        assert note_feuille(p, formule=1, indicateur=0) == 8.0
        assert note_feuille(p, formule=0, indicateur=2) == 5.0  # max(0,4 ; 0,5)
        assert note_feuille(p, formule=6, indicateur=0) == round(100 * 10 * 0.16) / 100

    def test_note_parfaite(self):
        r = resultat(_jouer([10]), 10)
        assert note_feuille(pourcentages([(r, ExerciceDeFeuille())])) == 10.0

    def test_note_globale(self):
        assert note_globale([(10, 1), (4, 2)]) == 6.0
        assert note_globale([]) == 0.0


def test_prerequis():
    ex = ExerciceDeFeuille(requis=10)
    # 10/10 · √(10/10) · 100 = 100.
    assert prerequis_atteint([(resultat(_jouer([10]), 10), ex)], 80)
    # 5/10 · √(5/10) · 100 ≈ 35,4.
    r = resultat(_jouer([5]), 10)
    assert prerequis_atteint([(r, ex)], 35)
    assert not prerequis_atteint([(r, ex)], 36)
    # Moins de 10 points requis : ignoré.
    assert prerequis_atteint([(resultat(EtatExercice(), 5), ExerciceDeFeuille(requis=5))], 100)


def test_mesure_wims432():
    """Mesure réelle, WIMS 4.32 local, classe 7642386, 2026-10-02 : la suite
    d'évènements du journal `score/paxeleve` (`new` = tirage, nombre = note),
    et ce qu'affiche la page « Notes » de l'enseignant — note 2.87/10, qualité
    3.3, cumul 40 %, réussite 40 %, acquis 0 ; QCM 105 : qualité 3.3, 50 %,
    « 3 + 2 » essais."""
    q102, q105 = EtatExercice(), EtatExercice()
    journal = [(q102, "new"), (q102, 0), (q105, "new"), (q105, 0), (q102, "new"), (q102, 0),
               (q105, "new"), (q105, "new"), (q105, 10), (q102, "new"), (q102, 0),
               (q105, "new"), (q105, 0), (q105, "new"), (q102, "new"), (q102, 0)]
    for etat, ev in journal:
        if ev == "new":
            etat.tirer()
        else:
            etat.noter(ev, 10 if etat is q102 else 20)
    r102, r105 = resultat(q102, 10), resultat(q105, 20)
    assert round(r105.qualite, 1) == 3.3 and r105.points == 10
    assert (r105.essais, q105.tirages - r105.essais) == (3, 2)
    p = pourcentages([(r102, ExerciceDeFeuille(10, 1)), (r105, ExerciceDeFeuille(20, 2))])
    assert (p.cumul, p.meilleur, p.niveau) == (40, 40, 0)
    assert round(p.qualite, 1) == 3.3
    assert note_feuille(p) == 2.87
