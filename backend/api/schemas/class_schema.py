import uuid
from datetime import datetime
from pydantic import BaseModel


class ClassCreate(BaseModel):
    name: str


class UserBrief(BaseModel):
    id: uuid.UUID
    first_name: str | None
    last_name: str | None
    email: str | None
    role: str

    model_config = {"from_attributes": True}


class ClassResponse(BaseModel):
    id: int
    name: str
    teacher_id: uuid.UUID
    created_at: datetime
    student_count: int = 0

    model_config = {"from_attributes": True}


class ClassDetailResponse(BaseModel):
    id: int
    name: str
    teacher_id: uuid.UUID
    created_at: datetime
    students: list[UserBrief] = []

    model_config = {"from_attributes": True}


class StudentClassResponse(BaseModel):
    id: int
    name: str
    teacher_first_name: str | None
    teacher_last_name: str | None

    model_config = {"from_attributes": True}


class UserCreate(BaseModel):
    email: str
    first_name: str
    last_name: str
    role: str
    password: str


class UserResponse(BaseModel):
    id: uuid.UUID
    email: str | None
    first_name: str | None
    last_name: str | None
    role: str
    created_at: datetime

    model_config = {"from_attributes": True}
