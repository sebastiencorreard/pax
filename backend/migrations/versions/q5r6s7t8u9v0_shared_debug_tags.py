"""shared debug tags (is_shared) + seed dbg ok/pb/bad

Adds ``tags.is_shared`` and makes ``tags.user_id`` nullable so a tag can be
shared (owned by no one, visible to every teacher/admin). Seeds the three
debug tags. A partial unique index keeps shared tag names unique (the existing
(user_id, name) unique can't, since NULL != NULL).

Revision ID: q5r6s7t8u9v0
Revises: p4q5r6s7t8u9
Create Date: 2026-05-29 00:00:00.000000

"""
from typing import Sequence, Union
from alembic import op
import sqlalchemy as sa

revision: str = 'q5r6s7t8u9v0'
down_revision: Union[str, None] = 'p4q5r6s7t8u9'
branch_labels: Union[str, Sequence[str], None] = None
depends_on: Union[str, Sequence[str], None] = None

_SHARED_TAGS = ("dbg ok", "dbg pb", "dbg bad")


def upgrade() -> None:
    op.add_column(
        "tags",
        sa.Column("is_shared", sa.Boolean(), nullable=False, server_default=sa.false()),
    )
    op.alter_column("tags", "user_id", existing_type=sa.dialects.postgresql.UUID(), nullable=True)
    op.create_index(
        "uq_shared_tag_name",
        "tags",
        ["name"],
        unique=True,
        postgresql_where=sa.text("is_shared"),
    )
    # Seed the shared debug tags (idempotent).
    for name in _SHARED_TAGS:
        op.execute(
            sa.text(
                "INSERT INTO tags (user_id, name, is_shared, created_at) "
                "SELECT NULL, :name, true, now() "
                "WHERE NOT EXISTS (SELECT 1 FROM tags WHERE name = :name AND is_shared)"
            ).bindparams(name=name)
        )


def downgrade() -> None:
    op.execute("DELETE FROM tags WHERE is_shared")
    op.drop_index("uq_shared_tag_name", table_name="tags")
    op.alter_column("tags", "user_id", existing_type=sa.dialects.postgresql.UUID(), nullable=False)
    op.drop_column("tags", "is_shared")
