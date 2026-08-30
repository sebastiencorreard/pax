"""Émulation de `chemeq`, le calculateur de chimie de WIMS.

`!exec chemeq` lit une formule ou une équation chimique et en tire, selon
l'option portée par la variable `chemeq_option`, la masse molaire (`M`) ou son
rendu LaTeX (`l` / `m`). Le binaire vit dans `wims/src/Misc/chemeq/` — du C++
avec lex/yacc — mais PAX n'appelle aucun processus externe : Maxima et PARI y
sont déjà émulés, et l'image n'en contient ni l'un ni l'autre.

Périmètre : ce que le corpus soumet réellement, soit les molécules et ions de
`slib/chemistry/chemeq_mass` et les équations de `chemeq_tex`. L'équilibrage
(`-e`, `-C`, dont `slib/chemistry/chemeq_equilibrium` a besoin) n'est pas
porté ; l'appel rend alors une chaîne vide, comme il le faisait pour tous.

Chaque sortie est confrontée au binaire du dépôt, qui sert d'oracle :
`backend/tests/test_chemeq.py` rejoue la comparaison sur toutes les entrées
relevées dans le corpus.

Grammaire couverte, telle que les exemples du corpus l'exercent :

    équation    := membre (('->' | '<->') membre)?
    membre      := terme ('+' terme)*
    terme       := coefficient? espèce
    coefficient := entier | entier '/' entier      (`2`, `3/2`)
    espèce      := groupe+ charge? état?
    groupe      := (symbole | '(' groupe+ ')') indice?
    charge      := '^' entier? ('+' | '-')         (`^+`, `^2-`)
    état        := '_' ('s' | 'l' | 'g' | 'aq')
"""

from __future__ import annotations

import re
from fractions import Fraction

# Masses molaires du tableau de `wims/src/Misc/chemeq/src/mendeleiev.cc`, tirées
# de NIST SP 966 (juillet 2019). Extraites du C++ par script plutôt que
# recopiées : une faute de frappe y serait indétectable à la lecture.
MASSES: dict[str, float] = {
    "H": 1.008, "He": 4.0026, "Li": 6.940, "Be": 9.0122, "B": 10.810, "C": 12.011,
    "N": 14.007, "O": 15.999, "F": 18.998, "Ne": 20.180, "Na": 22.990, "Mg": 24.305,
    "Al": 26.982, "Si": 28.085, "P": 30.974, "S": 32.060, "Cl": 35.450, "Ar": 39.948,
    "K": 39.098, "Ca": 40.078, "Sc": 44.956, "Ti": 47.867, "V": 50.942, "Cr": 51.996,
    "Mn": 54.938, "Fe": 55.845, "Co": 58.933, "Ni": 58.693, "Cu": 63.546, "Zn": 65.380,
    "Ga": 69.723, "Ge": 72.630, "As": 74.922, "Se": 78.971, "Br": 79.904, "Kr": 83.798,
    "Rb": 85.468, "Sr": 87.620, "Y": 88.906, "Zr": 91.224, "Nb": 92.906, "Mo": 95.950,
    "Tc": 97.000, "Ru": 101.070, "Rh": 102.910, "Pd": 106.420, "Ag": 107.870, "Cd": 112.410,
    "In": 114.820, "Sn": 118.710, "Sb": 121.760, "Te": 127.600, "I": 126.900, "Xe": 131.290,
    "Cs": 132.910, "Ba": 137.330, "La": 138.910, "Ce": 140.120, "Pr": 140.910, "Nd": 144.240,
    "Pm": 145.000, "Sm": 150.360, "Eu": 151.960, "Gd": 157.250, "Tb": 158.930, "Dy": 162.500,
    "Ho": 164.930, "Er": 167.260, "Tm": 168.930, "Yb": 173.050, "Lu": 174.970, "Hf": 178.49,
    "Ta": 180.95, "W": 183.84, "Re": 186.21, "Os": 190.23, "Ir": 192.22, "Pt": 195.08,
    "Au": 196.97, "Hg": 200.59, "Tl": 204.38, "Pb": 207.20, "Bi": 208.98, "Po": 209.00,
    "At": 210.00, "Rn": 222.00, "Fr": 223.00, "Ra": 226.00, "Ac": 227.000, "Th": 232.040,
    "Pa": 231.040, "U": 238.030, "Np": 237.000, "Pu": 244.000, "Am": 243.000, "Cm": 247.000,
    "Bk": 247.000, "Cf": 251.000, "Es": 252.000, "Fm": 257.000, "Md": 258.000, "No": 259.000,
    "Lr": 266.000, "Rf": 267.000, "Db": 268.000, "Sg": 269.000, "Bh": 270.000, "Hs": 269.000,
    "Mt": 278.000, "Ds": 281.000, "Rg": 282.000, "Cn": 285.000, "Nh": 286.000, "Fl": 289.000,
    "Mc": 289.000, "Lv": 293.000, "Ts": 294.000, "Og": 294.000
}


