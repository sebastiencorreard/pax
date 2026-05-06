from fastapi import APIRouter, Depends, HTTPException, status
from sqlalchemy.ext.asyncio import AsyncSession
from sqlalchemy import select
from sqlalchemy.orm import selectinload

from db import get_db
from models.user import User, Etablissement
from core.security import verify_password, create_access_token, hash_password
from pydantic import BaseModel
from api.schemas.auth import LoginRequest, TokenResponse, UserResponse, TeacherRegister
from api.schemas.user_admin import PasswordChangeRequest


class CoinAddRequest(BaseModel):
    amount: int
from api.deps import get_current_user

router = APIRouter(prefix="/api/auth", tags=["auth"])


@router.post("/register", response_model=UserResponse, status_code=201)
async def register_teacher(data: TeacherRegister, db: AsyncSession = Depends(get_db)):
    """Inscription publique réservée aux enseignants (@ac-aix-marseille.fr)."""
    existing = await db.execute(select(User).where(User.email == data.email))
    if existing.scalar_one_or_none():
        raise HTTPException(status_code=409, detail="Un compte avec cet e-mail existe déjà")

    etab = await db.execute(select(Etablissement).where(Etablissement.id == data.etab_id))
    if not etab.scalar_one_or_none():
        raise HTTPException(status_code=404, detail="Établissement introuvable")

    user = User(
        email=data.email,
        first_name=data.first_name,
        last_name=data.last_name,
        role="teacher",
        etab_id=data.etab_id,
        hashed_password=hash_password(data.password),
    )
    db.add(user)
    await db.commit()
    await db.refresh(user)
    return user


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
    return TokenResponse(access_token=token, must_change_password=user.must_change_password)


@router.post("/change-password")
async def change_password(
    data: PasswordChangeRequest,
    db: AsyncSession = Depends(get_db),
    current_user: User = Depends(get_current_user),
):
    # Only verify current password if NOT forced to change.
    # If forced, they just entered it to log in.
    if not current_user.must_change_password:
        if not data.current_password or not current_user.hashed_password or not verify_password(data.current_password, current_user.hashed_password):
            raise HTTPException(status_code=400, detail="Mot de passe actuel incorrect")
    
    if data.new_password != data.confirm_password:
        raise HTTPException(status_code=400, detail="Les nouveaux mots de passe ne correspondent pas")

    from core.security import hash_password
    current_user.hashed_password = hash_password(data.new_password)
    current_user.must_change_password = False
    await db.commit()
    return {"message": "Mot de passe mis à jour avec succès"}


@router.post("/guest", response_model=TokenResponse)
async def login_as_guest(db: AsyncSession = Depends(get_db)):
    """Issue a token for the singleton guest account.

    There is exactly one ``role='guest'`` user in the DB; this endpoint
    looks it up and returns a JWT for it. Guests have no password, so
    they cannot use ``/api/auth/login``. If no guest has been seeded
    (e.g. fresh DB), the endpoint returns 503 — the operator must run
    ``./create_user.sh --role guest --email guest@pax.fr --first-name Invite``.
    """
    result = await db.execute(select(User).where(User.role == "guest").limit(1))
    user = result.scalar_one_or_none()
    if user is None:
        raise HTTPException(
            status_code=status.HTTP_503_SERVICE_UNAVAILABLE,
            detail="Compte invité non configuré",
        )
    token = create_access_token(str(user.id), user.role)
    return TokenResponse(access_token=token)


@router.post("/coins/add")
async def add_coins(
    body: CoinAddRequest,
    db: AsyncSession = Depends(get_db),
    current_user: User = Depends(get_current_user),
):
    if body.amount > 0:
        current_user.coins += body.amount
        await db.commit()
    return {"coins": current_user.coins}


@router.get("/me", response_model=UserResponse)
async def me(
    db: AsyncSession = Depends(get_db),
    current_user: User = Depends(get_current_user),
):
    await db.refresh(current_user, attribute_names=["etablissement"])
    return current_user
