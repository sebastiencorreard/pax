from pydantic_settings import BaseSettings


class Settings(BaseSettings):
    # Base de données
    database_url: str = "postgresql+asyncpg://pax:pax@localhost:5432/pax"

    # Redis
    redis_url: str = "redis://localhost:6379/0"

    # Sécurité
    secret_key: str = "changeme"
    algorithm: str = "HS256"
    access_token_expire_minutes: int = 60

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

    class Config:
        env_file = ".env"


settings = Settings()
