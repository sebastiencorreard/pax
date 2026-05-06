from pydantic import BaseModel


class EtabResponse(BaseModel):
    id: int
    uai: str
    name: str
    commune: str | None
    code_postal: str | None
    type_etab: str | None

    model_config = {"from_attributes": True}
