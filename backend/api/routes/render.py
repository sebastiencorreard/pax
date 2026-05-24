from fastapi import APIRouter, Depends, HTTPException
from pydantic import BaseModel
from sqlalchemy.ext.asyncio import AsyncSession
from sqlalchemy import select

from config import settings
from db import get_db
from models.exercise import Exercise
from models.user import User
from api.deps import get_current_user
from core.oef.engine import load_and_render

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
    exercise_type: str = "standard"
    is_dynsteps: bool = False
    current_step: int | None = None
    total_steps: int | None = None
    type_meta: dict = {}
    css: str | None = None


@router.get("/{exercise_id}", response_model=RenderOut)
async def render_exercise(
    exercise_id: str,
    seed: int | None = None,
    m_step: int | None = None,
    db: AsyncSession = Depends(get_db),
    _: User = Depends(get_current_user),
):
    result = await db.execute(select(Exercise).where(Exercise.id == exercise_id))
    exercise = result.scalar_one_or_none()
    if not exercise:
        raise HTTPException(status_code=404, detail="Exercice introuvable")

    try:
        rendered = load_and_render(exercise.oef_path, seed=seed, m_step=m_step)
    except FileNotFoundError:
        raise HTTPException(
            status_code=404, detail=f"Fichier OEF introuvable : {exercise.oef_path}"
        )
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
        exercise_type=rendered.exercise_type,
        is_dynsteps=rendered.is_dynsteps,
        current_step=rendered.current_step,
        total_steps=rendered.total_steps,
        type_meta=rendered.type_meta,
        css=rendered.css,
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
    m_step: int | None = None,
    db: AsyncSession = Depends(get_db),
    current_user: User = Depends(get_current_user),
):
    """Renvoie la solution et les réponses attendues. Réservé au mode debug du front.

    Double-gated to keep the expected answer away from students:
    - Off entirely in production: 404 unless ``PAX_DEBUG=1`` is set in
      the environment. 404 (not 403) avoids advertising the endpoint's
      existence.
    - Even with the env flag, only teachers/admins can call it — a
      student account is rejected (also as 404 for the same reason).
    """
    if not settings.pax_debug or current_user.role not in ("teacher", "admin", "super_admin"):
        raise HTTPException(status_code=404, detail="Not found")

    from core.answer.strategies.standard import pretty_expected as _pretty_expected

    result = await db.execute(select(Exercise).where(Exercise.id == exercise_id))
    exercise = result.scalar_one_or_none()
    if not exercise:
        raise HTTPException(status_code=404, detail="Exercice introuvable")
    try:
        rendered = load_and_render(exercise.oef_path, seed=seed, m_step=m_step)
    except FileNotFoundError:
        raise HTTPException(
            status_code=404, detail=f"Fichier OEF introuvable : {exercise.oef_path}"
        )
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
                expected=_pretty_expected(a.expected, a.answer_type),
            )
            for a in rendered.answers
        ],
    )
