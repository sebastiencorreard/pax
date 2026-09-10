"""Les réglages qu'une feuille pose sur un exercice : `qcmlevel` et `confparm`.

Chez WIMS l'enseignant les choisit en posant l'exercice sur une feuille ; PAX
les verse dans le ctx du moteur (`load_and_render(reglages=…)`). Ces tests
lisent le corpus sur disque, sans base.
"""

import os

import pytest

from core.oef.def_engine import confparm_du_module, load_and_render, table_severite
from core.oef.render_cache import cache_key

RESSOURCES = os.path.abspath(
    os.path.join(os.path.dirname(__file__), "../../../../ressources")
)
# `!for val11 =1 to $val2` où `val2=$confparm1` : le paramètre fixe le nombre
# de questions, et le module le règle à 1 (`!default confparm1=1`).
DECALAGE_DEF = os.path.join(RESSOURCES, "H3/algebra/oefpuis.nl/def/decalage.def")
COSINUS = os.path.join(RESSOURCES, "H3/geometry/oefcosinus.fr/def")
NUMERATION = os.path.join(RESSOURCES, "H4/number/numeration.fr/def")
PENNEY = os.path.join(RESSOURCES, "H4/probability/oefpenney.it/def")
TRIGO2 = os.path.join(RESSOURCES, "H3/geometry/oeftrigo2.fr/def")


def _un_def(dossier: str) -> str:
    if not os.path.isdir(dossier):
        pytest.skip(f"{dossier} absent du corpus")
    return os.path.join(dossier, sorted(os.listdir(dossier))[0])


# ── Moteur ─────────────────────────────────────────────────────────────────


@pytest.mark.skipif(not os.path.isfile(DECALAGE_DEF), reason="corpus absent")
class TestMoteur:
    def test_sans_reglage_le_niveau_est_3(self):
        r = load_and_render(DECALAGE_DEF, seed=5)
        assert r.severite["qcmlevel"] == 3
        assert r.severite["givesol"] == 1

    def test_le_niveau_commande_les_dix_reglages(self):
        # `givesol = 1,1,1,0,0,0,0,0,0` : le corrigé se ferme au niveau 4.
        r = load_and_render(DECALAGE_DEF, seed=5, reglages={"qcmlevel": "7"})
        table = table_severite()["reglages"]
        for cle, paliers in table.items():
            assert r.severite[cle] == paliers[6], cle

    def test_un_confparm_de_feuille_ecrase_celui_du_module(self):
        une = load_and_render(DECALAGE_DEF, seed=5)
        trois = load_and_render(DECALAGE_DEF, seed=5, reglages={"confparm1": "3"})
        assert len(trois.answers) == 3 * len(une.answers)


# ── Clé du cache ───────────────────────────────────────────────────────────


class TestCleDuCache:
    def test_deux_niveaux_ne_partagent_pas_leur_rendu(self):
        a = cache_key("x.def", 1, None, None, {"qcmlevel": "3"})
        b = cache_key("x.def", 1, None, None, {"qcmlevel": "7"})
        assert a != b

    def test_sans_reglage_la_cle_ne_change_pas(self):
        # Les rendus déjà en cache restent valables pour qui ne règle rien.
        assert cache_key("x.def", 1, 2, {"r1": "3"}) == "pax:render:x.def:1:2:r1=3"
        assert cache_key("x.def", 1, 2, {"r1": "3"}, {}) == cache_key("x.def", 1, 2, {"r1": "3"})

    def test_l_ordre_des_reglages_est_indifferent(self):
        a = cache_key("x.def", 1, None, None, {"qcmlevel": "5", "confparm1": "2"})
        b = cache_key("x.def", 1, None, None, {"confparm1": "2", "qcmlevel": "5"})
        assert a == b


# ── Ce que le module laisse régler ──────────────────────────────────────────


class TestConfparmDuModule:
    def test_menu_avec_libelle_et_invites(self):
        confparm = confparm_du_module(_un_def(COSINUS))
        assert confparm == [{
            "nom": "confparm1",
            "libelle": "Affichage d'une figure",
            "defaut": "1",
            "choix": [
                {"valeur": "0", "libelle": "Non"},
                {"valeur": "1", "libelle": "Oui"},
            ],
        }]

    def test_un_confparm_sans_formulaire_n_est_pas_propose(self):
        # `oefcosinus.fr` pose `confparm2=1` sans le laisser changer.
        noms = [c["nom"] for c in confparm_du_module(_un_def(COSINUS))]
        assert "confparm2" not in noms

    def test_saisie_libre(self):
        par_nom = {c["nom"]: c for c in confparm_du_module(_un_def(NUMERATION))}
        assert par_nom["confparm1"]["choix"] == []
        assert par_nom["confparm1"]["defaut"] == "2,3,5,12"
        assert par_nom["confparm1"]["libelle"] == "Choix de la base p"
        assert len(par_nom["confparm3"]["choix"]) == 5

    def test_oui_non_dans_la_langue_du_module(self):
        par_nom = {c["nom"]: c for c in confparm_du_module(_un_def(TRIGO2))}
        assert [c["libelle"] for c in par_nom["confparm1"]["choix"]] == ["Non", "Oui"]

    def test_une_liste_calculee_devient_saisie_libre(self):
        # `!formselect confparm1 list $menu_list` : la liste n'existe que dans
        # une session WIMS.
        par_nom = {c["nom"]: c for c in confparm_du_module(_un_def(PENNEY))}
        assert par_nom["confparm1"]["choix"] == []
        assert all("$" not in c["libelle"] for c in par_nom["confparm2"]["choix"])

    def test_module_sans_introhook(self):
        assert confparm_du_module(None) == []
        assert confparm_du_module("/nulle/part/def/x.def") == []
