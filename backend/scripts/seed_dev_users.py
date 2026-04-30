"""
Creates default dev users if they don't already exist. Not for production.
"""
import sys
import os
import asyncio

sys.path.insert(0, os.path.dirname(os.path.dirname(os.path.abspath(__file__))))

from sqlalchemy.ext.asyncio import create_async_engine, async_sessionmaker
from sqlalchemy import select
from config import settings
from models.user import User
from core.security import hash_password

DEV_USERS = [
    {"email": "prof@pax.fr",  "password": "prof1234",  "first_name": "Alice", "last_name": "Dupont",  "role": "teacher"},
    {"email": "eleve@pax.fr", "password": "eleve1234", "first_name": "Bob",   "last_name": "Martin",  "role": "student"},
    {"email": "admin@pax.fr", "password": "admin1234", "first_name": "Admin", "last_name": "PAX",     "role": "admin"},
]

async def seed():
    engine = create_async_engine(settings.database_url)
    async_session = async_sessionmaker(engine, expire_on_commit=False)

    async with async_session() as db:
        for u in DEV_USERS:
            exists = await db.execute(select(User).where(User.email == u["email"]))
            if exists.scalar_one_or_none():
                print(f"  exists  : {u['email']} (skipped)")
                continue
            db.add(User(
                email=u["email"],
                first_name=u["first_name"],
                last_name=u["last_name"],
                role=u["role"],
                hashed_password=hash_password(u["password"]),
            ))
            print(f"  created : {u['email']}")
        await db.commit()

    await engine.dispose()

if __name__ == "__main__":
    asyncio.run(seed())
