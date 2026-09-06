import html
import os
import re
import unicodedata
from fastapi import APIRouter, Depends, HTTPException
from sqlalchemy.ext.asyncio import AsyncSession
from sqlalchemy import select

from db import get_db
from models.exercise import Exercise
from api.schemas.exercise import ExerciseResponse
from api.deps import get_current_user
from models.user import User
from core.oef.engine import find_def_path

router = APIRouter(prefix="/api/exercises", tags=["exercises"])


def _parse_index(index_path: str) -> dict:
    """Parse a WIMS INDEX file (key=value lines, ISO-8859-1 encoded)."""
    try:
        with open(index_path, encoding="iso-8859-1") as f:
            lines = f.readlines()
    except FileNotFoundError:
        return {}
    result = {}
    for line in lines:
        line = line.strip()
        if not line or line.startswith("#"):
            continue
        if "=" in line:
            k, v = line.split("=", 1)
            result[k.strip()] = v.strip()
    return result


def _module_from_path(oef_path: str) -> str:
    """Extract the module directory name from an oef_path.

    e.g. /ressources/H4/algebra/OEFevalwimsequ.fr/src/foo.oef
         -> OEFevalwimsequ.fr
    """
    parts = oef_path.replace("\\", "/").split("/")
    # structure: .../level/domain/module/src/exercise.oef
    return parts[-3] if len(parts) >= 4 else ""


def _module_dir_from_path(oef_path: str) -> str:
    """Return the module directory path (two levels above the .oef file)."""
    return os.path.dirname(os.path.dirname(oef_path))


def _format_author(raw: str) -> str:
    """Convert 'Firstname,Lastname' to 'Firstname Lastname'."""
    return raw.replace(",", " ").strip()


def _parse_exfile(file_path: str) -> dict[str, str]:
    """Parse a WIMS per-exercise metadata file (Extitles, Exkeywords, Exauthors).

    Format: one ``stem:value`` line per exercise (ISO-8859-1 encoded).
    Returns a dict mapping exercise stem → raw value string.
    """
    try:
        with open(file_path, encoding="iso-8859-1") as f:
            lines = f.readlines()
    except FileNotFoundError:
        return {}
    result: dict[str, str] = {}
    for line in lines:
        line = line.strip()
        if not line or line.startswith("#"):
            continue
        if ":" in line:
            stem, _, value = line.partition(":")
            result[stem.strip()] = value.strip()
    return result


def _split_csv(s: str) -> list[str]:
    """Split a comma-separated string into a cleaned list, skipping blanks."""
    return [item.strip() for item in s.split(",") if item.strip()]


@router.get("/", response_model=list[ExerciseResponse])
async def list_exercises(
    level: str | None = None,
    domain: str | None = None,
    lang: str = "fr",
    limit: int = 50,
    offset: int = 0,
    db: AsyncSession = Depends(get_db),
    _: User = Depends(get_current_user),
):
    query = select(Exercise).where(Exercise.lang == lang)
    if level:
        query = query.where(Exercise.level == level)
    if domain:
        query = query.where(Exercise.domain == domain)
    query = query.offset(offset).limit(limit)

    result = await db.execute(query)
    return result.scalars().all()


def _title_sort_key(title: str) -> list:
    """Natural, case/accent-insensitive sort key for an exercise title.

    Exercises are listed by their displayed title (not their filename). The key
    folds accents and case so "Évolution" sorts next to "Equation", and splits
    digit runs into ints so "Question 9" precedes "Question 10" (a plain string
    sort would put "10" first). WIMS itself orders via the module's `Exindex`,
    which we don't track; an alphabetical title sort is the closest intuitive
    equivalent and, here, also puts the "Course…" entries ahead of "Question…".
    """
    folded = "".join(
        c for c in unicodedata.normalize("NFKD", title or "") if not unicodedata.combining(c)
    ).casefold()
    return [
        int(tok) if tok.isdigit() else tok
        for tok in re.split(r"(\d+)", folded)
    ]


def _fold(texte: str) -> str:
    """Casse et accents pliés — la forme sous laquelle on compare une recherche.

    Un élève qui tape « algebre » doit trouver « algèbre », et « THALES »
    trouver « Thalès ». Même pliage que `_title_sort_key`, dont c'est la
    première moitié.
    """
    return "".join(
        c
        for c in unicodedata.normalize("NFKD", texte or "")
        if not unicodedata.combining(c)
    ).casefold()


# Le catalogue complet, construit une fois puis gardé en mémoire : 191 modules
# et 4278 exercices, quelques mégaoctets. Le reconstruire à chaque requête
# coûtait 200 ms — 136 de SQL, 37 de `find_def_path`, 20 de lecture des INDEX —
# et ce catalogue ne change pas en marche : les exercices sont importés par
# `entrypoint.sh` avant qu'`uvicorn` ne démarre, et aucune route n'en ajoute.
#
# **Le piège est celui de `_parse_def_cached`** : le cache vit aussi longtemps
# que le process. Un `INDEX` corrigé ou un exercice importé à chaud ne se voit
# qu'après `docker compose restart backend`.
_CATALOGUE: dict[str, list[dict]] | None = None