class ChemeqError(ValueError):
    """Entrée que la grammaire ne couvre pas — l'appelant rend alors le vide,
    comme le binaire rend son `ERROR: syntax error`."""


# `->` et `<->` séparent les deux membres ; le second est rendu par une double
# harpon, comme dans `chemeq.y`.
_FLECHES = ((r"<->", r"\leftrightharpoons"), (r"->", r"\longrightarrow"))

# Un symbole d'élément : majuscule éventuellement suivie d'une minuscule.
_SYMBOLE_RE = re.compile(r"[A-Z][a-z]?")
_ETATS = ("aq", "s", "l", "g")


class Terme:
    """Une espèce dans un membre d'équation, avec son coefficient.

    `atomes` garde l'ordre d'écriture et ne regroupe pas les symboles répétés,
    comme le fait `chemeq -C` ; `brut` est l'écriture normalisée que le binaire
    réaffiche (`H_2O` ressort `H2O`) ; `charge` est signée.
    """

    __slots__ = ("coefficient", "atomes", "tex", "brut", "charge")

    def __init__(self, coefficient, atomes, tex, brut, charge):
        self.coefficient = coefficient
        self.atomes = atomes
        self.tex = tex
        self.brut = brut
        self.charge = charge

    def affichage(self) -> str:
        """`2 H^+`, `1/2 O2`, `Fe` — coefficient puis formule, l'unité tue."""
        if self.coefficient == 1:
            return self.brut
        c = self.coefficient
        texte = f"{c.numerator}/{c.denominator}" if c.denominator != 1 else str(c.numerator)
        return f"{texte} {self.brut}"


class _Lecteur:
    """Curseur sur la chaîne, pour une descente récursive sans état global."""

    def __init__(self, src: str):
        self.src = src
        self.i = 0

    def fini(self) -> bool:
        return self.i >= len(self.src)

    def regarde(self) -> str:
        return self.src[self.i] if self.i < len(self.src) else ""

    def avale(self, quoi: str) -> bool:
        if self.src.startswith(quoi, self.i):
            self.i += len(quoi)
            return True
        return False

    def entier(self) -> int | None:
        m = re.match(r"\d+", self.src[self.i:])
        if not m:
            return None
        self.i += m.end()
        return int(m.group(0))

    def indice(self) -> int:
        """Indice d'un symbole ou d'un groupe, écrit `2` ou `_2`.

        Les auteurs emploient les deux — `H2O` comme `H_2O`, `(SO4)3` comme
        `(SO_4)_3` — et `chemeq` les tient pour équivalents. Le `_` d'un état
        (`_s`, `_g`) ne s'y confond pas : celui-là est suivi d'une lettre.
        """
        if re.match(r"_\d", self.src[self.i:]):
            self.i += 1
        return self.entier() or 1


