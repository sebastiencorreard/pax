import os
from pydantic import field_validator
from pydantic_settings import BaseSettings

_REPO_ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))

# Known placeholder secrets that must never reach a running app. Anything in
# this set (case-insensitive prefix match) is rejected at startup.
# Prefixes that appear in .env templates / documentation. Reject them so an
# operator can't ship a copy-pasted placeholder. We deliberately do NOT
# include `dev-only-*` here: that's the convention for the committed
# docker-compose.override.yml, which only loads in local dev.
_FORBIDDEN_SECRET_PREFIXES = ("changeme", "your-", "placeholder")
# Minimum entropy for the JWT key. 32 raw bytes is the floor for HMAC-SHA256.
_MIN_SECRET_LEN = 32


class Settings(BaseSettings):
    # Base de données
    database_url: str = "postgresql+asyncpg://pax:pax@localhost:5432/pax"

    # Redis
    redis_url: str = "redis://localhost:6379/0"

    # Sécurité — REQUIRED. No default: the app refuses to start if SECRET_KEY
    # is absent or matches a known placeholder. Generate with
    # `openssl rand -hex 32`. In dev, set it in docker-compose.override.yml;
    # in prod, in the root .env loaded by docker-compose.prod.yml.
    secret_key: str
    algorithm: str = "HS256"
    access_token_expire_minutes: int = 60

    # CORS
    cors_origins: list[str] = ["http://localhost:3000"]

    # Ressources OEF
    resources_root: str = os.path.join(_REPO_ROOT, "ressources")

    # WIMS
    wims_home: str = "/var/lib/wims"
    oef2wims_bin: str = "/var/lib/wims-svn/wims/bin/oef2wims"

    # Keycloak
    keycloak_url: str = "http://localhost:8180"
    keycloak_realm: str = "pax"
    keycloak_client_id: str = "pax-backend"

    # CAS
    maxima_bin: str = "/usr/bin/maxima"
    cas_timeout_seconds: float = 3.0

    # Debug — exposes /api/render/{id}/debug (the endpoint that leaks the
    # expected answer to support the front-end "Réponse auto" button).
    # Off by default; set PAX_DEBUG=1 in dev environments only.
    pax_debug: bool = False

    # Corrigé — écrit la bonne réponse dans la convention décimale de la langue
    # de l'exercice (`4,76` en français, cf. `core/oef/i18n.py`) au lieu du
    # point brut que sort le moteur. Confort d'affichage, pas une règle du
    # moteur : la notation, elle, accepte les deux écritures dans tous les cas.
    # Mettre PAX_LOCALIZE_FEEDBACK=0 pour revenir au point partout — utile pour
    # comparer un rendu à WIMS, qui n'y localise rien.
    pax_localize_feedback: bool = True

    @field_validator("secret_key")
    @classmethod
    def _validate_secret_key(cls, v: str) -> str:
        if len(v) < _MIN_SECRET_LEN:
            raise ValueError(
                f"SECRET_KEY must be at least {_MIN_SECRET_LEN} characters; "
                "generate one with `openssl rand -hex 32`"
            )
        low = v.lower()
        for bad in _FORBIDDEN_SECRET_PREFIXES:
            if low.startswith(bad):
                raise ValueError(
                    f"SECRET_KEY starts with the placeholder '{bad}'. "
                    "Generate a real one with `openssl rand -hex 32`."
                )
        return v


settings = Settings()  # type: ignore[call-arg]  # secret_key from env