async def _catalogue(db: AsyncSession) -> dict[str, list[dict]]:
    """Les modules par langue, chacun portant ses exercices et ses clés de tri.

    Chaque entrée porte un champ `_hay` — le texte replié sur lequel une
    recherche se fait — pour que filtrer 4278 exercices reste une comparaison
    de chaînes déjà normalisées, et non 4278 pliages par frappe.
    """
    global _CATALOGUE
    if _CATALOGUE is not None:
        return _CATALOGUE

    result = await db.execute(select(Exercise).order_by(Exercise.oef_path))
    exercises = result.scalars().all()

    par_langue: dict[str, dict[str, dict]] = {}
    auteurs: dict[str, dict[str, str]] = {}

    for ex in exercises:
        mod_name = _module_from_path(ex.oef_path)
        if not mod_name:
            continue
        modules = par_langue.setdefault(ex.lang, {})
        if mod_name not in modules:
            mod_dir = _module_dir_from_path(ex.oef_path)
            idx = _parse_index(os.path.join(mod_dir, "INDEX"))
            raw_author = idx.get("author") or idx.get("maintainer") or ""
            # WIMS titles carry HTML entities (e.g. "Roue 1 en &euro;");
            # decode them to text since the sidebar renders titles plainly.
            titre = html.unescape(idx.get("title") or mod_name)
            description = idx.get("description") or ""
            auteur = _format_author(raw_author)
            mots = _split_csv(idx.get("keywords", ""))
            modules[mod_name] = {
                "module": mod_name,
                "title": titre,
                "description": description,
                "author": auteur,
                "keywords": mots,
                "domain": ex.domain or "",
                "level": ex.level or "",
                "lang": ex.lang,
                "exercises": [],
                "_hay": _fold(" ".join([titre, description, auteur, *mots])),
            }
            auteurs[mod_dir] = _parse_exfile(os.path.join(mod_dir, "Exauthors"))

        mod_dir = _module_dir_from_path(ex.oef_path)
        stem = os.path.splitext(os.path.basename(ex.oef_path))[0]
        titre_ex = html.unescape(ex.title or os.path.basename(ex.oef_path))
        auteur_ex = _format_author(auteurs.get(mod_dir, {}).get(stem, ""))
        mots_ex = list(ex.keywords or [])
        modules[mod_name]["exercises"].append(
            {
                "id": ex.id,
                "title": titre_ex,
                "has_def": find_def_path(ex.oef_path) is not None,
                "author": auteur_ex,
                "keywords": mots_ex,
                "_hay": _fold(" ".join([titre_ex, auteur_ex, *mots_ex])),
            }
        )

    for modules in par_langue.values():
        for mod in modules.values():
            # List exercises by their (displayed) title — not the filename the
            # DB query happened to order by.
            mod["exercises"].sort(key=lambda e: _title_sort_key(e["title"]))

    _CATALOGUE = {
        lang: sorted(modules.values(), key=lambda m: (m["domain"], m["title"].lower()))
        for lang, modules in par_langue.items()
    }
    return _CATALOGUE


def _sans_hay(obj: dict, cles: tuple[str, ...]) -> dict:
    """Copie d'une entrée du catalogue, privée de ses champs de travail."""
    return {k: v for k, v in obj.items() if k in cles}


_CLES_MODULE = (
    "module", "title", "description", "author", "keywords",
    "domain", "level", "lang",
)
_CLES_EXERCICE = ("id", "title", "has_def", "author", "keywords")

# Plafond d'exercices détaillés dans une réponse de recherche. Une requête d'une
# seule lettre correspond à presque tout le corpus — 3903 exercices, 692 Ko —, ce
# qui ramène exactement le poids qu'on cherche à ne plus envoyer. Le compte
# annoncé (`total`) reste exact : seul le détail est coupé, et `truncated` le dit
# pour que l'écran invite à préciser plutôt que d'afficher une liste tronquée en
# silence.
_MAX_RESULTATS = 400


