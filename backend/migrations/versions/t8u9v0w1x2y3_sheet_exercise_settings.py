"""réglages d'un exercice sur une feuille : qcmlevel et confparm

Chez WIMS, l'enseignant règle un exercice en le posant sur une feuille : le
niveau de sévérité ``qcmlevel`` (1 à 9, ``oef/exo.init``) et les ``confparm``
que le module expose dans son ``introhook.phtml``. PAX lisait déjà les deux
côté moteur, mais servait à tout le monde le niveau 3 et les valeurs d'usine,
faute d'un endroit où ranger le choix.

Les deux colonnes vivent sur ``sheet_exercises`` et non sur ``sheets`` : un
même exercice peut ainsi être posé deux fois, sous deux réglages. NULL garde
le comportement d'avant.

Revision ID: t8u9v0w1x2y3
Revises: s7t8u9v0w1x2
Create Date: 2026-09-10 00:00:00.000000

"""
from typing import Sequence, Union

from alembic import op
import sqlalchemy as sa
from sqlalchemy.dialects import postgresql

revision: str = "t8u9v0w1x2y3"
down_revision: Union[str, None] = "s7t8u9v0w1x2"
branch_labels: Union[str, Sequence[str], None] = None
depends_on: Union[str, Sequence[str], None] = None


def upgrade() -> None:
    op.add_column(
        "sheet_exercises", sa.Column("qcmlevel", sa.SmallInteger(), nullable=True)
    )
    op.add_column(
        "sheet_exercises", sa.Column("confparm", postgresql.JSONB(), nullable=True)
    )
    op.create_check_constraint(
        "ck_sheet_exercises_qcmlevel", "sheet_exercises", "qcmlevel BETWEEN 1 AND 9"
    )


def downgrade() -> None:
    op.drop_constraint("ck_sheet_exercises_qcmlevel", "sheet_exercises", type_="check")
    op.drop_column("sheet_exercises", "confparm")
    op.drop_column("sheet_exercises", "qcmlevel")
