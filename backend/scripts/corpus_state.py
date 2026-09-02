#!/usr/bin/env python3
"""Empreinte du corpus rendu — pour comparer un avant/après **par valeurs**.

Compter les réponses ne suffit pas : deux régressions de la refonte du
découpage (la moyenne d'`oefstat/mean`, le `val14` de `concentration1`)
laissaient le nombre de réponses intact et n'ont changé que leur *valeur*.
On capture donc, par exercice et par graine : l'attendu, la palette, le type
et une empreinte de l'énoncé.

Une empreinte d'énoncé, en revanche, ne dit **pas ce qui a changé** : un
tableau JSXGraph évanoui et une virgule déplacée donnent le même hash
différent. On capture donc aussi la **structure** du rendu — le nombre de
segments par type et l'appariement `group-open`/`group-close` —, ce qui met
au jour la disparition d'un widget et le HTML déséquilibré, les deux angles
morts que seuls des tests unitaires avaient vus jusqu'ici.

    python3 scripts/corpus_state.py avant.json           # capture
    python3 scripts/corpus_state.py avant.json apres.json  # comparaison

Les graines sont celles des exercices sentinelles de
`docs/refactor-item-splitting.md`.
"""

import collections
import glob
import hashlib
import json
import os
import sys

sys.path.insert(0, os.path.dirname(os.path.dirname(os.path.abspath(__file__))))

from core.oef.def_engine import load_and_render  # noqa: E402

SEEDS = (42, 1135432845, 586627288)
ROOT = "/ressources"


