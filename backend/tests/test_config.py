"""Settings validation tests — particularly the SECRET_KEY guard rails."""

import pytest
from pydantic import ValidationError

from config import Settings


def _build(monkeypatch: pytest.MonkeyPatch, value: str) -> Settings:
    """Construct Settings with SECRET_KEY pinned via env, no .env loaded."""
    monkeypatch.setenv("SECRET_KEY", value)
    return Settings(_env_file=None)  # type: ignore[call-arg]


class TestSecretKeyValidator:
    def test_accepts_long_random(self, monkeypatch: pytest.MonkeyPatch):
        v = "e22ffd92f4b9fa1275b95ce12f2a74c3ab8c6faaba87a3f56c71ed82bdbfacfa"
        s = _build(monkeypatch, v)
        assert s.secret_key == v

    def test_rejects_too_short(self, monkeypatch: pytest.MonkeyPatch):
        with pytest.raises(ValidationError, match="at least 32 characters"):
            _build(monkeypatch, "abc")

    def test_rejects_changeme(self, monkeypatch: pytest.MonkeyPatch):
        with pytest.raises(ValidationError, match="placeholder"):
            _build(monkeypatch, "changeme" + "x" * 56)

    def test_rejects_case_insensitive_placeholder(
        self, monkeypatch: pytest.MonkeyPatch
    ):
        # "ChAnGeMe…" would slip past a naive ==-check.
        with pytest.raises(ValidationError, match="placeholder"):
            _build(monkeypatch, "ChAnGeMe" + "x" * 56)

    def test_dev_only_prefix_is_allowed(self, monkeypatch: pytest.MonkeyPatch):
        # The committed docker-compose.override.yml uses a `dev-only-…`
        # value; the validator lets it through because that file only
        # applies to local dev. Length floor still applies.
        v = "dev-only-key-DO-NOT-USE-IN-PRODUCTION"
        s = _build(monkeypatch, v)
        assert s.secret_key == v
