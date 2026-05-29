"""strip ressources~ prefix from exercise ids

Drops the redundant leading ``ressources~`` from ``exercises.id`` and the
``exercise_id`` of every referencing table. The four FK constraints are dropped
and recreated around the bulk update (a PK rewrite can't happen while children
point at the old value). Idempotent: a no-op when ids already lack the prefix
(important on a fresh DB, where this migration runs before any import).

Revision ID: p4q5r6s7t8u9
Revises: o3p4q5r6s7t8
Create Date: 2026-05-29 00:00:00.000000

"""
from typing import Callable, Sequence, Union
from alembic import op

revision: str = 'p4q5r6s7t8u9'
down_revision: Union[str, None] = 'o3p4q5r6s7t8'
branch_labels: Union[str, Sequence[str], None] = None
depends_on: Union[str, Sequence[str], None] = None

# (table, fk_constraint_name, ondelete) for each table referencing exercises.id.
_CHILDREN = [
    ("exercise_tags", "exercise_tags_exercise_id_fkey", "CASCADE"),
    ("attempts", "attempts_exercise_id_fkey", None),
    ("sheet_exercises", "sheet_exercises_exercise_id_fkey", None),
    ("homework_pool_exercises", "homework_pool_exercises_exercise_id_fkey", None),
]


def _rewrite(new_value: Callable[[str], str]) -> None:
    """Rewrite ids/exercise_ids using ``new_value(column)`` SQL, FK-safe."""
    for table, fk, _ in _CHILDREN:
        op.drop_constraint(fk, table, type_="foreignkey")

    op.execute(f"UPDATE exercises SET id = {new_value('id')}")
    for table, _, _ in _CHILDREN:
        op.execute(
            f"UPDATE {table} SET exercise_id = {new_value('exercise_id')}"
        )

    for table, fk, ondelete in _CHILDREN:
        kwargs = {"ondelete": ondelete} if ondelete else {}
        op.create_foreign_key(
            fk, table, "exercises", ["exercise_id"], ["id"], **kwargs
        )


def upgrade() -> None:
    # Strip the prefix; regexp_replace is a no-op when it isn't present.
    _rewrite(lambda c: f"regexp_replace({c}, '^ressources~', '')")


def downgrade() -> None:
    # Re-add the prefix only where it is missing.
    _rewrite(
        lambda c: f"CASE WHEN {c} LIKE 'ressources~%' THEN {c} "
        f"ELSE 'ressources~' || {c} END"
    )
