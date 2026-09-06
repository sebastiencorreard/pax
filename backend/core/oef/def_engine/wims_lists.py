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

# `myisspace` (`libwims.h:230`) — volontairement plus étroit que `str.isspace`,
# qui accepte aussi \v, \f et les espaces Unicode.
_SPACE = " \t\n\r"

_OPENERS = {"(": ")", "[": "]", "{": "}"}


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
    i = start
    n = len(s)
    while i < n:
        ch = s[i]
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
        elif ch == "}":
            brace -= 1
        else:
            i += 1
            continue
        if parenth < 0 or brak < 0 or brace < 0:
            if ch != close or parenth > 0 or brak > 0 or brace > 0:
                return -1
            break
        i += 1
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
    i = start
    while i < n:
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


# ── Items ────────────────────────────────────────────────────────────────────


def find_item_end(s: str, start: int = 0) -> int:
    """Fin de l'item courant : `strparstr(p, ",")` (`liblines.c`).

    C'est l'**unique** définition d'une frontière d'item dans WIMS.
    """
    return strparstr(s, ",", start)


def _item_bounds(s: str) -> list[tuple[int, int]]:
    """Bornes brutes (début, fin) de chaque item, séparateurs exclus."""
    if not s:
        return []
    bounds = []
    i = 0
    n = len(s)
    while True:
        end = find_item_end(s, i)
        bounds.append((i, end))
        if end >= n:
            return bounds
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
    out = []
    for a, b in _item_bounds(s):
        a2 = find_word_start(s, a)
        b2 = b
        while b2 > a2 and _is_space(s[b2 - 1]):
            b2 -= 1
        out.append(s[a2:b2])
    return out


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
