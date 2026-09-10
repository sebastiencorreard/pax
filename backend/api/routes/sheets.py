from fastapi import APIRouter, Depends, HTTPException
from sqlalchemy.ext.asyncio import AsyncSession
from sqlalchemy import select
from sqlalchemy.orm import selectinload

from db import get_db
from models.sheet import Sheet, SheetExercise
from models.exercise import Exercise
from models.user import User
from api.schemas.sheet import (
    SheetCreate, SheetUpdate, SheetExerciseAdd, SheetExerciseUpdate,
    SheetResponse, SheetDetailResponse, SheetItemResponse,
)
from api.deps import get_current_user, require_role
from core.oef.def_engine import table_severite

router = APIRouter(prefix="/api/sheets", tags=["sheets"])


async def _feuille_modifiable(db: AsyncSession, sheet_id: int, user: User) -> Sheet:
    """La feuille, si elle existe et que cet utilisateur peut la modifier."""
    result = await db.execute(select(Sheet).where(Sheet.id == sheet_id))
    sheet = result.scalar_one_or_none()
    if not sheet:
        raise HTTPException(status_code=404, detail="Feuille introuvable")
    if sheet.teacher_id != user.id and user.role != "admin":
        raise HTTPException(status_code=403, detail="Feuille appartenant à un autre enseignant")
    return sheet


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


# Déclarée avant `/{sheet_id}`, qui sinon la prendrait pour un identifiant.
@router.get("/severite")
async def get_severite(_: User = Depends(get_current_user)):
    """Les neuf niveaux de sévérité et ce que chacun commande (`oef/helpseverity`)."""
    return table_severite()


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
    await _feuille_modifiable(db, sheet_id, current_user)

    # Vérifie que l'exercice existe
    result = await db.execute(select(Exercise).where(Exercise.id == data.exercise_id))
    if not result.scalar_one_or_none():
        raise HTTPException(status_code=404, detail="Exercice introuvable")

    item = SheetExercise(sheet_id=sheet_id, **data.model_dump())
    db.add(item)
    await db.commit()
    return {"status": "ok"}


@router.patch("/{sheet_id}", response_model=SheetResponse)
async def update_sheet(
    sheet_id: int,
    data: SheetUpdate,
    db: AsyncSession = Depends(get_db),
    current_user: User = Depends(require_role("teacher", "admin")),
):
    sheet = await _feuille_modifiable(db, sheet_id, current_user)
    for field, value in data.model_dump(exclude_unset=True).items():
        setattr(sheet, field, value)
    await db.commit()
    await db.refresh(sheet)
    return sheet


@router.delete("/{sheet_id}", status_code=204)
async def delete_sheet(
    sheet_id: int,
    db: AsyncSession = Depends(get_db),
    current_user: User = Depends(require_role("teacher", "admin")),
):
    sheet = await _feuille_modifiable(db, sheet_id, current_user)
    await db.delete(sheet)
    await db.commit()


async def _exercice_de_feuille(
    db: AsyncSession, sheet_id: int, item_id: int
) -> SheetExercise:
    result = await db.execute(
        select(SheetExercise)
        .where(SheetExercise.id == item_id, SheetExercise.sheet_id == sheet_id)
        .options(selectinload(SheetExercise.exercise))
    )
    item = result.scalar_one_or_none()
    if not item:
        raise HTTPException(status_code=404, detail="Introuvable")
    return item


@router.patch("/{sheet_id}/exercises/{item_id}", response_model=SheetItemResponse)
async def update_sheet_exercise(
    sheet_id: int,
    item_id: int,
    data: SheetExerciseUpdate,
    db: AsyncSession = Depends(get_db),
    current_user: User = Depends(require_role("teacher", "admin")),
):
    """Règle un exercice posé : points, prérequis, et ce que WIMS règle au même
    endroit — le niveau de sévérité et les `confparm` du module."""
    await _feuille_modifiable(db, sheet_id, current_user)
    item = await _exercice_de_feuille(db, sheet_id, item_id)
    for field, value in data.model_dump(exclude_unset=True).items():
        setattr(item, field, value)
    await db.commit()
    return await _exercice_de_feuille(db, sheet_id, item_id)


@router.delete("/{sheet_id}/exercises/{item_id}", status_code=204)
async def remove_exercise_from_sheet(
    sheet_id: int,
    item_id: int,
    db: AsyncSession = Depends(get_db),
    current_user: User = Depends(require_role("teacher", "admin")),
):
    # Sans cette vérification, n'importe quel enseignant retirait un exercice
    # de la feuille d'un collègue.
    await _feuille_modifiable(db, sheet_id, current_user)
    item = await _exercice_de_feuille(db, sheet_id, item_id)
    await db.delete(item)
    await db.commit()
