from datetime import datetime
from pydantic import BaseModel
from .exercise import ExerciseResponse


class SheetCreate(BaseModel):
    title: str
    description: str | None = None
    open_at: datetime | None = None
    close_at: datetime | None = None


class SheetExerciseAdd(BaseModel):
    exercise_id: str
    position: int = 0
    weight: float = 1.0


class SheetResponse(BaseModel):
    id: int
    title: str
    description: str | None
    open_at: datetime | None
    close_at: datetime | None
    created_at: datetime

    class Config:
        from_attributes = True


class SheetDetailResponse(SheetResponse):
    items: list["SheetItemResponse"]


class SheetItemResponse(BaseModel):
    id: int
    position: int
    weight: float
    exercise: ExerciseResponse

    class Config:
        from_attributes = True
