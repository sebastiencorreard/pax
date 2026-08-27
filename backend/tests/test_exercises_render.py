"""
Tests de non-régression sur le rendu HTML de tous les exercices.
Pour chaque exercice :
  1. Vérifie la structure du HTML (délimiteurs LaTeX, pas de directives résiduelles…)
  2. Compare au snapshot de référence (tests/snapshots/ex_<slug>.json)

Mettre à jour les snapshots après un changement voulu :
    python3 scripts/update_snapshots.py

Les 549 snapshots présents portent les identifiants **entiers** d'avant la
migration `c1a2b3d4e5f6` : plus rien ne leur correspond, et la comparaison se
contente donc de passer son tour. Ils sont à régénérer — ou à supprimer si l'on
juge que `scripts/corpus_state.py`, qui compare déjà l'ensemble du corpus par
valeurs, rend ce mécanisme redondant.
"""

import re
import json
import pytest
import os
import sys

sys.path.insert(0, os.path.dirname(os.path.dirname(__file__)))
from core.oef.engine import load_and_render
from tests import corpus
from tests.known_failures import XFAIL_RENDER_STRUCTURE

SNAPSHOTS_DIR = os.path.join(os.path.dirname(__file__), "snapshots")
SEED = 42

# Parcourir les 4278 exercices demande une dizaine de minutes : ces tests ne
# sont pas de ceux qu'on lance à chaque sauvegarde. `PAX_TEST_CORPUS` restreint
# le parcours (cf. `tests/corpus.py`).
pytestmark = pytest.mark.slow

# ------------------------------------------------------------------ #
# Chargement des exercices
# ------------------------------------------------------------------ #


def _get_exercises():
    return corpus.exercises()


# Mis en cache au niveau du module pour ne pas requêter la DB à chaque test
_EXERCISES = None


def get_exercises():
    global _EXERCISES
    if _EXERCISES is None:
        _EXERCISES = _get_exercises()
    return _EXERCISES


# ------------------------------------------------------------------ #
# Checks structurels
# ------------------------------------------------------------------ #

LATEX_CMDS = {
    "frac",
    "sqrt",
    "cdot",
    "times",
    "leq",
    "geq",
    "neq",
    "left",
    "right",
    "begin",
    "end",
    "text",
    "mathbb",
    "mathrm",
    "mathbf",
    "displaystyle",
    "infty",
    "sum",
    "prod",
    "int",
    "lim",
    "to",
    "in",
    "cup",
    "cap",
    "subset",
    "forall",
    "exists",
    "not",
    "pm",
    "mp",
    "div",
    "ldots",
    "cdots",
    "vdots",
    "alpha",
    "beta",
    "gamma",
    "delta",
    "epsilon",
    "zeta",
    "eta",
    "theta",
    "lambda",
    "mu",
    "nu",
    "xi",
    "pi",
    "rho",
    "sigma",
    "tau",
    "phi",
    "chi",
    "psi",
    "omega",
    "Gamma",
    "Delta",
    "Theta",
    "Lambda",
    "Pi",
    "Sigma",
    "Phi",
    "Psi",
    "Omega",
    "vec",
    "overline",
    "underline",
    "hat",
    "tilde",
    "quad",
    "qquad",
    "phantom",
    "hspace",
    "vspace",
    "color",
    "textbf",
    "textit",
    "emph",
    "le",
    "ge",
    "ne",
    "ll",
    "gg",
    "equiv",
    "approx",
    "propto",
    "sim",
    "simeq",
    "cong",
    "perp",
    "parallel",
    "angle",
    "triangle",
    "square",
    "circ",
    "bullet",
    "star",
    "dagger",
    "nabla",
    "partial",
    "ell",
    "Re",
    "Im",
    "wp",
    "aleph",
    "hbar",
    "oint",
    "oplus",
    "otimes",
    "ominus",
    "odot",
    "langle",
    "rangle",
    "lceil",
    "rceil",
    "lfloor",
    "rfloor",
    "uparrow",
    "downarrow",
    "leftarrow",
    "rightarrow",
    "Leftarrow",
    "Rightarrow",
    "leftrightarrow",
    "Leftrightarrow",
    "mapsto",
    "longrightarrow",
    "longleftarrow",
    "overrightarrow",
    "widehat",
    "widetilde",
    "underbrace",
    "overbrace",
    "stackrel",
    "mathcal",
    "mathfrak",
    "boldsymbol",
    "pmod",
    "bmod",
    "ker",
    "dim",
    "deg",
    "exp",
    "log",
    "ln",
    "sin",
    "cos",
    "tan",
    "cot",
    "sec",
    "csc",
    "arcsin",
    "arccos",
    "arctan",
    "sinh",
    "cosh",
    "tanh",
    "max",
    "min",
    "sup",
    "inf",
    "gcd",
    "det",
    "operatorname",
    "n",
    "k",
    "p",
    "q",
    "r",
    "s",
    "t",
    "u",
    "v",
    "w",
    "x",
    "y",
    "z",
    "for",
    "if",
    "item",
    "enumerate",
    "itemize",
    "em",
}

OEF_DIRECTIVES = ["enonce", "embed", "statement", "answer", "while"]


# Zones où une syntaxe brute est le contenu, pas un défaut de conversion : la
# consigne de saisie (« saisir sqrt(3) pour √3 », présente dans tous les
# `quizz.fr`), et le code affiché des exercices de programmation, qui montre du
# Python — `from math import *` … `sqrt(x)`. 293 des 310 anomalies relevées
# venaient de là : c'est le contrôle qui se trompait, pas le rendu.
_ZONES_LITTERALES = re.compile(
    r"<(code|pre|kbd|samp)\b.*?</\1>"
    r"|<[^>]*class=\"[^\"]*(wims_instruction|tt|oef-code)[^\"]*\"[^>]*>.*?</[^>]+>",
    re.S | re.I,
)


