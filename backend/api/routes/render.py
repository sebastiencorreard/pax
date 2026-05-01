from fastapi import APIRouter, Depends, HTTPException
from pydantic import BaseModel
from sqlalchemy.ext.asyncio import AsyncSession
from sqlalchemy import select

from db import get_db
from models.exercise import Exercise
from models.user import User
from api.deps import get_current_user
from core.oef.engine import load_and_render, AnswerDef

router = APIRouter(prefix="/api/render", tags=["render"])


class AnswerOut(BaseModel):
    input_name: str
    label: str
    answer_type: str
    options: dict
    weight: float
    logical_name: str = ""


class RenderOut(BaseModel):
    exercise_id: str
    title: str
    lang: str
    statement_segments: list[dict]
    answers: list[AnswerOut]
    hint_html: str
    seed: int
    condition: dict | None = None


@router.get("/{exercise_id}", response_model=RenderOut)
async def render_exercise(
    exercise_id: str,
    seed: int | None = None,
    db: AsyncSession = Depends(get_db),
    _: User = Depends(get_current_user),
):
    result = await db.execute(select(Exercise).where(Exercise.id == exercise_id))
    exercise = result.scalar_one_or_none()
    if not exercise:
        raise HTTPException(status_code=404, detail="Exercice introuvable")

    try:
        rendered = load_and_render(exercise.oef_path, seed=seed)
    except FileNotFoundError:
        raise HTTPException(status_code=404, detail=f"Fichier OEF introuvable : {exercise.oef_path}")
    except Exception as e:
        raise HTTPException(status_code=500, detail=f"Erreur de rendu : {str(e)}")

    return RenderOut(
        exercise_id=exercise_id,
        title=rendered.title,
        lang=rendered.lang,
        statement_segments=rendered.statement_segments,
        answers=[
            AnswerOut(
                input_name=a.input_name,
                label=a.label,
                answer_type=a.answer_type,
                options=a.options,
                weight=a.weight,
                logical_name=a.logical_name,
            )
            for a in rendered.answers
        ],
        hint_html=rendered.hint_html,
        seed=rendered.seed,
        condition=rendered.condition,
    )


class DebugAnswerOut(BaseModel):
    input_name: str
    label: str
    answer_type: str
    expected: str


class DebugOut(BaseModel):
    exercise_id: str
    seed: int
    solution_html: str
    answers: list[DebugAnswerOut]


@router.get("/{exercise_id}/debug", response_model=DebugOut)
async def render_exercise_debug(
    exercise_id: str,
    seed: int | None = None,
    db: AsyncSession = Depends(get_db),
    _: User = Depends(get_current_user),
):
    """Renvoie la solution et les réponses attendues. Réservé au mode debug du front."""
    result = await db.execute(select(Exercise).where(Exercise.id == exercise_id))
    exercise = result.scalar_one_or_none()
    if not exercise:
        raise HTTPException(status_code=404, detail="Exercice introuvable")
    try:
        rendered = load_and_render(exercise.oef_path, seed=seed)
    except FileNotFoundError:
        raise HTTPException(status_code=404, detail=f"Fichier OEF introuvable : {exercise.oef_path}")
    except Exception as e:
        raise HTTPException(status_code=500, detail=f"Erreur de rendu : {str(e)}")

    return DebugOut(
        exercise_id=exercise_id,
        seed=rendered.seed,
        solution_html=rendered.solution_html,
        answers=[
            DebugAnswerOut(
                input_name=a.input_name,
                label=a.label,
                answer_type=a.answer_type,
                expected=a.expected,
            )
            for a in rendered.answers
        ],
    )