def _lire_groupes(lec: _Lecteur) -> tuple[list, str, str]:
    """Suite de groupes — `H2O`, `(SO4)3` — jusqu'à la fin de l'espèce.

    Rend (atomes comptés, LaTeX, écriture normalisée). Les trois se
    construisent du même parcours : séparer les passes les ferait diverger.

    Les atomes ne sont **pas** regroupés : `CH3COOH` compte six entrées, une
    par symbole écrit, comme le fait `chemeq -C`. Seuls les indices de groupe
    se propagent — `Fe2(SO4)3` donne `Fe:2, S:3, O:12`.

    L'écriture normalisée est celle que `chemeq` réaffiche : indices collés au
    symbole, `H_2O` ressortant `H2O`.
    """
    atomes: list[tuple[str, int]] = []
    tex: list[str] = []
    brut: list[str] = []
    while not lec.fini():
        c = lec.regarde()
        if c == "(":
            lec.i += 1
            interne, tex_interne, brut_interne = _lire_groupes(lec)
            if not lec.avale(")"):
                raise ChemeqError("parenthèse non fermée")
            n = lec.indice()
            atomes += [(s, k * n) for s, k in interne]
            tex.append(f"({tex_interne})" + (f"_{{{n}}}" if n != 1 else ""))
            brut.append(f"({brut_interne})" + (str(n) if n != 1 else ""))
            continue
        m = _SYMBOLE_RE.match(lec.src, lec.i)
        if not m:
            break
        symbole = m.group(0)
        # `Cl` avant `C` : le symbole à deux lettres l'emporte, mais seulement
        # s'il existe. `CO` est carbone + oxygène, pas cobalt.
        if symbole not in MASSES:
            symbole = symbole[0]
            if symbole not in MASSES:
                break
        lec.i += len(symbole)
        n = lec.indice()
        atomes.append((symbole, n))
        tex.append(rf"\mathrm{{{symbole}}}" + (f"_{{{n}}}" if n != 1 else ""))
        brut.append(symbole + (str(n) if n != 1 else ""))
    if not atomes:
        raise ChemeqError("espèce vide")
    return atomes, "".join(tex), "".join(brut)


def _lire_espece(lec: _Lecteur) -> tuple[list, str, str, int]:
    """Une espèce : ses groupes, puis sa charge et son état, tous deux
    optionnels et sans effet sur la masse — un ion pèse ce que pèsent ses
    atomes, l'électron mis à part, que `chemeq` néglige comme nous.

    Rend (atomes, LaTeX, écriture normalisée, charge). La charge est signée :
    `Cl^-` vaut -1 et `Ca^2+` vaut 2, ce dont `chemeq -e` rend compte.
    """
    atomes, tex, brut = _lire_groupes(lec)
    charge = 0
    if lec.avale("^"):
        n = lec.entier()
        signe = lec.regarde()
        if signe not in "+-":
            raise ChemeqError("charge sans signe")
        lec.i += 1
        charge = (n if n else 1) * (1 if signe == "+" else -1)
        tex += f"^{{{n if n else ''}{signe}}}"
        brut += f"^{n if n else ''}{signe}"
    if lec.regarde() == "_":
        for etat in _ETATS:
            if lec.src.startswith("_" + etat, lec.i):
                # Un `_` suivi d'autre chose n'est pas un état : on le laisse.
                fin = lec.i + 1 + len(etat)
                if fin >= len(lec.src) or not lec.src[fin].isalnum():
                    lec.i = fin
                    tex += f"_{{({etat})}}"
                    brut += f"_({etat})"
                    break
    return atomes, tex, brut, charge


def _lire_terme(lec: _Lecteur) -> "Terme":
    """Coefficient éventuel — entier ou fraction — puis l'espèce."""
    while lec.regarde() == " ":
        lec.i += 1
    coefficient = Fraction(1)
    tex_coef = ""
    depart = lec.i
    n = lec.entier()
    if n is not None:
        if lec.avale("/"):
            d = lec.entier()
            if d is None:
                raise ChemeqError("fraction sans dénominateur")
            coefficient = Fraction(n, d)
            tex_coef = rf"\frac{{{n}}}{{{d}}}\,"
        else:
            coefficient = Fraction(n)
            tex_coef = f"{n}\\,"
        while lec.regarde() == " ":
            lec.i += 1
        # Un nombre seul n'est pas un terme : il annonce une espèce.
        if lec.fini() or not (lec.regarde().isupper() or lec.regarde() == "("):
            lec.i = depart
            coefficient, tex_coef = Fraction(1), ""
    atomes, tex, brut, charge = _lire_espece(lec)
    while lec.regarde() == " ":
        lec.i += 1
    return Terme(coefficient, atomes, tex_coef + tex, brut, charge)


