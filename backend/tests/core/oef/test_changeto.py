"""`!changeto` et la slib introuvable — ce qui laissait `UNKNOWN_CMD:changeto`
dans l'énoncé.

`exec_changeto` (`src/exec.c`) arrête le fichier courant et lit la cible à sa
place. Les `var.proc` de module finissent par `!changeto oef/var.proc`.
"""
from core.oef.def_engine import DefEngine


def _module(tmp_path, slibs: dict[str, str]) -> DefEngine:
    """Un module factice : `def/essai.def` et ses slibs locales."""
    (tmp_path / "def").mkdir()
    def_path = tmp_path / "def" / "essai.def"
    def_path.write_text("")
    for nom, texte in slibs.items():
        chemin = tmp_path / "slib" / nom
        chemin.parent.mkdir(parents=True, exist_ok=True)
        chemin.write_text(texte)
    return DefEngine(seed=1, def_path=str(def_path))


def test_changeto_arrete_le_script_courant(tmp_path):
    e = _module(tmp_path, {"essai": "a=1\n!changeto oef/var.proc\na=2\n"})
    e._cmd_readproc("slib/essai")
    assert e.ctx["a"] == "1"
    assert "UNKNOWN_CMD" not in str(e.ctx.get("slib_out", ""))


def test_changeto_lit_la_cible(tmp_path):
    e = _module(tmp_path, {
        "depart": "!changeto slib/arrivee\nb=jamais\n",
        "arrivee": "b=lu\n",
    })
    e._cmd_readproc("slib/depart")
    assert e.ctx["b"] == "lu"


def test_changeto_substitue_la_cible(tmp_path):
    e = _module(tmp_path, {
        "depart": "cible=arrivee\n!changeto slib/$cible\n",
        "arrivee": "c=lu\n",
    })
    e._cmd_readproc("slib/depart")
    assert e.ctx["c"] == "lu"


def test_slib_introuvable_vide_slib_out(tmp_path):
    e = _module(tmp_path, {})
    e.ctx["slib_out"] = "reste du script précédent"
    e._cmd_readproc("slib/nexistepas")
    assert e.ctx["slib_out"] == ""
