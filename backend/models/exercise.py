from __future__ import annotations

from datetime import datetime
from typing import TYPE_CHECKING
from sqlalchemy import String, DateTime, ARRAY
from sqlalchemy.orm import Mapped, mapped_column, relationship

from db import Base

if TYPE_CHECKING:
    from models.sheet import SheetExercise


def path_to_id(oef_path: str) -> str:
    """Convert an oef_path to a URL-safe id by replacing '/' with '~'."""
    return oef_path.lstrip("/").replace("/", "~")


def id_to_path(exercise_id: str) -> str:
    """Reverse of path_to_id."""
    return "/" + exercise_id.replace("~", "/")


class Exercise(Base):
    __tablename__ = "exercises"

    id: Mapped[str] = mapped_column(String(600), primary_key=True)
    oef_path: Mapped[str] = mapped_column(String(500), unique=True)
    title: Mapped[str | None] = mapped_column(String(300), nullable=True)
    module: Mapped[str | None] = mapped_column(String(200), nullable=True)
    level: Mapped[str | None] = mapped_column(String(10), nullable=True)
    domain: Mapped[str | None] = mapped_column(String(100), nullable=True)
    lang: Mapped[str] = mapped_column(String(5), default="fr")
    keywords: Mapped[list[str] | None] = mapped_column(ARRAY(String), nullable=True)
    created_at: Mapped[datetime] = mapped_column(DateTime, default=datetime.utcnow)

    sheet_items: Mapped[list["SheetExercise"]] = relationship(back_populates="exercise")
