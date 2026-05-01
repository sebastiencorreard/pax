"""exercise id: integer -> path slug (slashes replaced by ~)

Revision ID: c1a2b3d4e5f6
Revises: bff6ef39b9f5
Create Date: 2026-04-30
"""

from alembic import op

revision = "c1a2b3d4e5f6"
down_revision = "bff6ef39b9f5"
branch_labels = None
depends_on = None


def upgrade() -> None:
    op.drop_constraint(
        "sheet_exercises_exercise_id_fkey", "sheet_exercises", type_="foreignkey"
    )
    op.drop_constraint(
        "homework_pool_exercises_exercise_id_fkey",
        "homework_pool_exercises",
        type_="foreignkey",
    )
    op.drop_constraint("attempts_exercise_id_fkey", "attempts", type_="foreignkey")

    op.execute("ALTER TABLE exercises DROP CONSTRAINT exercises_pkey CASCADE")
    op.execute(
        "ALTER TABLE exercises ALTER COLUMN id TYPE VARCHAR(600) USING regexp_replace(ltrim(oef_path, '/'), '/', '~', 'g')"
    )
    op.execute("ALTER TABLE exercises ADD PRIMARY KEY (id)")

    op.execute(
        "ALTER TABLE sheet_exercises ALTER COLUMN exercise_id TYPE VARCHAR(600) USING exercise_id::text"
    )
    op.execute(
        "ALTER TABLE homework_pool_exercises ALTER COLUMN exercise_id TYPE VARCHAR(600) USING exercise_id::text"
    )
    op.execute(
        "ALTER TABLE attempts ALTER COLUMN exercise_id TYPE VARCHAR(600) USING exercise_id::text"
    )

    op.create_foreign_key(None, "sheet_exercises", "exercises", ["exercise_id"], ["id"])
    op.create_foreign_key(
        None, "homework_pool_exercises", "exercises", ["exercise_id"], ["id"]
    )
    op.create_foreign_key(None, "attempts", "exercises", ["exercise_id"], ["id"])


def downgrade() -> None:
    op.drop_constraint(None, "sheet_exercises", type_="foreignkey")  # type: ignore[arg-type]
    op.drop_constraint(None, "homework_pool_exercises", type_="foreignkey")  # type: ignore[arg-type]
    op.drop_constraint(None, "attempts", type_="foreignkey")  # type: ignore[arg-type]

    op.execute("ALTER TABLE exercises DROP CONSTRAINT exercises_pkey CASCADE")
    op.execute("ALTER TABLE exercises ALTER COLUMN id TYPE INTEGER USING 0")
    op.execute("ALTER TABLE exercises ADD PRIMARY KEY (id)")

    op.execute(
        "ALTER TABLE sheet_exercises ALTER COLUMN exercise_id TYPE INTEGER USING 0"
    )
    op.execute(
        "ALTER TABLE homework_pool_exercises ALTER COLUMN exercise_id TYPE INTEGER USING 0"
    )
    op.execute("ALTER TABLE attempts ALTER COLUMN exercise_id TYPE INTEGER USING 0")

    op.create_foreign_key(None, "sheet_exercises", "exercises", ["exercise_id"], ["id"])
    op.create_foreign_key(
        None, "homework_pool_exercises", "exercises", ["exercise_id"], ["id"]
    )
    op.create_foreign_key(None, "attempts", "exercises", ["exercise_id"], ["id"])
