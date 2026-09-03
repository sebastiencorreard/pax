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
from core.oef.engine import load_and_render


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
    "autoeval", "chembrut", "chemclick", "chemdraw", "chemformula",
    "chemformula_analysis", "chessgame", "chset", "clicktile", "clock", "code",
    "complex", "compose", "crossword", "draft", "dragfill", "flashcard",
    "geogebra", "geogebra_translation", "imgcomp", "javacurve", "jmolclick",
    "js2wims1", "keyboard", "matrix", "multidraw", "puzzle", "reaction",
    "reorder", "runcode", "symtext", "textcomp", "time",
})

# Le sous-ensemble que le corpus emploie vraiment — le reste de `_DETTE` est
# une dette théorique, sans un seul exercice pour la porter.
#
# Ce relevé-ci est **statique** : il compte des `replytype<n>=` dans les
# `.def`, et à ce titre il sur-rapporte. Ce qu'un fichier déclare n'est pas ce
# qui parvient au checker — le moteur replie, masque ou écarte cinq de ces
# onze types avant le dispatch. La partition qui suit dit lesquels, et c'est
# `_DETTE_ATTEINTE` qui ordonne le travail.
_DETTE_EMPLOYEE = frozenset({
    "draft", "dragfill", "geogebra", "jmolclick", "js2wims1",
    "matrix", "reaction", "runcode", "symtext",
})

# Employés par le corpus, jamais parvenus à `check_answer` : le moteur les
# intercepte en amont, chacun à sa manière. Ils restent dans `_DETTE` parce que
# le dispatch, lui, ignore ces détours — si l'interception tombait, les
# réponses basculeraient d'un coup sur `check_text`.
#
#   dragfill  →  replié sur `clickfill` (`_normalize_reply_type`), voir plus bas
#   draft     →  capté en `options["draft"]`, champ brouillon non noté
#   matrix    →  ses 7 champs portent tous `?analyze`, qui masque le type en
#                `analyze` ; la notation passe par `:test` (et pour 7 d'entre
#                eux, plus du tout : rien ne les éprouve, ils sont `ungraded`)
#   symtext   →  idem, ses 2 champs sont `?analyze`
#   reaction  →  `?analyze` *et* `replyweight=0` : le type de module
#                d'oefstatistiques ne corrige rien, il dresse un tableau HTML
#                des temps relevés et conclut `diareply=good` sans condition
_DETTE_INTERCEPTEE = frozenset({
    "draft", "dragfill", "matrix", "reaction", "symtext",
})

# Ce qui reste vraiment à porter : les types qui atteignent `check_text` sur au
# moins un champ **pesant** (`replyweight` non nul) du corpus. Mesuré au rendu,
# non déclaré — cf. `test_ce_qui_atteint_vraiment_le_checker`.
#
#   runcode     98 champs, 98 exercices — exécution de code élève, le gros
#               morceau, et `js2wims1` en dépend (son `.input` lit les
#               variables d'une exécution Python)
#   geogebra     7 champs,  7 exercices — l'affichage est porté, reste la
#               correction (`anstype/geogebra`, 1128 lignes de scénarios)
#   jmolclick    1 champ,   1 exercice — l'affichage Jmol est porté, le clic
#               sur un atome manque
#   js2wims1     1 champ,   1 exercice — les 13 autres pèsent 0
_DETTE_ATTEINTE = frozenset({
    "geogebra", "jmolclick", "js2wims1", "runcode",
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


@pytest.mark.slow
@pytest.mark.skipif(
    not os.path.isdir(settings.resources_root),
    reason="corpus absent (les ressources ne sont pas montées)",
)
def test_ce_qui_atteint_vraiment_le_checker():
    """La dette telle qu'un élève la subit, mesurée au rendu.

    Les deux relevés qui précèdent lisent des fichiers ; celui-ci rend les
    exercices. L'écart n'est pas anecdotique — cinq des onze types déclarés
    n'arrivent jamais jusqu'à `check_answer` —, et il porte à conséquence : ce
    test dit sur quoi travailler, et un relevé statique enverrait porter un
    correcteur `matrix` dont pas un champ ne se sert.

    Deux filtres, et ils comptent autant que la mesure. `ungraded` écarte les
    brouillons, `weight` les champs de poids nul : leur note n'entre dans
    aucun total, si bien qu'un repli sur `check_text` n'y coûte rien. Les
    treize `js2wims1` d'oefechpython sont dans ce cas — ce qui leur manque est
    un *affichage*, pas un correcteur.

    Coûte une minute : il rend les 276 exercices qui déclarent un type de la
    dette, d'où le marqueur `slow`.
    """
    racine = settings.resources_root.rstrip("/")
    a_rendre = set()
    for chemin in glob.glob(f"{racine}/**/*.def", recursive=True):
        with open(chemin, "rb") as f:
            octets = f.read()
        if any(
            C.normalize_replytype(m.group(1).decode("latin-1")) in _DETTE
            for m in _RT.finditer(octets)
        ):
            oef = chemin.replace("/def/", "/src/")[:-4] + ".oef"
            if os.path.exists(oef):
                a_rendre.add(oef)

    atteints: set[str] = set()
    for chemin in sorted(a_rendre):
        try:
            rendu = load_and_render(
                "/ressources/" + os.path.relpath(chemin, racine), seed=42
            )
        except Exception:  # noqa: BLE001 — un rendu cassé relève d'un autre test
            continue
        for ans in rendu.answers:
            if ans.options.get("ungraded") or not ans.weight:
                continue
            type_effectif = C.normalize_replytype(ans.answer_type)
            if type_effectif in _DETTE:
                atteints.add(type_effectif)

    entrees = atteints - _DETTE_ATTEINTE
    sorties = _DETTE_ATTEINTE - atteints
    assert not entrees, (
        f"atteignent désormais check_text sur un champ noté : {sorted(entrees)} "
        "— régression du repli qui les interceptait, ou dette à recenser"
    )
    assert not sorties, (
        f"n'atteignent plus le checker : {sorted(sorties)} — checker porté (les "
        "retirer aussi de _DETTE), ou repli en amont (les passer à "
        "_DETTE_INTERCEPTEE)"
    )


def test_la_dette_employee_se_partitionne():
    """Tout type employé est soit intercepté, soit subi. Sans recouvrement :
    un type ne peut pas à la fois ne jamais parvenir au checker et y parvenir.
    """
    assert _DETTE_INTERCEPTEE | _DETTE_ATTEINTE == _DETTE_EMPLOYEE
    assert not (_DETTE_INTERCEPTEE & _DETTE_ATTEINTE)


def test_dragfill_ne_parvient_jamais_au_checker():
    """`dragfill` pèse 1160 déclarations, de loin la première de la liste, et
    pourtant aucun exercice ne s'en plaint : le moteur le replie sur
    `clickfill` avant de construire la réponse. Il ne figure dans `_DETTE` que
    parce que le dispatch, lui, ne connaît pas ce repli — si l'interception
    tombait, 1160 réponses basculeraient d'un coup sur `check_text`."""
    assert _normalize_reply_type("dragfill") == "clickfill"
    assert _normalize_reply_type("clickfill") == "clickfill"
