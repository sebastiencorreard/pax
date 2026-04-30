#!/bin/bash
fuser -k 3000/tcp 2>/dev/null && echo "Processus précédent arrêté (port 3000)"
cd "$(dirname "$0")/frontend"
nohup npm run dev > /tmp/pax-frontend.log 2>&1 &
echo "Frontend démarré (PID $!, logs : /tmp/pax-frontend.log)"
