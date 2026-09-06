"""
Script d'import d'exercices OEF dans la base PAX.

Usage:
    # Tous les niveaux découverts automatiquement (défaut) :
    python scripts/import_exercises.py
    # Un seul niveau / des domaines précis :
    python scripts/import_exercises.py --level H4 --domains algebra,analysis,number
"""

import sys
import os
import re
import argparse
import asyncio

# Dossiers de premier niveau importés par défaut : un nom « lettre majuscule +
# chiffre(s) » (H3, H4, H10…) plus les dossiers transverses `tool` et `Lang`.
LEVEL_RE = re.compile(r"^[A-Z]\d+$")
EXTRA_LEVEL_DIRS = ("tool", "Lang")


def discover_levels(resources_root: str) -> list[str]:
    """Liste triée des dossiers de niveau sous ``resources_root``.

    Retient ceux dont le nom est « <lettre majuscule><chiffre(s)> » (ex. H3,
    H4) ainsi que ``tool`` / ``Lang`` s'ils existent.
    """
    try:
        entries = os.listdir(resources_root)
    except FileNotFoundError:
        return []
    return sorted(
        d
        for d in entries
        if os.path.isdir(os.path.join(resources_root, d))
        and (LEVEL_RE.match(d) or d in EXTRA_LEVEL_DIRS)
    )

# Ajoute le répertoire parent au path
sys.path.insert(0, os.path.dirname(os.path.dirname(os.path.abspath(__file__))))

from sqlalchemy.ext.asyncio import create_async_engine, async_sessionmaker
from sqlalchemy import select
from config import settings
from models.exercise import Exercise, path_to_id
from core.oef.def_parser import parse as parse_def
from core.oef.engine import find_def_path


def extract_meta(oef_path: str) -> dict:
    """Titre, langue et mots-clés d'un exercice — lus dans son `.def`.

    PAX ne rend que des `.def` : c'est donc là que doit se lire ce qu'on montre
    de l'exercice, et non dans le `.oef` d'origine, qu'un parseur OEF entier
    était maintenu pour le seul bénéfice de cette fonction. Le `.def` porte
    `!set title=`, `language=` et `keywords=`, que `def_parser` extrait déjà ;
    la langue se lit sinon dans le suffixe du répertoire du module (`.fr`),
    comme le moteur le fait.

    **Les mots-clés arrivent en liste.** La colonne est un tableau, et lui
    passer la chaîne `literal_calculation` telle quelle la faisait éclater en
    caractères — `{l,i,t,e,r,a,l,_,…}` en base, et une recherche par mot-clé
    qui ne trouvait que des lettres.
    """
    def_path = find_def_path(oef_path)
    if not def_path:
        return {}
    try:
        try:
            with open(def_path, encoding="utf-8") as f:
                content = f.read()
        except UnicodeDecodeError:
            with open(def_path, encoding="cp1252") as f:
                content = f.read()
        df = parse_def(content)
    except Exception:
        return {}

    meta: dict = {}
    if df.title:
        meta["title"] = df.title.strip()
    lang = str(df.meta.get("language") or "").strip()
    if not lang:
        # `modules/<niveau>/<domaine>/<module>.<lang>/def/<ex>.def`
        module_dir = os.path.basename(os.path.dirname(os.path.dirname(def_path)))
        lang = module_dir.rsplit(".", 1)[-1] if "." in module_dir else ""
    if lang:
        meta["language"] = lang
    brut = str(df.meta.get("keywords") or "").strip()
    if brut:
        meta["keywords"] = [k.strip() for k in brut.split(",") if k.strip()]
    return meta


_LANGUES = {
    "french": "fr",
    "dutch": "nl",
    "english": "en",
    "german": "de",
    "spanish": "es",
}


def normalize_lang(brut: str | None) -> str | None:
    """Code ISO de la langue lue dans le `.def`, ou ``None`` si absente.

    Rendre ``None`` plutôt qu'un défaut permet à `rafraichir` de distinguer
    « le `.def` ne dit rien » de « le `.def` dit *fr* » : le premier cas ne
    doit jamais écraser ce que la base porte déjà.
    """
    if not brut:
        return None
    brut = str(brut).strip().lower()
    if not brut:
        return None
    return str(_LANGUES.get(brut, brut))[:5]