@router.get("/modules")
async def list_modules(
    level: str | None = None,
    domain: str | None = None,
    lang: str = "fr",
    q: str | None = None,
    scope: str = "modules",
    db: AsyncSession = Depends(get_db),
    _: User = Depends(get_current_user),
):
    """Le catalogue filtré, plus les facettes qui permettent de le filtrer.

    La recherche se fait **ici**, et non dans le navigateur. La page chargeait
    les 3911 exercices francophones — 683 Ko — puis les filtrait en JavaScript
    à chaque frappe ; elle reçoit maintenant les 191 modules seuls (~40 Ko), et
    les exercices d'un module quand elle le déplie (`/modules/{nom}/exercises`)
    ou quand une recherche les désigne.

    `scope` reprend les trois portées de l'écran : `modules` cherche dans les
    métadonnées du module, `exercises` dans celles des exercices, `all` essaie
    le module puis se rabat sur ses exercices.

    Les facettes ne listent que les niveaux et domaines **réellement présents**
    dans la langue demandée : proposer `U4` quand aucun exercice ne s'y trouve
    n'aide personne.
    """
    catalogue = await _catalogue(db)
    modules = catalogue.get(lang, [])

    # Facettes : comptées avant le filtre textuel, mais après les autres, pour
    # que chaque menu montre ce que l'autre laisse effectivement disponible.
    niveaux: dict[str, int] = {}
    domaines: dict[str, int] = {}
    for mod in modules:
        n = len(mod["exercises"])
        if not domain or mod["domain"] == domain:
            niveaux[mod["level"]] = niveaux.get(mod["level"], 0) + n
        if not level or mod["level"] == level:
            domaines[mod["domain"]] = domaines.get(mod["domain"], 0) + n

    retenus = [
        m
        for m in modules
        if (not level or m["level"] == level) and (not domain or m["domain"] == domain)
    ]

    besoin = _fold((q or "").strip())
    sortie = []
    total = 0
    for mod in retenus:
        entree = _sans_hay(mod, _CLES_MODULE)
        entree["exercise_count"] = len(mod["exercises"])

        if not besoin:
            entree["exercises"] = []
            sortie.append(entree)
            total += entree["exercise_count"]
            continue

        module_correspond = besoin in mod["_hay"]
        if scope == "modules":
            trouves = mod["exercises"] if module_correspond else []
        elif scope == "exercises":
            trouves = [e for e in mod["exercises"] if besoin in e["_hay"]]
        else:
            trouves = (
                mod["exercises"]
                if module_correspond
                else [e for e in mod["exercises"] if besoin in e["_hay"]]
            )
        if not trouves:
            continue
        reste = max(0, _MAX_RESULTATS - total)
        entree["exercises"] = [_sans_hay(e, _CLES_EXERCICE) for e in trouves[:reste]]
        entree["match_count"] = len(trouves)
        sortie.append(entree)
        total += len(trouves)

    return {
        "modules": sortie,
        "levels": [
            {"code": c, "count": n} for c, n in sorted(niveaux.items()) if c
        ],
        "domains": [
            {"name": d, "count": n} for d, n in sorted(domaines.items()) if d
        ],
        "total": total,
        "searched": bool(besoin),
        "truncated": bool(besoin) and total > _MAX_RESULTATS,
    }


@router.get("/modules/{module}/exercises")
async def list_module_exercises(
    module: str,
    lang: str = "fr",
    db: AsyncSession = Depends(get_db),
    _: User = Depends(get_current_user),
):
    """Les exercices d'un module, servis quand l'écran le déplie.

    C'est la contrepartie de `/modules`, qui n'en renvoie plus aucun : sans
    cette route, afficher un module demanderait de recharger le catalogue
    entier.
    """
    catalogue = await _catalogue(db)
    for mod in catalogue.get(lang, []):
        if mod["module"] == module:
            return [_sans_hay(e, _CLES_EXERCICE) for e in mod["exercises"]]
    raise HTTPException(status_code=404, detail="Module introuvable")


def _module_title(oef_path: str) -> str | None:
    """Read the module's INDEX file and return its `title` field, if any."""
    mod_dir = _module_dir_from_path(oef_path)
    if not mod_dir:
        return None
    idx = _parse_index(os.path.join(mod_dir, "INDEX"))
    return idx.get("title") or None


@router.get("/{exercise_id}", response_model=ExerciseResponse)
async def get_exercise(
    exercise_id: str,
    db: AsyncSession = Depends(get_db),
    _: User = Depends(get_current_user),
):
    result = await db.execute(select(Exercise).where(Exercise.id == exercise_id))
    exercise = result.scalar_one_or_none()
    if not exercise:
        raise HTTPException(status_code=404, detail="Exercice introuvable")
    payload = ExerciseResponse.model_validate(exercise)
    payload.module_title = _module_title(exercise.oef_path)
    return payload


@router.get("/{exercise_id}/source")
async def get_exercise_source(
    exercise_id: str,
    db: AsyncSession = Depends(get_db),
    _: User = Depends(get_current_user),
):
    result = await db.execute(select(Exercise).where(Exercise.id == exercise_id))
    exercise = result.scalar_one_or_none()
    if not exercise:
        raise HTTPException(status_code=404, detail="Exercice introuvable")
    try:
        with open(exercise.oef_path, encoding="utf-8") as f:
            content = f.read()
    except UnicodeDecodeError:
        with open(exercise.oef_path, encoding="iso-8859-1") as f:
            content = f.read()
    except FileNotFoundError:
        raise HTTPException(
            status_code=404, detail="Fichier OEF introuvable sur disque"
        )
    return {"oef_path": exercise.oef_path, "content": content}
