#!/bin/bash
# Clears all users from the database.

docker compose exec db psql -U pax pax -c "TRUNCATE users CASCADE;"
echo "Users cleared."
