"""Primitives de découpage de listes WIMS — port fidèle du source C.

Socle unique pour tout ce qui découpe une valeur WIMS en items, lignes ou
lignes-de-matrice. Chaque fonction porte en docstring la référence de son
original ; toute divergence doit être justifiée ici et nulle part ailleurs.

**L'axiome à retenir : la tabulation n'est jamais un séparateur.** Aucune
primitive de `liblines.c` ne la mentionne. Les tabulations que portent les
`.def` encodent les retours à la ligne du source OEF — ce sont les fichiers de
WIMS lui-même, qui les exécute tels quels — et ne sont donc que des blancs
ordinaires : conservées à l'intérieur d'un item, élaguées à ses bords.

**Ces primitives ignorent la langue, et c'est volontaire.** PAX suit la
convention locale pour le séparateur décimal et le séparateur de liste — en
français `3,93` et `2;5`, cf. `core/oef/i18n.py`. Cette convention vit
**uniquement aux frontières** : à l'affichage (`!texmath`, seul appelant
interne de `list_separator` ; `localizeChoiceDisplay` côté front) et à la
saisie (`normalize_decimal_reply`, les checkers numériques). Les valeurs qui
circulent dans le moteur restent, elles, dans la convention WIMS : items
séparés par des virgules, lignes de matrice par des points-virgules, quelle
que soit la langue de l'exercice. Rendre ces primitives sensibles à la locale
casserait tous les `.def` d'un coup.

Attention au `;`, qui porte **trois** sens distincts :

1. séparateur de lignes de matrice (`rows2lines`) — le seul que ce module
   connaisse ;
2. séparateur de liste **affiché** en locale à virgule (`i18n.list_separator`)
   — jamais réinjecté dans le moteur ;
3. sous-produit de l'idiome `!append item` + `!translate \\t to ;`, quand un
   item contient lui-même une virgule (les QCM de `brevet01`) — c'est de la
   donnée, pas une convention.

Voir `docs/refactor-item-splitting.md` pour l'analyse complète et le programme
de migration des appelants.
"""

import re
from functools import lru_cache

# `myisspace` (`libwims.h:230`) — volontairement plus étroit que `str.isspace`,
# qui accepte aussi \v, \f et les espaces Unicode.
_SPACE = " \t\n\r"

_OPENERS = {"(": ")", "[": "]", "{": "}"}
_BRACKETS = re.compile(r"[\[\](){}]")


def _is_space(ch: str) -> bool:
    return ch in _SPACE


def find_word_start(s: str, start: int = 0) -> int:
    """Index du premier non-blanc à partir de `start` (`liblines.c`)."""
    i = start
    while i < len(s) and _is_space(s[i]):
        i += 1
    return i


def find_word_end(s: str, start: int = 0) -> int:
    """Index du premier blanc à partir de `start` (`liblines.c`)."""
    i = start
    while i < len(s) and not _is_space(s[i]):
        i += 1
    return i


def find_matching(s: str, start: int, close: str) -> int:
    """Index du `close` appariant l'ouvrant qui précède `start`, ou -1.

    Port de `find_matching` (`liblines.c`). `start` pointe **après** l'ouvrant.

    Le point à ne pas simplifier : les trois compteurs `()`, `[]`, `{}` sont
    tenus **simultanément**, et le premier à passer sous zéro décide. Si le
    fermant rencontré n'est pas celui qu'on cherche, ou si un autre compteur
    reste positif, l'appariement échoue — `[a)b]` n'a pas de `]` appariant.
    """
    parenth = brak = brace = 0
    n = len(s)
    i = n
    # Seuls les crochets comptent : on saute de l'un à l'autre plutôt que
    # d'examiner chaque caractère — la boucle Python était le coût dominant
    # des listes indexées dans un `!for` (`Infra-rouge*`).
    for m in _BRACKETS.finditer(s, start):
        ch = m.group()
        if ch == "[":
            brak += 1
        elif ch == "]":
            brak -= 1
        elif ch == "(":
            parenth += 1
        elif ch == ")":
            parenth -= 1
        elif ch == "{":
            brace += 1
        else:
            brace -= 1
        if parenth < 0 or brak < 0 or brace < 0:
            if ch != close or parenth > 0 or brak > 0 or brace > 0:
                return -1
            i = m.start()
            break
    if i >= n or s[i] != close:
        return -1
    return i


