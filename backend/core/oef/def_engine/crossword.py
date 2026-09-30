"""`!exec crossword <fichier>` — le générateur de grilles de mots croisés.

Port de `wims/src/Misc/crossword/crossword.c` (jigsaw, Franz Korntner 1996,
adapté à WIMS par Bernadette Perrin-Riou), que `slib/text/crossword` appelle
sur la liste de mots déposée par `oef/togetfile.proc`. Il rend la grille en
lignes d'items : une lettre par case, une case vide pour un noir.

L'algorithme est **déterministe** — aucun tirage : la même liste donne la
même grille. Le port en profite pour se juger au binaire de l'arbre, sortie
contre sortie (`tests/core/oef/test_crossword.py`). Il en garde donc les
détails qui décident d'un départage : le score en `float` 32 bits, le hachage
tel que gcc l'a compilé (voir `_place`), l'ordre des
listes chaînées, et les mutations que `scan_grid` fait subir à la grille
qu'elle parcourt avant d'en copier les filles.

La variante `SYMMETRICAL` (0 dans le source) et les diagnostics ne sont pas
portés. La limite de temps (`TIMEMAX`, près de dix minutes) devient une limite
à quelques secondes : à l'échéance, comme le C, on rend la meilleure grille
trouvée.
"""

from __future__ import annotations

import struct
import time

GRIDMAX = 22
WORDMAX = 256
WORDLENMAX = 32
ADJMAX = 128
SCOREMAX = 1000
NODEMAX = 1500

STAR = 28
FREE = 31
TODOH = 1
TODOV = 2
BORDER = 4

_N = GRIDMAX * GRIDMAX
_DELAI = 8.0  # secondes
_HACHE_LETTRE = 0x7FFFFFFF


def _f32(x: float) -> float:
    return struct.unpack("f", struct.pack("f", x))[0]


class _Temps(Exception):
    pass


class _Node:
    __slots__ = ("words", "numword", "numchar", "numconn", "hash", "firstlevel",
                 "lastlevel", "score", "adjdir", "adjxy", "adjl", "grid", "attr")

    def copie(self) -> "_Node":
        n = _Node.__new__(_Node)
        n.words = self.words
        n.numword = self.numword
        n.numchar = self.numchar
        n.numconn = self.numconn
        n.hash = self.hash
        n.firstlevel = self.firstlevel
        n.lastlevel = self.lastlevel
        n.score = self.score
        n.adjdir = self.adjdir[:]
        n.adjxy = self.adjxy[:]
        n.adjl = self.adjl[:]
        n.grid = self.grid[:]
        n.attr = self.attr[:]
        return n


def _noeud_vide() -> _Node:
    n = _Node.__new__(_Node)
    n.words = 0
    n.numword = n.numchar = n.numconn = n.hash = 0
    n.firstlevel = n.lastlevel = 0
    n.score = 0.0
    n.adjdir, n.adjxy, n.adjl = [], [], []
    n.grid = bytearray(_N)
    n.attr = bytearray(_N)
    return n


def _ischar(c: int) -> bool:
    return c < STAR


