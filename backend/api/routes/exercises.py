from fastapi import APIRouter, Depends, HTTPException
from sqlalchemy.ext.asyncio import AsyncSession
from sqlalchemy import select

from db import get_db
from models.exercise import Exercise
from api.schemas.exercise import ExerciseResponse
from api.deps import get_current_user
from models.user import User

router = APIRouter(prefix="/api/exercises", tags=["exercises"])


@router.get("/", response_model=list[ExerciseResponse])
async def list_exercises(
    level: str | None = None,
    domain: str | None = None,
    lang: str = "fr",
    limit: int = 50,
    offset: int = 0,
    db: AsyncSession = Depends(get_db),
    _: User = Depends(get_current_user),
):
    query = select(Exercise).where(Exercise.lang == lang)
    if level:
        query = query.where(Exercise.level == level)
    if domain:
        query = query.where(Exercise.domain == domain)
    query = query.offset(offset).limit(limit)

    result = await db.execute(query)
    return result.scalars().all()


@router.get("/{exercise_id}", response_model=ExerciseResponse)
async def get_exercise(
    exercise_id: str,
    db: AsyncSession = Depends(get_db),
    _: User = Depends(get_current_user),
):
    result = await db.execute(select(Exercise).where(Exercise.id == exercise_id))
    exercise = result.scalar_one_or_none()
    if not exercise:
        raise HTTPException(status_code=404, detail="Exercice introuvable")
    return exercise


@router.get("/{exercise_id}/source")
async def get_exercise_source(
    exercise_id: str,
    db: AsyncSession = Depends(get_db),
    _: User = Depends(get_current_user),
):
    result = await db.execute(select(Exercise).where(Exercise.id == exercise_id))
    exercise = result.scalar_one_or_none()
    if not exercise:
        raise HTTPException(status_code=404, detail="Exercice introuvable")
    try:
        with open(exercise.oef_path, encoding="utf-8") as f:
            content = f.read()
    except UnicodeDecodeError:
        with open(exercise.oef_path, encoding="iso-8859-1") as f:
            content = f.read()
    except FileNotFoundError:
        raise HTTPException(status_code=404, detail="Fichier OEF introuvable sur disque")
    return {"oef_path": exercise.oef_path, "content": content}
