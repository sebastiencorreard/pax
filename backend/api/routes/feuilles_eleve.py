"""Les feuilles vues par l'élève : la liste, puis le travail sur chacune.

Cf. `docs/feuilles-eleve.md` §3.3, étape 3. L'élève ne voit que les feuilles
affectées à ses classes et visibles (`api/feuilles.py`) ; les notes sont
recalculées de ses tirages par le moteur de WIMS (`core/note_feuille.py`).
"""

from fastapi import APIRouter, Depends, HTTPException
from sqlalchemy import select
from sqlalchemy.ext.asyncio import AsyncSession
from sqlalchemy.orm import selectinload

from api.deps import require_role
from api.feuilles import ACTIVE, PERIMEE, affectation_eleve, bilan_eleve, note_enregistrable
from db import get_db
from models.class_model import Class, ClassStudent
from models.sheet import Sheet, SheetClass, SheetExercise
from models.user import User

router = APIRouter(prefix="/api/feuilles", tags=["feuilles"])


async def _feuille(db: AsyncSession, sheet_id: int) -> Sheet | None:
    return (await db.execute(
        select(Sheet).where(Sheet.id == sheet_id)
        .options(selectinload(Sheet.items).selectinload(SheetExercise.exercise))
    )).scalar_one_or_none()


def _affectation(aff: SheetClass, classe: Class) -> dict:
    return {
        "class_id": classe.id, "class_name": classe.name, "status": aff.status,
        "open_at": aff.open_at, "close_at": aff.close_at,
        "note_enregistrable": note_enregistrable(aff),
    }


@router.get("/mes")
async def mes_feuilles(
    db: AsyncSession = Depends(get_db),
    eleve: User = Depends(require_role("student")),
):
    """Les feuilles visibles de l'élève, avec sa note sur chacune."""
    lignes = (await db.execute(
        select(SheetClass, Class)
        .join(Class, Class.id == SheetClass.class_id)
        .join(ClassStudent, ClassStudent.class_id == SheetClass.class_id)
        .where(ClassStudent.student_id == eleve.id,
               SheetClass.status.in_((ACTIVE, PERIMEE)))
        .order_by(SheetClass.sheet_id, SheetClass.status)
    )).all()
    vues: dict[int, dict] = {}
    for aff, classe in lignes:
        if aff.sheet_id in vues:
            continue  # reçue par deux classes : l'affectation active d'abord
        if (await affectation_eleve(db, eleve.id, aff.sheet_id)) is None:
            continue  # pas encore ouverte
        feuille = await _feuille(db, aff.sheet_id)
        if feuille is None:
            continue
        bilan = await bilan_eleve(db, eleve.id, feuille)
        vues[aff.sheet_id] = {
            "sheet_id": feuille.id, "title": feuille.title, "description": feuille.description,
            **_affectation(aff, classe),
            "note": bilan["note"], "cumul": bilan["cumul"], "qualite": bilan["qualite"],
            "exercices": len([e for e in bilan["exercices"] if e["actif"]]),
        }
    return list(vues.values())


@router.get("/{sheet_id}")
async def ma_feuille(
    sheet_id: int,
    db: AsyncSession = Depends(get_db),
    eleve: User = Depends(require_role("student")),
):
    """Le travail de l'élève sur une feuille : exercice par exercice, et la note."""
    aff = await affectation_eleve(db, eleve.id, sheet_id)
    feuille = await _feuille(db, sheet_id) if aff else None
    if aff is None or feuille is None:
        raise HTTPException(status_code=404, detail="Feuille introuvable")
    classe = await db.get(Class, aff.class_id)
    bilan = await bilan_eleve(db, eleve.id, feuille)
    titres = {i.id: (i.exercise.title if i.exercise else None) for i in feuille.items}
    # Un exercice désactivé par l'enseignant n'est pas montré.
    exercices = [{**e, "title": titres.get(e["id"])} for e in bilan["exercices"] if e["actif"]]
    return {
        "sheet_id": feuille.id, "title": feuille.title, "description": feuille.description,
        **_affectation(aff, classe),
        "note_formule": feuille.note_formule, "note_indicateur": feuille.note_indicateur,
        **{k: bilan[k] for k in ("note", "cumul", "qualite", "meilleur", "niveau")},
        "exercices": exercices,
    }
