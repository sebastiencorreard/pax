"""Trois programmes que WIMS appelle par `!exec`, portés en Python.

L'image ne les embarque pas, et `_cmd_exec` rendait `""` pour chacun — si bien
que les exercices de H1, H2, H5 et H6 qui s'en servent affichaient des cases
vides. Chaque port suit sa source, citée en tête de fonction.

- `moneyprint` (`src/Misc/moneyprint/moneyprint.c`) : arrondir une liste de
  nombres à N décimales — 3 rendus, `OEFevalwimsdiv`, `oefexpalog10`… ;
- `float_calc` (`public_html/bin/float_calc`, un `bc -l`) : les changements de
  base d'`oefnumeration.fr` — 72 rendus ;
- `lceb` (`src/Misc/lceb/lceb_dynopt.c`) : le solveur du « compte est bon »
  d'`oeflceb.fr` — 10 rendus.
"""

from __future__ import annotations

import re
from fractions import Fraction

# ── moneyprint ────────────────────────────────────────────────────────────────

_MONEY_INTERDITS = set("\n\"'!=ABCDFGHIJKLMNOPQRSTUVWYZabcdfghijklmnopqrstuvwyz@#$%&()[]{}:~><?/\\|")
_MONEY_USAGE = (
    "error !\nusage:\n!exec moneyprint $your_wims_item_list $precision_word\n"
    "example:\nmoney=!exec moneyprint 1.2,30.1,.4,-.23123456 2\n"
    "The result is a comma separated list: 1.20,30.10,0.40,-0.23\n using 2 decimals\n"
    "Note: no calculations are done.\nNo spaces allowed"
)


def _atof(texte: str) -> float:
    """`atof` : le plus long préfixe lisible comme un réel, 0 sinon."""
    m = re.match(r"\s*[+-]?(\d+\.?\d*|\.\d+)([eE][+-]?\d+)?", texte)
    return float(m.group(0)) if m else 0.0


def moneyprint(parametre: str) -> str:
    """`!exec moneyprint LISTE [DÉCIMALES]` — chaque nombre arrondi.

    Port de `moneyprint.c` : `,` et `;` séparent (leur suite est conservée),
    2 décimales par défaut, et une notation scientifique (`1.2e+06`,
    `1.2*10^6`) garde sa puissance de 10, réécrite `*10^`. Une petite
    correction (`10^-(N+6)`) évite de tronquer `15.625` en `15.62`.
    """
    mots = parametre.split()
    if len(mots) not in (1, 2):
        return _MONEY_USAGE
    liste = mots[0]
    for c in liste:
        if c in _MONEY_INTERDITS:
            return f'error !\nfound illegal character "{c}" in argument'
    decimales = int(_atof(mots[1])) if len(mots) == 2 else 2
    if decimales > 32:
        return "error ! maximum amount of decimals is 32"

    # Le rang de chaque séparateur : `;` y est noté 1, `,` 0 (idx3 du C).
    separateurs = [1 if c == ";" else 0 for c in liste if c in ",;"]
    liste = liste.replace(";", ",")
    correction = 1 / 10 ** (decimales + 6)
    sortie: list[str] = []
    sep = ","
    for rang, mot in enumerate((t for t in liste.split(",") if t), start=1):
        if rang > 32:
            return "ERROR too many (> 32)conversion"
        if len(mot) > 31:
            return "ERROR string too large"
        pow_e = pow10 = 0
        nombre = exposant = ""
        for c in mot:
            if pow_e > 1:
                return "ERROR in syntax"
            if c == "+":
                continue
            if c in "eE":
                pow_e += 1
            elif c in "x*":
                pow10 += 1
            elif c == "^":
                pow10 = 5
            elif pow10 > 0:
                pow10 += 1
                if pow10 > 4:
                    exposant += c
            elif pow_e > 0:
                exposant += c
            else:
                nombre += c
        valeur = _atof(nombre)
        valeur = valeur + correction if valeur > 0 else valeur - correction
        texte = f"{valeur:.{decimales}f}"
        if pow_e == 1 or pow10 > 0:
            texte += f"*10^{exposant}"
        sortie.append(texte if rang == 1 else sep + texte)
        sep = ";" if rang - 1 < len(separateurs) and separateurs[rang - 1] == 1 else ","
    return "".join(sortie)


# ── float_calc (bc) ───────────────────────────────────────────────────────────

_CHIFFRES = "0123456789ABCDEF"