class _Jigsaw:
    def __init__(self, mots: list[bytes]):
        self.wordbase = mots
        self.wlen = [len(m) for m in mots]
        self.numword = len(mots)
        # Liens : (mot, décalage, suivant) — l'index 0 signifie « fin ».
        self.lw = [0]
        self.lofs = [0]
        self.lnext = [0]
        self.links1 = [0] * 32
        self.links2 = [0] * (32 * 32)
        self.links3 = [0] * (32 * 32 * 32)
        self._liens()
        self.xy2level = [(i % GRIDMAX) + (i // GRIDMAX) for i in range(_N)]
        self.level2xy = [
            i + GRIDMAX - 1 if i < GRIDMAX
            else _N - (GRIDMAX * 2 - 3 - i) * GRIDMAX - 2
            for i in range(GRIDMAX * 2)
        ]
        self.scores: list[list[_Node]] = [[] for _ in range(SCOREMAX)]
        self.solution = _noeud_vide()
        self.numnode = self.realnumnode = 0
        self.echeance = time.monotonic() + _DELAI

    def _lien(self, w: int, ofs: int, suivant: int) -> int:
        self.lw.append(w)
        self.lofs.append(ofs)
        self.lnext.append(suivant)
        return len(self.lw) - 1

    def _liens(self) -> None:
        done = False
        i = 0
        while not done and i < WORDLENMAX:
            done = True
            for w in range(self.numword - 1, -1, -1):
                p = self.wordbase[w]
                n = self.wlen[w]
                if i <= n - 3:
                    k = (p[i] * 32 + p[i + 1]) * 32 + p[i + 2]
                    self.links3[k] = self._lien(w, -i, self.links3[k])
                    done = False
                if i <= n - 2:
                    k = p[i] * 32 + p[i + 1]
                    self.links2[k] = self._lien(w, -i, self.links2[k])
                    done = False
                if 0 < i <= n - 2:
                    self.links1[p[i]] = self._lien(w, -i, self.links1[p[i]])
                    done = False
            i += 1

    # -- tests et placements ------------------------------------------------

    def _paire(self, grid, avant: int, c: int, apres: int) -> int:
        """Le lien d'une lettre posée entre deux voisines d'une autre ligne."""
        if grid[avant] == FREE:
            return self.links2[c * 32 + grid[apres]]
        if grid[apres] == FREE:
            return self.links2[grid[avant] * 32 + c]
        return self.links3[(grid[avant] * 32 + c) * 32 + grid[apres]]

    def _test(self, d: _Node, xybase: int, word: int, pas: int, trav: int) -> bool:
        n = self.wlen[word]
        if pas == 1:
            if xybase < 0 or xybase + n >= _N + 1:
                return False
        elif xybase < 0 or xybase + n * GRIDMAX >= _N + GRIDMAX:
            return False
        grid = d.grid
        xy = xybase
        for c in self.wordbase[word]:
            g = grid[xy]
            if g != c:
                if g != FREE:
                    return False
                if c != STAR and (_ischar(grid[xy - trav]) or _ischar(grid[xy + trav])):
                    if self._paire(grid, xy - trav, c, xy + trav) == 0:
                        return False
            xy += pas
        return True

    def _place(self, data: _Node, xybase: int, word: int, horiz: bool) -> int:
        if data.words >> word & 1:
            return 0
        n = self.wlen[word]
        if horiz:
            pas, trav, sens, autre = 1, GRIDMAX, "V", "H"
            if xybase < 0 or xybase + n >= _N + 1:
                return 0
        else:
            pas, trav, sens, autre = GRIDMAX, 1, "H", "V"
            if xybase < 0 or xybase + n * GRIDMAX >= _N + GRIDMAX:
                return 0

        grid = data.grid
        numadj = len(data.adjxy)
        nouv: list[tuple[int, int]] = []  # (xy, lien)
        xy = xybase
        for c in self.wordbase[word]:
            g = grid[xy]
            if g != c:
                if g != FREE:
                    return 0
                if c != STAR and (_ischar(grid[xy - trav]) or _ischar(grid[xy + trav])):
                    if grid[xy - trav] == FREE:
                        a_xy, lien = xy, self.links2[c * 32 + grid[xy + trav]]
                    elif grid[xy + trav] == FREE:
                        a_xy, lien = xy - trav, self.links2[grid[xy - trav] * 32 + c]
                    else:
                        a_xy = xy - trav
                        lien = self.links3[(grid[xy - trav] * 32 + c) * 32 + grid[xy + trav]]
                    if lien == 0 or numadj + len(nouv) == ADJMAX - 1:
                        return 0
                    nouv.append((a_xy, lien))
            xy += pas

        # Les paires nouvelles existent-elles vraiment ?
        verifies = []
        for a_xy, l in nouv:
            while l:
                if self._test(data, a_xy + self.lofs[l] * trav, self.lw[l],
                              trav, pas):
                    break
                l = self.lnext[l]
            if l == 0:
                return 0
            verifies.append((a_xy, l))

        d = data.copie()
        d.words |= 1 << word
        d.numword += 1
        for a_xy, l in verifies:
            d.adjdir.append(sens)
            d.adjxy.append(a_xy)
            d.adjl.append(l)
        grid, attr = d.grid, d.attr
        todo_ici = TODOH if horiz else TODOV
        todo_autre = TODOV if horiz else TODOH
        xy = xybase
        for c in self.wordbase[word]:
            if c != STAR:
                attr[xy] &= ~todo_ici
                for i in range(len(d.adjxy)):
                    if d.adjdir[i] == autre and d.adjxy[i] == xy:
                        # `d->adjdir[i] = d->adjdir[--d->numadj]` : le dernier
                        # prend la place du retiré.
                        dern = len(d.adjxy) - 1
                        d.adjdir[i] = d.adjdir[dern]
                        d.adjxy[i] = d.adjxy[dern]
                        d.adjl[i] = d.adjl[dern]
                        del d.adjdir[dern], d.adjxy[dern], d.adjl[dern]
                        break
                if grid[xy] == FREE:
                    # `d->hash += (123456+xy)*(123456-*p)` : le produit déborde
                    # toujours un `int`, et gcc -O2, qui le sait indéfini, l'a
                    # remplacé par une constante — `addq $0x7fffffff` dans le
                    # binaire de l'arbre. On suit le binaire, pas le source.
                    d.hash = (d.hash + _HACHE_LETTRE) & 0xFFFFFFFFFFFFFFFF
                    attr[xy] |= todo_autre
                    d.numchar += 1
                else:
                    d.numconn += 1
            grid[xy] = c
            xy += pas

        niveau = self.xy2level[xy - pas]
        if niveau > d.lastlevel:
            d.lastlevel = niveau
        self._ajoute(d)
        return 1

    def _ajoute(self, d: _Node) -> None:
        d.score = _f32(_f32(float(d.numconn)) / _f32(float(d.numchar)))
        i = int(_f32(d.score * (SCOREMAX - 1)))
        i = min(max(i, 0), SCOREMAX - 1)
        seau = self.scores[i]
        k = 0
        while k < len(seau):
            nx = seau[k]
            if d.score > nx.score or (d.score == nx.score and d.hash >= nx.hash):
                break
            k += 1
        while k < len(seau) and d.score == seau[k].score and d.hash == seau[k].hash:
            if d.grid == seau[k].grid:
                return
            k += 1
        seau.insert(k, d)
        if not d.adjxy:
            self.numnode += 1
        self.realnumnode += 1

    # -- balayage -----------------------------------------------------------

    def _scan(self, d: _Node) -> None:
        if d.adjxy:
            sens = d.adjdir.pop()
            xy = d.adjxy.pop()
            l = d.adjl.pop()
            horiz = sens == "H"
            mult = 1 if horiz else GRIDMAX
            while l:
                self._place(d, xy + self.lofs[l] * mult, self.lw[l], horiz)
                l = self.lnext[l]
            return

        if d.numword > self.solution.numword:
            self.solution = d.copie()

        grid, attr = d.grid, d.attr
        xy2level, links1, lofs, lw, lnext = (
            self.xy2level, self.links1, self.lofs, self.lw, self.lnext)
        level = d.firstlevel
        while level <= d.lastlevel and level <= GRIDMAX * 2 - 4:
            # Mots « serrés »
            hasplace = 0
            xy = self.level2xy[level]
            while not attr[xy] & BORDER:
                if attr[xy] & TODOH:
                    l = links1[grid[xy]]
                    while l:
                        tst = xy + lofs[l]
                        if tst >= 0 and xy2level[tst] == d.firstlevel:
                            hasplace += self._place(d, tst, lw[l], True)
                        l = lnext[l]
                if attr[xy] & TODOV:
                    l = links1[grid[xy]]
                    while l:
                        tst = xy + lofs[l] * GRIDMAX
                        if tst >= 0 and xy2level[tst] == d.firstlevel:
                            hasplace += self._place(d, tst, lw[l], False)
                        l = lnext[l]
                if hasplace:
                    return
                xy += GRIDMAX - 1

            # Mots « adjacents »
            hasplace = 0
            xy = self.level2xy[level]
            while not attr[xy] & BORDER:
                if attr[xy] & TODOH:
                    l = links1[grid[xy]]
                    while l:
                        tst = xy + lofs[l]
                        if tst >= 0 and grid[tst] == STAR:
                            hasplace += self._place(d, tst, lw[l], True)
                        l = lnext[l]
                if attr[xy] & TODOV:
                    l = links1[grid[xy]]
                    while l:
                        tst = xy + lofs[l] * GRIDMAX
                        if tst >= 0 and grid[tst] == STAR:
                            hasplace += self._place(d, tst, lw[l], False)
                        l = lnext[l]
                if hasplace:
                    return
                xy += GRIDMAX - 1

            # Fragments de mots (un seul, s'il vous plaît)
            hasplace = 0
            hasfree = False
            xy = self.level2xy[level]
            while not attr[xy] & BORDER:
                if grid[xy] == FREE:
                    hasfree = True
                if attr[xy] & TODOH:
                    cnt = 0
                    l = links1[grid[xy]]
                    while l:
                        tst = xy + lofs[l]
                        if tst >= 0 and grid[tst] != STAR:
                            cnt += self._place(d, tst, lw[l], True)
                        if cnt:
                            break
                        l = lnext[l]
                    if cnt == 0:
                        attr[xy] &= ~TODOH
                        grid[xy - 1] = STAR
                        grid[xy + 1] = STAR
                    hasplace += cnt
                if attr[xy] & TODOV:
                    cnt = 0
                    l = links1[grid[xy]]
                    while l:
                        tst = xy + lofs[l] * GRIDMAX
                        if tst >= 0 and grid[tst] != STAR:
                            cnt += self._place(d, tst, lw[l], False)
                        if cnt:
                            break
                        l = lnext[l]
                    if cnt == 0:
                        attr[xy] &= ~TODOV
                        grid[xy - GRIDMAX] = STAR
                        grid[xy + GRIDMAX] = STAR
                    hasplace += cnt
                if hasplace:
                    return
                xy += GRIDMAX - 1

            if not hasfree:
                d.firstlevel = level + 1
            level += 1

    def resous(self) -> _Node:
        d = _noeud_vide()
        for i in range(_N):
            d.grid[i] = STAR
            d.attr[i] = BORDER
        for y in range(1, GRIDMAX - 1):
            for x in range(1, GRIDMAX - 1):
                d.grid[x + y * GRIDMAX] = FREE
                d.attr[x + y * GRIDMAX] = 0
        for w in range(self.numword - 1, -1, -1):
            d.firstlevel = 2
            self._place(d, GRIDMAX, w, True)

        try:
            while True:
                self.realnumnode = self.numnode = 0
                todo = []
                for i in range(SCOREMAX - 1, -1, -1):
                    if self.scores[i]:
                        todo.extend(self.scores[i])
                        self.scores[i] = []
                for d in todo:
                    if d.adjxy or self.numnode < NODEMAX:
                        self._scan(d)
                if time.monotonic() > self.echeance:
                    raise _Temps
                if self.realnumnode == 0:
                    break
        except _Temps:
            pass
        return self.solution


def _lire_mots(texte: str) -> list[bytes] | None:
    """`load_words` : un mot par ligne, lu tant que les caractères sont des
    lettres ; entouré de deux `STAR`. `None` quand le C s'arrête sans rien
    écrire (mot trop long, trop de mots)."""
    mots: list[bytes] = []
    for ligne in texte.split("\n"):
        ligne = ligne[:79]
        lettres = []
        for ch in ligne:
            if not ("a" <= ch <= "z" or "A" <= ch <= "Z"):
                break
            lettres.append(ord(ch.lower()) - (ord("a") - 1))
        mot = bytes([STAR, *lettres, STAR])
        if len(mot) > WORDLENMAX - 2:
            return None
        if len(mot) > 2:
            if len(mots) == WORDMAX - 1:
                return None
            mots.append(mot)
    return mots


def _dump(d: _Node) -> str:
    grid = d.grid
    sizex = sizey = 0
    for y in range(1, GRIDMAX):
        for x in range(1, GRIDMAX):
            if _ischar(grid[x + y * GRIDMAX]) and x > sizex:
                sizex = x
    for x in range(1, GRIDMAX - 1):
        for y in range(1, GRIDMAX - 1):
            if _ischar(grid[x + y * GRIDMAX]) and y > sizey:
                sizey = y
    lignes = []
    for y in range(1, sizey + 1):
        out = []
        for x in range(1, sizex + 1):
            c = grid[x + y * GRIDMAX]
            if not _ischar(c):
                if x < sizex:
                    out.append(",")
            else:
                out.append(chr(c + ord("a") - 1))
                if x < sizex:
                    out.append(",")
        lignes.append("".join(out))
    return "\n".join(lignes) + ("\n" if lignes else "")


def crossword(texte: str) -> str:
    """La grille que `crossword <fichier>` écrirait pour ce contenu."""
    mots = _lire_mots(texte)
    if mots is None:
        return ""
    return _dump(_Jigsaw(mots).resous())


# -- la grille posée devant l'élève (`anstype/crossword.input`) --------------

def _sans_accent(s: str) -> str:
    import unicodedata  # noqa: PLC0415

    return "".join(
        c for c in unicodedata.normalize("NFKD", s) if not unicodedata.combining(c)
    )


def meme_texte(a: str, b: str) -> bool:
    """`issametext` (`compare.c`) : sans accents, sans casse, sans blancs
    autour."""
    return _sans_accent(a.strip()).lower() == _sans_accent(b.strip()).lower()


def lire_grille(bloc: str) -> list[list[str]]:
    """La grille d'un `replygood` : une ligne par rangée, une case par item,
    `""` pour un noir — complétée à la largeur de la plus longue rangée."""
    lignes = [l for l in bloc.replace("\t", "\n").split("\n")]
    while lignes and not lignes[-1].strip():
        lignes.pop()
    rangees = [[c.strip() for c in l.split(",")] for l in lignes]
    largeur = max((len(r) for r in rangees), default=0)
    return [r + [""] * (largeur - len(r)) for r in rangees]


def separer_attendu(good: str) -> tuple[str, str]:
    """`[grille],[mot,définition ⏎ …]` → les deux blocs, crochets ôtés."""
    import re  # noqa: PLC0415

    blocs = re.findall(r"\[(.*?)\]", good or "", re.DOTALL)
    grille = blocs[0] if blocs else ""
    defs = blocs[1] if len(blocs) > 1 else ""
    return grille, defs


def construire(good: str, transposer: bool, choisir) -> tuple[str, dict] | None:
    """La grille telle que `crossword.input` la dresse.

    Rend l'attendu réécrit (la grille, transposée si le tirage l'a voulu —
    `!set dir=!randint 2`) et la configuration du widget : le masque des
    cases, leurs numéros, les définitions horizontales et verticales. Le
    masque ne dit rien des lettres ; elles restent dans l'attendu, que le
    navigateur ne reçoit pas.

    `choisir(options)` tranche les `{a,b}` des définitions
    (`!embraced randitem`).
    """
    import re  # noqa: PLC0415

    bloc, defs_bruts = separer_attendu(good)
    grille = lire_grille(bloc)
    if not grille or not any(c for r in grille for c in r):
        return None
    if transposer:
        grille = [list(col) for col in zip(*grille)]
    nl, nc = len(grille), len(grille[0])

    def case(k: int, j: int) -> str:
        return grille[k][j] if 0 <= k < nl and 0 <= j < nc else ""

    # Les `{a,b}` des définitions : une variante tirée.
    defs_bruts = re.sub(
        r"\{([^{}]*)\}", lambda m: choisir(m.group(1).split(",")).strip(), defs_bruts
    )
    definitions = []
    for ligne in defs_bruts.replace("\t", "\n").split("\n"):
        mot, _, texte = ligne.partition(",")
        if mot.strip():
            definitions.append((mot.strip(), texte.strip()))

    def definition(mot: str) -> str:
        for m, t in definitions:
            if meme_texte(m, mot):
                return t
        return ""

    numeros = [[0] * nc for _ in range(nl)]
    vu_h: set[tuple[int, int]] = set()
    vu_v: set[tuple[int, int]] = set()
    horiz: list[list] = []
    vert: list[list] = []
    cnt = 0
    for k in range(nl):
        for j in range(nc):
            if not case(k, j) or (case(k, j - 1) and case(k - 1, j)):
                continue
            long_h = long_v = 0
            mot_h = mot_v = ""
            if (k, j) not in vu_h:
                jj = j
                while case(k, jj):
                    mot_h += case(k, jj)
                    vu_h.add((k, jj))
                    jj += 1
                long_h = jj - j
            if (k, j) not in vu_v:
                kk = k
                while case(kk, j):
                    mot_v += case(kk, j)
                    vu_v.add((kk, j))
                    kk += 1
                long_v = kk - k
            if long_h > 1 or long_v > 1:
                cnt += 1
                numeros[k][j] = cnt
                # `!replace internal : by ,` — les deux-points d'une définition
                # deviennent des virgules à l'affichage, chez WIMS aussi.
                if long_h > 1:
                    horiz.append([cnt, definition(mot_h).replace(":", ",")])
                if long_v > 1:
                    vert.append([cnt, definition(mot_v).replace(":", ",")])

    cases = [
        [(numeros[k][j] if grille[k][j] else -1) for j in range(nc)]
        for k in range(nl)
    ]
    attendu = "[" + "\n".join(",".join(r) for r in grille) + "],[" + defs_bruts + "]"
    return attendu, {"rows": nl, "cols": nc, "cells": cases,
                     "horizontal": horiz, "vertical": vert}


def noter(reponse: str, attendu: str) -> float:
    """La part des cases justes (`anstype/crossword`) : chaque case pleine de
    la grille contre la lettre de même rang dans la réponse, par
    `issametext`."""
    grille = lire_grille(separer_attendu(attendu)[0])
    rep = [l.split(",") for l in (reponse or "").replace(";", "\n").split("\n")]
    total = justes = 0
    for k, rangee in enumerate(grille):
        for j, lettre in enumerate(rangee):
            if not lettre:
                continue
            total += 1
            donnee = rep[k][j] if k < len(rep) and j < len(rep[k]) else ""
            if donnee.strip() and meme_texte(lettre, donnee):
                justes += 1
    return justes / total if total else 0.0


def reponse_de(attendu: str) -> str:
    """La grille attendue sous la forme où le widget l'envoie (`sendanswer()`
    de `crossword.input`) : une rangée par ligne, chaque case suivie d'une
    virgule. C'est ce que « Réponse auto » doit poser — l'attendu brut
    `[grille],[définitions]` n'est pas une réponse."""
    grille = lire_grille(separer_attendu(attendu)[0])
    return "\n".join("".join(c + "," for c in r) for r in grille)
