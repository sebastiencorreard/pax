# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## Project Overview

**PAX** (Progrès en Automatismes par les eXercices) is an interactive educational exercise platform — a WIMS-compatible clone — for mathematics and sciences. It is multilingual (French/Dutch/English) and targets Belgian/Dutch secondary school curricula.

## Architecture

Full-stack application split into three main layers:

**Backend** (`backend/`) — Python 3.12 + FastAPI (async)
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

## Development Commands

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

### Convenience scripts (nohup, log to /tmp/)
```bash
./start-backend.sh   # kills :8001, starts backend → /tmp/pax-backend.log
./start-frontend.sh  # kills :3000, starts frontend → /tmp/pax-frontend.log
```

## Key Configuration

Backend settings are Pydantic-based (`backend/config.py`), sourced from `.env`:
- DB: `postgresql+asyncpg://pax:pax@localhost:5432/pax`
- Redis: `redis://localhost:6379/0`
- Keycloak: `http://localhost:8180`, realm `pax` (auth not yet wired in Phase 1)
- Maxima binary: `/usr/bin/maxima`, 3 s timeout

## Exercise Resource Format

When editing or adding exercises under `ressources/`:
- Domain directories follow the pattern `<domain-name>-<version>.<lang>/` (e.g., `scheikunde-1.nl/`)
- `.js.el` molecule files encode: name, formula, molecular weight, combustion reactions (plain + LaTeX), and a WIMSchem visual representation as a flat coordinate/bond string
- Syllogism `.txt` exercises use the format `A -> B` / `nietA -> B` for logical notation, with Dutch labels (`Vraag #N`)
- OEF `.phtml` templates use WIMS variable syntax