def strparstr(s: str, sep: str, start: int = 0) -> int:
    """Index du prochain `sep` à profondeur zéro, ou `len(s)`.

    Port de `strparstr` (`liblines.c`). Les paires `()`/`[]`/`{}` sont sautées.

    Le repli est aussi important que la règle : sur un ouvrant **non apparié**,
    WIMS abandonne la protection et retombe sur une recherche naïve *depuis le
    début du balayage* — et si elle échoue, sur la fin de chaîne. C'est ce qui
    fait qu'une valeur aux crochets déséquilibrés se découpe quand même.
    """
    n = len(s)
    if not sep:
        return min(start, n)
    stops = _stops(sep[0])
    i = start
    while i < n:
        # Saut au prochain caractère qui peut compter : début de `sep`, ou
        # ouvrant. Les autres ne font qu'avancer d'un cran dans le C.
        m = stops.search(s, i)
        if m is None:
            return n
        i = m.start()
        if s.startswith(sep, i):
            return i
        close = _OPENERS.get(s[i])
        if close is not None:
            j = find_matching(s, i + 1, close)
            if j < 0:
                k = s.find(sep, start)
                return k if k >= 0 else n
            i = j
        i += 1
    return n


@lru_cache(maxsize=16)
def _stops(first: str) -> re.Pattern:
    return re.compile("[" + re.escape(first + "([{") + "]")


# ── Items ────────────────────────────────────────────────────────────────────


def find_item_end(s: str, start: int = 0) -> int:
    """Fin de l'item courant : `strparstr(p, ",")` (`liblines.c`).

    C'est l'**unique** définition d'une frontière d'item dans WIMS.
    """
    return strparstr(s, ",", start)


@lru_cache(maxsize=256)
def _item_bounds(s: str) -> tuple[tuple[int, int], ...]:
    """Bornes brutes (début, fin) de chaque item, séparateurs exclus.

    Mémorisée : `$(liste[$i])` dans un `!for` redécoupait la liste entière à
    chaque tour — WIMS le fait aussi (`fnd_item` rebalaie depuis le début),
    mais en C. `Infra-rouge1|3|5` indexaient ainsi 2 800 fois une liste de
    260 items et butaient sur le budget de rendu. Fonction pure de la chaîne,
    d'où un tuple : un appelant ne peut pas altérer ce qu'il partage.
    """
    if not s:
        return ()
    bounds = []
    i = 0
    n = len(s)
    while True:
        end = find_item_end(s, i)
        bounds.append((i, end))
        if end >= n:
            return tuple(bounds)
        i = end + 1


def itemnum(s: str) -> int:
    """Nombre d'items (`itemnum`, `liblines.c`).

    Une chaîne vide en compte 0 ; au-delà, **les items vides comptent** —
    `a,,b` en vaut 3 et `a,` en vaut 2. `!nonempty items` n'existerait pas si
    `itemcnt` les ignorait de lui-même.
    """
    return len(_item_bounds(s))


def fnd_item(s: str, n: int) -> str:
    """N-ième item, 1-indexé, **élagué de ses blancs de bord** (`fnd_item`).

    L'intérieur n'est pas touché : une tabulation au milieu d'un item y reste,
    et c'est ce qui permet à une commande flydraw multi-instructions de
    traverser une liste intacte. Hors bornes → chaîne vide.
    """
    bounds = _item_bounds(s)
    if not 1 <= n <= len(bounds):
        return ""
    a, b = bounds[n - 1]
    a = find_word_start(s, a)
    while b > a and _is_space(s[b - 1]):
        b -= 1
    return s[a:b]


