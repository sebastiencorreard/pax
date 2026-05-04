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
