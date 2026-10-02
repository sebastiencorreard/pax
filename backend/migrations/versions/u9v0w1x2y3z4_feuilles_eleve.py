"""feuilles côté élève : affectation aux classes, réglages de note, tirages

Cf. `docs/feuilles-eleve.md`.

- ``sheet_classes`` : une feuille affectée à une classe, avec son statut et ses
  dates **pour cette classe** — une même feuille peut servir à plusieurs.
- ``sheets.note_formule``, ``note_indicateur``, ``note_poids`` : les réglages
  de WIMS (`DF_SEVERITY = 1 2 1` : poids 1, formule `I·Q^0,3`, indicateur
  « meilleur »).
- ``tirages`` : chaque graine délivrée à un élève pour un exercice de feuille,
  et sa note une fois corrigée — le ``seed_score`` de WIMS. L'élève ne choisit
  plus sa graine (TODO IV.2 bis).
- ``attempts.sheet_id`` passe à ``ON DELETE SET NULL`` et ``grades.sheet_id``
  à ``ON DELETE CASCADE`` : sans cela, une feuille ayant des tentatives
  d'élèves ne pouvait plus être supprimée.

Revision ID: u9v0w1x2y3z4
Revises: t8u9v0w1x2y3
Create Date: 2026-10-02 00:00:00.000000

"""
from typing import Sequence, Union

from alembic import op
import sqlalchemy as sa
from sqlalchemy.dialects import postgresql

revision: str = "u9v0w1x2y3z4"
down_revision: Union[str, None] = "t8u9v0w1x2y3"
branch_labels: Union[str, Sequence[str], None] = None
depends_on: Union[str, Sequence[str], None] = None


def upgrade() -> None:
    op.create_table(
        "sheet_classes",
        sa.Column("id", sa.Integer(), primary_key=True),
        sa.Column("sheet_id", sa.Integer(),
                  sa.ForeignKey("sheets.id", ondelete="CASCADE"), nullable=False),
        sa.Column("class_id", sa.Integer(),
                  sa.ForeignKey("classes.id", ondelete="CASCADE"), nullable=False),
        # 0 = en préparation · 1 = active · 2 = périmée · 3 = cachée (WIMS)
        sa.Column("status", sa.SmallInteger(), nullable=False, server_default="1"),
        sa.Column("open_at", sa.DateTime(), nullable=True),
        sa.Column("close_at", sa.DateTime(), nullable=True),
        sa.Column("created_at", sa.DateTime(), nullable=False, server_default=sa.func.now()),
        sa.UniqueConstraint("sheet_id", "class_id", name="uq_sheet_classes"),
        sa.CheckConstraint("status BETWEEN 0 AND 3", name="ck_sheet_classes_status"),
    )
    op.create_index("ix_sheet_classes_class_id", "sheet_classes", ["class_id"])

    op.add_column("sheets", sa.Column("note_formule", sa.SmallInteger(),
                                      nullable=False, server_default="2"))
    op.add_column("sheets", sa.Column("note_indicateur", sa.SmallInteger(),
                                      nullable=False, server_default="1"))
    op.add_column("sheets", sa.Column("note_poids", sa.Numeric(),
                                      nullable=False, server_default="1"))
    op.create_check_constraint("ck_sheets_note_formule", "sheets", "note_formule BETWEEN 0 AND 6")
    op.create_check_constraint("ck_sheets_note_indicateur", "sheets",
                               "note_indicateur BETWEEN 0 AND 2")

    op.create_table(
        "tirages",
        sa.Column("id", postgresql.UUID(as_uuid=True), primary_key=True),
        sa.Column("student_id", postgresql.UUID(as_uuid=True),
                  sa.ForeignKey("users.id", ondelete="CASCADE"), nullable=False),
        sa.Column("sheet_item_id", sa.Integer(),
                  sa.ForeignKey("sheet_exercises.id", ondelete="CASCADE"), nullable=False),
        sa.Column("seed", sa.Integer(), nullable=False),
        sa.Column("issued_at", sa.DateTime(), nullable=False, server_default=sa.func.now()),
        sa.Column("scored_at", sa.DateTime(), nullable=True),
        sa.Column("score", sa.Numeric(), nullable=True),  # 0 à 10, comme WIMS
        sa.Column("hint", sa.Boolean(), nullable=False, server_default=sa.false()),
        sa.Column("attempt_id", postgresql.UUID(as_uuid=True),
                  sa.ForeignKey("attempts.id", ondelete="SET NULL"), nullable=True),
    )
    op.create_index("ix_tirages_eleve_item", "tirages", ["student_id", "sheet_item_id", "issued_at"])

    op.drop_constraint("attempts_sheet_id_fkey", "attempts", type_="foreignkey")
    op.create_foreign_key("attempts_sheet_id_fkey", "attempts", "sheets",
                          ["sheet_id"], ["id"], ondelete="SET NULL")
    op.drop_constraint("grades_sheet_id_fkey", "grades", type_="foreignkey")
    op.create_foreign_key("grades_sheet_id_fkey", "grades", "sheets",
                          ["sheet_id"], ["id"], ondelete="CASCADE")


def downgrade() -> None:
    op.drop_constraint("grades_sheet_id_fkey", "grades", type_="foreignkey")
    op.create_foreign_key("grades_sheet_id_fkey", "grades", "sheets", ["sheet_id"], ["id"])
    op.drop_constraint("attempts_sheet_id_fkey", "attempts", type_="foreignkey")
    op.create_foreign_key("attempts_sheet_id_fkey", "attempts", "sheets", ["sheet_id"], ["id"])
    op.drop_index("ix_tirages_eleve_item", table_name="tirages")
    op.drop_table("tirages")
    op.drop_constraint("ck_sheets_note_indicateur", "sheets", type_="check")
    op.drop_constraint("ck_sheets_note_formule", "sheets", type_="check")
    op.drop_column("sheets", "note_poids")
    op.drop_column("sheets", "note_indicateur")
    op.drop_column("sheets", "note_formule")
    op.drop_index("ix_sheet_classes_class_id", table_name="sheet_classes")
    op.drop_table("sheet_classes")
