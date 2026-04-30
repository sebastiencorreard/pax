#!/bin/bash
fuser -k 8001/tcp 2>/dev/null && echo "Processus précédent arrêté (port 8001)"
cd "$(dirname "$0")/backend"
nohup uvicorn main:app --reload --port 8001 > /tmp/pax-backend.log 2>&1 &
echo "Backend démarré (PID $!, logs : /tmp/pax-backend.log)"
