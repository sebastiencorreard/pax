"""L'élève et les feuilles : accès, tirages, enregistrement des notes.

Cf. `docs/feuilles-eleve.md` §3. Trois règles, toutes appliquées côté
serveur :

- un élève n'atteint un exercice de feuille que si la feuille est affectée à
  l'une de ses classes et visible (`sheet_classes.status` 1 « active » ou 2
  « périmée ») ;
- l'élève ne choisit pas sa graine : il reçoit son **tirage** en cours, ou un
  nouveau s'il le demande (le `new` de WIMS) ;
- une correction ne compte que sur un tirage délivré à cet élève et encore
  non noté, dans une feuille active et ouverte. Rejouer une graine dont on a
  vu la réponse ne rapporte plus rien (TODO IV.2 bis).
"""

from __future__ import annotations

import secrets
import uuid
from datetime import datetime

from sqlalchemy import select
from sqlalchemy.ext.asyncio import AsyncSession

from models.class_model import ClassStudent
from models.sheet import SheetClass, Tirage

# `sheet_classes.status`, comme WIMS : 0 en préparation, 1 active, 2 périmée,
# 3 cachée. Un élève voit une feuille active ou périmée ; seule l'active note.
ACTIVE, PERIMEE = 1, 2


async def affectation_eleve(db: AsyncSession, eleve_id: uuid.UUID, sheet_id: int) -> SheetClass | None:
    """L'affectation qui ouvre cette feuille à cet élève, ou None.

    Un élève peut la recevoir par plusieurs classes : l'affectation active
    passe devant la périmée.
    """
    lignes = (await db.execute(
        select(SheetClass)
        .join(ClassStudent, ClassStudent.class_id == SheetClass.class_id)
        .where(SheetClass.sheet_id == sheet_id,
               ClassStudent.student_id == eleve_id,
               SheetClass.status.in_((ACTIVE, PERIMEE)))
        .order_by(SheetClass.status)
    )).scalars().all()
    maintenant = datetime.utcnow()
    for aff in lignes:
        if aff.open_at is None or aff.open_at <= maintenant:
            return aff
    return None


def note_enregistrable(aff: SheetClass | None) -> bool:
    """La feuille note-t-elle en ce moment ? Active, et dans ses dates."""
    if aff is None or aff.status != ACTIVE:
        return False
    maintenant = datetime.utcnow()
    return ((aff.open_at is None or aff.open_at <= maintenant)
            and (aff.close_at is None or maintenant < aff.close_at))


async def tirage_courant(db: AsyncSession, eleve_id: uuid.UUID, item_id: int,
                         nouveau: bool = False) -> Tirage:
    """Le tirage en cours de l'élève sur cet exercice, ou un nouveau.

    Recharger la page rend le même énoncé ; seul un nouveau tirage demandé
    (`nouveau`) en délivre un autre — et compte, comme le `new` de WIMS, dans
    les tirages dont la qualité tient compte.
    """
    if not nouveau:
        courant = (await db.execute(
            select(Tirage)
            .where(Tirage.student_id == eleve_id, Tirage.sheet_item_id == item_id,
                   Tirage.scored_at.is_(None))
            .order_by(Tirage.issued_at.desc()).limit(1)
        )).scalar_one_or_none()
        if courant is not None:
            return courant
    tirage = Tirage(student_id=eleve_id, sheet_item_id=item_id,
                    seed=secrets.randbelow(2**31 - 2) + 1)
    db.add(tirage)
    await db.commit()
    await db.refresh(tirage)
    return tirage


async def tirage_a_noter(db: AsyncSession, eleve_id: uuid.UUID, item_id: int,
                         seed: int) -> Tirage | None:
    """Le tirage délivré à cet élève sous cette graine, s'il n'est pas noté."""
    return (await db.execute(
        select(Tirage)
        .where(Tirage.student_id == eleve_id, Tirage.sheet_item_id == item_id,
               Tirage.seed == seed, Tirage.scored_at.is_(None))
        .order_by(Tirage.issued_at.desc()).limit(1)
    )).scalar_one_or_none()


# ── Bilan d'un élève sur une feuille ─────────────────────────────────────────


