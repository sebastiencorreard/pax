"""Les réglages sous lesquels un exercice est rendu, puis corrigé.

Chez WIMS, l'enseignant règle un exercice en le posant sur une feuille : le
niveau de sévérité `qcmlevel` (1 à 9, `oef/exo.init`) et les `confparm` que le
module expose dans son `introhook.phtml`. La priorité est celle de TODO I.2 :

    valeurs du module  →  réglage de la feuille  →  paramètre d'URL

Le paramètre d'URL `qcmlevel` sert à l'essai ponctuel. Il est réservé aux
enseignants : sinon un élève n'aurait qu'à retoucher l'adresse pour baisser la
sévérité d'une feuille notée.

Rendu et correction doivent passer par ici avec les **mêmes** arguments. Le
niveau change la palette d'un `\\choice` (`qcmpresent`) ; une correction
rendue sous un autre niveau ne corrigerait pas ce que l'élève a vu.
"""

from dataclasses import dataclass, field

from fastapi import HTTPException
from sqlalchemy.ext.asyncio import AsyncSession

from models.sheet import SheetExercise
from models.user import User

ROLES_ENSEIGNANT = ("teacher", "admin", "super_admin")


@dataclass
class Reglages:
    # Ce que le moteur verse dans son ctx (`qcmlevel`, `confparm<n>`).
    moteur: dict[str, str] = field(default_factory=dict)
    # La feuille d'où ils viennent, pour rattacher la tentative.
    sheet_id: int | None = None
    # Les paramètres de la requête, que le front renvoie tels quels à la
    # correction pour qu'elle rende l'exercice sous les mêmes réglages.
    demande: dict[str, int] = field(default_factory=dict)


async def resoudre_reglages(
    db: AsyncSession,
    exercise_id: str,
    user: User,
    sheet_item: int | None,
    qcmlevel: int | None,
) -> Reglages:
    reg = Reglages()
    if sheet_item is not None:
        item = await db.get(SheetExercise, sheet_item)
        if item is None or item.exercise_id != exercise_id:
            raise HTTPException(
                status_code=404, detail="Exercice introuvable sur cette feuille"
            )
        reg.sheet_id = item.sheet_id
        reg.demande["sheet_item"] = sheet_item
        reg.moteur.update(item.confparm or {})
        if item.qcmlevel is not None:
            reg.moteur["qcmlevel"] = str(item.qcmlevel)
    if qcmlevel is not None:
        if user.role not in ROLES_ENSEIGNANT:
            raise HTTPException(
                status_code=403,
                detail="Seul un enseignant peut changer le niveau de sévérité",
            )
        reg.moteur["qcmlevel"] = str(qcmlevel)
        reg.demande["qcmlevel"] = qcmlevel
    return reg