def cutitems(s: str) -> list[str]:
    """Tous les items, élagués — l'énumération de `fnd_item(1..itemnum)`.

    Une nuance à connaître : le `cutitems` du C (`_cutit_(…, tag=3)`) s'arrête
    sur `*pp`, donc **abandonne un dernier item vide** — `"a,"` lui vaut un
    item quand `itemnum` en compte deux. La paire `itemnum`/`fnd_item`, elle,
    en voit bien deux, et c'est elle que modélisent les appelants de PAX
    (`!item`, `$(var[n])`, `!itemcnt`). Les appelants du `cutitems` C
    (`!distribute`, `!listuniq`, `!nonempty`) sont insensibles à la nuance :
    ils écartent les items vides ou complètent par des chaînes vides.
    """
    return list(_cutitems(s))


@lru_cache(maxsize=256)
def _cutitems(s: str) -> tuple[str, ...]:
    """Le découpage élagué, mémorisé comme `_item_bounds` et pour la même
    raison. `cutitems` en rend une copie : ses appelants mélangent ou trient
    parfois la liste reçue sur place."""
    out = []
    for a, b in _item_bounds(s):
        a2 = find_word_start(s, a)
        b2 = b
        while b2 > a2 and _is_space(s[b2 - 1]):
            b2 -= 1
        out.append(s[a2:b2])
    return tuple(out)


def itemchr(haystack: str, needle: str) -> bool:
    """`needle` est-il un item de `haystack` ? (`itemchr`, `liblines.c`)

    Ce n'est **pas** une égalité item à item : WIMS cherche la sous-chaîne puis
    vérifie ses frontières — début-de-chaîne ou virgule avant (blancs ignorés),
    fin-de-chaîne ou virgule après. Il n'y a donc aucune protection de
    crochets : `a` n'est pas un item de `[a,b]`, son voisin de gauche étant
    `[`. C'est la même règle qui sert au dédoublonnage de `listuniq` et à
    l'opérateur `isitemof`.
    """
    if not needle:
        return False
    n = len(needle)
    pos = haystack.find(needle)
    while pos >= 0:
        left = pos - 1
        while left >= 0 and _is_space(haystack[left]):
            left -= 1
        right = find_word_start(haystack, pos + n)
        before_ok = left < 0 or haystack[left] == ","
        after_ok = right >= len(haystack) or haystack[right] == ","
        if before_ok and after_ok:
            return True
        pos = haystack.find(needle, pos + 1)
    return False


# ── Lignes ───────────────────────────────────────────────────────────────────


def linenum(s: str) -> int:
    """Nombre de lignes (`linenum`, `liblines.c`).

    Deux asymétries à respecter : un `\\n` **final** ne crée pas de ligne
    supplémentaire, mais un `\\n` **initial** en crée bien une (vide).
    """
    if s.endswith("\n") and len(s) > 1:
        s = s[:-1]
    if not s:
        return 0
    return s.count("\n") + 1


def fnd_line(s: str, n: int) -> str:
    """N-ième ligne, 1-indexée, **sans élagage** (`fnd_line`, `liblines.c`)."""
    if s.endswith("\n") and len(s) > 1:
        s = s[:-1]
    if not s:
        return ""
    lines = s.split("\n")
    return lines[n - 1] if 1 <= n <= len(lines) else ""


def cutlines(s: str) -> list[str]:
    """Toutes les lignes, sans élagage."""
    return [fnd_line(s, i) for i in range(1, linenum(s) + 1)]


# ── Lignes de matrice ────────────────────────────────────────────────────────


def rows2lines(s: str) -> tuple[str, int]:
    """`;` de profondeur zéro → `\\n`. Renvoie (résultat, nb de conversions).

    Port de `rows2lines` (`liblines.c`). Trois subtilités :

    - la présence d'un `\\n` **suffit à ne rien faire** (la valeur est déjà en
      lignes) ;
    - un `;` fermant une entité HTML n'est pas un séparateur (`&alpha;` sur au
      plus 14 lettres, `&#nnn;` sur au plus 6 chiffres) ;
    - le compte renvoyé sert aux appelants : à zéro, `!nonempty rows` bascule
      sur les lignes.
    """
    if "\n" in s:
        return s, 0
    out = list(s)
    count = 0
    i = 0
    n = len(s)
    while i < n:
        ch = s[i]
        close = _OPENERS.get(ch)
        if close is not None:
            j = find_matching(s, i + 1, close)
            if j >= 0:
                i = j + 1
                continue
            i += 1
            continue
        if ch == ";":
            out[i] = "\n"
            count += 1
            i += 1
            continue
        if ch == "&" and i + 1 < n and s[i + 1].isalpha():
            j = i + 1
            while j < n and s[j].isalpha() and j - i < 14:
                j += 1
            i = j + 1
            continue
        if ch == "&" and i + 1 < n and s[i + 1] == "#":
            j = i + 2
            while j < n and s[j].isdigit() and j - i < 6:
                j += 1
            i = j + 1
            continue
        i += 1
    return "".join(out), count


