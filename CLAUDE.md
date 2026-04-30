# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## Project Overview

**PAX** (Progrès en Automatismes par les eXercices) is an interactive educational exercise platform — a WIMS-compatible clone — for mathematics and sciences. It is multilingual (French/Dutch/English) and targets Belgian/Dutch secondary school curricula.

## Architecture

Full-stack application split into three main layers:

**Backend** (`backend/`) — Python 3.10 + FastAPI (async)
- Entry point: `main.py` mounts 5 routers: `auth`, `exercises`, `sheets`, `render`, `check`
- `api/routes/` — HTTP handlers; `models/` — SQLAlchemy ORM; `core/` + `services/` — business logic
- Answer checking (`check.py`) uses SymPy + Maxima CAS for symbolic verification
- `render.py` translates OEF exercise files into HTML for display
- Database: PostgreSQL via asyncpg + Alembic migrations; cache/queue: Redis + Celery

**Frontend** (`frontend/`) — Nuxt 3 (SSR disabled, SPA mode) + Vue 3 + Tailwind CSS
- API base defaults to `http://localhost:8001`, override via `NUXT_PUBLIC_API_BASE`
- Auth state managed by Pinia store (`stores/`); KaTeX for LaTeX rendering; i18n defaults to French

**Exercise resources** (`ressources/`) — Content library organized by level (`H4/`) then domain (`algebra/`, `chemistry/`, `logic/`, etc.)
- Each exercise set lives in its own subdirectory and is OEF-compatible
- `.js.el` files: structured data (molecules, atoms) using WIMSchem coordinate/bond encoding
- `.txt` files: exercise definitions with premises, choices, and the correct answer marked `*`
- `.phtml` files: exercise templates (help, intro, form, answer sections)

## Running the Project (Docker — preferred)

```bash
docker compose up --build        # build and start all services
docker compose up -d             # start in background
docker compose down              # stop (preserves DB volume)
docker compose down -v           # stop and wipe DB volume
docker compose logs -f backend   # tail backend logs
docker compose exec backend bash # shell into backend container
docker compose exec db psql -U pax pax  # psql shell
```

Services:
- Frontend: http://localhost:3000
- Backend API: http://localhost:8001

On first start, `entrypoint.sh` runs automatically:
1. `alembic upgrade head` — applies all migrations
2. `python scripts/import_exercises.py --level H4` — imports all renderable OEF exercises
3. `uvicorn main:app` — starts the API

**Seed dev users** (run once after first `docker compose up`):
```bash
./seed-dev-users.sh
```
| Email | Password | Role |
|---|---|---|
| prof@pax.fr | prof1234 | teacher |
| eleve@pax.fr | eleve1234 | student |
| admin@pax.fr | admin1234 | admin |

## Development Commands (without Docker)

### Backend
```bash
cd backend
python3 -m venv .venv && source .venv/bin/activate
pip install -r requirements.txt
cp .env.example .env          # then edit .env
uvicorn main:app --reload     # dev server on :8001
```

Run tests:
```bash
cd backend && pytest                         # all tests
cd backend && pytest tests/path/to_test.py  # single file
```

Database migrations:
```bash
cd backend && alembic upgrade head
cd backend && alembic revision --autogenerate -m "description"
```

### Frontend
```bash
cd frontend
npm install
npm run dev    # dev server on :3000
npm run build
npm run lint
```

## Exercise ID System

Exercise primary keys are **path slugs** — the `oef_path` with the leading `/` stripped and all `/` replaced by `~`:

```
/ressources/H4/chemistry/equilibrium.fr/src/coefficients2.oef
→ ressources~H4~chemistry~equilibrium.fr~src~coefficients2.oef
```

Two helper functions in `models/exercise.py`:
- `path_to_id(oef_path)` — converts path to slug (used by import script)
- `id_to_path(exercise_id)` — reverses it

This makes IDs deterministic across fresh DB setups and URL-safe (`~` is RFC 3986 unreserved). All routes (`/api/exercises/{id}`, `/api/render/{id}`, `/api/check/{id}`) and frontend types use `str`, not `int`.

## Key Configuration

Backend settings are Pydantic-based (`backend/config.py`), sourced from `.env`:
- DB: `postgresql+asyncpg://pax:pax@localhost:5432/pax` (or `db:5432` in Docker)
- Redis: `redis://localhost:6379/0`
- Keycloak: `http://localhost:8180`, realm `pax` (auth not yet wired in Phase 1)
- Maxima binary: `/usr/bin/maxima`, 3 s timeout

## Database Tables

| Table | Purpose |
|---|---|
| `users` | Accounts (teacher / student / admin) |
| `exercises` | Imported OEF exercises (PK = path slug) |
| `sheets` | Exercise sheets created by teachers |
| `sheet_exercises` | Join: exercises on a sheet |
| `homework_assignments` | Sheets assigned to students |
| `homework_pools` | Groups of exercises for random selection |
| `homework_pool_exercises` | Join: exercises in a pool |
| `grades` | Student grades |
| `attempts` | Student answer attempts |
| `academies` | School districts |
| `etablissements` | Schools |

## Migrations

Three migrations in `backend/migrations/versions/`:
1. `abbbce7c5e1f` — init users table
2. `bff6ef39b9f5` — add exercises, sheets, attempts tables
3. `c1a2b3d4e5f6` — change `exercises.id` from integer to path slug (VARCHAR)

## Exercise Resource Format

When editing or adding exercises under `ressources/`:
- Domain directories follow the pattern `<domain-name>-<version>.<lang>/` (e.g., `scheikunde-1.nl/`)
- `.js.el` molecule files encode: name, formula, molecular weight, combustion reactions (plain + LaTeX), and a WIMSchem visual representation as a flat coordinate/bond string
- Syllogism `.txt` exercises use the format `A -> B` / `nietA -> B` for logical notation, with Dutch labels (`Vraag #N`)
- OEF `.phtml` templates use WIMS variable syntax
- `\language{}` values in OEF files may be full names (`french`, `dutch`) — the import script normalizes these to ISO codes (`fr`, `nl`) before inserting
