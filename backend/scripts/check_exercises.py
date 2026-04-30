#!/usr/bin/env python3
"""
Vérifie le rendu de tous les exercices et signale les anomalies.
Usage : python3 scripts/check_exercises.py [--limit N] [--id ID1,ID2,...]
"""
import sys, os, re, argparse, subprocess
sys.path.insert(0, os.path.dirname(os.path.dirname(__file__)))

from core.oef.engine import load_and_render

# ------------------------------------------------------------------ #
# Récupération des exercices depuis la DB
# ------------------------------------------------------------------ #

def get_exercises(ids=None, limit=None):
    cond = f"WHERE id = ANY(ARRAY[{','.join(map(str, ids))}])" if ids else ""
    lim  = f"LIMIT {limit}" if limit else ""
    out  = subprocess.check_output(
        ['psql', '-U', 'pax', '-h', 'localhost', 'pax', '-t', '-A', '-F', '|||',
         '-c', f'SELECT id, oef_path FROM exercises {cond} ORDER BY id {lim}'],
        env={**os.environ, 'PGPASSWORD': 'brougne99'}
    ).decode()
    return [(int(a), b.strip()) for line in out.strip().split('\n')
            if line for a, b in [line.split('|||')]]


# ------------------------------------------------------------------ #
# Checks appliqués au HTML rendu
# ------------------------------------------------------------------ #

CHECKS = []

def check(fn):
    CHECKS.append(fn)
    return fn

@check
def check_math_delimiters(html, _path):
    """\\( et \\) déséquilibrés"""
    opens  = len(re.findall(r'\\\(', html))
    closes = len(re.findall(r'\\\)', html))
    if opens != closes:
        return f"\\( déséquilibré : {opens} ouvrants, {closes} fermants"

@check
def check_raw_sqrt(html, _path):
    """sqrt( non converti en \\sqrt{"""
    if re.search(r'(?<!\\)sqrt\(', html):
        return "contient 'sqrt(' brut (non converti en \\sqrt{...})"

@check
def check_raw_texmath(html, _path):
    """texmath( non converti"""
    if 'texmath(' in html:
        return "contient 'texmath(' non converti"

@check
def check_unresolved_vars(html, _path):
    r"""Variables OEF non substituées : \a, \b, \enonce, etc."""
    m = re.search(r'\\([a-zA-Z][a-zA-Z0-9]*)(?![a-zA-Z{(])', html)
    # Exclure les commandes LaTeX légitimes
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
        'textit','emph','href','le','ge','ne','ll','gg','equiv','approx',
        'propto','sim','simeq','cong','perp','parallel','angle','triangle',
        'square','circ','bullet','star','dagger','ddagger','nabla','partial',
        'ell','Re','Im','wp','aleph','hbar','imath','jmath','oint','oplus',
        'otimes','ominus','odot','boxplus','boxtimes','diamond','langle',
        'rangle','lceil','rceil','lfloor','rfloor','uparrow','downarrow',
        'Uparrow','Downarrow','leftarrow','rightarrow','Leftarrow',
        'Rightarrow','leftrightarrow','Leftrightarrow','mapsto','hookrightarrow',
        'longrightarrow','longleftarrow','xleftarrow','xrightarrow',
        'overrightarrow','overleftarrow','widehat','widetilde',
        'underbrace','overbrace','stackrel','overset','underset',
        'mathcal','mathfrak','mathscr','boldsymbol','pmod','bmod',
        'ker','dim','deg','exp','log','ln','sin','cos','tan','cot',
        'sec','csc','arcsin','arccos','arctan','sinh','cosh','tanh',
        'max','min','sup','inf','limsup','liminf','gcd','det','tr',
        'operatorname','label','ref','eqref','tag','notag','nonumber',
        'item','enumerate','itemize','description',
        'n','k','p','q','r','s','t','u','v','w','x','y','z',
    }
    if m and m.group(1) not in LATEX_CMDS:
        return f"variable OEF non substituée : \\{m.group(1)}"

@check
def check_empty_statement(html, _path):
    """Énoncé vide ou quasi-vide"""
    text = re.sub(r'<[^>]+>', '', html).strip()
    if len(text) < 5:
        return f"énoncé quasi-vide : {repr(html[:80])}"

@check
def check_oef_directives(html, _path):
    r"""Directives OEF non traitées : \enonce, \embed{, etc."""
    for pattern, label in [
        (r'\\enonce\b', r'\enonce'),
        (r'\\embed\s*\{', r'\embed{'),
        (r'\\statement\s*\{', r'\statement{'),
        (r'\\answer\s*\{', r'\answer{'),
        (r'\\if\s*\{', r'\if{'),
        (r'\\while\s*\{', r'\while{'),
    ]:
        if re.search(pattern, html):
            return f"directive OEF non traitée : {label}"

@check
def check_wims_functions(html, _path):
    """Fonctions WIMS non évaluées dans le HTML final"""
    for fn in ['randint(', 'randitem(', 'wims(', 'item(']:
        if fn in html:
            return f"fonction WIMS non évaluée : {fn}"

@check
def check_no_answers(html, path):
    """Pas de champ de réponse dans l'énoncé (hors radio)"""
    if 'oef-input' not in html and 'cf-slot' not in html:
        # Les exercices radio (choice) n'ont pas d'embed — c'est normal
        pass  # On ne signale pas car les radio sont gérés séparément


# ------------------------------------------------------------------ #
# Runner principal
# ------------------------------------------------------------------ #

def main():
    parser = argparse.ArgumentParser()
    parser.add_argument('--limit', type=int, default=None)
    parser.add_argument('--id', type=str, default=None,
                        help='IDs séparés par des virgules')
    args = parser.parse_args()

    ids = [int(x) for x in args.id.split(',')] if args.id else None
    exercises = get_exercises(ids=ids, limit=args.limit)

    results = {'ok': [], 'warn': [], 'error': []}

    for ex_id, path in exercises:
        try:
            render = load_and_render(path, seed=42)
            html = render.statement_html
            issues = []
            for fn in CHECKS:
                msg = fn(html, path)
                if msg:
                    issues.append(msg)
            if issues:
                results['warn'].append((ex_id, path, issues))
            else:
                results['ok'].append(ex_id)
        except Exception as e:
            results['error'].append((ex_id, path, str(e)))

    total = len(exercises)
    n_ok    = len(results['ok'])
    n_warn  = len(results['warn'])
    n_error = len(results['error'])

    print(f"\n{'='*60}")
    print(f"  Résultats : {total} exercices testés")
    print(f"  ✅  OK      : {n_ok}")
    print(f"  ⚠️   Avert. : {n_warn}")
    print(f"  ❌  Erreurs : {n_error}")
    print(f"{'='*60}\n")

    if results['error']:
        print("── ERREURS (exception lors du rendu) ──────────────────────")
        for ex_id, path, msg in results['error']:
            print(f"  ex.{ex_id:4d}  {msg}")
            print(f"         {path}")
        print()

    if results['warn']:
        print("── AVERTISSEMENTS ──────────────────────────────────────────")
        for ex_id, path, issues in results['warn']:
            for issue in issues:
                print(f"  ex.{ex_id:4d}  {issue}")
        print()

    sys.exit(0 if n_error == 0 else 1)


if __name__ == '__main__':
    main()
