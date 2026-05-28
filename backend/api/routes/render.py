from fastapi import APIRouter, Depends, HTTPException
from pydantic import BaseModel
from sqlalchemy.ext.asyncio import AsyncSession
from sqlalchemy import select

from config import settings
from db import get_db
from models.exercise import Exercise
from models.user import User
from api.deps import get_current_user
from core.oef.engine import load_and_render, find_def_path
from core.chrono import module_scoredelay, get_or_create_started_at

router = APIRouter(prefix="/api/render", tags=["render"])


class AnswerOut(BaseModel):
    input_name: str
    label: str
    answer_type: str
    options: dict
    weight: float
    logical_name: str = ""


class ChronoOut(BaseModel):
    """Chronometer state sent to the client (display only). The server
    keeps the canonical ``started_at`` in Redis and re-reads it on /check;
    the client uses this payload to render a countdown but never to
    influence scoring."""
    soft: int  # T1 — countdown displays this value down to 0
    hard: int  # T2 — past this the score is zero (no client display)
    started_at: str  # ISO 8601 UTC, the server's anchor for elapsed time
    server_now: str  # so the client can correct for clock skew


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
    chrono: ChronoOut | None = None


@router.get("/{exercise_id}", response_model=RenderOut)
async def render_exercise(
    exercise_id: str,
    seed: int | None = None,
    m_step: int | None = None,
    db: AsyncSession = Depends(get_db),
    current_user: User = Depends(get_current_user),
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

    # Chrono — look up the module's `!default scoredelay` and seed (or read
    # back) the per-(user, exercise, seed) start timestamp from Redis. For
    # dynsteps/course exercises the chrono spans all steps, so we key on
    # the seed alone (not m_step) — same seed = same session.
    chrono_out: ChronoOut | None = None
    sd = module_scoredelay(find_def_path(exercise.oef_path))
    if sd is not None:
        from datetime import datetime, timezone
        started_at = get_or_create_started_at(
            user_id=str(current_user.id),
            exercise_id=exercise_id,
            seed=rendered.seed,
            scoredelay=sd,
        )
        chrono_out = ChronoOut(
            soft=sd.soft,
            hard=sd.hard,
            started_at=started_at.isoformat(),
            server_now=datetime.now(timezone.utc).isoformat(),
        )

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
        chrono=chrono_out,
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
