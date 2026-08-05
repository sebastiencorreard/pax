#!/usr/bin/env python3
"""Vérifie les exercices sentinelles du refactoring de découpage.

Le protocole de `docs/refactor-item-splitting.md` (§5.3) nomme une poignée
d'exercices dont on connaît la bonne valeur, chacun ayant payé une régression :
une moyenne fausse, un menu vidé, une palette tronquée. Les vérifier à la main
après chaque phase revenait à relire six rendus ; ce script les lit dans une
capture de `corpus_state.py`.

    python3 scripts/corpus_state.py /tmp/apres.json
    python3 scripts/sentinelles.py /tmp/apres.json

Sortie non nulle si l'une des sentinelles a bougé.
"""

import json
import sys

SEED = 42


def _find(state: dict, fragment: str, seed: int = SEED):
    for key, value in state.items():
        if fragment in key and key.endswith(f"@{seed}"):
            return value
    return None


def _expected(entry: dict) -> list[str]:
    return [a["attendu"] for a in entry["reponses"].values()] if entry else []


def check(state: dict) -> list[tuple[str, bool, object]]:
    out = []

    mean = _find(state, "oefstat.fr/def/mean.def")
    vals = _expected(mean)
    out.append(("oefstat/mean = 3.973684211",
                any("3.97368421" in (v or "") for v in vals), vals))

    symax2 = _find(state, "transform.fr/def/symax2.def")
    palettes = [len(a["palette"]) for a in symax2["reponses"].values()] if symax2 else []
    out.append(("transform/symax2 = menu à 20 options", 20 in palettes, palettes))

    boucle = _find(state, "def/bouclefor1.def")
    out.append(("oefpython/bouclefor1 = rang 3",
                _expected(boucle) == ["3"], _expected(boucle)))

    conc = _find(state, "moles.fr/def/concentration1.def")
    vals = _expected(conc)
    out.append(("moles.fr/concentration1 : val14 en mol",
                bool(vals) and "mol" in (vals[0] or ""), vals[:2]))

    decl = _find(state, "mathelexikon1.fr/def/Declinaisons.def")
    n = len(decl["reponses"]) if decl else 0
    out.append(("mathelexikon/Declinaisons = 13 champs", n == 13, n))

    lewis = _find(state, "oefmolecule.fr/def/lewis.def")
    champs = len(lewis["reponses"]) if lewis else 0
    etiquettes = max((len(a["palette"]) for a in lewis["reponses"].values()),
                     default=0) if lewis else 0
    out.append(("oefmolecule/lewis = 7 champs, 18 étiquettes",
                (champs, etiquettes) == (7, 18), (champs, etiquettes)))

    return out


def main() -> int:
    if len(sys.argv) != 2:
        print(__doc__)
        return 2
    with open(sys.argv[1]) as f:
        state = json.load(f)
    results = check(state)
    for label, ok, detail in results:
        print(f"{'  OK  ' if ok else ' ÉCHEC'} {label}  →  {detail}")
    return 0 if all(ok for _, ok, _ in results) else 1


if __name__ == "__main__":
    sys.exit(main())
