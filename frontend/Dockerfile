# Multi-stage build. `dev` runs the Nuxt dev server (HMR + devtools);
# `prod` builds the app once and serves the compiled output via Node.
# Compose files pick the target — `docker-compose.override.yml` (dev)
# selects `dev`; `docker-compose.prod.yml` selects `prod`.

# ── deps ──────────────────────────────────────────────────────────────────────
FROM node:20-alpine AS deps
WORKDIR /app
COPY package*.json ./
RUN npm ci || npm install

# ── dev: hot-reload server ────────────────────────────────────────────────────
FROM node:20-alpine AS dev
WORKDIR /app
COPY --from=deps /app/node_modules ./node_modules
COPY . .
EXPOSE 3000
ENV NODE_ENV=development
CMD ["npx", "nuxt", "dev", "--port", "3000", "--host", "0.0.0.0"]

# ── builder: produces .output/ for prod ───────────────────────────────────────
FROM node:20-alpine AS builder
WORKDIR /app
COPY --from=deps /app/node_modules ./node_modules
COPY . .
ENV NODE_ENV=production
RUN npx nuxt build

# ── prod: runs the built server, no devtools, no source code ──────────────────
FROM node:20-alpine AS prod
WORKDIR /app
COPY --from=builder /app/.output ./.output
EXPOSE 3000
ENV NODE_ENV=production
ENV NITRO_HOST=0.0.0.0
ENV NITRO_PORT=3000
CMD ["node", ".output/server/index.mjs"]
