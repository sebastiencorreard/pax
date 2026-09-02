"""La dette de types de réponse, figée.

`check_answer` se termine sur un `case _` à deux branches (`checkers.py`) :

* un nom que WIMS ne connaît pas est **un nom inventé par l'auteur**, et WIMS
  le ramène à `default` — comparaison mathématique. Rien à porter ;
* un nom que WIMS connaît, ou qu'un module définit, mais que PAX n'a pas encore
  porté est **une dette** : on retombe sur `check_text`, ce qui refuse toute
  réponse écrite autrement que la référence. C'est tracé par
  `[ANSWER-FALLBACK]`, dans un journal que personne ne lit.

Le repli est silencieux par construction : l'exercice se rend, le formulaire
s'affiche, l'élève répond, et seule la note trahit le problème. D'où ce
relevé : porter un type doit le faire *sortir* de la liste, et rien ne doit y
entrer sans qu'on le décide.

La mesure ne rend aucun exercice — elle interroge le dispatch directement, à
travers le journal qu'il alimente — et tient en quelques secondes.
"""
import collections
import glob
import os
import re

import pytest

from config import settings
from core.answer import checkers as C
from core.oef.def_engine import _normalize_reply_type


# Les types que le dispatch abandonne à `check_text`. Régénérer après avoir
# porté un checker :
#
#   docker compose exec -T backend python3 -c "
#   from core.answer import checkers as C
#   d=[t for t in sorted(C._WIMS_KNOWN_TYPES|C._MODULE_ANSTYPES)
#      if (C._logged_unhandled_types.clear() or
#          C.check_answer(t,'1','1',{},'fr') or True) and C._logged_unhandled_types]
#   print(d)"
_DETTE = frozenset({
    "aset", "autoeval", "chembrut", "chemclick", "chemdraw", "chemformula",
    "chemformula_analysis", "chessgame", "chset", "clicktile", "clock", "code",
    "complex", "compose", "crossword", "draft", "dragfill", "flashcard",
    "geogebra", "geogebra_translation", "imgcomp", "javacurve", "jmolclick",
    "js2wims1", "keyboard", "matrix", "multidraw", "puzzle", "reaction",
    "reorder", "runcode", "symtext", "textcomp", "time", "wlist",
})

# Le sous-ensemble que le corpus emploie vraiment — le reste de `_DETTE` est
# une dette théorique, sans un seul exercice pour la porter. C'est cette
# liste-ci qui ordonne le travail, et deux de ses entrées n'y figurent que pour
# mémoire, le moteur les interceptant avant le checker :
#
#   dragfill  →  replié sur `clickfill` (`_normalize_reply_type`), voir plus bas
#   draft     →  capté en `options["draft"]` par le moteur, champ non noté
#
# Les autres arrivent bien jusqu'à `check_text`. Un balayage du corpus complet
# en comptait 131 sur 9 types avant que `numexp2` (6 exercices) et
# `jsxgraphobjet` (3) ne soient portés.
_DETTE_EMPLOYEE = frozenset({
    "aset", "draft", "dragfill", "geogebra", "jmolclick", "js2wims1",
    "matrix", "reaction", "runcode", "symtext", "wlist",
})

_RT = re.compile(rb"replytype\d*\s*=\s*([A-Za-z_][A-Za-z_0-9]*)")


def _dette_mesuree() -> set[str]:
    """Les types dont le dispatch trace effectivement le repli.

    On lit le journal plutôt que `CheckResult.method` : des checkers portés
    (`case`, `raw`, `nocase`) rendent eux aussi `"text"`, et les confondre
    ferait passer une régression pour un état normal.
    """
    mesuree = set()
    for t in sorted(C._WIMS_KNOWN_TYPES | C._MODULE_ANSTYPES):
        C._logged_unhandled_types.clear()
        C.check_answer(t, "1", "1", {}, "fr")
        if C._logged_unhandled_types:
            mesuree.add(t)
    C._logged_unhandled_types.clear()
    return mesuree


def _usages_corpus() -> collections.Counter:
    """Décompte des `replytype<n>=` sur tous les `.def` du corpus.

    Relevé statique, sur les octets : les `.def` sont en ISO-8859 et le nom
    d'un type est de toute façon ASCII.
    """
    compte: collections.Counter = collections.Counter()
    racine = settings.resources_root.rstrip("/")
    for chemin in glob.glob(f"{racine}/**/*.def", recursive=True):
        with open(chemin, "rb") as f:
            for m in _RT.finditer(f.read()):
                compte[C.normalize_replytype(m.group(1).decode("latin-1"))] += 1
    return compte


def test_la_dette_est_exactement_celle_declaree():
    """Dans les deux sens : rien n'entre sans décision, et porter un checker
    oblige à retirer son type d'ici."""
    mesuree = _dette_mesuree()
    entrees = mesuree - _DETTE
    sorties = _DETTE - mesuree
    assert not entrees, (
        f"types nouvellement abandonnés à check_text : {sorted(entrees)} — "
        "régression, ou type à ajouter sciemment à _DETTE"
    )
    assert not sorties, (
        f"types désormais traités : {sorted(sorties)} — les retirer de _DETTE"
    )


@pytest.mark.skipif(
    not os.path.isdir(settings.resources_root),
    reason="corpus absent (les ressources ne sont pas montées)",
)
def test_le_corpus_n_emploie_de_la_dette_que_ce_qui_est_recense():
    """Un exercice ajouté au corpus peut réveiller une dette dormante ; il faut
    alors décider si le type se porte ou s'il rejoint la liste."""
    employee = {t for t in _usages_corpus() if t in _DETTE}
    entrees = employee - _DETTE_EMPLOYEE
    sorties = _DETTE_EMPLOYEE - employee
    assert not entrees, (
        f"le corpus emploie désormais : {sorted(entrees)} — dette dormante "
        "réveillée, à porter ou à recenser"
    )
    assert not sorties, (
        f"plus employés par le corpus : {sorted(sorties)} — les retirer de "
        "_DETTE_EMPLOYEE"
    )


def test_dragfill_ne_parvient_jamais_au_checker():
    """`dragfill` pèse 1160 déclarations, de loin la première de la liste, et
    pourtant aucun exercice ne s'en plaint : le moteur le replie sur
    `clickfill` avant de construire la réponse. Il ne figure dans `_DETTE` que
    parce que le dispatch, lui, ne connaît pas ce repli — si l'interception
    tombait, 1160 réponses basculeraient d'un coup sur `check_text`."""
    assert _normalize_reply_type("dragfill") == "clickfill"
    assert _normalize_reply_type("clickfill") == "clickfill"
