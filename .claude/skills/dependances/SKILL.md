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