def lines2rows(s: str) -> str:
    """Chaque `\\n` → `;`, sans protection (`lines2rows`, `liblines.c`)."""
    return s.rstrip(" \t\n\r").replace("\n", ";")


def cutrows(s: str) -> list[str]:
    """Lignes de matrice : `rows2lines` puis découpage en lignes."""
    converted, _ = rows2lines(s)
    return cutlines(converted)


# ── Découpage à profondeur zéro, et `!declosing` ─────────────────────────────
#
# Ces deux primitives existaient en **sept** exemplaires dans le moteur et les
# checkers — trois `_split_top_level`, un `_split_top_level_args`, trois
# `declosing` — et pas tous du même avis. Les découpeurs divergeaient sur une
# parenthèse fermante orpheline ; les `declosing`, sur une paire non
# équilibrée : `[a],[b]` était mutilé en `a],[b` par l'un, `(a]` accepté par
# l'autre, quand seul celui du moteur vérifiait que le premier ouvrant se ferme
# bien au dernier caractère. Une seule version, ici, et la bonne.


def split_top_level(s: str, sep: str) -> list[str]:
    """Découpe `s` aux `sep` situés hors de toute paire `()`, `[]`, `{}`.

    Construit sur `strparstr`, donc avec le repli de WIMS sur un ouvrant non
    apparié : la protection est abandonnée et la recherche redevient naïve.
    Aucun `strip` — ce que le C ne fait pas, on ne le fait pas non plus.
    """
    parts: list[str] = []
    start = 0
    n = len(s)
    while True:
        i = strparstr(s, sep, start)
        if i >= n:
            parts.append(s[start:])
            return parts
        parts.append(s[start:i])
        start = i + len(sep)


def split_top_level_args(s: str) -> list[str]:
    """Une liste d'arguments séparés par des virgules, chacun élagué."""
    return [p.strip() for p in split_top_level(s, ",")]


def declosing(s: str) -> str:
    """`!declosing` — retire **une** paire englobante de `()`, `[]` ou `{}`.

    Uniquement si toute la chaîne est enclose dans une paire équilibrée : le
    premier ouvrant doit s'apparier au dernier caractère. Sinon `[a,b],[c,d]`
    verrait ses deux listes fusionnées à tort (dataproc).
    """
    s = (s or "").strip()
    for open_, close_ in (("(", ")"), ("[", "]"), ("{", "}")):
        if s.startswith(open_) and s.endswith(close_):
            depth = 0
            for j, ch in enumerate(s):
                if ch == open_:
                    depth += 1
                elif ch == close_:
                    depth -= 1
                    if depth == 0:
                        if j != len(s) - 1:
                            return s
                        break
            return s[1:-1].strip()
    return s


# ── Remplacement d'objet (`_obj_replace`, `calc.c:883`) ──────────────────────
#
# `!replace <style> [number <n>] <quoi> by <par> in <texte>` : quatre styles —
# `word`, `item`, `line`, `char` —, chacun avec ou sans `number`. Sans
# `number`, ce sont les **occurrences** de l'objet `quoi` qui sont remplacées,
# frontières comprises (`itemchr`, `wordchr`…) ; avec, c'est le n-ième objet,
# compté de 1, ou depuis la fin s'il est négatif.

_SEPARATEURS = {"word": " ", "item": ",", "line": "\n", "char": ""}


