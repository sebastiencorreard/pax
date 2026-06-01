"""strip trailing .oef from exercise ids

Drops the redundant trailing ``.oef`` from ``exercises.id`` and the
``exercise_id`` of every referencing table (so ids read like
``H4~algebra~oefsuites1S.fr~src~limmonot1``). The four FK constraints are
dropped and recreated around the bulk update (a PK rewrite can't happen while
children point at the old value). Idempotent: a no-op when ids already lack the
extension (so it's safe on a fresh DB where it runs before any import, and
imports now produce ids without ``.oef`` — see models/exercise.py:path_to_id).

Mirrors p4q5r6s7t8u9 (strip ressources~ prefix).

Revision ID: r6s7t8u9v0w1
Revises: q5r6s7t8u9v0
Create Date: 2026-06-01 00:00:00.000000

"""
from typing import Callable, Sequence, Union
from alembic import op

revision: str = 'r6s7t8u9v0w1'
down_revision: Union[str, None] = 'q5r6s7t8u9v0'
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
        op.execute(f"UPDATE {table} SET exercise_id = {new_value('exercise_id')}")

    for table, fk, ondelete in _CHILDREN:
        kwargs = {"ondelete": ondelete} if ondelete else {}
        op.create_foreign_key(fk, table, "exercises", ["exercise_id"], ["id"], **kwargs)


def upgrade() -> None:
    # Strip a trailing ``.oef``; regexp_replace is a no-op when it's absent.
    _rewrite(lambda c: rf"regexp_replace({c}, '\.oef$', '')")


def downgrade() -> None:
    # Re-add ``.oef`` only where it is missing.
    _rewrite(
        lambda c: f"CASE WHEN {c} LIKE '%.oef' THEN {c} ELSE {c} || '.oef' END"
    )
