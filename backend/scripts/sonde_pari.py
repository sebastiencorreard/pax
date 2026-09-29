#!/usr/bin/env python3
"""Les expressions que le corpus soumet à `!exec pari`, et ce que PAX en fait.

L'entrée du banc PARI (`scripts/banc_pari/`) : chaque exercice est rendu
(graine 42), `_call_pari` enveloppé relève l'expression, la sortie de PAX et
l'exercice. On garde la première occurrence de chaque expression distincte.

    docker compose exec -T redis redis-cli FLUSHDB
    docker compose exec -T backend python scripts/sonde_pari.py > pari.json

Le JSON sorti est une liste de `{"expr", "pax", "exo", "session"}` ;
`session` dit si la session `gp` de l'exercice portait déjà un état — une
telle expression ne se compare pas au banc, qui lance un `gp` par expression.
"""
import contextlib
import io
import json
import multiprocessing
import os
import sys

sys.path.insert(0, "/app")

RACINE = os.environ.get("RESOURCES_ROOT", "/ressources")
GRAINE = int(os.environ.get("SONDE_SEED", "42"))


def _un(chemin: str) -> list[dict]:
    import core.oef.def_engine as de  # noqa: PLC0415
    from core.oef.engine import load_and_render  # noqa: PLC0415

    vus: list[dict] = []
    reel = de._call_pari

    def enveloppe(expr, session=None, rng=None):
        avant = bool(session)
        try:
            sortie = reel(expr, session=session, rng=rng)
        except Exception as e:  # noqa: BLE001
            sortie = f"<{type(e).__name__}>"
        vus.append({"expr": expr, "pax": sortie, "session": avant})
        return sortie

    de._call_pari = enveloppe
    try:
        with contextlib.redirect_stdout(io.StringIO()), contextlib.redirect_stderr(io.StringIO()):
            load_and_render(chemin, seed=GRAINE)
    except Exception:  # noqa: BLE001, S110
        pass
    finally:
        de._call_pari = reel
    court = chemin.replace(RACINE + "/", "")
    for v in vus:
        v["exo"] = court
    return vus


def main() -> int:
    tous = sorted(
        os.path.join(r, f)
        for r, _, fs in os.walk(RACINE)
        for f in fs
        if f.endswith(".oef")
    )
    filtre = os.environ.get("PAX_TEST_CORPUS")
    if filtre:
        tous = [p for p in tous if filtre in p]
    distinctes: dict[str, dict] = {}
    with multiprocessing.Pool(int(os.environ.get("SONDE_JOBS", "8"))) as pool:
        for i, vus in enumerate(pool.imap_unordered(_un, tous, chunksize=8), 1):
            for v in vus:
                distinctes.setdefault(v["expr"], v)
            if i % 1000 == 0:
                print(f"  … {i}/{len(tous)}", file=sys.stderr, flush=True)
    json.dump(sorted(distinctes.values(), key=lambda v: v["expr"]), sys.stdout,
              ensure_ascii=False, indent=0)
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
