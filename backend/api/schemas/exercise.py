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

    class Config:
        from_attributes = True


class ExerciseRendered(BaseModel):
    """Exercice prêt à être affiché : métadonnées + HTML de l'énoncé."""
    id: str
    title: str | None
    html: str        # énoncé rendu
    seed: int        # graine utilisée (pour reproductibilité)