def rafraichir(
    exercise: Exercise,
    title: str | None,
    lang: str | None,
    keywords: list[str] | None,
    dry_run: bool,
) -> list[str]:
    """Aligne une ligne existante sur son `.def` ; rend les champs changés.

    L'import est relancé à chaque démarrage (`entrypoint.sh`) : sans cette
    passe il n'était qu'additif, et une correction d'`extract_meta` ne
    touchait jamais les 4277 lignes déjà là. C'est ainsi que des mots-clés
    découpés lettre par lettre et des langues fausses ont survécu au
    changement de source (le `.def` au lieu du `.oef`).

    **Rien n'est effacé** : un champ que le `.def` ne renseigne pas laisse en
    place ce que la base porte. Seule une valeur lue écrase une valeur lue.
    """
    champs = []
    for nom, valeur in (("title", title), ("lang", lang), ("keywords", keywords)):
        if valeur is None:
            continue
        if getattr(exercise, nom) == valeur:
            continue
        champs.append(nom)
        if not dry_run:
            setattr(exercise, nom, valeur)
    return champs


async def import_exercises(
    level: str, domains: list[str], resources_root: str, dry_run: bool
):
    engine = create_async_engine(settings.database_url)
    async_session = async_sessionmaker(engine, expire_on_commit=False)

    modules_path = os.path.join(resources_root, level)
    if not os.path.isdir(modules_path):
        print(f"Dossier introuvable : {modules_path}")
        return

    print(f"\n=== Niveau {level} ===")

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
                    chemin = os.path.join(root, f)
                    # PAX ne rend que des `.def` : sans lui, rien à importer.
                    if find_def_path(chemin):
                        oef_files.append((domain, chemin))
    oef_files.sort(key=lambda x: x[1])

    print(f"Fichiers trouvés : {len(oef_files)}")

    ok = 0
    maj = 0
    inchange = 0

    async with async_session() as db:
        for domain, path in oef_files:
            meta = extract_meta(path)
            title = meta.get("title") or None
            lang = normalize_lang(meta.get("language"))
            keywords = meta.get("keywords") or None

            res = await db.execute(select(Exercise).where(Exercise.oef_path == path))
            existant = res.scalar_one_or_none()

            if existant is not None:
                champs = rafraichir(existant, title, lang, keywords, dry_run)
                if not champs:
                    inchange += 1
                    continue
                maj += 1
                if dry_run:
                    print(f"  DRY-RUN MAJ : [{domain}] {existant.id} ({', '.join(champs)})")
                else:
                    await db.commit()
                    print(f"  ~ [{domain}] {existant.id} ({', '.join(champs)})")
                continue

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
                lang=lang or "fr",
                keywords=keywords,
            )
            db.add(exercise)
            await db.commit()
            ok += 1
            print(f"  + [{domain}] {title or os.path.basename(path)}")

    await engine.dispose()
    print(
        f"\nRésultat : {ok} importés, {maj} mis à jour, {inchange} déjà à jour"
    )


async def import_levels(
    levels: list[str], domains_arg: str | None, resources_root: str, dry_run: bool
):
    """Importe chaque niveau ; domaines explicites ou tous les sous-dossiers."""
    for level in levels:
        level_path = os.path.join(resources_root, level)
        if not os.path.isdir(level_path):
            print(f"Dossier introuvable : {level_path}")
            continue
        if domains_arg:
            domains = [d.strip() for d in domains_arg.split(",")]
        else:
            domains = sorted(
                d
                for d in os.listdir(level_path)
                if os.path.isdir(os.path.join(level_path, d))
            )
        await import_exercises(level, domains, resources_root, dry_run)


if __name__ == "__main__":
    parser = argparse.ArgumentParser()
    parser.add_argument(
        "--level",
        default=None,
        help="Niveau unique à importer (ex. H4). Par défaut : tous les dossiers "
        "« <lettre majuscule><chiffre> » + tool/Lang.",
    )
    parser.add_argument(
        "--domains",
        default=None,
        help="Comma-separated list of domains, or omit to import all available",
    )
    parser.add_argument("--resources-root", default=settings.resources_root)
    parser.add_argument("--dry-run", action="store_true")
    args = parser.parse_args()

    if args.level:
        levels = [args.level]
    else:
        levels = discover_levels(args.resources_root)
        if not levels:
            print(f"Aucun dossier de niveau trouvé sous {args.resources_root}")
        else:
            print(f"Niveaux découverts : {', '.join(levels)}")

    asyncio.run(
        import_levels(levels, args.domains, args.resources_root, args.dry_run)
    )
