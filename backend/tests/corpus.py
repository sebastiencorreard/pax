"""Énumération du corpus d'exercices pour les tests paramétrés.

Remplace la requête `psql` que portaient `test_exercises_check` et
`test_exercises_render`. Elle n'apportait rien — `load_and_render` prend un
chemin de fichier, la base ne servait qu'à lister ces chemins — et coûtait
cher : mot de passe en dur, `psql` absent de l'image (les deux modules ne se
collectaient donc plus), identifiants convertis en entier alors qu'ils sont
des slugs depuis la migration `c1a2b3d4e5f6`.

Le corpus se lit directement sur le disque, ce qui rend ces tests exécutables
sans base, sans import préalable et sans client PostgreSQL.

`PAX_TEST_CORPUS` restreint le parcours à un sous-arbre — `H4/algebra` par
exemple. Un parcours complet représente 4278 exercices, soit une bonne dizaine
de minutes ; c'est le sens du marqueur `slow` que portent les deux modules.
"""

import glob
import os
import sys

sys.path.insert(0, os.path.dirname(os.path.dirname(os.path.abspath(__file__))))

from config import settings  # noqa: E402
from models.exercise import path_to_id  # noqa: E402


def oef_paths() -> list[str]:
    """Chemins des exercices `.oef`, triés, éventuellement restreints."""
    racine = settings.resources_root.rstrip("/")
    sous_arbre = os.environ.get("PAX_TEST_CORPUS", "").strip("/")
    motif = f"{racine}/{sous_arbre}/**/*.oef" if sous_arbre else f"{racine}/**/*.oef"
    # PAX ne rend que des `.def` : un `.oef` sans `.def` n'est pas un exercice
    # PAX, et le seul du corpus (`oefpression/mathml`) est un fichier de
    # démonstration hors `src/`. Le parseur OEF qui le rendait a été retiré.
    return sorted(
        c for c in glob.glob(motif, recursive=True)
        if os.path.exists(os.path.join(os.path.dirname(os.path.dirname(c)), "def",
                                       os.path.basename(c)[:-4] + ".def"))
    )


def exercises() -> list[tuple[str, str]]:
    """Couples `(identifiant, chemin)`, l'identifiant étant le slug des routes.

    Le chemin est rendu absolu-depuis-la-racine (`/ressources/…`) avant
    conversion, `path_to_id` attendant la forme stockée en base.
    """
    racine = settings.resources_root.rstrip("/")
    couples = []
    for chemin in oef_paths():
        relatif = "/ressources/" + os.path.relpath(chemin, racine)
        couples.append((path_to_id(relatif), chemin))
    return couples
