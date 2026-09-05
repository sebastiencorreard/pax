#!/usr/bin/env python3
"""Combien d'étapes le corpus cache-t-il derrière la première, et à quel prix ?

La suite lente ne rend que `m_step=1`. Cette sonde parcourt un exercice comme
un élève le ferait : bonne réponse à chaque étape, puis on demande au moteur
s'il en reste une — la question que `etape_suivante_existe` pose déjà en
production.
"""
import collections, contextlib, io, os, random, sys, time
sys.path.insert(0, "/app")
sys.path.insert(0, "/app/tests")
from core.oef.engine import load_and_render
from core.oef.def_engine.analyze import etape_suivante_existe
from tests import test_exercises_check as T

SEED = 42
MAX = 40          # large, pour distinguer un exercice long d'une boucle
# `ECHANTILLON=9999` pour tout le corpus ; une centaine suffit à jauger.
ECHANTILLON = int(os.environ.get("ECHANTILLON", "120"))

chemins = sorted(
    os.path.join(r, f)
    for r, _, fs in os.walk("/ressources") for f in fs if f.endswith(".oef")
)
random.Random(7).shuffle(chemins)

profondeurs = collections.Counter()
temps_total = 0.0
n_dyn = 0
lents = []
plafonnes = []

for p in chemins:
    o, e = io.StringIO(), io.StringIO()
    try:
        with contextlib.redirect_stdout(o), contextlib.redirect_stderr(e):
            r = load_and_render(p, seed=SEED)
    except Exception:
        continue
    if not r.is_dynsteps:
        continue
    n_dyn += 1
    if n_dyn > ECHANTILLON:
        break

    t0 = time.monotonic()
    etape, cumul = 1, {}
    while etape <= MAX:
        rep = {a.input_name: T._meilleure_reponse(a) for a in r.answers}
        cumul.update(rep)
        with contextlib.redirect_stdout(o), contextlib.redirect_stderr(e):
            suivante = etape_suivante_existe(r, rep, SEED, etape)
        # Même règle que le front : on avance tant que l'estimation du rendu
        # laisse de la place, ou que le serveur annonce une étape de plus.
        if not (etape < (r.total_steps or 1) or suivante is True):
            break
        etape += 1
        try:
            with contextlib.redirect_stdout(o), contextlib.redirect_stderr(e):
                r = load_and_render(p, seed=SEED, m_step=etape, prev_replies=cumul)
        except Exception:
            break
    d = time.monotonic() - t0
    temps_total += d
    profondeurs[etape] += 1
    court = p.replace("/ressources/", "")
    if d > 3: lents.append((round(d, 1), etape, court))
    if etape > MAX - 1: plafonnes.append(court)

print(f"échantillon : {min(n_dyn, ECHANTILLON)} exercices dynsteps\n")
print("étapes parcourues :")
for k in sorted(profondeurs):
    print(f"   {k:2} étape(s) : {profondeurs[k]:4} exercices")
total_rendus = sum(k * v for k, v in profondeurs.items())
print(f"\nrendus au total  : {total_rendus}  (contre {sum(profondeurs.values())} aujourd'hui)")
print(f"facteur          : ×{total_rendus / max(1, sum(profondeurs.values())):.2f}")
print(f"temps            : {temps_total:.1f}s, soit {temps_total / max(1, sum(profondeurs.values())):.2f}s par exercice")
print(f"\nles plus lents ({len(lents)}) :")
for d, k, c in sorted(lents, reverse=True)[:10]:
    print(f"   {d:6}s  {k:2} étapes  {c}")
if plafonnes:
    print(f"\nplafonnés à {MAX} étapes ({len(plafonnes)}) — parcours qui ne se termine pas :")
    for c in plafonnes[:8]: print("   ", c)

# Relevé du 2026-09-05, sur les 634 exercices `dynsteps` du corpus :
#
#     rendus     634 → 1319   (×2,08)
#     temps      69 s, soit 0,11 s par exercice
#     plus long  15 étapes ; aucun parcours ne diverge
#     plus lent  histocap, 27,6 s pour ses 6 étapes
