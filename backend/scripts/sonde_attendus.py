"""Cherche les attendus que leur propre corrigé contredit.

**Le point aveugle qu'elle couvre.** `test_exercises_check` vérifie que
l'attendu est *accepté* par le correcteur — ce qui reste vrai quand l'attendu
lui-même est faux. Le 2026-09-07, `quizz/course12_2step` attendait `1/2` pour
un coefficient directeur qui vaut `-1/2` : les 21 017 tests passaient, et
l'élève qui répondait juste était compté faux. Seul un signalement d'usage l'a
révélé.

**Le principe.** La seule autre source de vérité dans un exercice est son
corrigé. On le déclenche en soumettant une réponse volontairement fausse (il ne
s'affiche que sur erreur), puis on confronte les nombres qu'il montre à
l'attendu du moteur. Si le corrigé affiche l'**opposé** de ce que le moteur
attend, et pas l'attendu, l'un des deux ment.

**Volontairement étroite.** Seul le signe opposé est signalé. Les nombres des
axes d'un graphique traversent le corrigé et confirmeraient n'importe quel
petit entier : mieux vaut rater des cas que crier au loup. Chaque signalement
demande une vérification à la main — au premier passage, les 6 signalements
étaient tous des faux positifs (un corrigé qui pose l'équation sans la
résoudre, ou qui donne un terme intermédiaire négatif).

**Sa couverture est sa limite** : elle n'examine que les attendus numériques
d'exercices dont le `:feedback` affiche des nombres, soit ~990 des quelque
21 000 réponses du corpus.

Usage :
    docker compose exec backend python scripts/sonde_attendus.py
    docker compose exec backend python scripts/sonde_attendus.py \\
        --racine /ressources/H3/math --graines 42,7
"""

import argparse
import glob
import os
import re
import sys
from fractions import Fraction

sys.path.insert(0, os.path.dirname(os.path.dirname(os.path.abspath(__file__))))

from core.answer.checkers import check_answer  # noqa: E402
from core.answer.schemas import AnswerResult  # noqa: E402
from core.answer.strategies.analyze import run_feedback  # noqa: E402
from core.oef.def_engine import load_and_render  # noqa: E402

_BALISE = re.compile(r"<[^>]*>")
_NOMBRE = re.compile(r"-?\d+(?:[.,]\d+)?(?:/\d+)?")
# Une réponse qu'aucun exercice n'attend : le corrigé ne sort que sur erreur.
_FAUX = "999999"
_NUMERIQUES = ("numeric", "numexp", "default", "auto")


def _valeur(txt) -> float | None:
    """Le nombre que porte ``txt`` — entier, décimal ou fraction —, ou None."""
    txt = str(txt).strip().replace(",", ".")
    if not txt:
        return None
    try:
        return float(Fraction(txt)) if "/" in txt else float(txt)
    except (ValueError, ZeroDivisionError, OverflowError):
        return None


def _nombres(html: str) -> list[float]:
    """Les nombres du corrigé, balises ôtées.

    Les attributs comptent autant que le texte : une URL d'image ou un chemin
    SVG est pleine de nombres qui ne veulent rien dire ici.
    """
    texte = _BALISE.sub(" ", html or "")
    return [v for v in (_valeur(m.group(0)) for m in _NOMBRE.finditer(texte)) if v is not None]


def _proche(a: float, b: float) -> bool:
    return abs(a - b) <= 1e-9 * max(1.0, abs(a), abs(b))


def _corrige(rendu, graine: int) -> str | None:
    """Le corrigé, tel qu'un élève qui s'est trompé le voit."""
    reponses = {a.input_name: _FAUX for a in rendu.answers}
    resultats = []
    for a in rendu.answers:
        c = check_answer(a.answer_type, _FAUX, a.expected or "", a.options, lang=rendu.lang)
        resultats.append(
            AnswerResult(
                input_name=a.input_name, correct=c.correct, score=c.score,
                method=c.method, reply=_FAUX, expected=a.expected,
                status=c.status, detail=c.detail,
            )
        )
    return run_feedback(rendu, list(rendu.answers), reponses, resultats, graine)


def balayer(racine: str, graines: list[int]) -> tuple[int, dict]:
    examines = 0
    suspects: dict[str, tuple] = {}
    for chemin in sorted(glob.glob(f"{racine}/**/def/*.def", recursive=True)):
        for graine in graines:
            try:
                rendu = load_and_render(chemin, seed=graine)
                if not (rendu.check_sections or {}).get("feedback"):
                    continue
                html = _corrige(rendu, graine)
            except Exception:
                continue
            nombres = _nombres(html or "")
            if not nombres:
                continue
            for a in rendu.answers:
                if a.answer_type not in _NUMERIQUES:
                    continue
                attendu = _valeur(a.expected)
                if attendu is None or attendu == 0:
                    continue
                examines += 1
                if any(_proche(attendu, n) for n in nombres):
                    continue           # le corrigé confirme l'attendu
                if any(_proche(-attendu, n) for n in nombres):
                    suspects.setdefault(chemin, (graine, a.input_name, a.expected))
    return examines, suspects


def main() -> int:
    p = argparse.ArgumentParser(description=__doc__.split("\n")[0])
    p.add_argument("--racine", default="/ressources")
    p.add_argument("--graines", default="42,7,1465921361")
    args = p.parse_args()

    graines = [int(g) for g in args.graines.split(",") if g.strip()]
    examines, suspects = balayer(args.racine.rstrip("/"), graines)

    for chemin, (graine, nom, attendu) in sorted(suspects.items()):
        print(f"{chemin}\tgraine={graine}\t{nom}\tattendu={attendu}")
    print(
        f"\n{examines} attendus confrontés à leur corrigé, "
        f"{len(suspects)} à vérifier à la main.",
        file=sys.stderr,
    )
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
