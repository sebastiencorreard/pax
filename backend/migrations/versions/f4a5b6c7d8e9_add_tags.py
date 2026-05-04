"""Add user_tags and exercise_tags tables.

Revision ID: f4a5b6c7d8e9
Revises: e3f4a5b6c7d8
Create Date: 2026-05-05
"""

import sqlalchemy as sa
from alembic import op

revision = "f4a5b6c7d8e9"
down_revision = "e3f4a5b6c7d8"
branch_labels = None
depends_on = None


def upgrade() -> None:
    op.create_table(
        "tags",
        sa.Column("id", sa.Integer(), primary_key=True, autoincrement=True),
        sa.Column("user_id", sa.dialects.postgresql.UUID(as_uuid=True), sa.ForeignKey("users.id", ondelete="CASCADE"), nullable=False),
        sa.Column("name", sa.String(100), nullable=False),
        sa.Column("created_at", sa.DateTime(), nullable=False, server_default=sa.func.now()),
        sa.UniqueConstraint("user_id", "name", name="uq_tags_user_name"),
    )
    op.create_index("ix_tags_user_id", "tags", ["user_id"])

    op.create_table(
        "exercise_tags",
        sa.Column("id", sa.Integer(), primary_key=True, autoincrement=True),
        sa.Column("tag_id", sa.Integer(), sa.ForeignKey("tags.id", ondelete="CASCADE"), nullable=False),
        sa.Column("exercise_id", sa.String(600), sa.ForeignKey("exercises.id", ondelete="CASCADE"), nullable=False),
        sa.UniqueConstraint("tag_id", "exercise_id", name="uq_exercise_tags"),
    )
    op.create_index("ix_exercise_tags_tag_id", "exercise_tags", ["tag_id"])


def downgrade() -> None:
    op.drop_index("ix_exercise_tags_tag_id", table_name="exercise_tags")
    op.drop_table("exercise_tags")
    op.drop_index("ix_tags_user_id", table_name="tags")
    op.drop_table("tags")