def _lire_membre(src: str) -> list["Terme"]:
    """Les termes d'un membre, séparés par des `+` de premier niveau.

    Le `+` d'une charge (`Ca^2+`) n'en est pas un : il suit un `^` ou un
    chiffre qui le suit, jamais un blanc de séparation. On découpe donc sur le
    `+` qui ouvre un terme, repéré à la lecture plutôt qu'au découpage.
    """
    lec = _Lecteur(src.strip())
    termes = [_lire_terme(lec)]
    while not lec.fini():
        if not lec.avale("+"):
            raise ChemeqError(f"caractère inattendu : {lec.src[lec.i:]!r}")
        termes.append(_lire_terme(lec))
    return termes


def _format_c(x: float) -> str:
    """Un flottant comme `std::cout` l'imprime : six chiffres significatifs,
    zéros de queue retirés — `1801.56`, `588`, `18.015`."""
    s = f"{x:.6g}"
    return s


def masse_molaire(espece: list[tuple[str, int]]) -> float:
    return sum(MASSES[s] * n for s, n in espece)


def chemeq(entree: str, option: str) -> str:
    """Point d'entrée : l'équivalent d'un `!exec chemeq` sous `chemeq_option`.

    Rend la chaîne vide sur toute entrée hors périmètre — le binaire, lui,
    écrit `ERROR: syntax error at N` sur sa sortie standard, mais un message
    d'erreur qui remonterait dans une variable WIMS ferait plus de dégâts
    qu'un vide, que les scripts savent déjà traiter.
    """
    src = (entree or "").strip()
    if not src:
        return ""
    option = (option or "").strip()

    membres, fleche_tex = [src], ""
    for fleche, tex in _FLECHES:
        if fleche in src:
            gauche, _, droite = src.partition(fleche)
            membres, fleche_tex = [gauche, droite], tex
            break

    try:
        analyses = [_lire_membre(m) for m in membres]
    except (ChemeqError, KeyError, IndexError):
        return ""

    if option == "M":
        # Une masse par espèce, dans l'ordre de lecture, séparées par des
        # espaces — le coefficient stœchiométrique **compte** : `2Al` pèse
        # 53.964. C'est ce que lit `slib/chemistry/chemeq_mass`.
        sorties = [
            _format_c(float(t.coefficient) * masse_molaire(t.atomes))
            for membre in analyses
            for t in membre
        ]
        return " ".join(sorties)

    if option in ("l", "m"):
        rendus = ["\\,+\\,".join(t.tex for t in membre) for membre in analyses]
        return f"\\,{fleche_tex}\\,".join(rendus)

    if option in ("e", "C"):
        # Ces deux options décrivent l'équation membre par membre, pour
        # `slib/chemistry/chemeq_equilibrium` qui en tire son tableau. Sur une
        # **molécule seule**, sans flèche, le binaire n'a pas d'équation à
        # décrire et rend le LaTeX — comportement reproduit ici.
        if not fleche_tex:
            return chemeq(src, "l")
        membres_rendus = []
        for membre in analyses:
            especes = []
            for t in membre:
                if option == "e":
                    # `<affichage>|<coefficient>*<charge>`
                    detail = f"{_coefficient_texte(t.coefficient)}*{t.charge}"
                else:
                    # `<affichage>|<élément>:<coefficient>*<atomes>`, une entrée
                    # par symbole écrit, séparées par des espaces.
                    detail = " ".join(
                        f"{symbole}:{_coefficient_texte(t.coefficient)}*{n}"
                        for symbole, n in t.atomes
                    )
                especes.append(f"{t.affichage()}|{detail}")
            membres_rendus.append(", ".join(especes))
        return "; ".join(membres_rendus)

    # `v` (version) : hors périmètre.
    return ""


def _coefficient_texte(c: Fraction) -> str:
    return f"{c.numerator}/{c.denominator}" if c.denominator != 1 else str(c.numerator)
