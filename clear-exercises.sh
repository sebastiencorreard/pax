#!/bin/bash
# Clears all exercises (and related attempts, sheet_exercises, homework_pool_exercises) from the database.

docker compose exec db psql -U pax pax -c "TRUNCATE exercises CASCADE;"
echo "Exercises cleared."
