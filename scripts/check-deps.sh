#!/usr/bin/env bash
# Contrôle des dépendances : failles connues + versions en retard.
#
# Même contenu que le workflow `.github/workflows/dependencies.yml`, jouable à
# la main sans passer par GitHub. Utilise Docker, comme le reste du projet.
#
#   ./scripts/check-deps.sh              # tout
#   ./scripts/check-deps.sh backend      # Python seulement
#   ./scripts/check-deps.sh frontend     # npm seulement
set -uo pipefail
cd "$(dirname "$0")/.."

cible="${1:-tout}"
statut=0

# Avis écartés, avec leur raison. À garder synchronisé avec
# `.github/workflows/dependencies.yml`, et à revoir si le contexte change.
#
# PYSEC-2026-1325 — `ecdsa`, attaque temporelle Minerva sur P-256. Le projet
# amont considère les canaux auxiliaires hors périmètre : « there is no planned
# fix », donc l'avis ne se refermera jamais. Non atteignable ici : PAX signe et
# vérifie ses JWT en HS256 (`config.py:algorithm`, `core/security.py` qui
# restreint `algorithms` au décodage), si bien qu'aucune opération ECDSA n'est
# exercée. `ecdsa` n'est là que comme dépendance transitive de `python-jose`.
IGNORES=(--ignore-vuln PYSEC-2026-1325)

titre() { printf '\n\033[1m── %s ─────────────────────────────\033[0m\n' "$1"; }

if [[ "$cible" == "tout" || "$cible" == "backend" ]]; then
  titre "Python — failles connues (pip-audit)"
  # pip-audit n'est pas dans l'image : installé à la volée, sans la figer dans
  # requirements.txt pour un outil de contrôle.
  docker compose exec -T backend sh -c \
    "pip install -q pip-audit >/dev/null 2>&1; pip-audit --progress-spinner off --desc ${IGNORES[*]}" \
    || statut=1

  titre "Python — versions en retard"
  docker compose exec -T backend pip list --outdated 2>/dev/null
fi

if [[ "$cible" == "tout" || "$cible" == "frontend" ]]; then
  titre "npm — failles du périmètre de production"
  # Seul ce périmètre décide du statut : l'essentiel des avis npm vise la
  # chaîne de développement, qui n'est pas servie au public.
  (cd frontend && npm audit --omit=dev --audit-level=high) || statut=1

  titre "npm — audit complet (dev inclus, informatif)"
  (cd frontend && npm audit) || true

  titre "npm — versions en retard"
  (cd frontend && npm outdated) || true
fi

if [[ $statut -eq 0 ]]; then
  printf '\n\033[32mAucune faille bloquante.\033[0m\n'
else
  printf '\n\033[31mFailles à traiter (voir ci-dessus).\033[0m\n'
fi
exit $statut
