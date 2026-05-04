from fastapi import APIRouter, Depends, HTTPException
from sqlalchemy.ext.asyncio import AsyncSession
from sqlalchemy import select, func, delete
from sqlalchemy.exc import IntegrityError

from db import get_db
from models.tag import Tag, ExerciseTag
from models.exercise import Exercise
from models.user import User
from api.schemas.tag import TagCreate, TagResponse, TagWithCountResponse, ExerciseTagsSet
from api.deps import require_role

router = APIRouter(prefix="/api/tags", tags=["tags"])


async def _get_user_tag(tag_id: int, user: User, db: AsyncSession) -> Tag:
    result = await db.execute(select(Tag).where(Tag.id == tag_id, Tag.user_id == user.id))
    tag = result.scalar_one_or_none()
    if not tag:
        raise HTTPException(status_code=404, detail="Tag introuvable")
    return tag


@router.get("/", response_model=list[TagWithCountResponse])
async def list_tags(
    db: AsyncSession = Depends(get_db),
    current_user: User = Depends(require_role("teacher", "admin")),
):
    count_sq = (
        select(ExerciseTag.tag_id, func.count(ExerciseTag.id).label("cnt"))
        .group_by(ExerciseTag.tag_id)
        .subquery()
    )
    query = (
        select(Tag, func.coalesce(count_sq.c.cnt, 0).label("exercise_count"))
        .outerjoin(count_sq, Tag.id == count_sq.c.tag_id)
        .where(Tag.user_id == current_user.id)
        .order_by(Tag.name)
    )
    rows = (await db.execute(query)).all()
    return [
        TagWithCountResponse(
            id=tag.id,
            name=tag.name,
            created_at=tag.created_at,
            exercise_count=cnt,
        )
        for tag, cnt in rows
    ]


@router.post("/", response_model=TagResponse, status_code=201)
async def create_tag(
    payload: TagCreate,
    db: AsyncSession = Depends(get_db),
    current_user: User = Depends(require_role("teacher", "admin")),
):
    tag = Tag(user_id=current_user.id, name=payload.name)
    db.add(tag)
    try:
        await db.commit()
        await db.refresh(tag)
    except IntegrityError:
        await db.rollback()
        raise HTTPException(status_code=409, detail=f"Le tag « {payload.name} » existe déjà")
    return tag


@router.get("/{tag_id}/exercises")
async def get_tag_exercises(
    tag_id: int,
    db: AsyncSession = Depends(get_db),
    current_user: User = Depends(require_role("teacher", "admin")),
):
    """Retourne les exercices associés à un tag de l'utilisateur."""
    tag = await _get_user_tag(tag_id, current_user, db)
    exs_q = await db.execute(
        select(Exercise)
        .join(ExerciseTag, ExerciseTag.exercise_id == Exercise.id)
        .where(ExerciseTag.tag_id == tag_id)
        .order_by(Exercise.title)
    )
    exercises = exs_q.scalars().all()
    return {
        "tag": {"id": tag.id, "name": tag.name, "created_at": tag.created_at},
        "exercises": [
            {"id": ex.id, "title": ex.title or ex.id, "domain": ex.domain, "level": ex.level}
            for ex in exercises
        ],
    }


@router.delete("/{tag_id}", status_code=204)
async def delete_tag(
    tag_id: int,
    db: AsyncSession = Depends(get_db),
    current_user: User = Depends(require_role("teacher", "admin")),
):
    tag = await _get_user_tag(tag_id, current_user, db)
    await db.delete(tag)
    await db.commit()


@router.get("/exercise/{exercise_id}", response_model=list[TagResponse])
async def get_exercise_tags(
    exercise_id: str,
    db: AsyncSession = Depends(get_db),
    current_user: User = Depends(require_role("teacher", "admin")),
):
    query = (
        select(Tag)
        .join(ExerciseTag, ExerciseTag.tag_id == Tag.id)
        .where(ExerciseTag.exercise_id == exercise_id, Tag.user_id == current_user.id)
        .order_by(Tag.name)
    )
    result = await db.execute(query)
    return result.scalars().all()


@router.post("/exercise/{exercise_id}", response_model=list[TagResponse])
async def add_tag_to_exercise(
    exercise_id: str,
    payload: ExerciseTagsSet,
    db: AsyncSession = Depends(get_db),
    current_user: User = Depends(require_role("teacher", "admin")),
):
    # Vérifier que l'exercice existe
    ex = await db.execute(select(Exercise).where(Exercise.id == exercise_id))
    if not ex.scalar_one_or_none():
        raise HTTPException(status_code=404, detail="Exercice introuvable")

    if payload.tag_id is not None:
        tag = await _get_user_tag(payload.tag_id, current_user, db)
    elif payload.name:
        # get-or-create
        res = await db.execute(
            select(Tag).where(Tag.user_id == current_user.id, Tag.name == payload.name.strip())
        )
        tag = res.scalar_one_or_none()
        if not tag:
            tag = Tag(user_id=current_user.id, name=payload.name.strip())
            db.add(tag)
            await db.flush()
    else:
        raise HTTPException(status_code=422, detail="tag_id ou name requis")

    link = ExerciseTag(tag_id=tag.id, exercise_id=exercise_id)
    db.add(link)
    try:
        await db.commit()
    except IntegrityError:
        await db.rollback()  # déjà tagué — idempotent

    return await _exercise_tags(exercise_id, current_user, db)


@router.delete("/exercise/{exercise_id}/{tag_id}", status_code=204)
async def remove_tag_from_exercise(
    exercise_id: str,
    tag_id: int,
    db: AsyncSession = Depends(get_db),
    current_user: User = Depends(require_role("teacher", "admin")),
):
    await _get_user_tag(tag_id, current_user, db)
    await db.execute(
        delete(ExerciseTag).where(
            ExerciseTag.tag_id == tag_id,
            ExerciseTag.exercise_id == exercise_id,
        )
    )
    await db.commit()


@router.get("/library", response_model=list[dict])
async def get_library(
    db: AsyncSession = Depends(get_db),
    current_user: User = Depends(require_role("teacher", "admin")),
):
    """Retourne les tags de l'utilisateur avec leurs exercices associés."""
    tags_q = await db.execute(
        select(Tag).where(Tag.user_id == current_user.id).order_by(Tag.name)
    )
    tags = tags_q.scalars().all()

    result = []
    for tag in tags:
        exs_q = await db.execute(
            select(Exercise)
            .join(ExerciseTag, ExerciseTag.exercise_id == Exercise.id)
            .where(ExerciseTag.tag_id == tag.id)
            .order_by(Exercise.title)
        )
        exercises = exs_q.scalars().all()
        result.append({
            "tag": {"id": tag.id, "name": tag.name, "created_at": tag.created_at},
            "exercises": [
                {"id": ex.id, "title": ex.title or ex.id, "domain": ex.domain}
                for ex in exercises
            ],
        })
    return result


async def _exercise_tags(exercise_id: str, user: User, db: AsyncSession) -> list[Tag]:
    query = (
        select(Tag)
        .join(ExerciseTag, ExerciseTag.tag_id == Tag.id)
        .where(ExerciseTag.exercise_id == exercise_id, Tag.user_id == user.id)
        .order_by(Tag.name)
    )
    result = await db.execute(query)
    return result.scalars().all()
