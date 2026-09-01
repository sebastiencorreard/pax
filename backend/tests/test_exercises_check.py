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

# Types dont la virgule fait partie de la réponse — un ensemble solution
# `-6/5,-9/8`, des coordonnées, une suite d'étiquettes. Partout ailleurs elle
# sépare des écritures acceptables, comme le `|`.
_TYPES_LISTE = {
    "fset", "set", "coord", "clickfill", "dragfill", "correspond", "imagefill",
    "range", "matrix", "atext",
}


def _candidats(ans):
    """Réponses recevables tirées d'`expected`.

    WIMS y range souvent plusieurs écritures équivalentes — `parallèle|parallèles`,
    `-9*x^2+144,144-9*x^2`. C'est un catalogue de possibilités, pas une réponse :
    le soumettre en bloc est refusé, et à juste titre. Vérifié à la main sur les
    trois formes (voir `fset` en regard, où la virgule appartient à la réponse).
    """
    brut = ans.expected or ""
    yield brut
    # `atext` range sa réponse en **première ligne** de `replygood`, et le `;`
    # y fait un saut de ligne (`anstype/atext` : `!rows2lines` puis
    # `!line 1 of`). Ce qui suit n'est pas une écriture acceptable : les 14
    # `oefcountries` y listent les *autres* pays, pour le seul diagnostic
    # `unknownword`. Soumettre le tout n'a jamais été une bonne réponse.
    if ans.answer_type == "atext" and ";" in brut:
        from core.oef.def_engine.wims_lists import cutlines, rows2lines  # noqa: PLC0415
        lignes, _ = rows2lines(re.sub(r"[ \t]+", " ", brut))
        for ligne in cutlines(lignes):
            if ligne.strip():
                yield ligne.strip()
                break
    # `range` stocke des **bornes**, pas une réponse : `0.6,0.4` est
    # l'intervalle [0.4 ; 0.6]. La valeur qu'un élève est censé saisir — et que
    # WIMS affiche en corrigé (`replyGood`) — est le milieu du premier
    # intervalle. Soumettre les bornes n'a jamais été une bonne réponse ; cela
    # passait tant que `range` retombait sur une comparaison de texte.
    if ans.answer_type == "range":
        from core.answer.checkers import range_display_answer  # noqa: PLC0415
        milieu = range_display_answer(brut)
        if milieu:
            yield milieu
    # `sigunits` stocke `"<valeur> <unité> #N"`, où `#N` est la **consigne** :
    # arrondir à N chiffres significatifs. Soumettre l'attendu tel quel revient
    # à rendre la valeur non arrondie, que le checker refuse — à bon droit,
    # puisque l'exercice demande précisément l'arrondi. Même travers que les
    # bornes de `range` ci-dessus.
    if ans.answer_type == "sigunits" and "#" in brut:
        from core.answer.checkers import sigunits_display_answer  # noqa: PLC0415
        arrondi = sigunits_display_answer(brut)
        if arrondi:
            yield arrondi
    # `coord` n'attend pas une zone mais un **point** : `reply` est le pixel
    # cliqué, quand `expected` décrit la cible (`circle,110,80,30/3`). Le
    # centre de cette cible est une bonne réponse ; la description, non.
    if ans.answer_type == "coord":
        from core.answer.checkers import coord_display_answer  # noqa: PLC0415
        clic = coord_display_answer(brut)
        if clic:
            yield clic
    # `draw` attend la liste des coordonnées que l'élève a tracées, quand
    # l'attendu juxtapose la figure de fond et cette liste, précédée du type
    # d'objet — `[<figure>];crosshairs,1.59,-0.04,…`.
    if ans.answer_type == "draw":
        from core.answer.checkers import draw_display_answer  # noqa: PLC0415
        coords = draw_display_answer(brut)
        if coords:
            yield coords
    # `jsxgraphcurve` attend une **figure**, décrite après le `;` par sa forme
    # et ses coordonnées (`sline,250,250,389,501`). L'attendu porte l'image en
    # tête ; ce sont les coordonnées seules que l'élève produit en traçant.
    if ans.answer_type == "jsxgraphcurve" and ";" in brut:
        zone = brut.split(";", 1)[1]
        _, _, coords = zone.partition(",")
        if coords.strip():
            yield coords.strip()
    # `numexp` demande un **nombre**, jamais un calcul : c'est tout l'objet du
    # type, qui refuse `+ - * ^ (` (`nocompute` d'`anstype/numexp`). L'attendu
    # peut pourtant être une expression — `produit5` range `5*3` pour « 5³×3³,
    # soit 15³ » —, et la soumettre telle quelle revenait à taper la consigne
    # au lieu de la réponse, comme les bornes d'un `range` ou le `#N` d'un
    # `sigunits`.
    if ans.answer_type == "numexp" and re.search(r"[+\-*/^()]", brut):
        from core.answer.checkers import _eval_scalar  # noqa: PLC0415
        from core.oef.numfmt import format_wims_float  # noqa: PLC0415
        try:
            yield format_wims_float(_eval_scalar(brut, comma_is_decimal=False))
        except (ValueError, ZeroDivisionError, OverflowError):
            pass
    if "|" in brut:
        for part in brut.split("|"):
            yield part.strip()
    if "," in brut and ans.answer_type not in _TYPES_LISTE:
        for part in brut.split(","):
            yield part.strip()


