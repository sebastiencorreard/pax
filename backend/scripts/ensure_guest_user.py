"""Ensure the singleton guest user exists.

Idempotent: safe to run on every container startup. The "Continuer en
tant qu'invité" button on the login page calls ``POST /api/auth/guest``,
which looks up the singleton ``role='guest'`` user and issues a token —
this script makes sure that user is always there.

Guests have no password (``hashed_password=NULL``), so they cannot be
entered through ``POST /api/auth/login``.
"""

import asyncio
import os
import sys

sys.path.insert(0, os.path.dirname(os.path.dirname(os.path.abspath(__file__))))

from sqlalchemy import select
from sqlalchemy.ext.asyncio import async_sessionmaker, create_async_engine

from config import settings
from models.user import User

GUEST_EMAIL = "guest@pax.fr"
GUEST_FIRST_NAME = "Invite"
GUEST_LAST_NAME = ""


async def ensure_guest() -> None:
    engine = create_async_engine(settings.database_url)
    Session = async_sessionmaker(engine, expire_on_commit=False)
    try:
        async with Session() as db:
            existing = await db.execute(
                select(User).where(User.role == "guest").limit(1)
            )
            if existing.scalar_one_or_none() is not None:
                print("ensure_guest_user: guest already present, skipping")
                return

            # If a legacy account at the well-known email exists with a
            # different role / password (e.g. from the old dev seeder),
            # promote it instead of failing on the unique-email constraint.
            by_email = await db.execute(select(User).where(User.email == GUEST_EMAIL))
            user = by_email.scalar_one_or_none()
            if user is not None:
                user.role = "guest"
                user.hashed_password = None
                action = "promoted"
            else:
                user = User(
                    email=GUEST_EMAIL,
                    first_name=GUEST_FIRST_NAME,
                    last_name=GUEST_LAST_NAME,
                    role="guest",
                    hashed_password=None,
                )
                db.add(user)
                action = "created"
            await db.commit()
            print(f"ensure_guest_user: {action} {GUEST_EMAIL}")
    finally:
        await engine.dispose()


if __name__ == "__main__":
    asyncio.run(ensure_guest())
