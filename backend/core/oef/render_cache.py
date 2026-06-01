"""
Cache Redis pour ExerciseRender.

Évite le double rendu render→check pour le même (path, seed, m_step).
Utilise pickle : ExerciseRender contient des objets dataclass du parser
(check_sections.postdef/test/feedback) non trivialement sérialisables en JSON.

TTL : 600 s (10 min). Couvre amplement le cycle render→answer→check d'un élève.
Toutes les erreurs Redis sont silencieuses : le cache est best-effort.
"""

from __future__ import annotations

import logging
import pickle

logger = logging.getLogger(__name__)

CACHE_TTL = 600  # secondes


def _get_redis():
    """Retourne un client Redis synchrone, ou None si indisponible."""
    try:
        import redis
        from config import settings
        client = redis.Redis.from_url(settings.redis_url, socket_connect_timeout=1)
        client.ping()
        return client
    except Exception as exc:
        logger.debug("render_cache: Redis indisponible (%s)", exc)
        return None


# Client initialisé une seule fois par processus (lazy).
_redis = None
_redis_checked = False


def _redis_client():
    global _redis, _redis_checked
    if not _redis_checked:
        _redis = _get_redis()
        _redis_checked = True
    return _redis


def cache_key(
    path: str, seed: int, m_step: int | None, prev_replies: dict[str, str] | None = None
) -> str:
    # Course steps that echo previous replies (`$m_reply{n}`) render differently
    # per submitted answer, so the replies are part of the key.
    rep = ""
    if prev_replies:
        rep = ":" + ";".join(f"{k}={v}" for k, v in sorted(prev_replies.items()))
    return f"pax:render:{path}:{seed}:{m_step or 0}{rep}"


def get(key: str):
    """Retourne l'ExerciseRender mis en cache, ou None."""
    r = _redis_client()
    if r is None:
        return None
    try:
        data = r.get(key)
        if data:
            return pickle.loads(data)
    except Exception as exc:
        logger.debug("render_cache get error: %s", exc)
    return None


def set(key: str, rendered) -> None:
    """Met en cache rendered sous key avec TTL."""
    r = _redis_client()
    if r is None:
        return
    try:
        r.setex(key, CACHE_TTL, pickle.dumps(rendered, protocol=pickle.HIGHEST_PROTOCOL))
    except Exception as exc:
        logger.debug("render_cache set error: %s", exc)
