from fastapi import APIRouter, Depends, HTTPException
from sqlalchemy.ext.asyncio import AsyncSession
from sqlalchemy import select, func, delete, or_
from sqlalchemy.exc import IntegrityError

from db import get_db
from models.tag import Tag, ExerciseTag
from models.exercise import Exercise
from models.user import User
from api.schemas.tag import (
    TagCreate,
    TagResponse,
    TagWithCountResponse,
    ExerciseTagsSet,
)
from api.deps import require_role

router = APIRouter(prefix="/api/tags", tags=["tags"])


def _accessible(user_id):
    """A tag is accessible to a user if they own it or it is shared.

    Takes the *id* (not the ORM object): a commit/rollback can expire the
    ``current_user`` instance, and re-reading an attribute off an expired
    object would trigger a forbidden async lazy-load.
    """
    return or_(Tag.user_id == user_id, Tag.is_shared.is_(True))


async def _get_accessible_tag(tag_id: int, user_id, db: AsyncSession) -> Tag:
    result = await db.execute(
        select(Tag).where(Tag.id == tag_id, _accessible(user_id))
    )
    tag = result.scalar_one_or_none()
    if not tag:
        raise HTTPException(status_code=404, detail="Tag introuvable")
    return tag


@router.get("/", response_model=list[TagWithCountResponse])
async def list_tags(
    db: AsyncSession = Depends(get_db),
    current_user: User = Depends(require_role("teacher", "admin")),
):
    uid = current_user.id
    count_sq = (
        select(ExerciseTag.tag_id, func.count(ExerciseTag.id).label("cnt"))
        .group_by(ExerciseTag.tag_id)
        .subquery()
    )
    query = (
        select(Tag, func.coalesce(count_sq.c.cnt, 0).label("exercise_count"))
        .outerjoin(count_sq, Tag.id == count_sq.c.tag_id)
        .where(_accessible(uid))
        .order_by(Tag.is_shared.desc(), Tag.name)
    )
    rows = (await db.execute(query)).all()
    return [
        TagWithCountResponse(
            id=tag.id,
            name=tag.name,
            created_at=tag.created_at,
            is_shared=tag.is_shared,
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
        raise HTTPException(
            status_code=409, detail=f"Le tag « {payload.name} » existe déjà"
        )
    return tag


@router.get("/{tag_id}/exercises")
async def get_tag_exercises(
    tag_id: int,
    db: AsyncSession = Depends(get_db),
    current_user: User = Depends(require_role("teacher", "admin")),
):
    """Retourne les exercices associés à un tag (perso ou partagé)."""
    tag = await _get_accessible_tag(tag_id, current_user.id, db)
    exs_q = await db.execute(
        select(Exercise)
        .join(ExerciseTag, ExerciseTag.exercise_id == Exercise.id)
        .where(ExerciseTag.tag_id == tag_id)
        .order_by(Exercise.title)
    )
    exercises = exs_q.scalars().all()
    return {
        "tag": {"id": tag.id, "name": tag.name, "created_at": tag.created_at, "is_shared": tag.is_shared},
        "exercises": [
            {
                "id": ex.id,
                "title": ex.title or ex.id,
                "domain": ex.domain,
                "level": ex.level,
            }
            for ex in exercises
        ],
    }


@router.delete("/{tag_id}", status_code=204)
async def delete_tag(
    tag_id: int,
    db: AsyncSession = Depends(get_db),
    current_user: User = Depends(require_role("teacher", "admin")),
):
    tag = await _get_accessible_tag(tag_id, current_user.id, db)
    if tag.is_shared:
        raise HTTPException(
            status_code=403, detail="Un tag partagé ne peut pas être supprimé"
        )
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
        .where(ExerciseTag.exercise_id == exercise_id, _accessible(current_user.id))
        .order_by(Tag.is_shared.desc(), Tag.name)
    )
    result = await db.execute(query)
    return list(result.scalars().all())


@router.post("/exercise/{exercise_id}", response_model=list[TagResponse])
async def add_tag_to_exercise(
    exercise_id: str,
    payload: ExerciseTagsSet,
    db: AsyncSession = Depends(get_db),
    current_user: User = Depends(require_role("teacher", "admin")),
):
    # Capturé avant tout commit/rollback (qui expirerait l'objet current_user).
    uid = current_user.id

    # Vérifier que l'exercice existe
    ex = await db.execute(select(Exercise).where(Exercise.id == exercise_id))
    if not ex.scalar_one_or_none():
        raise HTTPException(status_code=404, detail="Exercice introuvable")

    if payload.tag_id is not None:
        tag = await _get_accessible_tag(payload.tag_id, uid, db)
    elif payload.name:
        name = payload.name.strip()
        # Prefer an existing shared tag with this name (e.g. the "dbg …" tags),
        # then the user's own; otherwise create a personal tag.
        res = await db.execute(
            select(Tag)
            .where(Tag.name == name, _accessible(uid))
            .order_by(Tag.is_shared.desc())
        )
        tag = res.scalars().first()
        if not tag:
            tag = Tag(user_id=uid, name=name)
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

    return await _exercise_tags(exercise_id, uid, db)


@router.delete("/exercise/{exercise_id}/{tag_id}", status_code=204)
async def remove_tag_from_exercise(
    exercise_id: str,
    tag_id: int,
    db: AsyncSession = Depends(get_db),
    current_user: User = Depends(require_role("teacher", "admin")),
):
    # Any teacher may remove a shared (debug) tag link, just as any may add it.
    await _get_accessible_tag(tag_id, current_user.id, db)
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
    """Retourne les tags de l'utilisateur (et partagés) avec leurs exercices."""
    tags_q = await db.execute(
        select(Tag)
        .where(_accessible(current_user.id))
        .order_by(Tag.is_shared.desc(), Tag.name)
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
        result.append(
            {
                "tag": {"id": tag.id, "name": tag.name, "created_at": tag.created_at, "is_shared": tag.is_shared},
                "exercises": [
                    {"id": ex.id, "title": ex.title or ex.id, "domain": ex.domain}
                    for ex in exercises
                ],
            }
        )
    return result


async def _exercise_tags(exercise_id: str, user_id, db: AsyncSession) -> list[Tag]:
    query = (
        select(Tag)
        .join(ExerciseTag, ExerciseTag.tag_id == Tag.id)
        .where(ExerciseTag.exercise_id == exercise_id, _accessible(user_id))
        .order_by(Tag.is_shared.desc(), Tag.name)
    )
    result = await db.execute(query)
    return list(result.scalars().all())
