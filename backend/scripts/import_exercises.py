"""
Script d'import d'exercices OEF dans la base PAX.
Tente de rendre chaque exercice et n'importe que ceux qui fonctionnent.

Usage:
    python scripts/import_exercises.py --level H4 --domains algebra,analysis,number,arithmetic
"""
import sys
import os
import argparse
import asyncio

# Ajoute le répertoire parent au path
sys.path.insert(0, os.path.dirname(os.path.dirname(os.path.abspath(__file__))))

from sqlalchemy.ext.asyncio import create_async_engine, async_sessionmaker, AsyncSession
from sqlalchemy import select
from config import settings
from models.exercise import Exercise
from core.oef.engine import load_and_render
from core.oef.parser import parse


def extract_meta(oef_path: str) -> dict:
    """Extrait title, language du fichier OEF."""
    try:
        with open(oef_path, 'rb') as f:
            raw = f.read()
        try:
            content = raw.decode('utf-8')
        except UnicodeDecodeError:
            content = raw.decode('iso-8859-1')
        directives = parse(content)
        meta = {}
        for d in directives:
            if d.name in ('title', 'language', 'author', 'keywords'):
                meta[d.name] = d.content.strip()
        return meta
    except Exception:
        return {}


def try_render(oef_path: str) -> bool:
    """Retourne True si l'exercice peut être rendu sans erreur."""
    try:
        result = load_and_render(oef_path, seed=12345)
        return bool(result.statement_html)
    except Exception:
        return False


async def import_exercises(level: str, domains: list[str], wims_root: str, dry_run: bool):
    engine = create_async_engine(settings.database_url)
    async_session = async_sessionmaker(engine, expire_on_commit=False)

    modules_path = os.path.join(wims_root, 'modules', level)
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
            for f in files:
                if f.endswith('.oef'):
                    oef_files.append((domain, os.path.join(root, f)))

    print(f"Fichiers trouvés : {len(oef_files)}")

    ok = 0
    skip_exists = 0
    skip_error = 0

    async with async_session() as db:
        for domain, path in oef_files:
            # Vérifie si déjà en base
            res = await db.execute(select(Exercise).where(Exercise.oef_path == path))
            if res.scalar_one_or_none():
                skip_exists += 1
                continue

            # Tente le rendu
            if not try_render(path):
                skip_error += 1
                print(f"  SKIP (erreur rendu) : {os.path.basename(path)}")
                continue

            meta = extract_meta(path)
            lang = meta.get('language', 'fr')
            title = meta.get('title', None)

            if dry_run:
                print(f"  DRY-RUN OK : [{domain}] {title or os.path.basename(path)}")
                ok += 1
                continue

            exercise = Exercise(
                oef_path=path,
                title=title,
                level=level,
                domain=domain,
                lang=lang,
                keywords=meta.get('keywords', None),
            )
            db.add(exercise)
            ok += 1
            print(f"  + [{domain}] {title or os.path.basename(path)}")

        if not dry_run:
            await db.commit()

    await engine.dispose()
    print(f"\nRésultat : {ok} importés, {skip_exists} déjà en base, {skip_error} erreurs de rendu")


if __name__ == '__main__':
    parser = argparse.ArgumentParser()
    parser.add_argument('--level', default='H4')
    parser.add_argument('--domains', default='algebra,analysis,number,arithmetic')
    parser.add_argument('--wims-root', default='/var/lib/wims/public_html')
    parser.add_argument('--dry-run', action='store_true')
    args = parser.parse_args()

    domains = [d.strip() for d in args.domains.split(',')]
    asyncio.run(import_exercises(args.level, domains, args.wims_root, args.dry_run))