def _prerequis(texte: str | None) -> tuple[list[int], int] | None:
    """`"1+3:60"` → `([1, 3], 60)` : les numéros d'exercices et le seuil."""
    if not texte or ":" not in texte:
        return None
    nums, _, seuil = texte.partition(":")
    try:
        return [int(n) for n in nums.split("+") if n.strip()], int(seuil)
    except ValueError:
        return None


async def bilan_eleve(db: AsyncSession, eleve_id: uuid.UUID, sheet) -> dict:
    """Le travail d'un élève sur une feuille, recalculé de ses tirages.

    Les tirages sont rejoués dans l'ordre à travers `core/note_feuille.py`,
    comme `rawscorecalc` relit le journal de WIMS : chacun compte comme un
    `new`, et sa note, s'il en a une, comme une ligne `score`.
    """
    from core.note_feuille import (  # noqa: PLC0415
        EtatExercice, ExerciceDeFeuille, note_feuille, pourcentages,
        prerequis_atteint, resultat,
    )

    items = sorted((i for i in sheet.items), key=lambda i: (i.position, i.id))
    etats = {i.id: EtatExercice() for i in items}
    tirages = (await db.execute(
        select(Tirage)
        .where(Tirage.student_id == eleve_id, Tirage.sheet_item_id.in_(list(etats) or [0]))
        .order_by(Tirage.issued_at)
    )).scalars().all()
    requis = {i.id: int(i.points or 0) for i in items}
    for t in tirages:
        e = etats[t.sheet_item_id]
        e.tirer()
        if t.hint:
            e.indiquer()
        if t.score is not None:
            e.noter(float(t.score), requis[t.sheet_item_id])

    resultats = {i.id: resultat(etats[i.id], requis[i.id]) for i in items}
    feuille = {i.id: ExerciceDeFeuille(requis[i.id], float(i.weight or 0), bool(i.active))
               for i in items}
    lignes = []
    for numero, i in enumerate(items, 1):
        r = resultats[i.id]
        verrou = False
        dep = _prerequis(i.prerequisite)
        if dep:
            nums, seuil = dep
            cibles = [items[n - 1] for n in nums if 1 <= n <= len(items)]
            verrou = not prerequis_atteint(
                [(resultats[c.id], feuille[c.id]) for c in cibles], seuil)
        lignes.append({
            "id": i.id, "numero": numero, "exercise_id": i.exercise_id,
            "actif": bool(i.active), "requis": requis[i.id], "poids": float(i.weight or 0),
            "prerequis": i.prerequisite, "verrouille": verrou,
            "points": r.points, "qualite": r.qualite, "meilleur": r.meilleur,
            "niveau": r.niveau, "essais": r.essais, "tirages": etats[i.id].tirages,
        })
    p = pourcentages([(resultats[i.id], feuille[i.id]) for i in items])
    note = note_feuille(p, int(sheet.note_formule), int(sheet.note_indicateur))
    return {"exercices": lignes, "cumul": p.cumul, "qualite": p.qualite,
            "meilleur": p.meilleur, "niveau": p.niveau, "note": note}


# ── Les notes d'une classe, vues par l'enseignant ────────────────────────────


async def _eleves(db: AsyncSession, class_id: int) -> list:
    from models.user import User  # noqa: PLC0415

    return list((await db.execute(
        select(User).join(ClassStudent, ClassStudent.student_id == User.id)
        .where(ClassStudent.class_id == class_id)
        .order_by(User.last_name, User.first_name)
    )).scalars().all())


def _eleve(u) -> dict:
    return {"id": str(u.id), "first_name": u.first_name, "last_name": u.last_name,
            "email": u.email}


