"""L'import des métadonnées est idempotent — il corrige les lignes déjà là.

`entrypoint.sh` relance `scripts/import_exercises.py` à chaque démarrage, mais
le script n'était qu'*additif* : il sautait tout `oef_path` déjà en base. Une
correction d'`extract_meta` ne touchait donc jamais les 4277 lignes existantes,
et trois défauts y ont survécu au changement de source (lire le `.def` plutôt
que le `.oef`, cf. de912828) : 800 listes de mots-clés découpées lettre par
lettre, 86 langues fausses (42 exercices catalans étiquetés `fr`, 20 portant la
chaîne littérale `\\lang`) et 55 titres, mojibake `cp1252` ou traduits de
travers.

Ces tests tiennent les deux moitiés du contrat : lire juste (`extract_meta`) et
propager sans rien effacer (`rafraichir`).
"""

import os
import sys

import pytest

sys.path.insert(0, os.path.dirname(os.path.dirname(os.path.abspath(__file__))))

from config import settings  # noqa: E402
from models.exercise import Exercise  # noqa: E402
from scripts.import_exercises import (  # noqa: E402
    extract_meta,
    normalize_lang,
    rafraichir,
)


def _exercise(**champs) -> Exercise:
    """Une ligne détachée : `rafraichir` n'a pas besoin d'une session."""
    defauts = {"id": "x", "oef_path": "/x.oef", "title": None, "lang": "fr",
               "keywords": None}
    return Exercise(**{**defauts, **champs})


class TestNormalizeLang:
    def test_un_nom_complet_devient_un_code_iso(self):
        assert normalize_lang("Dutch") == "nl"

    def test_un_code_inconnu_passe_tel_quel(self):
        """Le catalan n'est pas dans la table : il est déjà un code ISO."""
        assert normalize_lang("ca") == "ca"

    @pytest.mark.parametrize("brut", [None, "", "   "])
    def test_l_absence_de_langue_rend_none(self, brut):
        """`None` dit « le `.def` ne sait pas » — distinct de « il dit fr »."""
        assert normalize_lang(brut) is None


class TestRafraichir:
    def test_une_valeur_lue_ecrase_une_valeur_fausse(self):
        ex = _exercise(title="Compléter", lang="fr", keywords=["p", "b"])
        champs = rafraichir(ex, "Completar", "ca", ["pbsolving"], dry_run=False)
        assert set(champs) == {"title", "lang", "keywords"}
        assert (ex.title, ex.lang, ex.keywords) == ("Completar", "ca", ["pbsolving"])

    def test_un_champ_absent_du_def_ne_efface_rien(self):
        """Sans quoi un `.def` muet viderait le titre qu'un import antérieur
        avait su lire."""
        ex = _exercise(title="Titre acquis", lang="nl", keywords=["algebra"])
        assert rafraichir(ex, None, None, None, dry_run=False) == []
        assert (ex.title, ex.lang, ex.keywords) == ("Titre acquis", "nl", ["algebra"])

    def test_une_ligne_deja_juste_ne_bouge_pas(self):
        ex = _exercise(title="Factoritzar", lang="ca", keywords=["factorisation"])
        assert rafraichir(ex, "Factoritzar", "ca", ["factorisation"], False) == []

    def test_le_dry_run_annonce_sans_ecrire(self):
        ex = _exercise(title="Compléter", lang="fr")
        assert rafraichir(ex, "Completar", "ca", None, dry_run=True) == ["title", "lang"]
        assert (ex.title, ex.lang) == ("Compléter", "fr")


class TestExtractMeta:
    """Trois exercices du corpus, un par défaut corrigé."""

    def _oef(self, relatif: str) -> str:
        chemin = os.path.join(settings.resources_root.rstrip("/"), relatif)
        if not os.path.exists(chemin):
            pytest.skip(f"corpus absent : {relatif}")
        return chemin

    def test_les_mots_cles_arrivent_en_liste(self):
        """La colonne est un tableau : lui passer la chaîne la faisait éclater
        en caractères — `{3,_,s,h,a,p,e,…}` en base."""
        meta = extract_meta(self._oef("H3/algebra/oefqcm3.fr/src/brevet01.oef"))
        assert meta["keywords"] == ["3_shape", "gcd_lcm", "volume", "power"]

    def test_la_langue_se_lit_dans_le_suffixe_du_module(self):
        """`oefvectdirnorm.fr` ne pose pas de `language=` : le répertoire le
        dit. La base y portait la chaîne littérale `\\lang`."""
        meta = extract_meta(
            self._oef("H4/geometry/oefvectdirnorm.fr/src/01colineaire.oef")
        )
        assert meta["language"] == "fr"

    def test_le_titre_est_decode_en_cp1252(self):
        """`œ` est en `0x9c`, absent d'ISO-8859-1 — d'où `st\\x9cchiométriques`."""
        meta = extract_meta(
            self._oef("H4/chemistry/equilibrium.fr/src/coefficients.oef")
        )
        assert meta["title"] == "Coefficients stœchiométriques (1)"

    def test_un_oef_sans_def_ne_rend_rien(self):
        assert extract_meta("/ressources/nexiste/pas.oef") == {}