def texte_sans_zones_litterales(html: str) -> str:
    """Le HTML débarrassé des consignes et du code affiché."""
    return _ZONES_LITTERALES.sub(" ", html)


_ZONE_MATH = re.compile(r"\\\((.*?)\\\)", re.S)


def zones_mathematiques(html: str) -> str:
    """Le contenu des `\\( … \\)`, seul endroit où une conversion a lieu.

    Une syntaxe WIMS restée brute n'est un défaut que là : `\\(-3*sqrt(x) = 0\\)`
    s'affiche littéralement à l'élève. Dans le texte courant, `sqrt(` est au
    contraire ce qu'on lui demande de taper. Le contrôle portait sur tout le
    HTML et signalait 233 énoncés parfaitement corrects pour 5 vrais.
    """
    return "\n".join(_ZONE_MATH.findall(texte_sans_zones_litterales(html)))


def structural_issues(html: str) -> list[str]:
    issues = []
    # Les contrôles de syntaxe non convertie portent sur les seules formules :
    # ailleurs, `sqrt(` est ce que l'énoncé demande à l'élève de taper.
    maths = zones_mathematiques(html)

    # 1. Délimiteurs LaTeX équilibrés
    opens = len(re.findall(r"\\\(", html))
    closes = len(re.findall(r"\\\)", html))
    if opens != closes:
        issues.append(f"\\( déséquilibré : {opens} ouvrants / {closes} fermants")

    # 2. sqrt( brut
    if re.search(r"(?<!\\)sqrt\(", maths):
        issues.append("'sqrt(' brut non converti en \\sqrt{}")

    # 3. texmath( non converti
    if "texmath(" in maths:
        issues.append("'texmath(' non converti")

    # 4. Directives OEF résiduelles
    for d in OEF_DIRECTIVES:
        if re.search(rf"\\{d}\s*\{{", html):
            issues.append(f"directive OEF résiduelle : \\{d}{{")

    # 5. Fonctions WIMS non évaluées
    for fn in ["randint(", "randitem(", "wims("]:
        if fn in maths:
            issues.append(f"fonction WIMS non évaluée : {fn}")

    # 6. Énoncé vide — mais tout énoncé n'est pas fait de texte. Un exercice
    # peut poser sa question par une **image** (`0703` montre une table de
    # pressions) ou par le **widget** lui-même (`nompolygone` fait apparier
    # trois noms de polygones à leurs figures, et n'a rien d'autre à dire).
    # Ne compter que le texte y voyait un énoncé vide, alors qu'il ne manque
    # rien à l'élève.
    text = re.sub(r"<[^>]+>", "", html).strip()
    porte_un_visuel = re.search(
        r"<(?:img|svg|canvas)\b|<cf-slot\b|class=\"oef-", html or ""
    )
    if len(text) < 5 and not porte_un_visuel:
        issues.append("énoncé quasi-vide")

    return issues


# ------------------------------------------------------------------ #
# Paramétrage pytest
# ------------------------------------------------------------------ #


def pytest_generate_tests(metafunc):
    if "exercise" not in metafunc.fixturenames:
        return
    # Énumérer le corpus est immédiat ici, mais les 4278 paramètres alourdissent
    # la collecte pour rien quand `-m "not slow"` va les écarter.
    if "not slow" in (metafunc.config.getoption("markexpr") or ""):
        metafunc.parametrize("exercise", [])
        return
    exercises = get_exercises()
    metafunc.parametrize(
        "exercise",
        exercises,
        ids=[ex_id for ex_id, _ in exercises],
    )


# ------------------------------------------------------------------ #
# Test structurel
# ------------------------------------------------------------------ #


def test_render_structure(exercise):
    ex_id, path = exercise
    if ex_id in XFAIL_RENDER_STRUCTURE:
        pytest.xfail(f"{ex_id}: anomalie structurelle préexistante")
    render = load_and_render(path, seed=SEED)
    html = render.statement_html
    issues = structural_issues(html)
    assert not issues, "\n".join(issues)


# ------------------------------------------------------------------ #
# Test de non-régression (snapshot)
# ------------------------------------------------------------------ #


def test_render_snapshot(exercise):
    ex_id, path = exercise
    # Les snapshots couvrent **tout le corpus**. Un exercice sans référence est
    # donc un exercice arrivé depuis la dernière régénération : le signaler
    # plutôt que de le passer sous silence, car ce test se tait quand il ne
    # trouve rien — c'est ainsi qu'il n'a rien protégé pendant des mois.
    # Cf. `tests/snapshots/README.md`.
    snap_path = os.path.join(SNAPSHOTS_DIR, f"ex_{ex_id}.json")
    if not os.path.exists(snap_path):
        pytest.skip(f"{ex_id} sans référence — lancer scripts/update_snapshots.py")

    with open(snap_path) as f:
        snap = json.load(f)

    render = load_and_render(path, seed=SEED)
    assert render.statement_html == snap["statement_html"], (
        f"Le HTML a changé pour {ex_id}"
    )

    current_answers = [
        {
            "input_name": a.input_name,
            "expected": a.expected,
            "answer_type": a.answer_type,
            "options": a.options,
        }
        for a in render.answers
    ]
    assert current_answers == snap["answers"], (
        f"Les réponses attendues ont changé pour {ex_id}"
    )
