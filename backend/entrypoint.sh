#!/bin/bash
set -e

echo "Running database migrations..."
alembic upgrade head

echo "Importing exercises..."
python scripts/import_exercises.py --level H4

echo "Starting server..."
exec uvicorn main:app --host 0.0.0.0 --port 8001
