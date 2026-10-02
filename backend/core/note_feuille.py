"""La note d'un élève sur une feuille, selon le modèle de WIMS.

Port, fonction par fonction, de trois sources de WIMS 4.32 — cf.
`docs/feuilles-eleve.md` §2 :

- `src/Wimslogd/wimslogdscore.c` : l'état d'un élève sur un exercice
  (`scoreline`), et ce que `cmd_getscore` en tire (points, qualité) ;
- `src/score.c` : les quatre pourcentages d'une feuille
  (`calc_getscorepercent`) et les prérequis (`_depcheck`) ;
- `scripts/adm/class/sheetweights` et `modules/adm/class/userscore` : la
  formule qui fait une note de ces pourcentages.

Rien ici ne touche la base : on y entre des notes, on en sort des nombres.
Les arrondis suivent `rint` du C, c'est-à-dire l'arrondi au pair de Python.
"""

from __future__ import annotations

import math
from dataclasses import dataclass, field

# `oldfactor` : l'amortissement de la qualité, « should remain stable ».
FACTEUR_QUALITE = 0.85
# `MAX_TRY` : les compteurs saturent.
MAX_ESSAIS = 60000
# `scoremax` par défaut d'une classe (`userscore/var.proc`).
NOTE_MAX = 10.0

# `scripts/adm/class/sheetformula`, dans l'ordre : le réglage `s` (0 à 6).
FORMULES = ("max(I,Q)", "I", "I*Q^0.3", "I*Q^0.5", "I*Q", "I^2*Q", "(I*Q)^2")
# `DF_SEVERITY = 1 2 1` (`bases/sys/define.conf`) : poids, formule, indicateur.
POIDS_DEFAUT, FORMULE_DEFAUT, INDICATEUR_DEFAUT = 1.0, 2, 1


