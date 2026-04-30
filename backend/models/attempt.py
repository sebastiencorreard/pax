import uuid
from datetime import datetime
from sqlalchemy import String, DateTime, Integer, Numeric, ForeignKey, JSON
from sqlalchemy.orm import Mapped, mapped_column, relationship
from sqlalchemy.dialects.postgresql import UUID, JSONB

from db import Base


class Attempt(Base):
    """Une tentative d'un élève sur un exercice."""
    __tablename__ = "attempts"

    id: Mapped[uuid.UUID] = mapped_column(UUID(as_uuid=True), primary_key=True, default=uuid.uuid4)
    student_id: Mapped[uuid.UUID] = mapped_column(UUID(as_uuid=True), ForeignKey("users.id"))
    exercise_id: Mapped[int] = mapped_column(ForeignKey("exercises.id"))
    sheet_id: Mapped[int | None] = mapped_column(ForeignKey("sheets.id"), nullable=True)
    hw_assignment_id: Mapped[int | None] = mapped_column(
        ForeignKey("homework_assignments.id"), nullable=True
    )
    score: Mapped[float | None] = mapped_column(Numeric, nullable=True)   # 0.0 à 1.0
    answers: Mapped[dict | None] = mapped_column(JSONB, nullable=True)    # réponses brutes
    seed: Mapped[int | None] = mapped_column(Integer, nullable=True)      # graine aléatoire
    is_graded: Mapped[bool] = mapped_column(default=False)                # tentative notée ?
    created_at: Mapped[datetime] = mapped_column(DateTime, default=datetime.utcnow)


class Grade(Base):
    """Note finale d'un élève sur une feuille (meilleure tentative notée)."""
    __tablename__ = "grades"

    id: Mapped[int] = mapped_column(primary_key=True)
    student_id: Mapped[uuid.UUID] = mapped_column(UUID(as_uuid=True), ForeignKey("users.id"))
    sheet_id: Mapped[int] = mapped_column(ForeignKey("sheets.id"))
    score: Mapped[float | None] = mapped_column(Numeric, nullable=True)
    computed_at: Mapped[datetime] = mapped_column(DateTime, default=datetime.utcnow)