# Les bornes de GNU `bc` (1.07) : hors de ces bornes, il avertit sur la sortie
# d'erreur — que WIMS ne lit pas — et **ramène** la base à la borne. Or
# `oefnumeration/mult` écrit `obase=$val20; ibase=$val20`, `val20` étant la
# réponse de l'élève : une réponse `1` faisait tourner `ecrire` sans fin
# (`divmod(n, 1)` ne réduit jamais `n`) jusqu'à épuiser la mémoire du serveur.
_IBASE_MIN, _IBASE_MAX = 2, 36
_OBASE_MIN, _OBASE_MAX = 2, 2**31 - 1
# Plafond propre à PAX sur la taille d'une puissance, en bits : `bc` calcule
# `9^9^9` sans broncher, en y passant le temps qu'il faut, et WIMS l'arrête au
# bout de son délai d'`!exec`. Ici, sans délai, c'est un refus.
_BITS_MAX = 100_000


class _Bc:
    """Le sous-ensemble de `bc` qu'emploient les exercices : `ibase`, `obase`
    et des expressions entières (`+ - * / % ^`, parenthèses, moins unaire).
    Les chiffres `0-9` et `A-F` valent leur valeur quelle que soit la base,
    comme dans `bc`."""

    def __init__(self) -> None:
        self.ibase = 10
        self.obase = 10

    def _nombre(self, texte: str) -> Fraction:
        # Un chiffre seul vaut sa valeur quelle que soit la base ; dans un
        # nombre à plusieurs chiffres, un chiffre ≥ `ibase` vaut `ibase - 1`
        # (`bc` : `ibase=2; 12*13` rend `1001`, soit 3 × 3).
        if len(texte) == 1:
            return Fraction(_CHIFFRES.index(texte))
        entier, _, frac = texte.partition(".")

        def chiffre(c: str) -> int:
            return min(_CHIFFRES.index(c), self.ibase - 1)

        valeur = Fraction(0)
        for c in entier:
            valeur = valeur * self.ibase + chiffre(c)
        echelle = Fraction(1)
        for c in frac:
            echelle /= self.ibase
            valeur += chiffre(c) * echelle
        return valeur

    def evaluer(self, texte: str) -> Fraction:
        jetons = re.findall(r"[0-9A-F.]+|[-+*/%^()]", texte)
        pos = 0

        def voir() -> str | None:
            return jetons[pos] if pos < len(jetons) else None

        def prendre() -> str:
            nonlocal pos
            pos += 1
            return jetons[pos - 1]

        def somme() -> Fraction:
            v = produit()
            while voir() in ("+", "-"):
                v = v + produit() if prendre() == "+" else v - produit()
            return v

        def produit() -> Fraction:
            v = puissance()
            while voir() in ("*", "/", "%"):
                op = prendre()
                w = puissance()
                if op == "*":
                    v *= w
                elif op == "/":
                    v /= w
                else:
                    v = v - w * int(v / w)
            return v

        def puissance() -> Fraction:
            v = unaire()
            if voir() == "^":
                prendre()
                exposant = int(puissance())
                taille = max(v.numerator.bit_length(), v.denominator.bit_length(), 1)
                if abs(exposant) * taille > _BITS_MAX:
                    raise ValueError("puissance trop grande")
                v = v ** exposant
            return v

        def unaire() -> Fraction:
            if voir() == "-":
                prendre()
                return -unaire()
            if voir() == "(":
                prendre()
                v = somme()
                if voir() == ")":
                    prendre()
                return v
            return self._nombre(prendre())

        return somme()

    def ecrire(self, valeur: Fraction) -> str:
        if valeur.denominator != 1:
            raise ValueError("résultat non entier")
        n = int(valeur)
        signe = "-" if n < 0 else ""
        n = abs(n)
        if n == 0:
            return "0"
        chiffres = []
        while n:
            n, r = divmod(n, self.obase)
            chiffres.append(r)
        chiffres.reverse()
        if self.obase <= 16:
            return signe + "".join(_CHIFFRES[d] for d in chiffres)
        # Au-delà de 16, `bc` écrit chaque chiffre en décimal, précédé d'une
        # espace et sur autant de caractères que `obase - 1`.
        largeur = len(str(self.obase - 1))
        return signe + "".join(f" {d:0{largeur}d}" for d in chiffres)


def float_calc(parametre: str) -> str:
    """`!exec float_calc SCRIPT` — `bc -l` sur le script.

    `oefnumeration.fr` s'en sert pour changer de base :
    `obase=7; ibase=10; 48` → `66`, ou calculer en base B :
    `obase=5; ibase=5; 12 + 3` → `20`. Chaque expression qui n'est pas une
    affectation écrit sa valeur sur une ligne, en `obase`. `ibase` et `obase`
    se lisent dans la base d'entrée courante, comme chez `bc`.
    """
    bc = _Bc()
    lignes: list[str] = []
    try:
        for instruction in re.split(r"[;\n]", parametre):
            instruction = instruction.strip()
            if not instruction:
                continue
            m = re.fullmatch(r"(ibase|obase)\s*=\s*(.+)", instruction)
            if m:
                valeur = int(bc.evaluer(m.group(2)))
                if m.group(1) == "ibase":
                    bc.ibase = min(max(valeur, _IBASE_MIN), _IBASE_MAX)
                else:
                    bc.obase = min(max(valeur, _OBASE_MIN), _OBASE_MAX)
                continue
            lignes.append(bc.ecrire(bc.evaluer(instruction)))
    except (ValueError, IndexError, ZeroDivisionError):
        return ""
    return "\n".join(lignes)


