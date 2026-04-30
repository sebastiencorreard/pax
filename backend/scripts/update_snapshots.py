#!/usr/bin/env python3
"""
Régénère les snapshots de référence dans tests/snapshots/.
À lancer après un changement voulu du rendu.

Usage :
    python3 scripts/update_snapshots.py            # tous les exercices
    python3 scripts/update_snapshots.py --id 2,5   # exercices spécifiques
"""
import sys, os, json, argparse, subprocess

sys.path.insert(0, os.path.dirname(os.path.dirname(__file__)))
from core.oef.engine import load_and_render

SNAPSHOTS_DIR = os.path.join(os.path.dirname(__file__), '..', 'tests', 'snapshots')
SEED = 42


def get_exercises(ids=None):
    cond = f"WHERE id = ANY(ARRAY[{','.join(map(str, ids))}])" if ids else ""
    out = subprocess.check_output(
        ['psql', '-U', 'pax', '-h', 'localhost', 'pax', '-t', '-A', '-F', '|||',
         '-c', f'SELECT id, oef_path FROM exercises {cond} ORDER BY id'],
        env={**os.environ, 'PGPASSWORD': 'brougne99'}
    ).decode()
    return [(int(a), b.strip())
            for line in out.strip().split('\n')
            if line
            for a, b in [line.split('|||')]]


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument('--id', type=str, default=None,
                        help='IDs séparés par des virgules')
    args = parser.parse_args()

    ids = [int(x) for x in args.id.split(',')] if args.id else None
    exercises = get_exercises(ids=ids)

    os.makedirs(SNAPSHOTS_DIR, exist_ok=True)

    updated = errors = 0
    for ex_id, path in exercises:
        try:
            r = load_and_render(path, seed=SEED)
            snap = {
                'statement_html': r.statement_html,
                'answers': [
                    {'input_name': a.input_name, 'expected': a.expected,
                     'answer_type': a.answer_type, 'options': a.options}
                    for a in r.answers
                ],
            }
            snap_path = os.path.join(SNAPSHOTS_DIR, f'ex_{ex_id}.json')
            with open(snap_path, 'w', encoding='utf-8') as f:
                json.dump(snap, f, ensure_ascii=False, indent=2)
            updated += 1
        except Exception as e:
            print(f"  ❌ ex.{ex_id}: {e}")
            errors += 1

    print(f"Snapshots mis à jour : {updated}/{len(exercises)} ({errors} erreurs)")


if __name__ == '__main__':
    main()
