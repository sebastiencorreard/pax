"""Etablissements enrichis, rôles super_admin/inspector, liaison users-etabs.

Revision ID: j8k9l0m1n2o3
Revises: 5fd60ebc0a0d
Create Date: 2026-05-06
"""

import sqlalchemy as sa
from alembic import op

revision = "j8k9l0m1n2o3"
down_revision = ("5fd60ebc0a0d", "f4546adf9610")
branch_labels = None
depends_on = None


def upgrade() -> None:
    # ── 1. Colonnes manquantes sur etablissements ───────────────────────────
    op.add_column("etablissements", sa.Column("commune",   sa.String(100), nullable=True))
    op.add_column("etablissements", sa.Column("code_postal", sa.String(10), nullable=True))
    op.add_column("etablissements", sa.Column("type_etab", sa.String(100), nullable=True))

    # ── 2. Supprimer la contrainte unique globale (prénom, nom) sur users ───
    op.drop_constraint("uq_user_names", "users", type_="unique")

    # ── 3. Rôle enum : supprimer inspector, ajouter super_admin ────────────
    # Convertit les eventuels inspectors en admin
    op.execute("UPDATE users SET role = 'admin' WHERE role = 'inspector'")
    # Passe par varchar pour pouvoir recréer l'enum
    op.execute("ALTER TABLE users ALTER COLUMN role TYPE VARCHAR(20) USING role::VARCHAR(20)")
    op.execute("DROP TYPE user_role")
    op.execute(
        "CREATE TYPE user_role AS ENUM "
        "('student', 'teacher', 'admin', 'super_admin', 'guest')"
    )
    op.execute(
        "ALTER TABLE users ALTER COLUMN role TYPE user_role USING role::user_role"
    )

    # ── 4. Rattacher tous les users existants au Forbin (sauf guest) ────────
    op.execute(
        """
        UPDATE users
        SET etab_id = (SELECT id FROM etablissements WHERE uai = '0132401P' LIMIT 1)
        WHERE etab_id IS NULL AND role != 'guest'
        """
    )

    # ── 5. Index partiel : unicité (etab, prénom, nom) par établissement ────
    #        uniquement pour les élèves
    op.create_index(
        "uq_student_name_per_etab",
        "users",
        ["etab_id", "first_name", "last_name"],
        unique=True,
        postgresql_where=sa.text("role = 'student'"),
    )


def downgrade() -> None:
    op.drop_index("uq_student_name_per_etab", table_name="users")

    op.execute("UPDATE users SET role = 'admin' WHERE role = 'super_admin'")
    op.execute("ALTER TABLE users ALTER COLUMN role TYPE VARCHAR(20) USING role::VARCHAR(20)")
    op.execute("DROP TYPE user_role")
    op.execute(
        "CREATE TYPE user_role AS ENUM "
        "('student', 'teacher', 'admin', 'inspector', 'guest')"
    )
    op.execute(
        "ALTER TABLE users ALTER COLUMN role TYPE user_role USING role::user_role"
    )

    op.create_unique_constraint("uq_user_names", "users", ["first_name", "last_name"])

    op.drop_column("etablissements", "type_etab")
    op.drop_column("etablissements", "code_postal")
    op.drop_column("etablissements", "commune")
