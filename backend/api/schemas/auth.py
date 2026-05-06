import uuid
from datetime import datetime
from pydantic import BaseModel, EmailStr, field_validator

ALLOWED_EMAIL_DOMAIN = "@ac-aix-marseille.fr"


class LoginRequest(BaseModel):
    email: EmailStr
    password: str


class TokenResponse(BaseModel):
    access_token: str
    token_type: str = "bearer"
    must_change_password: bool = False


class TeacherRegister(BaseModel):
    email: str
    first_name: str
    last_name: str
    password: str
    etab_id: int

    @field_validator("email")
    @classmethod
    def email_domain(cls, v: str) -> str:
        if not v.lower().endswith(ALLOWED_EMAIL_DOMAIN):
            raise ValueError(f"L'adresse e-mail doit se terminer par {ALLOWED_EMAIL_DOMAIN}")
        return v.lower()

    @field_validator("password")
    @classmethod
    def password_length(cls, v: str) -> str:
        if len(v) < 8:
            raise ValueError("Le mot de passe doit faire au moins 8 caractères")
        return v


class EtabBrief(BaseModel):
    id: int
    name: str
    uai: str | None = None

    model_config = {"from_attributes": True}


class UserResponse(BaseModel):
    id: uuid.UUID
    email: str | None
    first_name: str | None
    last_name: str | None
    role: str
    must_change_password: bool = False
    coins: int = 0
    created_at: datetime | None = None
    etablissement: EtabBrief | None = None

    class Config:
        from_attributes = True
