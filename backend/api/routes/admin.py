import uuid
from fastapi import APIRouter, Depends, HTTPException, Query
from sqlalchemy.ext.asyncio import AsyncSession
from sqlalchemy import select, and_

from db import get_db
from models.user import User
from core.security import hash_password
from api.schemas.class_schema import UserCreate, UserResponse
from api.deps import get_current_user, require_role

router = APIRouter(prefix="/api/admin", tags=["admin"])

_TEACHER_CREATABLE = {"student"}
_ADMIN_CREATABLE   = {"student", "teacher"}
_SUPERADMIN_CREATABLE = {"student", "teacher"}


def _etab_filter(q, current_user: User):
    """Ajoute un filtre sur l'établissement si l'user n'est pas super_admin."""
    if current_user.role == "super_admin":
        return q
    return q.where(User.etab_id == current_user.etab_id)


@router.get("/users/", response_model=list[UserResponse])
async def list_users(
    role: str | None = Query(None),
    db: AsyncSession = Depends(get_db),
    current_user: User = Depends(require_role("teacher", "admin", "super_admin")),
):
    q = select(User)
    if current_user.role == "teacher":
        q = q.where(and_(User.role == "student", User.etab_id == current_user.etab_id))
    else:
        q = _etab_filter(q, current_user)
        if role:
            q = q.where(User.role == role)
        else:
            # admin/super_admin ne liste pas les guests
            q = q.where(User.role != "guest")
    q = q.order_by(User.last_name, User.first_name)
    result = await db.execute(q)
    return result.scalars().all()


@router.post("/users/", response_model=UserResponse, status_code=201)
async def create_user(
    data: UserCreate,
    db: AsyncSession = Depends(get_db),
    current_user: User = Depends(require_role("teacher", "admin", "super_admin")),
):
    if current_user.role == "teacher":
        allowed = _TEACHER_CREATABLE
    elif current_user.role == "admin":
        allowed = _ADMIN_CREATABLE
    else:
        allowed = _SUPERADMIN_CREATABLE

    if data.role not in allowed:
        raise HTTPException(403, f"Vous ne pouvez pas créer un compte de rôle '{data.role}'")

    existing = await db.execute(select(User).where(User.email == data.email))
    if existing.scalar_one_or_none():
        raise HTTPException(409, "Un compte avec cet e-mail existe déjà")

    # etab_id : super_admin peut spécifier, sinon hérite du créateur
    etab_id = getattr(data, "etab_id", None) or current_user.etab_id

    user = User(
        email=data.email,
        first_name=data.first_name,
        last_name=data.last_name,
        role=data.role,
        etab_id=etab_id,
        hashed_password=hash_password(data.password),
    )
    db.add(user)
    await db.commit()
    await db.refresh(user)
    return user


@router.delete("/users/{user_id}", status_code=204)
async def delete_user(
    user_id: uuid.UUID,
    db: AsyncSession = Depends(get_db),
    current_user: User = Depends(require_role("admin", "super_admin")),
):
    result = await db.execute(select(User).where(User.id == user_id))
    user = result.scalar_one_or_none()
    if not user:
        raise HTTPException(404, "Utilisateur introuvable")
    if user.id == current_user.id:
        raise HTTPException(400, "Vous ne pouvez pas supprimer votre propre compte")
    # admin ne peut supprimer que dans son étab
    if current_user.role == "admin" and user.etab_id != current_user.etab_id:
        raise HTTPException(403, "Cet utilisateur n'appartient pas à votre établissement")
    await db.delete(user)
    await db.commit()
