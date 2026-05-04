import uuid
from datetime import datetime
from sqlalchemy import String, DateTime, Enum as SAEnum, ForeignKey
from sqlalchemy.orm import Mapped, mapped_column, relationship
from sqlalchemy.dialects.postgresql import UUID

from db import Base


class Academie(Base):
    __tablename__ = "academies"

    id: Mapped[int] = mapped_column(primary_key=True)
    name: Mapped[str] = mapped_column(String(100))
    code: Mapped[str] = mapped_column(String(10), unique=True)

    etablissements: Mapped[list["Etablissement"]] = relationship(
        back_populates="academie"
    )


class Etablissement(Base):
    __tablename__ = "etablissements"

    id: Mapped[int] = mapped_column(primary_key=True)
    academie_id: Mapped[int] = mapped_column(ForeignKey("academies.id"))
    uai: Mapped[str] = mapped_column(String(8), unique=True)  # identifiant officiel EN
    name: Mapped[str] = mapped_column(String(200))

    academie: Mapped["Academie"] = relationship(back_populates="etablissements")
    users: Mapped[list["User"]] = relationship(back_populates="etablissement")


class User(Base):
    __tablename__ = "users"

    id: Mapped[uuid.UUID] = mapped_column(
        UUID(as_uuid=True), primary_key=True, default=uuid.uuid4
    )
    etab_id: Mapped[int | None] = mapped_column(
        ForeignKey("etablissements.id"), nullable=True
    )
    keycloak_id: Mapped[str | None] = mapped_column(
        String(100), unique=True, nullable=True
    )
    role: Mapped[str] = mapped_column(
        SAEnum(
            "student",
            "teacher",
            "admin",
            "inspector",
            "guest",
            name="user_role",
        )
    )
    email: Mapped[str | None] = mapped_column(String(200), unique=True, nullable=True)
    last_name: Mapped[str | None] = mapped_column(String(100), nullable=True)
    first_name: Mapped[str | None] = mapped_column(String(100), nullable=True)
    hashed_password: Mapped[str | None] = mapped_column(String(200), nullable=True)
    created_at: Mapped[datetime] = mapped_column(DateTime, default=datetime.utcnow)

    etablissement: Mapped["Etablissement | None"] = relationship(back_populates="users")
