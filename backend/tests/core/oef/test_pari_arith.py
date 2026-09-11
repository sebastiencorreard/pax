"""Fonctions arithmétiques de PARI : `bezout`, `lift`, `Mod`.

Employées par `OEFarithmTS` (H6) : `bezout(a,b)` rend le vecteur `[u,v,d]` de
Bézout, et `lift(Mod(a,n))` le représentant de `a` dans `[0, n)`.
"""
from core.oef.def_engine.cas import _call_pari


class TestBezout:
    def test_vecteur_de_bezout(self):
        # -1·491 + 123·4 = 1 = pgcd(491,4)
        assert _call_pari("bezout(491,4)") == "-1,123,1"

    def test_relation_verifiee(self):
        u, v, d = (int(x) for x in _call_pari("bezout(240,46)").split(","))
        assert u * 240 + v * 46 == d
        assert d == 2  # pgcd(240,46)


class TestModLift:
    def test_lift_mod_positif(self):
        assert _call_pari("lift(Mod(7,4))") == "3"

    def test_lift_mod_negatif(self):
        # le représentant est dans [0, n)
        assert _call_pari("lift(Mod(-1,4))") == "3"

    def test_inverse_modulaire_via_bezout(self):
        # 3 · 491^{-1} mod 4 : OEFarithmTS/bezout4
        assert _call_pari("lift(Mod(3*bezout(491,4)[1],4))") == "1"
