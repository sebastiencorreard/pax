# PAX — Progrès en Automatismes par les eXercices

Clone de WIMS, rétro-compatible avec le format OEF, orienté mathématiques.

## Stack

- **Backend** : Python 3.12 + FastAPI
- **Frontend** : Nuxt.js (Vue 3)
- **Base de données** : PostgreSQL
- **Cache** : Redis
- **Auth** : Keycloak (compatible GAR/ENT)
- **CAS** : SymPy + Maxima

## Lancer le projet en développement

```bash
# Backend
cd backend
python3 -m venv .venv
source .venv/bin/activate
pip install -r requirements.txt
cp .env.example .env
uvicorn main:app --reload

# Frontend (dans un autre terminal)
cd frontend
npm install
npm run dev
```

## Licence

AGPL-3.0
