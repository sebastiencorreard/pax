#!/usr/bin/env python3
"""Empreinte du corpus rendu — pour comparer un avant/après **par valeurs**.

Compter les réponses ne suffit pas : deux régressions de la refonte du
découpage (la moyenne d'`oefstat/mean`, le `val14` de `concentration1`)
laissaient le nombre de réponses intact et n'ont changé que leur *valeur*.
On capture donc, par exercice et par graine : l'attendu, la palette, le type
et une empreinte de l'énoncé.

    python3 scripts/corpus_state.py avant.json           # capture
    python3 scripts/corpus_state.py avant.json apres.json  # comparaison

Les graines sont celles des exercices sentinelles de
`docs/refactor-item-splitting.md`.
"""

import glob
import hashlib
import json
import os
import sys

sys.path.insert(0, os.path.dirname(os.path.dirname(os.path.abspath(__file__))))

from core.oef.def_engine import load_and_render  # noqa: E402

SEEDS = (42, 1135432845, 586627288)
ROOT = "/ressources"


def capture() -> dict:
    state: dict[str, dict] = {}
    for path in sorted(glob.glob(f"{ROOT}/**/*.def", recursive=True)):
        with open(path, "rb") as f:
            if b":question" not in f.read():
                continue
        rel = path.split("ressources/")[-1]
        for seed in SEEDS:
            try:
                r = load_and_render(path, seed=seed)
            except Exception as exc:  # noqa: BLE001
                state[f"{rel}@{seed}"] = {"erreur": type(exc).__name__}
                continue
            state[f"{rel}@{seed}"] = {
                "enonce": hashlib.sha1(
                    (r.statement_html or "").encode("utf-8")
                ).hexdigest()[:12],
                "vide": not (r.statement_html or "").strip(),
                "reponses": {
                    a.input_name: {
                        "type": a.answer_type,
                        "attendu": a.expected,
                        "palette": list(a.options.get("choices") or []),
                    }
                    for a in r.answers
                },
            }
    return state


def _flatten(state: dict) -> dict[str, str]:
    """Une clé par valeur observable, pour un diff lisible."""
    out: dict[str, str] = {}
    for key, ex in state.items():
        if "erreur" in ex:
            out[f"{key}|ERREUR"] = ex["erreur"]
            continue
        out[f"{key}|enonce"] = ex["enonce"]
        for name, a in ex["reponses"].items():
            out[f"{key}|{name}|type"] = a["type"]
            out[f"{key}|{name}|attendu"] = a["attendu"]
            out[f"{key}|{name}|palette"] = "\x1f".join(a["palette"])
    return out


def compare(before: dict, after: dict) -> int:
    a, b = _flatten(before), _flatten(after)
    ka, kb = set(a), set(b)
    disparues, apparues = sorted(ka - kb), sorted(kb - ka)
    modifiees = sorted(k for k in ka & kb if a[k] != b[k])

    # Une valeur qui se vide est le signal le plus sûr d'une régression.
    vidées = [k for k in modifiees if a[k].strip() and not b[k].strip()]
    remplies = [k for k in modifiees if not a[k].strip() and b[k].strip()]

    print(f"disparues {len(disparues)} | apparues {len(apparues)} "
          f"| modifiées {len(modifiees)}")
    print(f"  dont vidées {len(vidées)} | remplies {len(remplies)}")
    for k in vidées[:25]:
        print(f"   VIDÉE  {k}  |  {a[k][:60]!r}")
    for k in disparues[:15]:
        print(f"   PERDUE {k}  |  {a[k][:60]!r}")
    for k in modifiees[:15]:
        if k not in vidées:
            print(f"   ~      {k}\n            {a[k][:70]!r}\n         -> {b[k][:70]!r}")
    return 1 if (vidées or disparues) else 0


def main() -> int:
    if len(sys.argv) == 2:
        state = capture()
        with open(sys.argv[1], "w") as f:
            json.dump(state, f)
        erreurs = sum(1 for v in state.values() if "erreur" in v)
        vides = sum(1 for v in state.values() if v.get("vide"))
        print(f"capturé {len(state)} rendus ({len(SEEDS)} graines) "
              f"| erreurs {erreurs} | énoncés vides {vides} -> {sys.argv[1]}")
        return 0
    if len(sys.argv) == 3:
        with open(sys.argv[1]) as f:
            before = json.load(f)
        with open(sys.argv[2]) as f:
            after = json.load(f)
        return compare(before, after)
    print(__doc__)
    return 2


if __name__ == "__main__":
    sys.exit(main())
