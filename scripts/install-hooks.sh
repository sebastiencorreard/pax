#!/usr/bin/env bash
# Installe les git hooks du projet.
set -e
ROOT=$(git rev-parse --show-toplevel)

cp "$ROOT/scripts/hooks/pre-commit" "$ROOT/.git/hooks/pre-commit"
chmod +x "$ROOT/.git/hooks/pre-commit"
echo "Hook pre-commit installé."
