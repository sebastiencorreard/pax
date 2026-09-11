"""Ce qu'un rendu réclame et que le moteur n'a pas — mesuré, non déduit.

Le moteur ne lève rien quand il lui manque quelque chose : une commande
inconnue devient le texte `UNKNOWN_CMD:<cmd>`, une slib introuvable ne produit
rien, un programme `!exec` qu'il ne connaît pas rend une chaîne vide. Cette
sonde rend chaque exercice (graine 42, **sans** le cache Redis, pour que le
moteur s'exécute vraiment) et relève, par niveau :

- les commandes inconnues (texte `UNKNOWN_CMD:` dans le rendu ou le ctx) ;
- les slibs qu'aucun emplacement ne fournit ;
- les programmes `!exec` sans traitement ;
- les chemins lus par `!readproc` ;
- les exceptions.

    docker compose exec -T backend python scripts/sonde_manques.py [niveau…]
"""
import collections
import json
import os
import re
import sys

sys.path.insert(0, os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
os.environ.setdefault("PAX_WIMS_NOW", "20260101.12:00:00")

from core.oef import def_engine as E  # noqa: E402
from core.oef.engine import find_def_path  # noqa: E402
from tests import corpus  # noqa: E402

# Les programmes que `_cmd_exec` sait traiter — à tenir à jour avec son
# expression régulière, sinon la sonde signale comme manquant ce qui est porté
# (`moneyprint`, `float_calc` et `lceb` depuis le 2026-09-10).
_EXEC_GERES = {
    "maxima", "pari", "units-filter", "chemeq", "canvasdraw",
    "moneyprint", "float_calc", "lceb",
}
_UNKNOWN = re.compile(r"UNKNOWN_CMD:(\w+)")

courant: dict = {}
releve = collections.defaultdict(lambda: collections.defaultdict(collections.Counter))
exemples = collections.defaultdict(set)


def _note(cle: str, valeur: str) -> None:
    releve[courant["niveau"]][cle][valeur] += 1
    if len(exemples[(cle, valeur)]) < 3:
        exemples[(cle, valeur)].add(courant["id"])


_run_slib = E.DefEngine._run_slib


def run_slib(self, slib_path, params):
    nom = slib_path.rsplit("/", 1)[-1]
    if nom not in ("editor", "jmolshow") and self.def_path:
        module_dir = os.path.dirname(os.path.dirname(self.def_path))
        scripts = self._find_wims_scripts_dir()
        candidats = [os.path.join(module_dir, slib_path)]
        if slib_path.startswith("slib/"):
            candidats.append(os.path.join(module_dir, "slib", "local", slib_path[5:]))
        if scripts:
            candidats.append(os.path.join(scripts, slib_path))
        if not any(os.path.exists(c) for c in candidats):
            _note("slib_introuvable", slib_path)
    return _run_slib(self, slib_path, params)


_cmd_exec = E.DefEngine._cmd_exec


def cmd_exec(self, args):
    sortie = _cmd_exec(self, args)
    m = re.match(r"\s*(\S+)", args or "")
    if m and m.group(1).lower() not in _EXEC_GERES and not re.match(r"obabel", m.group(1), re.I):
        _note("exec_non_gere", m.group(1).lower())
    return sortie


_cmd_readproc = E.DefEngine._cmd_readproc


def cmd_readproc(self, args):
    m = re.match(r"\s*(\S+)", args or "")
    if m:
        _note("readproc", m.group(1))
    return _cmd_readproc(self, args)


E.DefEngine._run_slib = run_slib
E.DefEngine._cmd_exec = cmd_exec
E.DefEngine._cmd_readproc = cmd_readproc

niveaux = set(sys.argv[1:])
for ex_id, chemin in corpus.exercises():
    niveau = ex_id.split("~", 1)[0]
    if niveaux and niveau not in niveaux:
        continue
    courant.update(niveau=niveau, id=ex_id)
    releve[niveau]["_rendus"]["n"] += 1
    try:
        r = E.load_and_render(find_def_path(chemin), seed=42)
    except Exception as exc:  # noqa: BLE001
        _note("exception", f"{type(exc).__name__}: {str(exc)[:80]}")
        continue
    textes = [r.statement_html, r.hint_html or "", r.solution_html or ""]
    textes += [str(v) for v in (r.ev_ctx or {}).values()]
    textes += [a.expected or "" for a in r.answers]
    for cmd in {m.group(1) for t in textes for m in _UNKNOWN.finditer(t)}:
        _note("commande_inconnue", cmd)

sortie = {
    niveau: {cle: dict(c.most_common()) for cle, c in cles.items()}
    for niveau, cles in releve.items()
}
sortie["_exemples"] = {f"{k}|{v}": sorted(ids) for (k, v), ids in exemples.items()}
print(json.dumps(sortie, ensure_ascii=False, indent=1))
