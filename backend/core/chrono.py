"""Server-side chronometer for exercise scoring.

WIMS modules declare a chronometer via ``!default scoredelay=T1[,T2]`` in
``intro.phtml`` (seconds). T1 = soft limit (score starts decreasing); T2 =
hard limit (score = 0). Below T1 the student keeps the full score; between
T1 and T2 the score is multiplied by a linear factor going from 1 to 0;
beyond T2 the multiplier is 0.

Persistence: per-``(user, exercise, seed)`` start-timestamp in Redis with
a TTL that comfortably exceeds T2. No DB table — the chrono is purely a
timer-state concern, and Redis ephemerality means abandoned sessions
self-clean. (If the same student re-opens with the same seed before TTL
expiry, the original ``started_at`` is reused — refresh-resistant.)

All timing decisions stay on the server. The render endpoint sends the
canonical ``started_at`` and the two thresholds; the front-end only uses
them to render a visual countdown.
"""

from __future__ import annotations

import logging
import os
import re
from dataclasses import dataclass
from datetime import datetime, timezone

logger = logging.getLogger(__name__)


# ── Module-level scoredelay (parsed from intro.phtml) ────────────────────────


@dataclass(frozen=True)
class Scoredelay:
    soft: int  # T1 — score starts decreasing after this many seconds
    hard: int  # T2 — score is zero past this many seconds (hard >= soft)


# Parsed value cached per module directory.
_SCOREDELAY_CACHE: dict[str, Scoredelay | None] = {}

_SCOREDELAY_RE = re.compile(
    r"^\s*!default\s+scoredelay\s*=\s*(\d+)(?:\s*,\s*(\d+))?",
    re.IGNORECASE | re.MULTILINE,
)


def _parse_scoredelay(text: str) -> Scoredelay | None:
    """Extract T1[,T2] from an ``intro.phtml`` text. Returns None if absent."""
    m = _SCOREDELAY_RE.search(text)
    if not m:
        return None
    soft = int(m.group(1))
    hard = int(m.group(2)) if m.group(2) else soft
    if hard < soft:
        hard = soft  # be defensive: WIMS UI normally validates this
    return Scoredelay(soft=soft, hard=hard)


def module_scoredelay(def_path: str | None) -> Scoredelay | None:
    """Return the chrono config for the module owning this .def file, or None.

    Looks up ``<module_dir>/intro.phtml`` where module_dir is the .def's
    grandparent (``.../foo.fr/def/exo.def`` → ``.../foo.fr/``). Result is
    cached in-process so each module is read at most once.
    """
    if not def_path:
        return None
    module_dir = os.path.dirname(os.path.dirname(def_path))
    if module_dir in _SCOREDELAY_CACHE:
        return _SCOREDELAY_CACHE[module_dir]

    intro_path = os.path.join(module_dir, "intro.phtml")
    result: Scoredelay | None = None
    if os.path.isfile(intro_path):
        try:
            with open(intro_path, encoding="utf-8") as f:
                result = _parse_scoredelay(f.read())
        except UnicodeDecodeError:
            with open(intro_path, encoding="cp1252") as f:
                result = _parse_scoredelay(f.read())
        except OSError as exc:
            logger.debug("chrono: could not read %s (%s)", intro_path, exc)

    _SCOREDELAY_CACHE[module_dir] = result
    return result


# ── Session store (Redis-backed) ──────────────────────────────────────────────


def _redis():
    """Lazy Redis client shared with render_cache. None if Redis is down."""
    from core.oef.render_cache import _redis_client  # noqa: PLC0415
    return _redis_client()


def _session_key(user_id: str, exercise_id: str, seed: int) -> str:
    return f"pax:chrono:{user_id}:{exercise_id}:{seed}"


def get_or_create_started_at(
    user_id: str,
    exercise_id: str,
    seed: int,
    scoredelay: Scoredelay,
) -> datetime:
    """Return ``started_at`` for this (user, exercise, seed) triple.

    First call seeds Redis with ``now()``; subsequent calls return the same
    timestamp (refresh-resistant chrono). TTL is ``max(hard*2, 1800)`` so
    a slow student well past T2 still finds their session, but abandoned
    sessions disappear within ~30 minutes to an hour.
    """
    r = _redis()
    now = datetime.now(timezone.utc)
    if r is None:
        # No Redis → degrade gracefully: treat this render as the start.
        # No persistence means refresh resets the chrono; in practice Redis
        # is part of the standard pax stack, so this is just a safety net.
        return now

    key = _session_key(user_id, exercise_id, seed)
    ttl = max(scoredelay.hard * 2, 1800)
    try:
        existing = r.get(key)
        if existing:
            return datetime.fromisoformat(existing.decode("utf-8"))
        r.setex(key, ttl, now.isoformat())
    except Exception as exc:
        logger.debug("chrono session r/w error: %s", exc)
    return now


def read_started_at(user_id: str, exercise_id: str, seed: int) -> datetime | None:
    """Return the stored ``started_at`` for scoring on ``/check``, or None.

    None means "no session found" — the chrono shouldn't penalise the
    student (could be Redis loss, or they hit /check without /render).
    Caller decides whether that means full score or zero.
    """
    r = _redis()
    if r is None:
        return None
    try:
        data = r.get(_session_key(user_id, exercise_id, seed))
        if data:
            return datetime.fromisoformat(data.decode("utf-8"))
    except Exception as exc:
        logger.debug("chrono read error: %s", exc)
    return None


# ── Score multiplier ──────────────────────────────────────────────────────────


def score_factor(elapsed_seconds: float, scoredelay: Scoredelay) -> float:
    """Linear score multiplier from elapsed time.

    elapsed ≤ T1       → 1.0  (full score)
    T1 < elapsed < T2  → (T2 - elapsed) / (T2 - T1)
    elapsed ≥ T2       → 0.0

    Edge case T1 == T2 (single threshold): below the threshold = 1.0, at-or-
    above = 0.0 — a cliff rather than a ramp, matching WIMS' behaviour when
    the author specified only T1.
    """
    if elapsed_seconds <= scoredelay.soft:
        return 1.0
    if elapsed_seconds >= scoredelay.hard:
        return 0.0
    span = scoredelay.hard - scoredelay.soft
    if span <= 0:
        return 0.0  # cliff (T1 == T2)
    return (scoredelay.hard - elapsed_seconds) / span
