"""Lecture d'un GIF indexé, pour les zones cliquables de WIMS.

`anstype/click` interroge `Misc/clickzone.c`, qui décide de l'appartenance d'un
clic à une région en **remplissant** l'image par diffusion depuis le point
cliqué, puis en regardant si le point de référence de la zone a été atteint.
Les cartes du corpus (`dept.gif`, `region.gif` d'`oefdepregfr`) sont des GIF de
512×450 à quatre couleurs : le tracé y sépare les départements, et deux points
d'un même département communiquent sans franchir de trait.

Le décodage tient en un en-tête, une palette et une décompression LZW ; PAX
n'appelle aucun binaire et n'a pas de bibliothèque d'images, dans la même ligne
que l'émulation de Maxima, de PARI et de `chemeq`. Le périmètre est celui du
corpus : GIF87a/89a, palette globale ou locale, entrelacement compris, **une
seule image** — l'animation ne servirait à rien ici, seule la première trame
porte le tracé.

`backend/tests/test_gif.py` confronte la sortie au binaire `clickzone` du
dépôt, qui sert d'oracle comme le fait `chemeq` pour la chimie.
"""

from __future__ import annotations

import struct
from collections import deque


class GifError(ValueError):
    """Fichier illisible — l'appelant renonce au test de zone plutôt que de
    conclure sur une image qu'il n'a pas su lire."""


def _decompresser_lzw(donnees: bytes, taille_min: int, attendu: int) -> list[int]:
    """LZW de GIF : codes de longueur variable, dictionnaire remis à zéro sur
    le code `clear`.

    Il diffère du LZW de TIFF ou de `compress` par l'ordre des bits — les codes
    se lisent du **bit de poids faible** vers le fort, à travers les octets.
    """
    clear = 1 << taille_min
    fin = clear + 1
    dictionnaire: list[list[int]] = []
    sortie: list[int] = []

    def reinitialiser() -> None:
        nonlocal dictionnaire, taille_code, suivant
        dictionnaire = [[i] for i in range(clear)] + [[], []]
        taille_code = taille_min + 1
        suivant = fin + 1

    taille_code = taille_min + 1
    suivant = fin + 1
    reinitialiser()

    precedent: list[int] | None = None
    accumulateur = 0
    bits = 0
    for octet in donnees:
        accumulateur |= octet << bits
        bits += 8
        while bits >= taille_code:
            code = accumulateur & ((1 << taille_code) - 1)
            accumulateur >>= taille_code
            bits -= taille_code
            if code == clear:
                reinitialiser()
                precedent = None
                continue
            if code == fin:
                return sortie
            if code < len(dictionnaire) and (dictionnaire[code] or code < clear):
                entree = dictionnaire[code]
            elif precedent is not None:
                # Le cas « KwKwK » : un code qui se réfère à l'entrée qu'il est
                # justement en train de définir.
                entree = precedent + precedent[:1]
            else:
                raise GifError("code LZW invalide")
            sortie += entree
            if precedent is not None and suivant < 4096:
                dictionnaire.append(precedent + entree[:1])
                suivant += 1
                if suivant == (1 << taille_code) and taille_code < 12:
                    taille_code += 1
            precedent = entree
            if len(sortie) >= attendu:
                return sortie
    return sortie


def _lire_sous_blocs(donnees: bytes, i: int) -> tuple[bytes, int]:
    """Les données GIF viennent en sous-blocs préfixés de leur longueur, la
    suite s'arrêtant sur un bloc vide."""
    morceaux = []
    while i < len(donnees):
        n = donnees[i]
        i += 1
        if n == 0:
            break
        morceaux.append(donnees[i : i + n])
        i += n
    return b"".join(morceaux), i


def _desentrelacer(lignes: list[list[int]], hauteur: int) -> list[list[int]]:
    """Un GIF entrelacé range ses lignes en quatre passes (1/8, 1/8 décalé,
    1/4, 1/2) ; on les remet dans l'ordre."""
    ordre: list[int] = []
    for depart, pas in ((0, 8), (4, 8), (2, 4), (1, 2)):
        ordre += list(range(depart, hauteur, pas))
    remis: list[list[int]] = [[]] * hauteur
    for source, cible in enumerate(ordre):
        remis[cible] = lignes[source]
    return remis


