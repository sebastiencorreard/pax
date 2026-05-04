"""Add 'guest' value to the user_role enum.

Revision ID: e3f4a5b6c7d8
Revises: d2e3f4a5b6c7
Create Date: 2026-05-04
"""

from alembic import op


revision = "e3f4a5b6c7d8"
down_revision = "d2e3f4a5b6c7"
branch_labels = None
depends_on = None


def upgrade() -> None:
    # Postgres ALTER TYPE ... ADD VALUE must run outside a transaction.
    op.execute("COMMIT")
    op.execute("ALTER TYPE user_role ADD VALUE IF NOT EXISTS 'guest'")


def downgrade() -> None:
    # Removing an enum value in Postgres requires recreating the type and
    # rewriting every column referencing it. Not worth it for a test seed
    # — accept that this migration is one-way.
    pass
