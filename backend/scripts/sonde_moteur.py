#!/usr/bin/env python3
"""Ce que le moteur laisse tomber, mesuré en rendant tout le corpus.

Les inventaires du TODO (partie I.1) sortent d'ici. Le relevé statique — lire
les sources et compter les occurrences — sur-rapporte systématiquement : une
commande écrite dans un `.phtml` de module n'est jamais exécutée par le moteur
d'exercices, un type déclaré dans un `.def` peut être masqué avant le dispatch.
Seul le rendu dit la vérité.

**Vider le cache avant de lancer**, sans quoi la sonde mesure des rendus
d'hier :

    docker compose exec redis redis-cli FLUSHDB
    docker compose exec backend python scripts/sonde_moteur.py

Compter une vingtaine de minutes. Le moteur ne lève pas d'exception : il rend
une chaîne vide, un `NaN`, un énoncé sans question. C'est pourquoi la sonde
compte des symptômes plutôt que des erreurs.
"""
import collections
import contextlib
import io
import os
import re
import sys

sys.path.insert(0, "/app")
from core.oef.engine import load_and_render  # noqa: E402

RACINE = os.environ.get("RESOURCES_ROOT", "/ressources")
GRAINE = int(os.environ.get("SONDE_SEED", "1"))
UNK = re.compile(r"UNKNOWN_CMD:([a-z_0-9]+)", re.I)


def chemins() -> list[str]:
    return sorted(
        os.path.join(r, f)
        for r, _, fs in os.walk(RACINE)
        for f in fs
        if f.endswith(".oef")
    )


def main() -> int:
    cmds = collections.Counter()
    figures = collections.defaultdict(set)
    sans_reponse: list[str] = []
    analyze: list[str] = []
    erreurs = collections.Counter()
    exemple_err: dict[str, tuple[str, str]] = {}
    tous = chemins()

    for i, p in enumerate(tous, 1):
        # Le moteur journalise ses défauts sur stdout/stderr au lieu de les
        # lever ; on les capte à la source pour les rattacher à leur exercice.
        out, err = io.StringIO(), io.StringIO()
        try:
            with contextlib.redirect_stdout(out), contextlib.redirect_stderr(err):
                r = load_and_render(p, seed=GRAINE)
        except Exception as e:  # noqa: BLE001 — on veut la famille, pas la trace
            erreurs[type(e).__name__] += 1
            exemple_err.setdefault(type(e).__name__, (p, str(e)[:200]))
            continue

        court = p.replace(RACINE + "/", "")
        for ligne in err.getvalue().splitlines():
            if "FLYDRAW-UNHANDLED" in ligne:
                figures[court].add(ligne.split("]", 1)[1].strip().split()[0])

        blob = " ".join(
            filter(
                None,
                [
                    r.statement_html or "",
                    r.solution_html or "",
                    r.hint_html or "",
                    " ".join((a.expected or "") for a in r.answers),
                ],
            )
        )
        for m in UNK.finditer(blob):
            cmds[m.group(1).lower()] += 1

        if not r.answers:
            sans_reponse.append(court)
        elif any((a.answer_type or "").lower() == "analyze" for a in r.answers):
            analyze.append(court)

        if i % 500 == 0:
            print(f"  … {i}/{len(tous)}", file=sys.stderr, flush=True)

    print(f"\n=== {len(tous)} exercices, graine {GRAINE} ===\n")
    print(f"commandes inconnues (UNKNOWN_CMD) : {sum(cmds.values())}")
    for c, k in cmds.most_common():
        print(f"    {c:20} {k}")
    print(f"exceptions au rendu               : {sum(erreurs.values())}")
    for c, k in erreurs.most_common():
        chemin, msg = exemple_err[c]
        print(f"    {c:20} {k:5}  ex. {chemin}\n        {msg}")
    print(f"exercices sans aucune réponse     : {len(sans_reponse)}")
    for c in sans_reponse:
        print(f"    {c}")
    print(f"exercices notés par :test         : {len(analyze)}")
    print(f"exercices à primitive non traitée : {len(figures)}")
    for c in sorted(figures):
        print(f"    {c:56} {' '.join(sorted(figures[c]))}")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
