#!/bin/bash
# Thin wrapper around `docker compose exec backend python scripts/create_user.py`.
# Forwards all arguments to the script. Run from the repo root.
#
# Examples:
#   ./create_user.sh --email alice@example.com --first-name Alice --role teacher
#   ./create_user.sh --email bob@example.com  --first-name Bob --password bob1234
#
# The generated XKCD-style passphrase is the last line of stdout — capture
# with `PASS=$(./create_user.sh ... | tail -n 1)`.
set -euo pipefail

exec docker compose exec -T backend python scripts/create_user.py "$@"
