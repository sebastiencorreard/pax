"""unique_name_per_etab_all_roles

Remplace la contrainte partielle (élèves seulement) par une contrainte complète
sur (first_name, last_name, etab_id) pour tous les rôles.

Revision ID: n2o3p4q5r6s7
Revises: l0m1n2o3p4q5
Create Date: 2026-05-07 00:00:00.000000

"""
from typing import Sequence, Union
from alembic import op

revision: str = 'n2o3p4q5r6s7'
down_revision: Union[str, None] = 'l0m1n2o3p4q5'
branch_labels: Union[str, Sequence[str], None] = None
depends_on: Union[str, Sequence[str], None] = None


def upgrade() -> None:
    # Supprimer la contrainte partielle élèves-seulement si elle existe
    op.execute("DROP INDEX IF EXISTS uq_student_name_per_etab")
    # Supprimer l'ancienne contrainte tous-rôles si elle avait été créée
    op.execute("""
        DO $$ BEGIN
            IF EXISTS (
                SELECT 1 FROM pg_constraint
                WHERE conname = 'uq_user_name_per_etab'
                  AND conrelid = 'users'::regclass
            ) THEN
                ALTER TABLE users DROP CONSTRAINT uq_user_name_per_etab;
            END IF;
        END $$
    """)
    # Créer la contrainte complète (NULL etab_id exempté automatiquement)
    op.create_unique_constraint(
        'uq_user_name_per_etab', 'users', ['first_name', 'last_name', 'etab_id']
    )


def downgrade() -> None:
    op.drop_constraint('uq_user_name_per_etab', 'users', type_='unique')
