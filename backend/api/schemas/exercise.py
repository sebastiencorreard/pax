from pydantic import BaseModel


class ExerciseResponse(BaseModel):
    id: str
    oef_path: str
    title: str | None
    module: str | None
    level: str | None
    domain: str | None
    lang: str
    keywords: list[str] | None
    statement_ok: bool | None = None
    answer_ok: bool | None = None
    check_ok: bool | None = None

    class Config:
        from_attributes = True


class ExerciseQAUpdate(BaseModel):
    statement_ok: bool | None = None
    answer_ok: bool | None = None
    check_ok: bool | None = None


class ExerciseRendered(BaseModel):
    """Exercice prêt à être affiché : métadonnées + HTML de l'énoncé."""

    id: str
    title: str | None
    html: str  # énoncé rendu
    seed: int  # graine utilisée (pour reproductibilité)
