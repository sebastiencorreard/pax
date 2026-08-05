#!/usr/bin/env python3
"""
Régénère les snapshots de référence dans tests/snapshots/.
À lancer après un changement voulu du rendu.

Usage :
    python3 scripts/update_snapshots.py            # tous les exercices
    python3 scripts/update_snapshots.py --id 2,5   # exercices spécifiques
"""

import sys
import os
import json
import argparse

sys.path.insert(0, os.path.dirname(os.path.dirname(__file__)))
from core.oef.engine import load_and_render
from tests import corpus

SNAPSHOTS_DIR = os.path.join(os.path.dirname(__file__), "..", "tests", "snapshots")
SEED = 42


def get_exercises(ids=None):
    """Corpus lu sur le disque — la base ne servait qu'à lister des chemins.

    L'ancienne version passait par `psql` (mot de passe en dur, client absent
    de l'image) et convertissait l'identifiant en entier, ce qui n'a plus cours
    depuis que les identifiants sont des slugs.
    """
    tout = corpus.exercises()
    if not ids:
        return tout
    voulus = set(ids)
    return [(ex_id, chemin) for ex_id, chemin in tout if ex_id in voulus]


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument(
        "--id", type=str, default=None,
        help="Identifiants (slugs) séparés par des virgules"
    )
    args = parser.parse_args()

    ids = [x.strip() for x in args.id.split(",")] if args.id else None
    exercises = get_exercises(ids=ids)

    os.makedirs(SNAPSHOTS_DIR, exist_ok=True)

    updated = errors = 0
    for ex_id, path in exercises:
        try:
            r = load_and_render(path, seed=SEED)
            snap = {
                "statement_html": r.statement_html,
                "answers": [
                    {
                        "input_name": a.input_name,
                        "expected": a.expected,
                        "answer_type": a.answer_type,
                        "options": a.options,
                    }
                    for a in r.answers
                ],
            }
            snap_path = os.path.join(SNAPSHOTS_DIR, f"ex_{ex_id}.json")
            with open(snap_path, "w", encoding="utf-8") as f:
                json.dump(snap, f, ensure_ascii=False, indent=2)
            updated += 1
        except Exception as e:
            print(f"  ❌ ex.{ex_id}: {e}")
            errors += 1

    print(f"Snapshots mis à jour : {updated}/{len(exercises)} ({errors} erreurs)")


if __name__ == "__main__":
    main()