def _debuts(s: str, style: str) -> list[int]:
    """Début brut de chaque objet — ce que le C laisse dans `fnd_position`.

    Pour un item, c'est la position **juste après la virgule précédente**,
    blancs de tête compris : `fnd_item` pose `fnd_position` avant son
    `find_word_start`. Pour un mot, au contraire, c'est le mot lui-même.
    """
    if style == "item":
        return [a for a, _ in _item_bounds(s)]
    if style == "line":
        return [0] + [i + 1 for i, ch in enumerate(s) if ch == "\n" and i + 1 <= len(s)]
    if style == "char":
        return list(range(len(s)))
    debuts = []
    i = find_word_start(s)
    while i < len(s):
        debuts.append(i)
        i = find_word_start(s, find_word_end(s, i))
    return debuts


def objnum(s: str, style: str) -> int:
    if style == "item":
        return itemnum(s)
    if style == "line":
        return linenum(s)
    if style == "char":
        return len(s)
    return len(_debuts(s, "word"))


def objchr(s: str, mot: str, depuis: int = 0) -> int:
    """Position de la première occurrence **d'un item entier** (`itemchr`)."""
    if not mot:
        return -1
    n = len(mot)
    pos = s.find(mot, depuis)
    while pos >= 0:
        gauche = pos - 1
        while gauche >= 0 and _is_space(s[gauche]):
            gauche -= 1
        droite = find_word_start(s, pos + n)
        if (gauche < 0 or s[gauche] == ",") and (droite >= len(s) or s[droite] == ","):
            return pos
        pos = s.find(mot, pos + 1)
    return -1


def wordchr(s: str, mot: str, depuis: int = 0) -> int:
    """`wordchr` : l'occurrence doit être bordée de blancs ou de bouts."""
    if not mot:
        return -1
    n = len(mot)
    pos = s.find(mot, depuis)
    while pos >= 0:
        avant_ok = pos == 0 or _is_space(s[pos - 1])
        apres = pos + n
        apres_ok = apres >= len(s) or _is_space(s[apres])
        if avant_ok and apres_ok:
            return pos
        pos = s.find(mot, pos + 1)
    return -1


def linechr(s: str, mot: str, depuis: int = 0) -> int:
    if not mot:
        return -1
    n = len(mot)
    pos = s.find(mot, depuis)
    while pos >= 0:
        avant_ok = pos == 0 or s[pos - 1] == "\n"
        apres = pos + n
        apres_ok = apres >= len(s) or s[apres] == "\n"
        if avant_ok and apres_ok:
            return pos
        pos = s.find(mot, pos + 1)
    return -1


def replace_objet(
    quoi: str, par: str, texte: str, style: str, numero: int | None = None
) -> str:
    """Port de `_obj_replace` (`calc.c:883`).

    `numero` None → remplacement par occurrences ; sinon le n-ième objet.
    Un `numero` nul, ou hors bornes, laisse le texte intact — le C lève
    `bad_index` pour le premier, que PAX ne peut pas signaler à l'élève.
    """
    if style not in _SEPARATEURS:
        return texte
    sep = _SEPARATEURS[style]
    if numero is not None:
        total = objnum(texte, style)
        i = numero
        if i == 0:
            return texte
        if i < 0:
            i = total + i + 1
        if i > total or i < 1:
            return texte
        if style == "char":
            if not par:
                return texte
            return texte[: i - 1] + par[0] + texte[i:]
        debuts = _debuts(texte, style)
        p1 = debuts[i - 1]
        p2 = debuts[i] if i < total else len(texte)
        return texte[:p1] + par + (sep if i < total else "") + texte[p2:]

    if style == "char":
        if not quoi or not par:
            return texte
        return texte.replace(quoi[0], par[0])
    if not quoi and not par:
        return texte
    chercheur = {"item": objchr, "word": wordchr, "line": linechr}[style]
    out = texte
    pos = chercheur(out, quoi)
    while pos >= 0:
        out = out[:pos] + par + out[pos + len(quoi) :]
        # Le C repart de `p1+strlen(by)+1` : un remplacement ne peut pas être
        # relu comme une occurrence, et la frontière qui suit est sautée.
        pos = chercheur(out, quoi, pos + len(par) + 1)
    return out
