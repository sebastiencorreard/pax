"""Create a user account from the command line.

Run inside the backend container::

    docker compose exec backend python scripts/create_user.py \
        --email alice@example.com --first-name Alice --last-name Dupont \
        --role teacher

The generated XKCD-style French passphrase is printed on the **last line**
of stdout so callers can capture it with::

    PASSPHRASE=$(docker compose exec ... | tail -n 1)

There is intentionally no public registration endpoint; this script is the
only supported way to create accounts.
"""

from __future__ import annotations

import argparse
import asyncio
import sys

from sqlalchemy import select

# `scripts/` is run as a top-level entry point inside the container; the
# backend package layout is flat (config.py, db.py, models/ at root).
sys.path.insert(0, ".")

from core.security import hash_password  # noqa: E402
from db import AsyncSessionLocal  # noqa: E402
from models.user import User  # noqa: E402

# Local sibling import (avoids package-init complications when running
# this file as a script).
sys.path.insert(0, "scripts")
from _passphrase import generate_passphrase, wordlist_size  # noqa: E402


_VALID_ROLES = {"student", "teacher", "admin", "guest"}


def _parse_args() -> argparse.Namespace:
    p = argparse.ArgumentParser(description=(__doc__ or "").split("\n\n", 1)[0])
    p.add_argument("--email", required=True, help="Login email (must be unique).")
    p.add_argument("--first-name", required=True)
    p.add_argument("--last-name", default="")
    p.add_argument(
        "--role",
        default="student",
        choices=sorted(_VALID_ROLES),
        help="Role granted to the new user (default: student).",
    )
    p.add_argument(
        "--password",
        default=None,
        help=(
            "Set an explicit password instead of generating one. "
            "Useful for dev seeding; otherwise leave unset and read the "
            "generated passphrase from stdout."
        ),
    )
    p.add_argument(
        "--words",
        type=int,
        default=4,
        help=(
            f"Words in the generated passphrase (default 4, wordlist has "
            f"{wordlist_size()} entries)."
        ),
    )
    return p.parse_args()


async def _create(args: argparse.Namespace) -> None:
    async with AsyncSessionLocal() as session:
        # Reject duplicate emails up front.
        existing = await session.execute(select(User).where(User.email == args.email))
        if existing.scalar_one_or_none() is not None:
            print(f"error: user already exists: {args.email}", file=sys.stderr)
            sys.exit(2)

        # Guests have no password — they can only sign in via the
        # `/api/auth/guest` endpoint, which issues a token without
        # credentials. For all other roles, generate or accept one.
        is_guest = args.role == "guest"
        if is_guest:
            password = None
            hashed: str | None = None
        else:
            password = args.password or generate_passphrase(n_words=args.words)
            hashed = hash_password(password)

        user = User(
            email=args.email,
            first_name=args.first_name,
            last_name=args.last_name,
            role=args.role,
            hashed_password=hashed,
        )
        session.add(user)
        await session.commit()
        await session.refresh(user)

        print(
            f"created user id={user.id} email={user.email} role={user.role}",
            file=sys.stderr,
        )
        if password is not None:
            # Passphrase on stdout so it's captureable via shell pipelines.
            print(password)


def main() -> None:
    asyncio.run(_create(_parse_args()))


if __name__ == "__main__":
    main()
