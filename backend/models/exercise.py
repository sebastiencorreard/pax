from __future__ import annotations

from datetime import datetime
from typing import TYPE_CHECKING
from sqlalchemy import Boolean, String, DateTime, ARRAY
from sqlalchemy.orm import Mapped, mapped_column, relationship

from db import Base

if TYPE_CHECKING:
    from models.sheet import SheetExercise


# Exercise files all live under the `/ressources/` tree, so the leading
# `ressources` path component is redundant in the (URL-safe) id — we strip it.
_RESOURCES_PREFIX = "ressources~"


def path_to_id(oef_path: str) -> str:
    """Convert an oef_path to a URL-safe id by replacing '/' with '~'.

    The redundant leading ``ressources~`` component and the trailing ``.oef``
    extension are dropped, so
    ``/ressources/H4/algebra/oefsuites1S.fr/src/limmonot1.oef``
    → ``H4~algebra~oefsuites1S.fr~src~limmonot1``.
    """
    slug = oef_path.lstrip("/").replace("/", "~")
    if slug.startswith(_RESOURCES_PREFIX):
        slug = slug[len(_RESOURCES_PREFIX):]
    if slug.endswith(".oef"):
        slug = slug[: -len(".oef")]
    return slug


def id_to_path(exercise_id: str) -> str:
    """Reverse of path_to_id (assumes the file lives under /ressources/ and is
    an ``.oef``).

    Not used for file resolution at runtime — routes read the stored
    ``Exercise.oef_path`` directly — but kept as a faithful inverse.
    """
    path = "/ressources/" + exercise_id.replace("~", "/")
    if not path.endswith(".oef"):
        path += ".oef"
    return path


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
