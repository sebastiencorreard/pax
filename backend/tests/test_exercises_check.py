"""
Tests fonctionnels : soumet la bonne reponse et verifie score=1,
puis soumet une reponse fausse et verifie score<1.

Seuls les exercices dont les reponses sont connues (pas de condition complexe)
et non-radio sont testes automatiquement.
"""
import os
import re
import sys
import pytest
from tests import corpus
from tests.known_failures import XFAIL_CORRECT_SCORE, XFAIL_WRONG_SCORE

sys.path.insert(0, os.path.dirname(os.path.dirname(__file__)))
from core.oef.engine import load_and_render
from core.answer.checkers import check_answer

SEED = 42

# Parcourir les 4278 exercices demande une dizaine de minutes : ces tests ne
# sont pas de ceux qu'on lance à chaque sauvegarde. `PAX_TEST_CORPUS` restreint
# le parcours (cf. `tests/corpus.py`).
pytestmark = pytest.mark.slow


# ------------------------------------------------------------------ #
# Helpers
# ------------------------------------------------------------------ #

def _check_all(render, replies: dict) -> float:
    """Évalue toutes les réponses et retourne le score global."""
    if render.condition:
        pytest.skip("Exercice avec \\condition globale (non supporté ici)")

    total_weight = 0.0
    weighted_score = 0.0
    for ans in render.answers:
        reply_value = replies.get(ans.input_name, "").strip()
        result = check_answer(
            answer_type=ans.answer_type,
            reply=reply_value,
            expected=ans.expected,
            options=ans.options,
        )
        weighted_score += result.score * ans.weight
        total_weight += ans.weight

    return weighted_score / total_weight if total_weight > 0 else 0.0


def _wrong_answer(expected: str) -> str:
    """Génère une réponse clairement fausse à partir de la bonne."""
    try:
        n = float(expected.replace(',', '.'))
        return str(int(n) + 999)
    except (ValueError, AttributeError):
        return "__FAUX__"


# ------------------------------------------------------------------ #
# Sélection des exercices testables
# ------------------------------------------------------------------ #

_UNRESOLVED = re.compile(
    r'wims\(|randint\(|randitem\(|item\(|makelist\(|sort\(|'
    r'solve\(|diff\(|integrate\(|limit\(|evalue\(|'
    r'matrix\(|det\(|eigenvalues\(|append\s+item|'
    r'random\(|isin\b|'
    r'\?[^:]*:'        # opérateur ternaire OEF ?:
    r'|\\for\{|\\while\{'
)

def _expected_is_resolved(expected: str) -> bool:
    """Retourne False si la réponse attendue contient des fonctions non évaluées."""
    return not bool(_UNRESOLVED.search(expected))


def _get_testable_exercises():
    rows = corpus.exercises()

    testable = []
    for ex_id, path in rows:
        try:
            r = load_and_render(path, seed=SEED)
        except Exception:
            continue
        # Exclure : sans réponse, avec \condition, radio uniquement
        if not r.answers:
            continue
        if r.condition:
            continue
        if all(a.answer_type == 'radio' for a in r.answers):
            continue
        # Exclure si la réponse attendue contient des fonctions WIMS non résolues
        if not all(_expected_is_resolved(a.expected) for a in r.answers):
            continue
        testable.append((ex_id, path))
    return testable


_TESTABLE = None

def get_testable():
    global _TESTABLE
    if _TESTABLE is None:
        _TESTABLE = _get_testable_exercises()
    return _TESTABLE


def pytest_generate_tests(metafunc):
    if 'exercise' not in metafunc.fixturenames:
        return
    # Énumérer le corpus rend les 4278 exercices : inutile de payer ces minutes
    # à la collecte quand `-m "not slow"` va de toute façon les écarter.
    if "not slow" in (metafunc.config.getoption("markexpr") or ""):
        metafunc.parametrize('exercise', [])
        return
    testable = get_testable()
    metafunc.parametrize(
        'exercise',
        testable,
        ids=[ex_id for ex_id, _ in testable],
    )


# ------------------------------------------------------------------ #
# Tests
# ------------------------------------------------------------------ #

def test_correct_answer_scores_1(exercise):
    """Soumettre la bonne réponse donne score=1."""
    ex_id, path = exercise
    if ex_id in XFAIL_CORRECT_SCORE:
        pytest.xfail(f"{ex_id}: la bonne réponse ne donne pas 1 (bug préexistant)")
    render = load_and_render(path, seed=SEED)
    correct_replies = {a.input_name: a.expected for a in render.answers}
    score = _check_all(render, correct_replies)
    assert score == pytest.approx(1.0, abs=1e-9), \
        f"{ex_id}: score={score} avec la bonne réponse {correct_replies}"


def test_wrong_answer_scores_less_than_1(exercise):
    """Soumettre une réponse fausse donne score<1."""
    ex_id, path = exercise
    if ex_id in XFAIL_WRONG_SCORE:
        pytest.xfail(f"{ex_id}: une réponse fausse est acceptée (bug préexistant)")
    render = load_and_render(path, seed=SEED)
    # Ne prend que le premier champ pour le rendre faux
    wrong_replies = {}
    for i, a in enumerate(render.answers):
        if i == 0:
            wrong_replies[a.input_name] = _wrong_answer(a.expected)
        else:
            wrong_replies[a.input_name] = a.expected
    score = _check_all(render, wrong_replies)
    assert score < 1.0, \
        f"{ex_id}: score={score} même avec une réponse fausse {wrong_replies}"