async def notes_de_classe(db: AsyncSession, class_id: int) -> dict:
    """Le tableau des notes d'une classe : un élève par ligne, une feuille par
    colonne, et la note globale.

    Comme `adm/class/userscore` : seules les feuilles actives **ou périmées**
    (statut 1 ou 2) y figurent et comptent dans la moyenne, pondérée par leur
    `note_poids` — une feuille périmée garde ses notes. Chaque note est
    recalculée des tirages (`bilan_eleve`) : une requête par élève et par
    feuille, ce qu'une classe supporte.
    """
    from sqlalchemy.orm import selectinload  # noqa: PLC0415

    from core.note_feuille import note_globale  # noqa: PLC0415
    from models.sheet import Sheet  # noqa: PLC0415

    affs = (await db.execute(
        select(SheetClass, Sheet).join(Sheet, Sheet.id == SheetClass.sheet_id)
        .where(SheetClass.class_id == class_id, SheetClass.status.in_((ACTIVE, PERIMEE)))
        .options(selectinload(Sheet.items))
        .order_by(SheetClass.sheet_id)
    )).all()
    feuilles = [{"sheet_id": s.id, "title": s.title, "status": a.status,
                 "note_poids": float(s.note_poids)} for a, s in affs]
    lignes = []
    for u in await _eleves(db, class_id):
        notes, ponderees = {}, []
        for _, s in affs:
            b = await bilan_eleve(db, u.id, s)
            notes[s.id] = {"note": b["note"], "cumul": b["cumul"], "qualite": b["qualite"]}
            ponderees.append((b["note"], float(s.note_poids)))
        lignes.append({**_eleve(u), "notes": notes, "moyenne": note_globale(ponderees)})
    return {"feuilles": feuilles, "eleves": lignes}


async def notes_de_feuille(db: AsyncSession, sheet, class_id: int) -> dict:
    """Le détail d'une feuille pour une classe : un élève par ligne, un
    exercice par colonne (points, qualité, essais), et la note de feuille."""
    items = sorted(sheet.items, key=lambda i: (i.position, i.id))
    exercices = [{"id": i.id, "numero": n, "exercise_id": i.exercise_id,
                  "title": i.exercise.title if i.exercise else None,
                  "requis": int(i.points or 0), "actif": bool(i.active)}
                 for n, i in enumerate(items, 1)]
    lignes = []
    for u in await _eleves(db, class_id):
        b = await bilan_eleve(db, u.id, sheet)
        lignes.append({
            **_eleve(u),
            **{k: b[k] for k in ("note", "cumul", "qualite", "meilleur", "niveau")},
            "exercices": {e["id"]: {k: e[k] for k in ("points", "qualite", "essais", "tirages")}
                          for e in b["exercices"]},
        })
    return {"exercices": exercices, "eleves": lignes}


# En-têtes de l'export, dans la langue du séparateur (`core/oef/i18n.py`).
_ENTETES_CSV = {
    "fr": ("Nom", "Prénom", "Courriel", "Moyenne"),
    "nl": ("Naam", "Voornaam", "E-mail", "Gemiddelde"),
    "en": ("Last name", "First name", "Email", "Average"),
}


def _cellule(texte: str | None) -> str:
    """Un texte libre dans une cellule : `=`, `+`, `-` ou `@` en tête ferait
    d'un nom d'élève ou d'un titre de feuille une formule de tableur."""
    texte = texte or ""
    return f"'{texte}" if texte[:1] in ("=", "+", "-", "@", "\t", "\r") else texte


def csv_des_notes(notes: dict, lang: str | None) -> str:
    """Le tableau de `notes_de_classe` en CSV, comme l'export de WIMS
    (`userscore/csv/download.proc`, colonnes `login,name,allscore`) : un élève
    par ligne, puis ses notes de feuilles et la moyenne.

    Séparateurs et virgule décimale suivent la langue — un tableur français
    attend `;` et `2,5`. Un BOM ouvre le fichier : sans lui, Excel lit l'UTF-8
    comme du Windows-1252 et défigure les accents."""
    import csv  # noqa: PLC0415
    import io  # noqa: PLC0415

    from core.oef.i18n import _base, decimal_separator, list_separator  # noqa: PLC0415

    sep, dec = list_separator(lang), decimal_separator(lang)
    nom, prenom, courriel, moyenne = _ENTETES_CSV.get(_base(lang), _ENTETES_CSV["en"])

    def nombre(x: float) -> str:
        return f"{x:.2f}".replace(".", dec)

    sortie = io.StringIO()
    w = csv.writer(sortie, delimiter=sep, lineterminator="\r\n")
    feuilles = notes["feuilles"]
    w.writerow([nom, prenom, courriel, *(_cellule(f["title"]) for f in feuilles), moyenne])
    for e in notes["eleves"]:
        w.writerow([_cellule(e["last_name"]), _cellule(e["first_name"]), _cellule(e["email"]),
                    *(nombre(e["notes"][f["sheet_id"]]["note"]) for f in feuilles),
                    nombre(e["moyenne"])])
    return "\ufeff" + sortie.getvalue()
