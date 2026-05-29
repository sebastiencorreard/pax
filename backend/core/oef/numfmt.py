"""Number-to-string formatting shared across the OEF / .def pipelines.

WIMS stores reals as C ``double`` and prints them with limited precision, which
hides binary floating-point artefacts: ``2 + 0.9 + 0.05`` is
``2.9499999999999997`` but WIMS shows ``2.95``. We mirror that with 12
significant digits — well below a double's ~16-digit noise floor yet far above
any precision a school exercise needs. Integers stay integers (``7.0`` → ``7``).

This is locale-agnostic: it always emits a dot decimal. Locale-aware separator
substitution happens later, at the display boundary (see ``core/oef/i18n.py``).
"""

from __future__ import annotations


def format_wims_float(value: float) -> str:
    """Format a Python float the way WIMS would print it (noise-free)."""
    if value.is_integer():
        return str(int(value))
    return f"{value:.12g}"
