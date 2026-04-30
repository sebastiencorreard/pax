from __future__ import annotations

import uuid
from datetime import datetime
from typing import TYPE_CHECKING
from sqlalchemy import String, DateTime, Integer, Numeric, ForeignKey, Text, Boolean
from sqlalchemy.orm import Mapped, mapped_column, relationship
from sqlalchemy.dialects.postgresql import UUID

from db import Base

if TYPE_CHECKING:
    from models.exercise import Exercise


class Sheet(Base):
    """Feuille d'exercices donnée par un enseignant à une classe."""
    __tablename__ = "sheets"

    id: Mapped[int] = mapped_column(primary_key=True)
    teacher_id: Mapped[uuid.UUID] = mapped_column(UUID(as_uuid=True), ForeignKey("users.id"))
    title: Mapped[str] = mapped_column(String(300))
    description: Mapped[str | None] = mapped_column(Text, nullable=True)  # page de présentation (HTML)
    open_at: Mapped[datetime | None] = mapped_column(DateTime, nullable=True)
    close_at: Mapped[datetime | None] = mapped_column(DateTime, nullable=True)
    created_at: Mapped[datetime] = mapped_column(DateTime, default=datetime.utcnow)

    items: Mapped[list["SheetExercise"]] = relationship(
        back_populates="sheet", order_by="SheetExercise.position"
    )


class SheetExercise(Base):
    """Association entre une feuille et un exercice, avec options."""
    __tablename__ = "sheet_exercises"

    id: Mapped[int] = mapped_column(primary_key=True)
    sheet_id: Mapped[int] = mapped_column(ForeignKey("sheets.id", ondelete="CASCADE"))
    exercise_id: Mapped[int] = mapped_column(ForeignKey("exercises.id"))
    position: Mapped[int] = mapped_column(Integer, default=0)
    weight: Mapped[float] = mapped_column(Numeric, default=1.0)  # poids dans la note finale

    sheet: Mapped["Sheet"] = relationship(back_populates="items")
    exercise: Mapped["Exercise"] = relationship(back_populates="sheet_items")


class HomeworkAssignment(Base):
    """Devoir maison : exercices tirés au sort parmi des pools, avec mode entraînement/noté."""
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
    """Un pool = une liste d'exercices parmi lesquels un sera tiré au sort pour l'élève."""
    __tablename__ = "homework_pools"

    id: Mapped[int] = mapped_column(primary_key=True)
    assignment_id: Mapped[int] = mapped_column(ForeignKey("homework_assignments.id", ondelete="CASCADE"))
    position: Mapped[int] = mapped_column(Integer, default=0)  # numéro de la question dans le DM

    assignment: Mapped["HomeworkAssignment"] = relationship(back_populates="pools")
    exercises: Mapped[list["HomeworkPoolExercise"]] = relationship(back_populates="pool")


class HomeworkPoolExercise(Base):
    """Exercices disponibles dans un pool."""
    __tablename__ = "homework_pool_exercises"

    id: Mapped[int] = mapped_column(primary_key=True)
    pool_id: Mapped[int] = mapped_column(ForeignKey("homework_pools.id", ondelete="CASCADE"))
    exercise_id: Mapped[int] = mapped_column(ForeignKey("exercises.id"))

    pool: Mapped["HomeworkPool"] = relationship(back_populates="exercises")
    exercise: Mapped["Exercise"] = relationship()
