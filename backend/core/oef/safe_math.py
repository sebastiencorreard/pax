"""Garde-fou contre l'exécution de code par une expression non fiable.

`sympify`/`parse_expr` de SymPy et le `eval` du moteur exécutent du **code
Python arbitraire** : c'est un piège documenté de SymPy, non sûr sur une entrée
non fiable. Une réponse d'élève de la forme ``__import__('os').system(…)`` — ou,
sans nom dangereux, ``().__class__.__base__.__subclasses__()`` qui remonte aux
objets internes — s'exécute côté serveur. La route ``POST /api/check/{id}``
confie la réponse à ces analyseurs ; ``analyze`` injecte de plus la réponse dans
les expressions de l'auteur, évaluées par le moteur.

Fermer l'espace de noms ne suffit pas : les chaînes de *dunders* atteignent les
types internes sans aucun nom global, et un espace de noms vide casse au passage
la création des symboles (`2+3*x`). Ce qui protège vraiment, c'est de **valider
l'entrée** : `auto_symbol` masque déjà tout nom nu inconnu en `Symbol`, si bien
que le seul pivot vers un objet dangereux est l'accès par **attribut** (`.`) ou
par **dunder** (`__`). Une expression mathématique n'a besoin ni de l'un ni de
l'autre — le seul `.` légitime est le point décimal, entre des chiffres.

Mesuré sur les 9 817 attendus du corpus réellement analysés par SymPy : aucun
n'est rejeté. Les réponses **texte** (phrases, HTML, `atext`) contiennent des
points en toute légitimité, mais ne passent jamais par un évaluateur — ce garde
ne s'applique qu'aux valeurs confiées à `sympify`/`eval`.
"""

from __future__ import annotations

import re

# Un `.` encadré d'au moins un chiffre est un point décimal (`3.14`, `.5`,
# `3.`) ; tout autre `.` est un accès par attribut, qu'aucune expression
# mathématique n'emploie.
_POINT_NON_DECIMAL = re.compile(r"(?<!\d)\.(?!\d)")


class EntreeMathRefusee(ValueError):
    """Une expression porte une construction interdite (dunder ou attribut)."""


def entree_math_sure(s: str) -> bool:
    """``True`` si ``s`` ne peut pas servir d'évasion vers du code arbitraire.

    Rejette le double tiret bas (``__import__`` et toute chaîne de dunders) et
    l'accès par attribut (un ``.`` qui n'est pas un point décimal). Une chaîne
    vide est sûre.
    """
    if not s:
        return True
    if "__" in s:
        return False
    if _POINT_NON_DECIMAL.search(s):
        return False
    return True


def valider_entree_math(s: str) -> None:
    """Lève :class:`EntreeMathRefusee` si ``s`` n'est pas sûre."""
    if not entree_math_sure(s):
        raise EntreeMathRefusee(
            "expression refusée : accès par attribut ou dunder interdit"
        )
