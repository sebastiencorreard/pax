from pydantic import BaseModel
import uuid

class PasswordResetResponse(BaseModel):
    user_id: uuid.UUID
    temporary_password: str

class PasswordChangeRequest(BaseModel):
    current_password: str | None = None
    new_password: str
    confirm_password: str
