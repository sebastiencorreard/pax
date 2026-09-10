"""Les exercices dont le rendu frôle ou dépasse le budget temps.

Au-delà de `_RENDER_TIME_BUDGET` (8 s), le moteur abandonne le calcul des
variables **sans rien lever** et poursuit avec l'état partiel. Le rendu dépend
alors de la vitesse de la machine : `oefSpectroscopie/Infra-rouge5` prend
9,3 s sur un poste, rend sans son dessin ni son widget, et moins de 8 s en CI,
où il rend tout — son snapshot ne pouvait être juste des deux côtés.

Cette sonde rend chaque exercice (graine 42, sans cache) avec un budget
illimité, mesure sa durée, et note ceux qui dépassent un seuil. À lancer sur
une machine **au repos** : une mesure faite sous charge surestime tout.

    docker compose exec -T backend python scripts/sonde_budget.py [seuil_s] [niveau…]
"""
import os
import sys
import time

sys.path.insert(0, os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
os.environ.setdefault("PAX_WIMS_NOW", "20260101.12:00:00")

import core.oef.def_engine as E  # noqa: E402
from core.oef.engine import find_def_path  # noqa: E402
from tests import corpus  # noqa: E402

seuil = float(sys.argv[1]) if len(sys.argv) > 1 else 3.0
niveaux = set(sys.argv[2:])
budget = E._RENDER_TIME_BUDGET
E._RENDER_TIME_BUDGET = 3600.0

lents = []
n = 0
for ex_id, chemin in corpus.exercises():
    if niveaux and ex_id.split("~", 1)[0] not in niveaux:
        continue
    n += 1
    t = time.monotonic()
    try:
        E.load_and_render(find_def_path(chemin), seed=42)
    except Exception:  # noqa: BLE001 — un rendu cassé relève d'un autre relevé
        pass
    duree = time.monotonic() - t
    if duree >= seuil:
        lents.append((duree, ex_id))

lents.sort(reverse=True)
print(f"RENDUS {n} · budget {budget} s · seuil {seuil} s")
print(f"AU-DELA_DU_BUDGET {sum(1 for d, _ in lents if d > budget)}")
for duree, ex_id in lents:
    print(f"LENT {duree:6.2f} {'>' if duree > budget else ' '} {ex_id}")
