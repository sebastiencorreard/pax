#!/bin/bash
# Creates default development users. Not for production.

API="http://localhost:8001/api/auth/register"

register() {
  local label=$1
  local body=$2
  local response
  response=$(curl -s -o /dev/null -w "%{http_code}" -X POST "$API" \
    -H "Content-Type: application/json" \
    -d "$body")
  if [ "$response" = "201" ]; then
    echo "  created : $label"
  elif [ "$response" = "400" ]; then
    echo "  exists  : $label (skipped)"
  else
    echo "  error   : $label (HTTP $response)"
  fi
}

echo "Seeding dev users..."

register "prof@pax.fr (teacher)" \
  '{"email":"prof@pax.fr","password":"prof1234","first_name":"Alice","last_name":"Dupont","role":"teacher"}'

register "eleve@pax.fr (student)" \
  '{"email":"eleve@pax.fr","password":"eleve1234","first_name":"Bob","last_name":"Martin","role":"student"}'

register "admin@pax.fr (admin)" \
  '{"email":"admin@pax.fr","password":"admin1234","first_name":"Admin","last_name":"PAX","role":"admin"}'

register "guest@pax.fr (student)" \
  '{"email":"guest@pax.fr","password":"guest1234","first_name":"Invité","last_name":"","role":"student"}'

echo "Done."
