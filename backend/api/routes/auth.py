from fastapi import APIRouter, Depends, HTTPException, status
from sqlalchemy.ext.asyncio import AsyncSession
from sqlalchemy import select

from db import get_db
from models.user import User
from core.security import verify_password, create_access_token
from api.schemas.auth import LoginRequest, TokenResponse, UserResponse
from api.deps import get_current_user

router = APIRouter(prefix="/api/auth", tags=["auth"])


# User creation is admin-only and lives in `backend/scripts/create_user.py`,
# invoked via `docker compose exec backend python scripts/create_user.py …`.
# There is intentionally no public registration endpoint.


@router.post("/login", response_model=TokenResponse)
async def login(data: LoginRequest, db: AsyncSession = Depends(get_db)):
    result = await db.execute(select(User).where(User.email == data.email))
    user = result.scalar_one_or_none()

    if (
        not user
        or not user.hashed_password
        or not verify_password(data.password, user.hashed_password)
    ):
        raise HTTPException(
            status_code=status.HTTP_401_UNAUTHORIZED,
            detail="Email ou mot de passe incorrect",
        )

    token = create_access_token(str(user.id), user.role)
    return TokenResponse(access_token=token)


@router.get("/me", response_model=UserResponse)
async def me(current_user: User = Depends(get_current_user)):
    return current_user
