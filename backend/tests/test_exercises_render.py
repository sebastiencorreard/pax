"""
Tests de non-régression sur le rendu HTML de tous les exercices.
Pour chaque exercice :
  1. Vérifie la structure du HTML (délimiteurs LaTeX, pas de directives résiduelles…)
  2. Compare au snapshot de référence (tests/snapshots/ex_N.json)

Mettre à jour les snapshots après un changement voulu :
    python3 scripts/update_snapshots.py
"""
import re
import json
import pytest
import subprocess
import os
import sys

sys.path.insert(0, os.path.dirname(os.path.dirname(__file__)))
from core.oef.engine import load_and_render
from tests.known_failures import XFAIL_RENDER_STRUCTURE

SNAPSHOTS_DIR = os.path.join(os.path.dirname(__file__), 'snapshots')
SEED = 42

# ------------------------------------------------------------------ #
# Chargement des exercices
# ------------------------------------------------------------------ #

def _get_exercises():
    out = subprocess.check_output(
        ['psql', '-U', 'pax', '-h', 'localhost', 'pax', '-t', '-A', '-F', '|||',
         '-c', 'SELECT id, oef_path FROM exercises ORDER BY id'],
        env={**os.environ, 'PGPASSWORD': 'brougne99'}
    ).decode()
    return [(int(a), b.strip())
            for line in out.strip().split('\n')
            if line
            for a, b in [line.split('|||')]]

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
    'frac','sqrt','cdot','times','leq','geq','neq','left','right',
    'begin','end','text','mathbb','mathrm','mathbf','displaystyle',
    'infty','sum','prod','int','lim','to','in','cup','cap','subset',
    'forall','exists','not','pm','mp','div','ldots','cdots','vdots',
    'alpha','beta','gamma','delta','epsilon','zeta','eta','theta',
    'lambda','mu','nu','xi','pi','rho','sigma','tau','phi','chi',
    'psi','omega','Gamma','Delta','Theta','Lambda','Pi','Sigma',
    'Phi','Psi','Omega','vec','overline','underline','hat','tilde',
    'quad','qquad','phantom','hspace','vspace','color','textbf',
    'textit','emph','le','ge','ne','ll','gg','equiv','approx',
    'propto','sim','simeq','cong','perp','parallel','angle','triangle',
    'square','circ','bullet','star','dagger','nabla','partial',
    'ell','Re','Im','wp','aleph','hbar','oint','oplus',
    'otimes','ominus','odot','langle','rangle','lceil','rceil',
    'lfloor','rfloor','uparrow','downarrow','leftarrow','rightarrow',
    'Leftarrow','Rightarrow','leftrightarrow','Leftrightarrow',
    'mapsto','longrightarrow','longleftarrow','overrightarrow',
    'widehat','widetilde','underbrace','overbrace','stackrel',
    'mathcal','mathfrak','boldsymbol','pmod','bmod',
    'ker','dim','deg','exp','log','ln','sin','cos','tan','cot',
    'sec','csc','arcsin','arccos','arctan','sinh','cosh','tanh',
    'max','min','sup','inf','gcd','det','operatorname',
    'n','k','p','q','r','s','t','u','v','w','x','y','z',
    'for','if','item','enumerate','itemize','em',
}

OEF_DIRECTIVES = ['enonce', 'embed', 'statement', 'answer', 'while']


def structural_issues(html: str) -> list[str]:
    issues = []

    # 1. Délimiteurs LaTeX équilibrés
    opens  = len(re.findall(r'\\\(', html))
    closes = len(re.findall(r'\\\)', html))
    if opens != closes:
        issues.append(f"\\( déséquilibré : {opens} ouvrants / {closes} fermants")

    # 2. sqrt( brut
    if re.search(r'(?<!\\)sqrt\(', html):
        issues.append("'sqrt(' brut non converti en \\sqrt{}")

    # 3. texmath( non converti
    if 'texmath(' in html:
        issues.append("'texmath(' non converti")

    # 4. Directives OEF résiduelles
    for d in OEF_DIRECTIVES:
        if re.search(rf'\\{d}\s*\{{', html):
            issues.append(f"directive OEF résiduelle : \\{d}{{")

    # 5. Fonctions WIMS non évaluées
    for fn in ['randint(', 'randitem(', 'wims(']:
        if fn in html:
            issues.append(f"fonction WIMS non évaluée : {fn}")

    # 6. Énoncé vide
    text = re.sub(r'<[^>]+>', '', html).strip()
    if len(text) < 5:
        issues.append(f"énoncé quasi-vide")

    return issues


# ------------------------------------------------------------------ #
# Paramétrage pytest
# ------------------------------------------------------------------ #

def pytest_generate_tests(metafunc):
    if 'exercise' in metafunc.fixturenames:
        exercises = get_exercises()
        metafunc.parametrize(
            'exercise',
            exercises,
            ids=[f"ex{ex_id}" for ex_id, _ in exercises],
        )


# ------------------------------------------------------------------ #
# Test structurel
# ------------------------------------------------------------------ #

def test_render_structure(exercise):
    ex_id, path = exercise
    if ex_id in XFAIL_RENDER_STRUCTURE:
        pytest.xfail(f"ex.{ex_id}: anomalie structurelle préexistante")
    render = load_and_render(path, seed=SEED)
    html = render.statement_html
    issues = structural_issues(html)
    assert not issues, "\n".join(issues)


# ------------------------------------------------------------------ #
# Test de non-régression (snapshot)
# ------------------------------------------------------------------ #

def test_render_snapshot(exercise):
    ex_id, path = exercise
    snap_path = os.path.join(SNAPSHOTS_DIR, f'ex_{ex_id}.json')
    if not os.path.exists(snap_path):
        pytest.skip(f"Pas de snapshot pour ex.{ex_id} (lancer update_snapshots.py)")

    with open(snap_path) as f:
        snap = json.load(f)

    render = load_and_render(path, seed=SEED)
    assert render.statement_html == snap['statement_html'], \
        f"Le HTML a changé pour ex.{ex_id}"

    current_answers = [
        {'input_name': a.input_name, 'expected': a.expected,
         'answer_type': a.answer_type, 'options': a.options}
        for a in render.answers
    ]
    assert current_answers == snap['answers'], \
        f"Les réponses attendues ont changé pour ex.{ex_id}"
