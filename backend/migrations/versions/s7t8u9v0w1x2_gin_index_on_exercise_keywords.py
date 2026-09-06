"""index GIN sur exercises.keywords

Permet de filtrer les exercices par mot-clé en SQL — ``keywords && ARRAY[…]``
— au lieu de renvoyer les 3911 exercices francophones (683 Ko) au navigateur
pour qu'il les filtre en JavaScript à chaque frappe.

L'index n'a de sens que depuis que la colonne porte une vraie liste : elle a
longtemps contenu la chaîne éclatée caractère par caractère, et depuis le
2026-09-06 l'union des mots-clés du ``.def`` et du fichier ``Exkeywords`` du
module (cf. ``scripts/import_exercises.py``). Un GIN est le bon index pour un
tableau : il indexe chaque élément, et sert donc ``&&`` (intersection) comme
``@>`` (inclusion).

Sur 4278 lignes un parcours séquentiel ne coûte que 0,8 ms — l'index n'est pas
là pour ce corpus-ci, mais pour que la requête reste plate quand il grandira.

Revision ID: s7t8u9v0w1x2
Revises: r6s7t8u9v0w1
Create Date: 2026-09-06 00:00:00.000000

"""
from typing import Sequence, Union

from alembic import op

revision: str = "s7t8u9v0w1x2"
down_revision: Union[str, None] = "r6s7t8u9v0w1"
branch_labels: Union[str, Sequence[str], None] = None
depends_on: Union[str, Sequence[str], None] = None


def upgrade() -> None:
    op.execute(
        "CREATE INDEX IF NOT EXISTS ix_exercises_keywords "
        "ON exercises USING gin (keywords)"
    )


def downgrade() -> None:
    op.execute("DROP INDEX IF EXISTS ix_exercises_keywords")
