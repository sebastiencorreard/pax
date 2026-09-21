---
name: dependances
description: Mettre à jour une dépendance backend (requirements.txt) ou frontend (npm), et vérifier que la mise à jour a bien pris. Utiliser dès qu'une dépendance est ajoutée, retirée ou changée de version, ou pour comprendre les contrôles automatiques (dependabot, pip-audit, npm audit) et les avis de sécurité ignorés.
---

# Mettre à jour une dépendance

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
`cd frontend && npx playwright test`. The e2e suite **passes 37 / 0 failures**
(2 skipped) since it was put back in step on 2026-09-06 — this page long said
«17 pre-existing failures», which stopped being true then. `CLAUDE.md` carries
the live baselines for lint / typecheck / e2e; read them there rather than
here, so one number has one home. Its accounts (`eleve@pax.fr` / `eleve1234`,
`prof@pax.fr` / `prof1234`) must exist in the DB.

**Check the installed version, not the command's exit code.** A
`docker compose build backend` can return 0 while the container still runs the
old packages — seen on 2026-09-21, where sqlalchemy/alembic/uvicorn stayed put
and only `cryptography` moved, because it is pinned `>=` and floats on its own.
Trusting that one package would have validated three upgrades that were never
installed, with a green test suite proving nothing:

```bash
docker compose exec -T backend python3 -c \
  "import sqlalchemy, alembic, uvicorn; print(sqlalchemy.__version__, alembic.__version__, uvicorn.__version__)"
docker compose exec -T frontend node -e "console.log(require('vue/package.json').version)"
```

**A major that forces a duplicated toolchain is a migration, not an upgrade.**
TypeScript 7 (PR #60, 2026-09-21) is green in CI but seven `@typescript-eslint/*`
packages cap it at `<6.1.0`: the bump only lands by installing a **second,
nested TypeScript**, so eslint and `vue-tsc` would no longer judge the same
language and the 69-error typecheck baseline would lose its meaning. Held until
`@typescript-eslint` accepts TS 7 — same reasoning as the ignored
`nuxt`/`pinia`/`@vueuse` majors.

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

