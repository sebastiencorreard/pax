"""
Script d'import d'exercices OEF dans la base PAX.

Usage:
    python scripts/import_exercises.py --level H4 --domains algebra,analysis,number,arithmetic
"""

import sys
import os
import argparse
import asyncio

# Ajoute le répertoire parent au path
sys.path.insert(0, os.path.dirname(os.path.dirname(os.path.abspath(__file__))))

from sqlalchemy.ext.asyncio import create_async_engine, async_sessionmaker
from sqlalchemy import select
from config import settings
from models.exercise import Exercise, path_to_id
from core.oef.parser import parse, get_directives_compat


def extract_meta(oef_path: str) -> dict:
    """Extrait title, language du fichier OEF."""
    try:
        with open(oef_path, "rb") as f:
            raw = f.read()
        try:
            content = raw.decode("utf-8")
        except UnicodeDecodeError:
            content = raw.decode("iso-8859-1")
        directives = get_directives_compat(parse(content))
        meta = {}
        for d in directives:
            if d.name in ("title", "language", "author", "keywords"):
                meta[d.name] = d.content.strip()
        return meta
    except Exception:
        return {}


async def import_exercises(
    level: str, domains: list[str], resources_root: str, dry_run: bool
):
    engine = create_async_engine(settings.database_url)
    async_session = async_sessionmaker(engine, expire_on_commit=False)

    modules_path = os.path.join(resources_root, level)
    if not os.path.isdir(modules_path):
        print(f"Dossier introuvable : {modules_path}")
        return

    # Collecte tous les fichiers .oef dans les domaines demandés
    oef_files = []
    for domain in domains:
        domain_path = os.path.join(modules_path, domain)
        if not os.path.isdir(domain_path):
            print(f"  domaine absent : {domain}")
            continue
        for root, _, files in os.walk(domain_path):
            for f in sorted(files):
                if f.endswith(".oef"):
                    oef_files.append((domain, os.path.join(root, f)))
    oef_files.sort(key=lambda x: x[1])

    print(f"Fichiers trouvés : {len(oef_files)}")

    ok = 0
    skip_exists = 0

    _lang_map = {
        "french": "fr",
        "dutch": "nl",
        "english": "en",
        "german": "de",
        "spanish": "es",
    }

    async with async_session() as db:
        for domain, path in oef_files:
            # Vérifie si déjà en base
            res = await db.execute(select(Exercise).where(Exercise.oef_path == path))
            if res.scalar_one_or_none():
                skip_exists += 1
                continue

            meta = extract_meta(path)
            raw_lang = meta.get("language", "fr").lower()
            lang = str(_lang_map.get(raw_lang, raw_lang))[:5]
            title = meta.get("title", None)

            if dry_run:
                print(f"  DRY-RUN OK : [{domain}] {title or os.path.basename(path)}")
                ok += 1
                continue

            exercise = Exercise(
                id=path_to_id(path),
                oef_path=path,
                title=title,
                level=level,
                domain=domain,
                lang=lang,
                keywords=meta.get("keywords", None),
            )
            db.add(exercise)
            await db.commit()
            ok += 1
            print(f"  + [{domain}] {title or os.path.basename(path)}")

    await engine.dispose()
    print(f"\nRésultat : {ok} importés, {skip_exists} déjà en base")


if __name__ == "__main__":
    parser = argparse.ArgumentParser()
    parser.add_argument("--level", default="H4")
    parser.add_argument(
        "--domains",
        default=None,
        help="Comma-separated list of domains, or omit to import all available",
    )
    parser.add_argument("--resources-root", default=settings.resources_root)
    parser.add_argument("--dry-run", action="store_true")
    args = parser.parse_args()

    if args.domains:
        domains = [d.strip() for d in args.domains.split(",")]
    else:
        level_path = os.path.join(args.resources_root, args.level)
        domains = sorted(
            d
            for d in os.listdir(level_path)
            if os.path.isdir(os.path.join(level_path, d))
        )

    asyncio.run(
        import_exercises(args.level, domains, args.resources_root, args.dry_run)
    )
