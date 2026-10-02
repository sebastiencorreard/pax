from __future__ import annotations

import uuid
from datetime import datetime
from typing import TYPE_CHECKING
from sqlalchemy import String, DateTime, Integer, SmallInteger, Numeric, Boolean, ForeignKey, Text  # noqa: F401
from sqlalchemy.orm import Mapped, mapped_column, relationship
from sqlalchemy.dialects.postgresql import UUID, ARRAY, JSONB

from db import Base

if TYPE_CHECKING:
    from models.exercise import Exercise


class Sheet(Base):
    """Feuille d'exercices donnée par un enseignant à une classe."""

    __tablename__ = "sheets"

    id: Mapped[int] = mapped_column(primary_key=True)
    teacher_id: Mapped[uuid.UUID] = mapped_column(UUID(as_uuid=True), ForeignKey("users.id", ondelete="CASCADE"))
    title: Mapped[str] = mapped_column(String(300))
    description: Mapped[str | None] = mapped_column(Text, nullable=True)
    author: Mapped[str | None] = mapped_column(String(200), nullable=True)
    keywords: Mapped[list[str] | None] = mapped_column(ARRAY(String), nullable=True)
    level: Mapped[str | None] = mapped_column(String(10), nullable=True)
    domain: Mapped[str | None] = mapped_column(String(100), nullable=True)
    # 0 = caché · 1 = visible et scoré · 3 = visible non scoré ("testez-vous")
    status: Mapped[int] = mapped_column(SmallInteger, default=1)
    open_at: Mapped[datetime | None] = mapped_column(DateTime, nullable=True)
    close_at: Mapped[datetime | None] = mapped_column(DateTime, nullable=True)
    created_at: Mapped[datetime] = mapped_column(DateTime, default=datetime.utcnow)
    # Calcul de la note (WIMS, `DF_SEVERITY = 1 2 1`) : formule 0–6
    # (`I·Q^0,3` par défaut), indicateur 0–2 (cumul, meilleur, niveau), poids
    # de la feuille dans la note globale. Cf. `core/note_feuille.py`.
    note_formule: Mapped[int] = mapped_column(SmallInteger, default=2, server_default="2")
    note_indicateur: Mapped[int] = mapped_column(SmallInteger, default=1, server_default="1")
    note_poids: Mapped[float] = mapped_column(Numeric, default=1, server_default="1")

    # La base emporte les exercices d'une feuille supprimée (`ON DELETE
    # CASCADE`). Sans `passive_deletes`, l'ORM tentait d'abord de les détacher
    # (`sheet_id = NULL`), et supprimer une feuille non vide échouait sur la
    # contrainte NOT NULL — un 500 pour tout enseignant.
    items: Mapped[list["SheetExercise"]] = relationship(
        back_populates="sheet", order_by="SheetExercise.position",
        cascade="all, delete-orphan", passive_deletes=True,
    )


class SheetExercise(Base):
    """Association entre une feuille et un exercice, avec options WIMS."""

    __tablename__ = "sheet_exercises"

    id: Mapped[int] = mapped_column(primary_key=True)
    sheet_id: Mapped[int] = mapped_column(ForeignKey("sheets.id", ondelete="CASCADE"))
    exercise_id: Mapped[str] = mapped_column(String(600), ForeignKey("exercises.id"))
    position: Mapped[int] = mapped_column(Integer, default=0)
    # points : valeur de l'exercice dans la feuille (ex. 10, 30, 40)
    points: Mapped[int] = mapped_column(Integer, default=10)
    # weight : poids relatif pour la note globale (généralement 1)
    weight: Mapped[float] = mapped_column(Numeric, default=1.0)
    # multiplicity : coefficient de pondération du score (décimal possible : 0.3, 0.5, 1.5…)
    multiplicity: Mapped[float] = mapped_column(Numeric, default=1.0)
    # prerequisite : condition de déblocage, ex. "1:90" ou "1+2:70"
    prerequisite: Mapped[str | None] = mapped_column(String(100), nullable=True)
    active: Mapped[bool] = mapped_column(Boolean, default=True)
    # qcmlevel : niveau de sévérité WIMS, 1 à 9 (`oef/exo.init`) ; NULL = celui
    # que PAX prend faute de réglage, le niveau 3.
    qcmlevel: Mapped[int | None] = mapped_column(SmallInteger, nullable=True)
    # confparm : valeurs choisies pour les paramètres du module, ex.
    # {"confparm1": "2"} ; NULL = les valeurs d'usine de son `introhook.phtml`.
    confparm: Mapped[dict[str, str] | None] = mapped_column(JSONB, nullable=True)

    sheet: Mapped["Sheet"] = relationship(back_populates="items")
    exercise: Mapped["Exercise"] = relationship(back_populates="sheet_items")


