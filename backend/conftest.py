"""Pytest setup that runs before any test module imports.

The app refuses to start without a real ``SECRET_KEY`` (validator in
``config.py``); tests that import the FastAPI app or the ORM models
trigger that validator at import time, so we plant a strong dummy value
here instead of relying on the developer's shell.
"""

import os

os.environ.setdefault(
    "SECRET_KEY",
    # 64-char random hex — passes the validator and is obviously a test key.
    "0123456789abcdef" * 4,
)

# `$wims_now` est l'horloge de la session WIMS ; `quizzautomat.fr/var.proc` en
# tire `oefenv_year`, que `pcent5` imprime dans son énoncé. Sans horloge fixe,
# son snapshot serait périmé au changement d'année — la panne serait datée du
# 1er janvier, sans rapport avec un changement de code. On gèle donc l'instant
# pour toute la suite ; `_horloge_session` relit cette variable à chaque rendu.
os.environ.setdefault("PAX_WIMS_NOW", "20260101.12:00:00")