# ── lceb, le compte est bon ───────────────────────────────────────────────────

_OPS = "+*-/"
# Plafond propre à PAX : la recherche du C est exhaustive, et ce qui dure une
# fraction de seconde en C peut dépasser le budget d'un rendu en Python. Au-delà,
# on conclut comme si rien n'avait été trouvé.
_LCEB_PLAFOND = 400_000


class _R:
    __slots__ = ("val", "op", "l", "r", "used")

    def __init__(self, val: int, op: int = -1, l=None, r=None, used: int = 0):
        self.val, self.op, self.l, self.r, self.used = val, op, l, r, used


class _Trouve(Exception):
    def __init__(self, resultat: _R):
        self.resultat = resultat


def _operer(op: int, a: int, b: int) -> int | None:
    """Les quatre opérations de `lceb_dynopt.c`, entiers non signés 32 bits."""
    if op == 0:
        res = a + b if a and b else None
    elif op == 1:
        res = None if a == 1 or b == 1 else a * b
    elif op == 2:
        res = a - b if a and b else None
    else:
        res = None if (not b or b == 1 or a % b) else a // b
    if res is None:
        return None
    res &= 0xFFFFFFFF
    return None if res == 0xFFFFFFFF else res


def _afficher(r: _R, lignes: list[str]) -> None:
    if r.op >= 0:
        _afficher(r.l, lignes)
        _afficher(r.r, lignes)
        lignes.append(f"{r.l.val} {_OPS[r.op]} {r.r.val} = {r.val}")


def lceb(parametre: str) -> str:
    """`!exec lceb BUT N1 … N6` — trouver BUT avec les six nombres.

    Port de `lceb_dynopt.c`, bizarreries comprises, parce que l'exercice lit
    la sortie telle quelle (`!line 3 to -1`) : la première solution trouvée
    l'emporte, dans l'ordre de génération du C ; ses boucles `p->next` ne
    visitent pas le dernier élément d'une liste ; et l'écart du meilleur
    résultat approché y reste signé.
    """
    mots = parametre.split()
    if len(mots) != 7:
        return "There should be 7 arguments. goal, following by the 6 numbersto use"
    but = int(_atof(mots[0]))
    base = [_R(int(_atof(m)) & 0xFFFFFFFF, used=1 << i) for i, m in enumerate(mots[1:])]
    lignes = ["Processing " + "".join(f"{r.val} " for r in base) + f". Goal : {but}"]
    resultats: list[list[_R]] = [base, [], [], [], [], []]
    compte = 0

    def tester(r: _R) -> None:
        if r.val == but:
            raise _Trouve(r)

    def ajouter(cible: list[_R], p: _R, q: _R) -> None:
        nonlocal compte
        if p.val < q.val:
            p, q = q, p
        if p.used & q.used:
            return
        used = p.used | q.used
        for op in range(4):
            val = _operer(op, p.val, q.val)
            if val is None:
                continue
            r = _R(val, op, p, q, used)
            cible.append(r)
            compte += 1
            tester(r)
        if compte > _LCEB_PLAFOND:
            raise OverflowError

    def paires(liste: list[_R], cible: list[_R]) -> None:
        # `for (p = L; p->next; …) for (q = p->next; q; …)`
        for i in range(len(liste) - 1):
            for q in liste[i + 1 :]:
                ajouter(cible, liste[i], q)

    def croiser(gauche: list[_R], droite: list[_R], cible: list[_R]) -> None:
        for p in gauche:
            for q in droite:
                ajouter(cible, p, q)

    try:
        for p in base[:-1]:
            tester(p)
        paires(base, resultats[1])
        croiser(resultats[1], base, resultats[2])
        paires(resultats[1], resultats[3])
        croiser(resultats[2], base, resultats[3])
        croiser(resultats[3], base, resultats[4])
        croiser(resultats[2], resultats[1], resultats[4])
        paires(resultats[2], resultats[5])
        croiser(resultats[3], resultats[1], resultats[5])
        croiser(resultats[4], base, resultats[5])
    except _Trouve as trouve:
        lignes.append("FOUND")
        _afficher(trouve.resultat, lignes)
        return "\n".join(lignes)
    except OverflowError:
        pass

    meilleur, minimum = None, 10000
    for liste in resultats:
        for p in liste:
            if abs(p.val - but) < minimum:
                meilleur, minimum = p, p.val - but
    if meilleur is None:
        return "\n".join(lignes)
    lignes.append(f"NOTFOUND {meilleur.val} {minimum}")
    _afficher(meilleur, lignes)
    return "\n".join(lignes)
