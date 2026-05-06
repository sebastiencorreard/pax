"""add_language_to_user

Revision ID: l0m1n2o3p4q5
Revises: k9l0m1n2o3p4
Create Date: 2026-05-06 00:00:00.000000

"""
from typing import Sequence, Union
from alembic import op
import sqlalchemy as sa

revision: str = 'l0m1n2o3p4q5'
down_revision: Union[str, None] = 'k9l0m1n2o3p4'
branch_labels: Union[str, Sequence[str], None] = None
depends_on: Union[str, Sequence[str], None] = None


def upgrade() -> None:
    op.add_column('users', sa.Column('language', sa.String(5), nullable=False, server_default='fr'))


def downgrade() -> None:
    op.drop_column('users', 'language')
