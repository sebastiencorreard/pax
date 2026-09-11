"""Number-to-string formatting shared across the OEF / .def pipelines.

Deux écritures, qu'il ne faut pas confondre.

``wims_float2str`` est le portage de ``float2str`` (``src/evalue.c``), par
lequel WIMS écrit tout réel sorti de ``$[…]``, ``!values``, ``!makelist``, d'une
variable de ``!for``… : un entier strictement compris entre -10⁶ et 10⁶
s'écrit en entier, tout le reste en ``%.<print_precision>g``. Pour un exercice
OEF, ``print_precision`` vaut 8 (``oef/var.proc``). D'où ``$[1/3]`` →
``0.33333333`` et ``$[123456789]`` → ``1.2345679e+08``.

``format_wims_float`` est une écriture **propre à PAX**, pour ce que le moteur
affiche lui-même hors de ces commandes (corrigés des vérificateurs, résultats
SymPy de l'émulation Maxima, notes) : 12 chiffres significatifs, assez peu pour
masquer le bruit binaire (``2 + 0.9 + 0.05`` vaut ``2.9499999999999997``, écrit
``2.95``), et tout entier en entier (``7.0`` → ``7``). On l'a longtemps crue
fidèle à WIMS ; elle ne l'est pas — ``float2str`` le montre.

Both are locale-agnostic: they always emit a dot decimal. Locale-aware separator
substitution happens later, at the display boundary (see ``core/oef/i18n.py``).
"""

from __future__ import annotations

import math

# `print_precision` d'un exercice OEF : `oef/var.proc` pose
# `!default print_precision=8` puis `wims_print_precision=$print_precision`,
# que `var.c` recopie dans la globale lue par `float2str`. Aucun `.def` du
# corpus ne la change.
PRINT_PRECISION_OEF = 8


def format_wims_float(value: float) -> str:
    """Écriture sans bruit, sur 12 chiffres, des nombres que PAX affiche lui-même."""
    if value.is_integer():
        return str(int(value))
    return f"{value:.12g}"


def wims_float2str(d: float, precision: int = PRINT_PRECISION_OEF) -> str:
    """``float2str`` de ``src/evalue.c``, à la lettre.

        if(d==0) → "0"
        if(!isfinite(d)) → "Inf", "-Inf" ou "NaN"
        if(d<1000000 && d>-1000000 && d==floor(d)) → int2str(d)
        sinon snprintf("%.<i>g"), i = print_precision borné à [2, 32]

    Un entier Python y passe comme un réel : chez WIMS, `evalue` rend toujours
    un `double`.
    """
    try:
        d = float(d)
    except OverflowError:
        return "Inf" if d > 0 else "-Inf"
    if d == 0:
        return "0"
    if not math.isfinite(d):
        if d == d:
            return "Inf" if d > 0 else "-Inf"
        return "NaN"
    if -1000000 < d < 1000000 and d == math.floor(d):
        return str(int(d))
    precision = min(max(precision, 2), 32)
    return f"{d:.{precision}g}"
