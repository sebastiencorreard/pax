import html
import os
import re
import unicodedata
from fastapi import APIRouter, Depends, HTTPException
from sqlalchemy.ext.asyncio import AsyncSession
from sqlalchemy import select

from db import get_db
from models.exercise import Exercise
from api.schemas.exercise import ExerciseResponse
from api.deps import get_current_user
from models.user import User
from core.oef.engine import find_def_path

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


def _parse_exfile(file_path: str) -> dict[str, str]:
    """Parse a WIMS per-exercise metadata file (Extitles, Exkeywords, Exauthors).

    Format: one ``stem:value`` line per exercise (ISO-8859-1 encoded).
    Returns a dict mapping exercise stem → raw value string.
    """
    try:
        with open(file_path, encoding="iso-8859-1") as f:
            lines = f.readlines()
    except FileNotFoundError:
        return {}
    result: dict[str, str] = {}
    for line in lines:
        line = line.strip()
        if not line or line.startswith("#"):
            continue
        if ":" in line:
            stem, _, value = line.partition(":")
            result[stem.strip()] = value.strip()
    return result


def _split_csv(s: str) -> list[str]:
    """Split a comma-separated string into a cleaned list, skipping blanks."""
    return [item.strip() for item in s.split(",") if item.strip()]


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


def _title_sort_key(title: str) -> list:
    """Natural, case/accent-insensitive sort key for an exercise title.

    Exercises are listed by their displayed title (not their filename). The key
    folds accents and case so "Évolution" sorts next to "Equation", and splits
    digit runs into ints so "Question 9" precedes "Question 10" (a plain string
    sort would put "10" first). WIMS itself orders via the module's `Exindex`,
    which we don't track; an alphabetical title sort is the closest intuitive
    equivalent and, here, also puts the "Course…" entries ahead of "Question…".
    """
    folded = "".join(
        c for c in unicodedata.normalize("NFKD", title or "") if not unicodedata.combining(c)
    ).casefold()
    return [
        int(tok) if tok.isdigit() else tok
        for tok in re.split(r"(\d+)", folded)
    ]


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
    # Per-module cache of Exauthors / Exkeywords dicts (loaded once per module)
    _ex_authors: dict[str, dict[str, str]] = {}
    _ex_keywords: dict[str, dict[str, str]] = {}

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
                # WIMS titles carry HTML entities (e.g. "Roue 1 en &euro;");
                # decode them to text since the sidebar renders titles plainly.
                "title": html.unescape(idx.get("title") or mod_name),
                "description": idx.get("description") or "",
                "author": _format_author(raw_author),
                "keywords": _split_csv(idx.get("keywords", "")),
                "domain": ex.domain or "",
                "level": ex.level or "",
                "lang": ex.lang,
                "exercises": [],
            }
            _ex_authors[mod_name] = _parse_exfile(os.path.join(mod_dir, "Exauthors"))
            _ex_keywords[mod_name] = _parse_exfile(os.path.join(mod_dir, "Exkeywords"))

        stem = os.path.splitext(os.path.basename(ex.oef_path))[0]
        modules[mod_name]["exercises"].append(
            {
                "id": ex.id,
                "title": html.unescape(ex.title or os.path.basename(ex.oef_path)),
                "has_def": find_def_path(ex.oef_path) is not None,
                "author": _format_author(_ex_authors[mod_name].get(stem, "")),
                "keywords": _split_csv(_ex_keywords[mod_name].get(stem, "")),
            }
        )

    # Within each module, list exercises by their (displayed) title — not the
    # filename the DB query happened to order by.
    for mod in modules.values():
        mod["exercises"].sort(key=lambda e: _title_sort_key(e["title"]))

    # Sort modules by domain then title
    return sorted(
        modules.values(),
        key=lambda m: (m["domain"], m["title"].lower()),
    )


def _module_title(oef_path: str) -> str | None:
    """Read the module's INDEX file and return its `title` field, if any."""
    mod_dir = _module_dir_from_path(oef_path)
    if not mod_dir:
        return None
    idx = _parse_index(os.path.join(mod_dir, "INDEX"))
    return idx.get("title") or None


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
    payload = ExerciseResponse.model_validate(exercise)
    payload.module_title = _module_title(exercise.oef_path)
    return payload


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
