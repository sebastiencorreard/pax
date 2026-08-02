"""`!rename` — URL de service pour un fichier du module ou de `gifs/`.

Dans WIMS (`calc_rename`), la commande pose un lien symbolique dans le
répertoire de session et renvoie une URL `getfile/rename-<aléa>` : un moyen de
servir un fichier sans exposer son chemin. PAX servant `ressources/` par
`/api/static`, la traduction suffit.

Non reconnue, la commande ressortait en `UNKNOWN_CMD:rename` **dans l'attribut
`src`** : les 14 exercices d'`oefcountries` affichaient des images cassées à la
place de leurs drapeaux.
"""

import os

from core.oef.def_engine import DefEngine, _RESSOURCES_ROOT, load_and_render


def engine() -> DefEngine:
    return DefEngine(
        seed=1, def_path="/ressources/H3/geography/oefcountries.en/def/flagall.def"
    )


class TestRename:
    def test_shared_gifs_map_to_the_vendored_mirror(self):
        # `gifs/` est l'arbre partagé de WIMS, vendoré en `ressources/wims-gifs/`.
        assert engine()._cmd_rename("gifs/flags/fr-lgflag.gif") == (
            "/api/static/wims-gifs/flags/fr-lgflag.gif"
        )

    def test_missing_file_is_empty_not_a_broken_url(self):
        assert engine()._cmd_rename("gifs/flags/nexistepas.gif") == ""

    def test_paths_cannot_escape_the_served_root(self):
        # `calc_rename` refuse les `..` ; l'argument vient du `.def`.
        assert engine()._cmd_rename("../../etc/passwd") == ""
        assert engine()._cmd_rename("gifs/../../etc/passwd") == ""

    def test_no_argument(self):
        assert engine()._cmd_rename("") == ""


class TestCorpus:
    def test_flag_urls_are_served(self):
        r = load_and_render(
            "/ressources/H3/geography/oefcountries.en/def/flagall.def", seed=42
        )
        cfg = [s for s in r.statement_segments if s["type"] == "correspond"][0]["config"]
        assert cfg["lefts"], "aucune colonne d'images"
        for left in cfg["lefts"]:
            assert "UNKNOWN_CMD" not in left
            assert "/api/static/wims-gifs/flags/" in left
            # Le fichier doit exister : c'est ce qui distingue une URL correcte
            # d'une image cassée.
            rel = left.split("/api/static/")[1].split(">")[0].strip('"\'')
            assert os.path.isfile(os.path.join(_RESSOURCES_ROOT, rel)), rel
