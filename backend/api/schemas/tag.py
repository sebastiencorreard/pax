from datetime import datetime
from pydantic import BaseModel, field_validator


class TagCreate(BaseModel):
    name: str

    @field_validator("name")
    @classmethod
    def name_not_empty(cls, v: str) -> str:
        v = v.strip()
        if not v:
            raise ValueError("Le nom du tag ne peut pas être vide")
        if len(v) > 100:
            raise ValueError("Le nom du tag ne peut pas dépasser 100 caractères")
        return v


class TagResponse(BaseModel):
    id: int
    name: str
    created_at: datetime

    model_config = {"from_attributes": True}


class TagWithCountResponse(TagResponse):
    exercise_count: int


class ExerciseTagsSet(BaseModel):
    tag_id: int | None = None
    name: str | None = None
