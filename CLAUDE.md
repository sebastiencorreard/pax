# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## Project Overview

**PAX** (Progrès en Automatismes par les eXercices) is an interactive educational exercise platform — a WIMS-compatible clone — for mathematics and sciences. It is multilingual (French/Dutch/English) and targets Belgian/Dutch secondary school curricula.

## Architecture

Three layers. The **backend** (`backend/`) checks and renders: `check.py`
verifies answers symbolically through SymPy and Maxima, `render.py` turns an
OEF file into HTML. The **frontend** (`frontend/`) is a SPA.

**Exercise resources** (`ressources/`) — content library organized by level (`H4/`) then domain (`algebra/`, `chemistry/`, `logic/`, etc.)
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
2. `python scripts/import_exercises.py` — imports all renderable OEF exercises from every level dir (`H3`, `H4`, … any `<uppercase letter><digit>` name) plus `tool`/`Lang`; pass `--level H4` to restrict to one.
   It is **idempotent**: an exercise already in the DB has its title, language
   and keywords re-read from the `.def` and updated when they differ — a fix to
   `extract_meta` therefore reaches the 4278 existing rows on the next start.
   A field the `.def` does not carry never erases what the DB holds. `--dry-run`
   lists what would change without writing.
   Keywords are the **union** of the `.def`'s `keywords=` and of the module's
   `Exkeywords` file — the two disagree on 48 exercises and neither is complete
   on its own (a quizz's `.def` carries the author's aggregate line, truncated
   to 128 chars by the WIMS compiler; `Exkeywords` keeps only the first
   question, and 5 exercises are missing from it). Since the union is built at
   import time, `exercises.keywords` is the **single source** the API reads —
   `/api/exercises/modules` no longer opens `Exkeywords`, and a GIN index
   (`ix_exercises_keywords`) serves `keywords && ARRAY[…]` in SQL
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
cd backend && pytest -m slow                 # corpus sweep (4278 exercises)
cd backend && PAX_TEST_CORPUS=H4/algebra pytest -m slow   # one subtree
```

`test_exercises_check` and `test_exercises_render` walk the whole corpus, so
they carry the `slow` marker and `pytest.ini` excludes them by default —
otherwise every run would render 4278 exercises. They read the corpus **off
disk** (`tests/corpus.py`), needing neither a database nor a prior import.
Known-failing exercises live in `tests/known_failures.py`, keyed by **slug**;
rebuild those lists from a real run after fixing a bug.

Database migrations:
```bash
cd backend && alembic upgrade head
cd backend && alembic revision --autogenerate -m "description"
```

### Frontend
```bash
cd frontend
npm install
npm run dev        # dev server on :3000
npm run build
npm run lint       # eslint (config Nuxt officielle)
npm run lint:fix   # dont ~485 des problèmes se corrigent seuls
npm run typecheck  # vue-tsc sur .nuxt/tsconfig.json
npm run test:e2e   # playwright
```

**Ligne de base — juger le *delta*, pas le total.** Le dépôt a longtemps vécu
sans linter (`npm run lint` était documenté mais n'existait pas), et l'arriéré
est réel :

| commande | état au 2026-09-02 |
|---|---|
| `npm run lint` | 564 problèmes — 55 erreurs, 509 avertissements, dont **477 corrigeables par `lint:fix`** |
| `npm run typecheck` | 69 erreurs, concentrées sur `DrawAnswer.vue` (28) et `utils/figureColors.ts` (13) |
| `npm run test:e2e` | **36 passent, 2 ignorés, 0 échec** (38 tests, ~1 min) |

Résorber l'arriéré est un chantier à part : `lint:fix` touche des centaines de
fichiers pour un gain cosmétique, et mérite sa propre relecture. Ce qui compte
d'ici là, c'est qu'un changement n'aggrave aucun des trois compteurs.

**La suite e2e a été remise d'aplomb le 2026-09-06.** Elle annonçait ici « 0
échec » sur 20 tests ; il y en avait 37, dont **17 échouaient** depuis un moment
— non par régression, mais parce que les tests n'avaient pas suivi l'interface.
Ce qu'ils affirmaient et qui n'existait plus :

- le rôle (`student`) dans la barre du haut — elle affiche le nom complet, et
  c'est un `<header>`, non un `<nav>` ;
- un enseignant redirigé vers `/exercise` après connexion — il atterrit sur `/` ;
- des `a[href^="/exercise/"]` présents au chargement de `/exercise` — les
  modules y sont repliés, et leurs exercices ne sont même plus chargés ;
- une navigation au clic sur un exercice — au-dessus de 1024 px la liste
  l'affiche en prévisualisation, sans naviguer ;
- le numéro de tirage (`seed`), visible en mode de mise au point seulement ;
- le compteur d'étoiles sur la page d'un exercice — il vit dans la barre du
  tableau de bord, et cette page utilise le layout `default`.

Deux vrais défauts sont ressortis de l'exercice et ont été corrigés dans
l'application, pas dans les tests : les boutons *Déconnexion* et *Changer de
langue* n'avaient pour nom accessible que leur glyphe (`⎋`, `🇫🇷`) faute
d'`aria-label`, et la page d'un exercice ouverte en direct n'offrait aucun
retour vers la liste — la clé `exercise.back` traînait, orpheline, dans les
trois locales.

Le piège à retenir : `waitForURL('**/exercise**')` est satisfait par
`/auth/login?redirect=/exercise`, l'URL sur laquelle on retombe quand la
connexion échoue — un login raté y passait pour un succès.

**Mesurer la ligne de base avant de juger un delta** : celle écrite ici m'a fait
croire un moment que j'avais cassé quelque chose.

## Dependencies

**Applying an upgrade — rebuild, never restart.** A `restart` reuses the
container's own packages, and both stacks hide a stale install in a way that
makes a verification look green when it tested nothing. Backend:
`docker compose build backend`. Frontend: `docker compose down frontend &&
docker compose up -d frontend` — `/app/node_modules` is an anonymous volume,
which only `down` drops.

The full procedure — commands, the traps behind them, and the automated checks
(dependabot, `pip-audit`, `npm audit`, and the advisory deliberately ignored) —
is in the `dependances` skill.

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

The **corrected answer** shown after submitting goes through one pass of its
own, `_localize_feedback` in `api/routes/check.py`: the engine emits dots, the
exercise's language may want commas. It rewrites a dot only *between two
digits*, only on `expected` (never `reply` — that's what the student typed),
and only for answer types whose value is a number (`atext` answers "3.5
inches", `runcode` returns Python). It is a display convenience, **not** an
engine rule: no verdict depends on it, and the checkers accept `2,6` as
readily as `2.6`. `PAX_LOCALIZE_FEEDBACK=0` turns it off — handy when
diffing a render against WIMS, which localises nothing.

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
- [`regenerer-un-oef.md`](docs/regenerer-un-oef.md) — quand un exercice vient d'un `src/cpp/*.cpp` : `.cpp` → `.oef` → `.def`, et les pièges d'encodage
- [`wims-c-to-python-port.md`](docs/wims-c-to-python-port.md) — porting decisions vs the WIMS C source
