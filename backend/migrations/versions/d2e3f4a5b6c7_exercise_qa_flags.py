"""Add QA status flags to exercises (statement_ok, answer_ok, check_ok)

Revision ID: d2e3f4a5b6c7
Revises: c1a2b3d4e5f6
Create Date: 2026-05-03
"""

import sqlalchemy as sa
from alembic import op

revision = "d2e3f4a5b6c7"
down_revision = "c1a2b3d4e5f6"
branch_labels = None
depends_on = None


def upgrade() -> None:
    op.add_column("exercises", sa.Column("statement_ok", sa.Boolean(), nullable=True))
    op.add_column("exercises", sa.Column("answer_ok", sa.Boolean(), nullable=True))
    op.add_column("exercises", sa.Column("check_ok", sa.Boolean(), nullable=True))


def downgrade() -> None:
    op.drop_column("exercises", "check_ok")
    op.drop_column("exercises", "answer_ok")
    op.drop_column("exercises", "statement_ok")
