from __future__ import annotations

from datetime import datetime
from typing import TYPE_CHECKING
from sqlalchemy import String, DateTime, Integer, Text, ARRAY, ForeignKey, Numeric
from sqlalchemy.orm import Mapped, mapped_column, relationship

from db import Base

if TYPE_CHECKING:
    from models.sheet import SheetExercise


class Exercise(Base):
    __tablename__ = "exercises"

    id: Mapped[int] = mapped_column(primary_key=True)
    oef_path: Mapped[str] = mapped_column(String(500), unique=True)  # chemin vers le .oef
    title: Mapped[str | None] = mapped_column(String(300), nullable=True)
    module: Mapped[str | None] = mapped_column(String(200), nullable=True)  # ex: H4/algebra/canonicalForms.fr
    level: Mapped[str | None] = mapped_column(String(10), nullable=True)   # ex: H4, E6
    domain: Mapped[str | None] = mapped_column(String(100), nullable=True)  # ex: algebra, analysis
    lang: Mapped[str] = mapped_column(String(5), default="fr")
    keywords: Mapped[list[str] | None] = mapped_column(ARRAY(String), nullable=True)
    created_at: Mapped[datetime] = mapped_column(DateTime, default=datetime.utcnow)

    sheet_items: Mapped[list["SheetExercise"]] = relationship(back_populates="exercise")