def _structure(segments) -> tuple[str, str]:
    """(segments par type, verdict d'appariement) d'un rendu.

    Le déséquilibre se lit sur la profondeur des groupes de mise en page :
    une fermeture de trop (profondeur négative) tronque la mise en page côté
    front, un ouvrant non refermé (profondeur finale > 0) avale la suite de
    l'énoncé. Les deux sont invisibles au hash — il change, sans dire pourquoi.
    """
    counts = collections.Counter(s.get("type", "?") for s in segments or [])
    par_type = " ".join(f"{t}={n}" for t, n in sorted(counts.items()))

    depth = 0
    min_depth = 0
    for seg in segments or []:
        if seg.get("type") == "group-open":
            depth += 1
        elif seg.get("type") == "group-close":
            depth -= 1
            min_depth = min(min_depth, depth)
    if min_depth < 0:
        verdict = f"fermeture-orpheline({min_depth})"
    elif depth > 0:
        verdict = f"ouvrant-non-fermé(+{depth})"
    else:
        verdict = "équilibré"
    return par_type, verdict


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
            segments, groupes = _structure(r.statement_segments)
            state[f"{rel}@{seed}"] = {
                "enonce": hashlib.sha1(
                    (r.statement_html or "").encode("utf-8")
                ).hexdigest()[:12],
                "vide": not (r.statement_html or "").strip(),
                "segments": segments,
                "groupes": groupes,
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
        # Absents d'une capture antérieure à l'ajout de la structure : on ne
        # les invente pas, sinon tout le corpus ressort en « apparues ».
        for champ in ("segments", "groupes"):
            if champ in ex:
                out[f"{key}|{champ}"] = ex[champ]
        for name, a in ex["reponses"].items():
            out[f"{key}|{name}|type"] = a["type"]
            out[f"{key}|{name}|attendu"] = a["attendu"]
            out[f"{key}|{name}|palette"] = "\x1f".join(a["palette"])
    return out


def _seg_counts(dump: str) -> dict[str, int]:
    counts = {}
    for part in dump.split():
        typ, _, n = part.partition("=")
        counts[typ] = int(n)
    return counts


def _widgets(counts) -> int:
    """Nombre de champs de réponse, tous types confondus.

    Sert à distinguer un widget disparu d'un widget remplacé : porter un type
    change son nom de segment sans rien retirer à l'élève.
    """
    reponses = ("input", "textarea", "menu", "correspond", "coord", "draw",
                "jsxgraph", "codeeditor", "slot", "radio-inline", "jmol",
                "geogebra")
    return sum(n for t, n in counts.items() if t in reponses)


def compare(before: dict, after: dict) -> int:
    a, b = _flatten(before), _flatten(after)
    ka, kb = set(a), set(b)
    disparues, apparues = sorted(ka - kb), sorted(kb - ka)
    modifiees = sorted(k for k in ka & kb if a[k] != b[k])

    structurelles = [k for k in modifiees if k.endswith(("|segments", "|groupes"))]
    modifiees = [k for k in modifiees if k not in set(structurelles)]

    # Une valeur qui se vide est le signal le plus sûr d'une régression.
    vidées = [k for k in modifiees if a[k].strip() and not b[k].strip()]
    remplies = [k for k in modifiees if not a[k].strip() and b[k].strip()]

    # Un segment en moins, c'est un widget évanoui : un tableau JSXGraph, un
    # champ de saisie. Le hash d'énoncé le signale sans le nommer.
    #
    # Sauf quand un widget en **remplace** un autre : porter `type=draw` change
    # un `input` en `draw`, un pour un. Le compteur y lisait 27 pertes là où le
    # nombre total de champs de réponse ne bougeait pas. On sépare donc les
    # deux — une perte reste une perte, une substitution se lit comme telle.
    perdus, substitutions = [], []
    for k in structurelles:
        if not k.endswith("|segments"):
            continue
        av, ap = _seg_counts(a[k]), _seg_counts(b[k])
        manques = [f"{t} {av[t]}→{ap.get(t, 0)}" for t in sorted(av)
                   if ap.get(t, 0) < av[t]]
        if not manques:
            continue
        gagnes = sum(max(0, ap[t] - av.get(t, 0)) for t in ap)
        perdu_total = sum(max(0, av[t] - ap.get(t, 0)) for t in av)
        if gagnes == perdu_total and _widgets(av) == _widgets(ap):
            gains = [f"{t} {av.get(t, 0)}→{ap[t]}" for t in sorted(ap)
                     if ap[t] > av.get(t, 0)]
            substitutions.append((k, ", ".join(manques + gains)))
        else:
            perdus.append((k, ", ".join(manques)))

    déséquilibrés = [k for k in structurelles if k.endswith("|groupes")
                     and b[k] != "équilibré"]

    print(f"disparues {len(disparues)} | apparues {len(apparues)} "
          f"| modifiées {len(modifiees)}")
    print(f"  dont vidées {len(vidées)} | remplies {len(remplies)}")
    print(f"structure : {len(structurelles)} changements "
          f"| segments perdus {len(perdus)} | substitués {len(substitutions)} "
          f"| groupes déséquilibrés {len(déséquilibrés)}")
    for k in vidées[:25]:
        print(f"   VIDÉE  {k}  |  {a[k][:60]!r}")
    for k in disparues[:15]:
        print(f"   PERDUE {k}  |  {a[k][:60]!r}")
    for k, manques in perdus[:25]:
        print(f"   SEGMENT {k}  |  {manques}")
    for k, echange in substitutions[:10]:
        print(f"   ÉCHANGE {k}  |  {echange}")
    for k in déséquilibrés[:15]:
        print(f"   GROUPES {k}  |  {a[k]} -> {b[k]}")
    for k in structurelles[:10]:
        connus = {p for p, _ in perdus} | {p for p, _ in substitutions}
        if k.endswith("|segments") and k not in connus:
            print(f"   s      {k}\n            {a[k][:70]!r}\n         -> {b[k][:70]!r}")
    for k in modifiees[:15]:
        if k not in vidées:
            print(f"   ~      {k}\n            {a[k][:70]!r}\n         -> {b[k][:70]!r}")
    return 1 if (vidées or disparues or perdus or déséquilibrés) else 0


def main() -> int:
    if len(sys.argv) == 2:
        state = capture()
        with open(sys.argv[1], "w") as f:
            json.dump(state, f)
        erreurs = sum(1 for v in state.values() if "erreur" in v)
        vides = sum(1 for v in state.values() if v.get("vide"))
        bancals = sum(1 for v in state.values()
                      if v.get("groupes") not in (None, "équilibré"))
        print(f"capturé {len(state)} rendus ({len(SEEDS)} graines) "
              f"| erreurs {erreurs} | énoncés vides {vides} "
              f"| groupes déséquilibrés {bancals} -> {sys.argv[1]}")
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
