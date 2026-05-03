import os
from fastapi import APIRouter, Depends, HTTPException
from sqlalchemy.ext.asyncio import AsyncSession
from sqlalchemy import select

from db import get_db
from models.exercise import Exercise
from api.schemas.exercise import ExerciseResponse, ExerciseQAUpdate
from api.deps import get_current_user
from models.user import User

router = APIRouter(prefix="/api/exercises", tags=["exercises"])


def _parse_index(index_path: str) -> dict:
    """Parse a WIMS INDEX file (key=value lines, ISO-8859-1 encoded)."""
    try:
        with open(index_path, encoding="iso-8859-1") as f:
            lines = f.readlines()
    except FileNotFoundError:
        return {}
    result = {}
    for line in lines:
        line = line.strip()
        if not line or line.startswith("#"):
            continue
        if "=" in line:
            k, v = line.split("=", 1)
            result[k.strip()] = v.strip()
    return result


def _module_from_path(oef_path: str) -> str:
    """Extract the module directory name from an oef_path.

    e.g. /ressources/H4/algebra/OEFevalwimsequ.fr/src/foo.oef
         -> OEFevalwimsequ.fr
    """
    parts = oef_path.replace("\\", "/").split("/")
    # structure: .../level/domain/module/src/exercise.oef
    return parts[-3] if len(parts) >= 4 else ""


def _module_dir_from_path(oef_path: str) -> str:
    """Return the module directory path (two levels above the .oef file)."""
    return os.path.dirname(os.path.dirname(oef_path))


def _format_author(raw: str) -> str:
    """Convert 'Firstname,Lastname' to 'Firstname Lastname'."""
    return raw.replace(",", " ").strip()


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


@router.get("/modules")
async def list_modules(
    level: str | None = None,
    domain: str | None = None,
    lang: str = "fr",
    db: AsyncSession = Depends(get_db),
    _: User = Depends(get_current_user),
):
    """Return exercises grouped by module, with metadata from the INDEX file."""
    query = select(Exercise).where(Exercise.lang == lang)
    if level:
        query = query.where(Exercise.level == level)
    if domain:
        query = query.where(Exercise.domain == domain)
    query = query.order_by(Exercise.oef_path)

    result = await db.execute(query)
    exercises = result.scalars().all()

    # Group by module directory
    modules: dict[str, dict] = {}
    for ex in exercises:
        mod_name = _module_from_path(ex.oef_path)
        if not mod_name:
            continue
        if mod_name not in modules:
            mod_dir = _module_dir_from_path(ex.oef_path)
            idx = _parse_index(os.path.join(mod_dir, "INDEX"))
            raw_author = idx.get("author") or idx.get("maintainer") or ""
            modules[mod_name] = {
                "module": mod_name,
                "title": idx.get("title") or mod_name,
                "description": idx.get("description") or "",
                "author": _format_author(raw_author),
                "domain": ex.domain or "",
                "level": ex.level or "",
                "lang": ex.lang,
                "exercises": [],
            }
        modules[mod_name]["exercises"].append(
            {
                "id": ex.id,
                "title": ex.title or os.path.basename(ex.oef_path),
                "statement_ok": ex.statement_ok,
                "answer_ok": ex.answer_ok,
                "check_ok": ex.check_ok,
            }
        )

    # Sort modules by domain then title
    return sorted(
        modules.values(),
        key=lambda m: (m["domain"], m["title"].lower()),
    )


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


@router.patch("/{exercise_id}/qa", response_model=ExerciseResponse)
async def update_exercise_qa(
    exercise_id: str,
    payload: ExerciseQAUpdate,
    db: AsyncSession = Depends(get_db),
    _: User = Depends(get_current_user),
):
    result = await db.execute(select(Exercise).where(Exercise.id == exercise_id))
    exercise = result.scalar_one_or_none()
    if not exercise:
        raise HTTPException(status_code=404, detail="Exercice introuvable")
    data = payload.model_dump(exclude_unset=True)
    for field, value in data.items():
        setattr(exercise, field, value)
    await db.commit()
    await db.refresh(exercise)
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
        raise HTTPException(
            status_code=404, detail="Fichier OEF introuvable sur disque"
        )
    return {"oef_path": exercise.oef_path, "content": content}
