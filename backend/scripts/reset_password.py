"""Reset a user's password from the command line.

Run inside the backend container::

    docker compose exec backend python scripts/reset_password.py \
        --email admin@pax.fr --password newpassword123
"""

from __future__ import annotations

import argparse
import asyncio
import sys

from sqlalchemy import select

sys.path.insert(0, ".")

from core.security import hash_password  # noqa: E402
from db import AsyncSessionLocal  # noqa: E402
from models.user import User  # noqa: E402


def _parse_args() -> argparse.Namespace:
    p = argparse.ArgumentParser(description=__doc__)
    p.add_argument("--email", required=True, help="User email.")
    p.add_argument("--password", required=True, help="New password.")
    return p.parse_args()


async def _reset(args: argparse.Namespace) -> None:
    async with AsyncSessionLocal() as session:
        result = await session.execute(select(User).where(User.email == args.email))
        user = result.scalar_one_or_none()
        if user is None:
            print(f"error: user not found: {args.email}", file=sys.stderr)
            sys.exit(1)

        user.hashed_password = hash_password(args.password)
        await session.commit()

        print(f"successfully reset password for user: {args.email}", file=sys.stderr)


def main() -> None:
    asyncio.run(_reset(_parse_args()))


if __name__ == "__main__":
    main()
