"""add_theme_to_user

Revision ID: o3p4q5r6s7t8
Revises: n2o3p4q5r6s7
Create Date: 2026-05-11 00:00:00.000000

"""
from typing import Sequence, Union
from alembic import op
import sqlalchemy as sa

revision: str = 'o3p4q5r6s7t8'
down_revision: Union[str, None] = 'n2o3p4q5r6s7'
branch_labels: Union[str, Sequence[str], None] = None
depends_on: Union[str, Sequence[str], None] = None


def upgrade() -> None:
    op.add_column('users', sa.Column('theme', sa.String(10), nullable=False, server_default='system'))


def downgrade() -> None:
    op.drop_column('users', 'theme')
