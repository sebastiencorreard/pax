from fastapi import APIRouter, Depends, HTTPException
from sqlalchemy.ext.asyncio import AsyncSession
from sqlalchemy import select
from sqlalchemy.orm import selectinload

from db import get_db
from models.sheet import Sheet, SheetExercise
from models.exercise import Exercise
from models.user import User
from api.schemas.sheet import SheetCreate, SheetExerciseAdd, SheetResponse, SheetDetailResponse
from api.deps import get_current_user, require_role

router = APIRouter(prefix="/api/sheets", tags=["sheets"])


@router.post("/", response_model=SheetResponse, status_code=201)
async def create_sheet(
    data: SheetCreate,
    db: AsyncSession = Depends(get_db),
    current_user: User = Depends(require_role("teacher", "admin")),
):
    sheet = Sheet(teacher_id=current_user.id, **data.model_dump())
    db.add(sheet)
    await db.commit()
    await db.refresh(sheet)
    return sheet


@router.get("/", response_model=list[SheetResponse])
async def list_sheets(
    db: AsyncSession = Depends(get_db),
    current_user: User = Depends(get_current_user),
):
    if current_user.role == "teacher":
        query = select(Sheet).where(Sheet.teacher_id == current_user.id)
    else:
        query = select(Sheet)
    result = await db.execute(query.order_by(Sheet.created_at.desc()))
    return result.scalars().all()


@router.get("/{sheet_id}", response_model=SheetDetailResponse)
async def get_sheet(
    sheet_id: int,
    db: AsyncSession = Depends(get_db),
    _: User = Depends(get_current_user),
):
    result = await db.execute(
        select(Sheet)
        .where(Sheet.id == sheet_id)
        .options(selectinload(Sheet.items).selectinload(SheetExercise.exercise))
    )
    sheet = result.scalar_one_or_none()
    if not sheet:
        raise HTTPException(status_code=404, detail="Feuille introuvable")
    return sheet


@router.post("/{sheet_id}/exercises", status_code=201)
async def add_exercise_to_sheet(
    sheet_id: int,
    data: SheetExerciseAdd,
    db: AsyncSession = Depends(get_db),
    current_user: User = Depends(require_role("teacher", "admin")),
):
    # Vérifie que la feuille existe et appartient à ce prof
    result = await db.execute(select(Sheet).where(Sheet.id == sheet_id))
    sheet = result.scalar_one_or_none()
    if not sheet:
        raise HTTPException(status_code=404, detail="Feuille introuvable")
    if sheet.teacher_id != current_user.id and current_user.role != "admin":
        raise HTTPException(status_code=403, detail="Feuille appartenant à un autre enseignant")

    # Vérifie que l'exercice existe
    result = await db.execute(select(Exercise).where(Exercise.id == data.exercise_id))
    if not result.scalar_one_or_none():
        raise HTTPException(status_code=404, detail="Exercice introuvable")

    item = SheetExercise(sheet_id=sheet_id, **data.model_dump())
    db.add(item)
    await db.commit()
    return {"status": "ok"}


@router.delete("/{sheet_id}/exercises/{item_id}", status_code=204)
async def remove_exercise_from_sheet(
    sheet_id: int,
    item_id: int,
    db: AsyncSession = Depends(get_db),
    current_user: User = Depends(require_role("teacher", "admin")),
):
    result = await db.execute(
        select(SheetExercise).where(
            SheetExercise.id == item_id,
            SheetExercise.sheet_id == sheet_id,
        )
    )
    item = result.scalar_one_or_none()
    if not item:
        raise HTTPException(status_code=404, detail="Introuvable")
    await db.delete(item)
    await db.commit()
