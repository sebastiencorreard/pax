from fastapi import FastAPI
from fastapi.middleware.cors import CORSMiddleware

from config import settings
from api.routes import auth, exercises, sheets, render, check

app = FastAPI(
    title="PAX — Progrès en Automatismes par les eXercices",
    version="0.1.0",
    docs_url="/api/docs",
    redoc_url="/api/redoc",
)

app.add_middleware(
    CORSMiddleware,
    allow_origins=["http://localhost:3000"],  # Nuxt dev server (port 3000)
    allow_credentials=True,
    allow_methods=["*"],
    allow_headers=["*"],
)


@app.get("/api/health")
async def health():
    return {"status": "ok", "project": "PAX"}


app.include_router(auth.router)
app.include_router(exercises.router)
app.include_router(sheets.router)
app.include_router(render.router)
app.include_router(check.router)
