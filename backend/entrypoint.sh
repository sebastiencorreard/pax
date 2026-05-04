#!/bin/bash
set -e

echo "Waiting for database..."
until python - <<'EOF'
import asyncio, asyncpg, os, sys
async def check():
    try:
        conn = await asyncpg.connect(os.environ["DATABASE_URL"].replace("+asyncpg", ""))
        await conn.close()
    except Exception as e:
        sys.exit(1)
asyncio.run(check())
EOF
do
  echo "  database not ready, retrying in 2s..."
  sleep 2
done
echo "  database is up."

echo "Running database migrations..."
alembic upgrade head

echo "Ensuring guest user..."
python scripts/ensure_guest_user.py

echo "Starting server (exercise import running in background)..."
python scripts/import_exercises.py --level H4 &

exec uvicorn main:app --host 0.0.0.0 --port 8001