class ImageIndexee:
    """Une trame GIF : ses dimensions et l'index de palette de chaque pixel."""

    __slots__ = ("largeur", "hauteur", "pixels")

    def __init__(self, largeur: int, hauteur: int, pixels: list[int]):
        self.largeur = largeur
        self.hauteur = hauteur
        self.pixels = pixels

    def pixel(self, x: int, y: int) -> int | None:
        """Index de palette, ou None hors de l'image — `gdImageGetPixel` rend
        aussi une valeur hors sujet dans ce cas, mais l'appelant a besoin de
        distinguer les deux."""
        if 0 <= x < self.largeur and 0 <= y < self.hauteur:
            return self.pixels[y * self.largeur + x]
        return None

    def region_atteint(self, depart: tuple[int, int], cible: tuple[int, int]) -> bool:
        """Vrai si `cible` appartient à la région 4-connexe de même couleur que
        `depart` — le `gdImageFill` de `clickzone.c`, dont on n'a besoin que du
        verdict, pas de l'image peinte.

        Le parcours s'arrête dès la cible atteinte ; sur les cartes du corpus,
        une région couvre au plus quelques dizaines de milliers de pixels.
        """
        cx, cy = depart
        couleur = self.pixel(cx, cy)
        if couleur is None or self.pixel(*cible) is None:
            return False
        if depart == cible:
            return True
        # Une cible d'une autre couleur ne sera jamais peinte : `gdImageFill`
        # ne déborde pas du domaine de couleur du point de départ.
        if self.pixel(*cible) != couleur:
            return False
        vus = bytearray(self.largeur * self.hauteur)
        file = deque([(cx, cy)])
        vus[cy * self.largeur + cx] = 1
        while file:
            x, y = file.popleft()
            for nx, ny in ((x - 1, y), (x + 1, y), (x, y - 1), (x, y + 1)):
                if not (0 <= nx < self.largeur and 0 <= ny < self.hauteur):
                    continue
                pos = ny * self.largeur + nx
                if vus[pos] or self.pixels[pos] != couleur:
                    continue
                if (nx, ny) == cible:
                    return True
                vus[pos] = 1
                file.append((nx, ny))
        return False


def lire_gif(chemin: str) -> ImageIndexee:
    """Première trame d'un fichier GIF, en index de palette."""
    with open(chemin, "rb") as f:
        donnees = f.read()
    if donnees[:6] not in (b"GIF87a", b"GIF89a"):
        raise GifError("signature GIF absente")
    largeur, hauteur, flags = struct.unpack("<HHB", donnees[6:11])
    i = 13
    if flags & 0x80:
        i += 3 * (1 << ((flags & 7) + 1))  # palette globale, dont on n'a pas
                                           # besoin : seuls les index comptent
    while i < len(donnees):
        bloc = donnees[i]
        i += 1
        if bloc == 0x3B:  # fin du fichier
            break
        if bloc == 0x21:  # extension : commentaire, graphique, texte…
            i += 1        # étiquette
            _, i = _lire_sous_blocs(donnees, i)
            continue
        if bloc != 0x2C:
            raise GifError(f"bloc GIF inattendu : {bloc:#x}")
        gauche, haut, l_img, h_img, drapeaux = struct.unpack("<HHHHB", donnees[i : i + 9])
        i += 9
        if drapeaux & 0x80:
            i += 3 * (1 << ((drapeaux & 7) + 1))  # palette locale
        taille_min = donnees[i]
        i += 1
        brut, i = _lire_sous_blocs(donnees, i)
        plat = _decompresser_lzw(brut, taille_min, l_img * h_img)
        if len(plat) < l_img * h_img:
            raise GifError("données d'image tronquées")
        lignes = [plat[y * l_img : (y + 1) * l_img] for y in range(h_img)]
        if drapeaux & 0x40:
            lignes = _desentrelacer(lignes, h_img)
        if (gauche, haut, l_img, h_img) == (0, 0, largeur, hauteur):
            return ImageIndexee(largeur, hauteur, [p for ligne in lignes for p in ligne])
        # Trame plus petite que l'écran logique : on la replace, le fond
        # restant à l'index 0 comme le fait `gd`.
        pixels = [0] * (largeur * hauteur)
        for y, ligne in enumerate(lignes):
            base = (haut + y) * largeur + gauche
            pixels[base : base + l_img] = ligne
        return ImageIndexee(largeur, hauteur, pixels)
    raise GifError("aucune image dans le fichier")
