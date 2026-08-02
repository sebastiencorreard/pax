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
2. `python scripts/import_exercises.py` — imports all renderable OEF exercises from every level dir (`H3`, `H4`, … any `<uppercase letter><digit>` name) plus `tool`/`Lang`; pass `--level H4` to restrict to one
3. `uvicorn main:app` — starts the API

**Create a user** (run after `docker compose up`):
```bash
./create_user.sh --email alice@example.com --first-name Alice --last-name Dupont --role teacher
```
The script wraps `docker compose exec backend python scripts/create_user.py` and forwards arguments. It prints an XKCD-style French passphrase on stdout's last line; pass `--password XYZ` to set an explicit password instead. There is no public registration endpoint.

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

## Dependencies

### Applying an upgrade — rebuild, never restart

A `restart` reuses the container's own packages. Both stacks hide a stale
install in a way that makes a verification look green when it tested nothing:

```bash
# Backend — after editing backend/requirements.txt
docker compose build backend && docker compose up -d backend
docker compose exec -T backend pytest tests/ -q
```
`pip install -r requirements.txt` inside a live container keeps whatever is
already installed, so a dependency that is *used but not declared* stays
invisible. That is how `email-validator` — pulled implicitly by FastAPI 0.111,
no longer by 0.141 — only surfaced on a full image rebuild, as an ImportError
on the `auth` router at startup.

```bash
# Frontend
cd frontend && npm install <pkg>@<version> && cd ..
docker compose build frontend
docker compose down frontend && docker compose up -d frontend   # `restart` is NOT enough
```
`/app/node_modules` is an **anonymous volume** (`docker-compose.override.yml`),
so a `restart` keeps the image's original packages and host-side `npm install`
never reaches the running app. Only `down` drops the volume.

For a non-trivial upgrade, add the corpus regression (backend) and
`cd frontend && npx playwright test`. The e2e suite currently yields **17
pre-existing failures** — it describes an `/exercise` page that has since been
replaced — so judge the *delta*, not the total. Its accounts (`eleve@pax.fr` /
`eleve1234`, `prof@pax.fr` / `prof1234`) must exist in the DB.

### Automated checks

`.github/dependabot.yml` (weekly PRs) and `.github/workflows/dependencies.yml`
(`pip-audit` + `npm audit`) — **both inert until `.github/` reaches the default
branch**: Dependabot reads its config there, and scheduled workflows only run
from it. Same check locally, GitHub-free: `./scripts/check-deps.sh [backend|frontend]`,
exit 1 on a blocking advisory.

Backend minor/patch updates are **grouped into one PR** on purpose: FastAPI pins
starlette and pydantic follows FastAPI, so split PRs could never be green.
`nuxt` / `pinia` / `@vueuse` majors are ignored — migrations, not upgrades.

`PYSEC-2026-1325` (`ecdsa`, Minerva timing attack on P-256) is ignored in both,
with its rationale: upstream considers side channels out of scope, so it will
never close, and it is unreachable while JWTs are HS256 (`config.py:algorithm`,
`core/security.py` restricting `algorithms` on decode). **Re-enable it if the
project ever moves to ES256.**

## Exercise ID System

Exercise primary keys are **path slugs** — the `oef_path` with the leading `/` stripped, all `/` replaced by `~`, the redundant leading `ressources~` component dropped (everything lives under `/ressources/`), and the trailing `.oef` extension dropped:

```
/ressources/H4/chemistry/equilibrium.fr/src/coefficients2.oef
→ H4~chemistry~equilibrium.fr~src~coefficients2
```

Two helper functions in `models/exercise.py`:
- `path_to_id(oef_path)` — converts path to slug, stripping `ressources~` and the `.oef` suffix (used by import script)
- `id_to_path(exercise_id)` — reverses it (re-adds `/ressources/` and `.oef`); not used at runtime — routes resolve files via the stored `Exercise.oef_path`

This makes IDs deterministic across fresh DB setups and URL-safe (`~` is RFC 3986 unreserved). All routes (`/api/exercises/{id}`, `/api/render/{id}`, `/api/check/{id}`) and frontend types use `str`, not `int`.

## Image / static assets

Exercise images are served by the backend via `/api/static` (mounted on `ressources/`) — see [`docs/static-assets.md`](docs/static-assets.md). To add a new module image, drop it in `ressources/<level>/<domain>/<module>.<lang>/images/`; it's picked up automatically.

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

## Locale-driven decimal/list separators

Number display and answer parsing follow the **exercise language**, not the UI
locale. `backend/core/oef/i18n.py` is the single source of truth: comma-decimal
languages (`,` decimal / `;` list) vs dot-decimal (`.` decimal / `,` list).
**To support a new comma-decimal language, add its ISO code to
`COMMA_DECIMAL_LANGS` there — nothing else changes.** Decimals are formatted
noise-free via `core/oef/numfmt.py:format_wims_float` (12 significant digits,
like WIMS' `double` printing). The frontend (`composables/useKatex.ts`) wraps a
decimal comma as `{,}` so KaTeX doesn't add punctuation spacing.

## Documentation index (`docs/`)

In-depth references and dev guides:

- [`def-engine-commands.md`](docs/def-engine-commands.md) — WIMS `!cmd` reference
- [`def-engine-cas-functions.md`](docs/def-engine-cas-functions.md) — Maxima / Pari → Python mapping
- [`def-engine-workflow.md`](docs/def-engine-workflow.md) — dev workflow when adding new `.def` files
- [`refactor-item-splitting.md`](docs/refactor-item-splitting.md) — WIMS list-splitting ground truth (C source) + refactoring program; read before touching any item/row/list splitting
- [`slib.md`](docs/slib.md) — shared library scripts (`!readproc slib/…`)
- [`types-exercices-reponses.md`](docs/types-exercices-reponses.md) — catalogue of exercise + answer types
- [`exercises-course.md`](docs/exercises-course.md) — deep dive on `course` (sequential) exercises
- [`exercise-parameters.md`](docs/exercise-parameters.md) — WIMS session variables (`$imagedir`, `$confparm*`, `$m_step`, …)
- [`static-assets.md`](docs/static-assets.md) — `/api/static` endpoint, image serving, `$imagedir` resolution
- [`wims-c-to-python-port.md`](docs/wims-c-to-python-port.md) — porting decisions vs the WIMS C source
