from __future__ import annotations

import uuid
from datetime import datetime
from typing import TYPE_CHECKING
from sqlalchemy import (
    String,
    DateTime,
    Integer,
    Boolean,
    ForeignKey,
    UniqueConstraint,
    Index,
    text,
)
from sqlalchemy.orm import Mapped, mapped_column, relationship
from sqlalchemy.dialects.postgresql import UUID

from db import Base

if TYPE_CHECKING:
    from models.user import User
    from models.exercise import Exercise


class Tag(Base):
    __tablename__ = "tags"
    __table_args__ = (
        UniqueConstraint("user_id", "name", name="uq_tags_user_name"),
        # Shared tags have user_id NULL; the (user_id, name) unique above can't
        # dedupe them (NULL != NULL in SQL), so guard their names separately.
        Index(
            "uq_shared_tag_name",
            "name",
            unique=True,
            postgresql_where=text("is_shared"),
        ),
    )

    id: Mapped[int] = mapped_column(Integer, primary_key=True, autoincrement=True)
    # NULL for a shared tag (owned by no one, visible to all teachers/admins).
    user_id: Mapped[uuid.UUID | None] = mapped_column(
        UUID(as_uuid=True), ForeignKey("users.id", ondelete="CASCADE"), nullable=True
    )
    name: Mapped[str] = mapped_column(String(100))
    is_shared: Mapped[bool] = mapped_column(Boolean, nullable=False, default=False)
    created_at: Mapped[datetime] = mapped_column(DateTime, default=datetime.utcnow)

    exercise_links: Mapped[list["ExerciseTag"]] = relationship(back_populates="tag", cascade="all, delete-orphan")


class ExerciseTag(Base):
    __tablename__ = "exercise_tags"
    __table_args__ = (UniqueConstraint("tag_id", "exercise_id", name="uq_exercise_tags"),)

    id: Mapped[int] = mapped_column(Integer, primary_key=True, autoincrement=True)
    tag_id: Mapped[int] = mapped_column(Integer, ForeignKey("tags.id", ondelete="CASCADE"))
    exercise_id: Mapped[str] = mapped_column(String(600), ForeignKey("exercises.id", ondelete="CASCADE"))

    tag: Mapped["Tag"] = relationship(back_populates="exercise_links")
