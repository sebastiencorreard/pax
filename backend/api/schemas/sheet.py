import re
from datetime import datetime
from pydantic import BaseModel, field_validator
from .exercise import ExerciseResponse


# ── Feuille ──────────────────────────────────────────────────────────────────

class SheetCreate(BaseModel):
    title: str
    description: str | None = None
    author: str | None = None
    keywords: list[str] | None = None
    level: str | None = None
    domain: str | None = None
    status: int = 1
    open_at: datetime | None = None
    close_at: datetime | None = None

    @field_validator("status")
    @classmethod
    def status_valid(cls, v: int) -> int:
        if v not in (0, 1, 3):
            raise ValueError("status doit être 0 (caché), 1 (visible) ou 3 (testez-vous)")
        return v


class SheetResponse(BaseModel):
    id: int
    title: str
    description: str | None
    author: str | None
    keywords: list[str] | None
    level: str | None
    domain: str | None
    status: int
    open_at: datetime | None
    close_at: datetime | None
    created_at: datetime

    model_config = {"from_attributes": True}


class SheetUpdate(BaseModel):
    title: str | None = None
    description: str | None = None
    author: str | None = None
    keywords: list[str] | None = None
    level: str | None = None
    domain: str | None = None
    status: int | None = None
    open_at: datetime | None = None
    close_at: datetime | None = None

    @field_validator("status")
    @classmethod
    def status_valid(cls, v: int | None) -> int | None:
        if v is not None and v not in (0, 1, 3):
            raise ValueError("status doit être 0 (caché), 1 (visible) ou 3 (testez-vous)")
        return v


class SheetDetailResponse(SheetResponse):
    items: list["SheetItemResponse"]


# ── Exercice dans une feuille ─────────────────────────────────────────────────

# `oef/exo.init` lit six paramètres : `!for cf=1 to 6`.
_NOM_CONFPARM = re.compile(r"confparm[1-6]")
# Une valeur entre dans la clé du cache de rendu (`render_cache.cache_key`),
# où `|`, `;`, `=` et `:` sont des séparateurs.
_VALEUR_CONFPARM = re.compile(r"[^|;=:\r\n]{0,200}")


def _valider_prerequis(v: str | None) -> str | None:
    """Valide le format "N:score" ou "N+M+...:score"."""
    if v is not None and not re.fullmatch(r"[\d+]+:\d+", v):
        raise ValueError('prerequisite doit être au format "N:score" ou "N+M:score"')
    return v


def _valider_qcmlevel(v: int | None) -> int | None:
    if v is not None and not 1 <= v <= 9:
        raise ValueError("qcmlevel va de 1 à 9")
    return v


def _valider_confparm(v: dict[str, str] | None) -> dict[str, str] | None:
    if v is None:
        return v
    for nom, valeur in v.items():
        if not _NOM_CONFPARM.fullmatch(nom):
            raise ValueError(f"paramètre inconnu : {nom} (confparm1 à confparm6)")
        if not _VALEUR_CONFPARM.fullmatch(valeur):
            raise ValueError(f"valeur refusée pour {nom}")
    return v or None


class SheetExerciseAdd(BaseModel):
    exercise_id: str
    position: int = 0
    points: int = 10
    weight: float = 1.0
    multiplicity: float = 1.0
    prerequisite: str | None = None
    active: bool = True
    qcmlevel: int | None = None
    confparm: dict[str, str] | None = None

    _prerequis = field_validator("prerequisite")(_valider_prerequis)
    _qcmlevel = field_validator("qcmlevel")(_valider_qcmlevel)
    _confparm = field_validator("confparm")(_valider_confparm)


class SheetExerciseUpdate(BaseModel):
    """Modification d'un exercice déjà posé. Un champ absent reste tel quel ;
    `qcmlevel` ou `confparm` à `null` rendent au réglage par défaut."""
    position: int | None = None
    points: int | None = None
    weight: float | None = None
    multiplicity: float | None = None
    prerequisite: str | None = None
    active: bool | None = None
    qcmlevel: int | None = None
    confparm: dict[str, str] | None = None

    _prerequis = field_validator("prerequisite")(_valider_prerequis)
    _qcmlevel = field_validator("qcmlevel")(_valider_qcmlevel)
    _confparm = field_validator("confparm")(_valider_confparm)


class SheetItemResponse(BaseModel):
    id: int
    position: int
    points: int
    weight: float
    multiplicity: float
    prerequisite: str | None
    active: bool
    qcmlevel: int | None = None
    confparm: dict[str, str] | None = None
    exercise: ExerciseResponse

    model_config = {"from_attributes": True}
