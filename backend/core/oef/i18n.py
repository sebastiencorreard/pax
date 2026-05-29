"""Locale-driven number formatting conventions.

Some languages write decimals with a comma (``3,93``) and therefore use a
semicolon to separate list elements, so the two roles never collide — the
spreadsheet convention (Excel ``fr`` uses ``;`` because ``,`` is the decimal
separator). Others (``en``) use a dot for decimals and a comma for lists.

This module is the **single source of truth** for that choice. To support a new
language whose decimal separator is the comma, add its ISO code to
``COMMA_DECIMAL_LANGS`` — nothing else needs to change.
"""

from __future__ import annotations

# The only thing to edit when adding a comma-decimal language (e.g. "de", "es").
COMMA_DECIMAL_LANGS = {"fr", "nl"}


def _base(lang: str | None) -> str:
    """Bare language code, lowercased: ``fr-BE`` → ``fr``. Defaults to ``fr``."""
    return (lang or "fr").split("-")[0].strip().lower()


def uses_comma_decimal(lang: str | None) -> bool:
    """True if ``lang`` writes decimals with a comma."""
    return _base(lang) in COMMA_DECIMAL_LANGS


def decimal_separator(lang: str | None) -> str:
    """Decimal separator for ``lang``: ``","`` for comma-decimal locales, else ``"."``."""
    return "," if uses_comma_decimal(lang) else "."


def list_separator(lang: str | None) -> str:
    """List/element separator for ``lang``: ``";"`` for comma-decimal locales, else ``","``.

    Paired with :func:`decimal_separator` so the decimal and list separators are
    always distinct within a locale, which is what disambiguates ``2,5`` (one
    decimal) from a two-element list (``2;5`` in comma-decimal locales).
    """
    return ";" if uses_comma_decimal(lang) else ","