def _meilleure_reponse(ans) -> str:
    """La formulation d'`expected` qui obtient le meilleur score pour ce champ.

    Le test demande « une bonne réponse est-elle acceptée ? ». La valeur entière
    est essayée d'abord : quand elle convient, c'est elle qui est retenue.
    """
    meilleure, meilleur_score = ans.expected or "", -1.0
    for candidat in _candidats(ans):
        res = check_answer(
            answer_type=ans.answer_type,
            reply=candidat,
            expected=ans.expected,
            options=ans.options,
        )
        if res.score > meilleur_score:
            meilleure, meilleur_score = candidat, res.score
        if meilleur_score >= 1.0:
            break
    return meilleure


def _check_all(render, replies: dict) -> float:
    """Évalue toutes les réponses et retourne le score global."""
    if render.condition:
        pytest.skip("Exercice avec \\condition globale (non supporté ici)")

    total_weight = 0.0
    weighted_score = 0.0
    for ans in render.answers:
        # Un champ sans réponse attendue n'est pas noté — brouillon, `type=draft`
        # ou `default=vide`. Le faire peser tirait le score global vers le bas
        # quoi qu'on soumette, et 78 exercices échouaient pour cette seule raison.
        if not (ans.expected or "").strip():
            continue
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
    r"""Génère une réponse franchement fausse à partir de la bonne.

    L'ancienne version ajoutait 999. Or `\precision{M}` définit une tolérance
    **relative** — `compare.c` : `|d1-d2|*prec <= |d1+d2| + 1/prec` — de sorte
    qu'à 7 035 000 près, la tolérance vaut 1407 et l'écart de 999 tombait
    *dedans*. Trois exercices semblaient accepter une réponse fausse ; ils
    appliquaient la règle de WIMS à la lettre.

    `3n + 7` place la réponse hors tolérance quelle que soit la grandeur, et
    n'a pas de point fixe entier — `2n + 1` en avait un, `-1`, qui faisait
    passer la réponse « fausse » pour la bonne dans 18 exercices.
    """
    try:
        n = float(expected.replace(',', '.'))
        return str(int(n) * 3 + 7)
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
        # Ce filtre écarte **avant la collecte** : un exercice retiré ici ne
        # se signale ni en échec, ni en skip, ni nulle part. Le garder étroit.
        if not r.answers:
            # 24 exercices n'exposent aucune réponse. Onze affichent pourtant
            # des champs où l'élève peut écrire : défaut réel, à instruire.
            continue
        if r.condition:
            # `\condition` globale : la note dépend d'un croisement entre
            # champs que `_check_all` ne sait pas reproduire. Aucun exercice du
            # corpus n'y tombe aujourd'hui.
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
    correct_replies = {a.input_name: _meilleure_reponse(a) for a in render.answers}
    if not any(v.strip() for v in correct_replies.values()):
        pytest.skip("aucun champ noté (réponses attendues toutes vides)")
    # Un champ peut porter une réponse attendue **et** un poids nul : sa note
    # vient d'ailleurs. Les trois `analyze` d'`oefstatistiques` (`histocap`,
    # `histogramme`, `moustache`) sont dans ce cas — le widget affiche une
    # valeur, la notation se fait dans la section `:test`. Le score global se
    # divise alors par un poids total nul, et `_check_all` rend 0 : exiger 1
    # d'un exercice dont rien n'est noté n'a pas de sens.
    if not any(a.weight for a in render.answers if (a.expected or "").strip()):
        pytest.skip("aucun champ pesant (poids tous nuls — noté par :test)")
    score = _check_all(render, correct_replies)
    assert score == pytest.approx(1.0, abs=1e-9), \
        f"{ex_id}: score={score} avec la bonne réponse {correct_replies}"


def test_wrong_answer_scores_less_than_1(exercise):
    """Soumettre une réponse fausse donne score<1."""
    ex_id, path = exercise
    if ex_id in XFAIL_WRONG_SCORE:
        pytest.xfail(f"{ex_id}: une réponse fausse est acceptée (bug préexistant)")
    render = load_and_render(path, seed=SEED)
    # Fausser le premier champ **noté** : un champ sans réponse attendue est
    # ignoré à l'évaluation, le fausser ne prouverait rien.
    notes = [a for a in render.answers if (a.expected or "").strip()]
    if not notes:
        pytest.skip("aucun champ noté (réponses attendues toutes vides)")
    wrong_replies = {}
    for i, a in enumerate(notes):
        if i == 0:
            wrong_replies[a.input_name] = _wrong_answer(a.expected)
        else:
            wrong_replies[a.input_name] = _meilleure_reponse(a)
    score = _check_all(render, wrong_replies)
    assert score < 1.0, \
        f"{ex_id}: score={score} même avec une réponse fausse {wrong_replies}"
