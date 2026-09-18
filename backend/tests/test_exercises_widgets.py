"""Tout widget affiché dans un énoncé doit être une réponse déclarée.

Le front compose les options d'un menu à partir de `rendered.answers`, qu'il
indexe par `input_name` (`composables/useExerciseLogic.ts`). Un segment de
widget dont le nom ne s'y trouve pas est donc **inerte** : le menu s'affiche
avec une seule option — son propre libellé —, le champ de saisie n'est relié à
rien, et la correction l'ignore. Pour un exercice à étapes, c'est pire : le
filtre par étape ne garde que les champs vus par l'énoncé, si bien qu'un nom
qui ne correspond pas fait disparaître la réponse entière.

**Aucun autre test ne voit cela.** Les snapshots figent le rendu tel qu'il est,
quitte à figer un menu vide ; les tests de notation ne jugent que ce qui est
déjà déclaré. 196 exercices sont restés ainsi sans que rien ne s'en plaigne,
jusqu'au relevé du 2026-09-18 — d'où ce test, écrit le jour où ils ont été
réparés pour qu'ils ne se recassent pas en silence.

Le critère est **structurel**, et c'est délibéré : les mesures textuelles
tentées ce jour-là (longueur de l'énoncé, présence de code dans le texte) n'ont
produit que des faux positifs, un vrai-faux « 7⁰ = 1 » étant court par nature.
"""

import os
import sys

import pytest

sys.path.insert(0, os.path.dirname(os.path.dirname(__file__)))
from core.oef.engine import load_and_render
from tests import corpus
from tests.known_failures import WIDGETS_ORPHELINS

SEED = 42

# Comme les deux autres parcours du corpus : une dizaine de minutes, donc hors
# des lancements ordinaires (`pytest.ini` écarte `slow` par défaut).
pytestmark = pytest.mark.slow

# Les types de segment qui attendent une saisie de l'élève, et eux seuls.
# `jsxgraph` porte un nom lui aussi — celui de sa boîte de dessin — mais c'est
# une **figure**, qui n'a pas à correspondre à une réponse : le compter donnait
# 151 faux positifs.
TYPES_DE_CHAMP = {"menu", "input"}


def _get_exercises():
    return corpus.exercises()


_EXERCISES = None


def get_exercises():
    global _EXERCISES
    if _EXERCISES is None:
        _EXERCISES = _get_exercises()
    return _EXERCISES


def pytest_generate_tests(metafunc):
    if "exercise" not in metafunc.fixturenames:
        return
    if "not slow" in (metafunc.config.getoption("markexpr") or ""):
        metafunc.parametrize("exercise", [])
        return
    exercises = get_exercises()
    metafunc.parametrize(
        "exercise",
        exercises,
        ids=[ex_id for ex_id, _ in exercises],
    )


def test_aucun_widget_orphelin(exercise):
    """Chaque champ posé par l'énoncé porte le nom d'une réponse déclarée."""
    ex_id, path = exercise
    if ex_id in WIDGETS_ORPHELINS:
        pytest.xfail(f"{ex_id} : widget orphelin connu (cf. known_failures)")
    try:
        render = load_and_render(path, seed=SEED)
    except Exception as e:  # noqa: BLE001
        # Le rendu est éprouvé par `test_exercises_render` : ne pas doubler
        # son verdict, mais ne pas conclure à tort que tout va bien.
        pytest.skip(f"rendu impossible ({type(e).__name__}) — cf. test_exercises_render")

    declares = {a.input_name for a in render.answers}
    declares |= {a.logical_name for a in render.answers if a.logical_name}

    orphelins = [
        f"{s['type']}:{s['name']}"
        for s in (render.statement_segments or [])
        if s.get("type") in TYPES_DE_CHAMP
        and s.get("name")
        and s["name"] not in declares
    ]
    assert not orphelins, (
        f"{ex_id} : l'énoncé pose {orphelins}, que `answers` ne déclare pas "
        f"({sorted(declares) or 'aucune réponse'}). Le front ne peut ni "
        f"remplir ce widget ni le faire noter."
    )
