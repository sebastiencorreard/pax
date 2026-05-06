from fastapi import APIRouter, Depends, Query
from sqlalchemy.ext.asyncio import AsyncSession
from sqlalchemy import select, or_, func

from db import get_db
from models.user import Etablissement
from api.schemas.etablissement import EtabResponse

router = APIRouter(prefix="/api/etablissements", tags=["etablissements"])


@router.get("/search", response_model=list[EtabResponse])
async def search_etablissements(
    q: str = Query(..., min_length=2),
    db: AsyncSession = Depends(get_db),
):
    """Recherche publique d'établissements (commune, code postal, UAI, nom)."""
    q = q.strip()
    result = await db.execute(
        select(Etablissement)
        .where(
            or_(
                Etablissement.name.ilike(f"%{q}%"),
                Etablissement.commune.ilike(f"%{q}%"),
                Etablissement.code_postal.startswith(q),
                Etablissement.uai.ilike(f"%{q}%"),
            )
        )
        .order_by(Etablissement.commune, Etablissement.name)
        .limit(50)
    )
    return result.scalars().all()