@dataclass
class EtatExercice:
    """`struct scoredata` : ce que WIMS retient d'un élève sur un exercice."""

    user: float = 0.0      # somme des notes
    user2: float = 0.0     # qualité, amortie
    best: float = 0.0      # somme des N meilleures
    level: float = 0.0     # la plus faible des N meilleures
    last: float = 0.0
    essais: int = 0        # `try` : essais notés
    tirages: int = 0       # `new` : tirages, notés ou non
    indications: int = 0   # `hint`
    high: list[float] = field(default_factory=list)

    def tirer(self) -> None:
        """Un nouveau tirage (`new`, `renew`)."""
        if self.tirages < MAX_ESSAIS:
            self.tirages += 1

    def indiquer(self) -> None:
        """Une indication demandée (`hint`)."""
        self.indications += 1

    def noter(self, note: float, requis: int) -> None:
        """Une note enregistrée (`scoreline`, ligne `score`)."""
        if not math.isfinite(note):
            note = 0.0
        note = max(-10.0, min(10.0, note))
        self.user += note
        self.user2 = self.user2 * FACTEUR_QUALITE + note
        self.last = note
        # Les N meilleures, N = ⌈requis/10⌉, rangées par ordre croissant :
        # la nouvelle note chasse la plus faible et prend sa place.
        n = max(1, -(-requis // 10))
        if len(self.high) < n:
            self.high = [0.0] * (n - len(self.high)) + self.high
        if self.high[0] < note:
            self.best += note - self.high[0]
            k = 1
            while 10 * k < requis and k < len(self.high) and self.high[k] < note:
                self.high[k - 1] = self.high[k]
                k += 1
            self.high[k - 1] = note
            self.level = self.high[0]
        if self.essais < MAX_ESSAIS:
            self.essais += 1


@dataclass(frozen=True)
class ResultatExercice:
    """Une ligne de `cmd_getscore` (`struct scoreresult`)."""

    points: float    # `score` : somme des notes, plafonnée aux points requis
    qualite: float   # `mean` : 0 à 10
    meilleur: float  # `best`
    niveau: float    # `level`
    essais: int


def resultat(etat: EtatExercice, requis: int) -> ResultatExercice:
    """`cmd_getscore` pour un exercice de feuille."""
    if etat.essais <= 0:
        return ResultatExercice(0.0, 0.0, 0.0, 0.0, 0)
    points = min(etat.user, float(requis))
    tirages = etat.tirages + (1 if etat.indications > 0 else 0)
    # Un tirage abandonné par essai noté, plus cinq, sont gratuits.
    if tirages < etat.essais * 2 + 5:
        tt = 1.0
    else:
        tt = (tirages - 4) / (2 * etat.essais)
    ts = (1 - FACTEUR_QUALITE ** etat.essais) / (1 - FACTEUR_QUALITE)
    return ResultatExercice(points, etat.user2 / (ts * tt), etat.best, etat.level, etat.essais)


@dataclass(frozen=True)
class ExerciceDeFeuille:
    """Ce que la feuille dit d'un exercice : points requis, poids, actif."""

    requis: int = 10
    poids: float = 1.0
    actif: bool = True


@dataclass(frozen=True)
class Pourcentages:
    """`calc_getscorepercent` : une ligne `cumul qualité meilleur niveau`."""

    cumul: float     # I0, sur 100
    qualite: float   # Q, sur 10
    meilleur: float  # I1, sur 100
    niveau: float    # I2, sur 100


def pourcentages(lignes: list[tuple[ResultatExercice, ExerciceDeFeuille]]) -> Pourcentages:
    """Les quatre pourcentages d'une feuille."""
    def poids(e: ExerciceDeFeuille) -> float:
        # `require == 0` → poids nul ; un exercice inactif ne compte pas.
        return (e.poids if e.requis else 0.0) * (1 if e.actif else 0)

    somme = sum(e.requis * poids(e) for _, e in lignes)
    if somme == 0:
        return Pourcentages(0.0, 0.0, 0.0, 0.0)
    tot = moy = totb = totl = totw = 0.0
    for r, e in lignes:
        # Qualité < 1 : l'exercice est ignoré ; < 2 : ses points divisés par deux.
        if r.qualite < 1:
            continue
        dt, db, dl = r.points, r.meilleur, r.niveau
        if r.qualite < 2:
            dt, db, dl = dt / 2, db / 2, dl / 2
        w = poids(e)
        d = dt * w
        moy += r.qualite * d
        tot += d
        totb += db * w
        totl += dl * w
        totw += w
    return Pourcentages(
        cumul=round(100 * tot / somme),
        qualite=moy / tot if tot > 0 else 0.0,
        meilleur=round(100 * totb / somme),
        niveau=round(10 * totl / totw) if totw > 0 else 0.0,
    )


def note_feuille(p: Pourcentages, formule: int = FORMULE_DEFAUT,
                 indicateur: int = INDICATEUR_DEFAUT, note_max: float = NOTE_MAX) -> float:
    """La note de la feuille (`userscore/main.phtml`) : `scoremax × f(I, Q)`.

    `I` est le cumul, le meilleur ou le niveau (`indicateur` 0, 1 ou 2),
    ramené à 1 ; `Q` la qualité ramenée à 1.
    """
    i = (p.cumul, p.meilleur, p.niveau)[min(max(indicateur, 0), 2)] / 100
    q = p.qualite / 10
    f = (
        lambda: max(i, q),
        lambda: i,
        lambda: i * q ** 0.3,
        lambda: i * q ** 0.5,
        lambda: i * q,
        lambda: i ** 2 * q,
        lambda: (i * q) ** 2,
    )[min(max(formule, 0), 6)]()
    return round(100 * note_max * f) / 100


def note_globale(notes: list[tuple[float, float]], note_max: float = NOTE_MAX) -> float:
    """Moyenne des notes de feuilles actives, pondérée : `[(note, poids)]`."""
    total = sum(w for _, w in notes)
    if total <= 0:
        return 0.0
    return round(100 * sum(n * w for n, w in notes) / total) / 100


def prerequis_atteint(lignes: list[tuple[ResultatExercice, ExerciceDeFeuille]],
                      pourcentage: int) -> bool:
    """`_depcheck` : sur les exercices dont on dépend,
    `Σpoints/Σrequis · √(Σqualité/(n·10)) · 100 ≥ pourcentage`.
    Ignoré si `Σrequis < 10`."""
    ttot = sum(e.requis for _, e in lignes)
    if ttot < 10:
        return True
    tgot = sum(r.points for r, _ in lignes)
    tmean = sum(r.qualite for r, _ in lignes)
    return tgot / ttot * math.sqrt(tmean / (len(lignes) * 10)) * 100 >= pourcentage
