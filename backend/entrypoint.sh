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
        print(f"  Connection error: {e}", file=sys.stderr)
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
# `IMPORT_ARGS` restreint le corpus importé — `--level H4 --domains algebra`,
# par exemple. Vide par défaut : tout est importé. Sert à la CI, dont le job de
# tests attend la fin de l'import (les 4278 exercices demandent une vingtaine de
# minutes sur un runner), et à qui veut démarrer vite en développement.
# Volontairement non protégé par des guillemets : plusieurs arguments.
# shellcheck disable=SC2086
python scripts/import_exercises.py ${IMPORT_ARGS:-} &

# Hot reload in dev: docker-compose.override.yml bind-mounts the source and
# sets UVICORN_RELOAD=1. Production keeps the default (no --reload).
RELOAD_ARGS=()
if [ "${UVICORN_RELOAD:-0}" = "1" ]; then
  echo "  hot reload enabled (UVICORN_RELOAD=1)"
  RELOAD_ARGS=(--reload --reload-dir /app)
fi

exec uvicorn main:app --host 0.0.0.0 --port 8001 "${RELOAD_ARGS[@]}"