class SheetClass(Base):
    """Une feuille affectée à une classe, avec son statut et ses dates pour
    cette classe : une même feuille peut servir à plusieurs."""

    __tablename__ = "sheet_classes"

    id: Mapped[int] = mapped_column(primary_key=True)
    sheet_id: Mapped[int] = mapped_column(ForeignKey("sheets.id", ondelete="CASCADE"))
    class_id: Mapped[int] = mapped_column(ForeignKey("classes.id", ondelete="CASCADE"))
    # 0 = en préparation · 1 = active · 2 = périmée · 3 = cachée (WIMS)
    status: Mapped[int] = mapped_column(SmallInteger, default=1, server_default="1")
    open_at: Mapped[datetime | None] = mapped_column(DateTime, nullable=True)
    close_at: Mapped[datetime | None] = mapped_column(DateTime, nullable=True)
    created_at: Mapped[datetime] = mapped_column(DateTime, default=datetime.utcnow)

    sheet: Mapped["Sheet"] = relationship()


class Tirage(Base):
    """Une graine délivrée à un élève pour un exercice de feuille, et sa note.

    Le `seed_score` de WIMS. L'élève ne choisit pas sa graine : le serveur la
    délivre, et ne note qu'une fois chaque tirage (TODO IV.2 bis)."""

    __tablename__ = "tirages"

    id: Mapped[uuid.UUID] = mapped_column(UUID(as_uuid=True), primary_key=True, default=uuid.uuid4)
    student_id: Mapped[uuid.UUID] = mapped_column(
        UUID(as_uuid=True), ForeignKey("users.id", ondelete="CASCADE"))
    sheet_item_id: Mapped[int] = mapped_column(ForeignKey("sheet_exercises.id", ondelete="CASCADE"))
    seed: Mapped[int] = mapped_column(Integer)
    issued_at: Mapped[datetime] = mapped_column(DateTime, default=datetime.utcnow)
    scored_at: Mapped[datetime | None] = mapped_column(DateTime, nullable=True)
    score: Mapped[float | None] = mapped_column(Numeric, nullable=True)  # 0 à 10
    hint: Mapped[bool] = mapped_column(Boolean, default=False, server_default="false")
    attempt_id: Mapped[uuid.UUID | None] = mapped_column(
        UUID(as_uuid=True), ForeignKey("attempts.id", ondelete="SET NULL"), nullable=True)


class HomeworkAssignment(Base):
    """Devoir maison : exercices tirés au sort parmi des pools."""

    __tablename__ = "homework_assignments"

    id: Mapped[int] = mapped_column(primary_key=True)
    sheet_id: Mapped[int] = mapped_column(ForeignKey("sheets.id", ondelete="CASCADE"))
    time_limit_minutes: Mapped[int | None] = mapped_column(Integer, nullable=True)
    max_graded_attempts: Mapped[int] = mapped_column(Integer, default=3)
    open_at: Mapped[datetime | None] = mapped_column(DateTime, nullable=True)
    close_at: Mapped[datetime | None] = mapped_column(DateTime, nullable=True)

    sheet: Mapped["Sheet"] = relationship()
    pools: Mapped[list["HomeworkPool"]] = relationship(
        back_populates="assignment", order_by="HomeworkPool.position"
    )


class HomeworkPool(Base):
    """Un pool = liste d'exercices parmi lesquels un sera tiré au sort."""

    __tablename__ = "homework_pools"

    id: Mapped[int] = mapped_column(primary_key=True)
    assignment_id: Mapped[int] = mapped_column(
        ForeignKey("homework_assignments.id", ondelete="CASCADE")
    )
    position: Mapped[int] = mapped_column(Integer, default=0)

    assignment: Mapped["HomeworkAssignment"] = relationship(back_populates="pools")
    exercises: Mapped[list["HomeworkPoolExercise"]] = relationship(back_populates="pool")


class HomeworkPoolExercise(Base):
    """Exercices disponibles dans un pool."""

    __tablename__ = "homework_pool_exercises"

    id: Mapped[int] = mapped_column(primary_key=True)
    pool_id: Mapped[int] = mapped_column(ForeignKey("homework_pools.id", ondelete="CASCADE"))
    exercise_id: Mapped[str] = mapped_column(String(600), ForeignKey("exercises.id"))

    pool: Mapped["HomeworkPool"] = relationship(back_populates="exercises")
    exercise: Mapped["Exercise"] = relationship()
