"""Modèles de données partagés entre les stratégies de vérification et la route."""

from __future__ import annotations
from pydantic import BaseModel


class AnswerResult(BaseModel):
    input_name: str
    correct: bool
    score: float
    method: str
    reply: str | None = None
    expected: str | None = None
    status: str = "ok"
    detail: str | None = None
