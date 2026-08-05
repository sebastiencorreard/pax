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

import re

# The only thing to edit when adding a comma-decimal language (e.g. "de", "es").
COMMA_DECIMAL_LANGS = {"fr", "nl"}

# A decimal point, i.e. one *between two digits* — `1.5`, never the dot of
# `fig.2`, of a `3.10` version string or of an `x2.png` filename. Same guard as
# `def_engine/presentation.py`, which localises the statement.
_DECIMAL_DOT_RE = re.compile(r"(?<=\d)\.(?=\d)")


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


def localize_decimals(s: str, lang: str | None) -> str:
    """Rewrite decimal points as the separator ``lang`` writes them.

    Only a dot **between two digits** is touched, so a filename (``x2.png``),
    a version (``3.10``) or a sentence's full stop survives intact. Nothing
    else is rewritten — in particular not the list separator, which cannot be
    told apart from a decimal comma once the conversion has happened.

    Idempotent, and a no-op for dot-decimal languages.
    """
    if not s or not uses_comma_decimal(lang):
        return s
    return _DECIMAL_DOT_RE.sub(",", s)
