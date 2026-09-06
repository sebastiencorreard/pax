"""
Engine for compiled WIMS .def script files.

Evaluates the variable section, renders the :question section (or the literal
question= text), extracts answer metadata, and returns an ExerciseRender.
"""

from __future__ import annotations

import datetime
import math
import os
import random
import re
import time
from functools import lru_cache


class _RenderBudgetExceeded(Exception):
    """Levée quand un rendu dépasse son budget temps (garde-fou contre une
    boucle emballée : slib incomplet, borne géante…). Rattrapée au niveau du
    rendu, qui poursuit avec l'état partiel calculé — un rendu approximatif vaut
    mieux qu'un rendu de plusieurs minutes."""


# Budget temps d'un rendu, en secondes. WIMS lui-même borne le temps d'exécution.
_RENDER_TIME_BUDGET = 8.0

# Longueur du tampon de ligne de WIMS (`wimsdef.h`), au-delà de laquelle ses
# fonctions de lecture coupent.
_MAX_LINELEN = 45000

# `\nextstep` ne dit jamais combien d'étapes restent : l'exercice s'arrête quand
# la variable devient vide. On rejoue donc `:postdef` jusqu'à cet arrêt, borné
# pour qu'un `.def` mal formé ne parte pas en boucle (le maximum observé sur le
# corpus est 6).
_MAX_NEXTSTEPS = 32

# Budget propre au rejeu de `\nextstep`, distinct de celui du rendu. Ce rejeu
# est une **heuristique** : il rejoue `:postdef` jusqu'à 31 fois pour deviner
# combien d'étapes viendront, et repart parfois les mains vides. Lui laisser le
# budget du rendu entier lui permettait d'y passer huit secondes pour n'en rien
# tirer — c'était le cas d'`oefstatistiques/histocap`, dont le rendu prenait
# 8,2 s dont 8,0 ici, pour finir sur `total=None`.
#
# Mesuré sur les 4278 exercices : neuf y passent plus de 0,3 s, un seul plus de
# 2 s (histocap, qui n'aboutit pas). Le plus lent qui **aboutit** tient en
# 0,34 s. Deux secondes laissent donc six fois la marge du pire cas utile.
_NEXTSTEP_TIME_BUDGET = 2.0

from .cas import (
    _MATH_NS,
    _PARI_HELPERS,
    _PYTHON_KEYWORDS,
    _call_maxima,
    _call_pari,
    _format_pari_result,
    _MAXIMA_TO_SYMPY,
    _rint,
    _split_top_level_args,
    _sympify_arg,
    _expr_to_latex,
)
from .presentation import (
    _close_inline_math,
    _normalize_math_content,
    _split_top_level,
    localize_decimals,
    wims_matrices_to_latex,
)
from .slib import _SlibExit, _SlibMixin
from ..numfmt import format_wims_float
from ..i18n import list_separator, uses_comma_decimal
from . import wims_lists as wl
from .wims_img import calc_imgrename
from ..def_parser import (
    Assign,
    Command,
    DefFile,
    ForLoop,
    WhileLoop,
    IfBlock,
    Insmath,
    Output,
    ReadDraw,
    ReadEmbed,
    ReadProc,
    ReadSpecial,
    parse as parse_def,
)
from ..engine import AnswerDef, ExerciseRender, _segment_statement, _embedded_widget_names

# Sous-modules extraits — re-exportés ici pour rétrocompatibilité des imports
# externes : `from core.oef.def_engine import check_analyze` continue de fonctionner.
from .compare import _wims_compare                                      # noqa: E402
from .analyze import _analyze_wrap, check_analyze, render_feedback, _parse_numeric  # noqa: E402


# Patterns for variable substitution.
# A subscript char: anything but "]"/";"/"$", plus a "$" that does NOT start
# a "$(" — so arithmetic parens are allowed (`(2*$m_k-1)%3+1`, `(1+3)`) and
# plain `$var` refs too, but a *nested* `$(…)` makes the pattern stop. That
# deferral lets a nested $(outer[…$(inner[i])…]) resolve inner-first:
# _resolve_indexed_forms loops and picks up the outer once the inner is gone
# (e.g. $(val14[$m_h;$(val11[$m_h])])).
_SUB = r"(?:[^\]$;]|\$(?!\())"
# `$(var[n..m])` — bounds may be ints, `$var`, or arithmetic; _eval_arith
# reduces them after substitution. Bounds use _SUB so a nested range-slice
# `$(outer[$(inner[1..3]);])` doesn't make this regex match the OUTER ref on
# the inner's "..".
# Range bound separator: `..` or WIMS' ` to ` (e.g. `$(val[1 to 3])`).
_RANGE_SLICE_RE = re.compile(rf"\$\((\w+)\[({_SUB}+?)(?:\.\.|\s+to\s+)({_SUB}+?)\]\)")
_INDEXED2_RE = re.compile(rf"\$\((\w+)\[({_SUB}*?);({_SUB}*)\]\)")  # $(var[n;m])
# INDEXED1's subscript also excludes ";" (built into _SUB) so it never
# swallows a $(var[n;m]) matrix form, whose ";" must go to _INDEXED2_RE.
_INDEXED1_RE = re.compile(rf"\$\((\w+)\[({_SUB}+)\]\)")  # $(var[n])
_PAREN_VAR_RE = re.compile(r"\$\((\w+)\)")  # $(var)
_DOLLAR_VAR_RE = re.compile(r"\$([a-zA-Z_][a-zA-Z0-9_]*)")  # $varname
# A bare $var sitting inside a $(...) — i.e. the name/subscript of an
# enclosing reference is itself built from a variable ($(slib_theme$slib_n)).
_DOLLAR_IN_PAREN_RE = re.compile(r"\$\([^)]*\$[a-zA-Z_]")

# Division par une puissance de 10 — `/1000` comme `/10**(3)`, parenthèses
# éventuelles. Signe d'une mise à l'échelle décimale, non d'une fraction
# (cf. `_expected_as_fraction`).
_DIVISION_DECIMALE_RE = re.compile(r"/\s*\(*\s*(?:10\s*\*\*|10*0)\b")


# `<nom>.<lang>` — la langue que WIMS lit dans le nom du répertoire du module.
_MODULE_LANG_RE = re.compile(r"\.([a-z]{2})$")


def _langue_du_module(def_path: str | None) -> str:
    r"""Code ISO du module, tiré de son répertoire (`oefpenney.it` → `it`).

    C'est la source de `$lang` chez WIMS, et donc d'`oefenv_lang` : un `.def`
    sans `\language` ne dit rien de la langue du module qui l'héberge.
    """
    if not def_path:
        return ""
    module = os.path.basename(os.path.dirname(os.path.dirname(def_path)))
    m = _MODULE_LANG_RE.search(module)
    return m.group(1) if m else ""


def _fin_nom_math(s: str, i: int) -> int:
    """`find_mathvar_end` : un nom mathématique court sur les lettres, les
    chiffres, le point et l'apostrophe — `f'` et `x.1` en sont."""
    j = i
    while j < len(s) and (s[j].isalnum() or s[j] in ".'"):
        j += 1
    return max(j, i + 1)


def _PORTE_UN_METACARACTERE(old: str, new: str) -> bool:
    """`strpbrk(bf[0],"\\\\[^.*$")` de `calc.c` — sur l'un OU l'autre motif.

    C'est ce test, et lui seul, qui décide si `!replace` remplace du texte ou
    lance sed. Le caractère cherché dans le *remplacement* compte autant que
    dans le motif : `!replace , by \\n in …` passe donc en regexp.
    """
    return any(c in old or c in new for c in "\\[^.*$")


# Métacaractères que BRE écrit **échappés**, là où l'expression régulière de
# Python les veut nus : `\(` y ouvre un groupe, `(` est un littéral.
_BRE_ECHAPPES_ACTIFS = "(){}|+?"
# …et ceux qui restent littéraux une fois échappés, dans les deux notations.
_BRE_ECHAPPES_LITTERAUX = "^$.*[]\\"


def _bre_vers_python(motif: str) -> str:
    """Traduit une expression régulière POSIX **basique** — celle de sed — en
    son équivalent Python.

    La différence tient aux échappements, exactement inversés pour sept
    caractères : `\\(` groupe en BRE quand `(` est un littéral, et
    réciproquement. Les classes `[…]` se recopient telles quelles : à
    l'intérieur, plus rien n'est métacaractère hormis `]`, `^` en tête et `-`.

    Une divergence subsiste, sur les correspondances **vides** : `s/x*/Q/g`
    rend `QyQ` chez sed et `QQyQ` en Python, qui substitue aussi la
    correspondance vide suivant une non vide. Aucun des 121 motifs du corpus ne
    l'exerce — tous exigent au moins un caractère —, et le seul `*` isolé ne se
    compile pas, ce qui fait retomber l'appelant sur le remplacement littéral,
    précisément ce que POSIX demande d'un `*` en tête d'expression.
    """
    out: list[str] = []
    i = 0
    while i < len(motif):
        c = motif[i]
        if c == "\\" and i + 1 < len(motif):
            suivant = motif[i + 1]
            if suivant in _BRE_ECHAPPES_ACTIFS:
                out.append(suivant)          # `\(` → `(`
            elif suivant in _BRE_ECHAPPES_LITTERAUX:
                out.append("\\" + suivant)   # `\^` reste un accent littéral
            else:
                out.append("\\" + suivant)   # `\n`, `\t`, `\w` : tels quels
            i += 2
            continue
        if c == "[":
            fin = i + 1
            if fin < len(motif) and motif[fin] == "^":
                fin += 1
            if fin < len(motif) and motif[fin] == "]":
                fin += 1                     # un `]` en tête est un littéral
            while fin < len(motif) and motif[fin] != "]":
                fin += 1
            if fin >= len(motif):
                out.append("\\[")            # crochet non fermé : littéral
                i += 1
                continue
            out.append(motif[i : fin + 1])
            i = fin + 1
            continue
        if c in _BRE_ECHAPPES_ACTIFS:
            out.append("\\" + c)             # `(` est un littéral en BRE
        else:
            out.append(c)
        i += 1
    return "".join(out)


def _sed_substitution(old: str, new: str):
    """La fonction de substitution `s/old/new/g` de sed, ou None si le motif
    ne se compile pas — auquel cas l'appelant retombe sur le remplacement
    littéral plutôt que d'abandonner la valeur."""
    try:
        motif = re.compile(_bre_vers_python(old))
    except re.error:
        return None
    # Dans le remplacement, sed ne connaît que `&` (tout le motif) et `\1`…
    # Le reste est littéral, `\` compris — que `re.sub` interpréterait.
    remplacement = re.sub(r"\\(?![1-9])", r"\\\\", new)
    remplacement = re.sub(r"(?<!\\)&", r"\\g<0>", remplacement)
    try:
        return lambda texte: motif.sub(remplacement, texte)
    except re.error:
        return None

# Answer types whose value is an algebraic expression (potentially long), so a
# no-embed fallback reply field gets a wider default than a numeric one.
_WIDE_FALLBACK_TYPES = {
    "litexp", "algexp", "formal", "function", "numexp", "default", "auto",
}

# L'intitulé que WIMS pose au-dessus des champs qu'il n'a pas embarqués
# (`$name_enterreply` de `scripts/oef/<lang>/names.proc`, rendu par
# `oef/form.phtml`). Il ne paraît que s'il reste une réponse à y mettre.
_ENTER_REPLY = {
    "fr": "Entrez votre réponse :",
    "en": "Enter your reply:",
    "nl": "Voer hier je antwoord in:",
    "it": "Inserire la risposta:",
    "es": "Introduzca su respuesta:",
    "de": "Antwort eingeben:",
    "ca": "Entrar la resposta:",
}

# Les types dont le `.input` écrit `<label>nom</label>&nbsp;=` — la réponse s'y
# lit comme une égalité (`Solution(s) = …`). Les autres posent le nom seul :
# `atext` demande une phrase, `case` un mot, `coord` un point. Relevé sur les
# `anstype/*.input` de l'arbre WIMS, non deviné.
_EGAL_APRES_LABEL = {
    "algexp", "aset", "chemeq", "complex", "default", "formal", "fset",
    "function", "litexp", "matrix", "numeric", "numexp", "range", "set",
    "sigunits", "units", "vector",
}

# Racine servie par `/api/static` (cf. `main.py`). `!rename` y ramène ses
# chemins ; c'est aussi la barrière qui les y confine.
_RESSOURCES_ROOT = os.path.normpath(
    os.path.join(os.path.dirname(__file__), "..", "..", "..", "..", "ressources")
)

# `anstype/inputcss.inc` injects the lines that follow the size verbatim into the
# `<input>` tag, so they may be bare flags (`autofocus`) or `name="value"` pairs
# (`autocomplete="off"`). Only attributes on this allow-list are forwarded: the
# tail is exercise content, and an `on…` handler reaching the DOM would run.
_ALLOWED_INPUT_ATTRS = {
    "autocomplete", "autofocus", "dir", "inputmode", "lang", "maxlength",
    "placeholder", "readonly", "spellcheck", "title",
}
_INPUT_ATTR_RE = re.compile(
    r"""([A-Za-z][A-Za-z0-9-]*)(?:\s*=\s*("[^"]*"|'[^']*'|[^\s"']+))?"""
)


def _split_range_spec(idx_s: str) -> tuple[str, str] | None:
    """Bornes d'un indice-plage `a to b` / `a..b`, ou None (`_blockof`, calc.c).

    Le `to` est cherché à **profondeur zéro** et doit être un mot : précédé
    d'un blanc (ou en tête) *et* suivi d'un blanc — un `to` collé, ou en fin de
    chaîne, n'ouvre pas de plage. À défaut, `..`, sans condition de frontière.
    """
    n = len(idx_s)
    i = wl.strparstr(idx_s, "to")
    while i < n:
        before_ok = i == 0 or idx_s[i - 1] in " \t\n\r"
        after_ok = i + 2 < n and idx_s[i + 2] in " \t\n\r"
        if before_ok and after_ok:
            return idx_s[:i], idx_s[i + 2:]
        i = wl.strparstr(idx_s, "to", i + 2)
    i = wl.strparstr(idx_s, "..")
    if i < n:
        return idx_s[:i], idx_s[i + 2:]
    return None


_JS_IDENT = re.compile(r"[A-Za-z_$][A-Za-z_0-9$]*")


def _objets_cliquables(replygood: str) -> list[str]:
    """Les objets qu'un `jsxgraphobjet` rend cliquables, dédoublonnés.

    `anstype/jsxgraphobjet.input` ne distingue pas la bonne réponse des
    leurres : il ramène `;`, `&` et `|` à la virgule et prend la liste entière
    (`!listuniq`), les trois séparateurs disant respectivement la ligne, le
    groupe et l'alternative. `hypo;cat1|cat2` désigne donc trois segments
    cliquables, dont `hypo` est le seul attendu.

    Le nom sert de variable JavaScript dans le script de la figure : on écarte
    ce qui n'est pas un identifiant, un `replygood` mal formé n'ayant pas à
    finir dans du code.
    """
    plat = replygood.replace(";", ",").replace("&", ",").replace("|", ",")
    vus: list[str] = []
    for brut in plat.split(","):
        nom = brut.strip()
        if nom and nom not in vus and _JS_IDENT.fullmatch(nom):
            vus.append(nom)
    return vus


def _normalize_reply_type(rtype: str) -> str:
    """Canonical reply type, folding `dragfill` onto `clickfill`.

    `help/anstype/clickfill.phtml` documents the two as one widget with one
    difference: a label may be dropped several times in a `clickfill`, at most
    once in a `dragfill`. Everything else — `replygood` as `correct;pool`, the
    `HxVxLxT` embed size, the shared shuffled palette — is identical, so the
    single-use constraint travels separately (`options["single_use"]`).
    """
    t = rtype.strip().lower()
    return "clickfill" if t == "dragfill" else t


def _expected_is_developed(good_raw: str) -> bool:
    """L'attendu est-il une somme de monômes réduite ?

    Sert à ne marquer `expand` que là où la forme développée est bien ce que
    l'exercice demande. Une factorisation (`(2 y + 13)^2`) ou une réponse
    multiple laisse la question ouverte : on s'abstient plutôt que d'imposer.
    """
    from core.answer.checkers import is_polexpand  # noqa: PLC0415

    premier = (good_raw or "").split(",")[0].strip()
    return bool(premier) and is_polexpand(premier)


def _order_fill_choices(
    choices: list[str],
    opt_words: list[str],
    rng,
    *,
    is_dragfill: bool,
    slots: int,
) -> list[str]:
    """Ordre d'affichage d'une palette, d'après ``anstype/fill.after``.

    Le fichier — partagé par `clickfill` et `dragfill` — décide en trois temps :

        !if $wims_fill_type=dragfill
          !if keeporder notwordof $wims_fill_option
            !ifval $t_<=$filltotal or $t_<=12
              !set list=!shuffle $list
            !else
              !set list=!sort items $list
        !else
          !set list=!listuniq $list
          !if keeporder notwordof $wims_fill_option
            !set list=!sort items $list
        !endif
        !if shuffle iswordof $wims_fill_option
          !set list=!shuffle $list
        !if sort iswordof $wims_fill_option
          !set list=!sort items $list

    Un `clickfill` est donc **trié** par défaut, et ne se mélange que si
    l'auteur écrit `shuffle` — PAX le mélangeait systématiquement. Un
    `dragfill` se mélange tant qu'il tient dans ses cases ou dans douze
    étiquettes, et se trie au-delà (une longue liste reste parcourable).

    Le tri est celui de `calc_sort` sans mot-clé : `strcmp`, donc par octets et
    sensible à la casse. En UTF-8 l'ordre des octets suit celui des points de
    code, si bien que le `sorted` de Python lui est équivalent.

    Les deux options finales s'appliquent aux deux types : elles sont hors du
    `if/else` dans le C.
    """
    if "keeporder" not in opt_words:
        if is_dragfill:
            if len(choices) <= max(slots, 12):
                rng.shuffle(choices)
            else:
                choices.sort()
        else:
            choices.sort()
    if "shuffle" in opt_words:
        rng.shuffle(choices)
    if "sort" in opt_words:
        choices.sort()
    return choices


def _parse_input_attributes(tail: str) -> dict[str, object]:
    """HTML attributes carried by the extra lines of an `\\embed` size parameter.

    Returns ``{name: value}``, a bare flag mapping to ``True``. Unknown names are
    dropped silently — WIMS' own tail also holds non-attribute payloads (the
    `brd [responsive …]` of a jsxgraph embed, which never reaches this path).
    """
    attrs: dict[str, object] = {}
    for line in tail.splitlines():
        line = line.strip()
        if not line:
            continue
        for m in _INPUT_ATTR_RE.finditer(line):
            name = m.group(1).lower()
            if name not in _ALLOWED_INPUT_ATTRS:
                continue
            raw = m.group(2)
            if raw is None:
                attrs[name] = True
            else:
                attrs[name] = raw[1:-1] if raw[:1] in ("'", '"') else raw
    return attrs


# ── Public entry point ────────────────────────────────────────────────────────


@lru_cache(maxsize=256)
def _module_confparm_defaults(def_path: str | None) -> tuple[tuple[str, str], ...]:
    """Valeurs par défaut des `confparm` posées par le module lui-même.

    Un module WIMS règle ses paramètres dans son `introhook.phtml`, le bloc
    inséré dans sa page d'accueil : la valeur est fixée, le `!formselect` qui
    suit laisse l'enseignant en choisir une autre.

        !default confparm1=1
        !formselect confparm1 list 1,2,3,4,5

    Sans cette lecture, `$confparm1` reste vide, et un exercice qui boucle
    dessus — `!for val11 =1 to $val2` où `val2=$confparm1` — se rend sans une
    seule question. `!default` ne remplace jamais une valeur déjà posée, d'où
    l'application avant tout le reste.

    **Les deux formes comptent.** Le corpus compte 8 modules qui posent ainsi
    une valeur — 7 par `!default`, `droiteplanrep.fr` par `!set` ; l'arbre WIMS
    en compte 23, dont 9 par `!set`. Ne lire que `!default` laisserait donc
    `droiteplanrep.fr` sans son `confparm1=1`, celui-là même que son
    `!formradio … prompt Non, Oui` propose ensuite de changer.

    `!set` l'emporte sur `!default` s'ils coexistent, comme chez WIMS où il
    écrase une valeur déjà posée. Aucun module du corpus ne mélange les deux ;
    la règle est là pour ne pas dépendre de l'ordre des lignes.
    """
    if not def_path:
        return ()
    hook = os.path.join(
        os.path.dirname(os.path.dirname(def_path)), "introhook.phtml"
    )
    try:
        with open(hook, encoding="latin-1") as f:
            texte = f.read()
    except OSError:
        return ()
    trouves: dict[str, str] = {}
    for forme in ("set", "default"):
        for m in re.finditer(
            rf"^\s*!{forme}\s+(confparm\d+)\s*=\s*(.*?)\s*$", texte, re.M
        ):
            trouves.setdefault(m.group(1), m.group(2))
    return tuple(trouves.items())


def _position_du_mot(botte: str, mot: str) -> int:
    """`wordchr` : index de la première occurrence de `mot` **en tant que mot**.

    Les bornes sont les caractères non alphanumériques, le souligné excepté —
    sans quoi `swac_text` répondrait à une recherche de `text`.
    """
    if not mot:
        return -1
    def est_lettre(c: str) -> bool:
        return c.isalnum() or c == "_"

    i = botte.find(mot)
    while i >= 0:
        avant_ok = i == 0 or not est_lettre(botte[i - 1])
        j = i + len(mot)
        apres_ok = j >= len(botte) or not est_lettre(botte[j])
        if avant_ok and apres_ok:
            return i
        i = botte.find(mot, i + 1)
    return -1


# Les langues que WIMS déclare installées par défaut (`bases/sys/defaults.conf`,
# `DF_site_languages`). Un déploiement PAX qui n'en servirait qu'une partie
# n'aurait qu'à restreindre cette liste : elle ne sert qu'à valider la langue
# qu'un exercice demande, jamais à en choisir une.
_LANGUES_DU_SITE = "en fr es it nl ca si de cn"

# Racine des URL de session (`$wims_ref_name`). Voir le commentaire à sa pose :
# le préfixe `https` est ce que `jmolshow` teste, le domaine `.invalid` dit que
# personne n'est censé la déréférencer.
_WIMS_REF_NAME = "https://pax.invalid/wims.cgi"


def _chemin_du_module(def_path: str | None) -> str:
    """`$module_dir` : le chemin du module tel que WIMS le nomme.

    WIMS enracine ses modules dans `modules/` (`wims.c:159`) ; PAX les tient
    sous `ressources/`, mais ce sont les tests de chaîne des slib qui comptent
    (`adm/createxo isin $module_dir`), et ils sont écrits pour la forme WIMS.
    """
    if not def_path:
        return ""
    module = os.path.dirname(os.path.dirname(def_path))
    tete, _, queue = module.partition("/ressources/")
    return "modules/" + queue if queue else ""


def _rangees_protegees(s: str) -> list[str]:
    """Découpe en rangées sur les `;` de profondeur zéro, **toujours**.

    `rows2lines` (`liblines.c`) ne convertit les `;` que si la valeur ne
    contient aucun saut de ligne ; sinon rangées et lignes se confondent. Cette
    garde suffit tant que la valeur est courte, mais elle dégénère sur un
    `replygood` de `type=draw`, qui juxtapose une **figure multiligne** et la
    réponse attendue :

        replygood1=[<figure sur dix lignes>];crosshairs,1.59,-0.04,…

    WIMS y lit alors comme « rangée 2 » la deuxième *ligne de la figure* —
    `yrange -1.46,2.29` —, dont il tire un type d'objet à dessiner qui n'existe
    pas. C'est le cas d'`oefpolynet/31` et `32` ; `evolmeth`, dont la figure est
    tabulée et non multiligne, y échappe. On lit donc la syntaxe que l'auteur a
    écrite — les crochets délimitent la figure, le `;` sépare — plutôt que le
    résultat dégénéré.
    """
    parts: list[str] = []
    courant: list[str] = []
    i = 0
    n = len(s)
    while i < n:
        ch = s[i]
        ferme = {"(": ")", "[": "]", "{": "}"}.get(ch)
        if ferme is not None:
            j = wl.find_matching(s, i + 1, ferme)
            if j >= 0:
                courant.append(s[i : j + 1])
                i = j + 1
                continue
        if ch == ";":
            parts.append("".join(courant))
            courant = []
        else:
            courant.append(ch)
        i += 1
    parts.append("".join(courant))
    return parts


def _declos(s: str) -> str:
    """Retire une paire de crochets englobante — le `!declosing` de WIMS."""
    t = s.strip()
    if len(t) >= 2 and t[0] == "[" and t[-1] == "]":
        return t[1:-1]
    return t


def _plage_flydraw(programme: str, mot: str) -> str:
    """`xrange a,b` / `yrange a,b` d'un programme flydraw, ou la chaîne vide.

    Les bornes peuvent être des expressions (`-1*6+1,6*1.5` chez `evolmeth`) :
    on les rend telles quelles, à charge du lecteur de les évaluer.
    """
    m = re.search(
        rf"(?:^|[\n\t;])\s*{mot}\s+([^\n\t;]+)", programme, re.IGNORECASE
    )
    return m.group(1).strip() if m else ""


def _horloge_session() -> datetime.datetime:
    """L'instant que voit l'exercice, gelable par `PAX_WIMS_NOW`.

    WIMS fige l'heure une fois par requête (`wims.c:1200`) ; PAX la fige une
    fois par rendu. La variable d'environnement — au format `AAAAMMJJ.hh:mm:ss`
    de `$wims_now` — sert aux snapshots : `quizzautomat.fr/pcent5` date son
    énoncé de l'année courante, et sans horloge fixe sa référence pourrit au
    changement d'année.
    """
    fige = os.environ.get("PAX_WIMS_NOW")
    if fige:
        try:
            return datetime.datetime.strptime(fige, "%Y%m%d.%H:%M:%S")
        except ValueError:
            pass
    return datetime.datetime.now()


@lru_cache(maxsize=512)
def _module_var_proc_lines(def_path: str | None) -> tuple[str, ...]:
    """Lignes du `var.proc` du module, exécutées avant chaque exercice.

    WIMS lit ce fichier « for all valid calls to the module » : il porte
    l'environnement commun aux exercices, là où `introhook.phtml` ne porte que
    les valeurs par défaut réglables par l'enseignant. La différence compte dès
    qu'un paramètre se **calcule** plutôt que se choisir :

        basep=!randitem $confparm1        (numeration.fr)
        confparm4=$basep\\…

    `confparm4` n'existe nulle part ailleurs, et sans lui `slib/basep` reçoit
    un `NaN`.
    """
    if not def_path:
        return ()
    chemin = os.path.join(os.path.dirname(os.path.dirname(def_path)), "var.proc")
    try:
        with open(chemin, encoding="utf-8") as f:
            texte = f.read()
    except UnicodeDecodeError:
        with open(chemin, encoding="cp1252") as f:
            texte = f.read()
    except OSError:
        return ()
    from ..def_parser import _merge_continuations  # noqa: PLC0415

    return tuple(_merge_continuations(texte.split("\n")))


@lru_cache(maxsize=2048)
def _parse_def_cached(def_path: str) -> DefFile:
    """Parse a .def file into an AST and cache the result by path.

    The AST (DefFile) is read-only: DefEngine re-evaluates it for each seed.
    Files are static during a process lifetime, so no TTL is needed.
    maxsize=2048 covers the full H4 corpus (2270 files) with some headroom.
    """
    try:
        with open(def_path, encoding="utf-8") as f:
            text = f.read()
    except UnicodeDecodeError:
        with open(def_path, encoding="cp1252") as f:
            text = f.read()
    return parse_def(text)


def load_and_render(
    def_path: str,
    seed: int | None = None,
    m_step: int | None = None,
    prev_replies: dict[str, str] | None = None,
) -> ExerciseRender:
    """Parse (cached) and evaluate a .def file, returning an ExerciseRender.

    ``prev_replies`` ({input_name: value}) are the answers submitted on earlier
    course steps; they populate `$m_reply{n}`/`$m_sc_reply{n}` for the step
    statement's per-reply verdict.
    """
    if seed is None:
        seed = random.randint(0, 2**31)

    def_file = _parse_def_cached(def_path)
    engine = DefEngine(seed=seed, def_path=def_path)
    if m_step is not None:
        engine.ctx["m_step"] = str(m_step)
        engine.ctx["step"] = str(m_step)  # WIMS alias
    if prev_replies:
        engine.prev_replies = dict(prev_replies)
    return engine.render(def_file)


# ── Engine ────────────────────────────────────────────────────────────────────


class DefEngine(_SlibMixin):
    # Voir `_eval_arith` : au rendu un calcul raté se montre tel quel, à la
    # correction il vaut NaN. `check_analyze` lève ce drapeau. Attribut de
    # **classe** à dessein — les tests du pipeline construisent un moteur sans
    # passer par `__init__`, et un attribut d'instance les ferait tomber.
    _strict_arith: bool = False
    # Les palettes des `\choice`, composées par `_prepare_choices`.
    _choice_lists: dict[str, list[str]] = {}
    # Faut-il proposer « aucune de ces réponses » ? Oui quand la bonne
    # réponse n'est pas garantie présente (`qcmgood<1`, cf. `formc.phtml`).
    _choice_none: dict[str, bool] = {}

    def __init__(self, seed: int, def_path: str | None = None):
        self.seed = seed
        self._choice_lists = {}
        self._choice_none = {}
        self.rng = random.Random(seed)
        # Échéance du budget temps (posée par render()) ; None = pas de limite.
        self._deadline: float | None = None
        # WIMS treats ``$empty`` as the predefined empty-string sentinel;
        # exposing it as a regular ctx entry keeps `_subst` happy.
        # Always initialize m_step to "1" so it's defined when var_instructions execute.
        # Also set step as an alias for m_step (WIMS uses both \step and \m_step).
        # ``imagedir`` is a sentinel "pax-img:_" — the trailing "_" is a dummy
        # path element so ``$imagedir/../<file>`` (the common WIMS pattern)
        # normalises to ``pax-img:<file>`` after path resolution. The actual
        # file lookup happens in inline_pax_images() during post-render.
        self.ctx: dict[str, str] = {
            "empty": "",
            "m_step": "1",
            "step": "1",
            "m_times": "×",
            "m_div": "÷",
            "m_le": "≤",
            "m_ge": "≥",
            "m_neq": "≠",
            "imagedir": "pax-img:_",
        }
        # Path of the .def file being rendered. Used to resolve `!readproc
        # slib/<name>` paths relative to the module directory.
        self.def_path = def_path
        # Les `confparm` que le module se donne à lui-même, avant tout le reste.
        self.ctx.update(_module_confparm_defaults(def_path))
        # Variables du mini-interpréteur PARI. WIMS pilote un unique processus
        # `gp` par exécution, donc les `!exec pari` successifs se partagent leur
        # état : oefforpython.fr définit `l=vector(n);for(…)` dans un appel puis
        # l'affiche avec `print(l)` dans le suivant.
        self.pari_session: dict[str, object] = {}
        # Le magasin de `oef/togetfile.proc` — les fichiers que WIMS écrirait
        # dans le répertoire de la session (`.xyz`, `.spt` d'une figure Jmol).
        # Il vit hors de `ctx`, qui n'accepte que des chaînes, et ne dure que
        # le temps d'un rendu : producteur et lecteur sont dans ce moteur-ci.
        self._getfile_store: dict[str, str] = {}
        # Exercise content language (ISO code). Set from df.meta at render time;
        # drives the decimal/list separator for number display & checking
        # (see core/oef/i18n.py). Defaults to French until render() reads it.
        self.lang = "fr"
        # Set of reply names (e.g. "reply4") referenced by !read oef/embed.phtml
        # during the current render. Used to filter `answers` for dynsteps/course
        # exercises so only the active step's answers are exposed to the API.
        self._touched_replies: set[str] = set()
        # Raw (unevaluated) RHS of the last assignment to each variable. Lets
        # the numeric-answer fraction recovery trace `$[$val9]` back through
        # `val9=$[$(val8[2])]` to the original `3/4` (the floated ctx value has
        # lost it). See `_expected_as_fraction`.
        self.raw_assigns: dict[str, str] = {}
        # Replies the student already submitted on previous steps of a course
        # exercise, {input_name: value}. Used to populate WIMS' memorised
        # `$m_reply{n}` / `$m_sc_reply{n}` so a later step's statement can echo
        # "reply : BONNE/MAUVAISE REPONSE" (lebrun5). Set by load_and_render.
        self.prev_replies: dict[str, str] = {}

    # ── Top-level render ──────────────────────────────────────────────────────

    # ── \nextstep (étapes dynamiques) ─────────────────────────────────────────

    @staticmethod
    def _normalise_nextstep(raw: str) -> str:
        """Port de `wims/public_html/scripts/oef/nextstep.proc`.

        `replies`/`choices` → `r`/`c`, minuscules, espaces retirés, tabulations
        converties en lignes (`!rows2lines`), puis **première ligne non vide**.
        Une chaîne vide signifie « plus d'étape ».
        """
        if not raw.strip():
            return ""
        s = raw.lower()
        for long, short in (
            ("replies", "r"), ("choices", "c"), ("reply", "r"), ("choice", "c")
        ):
            s = s.replace(long, short)
        # `!nospace` retire les blancs sauf les sauts de ligne ; `!rows2lines`
        # promeut ensuite les tabulations en sauts de ligne.
        s = re.sub(r"[^\S\n\r\t]", "", s)
        for line in re.split(r"[\t\r\n]+", s):
            if line:
                return line
        return ""

    @staticmethod
    def _nextstep_depends_on_replies(postdef: list, nextstep_raw: str) -> bool:
        """True si la *suite* de l'exercice dépend des réponses déjà données.

        26 des 97 exercices dont `\\nextstep` pointe vers une variable calculée
        en `:postdef` font dépendre l'existence de l'étape suivante de la
        *justesse* d'une réponse (`!ifval ($m_step==2 and $m_sc_reply1==1)`,
        oefechpython.fr/de4) — c'est ce que la doc OEF appelle « étapes
        dynamiques ». Leur nombre d'étapes n'est pas connaissable avant que
        l'élève ait répondu.

        Seules comptent les affectations de la variable que `\\nextstep`
        désigne : `heron1` lit `$m_sc_reply2` pour composer un feedback, mais
        son `val6` ne branche que sur `$m_step`, donc son total est connu.
        """
        from ..def_parser import Assign, IfBlock  # noqa: PLC0415

        m = re.fullmatch(r"\$\(?(\w+)\)?", (nextstep_raw or "").strip())
        if not m:
            # Forme littérale (`reply1<TAB>reply2,reply3`) : rien à recalculer.
            return False
        target = m.group(1)
        pat = re.compile(r"\$m_(?:sc_)?(?:reply|choice)")

        def walk(body: list, guarded: bool) -> bool:
            for instr in body:
                if isinstance(instr, IfBlock):
                    cond = guarded or bool(pat.search(instr.condition))
                    if walk(instr.then_body, cond) or walk(instr.else_body, cond):
                        return True
                elif isinstance(instr, Assign) and instr.name == target:
                    if guarded or pat.search(instr.value or ""):
                        return True
            return False

        return walk(postdef, False)

    def _resolve_nextstep(
        self, df: DefFile, dynamic_out: list | None = None
    ) -> tuple[int | None, list[str]] | None:
        """Progression d'un exercice `\\nextstep` : (total d'étapes, `oefsteps`).

        WIMS relit `$nextstep` après chaque étape (`nextstep.proc`) et s'arrête
        dès qu'il est vide ; le total n'est donc jamais écrit dans le `.def`. On
        rejoue la progression en repartant de l'étape 1 — `:postdef` ne branche
        que sur `$m_step` et sur les réponses mémorisées, toutes deux déjà dans
        le contexte au moment du rendu.

        Le total renvoyé vaut ``None`` quand la suite dépend des réponses : au
        delà de l'étape courante on ne sait pas encore combien d'étapes
        viendront, et annoncer un nombre serait un mensonge. Les lignes déjà
        déterminées, elles, restent exactes et sont renvoyées dans tous les cas.

        Renvoie ``None`` quand `\\nextstep` est inactif (`postvarcnt=0`, le cas
        majoritaire : WIMS sort alors immédiatement de `nextstep.proc`).
        """
        try:
            postvarcnt = int(str(df.meta.get("postvarcnt", "0")).strip() or "0")
        except ValueError:
            postvarcnt = 0
        postdef = df.sections.get("postdef") or []
        if postvarcnt <= 0 or not postdef or "nextstep" not in self.ctx:
            return None

        try:
            current = int(self.ctx.get("m_step", "1"))
        except (TypeError, ValueError):
            current = 1
        dynamic = self._nextstep_depends_on_replies(postdef, self.ctx.get("nextstep", ""))
        if dynamic_out is not None:
            dynamic_out.append(dynamic)

        saved = dict(self.ctx)
        steps: list[str] = []
        total: int | None = None
        deadline = self._deadline
        self._deadline = time.monotonic() + _NEXTSTEP_TIME_BUDGET
        try:
            # `step.proc` fait `!advance oefstep` / `m_step=$oefstep` *avant*
            # de lire `nextstep.proc` : `:postdef` s'exécute donc avec `m_step`
            # pointant l'étape à venir, et les `.def` testent bien `m_step==2`
            # pour décider si une deuxième étape existe. La première est déjà
            # décrite par `oefsteps`, d'où le départ à 2.
            for k in range(2, _MAX_NEXTSTEPS + 1):
                # Progression conditionnée par les réponses : au-delà de l'étape
                # courante, le rejeu extrapolerait sur des réponses que l'élève
                # n'a pas encore données. On laisse alors le total indéterminé
                # plutôt que d'en annoncer un faux.
                if dynamic and k > current:
                    break
                self.ctx["m_step"] = str(k)
                self.ctx["step"] = str(k)
                try:
                    self._exec(postdef, output_buf=None)
                except _RenderBudgetExceeded:
                    break
                line = self._normalise_nextstep(self._subst(self.ctx.get("nextstep", "")))
                if not line:
                    total = k - 1
                    # Progression conditionnée par les réponses : sans elles,
                    # `:postdef` peut refuser d'ouvrir une étape pourtant déjà
                    # atteinte (oefechpython.fr/de4). Le total ne peut alors
                    # pas être inférieur à l'étape en cours. Pour un exercice
                    # déterministe, au contraire, `k-1` fait autorité — un
                    # `m_step` au-delà est une étape qui n'existe pas.
                    if dynamic:
                        total = max(total, current)
                    break
                steps.append(line)
        finally:
            self._deadline = deadline
            self.ctx.clear()
            self.ctx.update(saved)
        return total, steps

    def render(self, df: DefFile) -> ExerciseRender:
        # m_step is now always initialized to "1" in __init__, and can be
        # overridden by load_and_render before calling render(). This ensures
        # m_step is defined when var_instructions execute, so conditions like
        # !if $m_step=2 work correctly.
        self.lang = df.meta.get("language", "fr")
        # `slib/oef/env <mot>` rend `$(oefenv_<mot>)`, et ces variables sont
        # posées par `oef/var.proc` — que PAX ne lit pas :
        #
        #     oefenv_presentgood=$presentgood
        #     oefenv_lang=$lang            (ou $lang_choice si le module est traduit)
        #
        # Faute d'elles, les 534 `slib/oef/env lang` du corpus rendaient tous
        # le vide. `presentgood` vaut « le corrigé est-il montré » : PAX rend
        # l'énoncé, jamais la correction, d'où `no`.
        #
        # `$lang` est celle du **module**, que WIMS tient de son répertoire —
        # `oefpenney.it` est italien —, non celle du `.def`. Un exercice sans
        # `\language` y retomberait sur le `fr` par défaut de `self.lang` et
        # afficherait du français dans un module italien : c'est ce qui est
        # arrivé aux dix `oefpenney.it`, dont les textes existent dans les deux
        # langues et se choisissent précisément là-dessus.
        langue_module = _langue_du_module(self.def_path) or self.lang
        self.ctx.setdefault("oefenv_lang", langue_module)
        self.ctx.setdefault("oefenv_presentgood", "no")
        # `$lang` est une variable de **session** chez WIMS. Elle ne comptait pas
        # tant que PAX posait directement `oefenv_lang`, mais le `var.proc` du
        # module la relit — quatre modules y écrivent `oefenv_lang=$lang` — et
        # sans elle il rétablissait le vide qu'on venait de combler, pour
        # dix-huit exercices. `$presentgood` s'y prêterait aussi, mais aucun
        # `var.proc` du corpus ne le lit : on ne le pose pas.
        self.ctx.setdefault("lang", langue_module)
        # `$wims_now` / `$wims_nowseconds` — l'horloge de la session, posée par
        # WIMS au tout début de la requête (`wims.c:1200`, format
        # `AAAAMMJJ.hh:mm:ss`, et les secondes depuis l'époque). Un seul
        # consommateur dans le corpus, mais il suffisait à casser l'énoncé :
        # `quizzautomat.fr/var.proc` en tire `oefenv_year`, et sans lui
        # `pcent5` datait son chiffre d'affaires « en -2 » et « en -1 ».
        # `$wims_site_languages` — les langues installées sur le site, que
        # WIMS lit dans `wims.conf` (`DF_site_languages`, `defaults.conf:72`).
        # `slib/lang/fname` s'en sert pour valider la langue demandée :
        # `!bound slib_lang within $slib_langs default en`. Sur une liste vide,
        # tout retombe sur `en`, et la forme à trois paramètres rendait des
        # prénoms anglais dans des exercices français (`fr,boy,2`).
        self.ctx.setdefault("wims_site_languages", _LANGUES_DU_SITE)
        # `$module_dir` — `modules/<niveau>/<domaine>/<module>.<lang>`
        # (`wims.c:159` + `variables.c:564`). Ses quatre lecteurs du corpus
        # passent par `slib/geo2D/geogebra`, non porté : le rendu ne bouge pas.
        # On la pose quand même parce que le vide n'y est pas neutre —
        # `slib/chemistry/jmolshow` écrit `!replace internal $module_dir/ by in
        # …`, qui dégénère alors en « supprimer toutes les barres obliques ».
        # La branche n'est pas atteinte aujourd'hui ; elle le serait au premier
        # exercice Jmol servi depuis un fichier local.
        chemin_module = _chemin_du_module(self.def_path)
        if chemin_module:
            self.ctx.setdefault("module_dir", chemin_module)
        maintenant = _horloge_session()
        self.ctx.setdefault("wims_now", maintenant.strftime("%Y%m%d.%H:%M:%S"))
        self.ctx.setdefault("wims_nowseconds", str(int(maintenant.timestamp())))
        # `$wims_ref_name` — l'URL absolue du script WIMS, que `variables.c:118`
        # pose après avoir réécrit `http:` en `https:`. Le **`http`** compte :
        # `slib/chemistry/jmolshow` s'en sert pour distinguer une URL d'un
        # chemin de fichier (`!if __http isin __$slib_file`). Vide, le test
        # échoue, le slib prend l'URL que `togetfile` vient de lui rendre pour
        # un chemin, n'y lit rien, et **ré-écrit un fichier vide par-dessus** —
        # mesuré à 55 écritures vides sur les neuf exercices Jmol, dont les
        # `.xyz`/`.spt` corrects se retrouvaient orphelins.
        #
        # L'hôte est en `.invalid` (RFC 2606, garanti non résoluble) parce que
        # **rien ne doit être allé chercher là** : PAX ne sert pas de route
        # `cmd=getfile`. L'URL circule entre `togetfile.proc` et `jmolshow`,
        # tous deux internes au moteur, et `_render_jmol_embed` la résout
        # contre le magasin en mémoire avant qu'elle n'atteigne le navigateur.
        self.ctx.setdefault("wims_ref_name", _WIMS_REF_NAME)

        # Reply metadata (`replytype1=…`, `replyname1=…`, …) lives in
        # df.reply_meta, not in var_instructions. Seed it into ctx so the
        # statement rendering (specifically `_render_embed`) can see e.g.
        # `replytype1` to decide whether to emit a text input.
        for rm in df.reply_meta:
            n = rm.get("n")
            if n is None:
                continue
            for key in ("type", "name", "good", "option", "weight"):
                if key in rm:
                    self.ctx[f"reply{key}{n}"] = rm[key]

        # Idem pour les `\choice` — le même pré-semage, pour les mêmes raisons.
        for cm in df.choice_meta:
            n = cm.get("n")
            if n is None:
                continue
            for key in ("name", "good", "bad", "option", "weight"):
                if key in cm:
                    self.ctx[f"choice{key}{n}"] = cm[key]

        # Budget temps : abandonne le calcul des variables s'il s'emballe
        # (boucle non terminante d'un slib incomplet). On poursuit le rendu avec
        # l'état partiel plutôt que de bloquer plusieurs minutes.
        self._deadline = time.monotonic() + _RENDER_TIME_BUDGET
        try:
            # L'environnement du module vient avant l'exercice, comme chez WIMS :
            # ce que le `.def` pose ensuite l'emporte sur ce que le module suggère.
            lignes_module = _module_var_proc_lines(self.def_path)
            if lignes_module:
                try:
                    self._run_script_lines(list(lignes_module))
                except _SlibExit:
                    pass
            self._exec(df.var_instructions, output_buf=None)
        except _RenderBudgetExceeded:
            pass
        finally:
            self._deadline = None

        # Course/dynsteps: expose the previous steps' submitted replies + their
        # scores as WIMS' memorised `$m_reply{n}` / `$m_sc_reply{n}` so this
        # step's statement can echo "reply : BONNE/MAUVAISE REPONSE" (lebrun5).
        # Done after var_instructions so the expected (`$replygood{n}`, which
        # may reference val vars computed above) is resolvable.
        self._apply_prev_replies()

        # Les listes déroulantes des `\choice`, composées **avant** le rendu :
        # `\embed{c1}` les affiche, et leurs options se lisent dans les `valN`
        # que les instructions ci-dessus viennent de calculer.
        self._prepare_choices(df)

        # Render statement HTML
        stmt = df.statement.strip()
        if "__EXECUTED__" in stmt or "__EXECUTED" in stmt:
            q_section = df.sections.get("question", [])
            html = self._render_section(q_section)
        else:
            html = self._subst(stmt)

        from ..flydraw import inline_svg_imgs, inline_wims_gifs, inline_pax_images, group_inline_figures  # noqa: PLC0415

        html = _close_inline_math(html, self.lang)
        # A `<div class="wims_instruction">` (calculator notice, answer-format
        # hint…) is rendered *in source order*, like WIMS — it's just a CSS class
        # for technical instructions, WIMS never repositions it. (We used to
        # hoist it to the top; that wrongly put litt1's "Une seule bonne réponse"
        # *above* "Cliquez sur les bonnes réponses" — WIMS keeps it below.)
        # Group each flydraw figure with its label *before* the SVGs are
        # inlined — the placeholder is a single <img> tag here, easy to
        # locate; once inlined, the body contains its own <image>/<polygon>
        # which the boundary regex would otherwise stumble on.
        html = group_inline_figures(html)
        html = inline_svg_imgs(html)
        html = inline_wims_gifs(html)
        if self.def_path:
            module_dir = os.path.dirname(os.path.dirname(self.def_path))
            exercise = os.path.splitext(os.path.basename(self.def_path))[0]
            html = inline_pax_images(html, module_dir, exercise)
        # Drop empty `<li>` / `<ul>` shells left behind when radio embeds
        # are stripped (the frontend renders the radio buttons separately
        # from `options.choices`).
        html = re.sub(r"<li[^>]*>\s*</li>", "", html)
        html = re.sub(r"<ul[^>]*>\s*</ul>", "", html)
        answers = self._extract_answers(df)

        # Les figures d'une palette ou d'un attendu sont incorporées comme
        # celles de l'énoncé. Le marqueur `<img src="/api/render/svg/…">` est
        # une forme *interne*, choisie pour survivre aux découpages de listes
        # WIMS ; il ne peut pas sortir tel quel, car le cache SVG vit en
        # mémoire du backend et un rendu resservi par Redis le laisse sans
        # image (`oefmolecule/lewis` affichait 10 étiquettes vides). Palette et
        # attendu sont traités **ensemble** : ce sont deux chaînes comparées
        # l'une à l'autre, les incorporer d'un seul côté casserait la notation.
        # Les images de module (`pax-img:…`, posées par `$imagedir` ou par
        # `imgrename(…)`) y sont résolues au même titre : la palette d'un
        # `type=correspond` est faite de balises `<img>` — `oefmolecule` fait
        # apparier des modèles moléculaires à leur nom — et sans cette passe
        # l'URL sentinelle sortait telle quelle, donc aucune image à l'écran.
        for a in answers:
            if a.expected:
                if "/api/render/svg/" in a.expected:
                    a.expected = inline_svg_imgs(a.expected)
                a.expected = self._inline_module_imgs(a.expected)
            # `choices` porte la palette d'un radio ou d'un menu ; `lefts` et
            # `rights` les deux colonnes d'un `correspond`, que `oefgrfctref`
            # fait apparier — une courbe à gauche, son expression à droite.
            # Les trois sont du HTML d'affichage et se traitent pareil : sans
            # cette passe, les 36 figures de `lefts` sortaient en marqueur, donc
            # en image morte.
            for clef in ("choices", "lefts", "rights", "rights_shuffled"):
                valeurs = a.options.get(clef)
                if not valeurs:
                    continue
                a.options[clef] = [
                    self._inline_module_imgs(
                        inline_svg_imgs(v) if "/api/render/svg/" in v else v
                    )
                    if isinstance(v, str) else v
                    for v in valeurs
                ]

        # If the question text has no input/slot widget but the exercise
        # declares replies, append a default input for each so the frontend
        # has somewhere to type the answer (matches WIMS' fallback behaviour).
        # Skip this for dynamic steps exercises (they control visibility per step).
        segments = _segment_statement(html)
        widget_names = {
            s["name"] for s in segments
            if s["type"] in ("input", "slot", "menu", "textarea", "correspond", "draw", "coord")
        }
        # Widgets embedded inside a <table> become native <input>s and don't
        # surface as input segments — count them too so the fallback below
        # doesn't re-append every reply underneath the table.
        widget_names |= _embedded_widget_names(html)
        
        # Extract dynamic steps info
        oefsteps_val = self.ctx.get("oefsteps", "").strip()
        is_dynsteps_var = self.ctx.get("dynsteps", "").strip().lower() == "yes"
        
        if is_dynsteps_var:
            exercise_type = "dynsteps"
        elif oefsteps_val:
            exercise_type = "course"
        else:
            exercise_type = "standard"

        type_meta = {}
        if exercise_type != "standard":
            try:
                type_meta["current_step"] = int(self.ctx.get("m_step", "1"))
            except (ValueError, TypeError):
                type_meta["current_step"] = 1

            # `\nextstep` fait autorité quand il est actif : lui seul sait où
            # l'exercice s'arrête. Les lignes rejouées complètent `oefsteps`,
            # qui ne contient que l'étape courante au premier rendu.
            dynamic_flag: list[bool] = []
            plan = self._resolve_nextstep(df, dynamic_flag)
            # Le rejeu ne fait autorité que s'il a tranché : soit il a trouvé la
            # fin, soit il a établi que la suite dépend des réponses et qu'aucun
            # total n'est annonçable. Sinon — `$nextstep` constant, comme les
            # tables de arithtable.*/table2x2 dont `:postdef` ne touche jamais la
            # variable — on n'a rien appris : ni total, ni étapes à ajouter à
            # `oefsteps`, et les heuristiques de repli reprennent la main.
            nextstep_active = plan is not None and (
                plan[0] is not None or (dynamic_flag and dynamic_flag[0])
            )
            if nextstep_active:
                total, extra = plan
                if total is not None:
                    type_meta["total_steps"] = total
                known = [s for s in re.split(r"[;\n\r\t]+", oefsteps_val) if s.strip()]
                for line in extra:
                    if total is not None and len(known) >= total:
                        break
                    known.append(line)
                if known:
                    oefsteps_val = "\n".join(known)
                    self.ctx["oefsteps"] = oefsteps_val

            # Try to extract total steps from common variable names.
            # 1. Look at oefsteps first
            if not nextstep_active and "total_steps" not in type_meta and oefsteps_val:
                # oefsteps may be tab-, semicolon-, or newline-separated (e.g. "r1\tr2\tr3\tr4")
                steps = re.split(r"[;\n\r\t]+", oefsteps_val)
                steps = [s.strip() for s in steps if s.strip()]
                if steps:
                    type_meta["total_steps"] = len(steps)
            
            # 2. Fall back to other common variables if total_steps still
            # missing. Ce repli devine un total à partir de noms de variables
            # arbitraires (`val62`, `val71`, …) : à ne tenter que faute de mieux.
            if not nextstep_active and "total_steps" not in type_meta:
                for var_name in ("val62", "val71", "cnt", "val61", "val70"):
                    val = self.ctx.get(var_name, "")
                    try:
                        type_meta["total_steps"] = int(val)
                        break
                    except (ValueError, TypeError):
                        # Try counting tab-separated items in the list
                        if "\t" in val:
                            type_meta["total_steps"] = len(val.split("\t"))
                            break
                        continue

        is_dynsteps_flag = exercise_type != "standard"

        # For dynsteps/course exercises, only the answers referenced by the
        # current step's statement are active. `_render_embed` records each
        # reply it sees in `_touched_replies`; we filter `answers` to those.
        # This makes downstream code (hasRadioAnswers, allFilled, check route)
        # naturally correct without per-step bookkeeping.
        if is_dynsteps_flag and self._touched_replies:
            answers = [a for a in answers if a.input_name in self._touched_replies]
        elif is_dynsteps_flag and oefsteps_val:
            # No embed recorded the active replies (embedcnt=0): derive the
            # current step's replies from oefsteps so the right fields appear
            # (simpquot's course step is e.g. "r1,r3" = replies 1 and 3).
            steps = [s.strip() for s in re.split(r"[;\n\r\t]+", oefsteps_val) if s.strip()]
            cur = type_meta.get("current_step", 1)
            if 1 <= cur <= len(steps):
                refs: set[str] = set()
                for tok in steps[cur - 1].split(","):
                    rm = re.fullmatch(r"r(\d+)", tok.strip(), re.I)
                    if rm:
                        refs.add(f"reply{rm.group(1)}")
                    elif tok.strip():
                        refs.add(tok.strip())
                if refs:
                    answers = [a for a in answers if a.input_name in refs]

        text_replies = [
            a for a in answers
            if a.answer_type.lower()
            not in ("radio", "menu", "mark", "correspond", "jsxgraph",
                    "jsxgraphobjet", "geogebra", "jmolclick", "runcode",
                    "js2wims1", "click", "reaction")
        ]
        # Un champ de secours par réponse **que l'énoncé n'a pas embarquée**.
        #
        # C'est la règle de WIMS, et elle se lit en cinq lignes dans
        # `oef/formr.phtml` : le formulaire parcourt `ansorder` et, pour chaque
        # réponse, `!if r$i isitemof $embedded → !exit`, sinon il pose le champ.
        # La décision est **par réponse**, non pour l'énoncé entier.
        #
        # PAX ne l'ajoutait que si l'énoncé ne portait *aucun* widget. Un auteur
        # qui n'embarque qu'une partie de ses champs laissait donc les autres
        # sans nulle part où écrire : `OEFevalwimsgrph/eqalghyper3`, `4` et `5`
        # posent l'embed de leur zone de brouillon et **oublient celui de la
        # réponse** — l'élève voyait le brouillon, et rien pour répondre.
        # Huit autres exercices étaient dans ce cas, dont `oefphotocopie/ex03`
        # (deux champs sur trois) et `oefstatistiques/medicament1`.
        #
        # `widget_names` compte les widgets des tableaux comme ceux des
        # segments (`_embedded_widget_names`), sans quoi ce repli doublerait
        # chaque champ d'un `<table>`.
        orphelines = [a for a in text_replies if a.input_name not in widget_names]
        if orphelines:
            # Le bloc que WIMS pose sous l'énoncé pour les réponses qu'il n'a
            # pas embarquées (`oef/form.phtml`) : un intitulé, puis un champ par
            # réponse précédé de son nom. Le titre ne paraît que s'il reste
            # quelque chose à y mettre — `!if $fieldtot<=$N_ → !goto send`.
            html += (
                f'<div class="oef-enterreply">{_ENTER_REPLY.get(self.lang or "fr", _ENTER_REPLY["fr"])}</div>'
            )
            for a in orphelines:
                # No embed → WIMS renders a default-width reply field. Algebraic
                # answers (litexp/algexp…) can be long expressions
                # (`162sqrt(6)+567`), so give them room; a bare 10 was too narrow
                # (devred). Numeric-ish answers keep a modest default.
                size = 20 if a.answer_type.lower() in _WIDE_FALLBACK_TYPES else 14
                # `<label>$(replyname$i)</label>` précède **toujours** le champ
                # dans les `anstype/<type>.input` — ce n'est pas une commodité
                # quand il y en a plusieurs, c'est le nom que l'auteur donne à
                # la réponse. `eqalghyper3` appelle la sienne « Solution(s) », et
                # sans elle l'élève voit un champ nu sans savoir ce qu'on
                # attend. Le `=` qui suit vient des mêmes fichiers ; `case` et
                # quelques autres s'en passent.
                label = ""
                if a.label and a.label.strip():
                    nom = a.label.strip()
                    # Six exercices ponctuent déjà leur `replyname` — « Hoek: »,
                    # « Mesure de l'angle : ». Y ajouter le nôtre donnait
                    # « antwoord:: ». WIMS écrit `<label>$(replyname$i)</label>=`
                    # sans regarder, mais WIMS n'affiche pas un `=` après un `:`
                    # non plus : c'est l'auteur qui a tranché, on le suit.
                    lien = (
                        ""
                        if nom.endswith((":", "=", "："))
                        else (" =" if a.answer_type.lower() in _EGAL_APRES_LABEL else " :")
                    )
                    label = (
                        f'<label for="{a.input_name}">'
                        f'{_close_inline_math(nom, self.lang)}</label>{lien} '
                    )
                champ = (
                    f'<span class="oef-input" name="{a.input_name}" '
                    f'data-size="{size}"></span>'
                )
                if a.answer_type.lower() in ("set", "fset", "aset"):
                    champ = (
                        f'<span class="oef-set-brace">{{</span>{champ}'
                        f'<span class="oef-set-brace">}}</span>'
                    )
                html += f'<br>{label}{champ}'
            segments = _segment_statement(html)
            widget_names = {
                s["name"] for s in segments if s["type"] in ("input", "slot", "menu")
            }

        # WIMS matrix-bracket notation → LaTeX pmatrix, inside `\(…\)` math.
        # Runs for every locale and *before* the decimal localisation below so
        # a column vector's structural `;`/`,` is consumed while numbers are
        # still dot-decimal (otherwise a localised `1,2` decimal would be split
        # into two columns — see presentation.wims_matrices_to_latex).
        for seg in segments:
            if seg.get("type") == "html":
                seg["content"] = wims_matrices_to_latex(seg["content"])

        # Locale-aware decimal display for the statement (comma-decimal
        # languages): localise bare numbers in the text / table (e.g.
        # `<td>1.21</td>` → `<td>1,21</td>`) and inside `\(…\)` math. The
        # `wims_instruction` block is skipped — it carries the boilerplate
        # "saisir 1.3 pour 1,3" help, whose dot is intentional.
        if uses_comma_decimal(self.lang):
            instr_depth = 0
            for seg in segments:
                if seg.get("type") == "group-open":
                    if "wims_instruction" in (seg.get("class") or ""):
                        instr_depth += 1
                    elif instr_depth:
                        instr_depth += 1
                elif seg.get("type") == "group-close" and instr_depth:
                    instr_depth -= 1
                elif seg.get("type") == "html" and not instr_depth:
                    seg["content"] = localize_decimals(seg["content"], self.lang)

        raw_css = self.ctx.get("oefcss") or self.ctx.get("css", "")
        css = None
        if raw_css:
            css = re.sub(r"</?style[^>]*>", "", raw_css, flags=re.IGNORECASE).strip()

        check_sections = None
        if "postdef" in df.sections or "test" in df.sections or "feedback" in df.sections:
            check_sections = {
                "postdef": df.sections.get("postdef", []),
                "test": df.sections.get("test", []),
                "feedback": df.sections.get("feedback", []),
                "ctx": dict(self.ctx),
                # Le chemin du `.def`, sans quoi le moteur de correction ne sait
                # pas où sont les `slib` du module : `_run_slib` en déduit le
                # répertoire, et sans lui il retourne sans rien faire — en
                # silence, comme le reste du moteur.
                "def_path": self.def_path,
            }

        import html as _html  # noqa: PLC0415
        return ExerciseRender(
            # Decode HTML entities (e.g. "&euro;" → "€") so the title reads as
            # text wherever it is shown plainly (page header, sidebar list).
            title=_html.unescape(self._subst(df.title)),
            lang=df.meta.get("language", "fr"),
            statement_html=html,
            statement_segments=segments,
            answers=answers,
            hint_html=self._render_block_or_text(df.meta.get("hint", ""), df.sections.get("hint", [])),
            solution_html=self._render_block_or_text(df.meta.get("solution", ""), df.sections.get("solution", [])),
            seed=self.seed,
            meta={k: v for k, v in df.meta.items() if k not in ("language",)},
            ev_ctx=dict(self.ctx),
            check_sections=check_sections,
            exercise_type=exercise_type,
            is_dynsteps=is_dynsteps_flag,
            current_step=type_meta.get("current_step"),
            total_steps=type_meta.get("total_steps"),
            type_meta=type_meta,
            css=css,
            severite=self.severite(),
        )

    # ── Instruction execution ─────────────────────────────────────────────────

    def _exec(self, instructions: list, output_buf: list[str] | None) -> None:
        """Execute a list of instructions sequentially."""
        deadline = self._deadline
        for instr in instructions:
            if deadline is not None and time.monotonic() > deadline:
                raise _RenderBudgetExceeded()
            if isinstance(instr, Assign):
                val = self._eval_value(instr.value)
                self.ctx[instr.name] = val
                self.raw_assigns[instr.name] = instr.value

            elif isinstance(instr, Command):
                # Standalone ctx-mutating command (!distribute/!reset/…); the
                # handler substitutes its own args and writes to ctx.
                self._eval_cmd(instr.cmd, instr.args)

            elif isinstance(instr, IfBlock):
                cond = self._eval_condition(instr.kind, instr.condition)
                body = instr.then_body if cond else instr.else_body
                self._exec(body, output_buf)

            elif isinstance(instr, ForLoop):
                self._exec_for(instr, output_buf)

            elif isinstance(instr, WhileLoop):
                # Repeat the body while the (re-evaluated) condition holds; a
                # bound guards against a non-terminating/ill-formed loop.
                guard = 0
                while self._eval_condition("if", instr.condition):
                    self._exec(instr.body, output_buf)
                    guard += 1
                    if guard > 100000:
                        break

            elif isinstance(instr, Output):
                if output_buf is not None:
                    output_buf.append(self._subst(instr.html))

            elif isinstance(instr, Insmath):
                if output_buf is not None:
                    expr = self._subst(instr.expr)
                    output_buf.append(f"\\({expr}\\)")

            elif isinstance(instr, ReadEmbed):
                if output_buf is not None:
                    output_buf.append(self._render_embed(instr.args))

            elif isinstance(instr, ReadProc):
                # Run for its side effects (sets ctx['ins_url'], etc.). La
                # plupart de nos procs ne rendent rien de textuel ; ceux qui
                # produisent du HTML — `oef/img.phtml` en pose une balise
                # `<img>` — le déposent dans `_proc_html`, consommé ici.
                self.ctx.pop("_proc_html", None)
                self._cmd_readproc(f"{instr.path} {instr.args}".strip())
                if output_buf is not None:
                    output_buf.append(self.ctx.pop("_proc_html", ""))

            elif isinstance(instr, ReadDraw):
                # !read oef/draw.phtml ARGS — render a graph and inline it
                # right where the directive sits in the question section.
                self._cmd_readproc(f"oef/draw.phtml {instr.args}")
                url = self.ctx.get("ins_url", "")
                if output_buf is not None and url:
                    output_buf.append(f'<img src="{url}" alt="">')

            elif isinstance(instr, ReadSpecial):
                # !read oef/special.phtml ARGS — an OEF \special. Currently
                # `mathmlinput` (math with inline answer fields) is rendered;
                # other specials produce nothing rather than leaking markup.
                if output_buf is not None:
                    output_buf.append(self._render_special(instr.args))

    def _exec_for(self, loop: ForLoop, output_buf: list[str] | None) -> None:
        """Execute a !for loop — numeric (`X = a to b`) or list (`X in list`)."""
        range_s = self._subst(loop.range_expr)

        # List form: `!for VAR in LIST` — iterate VAR over each item of LIST
        # (tab- or comma-separated). For this form the parser leaves loop.var
        # empty and keeps the whole `VAR in LIST` in range_expr.
        m_in = re.match(r"\$?(\w+)\s+in\s+(.*)", range_s, re.I | re.S)
        if m_in and not re.search(r"\s+to\s+", range_s, re.I):
            var = (loop.var.lstrip("$") or m_in.group(1)).strip()
            items_raw = m_in.group(2).strip()
            # `cutfor` (`evalue.c`) : la virgule de profondeur zéro, items
            # élagués — le `!for … in …` d'un `.def` ne se découpe pas
            # autrement que celui d'un slib ou d'un `!makelist`.
            items = wl.cutitems(items_raw)
            saved = self.ctx.get(var)
            for item in items:
                self.ctx[var] = item.strip()
                self._exec(loop.body, output_buf)
            if saved is not None:
                self.ctx[var] = saved
            else:
                self.ctx.pop(var, None)
            return

        m = re.match(r"(.*?)\s+to\s+(.*)", range_s, re.I)
        if not m:
            return
        borne_haute = m.group(2).strip()
        # `!for v = a to b step s` — `exec_for` cherche le mot `step` dans la
        # borne haute, et prend 1 à défaut. Sans cette lecture, `end` valait
        # `$val16 step 2`, l'évaluation échouait et la boucle **ne tournait pas
        # du tout** : 92 fichiers du corpus emploient cette forme, dont
        # `equilibrium` qui y construit les lignes de son tableau.
        pas_expr = "1"
        m_step = re.match(r"(.*?)\s+step\s+(.*)", borne_haute, re.I)
        if m_step:
            borne_haute, pas_expr = m_step.group(1).strip(), m_step.group(2).strip()
        try:
            start = float(self._eval_arith(m.group(1).strip()))
            end = float(self._eval_arith(borne_haute))
            pas = float(self._eval_arith(pas_expr))
        except (ValueError, TypeError):
            return
        if pas == 0:
            # `module_error("zero_step")` : WIMS interrompt l'exercice. Ne rien
            # exécuter vaut mieux que boucler sans fin.
            return

        var = loop.var.lstrip("$")
        saved = self.ctx.get(var)
        # Les bornes sont des `double` dans le C, et `float2str` écrit un entier
        # sans décimale : `!for q=0 to 360 step 45` donne bien `45`, non `45.0`.
        entier = all(float(x).is_integer() for x in (start, end, pas))
        valeur = start
        # Backstop contre une borne géante à corps vide (le budget temps du
        # rendu ne s'arme que si le corps s'exécute) : cap dur d'itérations.
        for _ in range(100001):
            if (pas > 0 and valeur > end) or (pas < 0 and valeur < end):
                break
            self.ctx[var] = str(int(valeur)) if entier else format_wims_float(valeur)
            self._exec(loop.body, output_buf)
            valeur += pas
        if saved is not None:
            self.ctx[var] = saved
        else:
            self.ctx.pop(var, None)

    def _eval_value(self, value: str) -> str:
        """Evaluate the RHS of an assignment.

        `imgrename(…)` est développé sur le résultat : dans WIMS c'est une
        fonction du calculateur (`calc.c`, table `calc_list`), donc toute
        valeur calculée y passe. Les deux formes que porte le corpus sont ainsi
        couvertes d'un même point — l'appel direct (`val69=imgrename($val1/$val69)`)
        comme celui niché dans un `!makelist`. `!nosubst`, qui coupe le
        calculateur, en est exclu.
        """
        # !cmd — WIMS command
        if value.startswith("!"):
            cmd_line = value[1:].strip()
            cmd, _, args = cmd_line.partition(" ")
            cmd = cmd.lower()
            if cmd == "nosubst":
                return args

            # For other commands, substitute variables first
            args = self._subst(args)
            return calc_imgrename(self._eval_cmd(cmd, args))

        # `$[…]` n'a pas de voie à part : `_subst` l'évalue en premier, puis
        # substitue les variables du reste de la chaîne. La sortie anticipée
        # qui vivait ici rendait la valeur dès le calcul, si bien qu'une
        # concaténation dont le **premier** caractère ouvrait un crochet
        # perdait ses variables suivantes :
        #
        #     insdraw_size=$[rint($slib_size/$slib_ratio)],$slib_size
        #
        # valait `178,$slib_size` — et tous les patrons de polyèdre sortaient
        # à la taille par défaut, faute d'une hauteur lisible.

        # `substit` (`evalue.c`) ne réécrit rien : une concaténation `$a,$b`
        # est une substitution textuelle, séparateur compris. Le cas spécial
        # qui vivait ici — tabulations internes neutralisées, bascule vers un
        # join tabulé pour le HTML à virgules — compensait la priorité
        # tabulation de `_split_items` ; il tombe avec elle.

        # Literal string with variable substitution
        return calc_imgrename(self._subst(value))

    def _eval_dollar_bracket(self, s: str) -> str:
        """Evaluate $[expr] — find the outermost brackets and eval."""
        # May be embedded in a larger string, e.g. "prefix$[expr]suffix"
        result = []
        i = 0
        while i < len(s):
            if s[i] == "$" and i + 1 < len(s) and s[i + 1] == "[":
                end = _find_matching_bracket(s, i + 1, "[", "]")
                expr = s[i + 2 : end]
                result.append(self._eval_arith(expr, strict=self._strict_arith))
                i = end + 1
            else:
                result.append(s[i])
                i += 1
        return "".join(result)

    def _eval_arith(self, expr: str, strict: bool = False) -> str:
        """Evaluate a WIMS arithmetic expression string.

        ``strict`` sépare **afficher** de **noter**, et l'asymétrie est
        délibérée.

        Quand PAX ne sait pas évaluer une expression, il la rend telle quelle.
        Au rendu, c'est le moindre mal : montrer `[2,2,4]*[0.6;0.5;0.7]` est
        laid, mais `NaN` ne vaut pas mieux, et la règle stricte produisait
        `width="nan"` dans le SVG d'`OEFspectres/spectre3` — du SVG invalide là
        où il y avait un nombre. Dix-neuf exercices changeaient d'aspect, aucun
        en mieux.

        À la correction, le même passe-plat est un défaut grave : un `:test`
        qui demande `NaN notin $val19` voit passer la forme symbolique
        `-__faux__ - 7*x + 5` et conclut que la réponse est bonne. Les quatre
        `OEFequdrt/equcond*` **validaient tout**, y compris une chaîne absurde.

        D'où la règle : au rendu on montre ce qu'on a, à la correction un calcul
        raté vaut `NaN` et ne valide rien. `check_analyze` pose le drapeau.
        """
        # 1. Substitute all variable references
        expr = self._subst_for_arith(expr)
        # 1b. An empty function argument — e.g. `rint()` produced when an
        # undefined/empty variable was substituted into `rint($confparm1)` —
        # is a failed numeric calc. WIMS' `$[…]` yields NaN here; returning the
        # literal `rint()` instead would slip past guards like
        # `!ifval NaN isin $x or $x=` (deve7: confparm1 unset → must fall back).
        if re.search(r"[A-Za-z_]\w*\(\s*\)", expr):
            return "NaN"
        # 1c. Un opérande **manquant vaut zéro**, comme dans `Lib/evalue.c` :
        # après un opérateur binaire, l'évaluateur récursif retombe sur
        # `if(*evalue_pt==0) return 0;`. D'où `2+` = 2, `5-` = 5, `3*` = 0 et
        # `2^` = 1 — ce n'est pas « ignorer l'opérateur », c'est lui donner
        # zéro à droite. `/` et `%` font exception : WIMS y lève une division
        # par zéro (`evalue_error=10`), et on laisse alors l'expression telle
        # quelle, qui est la façon dont PAX dit « je n'ai pas su ».
        #
        # `moles.fr/masse2` en dépendait sans qu'on le sache : son
        # `val7=$[rint(2+$val2)]` tire `val2` de `$confparm1`, que
        # l'`introhook` du module n'initialise pas (`!formbar confparm1 from 1
        # to 7`, sans `!default`). L'expression devenait `rint(2+)`, la boucle
        # `!for val18=1 to $val7` ne tournait pas, et les **27 réponses** de
        # l'exercice sortaient sans attendu : l'élève ne pouvait pas avoir
        # juste. Quatre occurrences dans tout le corpus, sur deux exercices.
        expr = re.sub(r"(?<=[-+*^])\s*(?=\)|$)", "0", expr)

        # 2. Replace ^ with ** for Python
        expr = expr.replace("^", "**")
        # 2b. Zéros de tête : le C les lit sans broncher, Python 3 refuse
        # `002` (« leading zeros in decimal integer literals »). Ils arrivent
        # d'une concaténation de chiffres, tout ce qu'il y a de courant —
        # `oefpyramid` fabrique ses nombres par `$[($(tmp0)$(tmp1)$(tmp2))/…]`,
        # et un tirage de 0, 0, 2 donnait `$[(002)/1]`. L'évaluation échouait
        # en silence, l'attendu restait la formule, et aucune réponse ne pouvait
        # valoir 1. On ne touche ni au `0` seul, ni à la partie décimale d'un
        # nombre (`10.02`), ni aux chiffres déjà précédés d'un chiffre.
        expr = re.sub(r"(?<![\d.\w])0+(?=\d)", "", expr)
        # 3. Evaluate
        ns = dict(_MATH_NS)
        # Les fonctions aléatoires de `Lib/evalue.c` tirent sur le générateur
        # **du rendu**, pas sur un global : deux rendus de même graine doivent
        # rendre la même chose, sans quoi ni les snapshots ni `corpus_state`
        # ne voudraient plus rien dire. `slib/matrix/non0` s'en sert
        # (`(random($range)+1)*(2*random(2)-1)`), et sans elles l'expression
        # repartait telle quelle.
        #
        #     double drand(double m) { … return (r/RAND_MAX)*m; }
        #     double irand(double n) { … r = random()*end/RAND_MAX; … }
        ns.update({
            "drand": lambda m=1.0: self.rng.random() * float(m),
            "random": lambda m=1.0: self.rng.random() * float(m),
            "randdouble": lambda m=1.0: self.rng.random() * float(m),
            "randfloat": lambda m=1.0: self.rng.random() * float(m),
            "randreal": lambda m=1.0: self.rng.random() * float(m),
            "rand": lambda m=1.0: self.rng.random() * float(m),
            "irand": lambda n: 0 if int(n) == 0 else self.rng.randrange(abs(int(n))),
            "randint": lambda n: 0 if int(n) == 0 else self.rng.randrange(abs(int(n))),
        })
        # Le contexte, pour les noms de variables nus — mais **seulement ceux
        # que l'expression nomme**. La boucle portait sur tout le contexte :
        # `eval` ne peut lire qu'un nom présent dans l'expression, et convertir
        # les autres était du travail jeté. `oefstatistiques/histocap` appelle
        # cette fonction 7435 fois sur un contexte de plusieurs centaines
        # d'entrées — trois millions de `strip`/`isdigit`, cinq des huit
        # secondes de son rendu.
        for k in set(_IDENT_RE.findall(expr)):
            v = self.ctx.get(k)
            if v is None:
                continue
            s = v.strip()
            try:
                ns[k] = int(s) if s.lstrip("-").isdigit() else float(s)
            except (ValueError, AttributeError):
                ns[k] = s
        try:
            res = eval(expr, ns)  # noqa: S307
            if isinstance(res, float):
                return format_wims_float(res)
            return str(res)
        except ZeroDivisionError:
            # `Lib/evalue.c` — `if(dd==0) {evalue_error=10; return NAN;}`. Même
            # raison que pour l'argument vide plus haut : rendre l'expression
            # littérale la ferait passer pour du texte devant un garde
            # `!ifval NaN isin $x`, alors que WIMS y voit un échec de calcul.
            # `fonctaffin/afeg` divise par `$(val11[…])`, qui se substitue en
            # `-` seul — donc par zéro.
            return "NaN"
        except Exception:
            # Sous `$[…]`, un calcul qui échoue vaut NaN (cf. docstring).
            return "NaN" if strict else expr

    # ── Variable substitution ─────────────────────────────────────────────────

    def _subst(self, s: str) -> str:
        """Substitute all WIMS variable references in a string."""
        if not s or "$" not in s:
            return s
        _var = lambda m: str(self.ctx.get(m.group(1)) if m.group(1) in self.ctx else self.ctx.get(m.group(1).lower(), ""))  # noqa: E731
        # 1. $[expr] blocks first
        s = self._eval_dollar_bracket(s)
        # 1b. Resolve a bare $var that builds the *name* (or subscript) of an
        #     enclosing $(...) — e.g. $(slib_theme$slib_n) → $(slib_theme1),
        #     $(slib_code$jj[2]) → $(slib_code1[2]) — so the indexed/paren
        #     passes below can expand it. Only fires when a $var sits between
        #     a $( and its closing ), leaving $(missing)-style nested *paren*
        #     refs (handled later) and standalone $var untouched.
        if _DOLLAR_IN_PAREN_RE.search(s):
            s = _DOLLAR_VAR_RE.sub(_var, s)
        # 1c. A simple `$var` ref sitting immediately *before* a `$(…)` must be
        #     resolved at this boundary, before the indexed pass expands the
        #     `$(…)`. Otherwise a `$(val31[1])`→"12 a" inserted after an empty
        #     `$val33` would merge into the name ("$val33"+"12 a" → "val3312"),
        #     swallowing the leading digits — WIMS stops the name at the `$`.
        #     (deve7 solution: `($val33$(val31[1])$val34)^2` → `( a)^2`.)
        s = re.sub(r"\$([A-Za-z_]\w*)(?=\$\()", _var, s)
        # 2-4. $(var[n..m]) slices, $(var[n;m]) matrices and $(var[n]) lists,
        #      resolved inner-first to a fixpoint (handles nested subscripts).
        s = self._resolve_indexed_forms(s)
        # 5. $(var) simple reference
        s = _PAREN_VAR_RE.sub(_var, s)
        # 6. $var simple reference (skip $[ which was already handled)
        s = _DOLLAR_VAR_RE.sub(_var, s)
        return s

    def _subst_for_arith(self, expr: str) -> str:
        """Substitute variable references inside an arithmetic expression."""
        if not expr or "$" not in expr:
            return expr
        # Résoudre les `$name` (opérateurs et indices de sous-listes) AVANT les
        # formes indexées `$(var[i])`. Sinon la valeur numérique d'un
        # `$(val15[1])` se colle au `$var` qui précède et le corrompt en un
        # nouveau nom : `$val18$val19$(val15[1])` (val19="-") donnait `$val18` +
        # `$val193`(inconnu→0) = `rint(30)` au lieu de `rint(3-3)` (mediane5).
        expr = _DOLLAR_VAR_RE.sub(lambda m: str(self.ctx.get(m.group(1)) if m.group(1) in self.ctx else self.ctx.get(m.group(1).lower(), "0")), expr)
        expr = self._resolve_indexed_forms(expr)
        expr = _PAREN_VAR_RE.sub(lambda m: str(self.ctx.get(m.group(1)) if m.group(1) in self.ctx else self.ctx.get(m.group(1).lower(), "0")), expr)
        return expr

    def _resolve_indexed_forms(self, s: str) -> str:
        """Resolve $(var[n..m]), $(var[n;m]) and $(var[n]) inner-first.

        Subscripts exclude "(" (see the regex definitions), so a nested
        reference like $(val14[$m_h;$(val11[$m_h])]) only matches its inner
        $(val11[…]) on the first pass; once that is gone the outer matrix
        form matches on the next pass. We loop to a fixpoint (a small bound
        guards against pathological input) instead of a fixed pass count.
        """
        if "$(" not in s:
            return s
        for _ in range(8):
            before = s
            s = _RANGE_SLICE_RE.sub(self._resolve_range_slice, s)
            s = _INDEXED2_RE.sub(self._resolve_indexed2, s)
            s = _INDEXED1_RE.sub(self._resolve_indexed1, s)
            # Collapse *defined* simple `$(var)` refs too: subscripts exclude
            # `$(`, so a simple ref nested in a subscript (e.g. the row index in
            # `$(val8[$(tmp0);])`) would otherwise never disappear and the outer
            # matrix form could never match. Undefined names are left as-is so
            # the caller's final pass applies its own default ("" vs "0").
            s = _PAREN_VAR_RE.sub(
                lambda m: str(self.ctx[m.group(1)]) if m.group(1) in self.ctx
                else (str(self.ctx[m.group(1).lower()]) if m.group(1).lower() in self.ctx
                      else m.group(0)),
                s,
            )
            if s == before:
                break
        return s

    def _resolve_range_slice(self, m: re.Match) -> str:
        """Resolve $(var[n..m]) — items n through m as a comma list.

        Bounds can be expressions (e.g. `$val6`, `$val6+1`); they're
        substituted and evaluated via `_eval_arith` before slicing.
        """
        name, start_s, end_s = m.group(1), m.group(2), m.group(3)
        value = self.ctx.get(name, self.ctx.get(name.lower(), ""))
        if not value:
            return ""
        try:
            start = int(round(float(self._eval_arith(self._subst_for_arith(start_s)))))
            end = int(round(float(self._eval_arith(self._subst_for_arith(end_s)))))
        except (ValueError, TypeError):
            return ""
        items = wl.cutitems(value)
        # WIMS indices are 1-based and a negative index counts from the end with
        # -1 = the *last* item, **inclusive** (`[2..-1]` = item 2 through the
        # last). Python's `items[1:-1]` would drop the last, so map a negative
        # end to its inclusive Python bound (-1 → None, -2 → -1, …).
        py_end: int | None = end
        if end < 0:
            py_end = end + 1 or None
        return ",".join(items[start - 1 : py_end])

    def _resolve_indexed1(self, m: re.Match) -> str:
        """`$(var[n])` — n-ième item, ou sous-liste si `n` est une liste.

        Découpage par `cutitems` : la virgule seule sépare, à profondeur zéro.
        Le `;` n'est pas une frontière d'item — c'en est une de *ligne de
        matrice* —, et le prendre pour tel hachait les tableaux JSXGraph de
        `couf`, dont le JavaScript en est truffé.
        """
        name, idx_expr = m.group(1), m.group(2)
        value = self.ctx.get(name, self.ctx.get(name.lower(), ""))
        if not value:
            return ""
        idx_s = self._subst_for_arith(idx_expr)
        items = wl.cutitems(value)

        try:
            idx = int(round(float(self._eval_arith(idx_s))))
            if 1 <= idx <= len(items):
                return items[idx - 1]
            # Indice négatif WIMS : -1 = dernier item.
            if -len(items) <= idx <= -1:
                return items[idx]
            return ""
        except (ValueError, TypeError):
            pass

        # Liste d'indices : `$(var[$liste])` avec `$liste = "5,4"` rend les
        # items 5 et 4, joints par des virgules.
        result_items = []
        for part in wl.cutitems(idx_s):
            try:
                idx = int(round(float(self._eval_arith(part))))
            except (ValueError, TypeError):
                continue
            if 1 <= idx <= len(items):
                result_items.append(items[idx - 1])
        return ",".join(result_items)

    def _resolve_indexed2(self, m: re.Match) -> str:
        """`$(var[lignes;colonnes])` — port de `substit` (`evalue.c:109-131`).

        Le C n'a pas de code d'indexation à lui : il **réécrit la référence en
        commandes**. `$(v[l;c])` devient `calc_rowof("l of $v")` — ou la valeur
        entière si la partie lignes est vide — puis `calc_columnof("c of …")`
        si la partie colonnes ne l'est pas. Et `calc_columnof` est lui-même un
        `rows2lines` suivi d'un `calc_itemof` par ligne.

        D'où la règle qui tenait lieu de bug ici : une « cellule » se termine à
        la virgule, jamais au `;` — celui-ci a déjà été consommé comme fin de
        ligne. Et la tabulation ne sépare rien du tout.
        """
        name, row_expr, col_expr = m.group(1), m.group(2), m.group(3)
        value = self.ctx.get(name, self.ctx.get(name.lower(), ""))
        if not value:
            return ""
        row_s = self._subst_for_arith(row_expr).strip()
        col_s = self._subst_for_arith(col_expr).strip()

        tbuf = self._rowof(row_s, value) if row_s else value
        return self._columnof(col_s, tbuf) if col_s else tbuf

    def _columnof(self, idx_s: str, data: str) -> str:
        """`!column I of MATRICE` — port de `calc_columnof` (`calc.c`).

        `rows2lines` d'abord, puis un `calc_itemof` par ligne. Le séparateur de
        sortie suit trois règles, dans cet ordre : `;` si `rows2lines` a
        converti quelque chose, `\n` sinon — mais `,` dès que l'indice demandé
        est **unique** (ni virgule, ni `to`, ni `..`), parce qu'une colonne
        simple est une liste d'items, pas une matrice.
        """
        converted, count = wl.rows2lines(data)
        sep = ";" if count else "\n"
        if "," not in idx_s and ".." not in idx_s and not re.search(r"\bto\b", idx_s):
            sep = ","
        return sep.join(self._itemof(idx_s, line) for line in wl.cutlines(converted))

    # ── Condition evaluation ──────────────────────────────────────────────────

    def _eval_condition(self, kind: str, condition: str) -> bool:
        """Evaluate a !if or !ifval condition (port of WIMS compare.c).

        Pass ``self._subst`` so substitution happens *after* operator
        identification — matches compare.c's late ``substitute(buf1/buf2)``
        and prevents a `<`/`>` inside a substituted HTML value (e.g. a
        ``$val6`` instruction div) from being parsed as a relational op.
        """
        return _wims_compare(condition, numeric=(kind == "ifval"), subst=self._subst)

    def _eval_loop_expr(self, expr: str, var: str, val: str) -> str:
        """Evaluate a loop body expression, substituting the loop variable."""
        # Substitute bare loop variable (e.g. 'x' in 'reply x')
        # We use a regex to match the variable name as a whole word
        res = re.sub(rf"\b{re.escape(var)}\b", val, expr)
        # Also handle standard substitution (for other variables)
        res = self._subst(res.replace("\\", "$"))
        
        # If it looks like arithmetic, try to eval it
        if any(c in res for c in "+-*/^"):
            try:
                # Use a dummy namespace with common math functions
                ns = dict(_MATH_NS)
                # Also inject all current ctx
                for k, v in self.ctx.items():
                    try: ns[k] = float(v)
                    except: ns[k] = v
                
                eval_res = eval(res.replace("^", "**"), ns)
                if isinstance(eval_res, float):
                    return format_wims_float(eval_res)
                if isinstance(eval_res, int):
                    return str(eval_res)
            except:
                pass
        return res

    # ── Commands ──────────────────────────────────────────────────────────────

    def _eval_cmd(self, cmd: str, args: str) -> str:
        """Evaluate a WIMS !cmd and return the result as a string."""
        args = args.strip()

        # Modificateur WIMS `… repeat N` : exécute la commande N fois et joint
        # les résultats par des virgules. Utilisé par les tirages aléatoires
        # (`!randint N,M repeat K`, cf. slib/stat/random). Restreint à la famille
        # aléatoire pour ne pas confondre un « repeat » textuel ; N est évalué.
        if cmd in ("randint", "random", "randitem", "randword", "randchar", "randrow"):
            rep_m = re.match(r"^(.*\S)\s+repeat\s+(\S+)\s*$", args, re.DOTALL)
            if rep_m:
                try:
                    n = int(round(float(self._eval_arith(rep_m.group(2)))))
                except (ValueError, TypeError):
                    n = None
                if n is not None and n >= 1:
                    base = rep_m.group(1).strip()
                    return ",".join(self._eval_cmd(cmd, base) for _ in range(n))

        if cmd == "randint":
            return self._cmd_randint(args)

        if cmd == "random":
            return self._cmd_random(args)

        if cmd == "randitem":
            return self._cmd_randitem(args)

        if cmd == "nonempty":
            return self._cmd_nonempty(args)

        if cmd == "shuffle":
            return self._cmd_shuffle(args)

        if cmd == "item":
            return self._cmd_item(args)

        if cmd in ("row", "rows"):
            return self._cmd_row(args)

        if cmd == "itemcnt":
            # `itemnum` (`liblines.c`) : la virgule seule sépare, à profondeur
            # zéro, et **les items vides comptent** — `a,,b` en vaut 3. WIMS ne
            # fournirait pas `!nonempty items` si `!itemcnt` les ignorait de
            # lui-même, et les trous portent du sens : les colonnes sans signe
            # d'un tableau de variation (`x,reply1,,reply2,,reply3`) en sont.
            # Une chaîne vide en compte 0.
            return str(wl.itemnum(self._subst(args)))

        if cmd in ("rowcnt", "rowcount", "rowno", "rownum"):
            val = self._subst(args)
            return str(len(wl.cutrows(val)))

        if cmd == "trim":
            return self._subst(args).strip()

        if cmd == "lower":
            return self._subst(args).lower()

        if cmd == "upper" or cmd == "uppercase":
            return self._subst(args).upper()

        if cmd == "replace":
            return self._cmd_replace(args)

        if cmd == "translate":
            return self._cmd_translate(args)

        if cmd == "append":
            return self._cmd_append(args)

        if cmd == "exec":
            return self._cmd_exec(args)

        if cmd == "rawmath":
            # `!rawmath` normalises a math expression, keeping it in a form
            # suitable for downstream evaluation (`pari print()`, plotting).
            # NOT a LaTeX conversion — that's `!texmath`.
            # Mirrors WIMS' __replace_plusminus (rawmath.c) which collapses
            # any run of +/- (possibly separated by whitespace) into a
            # single sign. Without this, substituting a negative variable
            # into `$a - $b` produces `3 - -6` instead of `3 + 6`.
            expr = self._subst(args)
            def _collapse(m: re.Match) -> str:
                signs = re.findall(r"[+-]", m.group(0))
                return "-" if signs.count("-") % 2 == 1 else "+"
            expr = re.sub(r"[+-](\s*[+-])+", _collapse, expr)
            return expr

        if cmd == "texmath":
            s = self._subst(args)
            # A top-level comma list (e.g. the solution set `-1,0`) is a *list*,
            # not a tuple: render each element and join with the locale list
            # separator — WIMS never wraps it in parentheses (the `{…}` braces
            # come from the template). Commas inside ()/[]/{} (function args,
            # an explicit point `(a,b)`) stay put. ``;`` in comma-decimal
            # locales also avoids KaTeX reading `-1,0` as one decimal.
            parts = _split_top_level(s, ",")
            if len(parts) > 1 and all(p.strip() for p in parts):
                sep = list_separator(self.lang)
                return sep.join(_expr_to_latex(p.strip()) for p in parts)
            return _expr_to_latex(s)

        if cmd == "insmath":
            return self._subst(args)

        if cmd == "nosubst":
            return args

        if cmd == "values":
            return self._cmd_values(args)

        if cmd == "makelist":
            return self._cmd_makelist(args)

        if cmd == "positionof":
            return self._cmd_positionof(args)

        if cmd in ("randrow", "randitem_row"):
            return self._cmd_randrow(args)

        if cmd == "sort":
            return self._cmd_sort(args)

        if cmd == "mathsubst":
            # !mathsubst x=1 in x^2+x -> 1^2+1
            m = re.match(r"(.*?)\s+in\s+(.*)", args, re.I | re.DOTALL)
            if not m:
                return self._subst(args)
            subst_list = self._subst(m.group(1)).strip()
            expr = self._subst(m.group(2)).strip()
            for part in subst_list.split(","):
                if "=" in part:
                    k, v = part.split("=", 1)
                    k, v = k.strip(), v.strip()
                    # case-insensitive match for the variable key
                    expr = re.sub(rf"\b{re.escape(k)}\b", v, expr, flags=re.IGNORECASE)
            return expr

        if cmd == "solve":
            return self._cmd_solve(args)

        if cmd == "listuniq":
            return self._cmd_listuniq(args)

        if cmd == "listintersect":
            return self._cmd_listintersect(args)

        if cmd == "declosing":
            return self._cmd_declosing(args)

        if cmd == "nospace":
            return re.sub(r"\s+", "", self._subst(args))

        if cmd == "getopt":
            return self._cmd_getopt(args)

        if cmd in ("varlist", "listvar"):
            return self._cmd_varlist(args)

        if cmd == "getdef":
            return self._cmd_getdef(args)

        if cmd == "embraced":
            return self._cmd_embraced(args)

        if cmd == "word":
            return self._cmd_word(args)

        if cmd == "column":
            return self._cmd_column(args)

        if cmd in ("charcnt", "charcount", "charno", "charnum", "lengthof"):
            return str(len(self._subst(args).strip()))

        # ── Missing aliases for already-implemented commands ──────────────────
        if cmd in ("tolower", "lowercase"):
            return self._subst(args).lower()

        if cmd in ("toupper", "uppercase"):
            return self._subst(args).upper()

        if cmd in ("randperm", "randpermute"):
            return self._cmd_shuffle(args)

        # ── Line-based access (like !item but for newline-separated data) ─────
        if cmd in ("line", "lines"):
            return self._cmd_line(args)

        if cmd in ("linecnt", "linecount", "lineno", "linenum"):
            s = self._subst(args)
            n = len([l for l in s.splitlines() if l.strip()])
            return str(n) if n else "0"

        # ── Character access ──────────────────────────────────────────────────
        if cmd in ("char", "chars"):
            return self._cmd_char(args)

        # ── Word count ────────────────────────────────────────────────────────
        if cmd in ("wordcnt", "wordcount", "wordno", "wordnum"):
            return str(len(self._subst(args).split()))

        # ── Arithmetic aggregate ──────────────────────────────────────────────
        if cmd in ("add", "sum"):
            return self._cmd_sum(args)

        if cmd in ("multiply", "prod", "product"):
            return self._cmd_product(args)

        # ── List set operations ───────────────────────────────────────────────
        if cmd in ("listunion",):
            return self._cmd_listunion(args)

        if cmd in ("listcomplement",):
            return self._cmd_listcomplement(args)

        # ── Conversion: items ↔ lines ↔ words ────────────────────────────────
        if cmd in ("items2lines", "itemstolines", "list2lines", "listtolines"):
            s = self._subst(args)
            # Virgules protégées par les crochets : `[a,b],[c,d]` → 2 lignes,
            # pas 6 (slib/stat/dataproc sépare `[data],[poids]`).
            return "\n".join(x.strip() for x in wl.cutitems(s) if x.strip())

        if cmd in ("lines2items", "linestoitems", "lines2list", "linestolist"):
            s = self._subst(args)
            return ",".join(x.strip() for x in s.splitlines() if x.strip())

        if cmd in ("words2items", "wordstoitems", "words2list", "wordstolist"):
            s = self._subst(args)
            return ",".join(s.split())

        if cmd in ("items2words", "itemstowords", "list2words", "listtowords"):
            s = self._subst(args)
            return " ".join(x.strip() for x in s.split(",") if x.strip())

        if cmd in ("lines2words", "linestowords"):
            s = self._subst(args)
            return " ".join(x.strip() for x in s.splitlines() if x.strip())

        if cmd in ("words2lines", "wordstolines"):
            s = self._subst(args)
            return "\n".join(s.split())

        if cmd in ("rows2lines",):
            s = self._subst(args)
            if "\n" not in s and ";" in s:
                return "\n".join(x.strip() for x in s.split(";"))
            return "\n".join(x.strip() for x in s.split("\t") if x.strip())

        if cmd in ("lines2rows",):
            s = self._subst(args)
            return "\t".join(x.strip() for x in s.splitlines() if x.strip())

        # ── String normalisation ──────────────────────────────────────────────
        if cmd in ("singlespace",):
            return re.sub(r"\s+", " ", self._subst(args)).strip()

        if cmd in ("detag",):
            return re.sub(r"<[^>]*>", "", self._subst(args))

        if cmd in ("deaccent",):
            import unicodedata
            s = self._subst(args)
            return "".join(
                c for c in unicodedata.normalize("NFD", s)
                if unicodedata.category(c) != "Mn"
            )

        # ── Random variants ───────────────────────────────────────────────────
        if cmd in ("randword",):
            return self._cmd_randword(args)

        if cmd in ("randline",):
            return self._cmd_randline(args)

        if cmd in ("randchar",):
            s = self._subst(args)
            return self.rng.choice(list(s)) if s else ""

        # ── Arithmetic evaluation ─────────────────────────────────────────────
        if cmd in ("evalue", "eval"):
            try:
                result = self._eval_arith(self._subst(args))
                v = float(result)
                if v == int(v):
                    return str(int(v))
                return f"{v:.6g}"
            except Exception:
                return "0"

        # ── Explicit substitution (no-op: subst already done by caller) ───────
        if cmd in ("subst", "substit", "substitute"):
            return self._subst(args)

        # ── Record access (WIMS datafiles : records séparés par \n:) ─────────
        if cmd in ("record", "records"):
            return self._cmd_record(args)

        if cmd in ("recordcnt", "recordcount", "recordno", "recordnum"):
            return self._cmd_recordcnt(args)

        if cmd in ("rename",):
            return self._cmd_rename(args)

        # `randfile` et `randrecord` sont **la même fonction** dans la table de
        # `calc.c` — les deux noms y pointent sur `calc_randfile` (lignes 2393
        # et 2402). Seul `randrecord` était routé, si bien que le
        # `!randfile $val2.dat` de `chemavance1` rendait le vide : son équation
        # de réaction n'était jamais tirée, et le tableau d'avancement partait
        # d'une équation vide.
        if cmd in ("randfile", "randrecord"):
            return self._cmd_randrecord(args)

        # ── Slib helper commands (mutate self.ctx, return empty string) ────────
        if cmd in ("distribute",):
            self._cmd_distribute(args)
            return ""

        if cmd in ("bound",):
            self._cmd_bound(args)
            return ""

        if cmd in ("default",):
            self._cmd_default(args)
            return ""

        if cmd in ("advance", "increase"):
            self._cmd_advance(args)
            return ""

        if cmd in ("reset",):
            self._cmd_reset(args)
            return ""

        # ── Select rows by condition ──────────────────────────────────────────
        if cmd in ("select",):
            return self._cmd_select(args)

        # ── Remaining calc.c commands ─────────────────────────────────────────
        if cmd in ("listintersection",):
            return self._cmd_listintersect(args)

        if cmd in ("date",):
            import datetime
            fmt = self._subst(args).strip() or "+%Y-%m-%d"
            fmt = fmt.lstrip("+")
            try:
                return datetime.datetime.now().strftime(fmt)
            except Exception:
                return datetime.datetime.now().strftime("%Y-%m-%d")

        if cmd in ("htmlmath", "math2html"):
            # PAX uses KaTeX on the frontend; return the LaTeX expression wrapped
            # in \(...\) so the frontend can render it.
            expr = self._subst(args)
            return f"\\({expr}\\)"

        if cmd in ("lookup",):
            return self._cmd_lookup(args)

        if cmd in ("text",):
            return self._cmd_text(args)

        if cmd in ("solve", "rootof"):
            return self._cmd_solve(args)

        if cmd == "insdraw":
            return self._cmd_insdraw(args)

        if cmd in ("read", "readproc"):
            # `exec_readproc` n'est que `exec_read` la sortie coupée :
            #
            #     void exec_readproc(char *p)
            #     { int o=outputing; outputing=0; exec_read(p); outputing=o; }
            #
            # Les `!read` d'un `.def` sont typés au parsing (embed, draw,
            # special…), mais ceux que portent les **slib** arrivaient ici sans
            # être reconnus : `slib/chemistry/jmolshow` lit son
            # `jmolshow_init` par `!read`, et le `UNKNOWN_CMD:read` s'affichait
            # dans l'énoncé, sous les yeux de l'élève. Le HTML éventuel du
            # fichier lu est rendu, ce qui distingue `read` de `readproc`.
            self.ctx.pop("_proc_html", None)
            self._cmd_readproc(args)
            html = self.ctx.pop("_proc_html", "")
            return html if cmd == "read" else ""

        return f"UNKNOWN_CMD:{cmd}"

    def _cmd_randint(self, args: str) -> str:
        """!randint a, b — random integer in [a, b]; !randint N — in [1, N]."""
        # Split at top-level commas only: a bound may itself be a call with
        # commas, e.g. `!randint 3, min(9,$L)` (0923) — a plain split(",")
        # would shred `min(9,10)` into "min(9" / "10)" and fail → "0".
        parts = [self._subst(p.strip()) for p in _split_top_level_args(args)]
        try:
            a = int(round(float(self._eval_arith(parts[0]))))
            if len(parts) == 1:
                # `calc_randint` : « Missing ubound: random between +-1 and
                # lbound » — l'autre borne est 1, ou -1 si la première est
                # négative. `!randint -3` tire donc dans [-3, -1], quand
                # `randint(1, -3)` levait ici une ValueError et rendait 0.
                b = -1 if a < 0 else 1
            else:
                b = int(round(float(self._eval_arith(parts[1]))))
            # `if(lbound>ubound) {i=lbound; lbound=ubound; ubound=i;}` — WIMS
            # **échange** les bornes inversées plutôt que d'abandonner. Sans
            # cela, le `!randint 2, $val17-1` de `chiffres3`, dont la seconde
            # borne peut tomber à 1, levait une ValueError et rendait 0 — d'où
            # un nombre de chiffres significatifs nul, et tout un exercice de
            # volumes à zéro.
            if a > b:
                a, b = b, a
            return str(self.rng.randint(a, b))
        except (ValueError, TypeError, IndexError):
            return "0"

    def _cmd_random(self, args: str) -> str:
        """!random a, b — random float in [a, b]."""
        parts = [self._subst(p.strip()) for p in _split_top_level_args(args)]
        if len(parts) < 2:
            return "0"
        try:
            a = float(self._eval_arith(parts[0]))
            b = float(self._eval_arith(parts[1]))
            return f"{self.rng.uniform(a, b):.4f}"
        except (ValueError, TypeError):
            return "0"

    def _cmd_randitem(self, args: str) -> str:
        """``!randitem item1, item2, …`` — en tire un au sort.

        Port de `calc_randitem` : `itemnum` puis `fnd_item`. Les items vides
        comptent donc dans le tirage, et un item entre crochets reste entier.
        """
        val = self._subst(args)
        n = wl.itemnum(val)
        if n <= 0:
            return ""
        return wl.fnd_item(val, self.rng.randrange(n) + 1)

    def _cmd_nonempty(self, args: str) -> str:
        """``!nonempty items|lines|rows LISTE`` — retire les entrées vides.

        Port de `calc_nonempty`. Les `rows` passent par `rows2lines` ; **si
        rien n'est converti**, WIMS bascule sur le traitement des lignes — d'où
        le repli explicite ci-dessous. `words` est une extension PAX (absente
        de `calc.c`), conservée faute d'avoir mesuré ses appelants.
        """
        m = re.match(r"(items?|rows?|lines?|words?)\s*(.*)", args, re.I | re.DOTALL)
        if not m:
            return self._subst(args)
        kind = m.group(1).lower()
        val = self._subst(m.group(2))

        if kind.startswith("word"):
            return " ".join(w for w in val.split() if w)
        if kind.startswith("row"):
            converted, n = wl.rows2lines(val)
            if n:
                return ";".join(x for x in wl.cutlines(converted) if x.strip())
            kind = "lines"
        if kind.startswith("line"):
            return "\n".join(x for x in wl.cutlines(val) if x.strip())
        return ",".join(x for x in wl.cutitems(val) if x)

    def _cmd_shuffle(self, args: str) -> str:
        """``!shuffle LISTE`` ou ``!shuffle N`` — permutation aléatoire.

        Port de `calc_randperm` : c'est la présence d'une **virgule de premier
        niveau** qui fait la liste (`p1=find_item_end(pp); if(*p1==',')`) ;
        sinon l'argument est évalué et l'on permute `1..n`. Sortie en virgules,
        items vides conservés.

        Les options `even`/`odd` et la variable `wims_shuffle_order` publiée
        par WIMS ne sont pas gérées (cf. `docs/refactor-item-splitting.md`).
        """
        val = self._subst(args.strip())
        if wl.find_item_end(val) < len(val):
            items = wl.cutitems(val)
            self.rng.shuffle(items)
            return ",".join(items)
        try:
            n = int(round(float(self._eval_arith(val))))
        except (ValueError, TypeError):
            return val
        if n <= 1:
            return val if n == 1 else ""
        items = [str(i) for i in range(1, n + 1)]
        self.rng.shuffle(items)
        return ",".join(items)

    def _cmd_item(self, args: str) -> str:
        """!item I of list — 1-indexed item, or list of items.

        ``I`` may be a single index, a ``N to M`` range, or a comma-separated
        list of indices.
        """
        m = re.match(r"(.+?)\s+of\s*(.*)", args, re.DOTALL | re.I)
        if not m:
            return ""
        return self._itemof(self._subst(m.group(1).strip()),
                            self._subst(m.group(2).strip()))

    def _itemof(self, idx_s: str, data: str) -> str:
        """`calc_itemof` sur des opérandes **déjà substituées**.

        Séparé de `_cmd_item` parce que `substit` (`evalue.c`) réécrit
        `$(v[l;c])` en `calc_rowof`/`calc_columnof`, qui appellent à leur tour
        `calc_itemof` : la valeur y arrive substituée, et la resubstituer
        rejouerait les `$` qu'elle contient.

        Toute la sélection — plage, liste, indice négatif — vit dans
        `_blockof`, comme dans le C où `calc_itemof` n'est qu'un appel avec
        `itemnum`/`fnd_item`.
        """
        # `append_char` vaut `", "` — virgule **et espace** —, pas `","` :
        # `_blockof(p,itemnum,fnd_item,", ","item")`. C'est le seul des cinq
        # sélecteurs à en porter un ; il ne se voit que quand `!item` rend
        # plusieurs items, et l'espace est élagué au prochain découpage.
        return self._blockof(data, wl.cutitems, ", ", idx_s)

    def _cmd_row(self, args: str) -> str:
        """!row I of matrix — ligne(s) I, séparateur auto.

        `calc_rowof` passe par le `_blockof` commun à `!item`/`!line` : `I` peut
        donc être une plage (`3 to -1`) ou une liste (`1,3`) autant qu'un indice.
        Le séparateur de sortie est celui d'entrée, comme dans `calc.c` (`;`
        quand la matrice n'a pas de saut de ligne mais des points-virgules).
        """
        m = re.match(r"(.+?)\s+of\s*(.*)", args, re.DOTALL | re.I)
        if not m:
            return ""
        return self._rowof(self._subst(m.group(1).strip()),
                           self._subst(m.group(2).strip()))

    def _rowof(self, idx_s: str, data: str) -> str:
        """`calc_rowof` sur des opérandes déjà substituées (cf. `_itemof`)."""
        # `;` si la matrice n'a pas de saut de ligne mais en porte un, `\n`
        # dans tous les autres cas — il n'y a pas de troisième branche, et
        # surtout pas de tabulation.
        sep = ";" if ("\n" not in data and ";" in data) else "\n"
        return self._blockof(
            data, lambda s: [r.strip() for r in wl.cutrows(s)], sep, idx_s
        )

    def _cmd_replace(self, args: str) -> str:
        """!replace [internal/word] A by B in text.

        Sans le préfixe `internal`, et dès que l'un des deux motifs porte un
        caractère de `\\[^.*$`, WIMS ne remplace pas du texte : il lance **sed**
        (`calc.c:calc_replace`) —

            if(internal || … || (strpbrk(bf[0],"\\\\[^.*$")==NULL &&
                                 strpbrk(bf[1],"\\\\[^.*$")==NULL)) {
              /* No regexp, direct replace */

        — sur `s/<motif>/<par>/g`. C'est ce qui donne son sens à
        `!replace [0-9] by $ in F4` (retirer les chiffres) ou à
        `!replace \\^ by ** in x^2`. Traités littéralement, ces motifs ne
        trouvaient jamais rien : `slib/chemistry/molecule` en tirait un nombre
        d'atomes égal au symbole (`U,Uranium,…` au lieu de `1,Uranium,…`), et
        la masse molaire d'`UF4` sortait en `0+U*238.03+F4*`.
        """
        # Standard: !replace internal x by y in text
        # Shortcut: !replace x by y in text (defaults to internal)
        # `\s+in\s*` (pas `\s+in\s+`) : le texte cible peut être vide quand un
        # `$var` substitué est vide (`!replace internal , by + in $vide` →
        # texte ""). Sinon le regex échoue et la commande fuite en littéral
        # (`internal , by + in`) dans la valeur calculée (moyenneB2).
        m = re.match(r"(internal|word)\s+(.*?)\s+by\s+(.*?)\s+in\s*(.*)", args, re.I | re.DOTALL)
        if m:
            mode, old, new, text = m.groups()
        else:
            # Sans préfixe : ni `internal` ni `word`. La nuance compte, c'est
            # `internal` qui coupe la voie regexp.
            m = re.match(r"(.*?)\s+by\s+(.*?)\s+in\s*(.*)", args, re.I | re.DOTALL)
            if m:
                mode, old, new, text = "", m.group(1), m.group(2), m.group(3)
            else:
                # Empty replacement: `!replace internal , by in $text` deletes
                # every comma (interint3 strips the clickfill list separators
                # from the displayed interval). Optional `internal|word` prefix
                # must be consumed so `old` is just `,`, not `internal ,`.
                m = re.match(
                    r"(?:(internal|word)\s+)?(.*?)\s+by\s+in\s+(.*)",
                    args, re.I | re.DOTALL,
                )
                if m:
                    mode, old, new, text = (m.group(1) or ""), m.group(2), "", m.group(3)
                else:
                    return self._subst(args)
        
        # Motif vide → aucune occurrence à remplacer. WIMS ne fait rien ; Python
        # insérerait le remplacement entre *chaque* caractère (`"ab".replace("",
        # "X")` vaut `"XaXbX"`). `slib/function/tabsignes` écrit
        # `!replace internal $empty by \qquad \qquad in $slib_cel` pour espacer
        # les cellules vides, ce qui hachait toutes les autres : son marqueur
        # `reply1` ressortait en `\qquad r\qquad e\qquad p\qquad l\qquad y…`.
        # `by $` — un dollar seul — nomme la variable de nom **vide**, que
        # `substit` (`evalue.c`) résout comme n'importe quelle autre : sa
        # boucle `for(p2=pp+1; myisalnum(*p2)…)` s'arrête aussitôt, le nom est
        # vide, et le `$` disparaît. C'est ainsi que
        # `!replace [0-9] by $ in $slib_mol` retire les chiffres, et
        # `!replace internal : by $ in $error` les deux-points. Les neuf
        # occurrences du corpus ont toutes ce sens. La règle n'est pas portée
        # dans `_subst` : les 14 000 `$ ` du corpus y sont d'abord les
        # délimiteurs de `!translate internal $…$`.
        # Le même `$…$` sert aussi de **délimiteur** autour d'une valeur que les
        # espaces de bord perdraient — `!translate` le déballe déjà. `substit`
        # y arrive par le même chemin : chaque `$` ouvre un nom qui s'arrête au
        # premier caractère non alphanumérique, donc vide, donc effacé, et il
        # ne reste que ce qu'ils encadrent. `slib/lang/swac` écrit ainsi
        #
        #     slib_word=!replace internal " by $\
        #     $ in $slib_word
        #
        # pour couper ses mots sur les guillemets : le remplacement est un saut
        # de ligne. Pris littéralement, il insérait `$\n$` et le mot cherché
        # devenait `$` — aucun des dix-huit appels allemands ne trouvait son son.
        def _deballer(s: str) -> str:
            t = s.strip()
            if t == "$":
                return ""
            if len(t) >= 2 and t.startswith("$") and t.endswith("$"):
                return t[1:-1]
            return s

        old = _deballer(old)
        new = _deballer(new)
        if not old:
            return text
        if mode.lower() == "word":
            # Escape old for regex if using word mode
            return re.sub(rf"\b{re.escape(old)}\b", new, text)
        if not mode and _PORTE_UN_METACARACTERE(old, new):
            substitue = _sed_substitution(old, new)
            if substitue is not None:
                return substitue(text)
        return text.replace(old, new)

    def _cmd_translate(self, args: str) -> str:
        """!translate A to B in text — character-wise translation (port of calc.c calc_translate).

        WIMS allows $CHARS$ as a dollar-delimited character set, e.g.
        ``!translate internal $\\t\\n$ to ;; in $src`` translates each tab or
        newline to a semicolon.  The surrounding ``$`` are delimiters, not
        characters to translate.
        """
        m = re.match(r"(?:internal\s+)?(.*?)\s+to\s+(.*?)\s+in\s*(.*)", args, re.I | re.DOTALL)
        if not m:
            return self._subst(args)
        a_raw, b_raw, text_raw = m.groups()

        # Strip $...$ delimiters from character set (WIMS quoting for whitespace/special chars).
        # WIMS applique `substit()` aux deux opérandes de la même façon
        # (`calc.c:calc_translate`), donc le déballage vaut aussi pour la
        # cible : `!translate internal ; to $\<LF>$` remplace `;` par un saut
        # de ligne. Sans cela, `slib/stat/dataproc` collait données et
        # effectifs en une seule liste (`1,4,6$2,3,3`), `slib_weight` restait
        # vide, et toutes les statistiques pondérées tombaient dans la branche
        # non pondérée avec un effectif faux.
        def _unquote(raw: str) -> str:
            s = raw.strip()
            if len(s) >= 2 and s.startswith("$") and s.endswith("$"):
                return s[1:-1]  # Literal chars between the $ delimiters
            return self._subst(raw)

        a = _unquote(a_raw)
        b = _unquote(b_raw)
        text = self._subst(text_raw)

        # C: if len(b) < len(a), truncate a to len(b) (extra chars in a are IGNORED, not deleted)
        if len(b) < len(a):
            a = a[:len(b)]
        elif len(b) > len(a):
            b = b[:len(a)]

        if not a:
            return text

        table = str.maketrans(a, b)
        return text.translate(table)

    def _cmd_append(self, args: str) -> str:
        """``!append item|line|word|semicolon|colon X to LISTE``.

        Port de `calc_append` : le séparateur vient de la table `apch_list`
        (`item`→`,`, `line`→`\n`, `word`→espace, `semicolon`→`;`,
        `colon`→`:`), et n'est inséré que si la liste cible n'est pas vide.

        Aucun basculement vers la tabulation : WIMS n'en a pas, et c'en était
        un des producteurs qui obligeaient les consommateurs à la traiter en
        séparateur.
        """
        m = re.match(r"(items?|lines?|words?|semicolons?|colons?)\s+(.*?)\s+to\s*(.*)",
                     args, re.I | re.DOTALL)
        if not m:
            return self._subst(args)
        kind_raw = m.group(1).lower()
        val = self._subst(m.group(2))
        target = self._subst((m.group(3) or ""))

        if kind_raw.startswith("line"):
            sep = "\n"
        elif kind_raw.startswith("word"):
            sep = " "
        elif kind_raw.startswith("semi"):
            sep = ";"
        elif kind_raw.startswith("colon"):
            sep = ":"
        else:
            sep = ","

        # `if(*p3) *p4++=append_char` : `p3` a sauté les blancs de tête, donc
        # une cible entièrement blanche ne reçoit pas de séparateur.
        if not target.strip():
            return val
        return f"{target}{sep}{val}"

    def _cmd_exec(self, args: str) -> str:
        """`!exec <programme> <entrée>` — les binaires que WIMS appelle.

        Aucun n'existe ici : `maxima` et `pari` sont émulés de longue date, et
        l'image ne contient ni l'un ni l'autre. `units-filter` (arrondi aux
        chiffres significatifs) et `chemeq` (chimie) suivent la même voie.

        `chemeq` lit son option dans la variable `chemeq_option`, que le script
        pose juste avant l'appel — c'est ainsi que `slib/chemistry/chemeq_mass`
        demande une masse molaire (`M`) et `chemeq_tex` un rendu LaTeX (`l`).
        L'entrée peut être vide : le slib d'équilibrage interroge d'abord la
        version (`chemeq_option=v`, sans argument).
        """
        # `obabel.sh` — le convertisseur de formats chimiques. WIMS l'appelle
        # pour transformer un SMILES (`@CCCCC`) en coordonnées 3D, et **son
        # script rend `-1` quand il échoue** ; `slib/chemistry/jmolshow` teste
        # exactement cela (`!if $slib_temp!=-1`) pour se replier sur le service
        # distant cactus.nci.nih.gov, que l'applet interroge elle-même.
        #
        # Le repli était donc inatteignable : faute d'être reconnu, `obabel.sh`
        # tombait dans le `return ""` ci-dessous, et `"" != "-1"` fait prendre
        # la branche « la conversion a réussi » — avec un fichier vide. Mesuré
        # sur `isomerie` et `jmol` : 18 rendus, 18 molécules vides. Rendre
        # `-1`, c'est dire la vérité (PAX n'embarque pas Open Babel) dans les
        # termes où le slib l'attend.
        if re.match(r"obabel(\.sh)?\b", args.strip(), re.I):
            return "-1"

        m = re.match(
            r"(maxima|pari|units-filter|chemeq|canvasdraw)\b\s*(.*)", args, re.DOTALL | re.I
        )
        if not m:
            return ""
        engine = m.group(1).lower()
        expr = m.group(2).strip()
        if engine == "maxima":
            return _call_maxima(expr)
        if engine == "pari":
            return _call_pari(expr, session=self.pari_session, rng=self.rng)
        if engine == "units-filter":
            from core.answer.checkers import units_filter  # noqa: PLC0415

            return units_filter(expr)
        if engine == "chemeq":
            from .chemeq import chemeq  # noqa: PLC0415

            return chemeq(expr, str(self.ctx.get("chemeq_option", "")))
        if engine == "canvasdraw":
            return self._exec_canvasdraw(expr)
        return ""

    def _exec_canvasdraw(self, script: str) -> str:
        """`!exec canvasdraw <script>` — le dessin, rendu en SVG.

        WIMS en tire un `<canvas>` piloté en JavaScript ; PAX rend le même
        programme flydraw en SVG, comme le fait déjà `oef/canvasdraw.phtml`.
        La différence de forme n'en est pas une pour l'énoncé : dans les deux
        cas une image, à la même échelle.

        La taille se lit **dans le script** (`size 245,200`), là où
        `oef/canvasdraw.phtml` la reçoit en en-tête. `slib/geo2D/offdraw` la
        calcule à partir du rapport d'aspect du patron et l'écrit en première
        ligne ; sans cette lecture, tous les patrons de polyèdre sortaient au
        format par défaut.
        """
        from ..flydraw import flydraw_to_url  # noqa: PLC0415

        m = re.search(
            r"^\s*size\s+([0-9.]+)\s*,\s*([0-9.]+)\s*$", script, re.MULTILINE
        )
        try:
            largeur = int(float(m.group(1))) if m else 300
            hauteur = int(float(m.group(2))) if m else 300
        except (TypeError, ValueError):
            largeur, hauteur = 300, 300
        mod_dir = (
            os.path.dirname(os.path.dirname(self.def_path)) if self.def_path else None
        )
        url = flydraw_to_url(largeur, hauteur, script, base_dir=mod_dir)
        return f'<img src="{url}" alt="">'

    def _cmd_makelist(self, args: str) -> str:
        """!makelist expr for var=start to end — or — for var in list."""
        # "for var in list" form: iterate over a comma/tab-separated list
        in_m = re.match(r"(.*?)\s+for\s+(\w+)\s+in\s+(.*)", args, re.I | re.DOTALL)
        range_m = re.match(
            r"(.*?)\s+for\s+(\w+)\s*=\s*(.+?)\s+to\s+(.+)", args, re.I | re.DOTALL
        )
        if in_m:
            expr = in_m.group(1).strip()
            var = in_m.group(2)
            list_raw = self._subst(in_m.group(3).strip())
            # `cutfor` (`evalue.c`) découpe la liste d'un `for … in …` par
            # `strparchr(inp, ',')` : la virgule de profondeur zéro, et rien
            # d'autre. Les branches `\n`/`\t`/`;` qui vivaient ici
            # compensaient un `!column` qui joignait ses lignes — depuis qu'il
            # suit `calc_columnof`, `slib/stat/dataproc` rend bien à
            # `slib/stat/arithmean` une liste à virgules.
            items = wl.cutitems(list_raw)
        elif range_m:
            expr = range_m.group(1).strip()
            var = range_m.group(2)
            start_s = range_m.group(3).strip()
            end_s = range_m.group(4).strip()
            try:
                start = int(round(float(self._eval_arith(self._subst(start_s)))))
                end = int(round(float(self._eval_arith(self._subst(end_s)))))
            except (ValueError, TypeError):
                return ""
            # Cap dur : une borne géante (valeur amont cassée d'un slib) ferait
            # une liste énorme et un rendu de plusieurs secondes.
            end = min(end, start + 100000)
            items = [str(i) for i in range(start, end + 1)]
        else:
            return ""

        saved = self.ctx.get(var)
        results = []
        for val_str in items:
            self.ctx[var] = val_str
            parts = [self._eval_loop_expr(p.strip(), var, val_str) for p in expr.split(",")]
            results.append(",".join(parts))
        if saved is not None:
            self.ctx[var] = saved
        else:
            self.ctx.pop(var, None)

        # `_values` (`calc.c`) joint **toutes** ses valeurs par une virgule
        # (`if(pp>p) *pp++=','`), sans séparateur de lignes. La tabulation
        # produisait un `slib_weight` en `1<TAB>1<TAB>…` que
        # `slib/stat/arithmean` passait tel quel à PARI.
        return ",".join(results)

    def _cmd_positionof(self, args: str) -> str:
        """!positionof [word|item|line|char|row] X in $list — les rangs de X.

        `_pos` (`calc.c`) parcourt **toute** la liste et concatène le rang de
        chaque item égal au motif (`if(t>0) strcat(out,",")`) : trois
        occurrences rendent `2,5,7`, pas `2`. Rien trouvé laisse `out` intact,
        donc **la chaîne vide** — jamais `"0"`, qui a l'air d'un rang et que
        les `.def` réinjectent tel quel en indice.
        """
        # `calc_pos` sépare motif et liste par `wordchr(p1,"in")` : le « in »
        # doit être un **mot**, donc suivi d'un blanc ou de la fin. Le `\s*`
        # qui vivait ici coupait sur le « in » de « inverses », et
        # `OEFevalwimsnbrel/progA3` cherchait « La somme des » dans « verses
        # de 7.5 … » — introuvable, quelle que soit la liste.
        m = re.match(
            r"(word|item|line|char|row)?\s*(.*?)\s+in(?=\s|$)\s*(.*)",
            args, re.DOTALL | re.I,
        )
        if not m:
            return ""
        style = (m.group(1) or "").lower()
        needle = self._subst(m.group(2).strip())
        haystack = self._subst(m.group(3).strip())
        # `_pos` (`calc.c`) compare l'objet **élagué** au motif par `strcmp` :
        # aucune normalisation, pas même sur les espaces. Celle qui vivait ici
        # rattrapait le `[1, 2]` que produisait notre émulation de GP ; le mode
        # brut de WIMS (`default(output,0)`) n'en émet pas.
        #
        # `calc_pos` connaît cinq styles, tous confiés au même `_pos` avec un
        # découpeur différent. Seul `item` était porté : un `!positionof row`
        # rendait le vide, et `oefpolynet/31` y perdait le sommet de référence
        # que son énoncé dit « marqué par une croix » — sans lui, l'exercice ne
        # peut pas être répondu.
        decoupeurs = {
            "item": wl.cutitems,
            "row": wl.cutrows,
            "line": wl.cutlines,
            "word": lambda t: t.split(),
            "char": list,
        }
        if not style:
            # Sans mot-clé, `calc_pos` cherche une **sous-chaîne** et rend les
            # décalages en octets, à partir de zéro (`i = pp - buf[1]`).
            if not needle:
                return ""
            positions, depart = [], haystack.find(needle)
            while depart >= 0:
                positions.append(str(depart))
                depart = haystack.find(needle, depart + 1)
            return ",".join(positions)
        objets = decoupeurs[style](haystack)
        return ",".join(str(i) for i, o in enumerate(objets, 1) if o == needle)

    def _cmd_randrow(self, args: str) -> str:
        """!randrow $matrix — ligne aléatoire (séparateur auto)."""
        val = self._subst(args.strip())
        rows = wl.cutrows(val)
        return self.rng.choice(rows) if rows else ""

    def _cmd_sort(self, args: str) -> str:
        """!sort [numeric|reverse] [items|rows|list] LIST — sort."""
        # Strip optional modifiers: numeric, alphabetic, alpha, reverse, down
        numeric = False
        reverse = False
        rest = args
        while True:
            m = re.match(r"(numeric|alphabetic|alpha|reverse|down)\s+(.*)", rest, re.I | re.DOTALL)
            if not m:
                break
            modifier = m.group(1).lower()
            rest = m.group(2)
            if modifier in ("numeric",):
                numeric = True
            if modifier in ("reverse", "down"):
                reverse = True

        # `of` optionnel après le type (`!sort numeric item of $v`, slib/stat/freq).
        m = re.match(r"(items?|rows?|lines?|words?|list)(?:\s+of)?\s+(.*)", rest, re.I | re.DOTALL)
        if m:
            kind, val = m.group(1).lower(), self._subst(m.group(2))
        else:
            kind, val = "items", self._subst(rest)

        # `calc_sort` : items→`,`, mots→espace, lignes/rows→`\n`. Les rows
        # sont converties en lignes d'abord, puis **reconverties** en fin de
        # course (`if(t) lines2rows(p)`).
        back_to_rows = 0
        if kind.startswith("row"):
            val, back_to_rows = wl.rows2lines(val)
            sep, items = "\n", [x for x in wl.cutlines(val) if x.strip()]
        elif kind.startswith("word"):
            sep, items = " ", val.split()
        else:
            sep, items = ",", [x for x in wl.cutitems(val) if x]

        if numeric:
            def _num_key(s: str) -> float:
                try:
                    return float(self._eval_arith(s))
                except Exception:
                    return 0.0
            items.sort(key=_num_key, reverse=reverse)
        else:
            items.sort(reverse=reverse)

        out = sep.join(items)
        return wl.lines2rows(out) if back_to_rows else out

    def _cmd_values(self, args: str) -> str:
        """!values V for var=start to end — list of values."""
        return self._cmd_makelist(args).replace("\t", ",")

    def _list_items(self, value: str) -> list[str]:
        """Items d'une liste WIMS, pour les commandes ensemblistes.

        `find_item_end` vaut `strparstr(p, ",")` : la virgule ne sépare qu'à
        profondeur zéro, les paires `()`/`[]`/`{}` protégeant leur contenu.
        `[polyline red,-1,0],[polyline red,0,-1]` vaut donc **deux** dessins et
        non quinze morceaux.

        Il n'y a en revanche **aucun déballage** de la paire englobante :
        `[0,4,3.5]` vaut un item pour WIMS. Une valeur qui doit être lue comme
        une liste est déballée en amont, par `!declosing`.

        La tabulation prime quand il y en a, comme pour `!item`.
        """
        return [x for x in wl.cutitems(value) if x]

    def _cmd_listuniq(self, args: str) -> str:
        """``!listuniq liste`` — items distincts, joints par des virgules.

        Port de `calc_listuniq` : `cutitems` puis test d'appartenance par
        `itemchr`. Deux conséquences à ne pas « corriger » — les items vides
        sont écartés, et la comparaison est celle d'`itemchr`, une recherche
        de sous-chaîne encadrée, non une égalité.
        """
        out: list[str] = []
        acc = ""
        for item in wl.cutitems(self._subst(args)):
            if item and not wl.itemchr(acc, item):
                out.append(item)
                acc = ",".join(out)
        return acc

    def _cmd_listintersect(self, args: str) -> str:
        """``!listintersect L1 and L2`` — items de L1 présents dans L2.

        Port de `calc_listintersect` : items vides écartés, doublons écartés,
        appartenance par `itemchr`, sortie en virgules.
        """
        m = re.match(r"(.*?)\s+and\s+(.*)", args, re.I | re.DOTALL)
        if not m:
            return ""
        l1 = self._subst(m.group(1))
        l2 = self._subst(m.group(2))
        out: list[str] = []
        acc = ""
        for item in wl.cutitems(l1):
            if item and wl.itemchr(l2, item) and not wl.itemchr(acc, item):
                out.append(item)
                acc = ",".join(out)
        return acc

    def _cmd_declosing(self, args: str) -> str:
        """!declosing text — retire une paire englobante équilibrée (`wims_lists`)."""
        return wl.declosing(self._subst(args))

    def _cmd_getopt(self, args: str) -> str:
        r"""`!getopt <nom> in <options>` — la valeur d'une option `nom=valeur`.

        Port de `calc_getopt` (`calc.c:2051`). Trois choses que le découpage
        naïf sur les blancs et les virgules manquait :

        1. **La normalisation.** WIMS remplace tout blanc par une espace, puis
           chaque `=` par une tabulation. C'est la tabulation, et elle seule,
           qui sépare le nom de sa valeur ; la virgule n'est **pas** un
           séparateur d'options.
        2. **Les délimiteurs.** Une valeur ouverte par `"`, `(`, `[` ou `{`
           court jusqu'à son appariant et le rend **sans** les délimiteurs.
           C'est ce qui garde entier un `swac_text="to build"` — que le
           découpage sur les espaces coupait en deux — et ce qui débarrasse
           `swac_baseform="build"` de ses guillemets, sans quoi le `!lookup`
           suivant cherchait `"build"` dans un fichier indexé sur `build`.
        3. **L'option sans valeur.** `nom` seul, non suivi d'un `=`, se rend
           lui-même : c'est un drapeau, et il est vrai.

        Le fait de rendre depuis le tampon normalisé est fidèle et visible :
        un `=` à l'intérieur d'une valeur en ressort en tabulation, comme chez
        WIMS.
        """
        m = re.match(r"(.*?)\s+in\s+(.*)", args, re.I | re.DOTALL)
        if not m:
            return ""
        cle = self._subst(m.group(1)).strip()
        if not cle:
            return ""
        texte = self._subst(m.group(2))
        botte = "".join(
            "\t" if c == "=" else (" " if c in " \t\n\r\f\v" else c) for c in texte
        )

        i = _position_du_mot(botte, cle)
        if i < 0:
            return ""
        fin_cle = wl.find_word_end(botte, i)
        j = fin_cle
        while j < len(botte) and botte[j] in " \t":
            if botte[j] != "\t":
                j += 1
                continue
            k = wl.find_word_start(botte, j)
            if k >= len(botte):
                return ""
            # Un ouvrant sans appariant ne délimite rien : WIMS retombe alors
            # sur le cas commun (`goto nomatch`), un seul mot.
            ouvrant = botte[k]
            if ouvrant == '"':
                f = botte.find('"', k + 1)
                if f >= 0:
                    return botte[k + 1 : f]
            elif ouvrant in ("(", "[", "{"):
                f = wl.find_matching(botte, k + 1, {"(": ")", "[": "]", "{": "}"}[ouvrant])
                if f >= 0:
                    return botte[k + 1 : f]
            return botte[k : wl.find_word_end(botte, k)]
        # Aucun `=` derrière le nom : drapeau nu, qui se rend lui-même.
        return botte[i:fin_cle]

    def _cmd_embraced(self, args: str) -> str:
        """``!embraced <op> <texte>`` — applique `op` **dans chaque `{…}`**.

        Port de `calc_embraced` (`calc.c`). Le point à ne pas manquer : la
        commande ne choisit rien dans la liste globale — elle remplace chaque
        groupe accolé **sur place** par le résultat de `op` sur son seul
        contenu, en laissant intact tout le texte autour. C'est ce qui permet à
        `unitecell` d'écrire `232,197;Membrane,{coords…};Cytoplasme,{coords…}`
        et de récupérer le même squelette avec une coordonnée tirée par ligne :
        la taille en ligne 1, une ligne par organite ensuite.

        `linkedranditem` tire **un seul** rang, appliqué à tous les groupes —
        c'est ce qui les « lie ».
        """
        s = self._subst(args)
        m = re.match(r"\s*(\w+)\s+(.*)$", s, re.DOTALL)
        if not m:
            return s
        op, text = m.group(1).lower(), m.group(2)

        def groups(t: str) -> list[tuple[int, int]]:
            """Spans des `{…}` de premier niveau (imbrication comprise)."""
            out, depth, start = [], 0, -1
            for i, ch in enumerate(t):
                if ch == "{":
                    if depth == 0:
                        start = i
                    depth += 1
                elif ch == "}" and depth:
                    depth -= 1
                    if depth == 0:
                        out.append((start, i + 1))
            return out

        spans = groups(text)
        if not spans:
            return text

        if op == "extract":
            a, b = spans[0]
            return text[a + 1 : b - 1]
        if op == "delete":
            out, last = [], 0
            for a, b in spans:
                out.append(text[last:a])
                last = b
            out.append(text[last:])
            return "".join(out)

        if op == "linkedranditem":
            a, b = spans[0]
            n = len([x for x in wl.cutitems(text[a + 1 : b - 1]) if x])
            idx = self.rng.randrange(n) if n else 0
            def pick(content: str) -> str:
                items = [x for x in wl.cutitems(content) if x]
                return items[idx] if idx < len(items) else ""
        elif op == "randrow":
            def pick(content: str) -> str:
                rows = [r for r in wl.cutrows(content) if r.strip()]
                return self.rng.choice(rows) if rows else ""
        elif op == "randitem":
            def pick(content: str) -> str:
                return self._cmd_randitem(content)
        else:
            return text

        out, last = [], 0
        for a, b in spans:
            out.append(text[last:a])
            out.append(pick(text[a + 1 : b - 1]))
            last = b
        out.append(text[last:])
        return "".join(out)

    def _cmd_word(self, args: str) -> str:
        """!word N of text — mot(s) N, 1-indexé.

        Même `_blockof` que `!item`/`!line` (`calc_wordof` dans `calc.c`) : `N`
        peut être une plage ou une liste, les mots ressortant séparés par une
        espace.
        """
        m = re.match(r"(.*?)\s+of\s+(.*)", args, re.I | re.DOTALL)
        if not m:
            return ""
        idx_s = self._subst(m.group(1).strip())
        data = self._subst(m.group(2))
        return self._blockof(data, str.split, " ", idx_s)

    def _cmd_column(self, args: str) -> str:
        """!column C of matrix — select column(s) of a matrix.

        ``C`` may be a single index or a list/range (``3,4,2``, ``1 to 3``).
        Rows may be tab-separated (raw WIMS) or ``;``-separated (post-
        ``!translate \\t\\n to ;;``). Columns are comma-separated, with a
        parenthesis-aware split that keeps commas inside ``\\(...\\)`` (LaTeX).

        A single column → its cells across all rows as a comma list (a vector).
        Several columns → a sub-matrix preserving rows, rows joined by newline
        (callers translate ``\\n`` → ``;`` as needed, e.g. liaison3's correspond
        data).
        """
        m = re.match(r"(.*?)\s+of\s+(.*)", args, re.I | re.DOTALL)
        if not m:
            return ""
        spec = self._subst(m.group(1).strip())

        value = self._subst(m.group(2))
        # Lignes séparées par tab, newline (données de slib/stat/dataproc), ou
        # `;` (après `!translate \t\n to ;;`). Sans le newline, `!column 1 of`
        # sur des données en lignes renvoyait tout le bloc comme une seule
        # cellule (dataproc → slib_data mal formé → variance fausse).
        if "\t" in value:
            rows = value.split("\t")
        elif "\n" in value:
            rows = value.split("\n")
        else:
            rows = wl.cutrows(value)
        all_cols = [re.split(r",(?![^(]*\))", r) for r in rows]
        if all(len(c) == 1 for c in all_cols):
            all_cols = [r.split(";") for r in rows]

        # Les indices se lisent avec la grammaire commune (`_index_list`), donc
        # sur le nombre de colonnes — celui de la première ligne, la matrice
        # étant rectangulaire. Le parsing maison d'avant découpait aux virgules
        # *et aux espaces*, ce qui lui faisait prendre le `to` d'une plage pour
        # un indice, échouer à l'évaluer, et rendre une chaîne vide.
        largeur = max((len(c) for c in all_cols), default=0)
        indices = self._index_list(spec, largeur)
        if not indices:
            return ""

        def pick(cols: list[str], i: int) -> str | None:
            return cols[i - 1].strip() if 1 <= i <= len(cols) else None

        if len(indices) == 1:
            i = indices[0]
            return ",".join(v for cols in all_cols if (v := pick(cols, i)) is not None)
        out_rows = []
        for cols in all_cols:
            out_rows.append(",".join(v for i in indices if (v := pick(cols, i)) is not None))
        return "\n".join(out_rows)

    # ── Slib helper command implementations ──────────────────────────────────

    def _cmd_distribute(self, args: str) -> None:
        """!distribute items/lines/words $src into a,b,c — assign each to a var."""
        m = re.match(r"(items?|lines?|words?)\s+(.*?)\s+into\s+(.*)", args, re.I | re.DOTALL)
        if not m:
            return
        kind = m.group(1).lower()
        src = self._subst(m.group(2).strip())
        targets = [t.strip() for t in self._subst(m.group(3)).split(",")]
        if kind.startswith("line"):
            items = src.split("\n")
        elif kind.startswith("word"):
            items = src.split()
        else:
            # Items are comma-separated but commas inside [...] are protected
            # (e.g. `[python,[code]],1,readonly` → 3 items, not 5) — matching WIMS.
            # Une paire englobant *toute* la chaîne est en revanche la notation
            # de liste, pas une protection : `[[1,2;1,4],[2]]` porte deux items.
            # Sans ce déballage, `slib/function/tabsignes` recevait positions et
            # rang collés en un seul, et ne voyait plus qu'une réponse au lieu
            # de six.
            items = [x.strip() for x in wl.cutitems(self._cmd_declosing(src))]
        for i, t in enumerate(targets):
            self.ctx[t] = items[i].strip() if i < len(items) else ""

    def _cmd_bound(self, args: str) -> None:
        """!bound VAR within|among LIST [default DEF] — clamp to allowed values.
        !bound VAR between [integer[s]] MIN and|, MAX [default DEF] — numeric clamp.

        Port of exec_bound (exec.c): with `integer`, rounds the input; if the
        value lies in [MIN, MAX] it's kept (or rounded). Otherwise: use DEF if
        provided, else clamp to the nearest boundary.
        """
        # Form 1: "VAR between [integer[s]] MIN <and|,> MAX [default DEF]"
        m = re.match(
            r"(\w+)\s+between\s+(.*?)(?:\s+default\s+(.*))?$",
            args, re.I | re.DOTALL,
        )
        if m:
            var = m.group(1).strip()
            body = self._subst(m.group(2).strip())
            default_s = self._subst(m.group(3).strip()) if m.group(3) else None

            integer_mode = False
            int_m = re.match(r"^integers?\s+(.*)", body, re.I | re.DOTALL)
            if int_m:
                integer_mode = True
                body = int_m.group(1).strip()

            # `and` or `,` separator
            split_m = re.match(r"(.*?)\s+and\s+(.*)", body, re.I | re.DOTALL)
            if not split_m:
                split_m = re.match(r"(.*?),\s*(.*)", body, re.DOTALL)
            if not split_m:
                return
            lo_s = split_m.group(1).strip()
            hi_s = split_m.group(2).strip()

            raw = self.ctx.get(var, "").strip()
            try:
                val = float(self._eval_arith(raw)) if raw else None
                lo = float(self._eval_arith(lo_s))
                hi = float(self._eval_arith(hi_s))
            except (ValueError, TypeError):
                if default_s is not None:
                    self.ctx[var] = default_s
                return
            if lo > hi:
                lo, hi = hi, lo
            if integer_mode and val is not None:
                val = round(val)
            if val is not None and lo <= val <= hi:
                if integer_mode:
                    self.ctx[var] = str(int(val))
                return
            if default_s is not None:
                self.ctx[var] = default_s
                return
            if integer_mode:
                from math import ceil as _ceil, floor as _floor
                lo, hi = _ceil(lo), _floor(hi)
            clamped = lo if (val is None or val < lo) else hi
            self.ctx[var] = str(int(clamped)) if integer_mode else str(clamped)
            return

        # Form 2: "VAR within|among LIST [default DEF]"
        m = re.match(
            r"(\w+)\s+(?:within|among)\s+(.*?)(?:\s+default\s+(.*))?$",
            args, re.I | re.DOTALL,
        )
        if m:
            var = m.group(1).strip()
            # `cutitems` plutôt qu'un `split(",")` : c'est le découpage du C, et
            # il donne **zéro** item sur une chaîne vide là où `split` en donne
            # un, vide. La nuance décide de tout — `exec_bound` (exec.c:1594)
            # rend la main sans rien écrire quand la liste est vide :
            #
            #     bcnt=cutitems(lbuf,blist,2048);
            #     if(bcnt<=0) { *p=0; return; }
            #
            # PAX y écrivait la valeur par défaut, ce qui remplaçait une valeur
            # légitime par un repli au seul motif que la liste de référence
            # manquait — la langue de `slib/lang/fname` en dépendait.
            allowed = wl.cutitems(self._subst(m.group(2).strip()))
            if not allowed:
                return
            default_s = self._subst(m.group(3).strip()) if m.group(3) else None
            if self.ctx.get(var, "") in allowed:
                return
            self.ctx[var] = default_s if default_s is not None else allowed[0]

    def _cmd_default(self, args: str) -> None:
        """!default VAR=VALUE — set VAR to VALUE only if VAR is currently empty/unset."""
        m = re.match(r"(\w+)\s*=\s*(.*)", args, re.DOTALL)
        if not m:
            return
        var, value = m.group(1).strip(), self._subst(m.group(2).strip())
        if not self.ctx.get(var, "").strip():
            self.ctx[var] = value

    def _cmd_advance(self, args: str) -> None:
        """``!advance VAR`` / ``!increase VAR`` — ajoute 1 à un compteur.

        Les deux noms désignent **la même fonction** dans la table d'`exec.c`
        (`exec_increase`, lignes 1853 et 1950), comme `randfile` et
        `randrecord`. Seul `advance` était routé : les 1491 `!increase` du
        corpus, répartis sur 316 fichiers, ne faisaient rien — et leur valeur
        de retour `UNKNOWN_CMD:increase` pouvait fuiter dans une variable.

        Le C ne lit qu'un mot et ajoute toujours 1 ; aucune occurrence du
        corpus ne porte de second argument. La valeur courante passe par
        `atoi`, qui rend 0 sur ce qui n'est pas un entier — d'où le repli
        plutôt qu'une exception.
        """
        parts = args.split()
        if not parts:
            return
        var = parts[0].strip()
        try:
            courant = int(str(self.ctx.get(var, "0")).strip() or "0")
        except (ValueError, TypeError):
            courant = 0
        self.ctx[var] = str(courant + 1)

    def _cmd_varlist(self, args: str) -> str:
        """``!varlist [nofn] <expression>`` — les noms de variables qu'elle porte.

        `mathvarlist` (`Lib/math.c`) parcourt l'expression et retient chaque
        nom **commençant** par une lettre, dédoublonné, dans l'ordre
        d'apparition, joint par des virgules. Un nom court sur les lettres,
        chiffres, points et apostrophes (`find_mathvar_end`), ce qui laisse
        `f'` entier ; un nombre n'en est jamais un, la boucle exigeant une
        lettre en tête.

        `nofn` en préfixe écarte les noms suivis d'une parenthèse — les
        fonctions —, ce qui distingue `a*b+f(x)` → `a,b,f,x` de sa variante
        `a,b,x`.

        `listvar` en est le second nom, comme `advance` l'est d'`increase` :
        les deux entrées de la table pointent sur la même fonction
        (`calc.c:2359` et `2453`, `exec.c:1988` et `2071`).
        """
        expression = self._subst(args).strip()
        nofn = False
        if re.match(r"nofn\b", expression):
            nofn = True
            expression = expression[len("nofn"):].strip()

        noms: list[str] = []
        i = 0
        while i < len(expression):
            c = expression[i]
            if not c.isalpha():
                i += 1
                continue
            # Un nom ne commence pas au milieu d'un autre.
            if i > 0 and expression[i - 1].isalnum():
                i = _fin_nom_math(expression, i)
                continue
            fin = _fin_nom_math(expression, i)
            nom = expression[i:fin]
            suite = expression[fin:].lstrip()
            if nofn and suite.startswith("("):
                i = fin
                continue
            if nom not in noms:
                noms.append(nom)
            i = fin
        return ",".join(noms)

    def _cmd_getdef(self, args: str) -> str:
        """``!getdef <expression> in <fichier>`` — lit des définitions **dans un
        fichier du module**.

        `exec.c:1914` l'envoie à `calc_defof`, non à `calc_getopt` : les deux
        commandes n'ont de commun que leur préfixe. `getopt` cherche une option
        dans une chaîne ; `getdef` ouvre un fichier du module et y remplace
        **chaque identifiant** de l'expression par la valeur qu'il y trouve
        (`lines.c:getdef`, qui boucle sur les noms et appelle `_getdef`).

        `_getdef` retient une ligne `nom = valeur` — le nom précédé d'un blanc
        ou en tête de fichier —, éventuellement introduite par `!set`, `!let`,
        `!def` ou `!define`, et rien d'autre. La valeur court jusqu'à la fin de
        la ligne, espaces de queue retirés.

        Aucun des 55 appels que le corpus exécute n'y trouve quoi que ce soit :
        leurs fichiers cibles sont des listes de phrases, sans un seul `=`.
        WIMS y rend donc le vide, et PAX le rendait déjà — mais par le mauvais
        chemin, `getopt` répondant à la place. Un module qui livrerait un vrai
        fichier de définitions était jusqu'ici mal servi.
        """
        m = re.match(r"(.*?)\s+in\s+(.*)", self._subst(args), re.S)
        if not m:
            return ""
        expression, cible = m.group(1).strip(), m.group(2).strip()
        # `find_module_file` : le premier mot, cherché dans le module.
        cible = cible.split()[0] if cible.split() else ""
        if not cible or not expression or "/" in cible or ".." in cible:
            return ""
        module_dir = os.path.dirname(os.path.dirname(self.def_path or ""))
        chemin = os.path.join(module_dir, cible)
        if not os.path.isfile(chemin):
            return ""
        try:
            with open(chemin, encoding="utf-8", errors="replace") as f:
                contenu = f.read()
        except OSError:
            return ""

        def definition(nom: str) -> str:
            motif = re.compile(
                rf"(?:^|\n)[ \t]*(?:!(?:set|let|def|define)[ \t]+)?"
                rf"{re.escape(nom)}[ \t]*=(.*)"
            )
            trouve = motif.search(contenu)
            return trouve.group(1).strip() if trouve else ""

        return re.sub(r"[A-Za-z_]\w*", lambda mm: definition(mm.group(0)), expression)

    def _cmd_reset(self, args: str) -> None:
        """``!reset VAR [VAR2 …]`` — vide chacune des variables nommées.

        `exec_reset` (`exec.c`) ouvre sur `items2words(p)` : la **virgule sépare
        autant que l'espace**. Ne découper que sur les blancs laissait à chaque
        nom sa virgule (`slib_eq,` au lieu de `slib_eq`), si bien qu'un
        `!reset a, b, c` ne vidait que le dernier. `slib/chemistry/chemeq_equilibrium`
        ouvre sur un tel `!reset` de trente noms, dont `slib_phrase` où il
        construit sa réponse : d'un appel au suivant, la précédente y restait et
        les deux tableaux se concaténaient.

        La forme `nom[N]` vide la série `nom1`…`nomN`, comme le fait la boucle
        du C.
        """
        for var in self._subst(args.strip()).replace(",", " ").split():
            m = re.fullmatch(r"([A-Za-z_]\w*)\[(\d+)\]", var)
            if m:
                for i in range(1, int(m.group(2)) + 1):
                    self.ctx[f"{m.group(1)}{i}"] = ""
                continue
            self.ctx[var] = ""

    def _blockof(self, data: str, split_fn, sep: str, idx_s: str) -> str:
        """Sélecteur commun à `!item`/`!line`/`!row`/`!word`/`!char` (`_blockof`).

        Port de `calc.c` : `split_fn` tient lieu de la paire `len_fn`/`fnd_fn`,
        `sep` de l'`append_char`. Deux formes d'indice, dans cet ordre —

        - une **plage** `a to b` (le `to` doit être un mot, cherché à
          profondeur zéro) ou `a..b` : bornes évaluées, négatives comptées
          depuis la fin (`-1` = dernier), puis rabotées à `[1, t]`. Une plage
          vide rend une chaîne vide ;
        - sinon une **liste d'indices** découpée par `find_item_end`, chacun
          évalué et compté depuis la fin s'il est négatif ; ceux qui sortent
          des bornes sont **sautés**, pas fatals — un indice unique n'est que
          le cas à un élément.
        """
        parts = split_fn(data)
        t = len(parts)

        def one(i: int) -> str:
            """`_blockof_one` : hors bornes → chaîne vide."""
            return parts[i - 1] if 1 <= i <= t else ""

        return sep.join(one(i) for i in self._index_list(idx_s, t))

    def _index_list(self, idx_s: str, t: int) -> list[int]:
        """Indices 1-based désignés par ``idx_s`` sur ``t`` éléments.

        La grammaire d'indices de `calc.c`, commune à `!item`, `!line`, `!row`,
        `!word`, `!char` — et désormais à `!column`, qui avait le sien et n'y
        connaissait pas la plage : `!column 1 to $val25 of` rendait une chaîne
        **vide**, faute de savoir lire le mot `to` comme un indice. Neuf
        fichiers du corpus s'en servent, dont les `ConnexionInt` qui n'avaient
        alors plus de données à moyenner.
        """
        def num(expr: str) -> int | None:
            try:
                return int(round(float(self._eval_arith(expr.strip()))))
            except (ValueError, TypeError):
                return None

        bounds = _split_range_spec(idx_s)
        if bounds is not None:
            i, j = num(bounds[0]), num(bounds[1])
            if i is None or j is None:
                return []
            if i < 0:
                i = t + i + 1
            if i < 1:
                i = 1
            if j < 0:
                j = t + j + 1
            if j > t:
                j = t
            return list(range(i, j + 1))

        out: list[int] = []
        for raw in wl.cutitems(idx_s):
            i = num(raw)
            if i is None:
                continue
            if i < 0:
                i = t + i + 1
            # Hors bornes : sauté, pas fatal — un indice unique n'est que le
            # cas à un élément.
            if i > t or i < 0:
                continue
            out.append(i)
        return out

    def _cmd_line(self, args: str) -> str:
        """!line N of text — Nth newline-separated line (1-indexed)."""
        m = re.match(r"(.+?)\s+of\s*(.*)", args, re.DOTALL | re.I)
        if not m:
            return ""
        idx_s = self._subst(m.group(1).strip())
        data = self._subst(m.group(2).strip())
        return self._blockof(data, lambda s: [l.strip() for l in s.splitlines() if l.strip()], "\n", idx_s)

    def _cmd_char(self, args: str) -> str:
        """!char N of text — Nth character (1-indexed)."""
        m = re.match(r"(.+?)\s+of\s*(.*)", args, re.DOTALL | re.I)
        if not m:
            return ""
        idx_s = self._subst(m.group(1).strip())
        data = self._subst(m.group(2).strip())
        return self._blockof(data, list, "", idx_s)

    def _cmd_randword(self, args: str) -> str:
        """!randword list — random word from space-separated list."""
        data = self._subst(args)
        words = data.split()
        return self.rng.choice(words) if words else ""

    def _cmd_randline(self, args: str) -> str:
        """!randline text — random newline-separated line."""
        data = self._subst(args)
        lines = [l.strip() for l in data.splitlines() if l.strip()]
        return self.rng.choice(lines) if lines else ""

    def _cmd_sum(self, args: str) -> str:
        """!add / !sum list — arithmetic sum of comma-separated values.

        Forme itérée `!sum EXPR for VAR in LIST` / `… for VAR=a to b`
        (slib/stat/dataproc : `!sum x for x in $poids`) : on génère la liste via
        `!makelist` puis on somme.
        """
        if re.search(r"\bfor\b", args, re.I):
            args = self._cmd_makelist(args).replace("\t", ",")
        parts = [self._subst(p.strip()) for p in args.split(",")]
        total = 0.0
        for p in parts:
            try:
                total += float(self._eval_arith(p))
            except (ValueError, TypeError):
                pass
        if total == int(total):
            return str(int(total))
        return f"{total:g}"

    def _cmd_product(self, args: str) -> str:
        """!multiply / !product — arithmetic product of comma-separated values."""
        parts = [self._subst(p.strip()) for p in args.split(",")]
        result = 1.0
        for p in parts:
            try:
                result *= float(self._eval_arith(p))
            except (ValueError, TypeError):
                pass
        if result == int(result):
            return str(int(result))
        return f"{result:g}"

    def _cmd_listunion(self, args: str) -> str:
        """!listunion L1 and L2 — union of two comma-separated lists (no duplicates)."""
        m = re.match(r"(.*?)\s+and\s+(.*)", args, re.I | re.DOTALL)
        if not m:
            return ""
        l1 = [x.strip() for x in self._subst(m.group(1)).split(",") if x.strip()]
        l2 = [x.strip() for x in self._subst(m.group(2)).split(",") if x.strip()]
        seen: dict = {}
        result = []
        for item in l1 + l2:
            if item not in seen:
                seen[item] = True
                result.append(item)
        return ",".join(result)

    def _cmd_listcomplement(self, args: str) -> str:
        """``!listcomplement L1 in L2`` — items de L2 absents de L1.

        Port de `calc_listcomplement` : mêmes règles que `listintersect`.
        """
        m = re.match(r"(.*?)\s+in\s+(.*)", args, re.I | re.DOTALL)
        if not m:
            return ""
        l1 = self._subst(m.group(1))
        l2 = self._subst(m.group(2))
        out: list[str] = []
        acc = ""
        for item in wl.cutitems(l2):
            if item and not wl.itemchr(l1, item) and not wl.itemchr(acc, item):
                out.append(item)
                acc = ",".join(out)
        return acc

    def _cmd_select(self, args: str) -> str:
        """!select DATA where CONDITION — filter rows matching condition.

        Supports 'column N' references in CONDITION (replaced by the Nth
        comma-separated column of each row, then evaluated via _eval_condition).
        """
        m = re.match(r"(.*?)\s+where\s+(.*)", args, re.I | re.DOTALL)
        if not m:
            return ""
        data_raw = self._subst(m.group(1).strip())
        cond_template = m.group(2).strip()

        # Normalise rows to newline-separated
        if "\n" not in data_raw and ";" in data_raw:
            rows = [r.strip() for r in data_raw.split(";") if r.strip()]
        elif "\t" in data_raw:
            rows = [r.strip() for r in data_raw.split("\t") if r.strip()]
        else:
            rows = [r.strip() for r in data_raw.splitlines() if r.strip()]

        selected = []
        for row in rows:
            cols = [c.strip() for c in row.split(",")]

            def inject_columns(cond: str, cols: list[str]) -> str:
                def replace_col(mo: re.Match) -> str:
                    try:
                        ci = int(mo.group(1)) - 1
                        return cols[ci] if 0 <= ci < len(cols) else ""
                    except (ValueError, IndexError):
                        return ""
                return re.sub(r"\bcolumn\s+(\d+)\b", replace_col, cond, flags=re.I)

            cond = inject_columns(cond_template, cols)
            cond = self._subst(cond)
            if _wims_compare(cond, numeric=False):
                selected.append(row)

        return "\n".join(selected)

    def _read_module_file(self, filename: str) -> str | None:
        """Lit un fichier de données du module, sinon de l'arbre partagé.

        Un slib partagé lit ses données là où il vit, non dans le module qui
        l'appelle : `slib/lang/swac` cherche `data/swac/packs` sous
        `scripts/`, que le module soit un cours d'anglais ou de néerlandais.
        D'où le repli sur `wims-scripts/` — le module reste prioritaire, un
        fichier local l'emportant sur son homonyme partagé.
        """
        if not self.def_path:
            return None
        # Concaténation textuelle, comme `mkfname(buf,"%s/%s",…)` : `os.path.join`
        # prendrait un `/data1` pour un chemin absolu et jetterait le préfixe.
        module_dir = os.path.dirname(os.path.dirname(self.def_path))
        candidats = [f"{module_dir}/{filename}"]
        scripts_dir = self._find_wims_scripts_dir()
        if scripts_dir:
            candidats.append(f"{scripts_dir}/{filename}")
        full = next((c for c in candidats if os.path.exists(c)), None)
        if full is None:
            return None
        try:
            return open(full, encoding="utf-8").read()
        except UnicodeDecodeError:
            return open(full, encoding="cp1252").read()
        except OSError:
            return None

    def _cmd_rename(self, args: str) -> str:
        """!rename PATH — URL de service pour un fichier du module ou de `gifs/`.

        WIMS (`calc_rename`) pose un lien symbolique dans le répertoire de
        session et renvoie une URL `getfile/rename-<alea>` : c'est un moyen de
        servir un fichier sans en exposer le chemin. PAX sert `ressources/` par
        `/api/static`, donc la traduction suffit — pas de lien, pas d'aléa.

        La liste blanche de chemins de `calc_rename` (`gifs`, le répertoire du
        module, `modules/data/`, `scripts/data/`) est reprise, complétée par son
        refus des `..` : le paramètre vient du `.def`, et rien ne doit pouvoir
        pointer hors de `ressources/`. Un fichier absent rend la chaîne vide,
        comme WIMS quand le `symlink` échoue.
        """
        path = self._subst(args).strip().split()[0] if self._subst(args).strip() else ""
        if not path or ".." in path.split("/"):
            return ""
        # `$imagedir` vaut la sentinelle `pax-img:` — déjà la forme « servable »
        # de PAX, que `flydraw.inline_pax_images` résout en post-rendu. C'est
        # elle qui tient chez nous le rôle de `calc_rename` ; le chemin ressort
        # donc intact, sans quoi `!rename $imagedir/x.png` (ce que devient un
        # `\img{}` via `oef/img.phtml`) rendrait une chaîne vide.
        if path.startswith("pax-img:"):
            return path
        # `gifs/…` désigne l'arbre partagé de WIMS, vendoré en
        # `ressources/wims-gifs/` (cf. `_find_wims_gifs_dir`).
        if path.startswith("gifs/"):
            rel = f"wims-gifs/{path[len('gifs/'):]}"
        # `scripts/data/…` est l'autre arbre partagé de la liste blanche de
        # `calc_rename`, vendoré en `ressources/wims-scripts/data/` : c'est là
        # que `oefcountries` va chercher ses 268 cartes
        # (`scripts/data/maps/<code>.jpg`).
        elif path.startswith("scripts/data/"):
            rel = f"wims-scripts/data/{path[len('scripts/data/'):]}"
        else:
            if not self.def_path:
                return ""
            module_dir = os.path.dirname(os.path.dirname(self.def_path))
            rel = os.path.relpath(os.path.join(module_dir, path), _RESSOURCES_ROOT)
            if rel.startswith(".."):
                return ""
        if not os.path.isfile(os.path.join(_RESSOURCES_ROOT, rel)):
            return ""
        return f"/api/static/{rel}"

    @staticmethod
    def _split_records(text: str) -> list[str]:
        """Découpe un fichier WIMS en enregistrements séparés par `\\n:`.

        Chaque enregistrement inclut son nom comme première ligne (sans le
        `:` initial), conformément à `datafile_fnd_record` (`lines.c:666`),
        dont le commentaire précise « find record n, **starting from 1** ».

        **Ce qui précède le premier `:` n'en est pas un.** C'est l'en-tête du
        fichier, que `datafile_fnd_record` sert à l'indice 0 (`datacache[0]`)
        et que `_cmd_record` traite déjà à part. Le garder ici décalait tout
        d'un rang : `!record 1` redonnait l'en-tête, et les données ne
        commençaient qu'à 2. `OEFspectres/spectre3` y perdait sa table de
        spectres — `!rowcnt` tombait à 1, `!randint 2, $val8-1` devenait
        `!randint 2, 0`, et le choix correct de l'exercice sortait vide.

        `datafile_recordnum` (`lines.c:659`, `ret=i-1`) l'exclut de même du
        compte : un fichier d'en-tête plus un enregistrement en déclare **un**.
        """
        chunks = re.split(r"(?:^|\n):", text)
        # Le premier morceau n'est un enregistrement que si le fichier ouvre
        # directement sur un `:` — auquel cas `re.split` a produit un vide.
        if chunks and not text.lstrip().startswith(":"):
            chunks = chunks[1:]
        return [c.rstrip("\n") for c in chunks if c.strip()]

    def _cmd_record(self, args: str) -> str:
        """!record N of FILE — Nième enregistrement d'un fichier données WIMS.

        Format du fichier :
            :nom_enregistrement1
            ligne1
            ligne2
            :nom_enregistrement2
            ...

        Retourne l'enregistrement avec son nom comme première ligne
        (les lignes suivantes sont accessibles via !row 2, !row 3, …).

        L'indice **0** est licite ici, et pour `record` seul : `_blockof` le
        refuse à `!row` ou `!item` mais l'accepte quand la fonction de
        recherche est `datafile_fnd_record` (calc.c:614). Il désigne alors
        l'en-tête — ce qui précède le premier `\\n:` —, dont `slib/lang/swac`
        tire l'hôte des fichiers audio :

            ADDRESS=!record 0 of data/swac/packs
        """
        m = re.match(r"(.+?)\s+of\s+(\S+)", args, re.I | re.DOTALL)
        if not m:
            return ""
        idx_s = self._subst(m.group(1).strip())
        filename = self._subst(m.group(2).strip())
        text = self._read_module_file(filename)
        if text is None:
            return ""
        records = self._split_records(text)
        try:
            idx = int(round(float(self._eval_arith(idx_s))))
            if idx == 0:
                debut = re.search(r"(?:^|\n):", text)
                entete = text[: debut.start()] if debut else text
                # `datafile_fnd_record` recopie dans un tampon de MAX_LINELEN
                # (wimsdef.h) et coupe au-delà — un fichier sans `:`, comme
                # `oefmolecule/1centre`, ressort donc entier mais borné.
                return entete[: _MAX_LINELEN - 1].strip("\n")
            if 1 <= idx <= len(records):
                return records[idx - 1]
        except (ValueError, TypeError):
            pass
        return ""

    def _cmd_recordcnt(self, args: str) -> str:
        """!recordcnt FILE — nombre d'enregistrements dans un fichier données."""
        filename = self._subst(args.strip())
        text = self._read_module_file(filename)
        if text is None:
            return "0"
        return str(len(self._split_records(text)))

    def _cmd_lookup(self, args: str) -> str:
        """!lookup KEY in DATAFILE — look up KEY in a key:value data file.

        Format of data file:
            key1: value line 1 (may be comma-separated list)
            key2: value line 2
        Lookup is case-insensitive; KEY is trimmed.
        DATAFILE is resolved by `_read_module_file`: the module first, then the
        shared `wims-scripts/` tree where a slib keeps its own data.

        Une valeur peut courir sur plusieurs lignes, chacune terminée par une
        contre-oblique. `_lookup` (calc.c:1883-1887) avance de saut de ligne en
        saut de ligne tant qu'une contre-oblique le précède, la **remplace par
        une espace** et garde le saut de ligne — la valeur rendue est donc
        multiligne. C'est ainsi que sont écrits les `sw_tags` de swac, dont un
        enregistrement porte tous les mots-clés d'un enregistrement audio :

            eng-balm-verbs/t/eng-to_build:swac_text="to build"\\
            swac_alphaidx="build"\\
            swac_baseform="build"

        Sans cette suite, `slib/lang/swac` ne rendait que `swac_text` ; les
        `!getopt swac_baseform` d'`oefanglais` repartaient vides, et avec eux
        les trois formes verbales que l'exercice fait ensuite prononcer.
        """
        m = re.match(r"(.*?)\s+in\s+(\S+)", args, re.I | re.DOTALL)
        if not m:
            return ""
        key = self._subst(m.group(1)).strip()
        filename = self._subst(m.group(2)).strip()
        if not key:
            return ""
        text = self._read_module_file(filename)
        if text is None:
            return ""
        # Search for "KEY:" at the start of a line (case-insensitive)
        needle = key.lower() + ":"
        lignes = text.splitlines()
        for i, line in enumerate(lignes):
            if not line.lower().startswith(needle):
                continue
            morceaux = [line[len(needle):]]
            j = i
            while morceaux[-1].endswith("\\") and j + 1 < len(lignes):
                morceaux[-1] = morceaux[-1][:-1] + " "
                j += 1
                morceaux.append(lignes[j])
            return "\n".join(morceaux).strip()
        return ""

    def _cmd_text(self, args: str) -> str:
        """!text SUBCOMMAND ... — WIMS string manipulation for structured text.

        Supported sub-commands (from calc.c `text`):
          select CHARS in STRING  — keep only chars of STRING present in CHARS
          copy   STRING mask MASK — keep chars where MASK digit is '1'
          expand STRING using MASK — replicate chars where MASK digit is '1'
          insert SRC into DST mask MASK — insert SRC chars into DST at '1' positions
        """
        s = self._subst(args)

        # select CHARS in STRING
        m = re.match(r"select\s+(.*?)\s+in\s+(.*)", s, re.I | re.DOTALL)
        if m:
            charset = set(m.group(1).strip())
            text = m.group(2).strip()
            return "".join(c for c in text if c in charset)

        # copy STRING mask MASK
        m = re.match(r"copy\s+(.*?)\s+mask\s+(\S+)", s, re.I | re.DOTALL)
        if m:
            src = m.group(1).strip()
            mask = m.group(2).strip()
            return "".join(c for c, bit in zip(src, mask) if bit == "1")

        # expand STRING using MASK — port of Lib/text.c text_expand:
        # walk MASK cyclically, emitting ' ' for a '0' bit and the next src
        # char for a '1' bit, until every char of STRING has been placed.
        m = re.match(r"expand\s+(.*?)\s+using\s+(\S+)", s, re.I | re.DOTALL)
        if m:
            src = m.group(1).strip()
            mask = m.group(2).strip()
            if not src or not mask or "1" not in mask:
                return ""
            result = []
            i = j = 0
            while i < len(src):
                if mask[j % len(mask)] == "0":
                    result.append(" ")
                else:
                    result.append(src[i])
                    i += 1
                j += 1
            return "".join(result)

        # insert SRC into DST mask MASK
        m = re.match(r"insert\s+(.*?)\s+into\s+(.*?)\s+mask\s+(\S+)", s, re.I | re.DOTALL)
        if m:
            src = m.group(1).strip()
            dst = list(m.group(2).strip())
            mask = m.group(3).strip()
            src_iter = iter(src)
            for i, bit in enumerate(mask):
                if bit == "1" and i < len(dst):
                    try:
                        dst[i] = next(src_iter)
                    except StopIteration:
                        break
            return "".join(dst)

        return s

    def _cmd_insdraw(self, args: str) -> str:
        """!insdraw <flydraw commands> — render the body via flydraw and set
        ``$ins_url`` to the resulting URL. The slib draw/* scripts rely on
        this side effect (they then wrap ``$ins_url`` in an <img> themselves).

        Size comes from ``$insdraw_size`` (``W,H``) — set by the caller right
        before invoking !insdraw. Defaults to 300x300 when missing.
        """
        from ..flydraw import flydraw_to_url  # noqa: PLC0415

        body = self._subst(args)
        size_raw = self._subst(self.ctx.get("insdraw_size", "")).strip()
        size_parts = [p.strip() for p in size_raw.split(",") if p.strip()]
        try:
            w = int(float(size_parts[0])) if size_parts else 300
            h = int(float(size_parts[1])) if len(size_parts) > 1 else w
        except ValueError:
            w, h = 300, 300

        mod_dir = os.path.dirname(os.path.dirname(self.def_path)) if self.def_path else None
        url = flydraw_to_url(w, h, body, base_dir=mod_dir)
        self.ctx["ins_url"] = url
        return ""

    def _cmd_solve(self, args: str) -> str:
        """!solve EXPR for VAR = START to END — ALL real roots of EXPR=0 in [START,END].

        Faithful port of WIMS ``calc.c:calc_solve``: scan the interval in 100
        steps, detect every sign change between consecutive samples, refine each
        by 30 bisection steps, and return the roots as a comma-separated list.
        This is what ``!itemcnt`` then counts — e.g. quizz 1218 "nombre de
        solutions de f'(x)=0" (4 extrema). A range with a single root (quizz
        1120's ``(Cf)`` position, used as a scalar via ``$[…]``) just yields a
        one-element list. EXPR may be an equation ``lhs=rhs`` (taken as lhs-rhs).
        """
        m = re.match(r"(.*?)\s+for\s+(\w+)\s*=\s*(.*?)\s+to\s+(.*)", args, re.I | re.DOTALL)
        if not m:
            return ""
        expr_raw = self._subst(m.group(1)).strip()
        var = m.group(2).strip()
        try:
            start = float(self._eval_arith(self._subst(m.group(3).strip())))
            stop = float(self._eval_arith(self._subst(m.group(4).strip())))
        except (ValueError, TypeError):
            return ""

        # If expr contains '=', turn it into LHS - RHS
        if "=" in expr_raw and "==" not in expr_raw:
            lhs, _, rhs = expr_raw.partition("=")
            expr_py = f"({lhs.strip()}) - ({rhs.strip()})".replace("^", "**")
        else:
            expr_py = expr_raw.replace("^", "**")

        try:
            code = compile(expr_py, "<solve>", "eval")
        except SyntaxError:
            return ""
        ns = dict(_MATH_NS)

        def f(v: float) -> float:
            ns[var] = v
            try:
                return float(eval(code, ns))
            except Exception:
                return float("nan")

        if start > stop:
            start, stop = stop, start
        step = (stop - start) / 100.0
        if step == 0:
            return ""

        def _fmt(v: float) -> str:
            r = round(v, 6)
            return str(int(r)) if r == int(r) else f"{r:.6g}"

        roots: list[str] = []
        prev = f(start)
        for i in range(1, 101):
            v = start + i * step
            dd = f(v)
            if (
                not math.isfinite(prev)
                or not math.isfinite(dd)
                or (prev > 0 and dd > 0)
                or (prev < 0 and dd < 0)
            ):
                prev = dd
                continue
            # an exact-zero sample is refined at the *next* boundary (skip now,
            # unless it's the last point) — mirrors WIMS' `if(dd==0 && v<stop)`.
            if dd == 0 and v < stop:
                prev = dd
                continue
            # sign change in [v-step, v] → 30-step bisection
            v1, v2, d1 = v - step, v, prev
            v3 = v1
            ok = True
            for _ in range(30):
                v3 = (v1 + v2) / 2
                d3 = f(v3)
                if not math.isfinite(d3):
                    ok = False
                    break
                if (d1 > 0 and d3 > 0) or (d1 < 0 and d3 < 0):
                    d1, v1 = d3, v3
                else:
                    v2 = v3
            if ok:
                roots.append(_fmt(v3))
            prev = dd
        return ",".join(roots)

    # ── Section rendering ─────────────────────────────────────────────────────

    def _render_section(self, instructions: list) -> str:
        """Render an executed section (:question etc.) to HTML."""
        buf: list[str] = []
        self._exec(instructions, output_buf=buf)
        return "".join(buf)

    def _render_block_or_text(self, literal: str, section_instrs: list) -> str:
        """Render hint/solution: use section if it has content, else literal.

        Closes WIMS inline math (``\\(…)`` → ``\\(…\\)``) and inlines any flydraw
        SVG/GIF, exactly like the statement pipeline — otherwise the solution
        table cells (deve7: ``\\(( 12 a + 4 )^2)``) reach the front with an
        unclosed ``\\(`` and KaTeX can't render them (shows raw ``\\displaystyle …``).
        """
        out = ""
        if section_instrs:
            rendered = self._render_section(section_instrs)
            if rendered.strip():
                out = rendered
        if not out and literal and literal.strip():
            out = self._subst(literal)
        if not out:
            return ""
        out = _close_inline_math(out, self.lang)
        if "/api/render/svg/" in out or "wimsdraw" in out:
            from ..flydraw import inline_svg_imgs, inline_wims_gifs  # noqa: PLC0415
            out = inline_svg_imgs(out)
            out = inline_wims_gifs(out)
        # Une indication porte volontiers une image de module : `mole/…` y met
        # sa table périodique, `fonctaffin/coef` la capture qui explique la
        # pente. Elles n'empruntent pas l'énoncé, donc pas sa passe de
        # post-rendu — sans cette résolution, l'URL sentinelle sortait telle
        # quelle et l'indication s'ouvrait sur une image brisée.
        return self._inline_module_imgs(out)

    def _split_correspond_column(self, row: str) -> list[str]:
        """Items d'une colonne de `correspond` — `!nonempty items` (`liblines.c`).

        `anstype/correspond.input` ne fait rien d'autre : `!rows2lines` sur le
        `replygood`, `!distribute lines` en deux colonnes, puis
        `!nonempty items` sur chacune. Une heuristique vivait ici pour
        rattraper les colonnes d'éléments HTML (les 4 `<img>` d'`assgrhyper`),
        dont le balisage multi-lignes porte des tabulations : elle coupait
        après un `>` suivi d'une tabulation. La virgule les sépare déjà —
        mesuré : 4 items dans les deux cas.
        """
        return [c for c in wl.cutitems(row) if c.strip()]

    def _inline_module_imgs(self, s: str) -> str:
        """Résout les `pax-img:…` d'un fragment hors énoncé.

        L'énoncé traverse `inline_pax_images` en post-rendu, mais une palette
        part sérialisée en JSON dans un attribut `data-config` : le HTML y est
        échappé (`&lt;img src=\\&quot;pax-img:…`) et la passe de post-rendu ne
        peut plus le voir. Les fragments qui n'empruntent pas l'énoncé doivent
        donc être résolus ici, avant leur sérialisation.
        """
        if "pax-img:" not in s or not self.def_path:
            return s
        from ..flydraw import inline_pax_images  # noqa: PLC0415
        module_dir = os.path.dirname(os.path.dirname(self.def_path))
        exercise = os.path.splitext(os.path.basename(self.def_path))[0]
        return inline_pax_images(s, module_dir, exercise)

    def _prep_correspond_item(self, raw: str) -> str:
        """Normalise one correspond cell for display: close WIMS inline math and,
        for a flydraw graph, collapse the multi-line ``<img>`` whitespace and
        inline its SVG (so it travels in the payload, like the rest of the
        rendered statement — the ``/api/render/svg`` cache is in-memory only).

        Une image de module (`oefmolecule` fait apparier des modèles
        moléculaires à leur nom) y est résolue de même : la cellule part en
        JSON échappé, hors de portée de la passe de post-rendu."""
        s = _close_inline_math(self._subst(raw.strip()), self.lang)
        if "/api/render/svg/" in s:
            from ..flydraw import inline_svg_imgs  # noqa: PLC0415
            s = re.sub(r"\s+", " ", s)            # flatten the multi-line markup
            # (le blanc qui suivait le guillemet — `src="<TAB>/api/…` — était
            # retiré ici ; `_IMG_SVG_RE` le tolère désormais lui-même.)
            s = inline_svg_imgs(s)
        return self._inline_module_imgs(s)

    def _inline_radio_choices(self, n: str) -> list[str]:
        """Choice list of radio reply ``n`` from ``replygood{n}`` (``correct;a,b,…``).

        Used by the inline-radio test in :meth:`_render_embed` to recognise the
        "pick figure N" style (choices are the bare positions ``1,2,…``). Returns
        ``[]`` when there's no choice list yet (e.g. plain/analyze radios).
        """
        raw = self._subst(self.ctx.get(f"replygood{n}", "")).strip()
        if ";" not in raw:
            return []
        after = raw.split(";", 1)[1].strip()
        # Découpage prudent : une virgule **dans** un `\(…\)` n'en sépare pas
        # deux choix. `oeffonctgen/qcmensdef` propose des intervalles —
        # `\(\rbrack -\infty , 3 \lbrack \cup \rbrack 3 , +\infty \lbrack\)` —
        # qu'un `split(",")` cassait en trois morceaux, dont deux au math
        # déséquilibré. C'est le même découpage que la branche `checkbox`.
        return [c.strip() for c in re.split(r",(?![^(]*\))", after) if c.strip()]

    def _apply_prev_replies(self) -> None:
        """Set `$m_reply{n}` / `$m_sc_reply{n}` (and `$reply{n}` / `$sc_reply{n}`)
        from the replies submitted on earlier course steps, grading each against
        its `replygood{n}` so the step statement shows the right verdict/colour."""
        if not self.prev_replies:
            return
        for name, value in self.prev_replies.items():
            m = re.match(r"r(?:eply)?(\d+)$", name)
            if not m:
                continue
            n = m.group(1)
            self.ctx[f"reply{n}"] = value
            self.ctx[f"m_reply{n}"] = value
            expected = self._subst(self.ctx.get(f"replygood{n}", "")).strip()
            rtype = self._reply_type(n) or "numexp"
            correct = self._grade_prev_reply(value, expected, rtype)
            sc = "1" if correct else "0"
            self.ctx[f"sc_reply{n}"] = sc
            self.ctx[f"m_sc_reply{n}"] = sc

    def _grade_prev_reply(self, reply: str, expected: str, rtype: str) -> bool:
        """Best-effort grade of a previous-step reply (for the `$m_sc_reply`
        verdict only — the authoritative score is computed at check time)."""
        if not reply.strip():
            return False
        try:
            from core.answer.checkers import check_answer  # noqa: PLC0415
            return check_answer(rtype or "numexp", reply, expected, lang=self.lang).correct
        except Exception:
            return reply.strip() == expected.strip()

    def _reply_type(self, n) -> str:
        """Type canonique de la réponse `n`, tel que le `.def` le déclare.

        `replytypeN` n'est pas toujours littéral : `unitecell` écrit
        `replytype1=$val12`, et la valeur brute reste dans le contexte. Il faut
        donc substituer avant de comparer — sans quoi le test échoue en
        silence, et `imagefill` refusait toutes ses cases faute de reconnaître
        un `clickfill` écrit derrière une variable.
        """
        return _normalize_reply_type(self._subst(self.ctx.get(f"replytype{n}", "")))

    def _render_special(self, args: str) -> str:
        """Dispatch an OEF ``\\special`` (``!read oef/special.phtml <kind> …``).

        Les `\\special` non gérés rendent une chaîne vide plutôt que de laisser
        fuir du balisage — mais ce silence *supprime le texte de l'énoncé*
        quand le `\\special` en porte (`help`, `tooltip`), d'où les rendus
        ci-dessous. Restent non gérés : `drawinput` et `jsxgraphinput`
        (widgets front).
        """
        s = self._subst(args).strip()
        m = re.match(r"^\s*(\w+)\s+(.*)$", s, re.DOTALL)
        if not m:
            return ""
        kind, rest = m.group(1).lower(), m.group(2)
        if kind == "mathmlinput":
            return self._render_mathmlinput(rest)
        if kind == "expandlines":
            return self._render_expandlines(rest)
        if kind == "tooltip":
            return self._render_tooltip(rest)
        if kind == "help":
            return self._render_special_help(rest)
        if kind == "editarea":
            return self._render_editarea(rest)
        if kind == "glossary":
            return self._render_glossary(rest)
        if kind == "codeinput":
            return self._render_codeinput(rest)
        if kind == "imagefill":
            return self._render_imagefill(rest)
        return ""

    def _render_imagefill(self, args: str) -> str:
        """``imagefill IMG,LxH,lxh<TAB>replyN,x,y[,L]<TAB>…``

        Port d'`oef/special/imagefill.phtml` : une grande image sur laquelle des
        champs `clickfill`/`dragfill` sont posés à des coordonnées absolues.
        WIMS empile des calques DynAPI ; en CSS c'est un conteneur
        `position:relative` et des cases `position:absolute`, à quoi se réduit
        tout le mécanisme.

        Découpage repris tel quel du phtml : une tabulation suivie d'une virgule
        est absorbée, les autres deviennent des séparateurs de lignes ; la ligne
        1 porte image/grande taille/petite taille, les suivantes un champ
        chacune. Les tailles s'écrivent `LxH` ou `L x H`, d'où le `x` traité
        comme un séparateur au même titre que la virgule.

        Le 4ᵉ paramètre d'une ligne est le nombre d'étiquettes que la case peut
        recevoir (défaut 1) : autant de cases côte à côte, comme le
        `stretchH:$sizei*$ssizex` du calque WIMS.
        """
        import html as _html  # noqa: PLC0415

        # `imagefill.phtml` traduit les tabulations en `;` *puis* découpe les
        # lignes sur `;` — les deux séparateurs sont donc équivalents, et
        # `oefmolecule` livre effectivement ses champs en `;`. La tabulation
        # suivie d'une virgule est absorbée avant, comme dans le phtml.
        raw = args.replace("\t,", ",").replace("\t", ";")
        rows = [r for r in wl.cutrows(raw) if r.strip()]
        if not rows:
            return ""
        head = [p.strip() for p in rows[0].split(",")]
        img = head[0] if head else ""
        if not img:
            return ""

        def _dims(spec: str) -> tuple[int, int] | None:
            """`LxH` / `L x H` / `L,H` → (L, H) ; None si non numérique."""
            parts = [p for p in re.split(r"[x,\s]+", spec.strip()) if p]
            if len(parts) < 2:
                return None
            try:
                return int(round(float(parts[0]))), int(round(float(parts[1])))
            except (ValueError, TypeError):
                return None

        big = _dims(head[1]) if len(head) > 1 else None
        small = _dims(head[2]) if len(head) > 2 else None
        # Une taille non évaluée (`[227,13,146,15] x [18,120,48,117]` d'unitecell)
        # ne doit pas coûter l'exercice : l'image garde sa taille naturelle et les
        # cases prennent un gabarit par défaut.
        sx, sy = small or (40, 30)

        slots: list[str] = []
        for row in rows[1:]:
            cells = [c.strip() for c in re.split(r"[x,]", row) if c.strip()]
            if len(cells) < 3:
                continue
            n = re.sub(r"[^0-9()+\-*/]", "", cells[0])
            try:
                n = str(int(round(float(self._eval_arith(n)))))
            except (ValueError, TypeError):
                continue
            if not 1 <= int(n) <= 100:
                continue
            if self._reply_type(n) != "clickfill":
                continue
            try:
                px, py = int(round(float(cells[1]))), int(round(float(cells[2])))
            except (ValueError, TypeError):
                continue
            try:
                count = max(1, int(round(float(cells[3])))) if len(cells) > 3 else 1
            except (ValueError, TypeError):
                count = 1
            self._touched_replies.add(f"reply{n}")
            for i in range(count):
                slots.append(
                    f'<cf-slot name="reply{n}" data-index="{i}" data-w="{sx}" '
                    f'style="position:absolute;left:{px + i * sx}px;top:{py}px;'
                    f'width:{sx}px;height:{sy}px"></cf-slot>'
                )

        box = f"position:relative;display:inline-block;line-height:0"
        if big:
            box += f";width:{big[0]}px;height:{big[1]}px"
        img_style = f"width:{big[0]}px;height:{big[1]}px" if big else "max-width:100%"
        return (
            f'<div class="oef-imagefill" style="{box}">'
            f'<img src="{_html.escape(img, quote=True)}" alt="" style="{img_style}">'
            f'{"".join(slots)}</div>'
        )

    def _render_codeinput(self, args: str) -> str:
        """``codeinput <code>,<taille>,<pre|div><TAB>replyN,<taille>,<css>…``

        Port de la branche `q_form` d'`oef/special/codeinput.phtml` : le bloc
        `code` est recopié tel quel, et chaque marqueur `replyN` qu'il contient
        est remplacé par le champ de la réponse N. C'est le même principe que
        `mathmlinput`, sur du texte au lieu d'une formule.

        Les marqueurs les plus longs passent d'abord — sans quoi `reply1`
        s'apparierait à l'intérieur de `reply10` (WIMS obtient le même effet en
        triant ses lignes à l'envers).

        `slib/function/tabsignes` place ses marqueurs dans des cellules de
        tableau déjà mises en forme mathématique, sous la forme `\\(reply1\\)` :
        les délimiteurs sont absorbés avec le marqueur, sinon KaTeX recevrait
        du HTML à composer.
        """
        body = args.replace("\t", "\n")
        lines = [line for line in body.split("\n")]
        head = _split_top_level(lines[0], ",")
        if not head:
            return ""
        # Les deux derniers champs de l'en-tête sont la taille par défaut et la
        # balise ; ce qui précède est le code — qui peut lui-même porter des
        # virgules (le tableau de `tabsignes` en a une).
        if len(head) >= 3:
            code = ",".join(head[:-2]).strip()
            default_size = head[-2].strip()
            tag = head[-1].strip().lower()
        else:
            code, default_size, tag = head[0].strip(), "", ""
        code = self._cmd_declosing(code)
        if not code:
            return ""
        tag = "div" if tag == "div" else "pre"

        specs: list[tuple[str, str]] = []
        for spec in lines[1:]:
            fields = _split_top_level(spec, ",")
            ref = re.sub(r"\s+", "", fields[0]) if fields else ""
            if not re.fullmatch(r"(?:reply|r)\d+", ref, re.I):
                continue
            size = fields[1].strip() if len(fields) > 1 and fields[1].strip() else default_size
            specs.append((ref, size))

        # Marqueurs longs d'abord : `reply10` avant `reply1`.
        for ref, size in sorted(specs, key=lambda s: len(s[0]), reverse=True):
            n = re.sub(r"\D", "", ref)
            name = f"reply{n}"
            widget = self._render_embed(f"{name},{size}" if size else name)
            if not widget:
                continue
            pattern = re.compile(
                r"(?:\\\(\s*)?\b(?:reply|r)" + re.escape(n) + r"\b(?:\s*\\\))?",
                re.I,
            )
            code = pattern.sub(lambda _m, w=widget: w, code, count=1)
        return f'<{tag} class="oef_codeinput">{code}</{tag}>'

    def _render_glossary(self, args: str) -> str:
        """``glossary <chemin>,tooltip=[<ancre>,<largeur>]`` — terme de glossaire.

        Port d'`oef/special/glossary.phtml` : l'ancre reste dans la phrase et la
        définition s'ouvre au survol, dans la même structure `.wims_tooltip` que
        `\\special{tooltip}`. Sans ce rendu, l'ancre disparaissait avec le reste :
        la solution de `descriptives.fr/ecarttype` s'ouvrait sur « est la racine
        carré de la . », amputée de ses deux termes.

        Les définitions vivent dans `data/glossary/…`, vendorées sous
        `ressources/wims-scripts/`. Un terme absent (le `cumulate_frequency1`
        d'`oefstatistiques`, coquille pour `cumulative_`) rend l'ancre seule
        plutôt que rien.
        """
        parts = _split_top_level(args, ",")
        if not parts:
            return ""
        path = parts[0].strip()
        option = ",".join(parts[1:])
        # `!getopt tooltip in $option` → `[ancre,largeur]`
        m = re.search(r"tooltip\s*=\s*\[(.*)\]", option, re.DOTALL)
        anchor, width = "", ""
        if m:
            inner = _split_top_level(m.group(1), ",")
            anchor = inner[0].strip() if inner else ""
            width = inner[1].strip() if len(inner) > 1 else ""
        if not anchor:
            return ""

        body = self._read_glossary_entry(path, option)
        if not body:
            return anchor
        style = f' style="width:{width}"' if width else ' style="width:400px"'
        return (
            f'<div class="wims_tooltip">{anchor}'
            f'<div class="wims_tooltiptext"{style}>'
            f'<div class="wims_glossary">{body}</div></div></div>'
        )

    def _read_glossary_entry(self, path: str, option: str) -> str:
        """Contenu d'une fiche de glossaire.

        Les fiches sont découpées en *records* par des lignes réduites à `:`.
        L'en-tête (les `!set gl_title=…`) précède le premier séparateur et n'est
        pas un record, si bien que les records **pairs** portent le contenu —
        c'est ce que suppose la boucle de `glossary.phtml` (`!if $[$j%2]=0`),
        qui lit les records 4..N et traite les impairs comme des noms de fiches
        à inclure.
        """
        scripts_dir = self._find_wims_scripts_dir()
        if not scripts_dir:
            return ""
        data_dir = os.path.join(scripts_dir, "data", "glossary")
        full = os.path.normpath(os.path.join(data_dir, path))
        # Le chemin vient du .def, mais restons dans l'arborescence glossaire.
        if not full.startswith(os.path.normpath(data_dir) + os.sep):
            return ""
        if not os.path.isfile(full):
            return ""
        try:
            with open(full, encoding="utf-8") as fh:
                text = fh.read()
        except (UnicodeDecodeError, OSError):
            try:
                with open(full, encoding="latin-1") as fh:
                    text = fh.read()
            except OSError:
                return ""

        records = re.split(r"(?:^|\n):[ \t]*(?=\n|$)", text)[1:]
        if not records:
            return ""
        if re.search(r"content\s*=\s*\[?\s*abstract", option):
            wanted = [1]
        else:
            wanted = list(range(4, len(records) + 1))
        out: list[str] = []
        for j in wanted:
            rec = records[j - 1].strip() if j <= len(records) else ""
            if not rec:
                continue
            if j % 2 == 0:
                out.append(rec)
            else:
                # Record impair non vide : un nom de fiche à inclure (macros).
                out.append(self._read_glossary_entry(rec, option))
        return "\n".join(x for x in out if x)

    def _render_editarea(self, args: str) -> str:
        """``editarea <code>`` — bloc de code en lecture seule.

        Port d'`oef/special/editarea.phtml` : tabulations promues en sauts de
        ligne, puis un `textarea` en lecture seule dimensionné sur le contenu
        (`cols` = ligne la plus longue + 20, `rows` = nombre de lignes). WIMS y
        ajoute la coloration syntaxique d'EditArea ; sans elle le code reste
        parfaitement lisible.

        Sans ce rendu, `oefpython.fr/liste_portee1` demandait la valeur finale
        d'un script Python **que l'énoncé n'affichait pas** : l'exercice était
        insoluble, pas seulement dégradé.
        """
        import html as _html  # noqa: PLC0415

        code = args.replace("\t", "\n").strip("\n")
        if not code.strip():
            return ""
        lines = code.split("\n")
        cols = max((len(line) for line in lines), default=0) + 20
        return (
            f'<textarea class="wims_show" cols="{cols}" rows="{len(lines)}" '
            f'readonly="readonly">{_html.escape(code)}</textarea>'
        )

    def _render_expandlines(self, args: str) -> str:
        """``expandlines <texte>`` — bloc préformaté dont les tabulations sont
        des sauts de ligne (`oef/special/expandlines.phtml`)."""
        return f"<pre>{args.replace(chr(9), chr(10))}</pre>"

    def _render_special_help(self, args: str) -> str:
        """``help <sujet>, <libellé>`` — lien vers l'aide du module.

        PAX n'a pas (encore) de pages d'aide par module, donc le lien ne mène
        nulle part ; on rend le libellé comme WIMS le fait déjà en mode examen
        (`<span class="disabled_link">`). L'important est que le texte cesse de
        disparaître de l'énoncé : `\\special{help fscient, format scientifique}`
        rendait le vide au milieu d'une phrase.
        """
        parts = _split_top_level(args, ",")
        prompt = ",".join(parts[1:]).strip() if len(parts) > 1 else args.strip()
        if not prompt:
            return ""
        import html as _html  # noqa: PLC0415

        subject = _html.escape(parts[0].strip(), quote=True)
        return (
            f'<span class="disabled_link oef_specialhelp" data-help="{subject}">'
            f"{prompt}</span>"
        )

    def _render_tooltip(self, args: str) -> str:
        """``tooltip <ancre>,<options>,<texte>`` — infobulle CSS.

        Port de la branche moderne d'`oef/special/tooltip.phtml` : un `span`
        (ou un `div` si le texte porte du balisage) contenant l'ancre puis le
        texte dans un `.wims_tooltiptext`. La variante `DURATION` s'appuie sur
        `wz_tooltip.js`, absent de PAX ; on la rend avec la même structure CSS
        plutôt qu'avec du JavaScript mort — l'infobulle reste consultable, seul
        le minutage se perd.
        """
        parts = _split_top_level(args, ",")
        anchor = self._cmd_declosing(parts[0].strip()) if parts else ""
        # `!set text=!item 3 to -1` ; s'il est vide, l'item 2 était le texte et
        # non les options.
        option = parts[1].strip() if len(parts) > 2 else ""
        text = ",".join(parts[2:]).strip() if len(parts) > 2 else (
            parts[1].strip() if len(parts) > 1 else ""
        )
        text = text.replace("&#59;", ";").replace("&#44;", ",")
        text = self._cmd_declosing(text)
        if not anchor:
            # `!if $parm1 = $empty` : sans ancre, WIMS n'émet que le texte.
            return text
        if not text:
            return anchor

        css_class = style = ""
        if option and "DURATION" not in option:
            opt = self._cmd_declosing(option)
            cm = re.search(r"\bclass\s*=\s*([^\s,]+)", opt)
            sm = re.search(r"\bstyle\s*=\s*([^,]+)", opt)
            css_class = self._cmd_declosing(cm.group(1)).strip() if cm else ""
            style = self._cmd_declosing(sm.group(1)).strip() if sm else ""
        # `!detag $text = $text` : un texte balisé ne peut pas vivre dans un
        # `span` (HTML invalide dès qu'il contient un bloc).
        tag = "span" if re.sub(r"<[^>]*>", "", text) == text else "div"
        style_attr = f' style="{style}"' if style else ""
        inner_class = f"wims_tooltiptext {css_class}".strip()
        return (
            f'<{tag} class="wims_tooltip">{anchor}'
            f'<{tag} class="{inner_class}"{style_attr}>{text}</{tag}>'
            f"</{tag}>"
        )

    def _render_mathmlinput(self, args: str) -> str:
        """``mathmlinput [EXPR],<size>,<opts>\\t<replyN,size>…`` — render EXPR as
        math with each ``replyN`` token replaced by an inline answer field
        (WIMS' ``\\input{…}`` in the math). ``reply1^{reply2}`` thus becomes a
        base field with a superscript exponent field, as in elassaoui3.

        Mirrors ``oef/special/mathmlinput.phtml``: tabs become whitespace (the
        wrapped EXPR keeps its tab as a harmless newline; the option/reply lines
        are tab-separated), the bracketed EXPR is item 1, then line 1 is the
        default size and the remaining lines are ``replyN,size``.
        """
        s = args.replace("\t", "\n")
        # The EXPR is the leading ``[…]`` — but it may itself contain ``[``/``]``
        # (intervals ``\left[…\right]``, carlo1). A non-greedy ``\[(.*?)\]`` stops
        # at the inner ``]`` and truncates the closing delimiter; match the
        # bracket-balanced span instead.
        start = s.find("[")
        if start < 0:
            return ""
        depth = 0
        end = -1
        for j in range(start, len(s)):
            if s[j] == "[":
                depth += 1
            elif s[j] == "]":
                depth -= 1
                if depth == 0:
                    end = j
                    break
        if end < 0:
            return ""
        code = s[start + 1 : end]
        rest_lines = re.sub(r"^\s*,?", "", s[end + 1 :]).split("\n")
        opt_line = rest_lines[0] if rest_lines else ""
        dm = re.search(r"\d+", opt_line)
        default_size = int(dm.group(0)) if dm else 5
        sizes: dict[str, int] = {}
        for ln in rest_lines[1:]:
            cells = [c.strip() for c in ln.split(",")]
            if not cells or not cells[0]:
                continue
            num = re.search(r"\d+", cells[0])
            if not num:
                continue
            name = f"reply{num.group(0)}"
            try:
                sizes[name] = int(cells[1]) if len(cells) > 1 and cells[1] else default_size
            except ValueError:
                sizes[name] = default_size
        return self._mathmlinput_html(code, sizes, default_size)

    def _mathmlinput_html(self, code: str, sizes: dict[str, int], default_size: int) -> str:
        """Render mathmlinput (math + ``replyN`` fields).

        A container that embeds fields — matrix/array, ``\\left…\\right``
        vector/interval/set, ``\\frac``, ``\\vec``/``\\overrightarrow``, with a
        prefix/suffix or nested — is emitted as **native MathML** (like WIMS):
        the browser stretches the ``<mo>`` fences / ``<mfrac>`` to the content
        height, and the fields sit in ``<annotation-xml>`` cells. Plain code
        (no container — elassaoui3's ``reply1^{reply2}``) uses the inline
        interleave (KaTeX + inputs)."""
        code = re.sub(r"^\s*\\displaystyle\s*", "", code.strip())
        structural = r"\\begin\{|\\left\b|\\right\b|\\[dt]?frac\b|\\overrightarrow\b|\\vec\b|\\overline\b"
        if re.search(structural, code) and re.search(r"reply\d", code):
            body = self._mml_mathml(code, sizes, default_size)
            return f'<math class="oef-mathml" display="inline">{body}</math>'
        return self._mathmlinput_inline(code, sizes, default_size)

    def _mml_annot(self, html: str) -> str:
        """Embed an HTML fragment (KaTeX spans + answer ``<input>``) inside
        MathML via ``<semantics><annotation-xml>`` — WIMS' way of placing form
        fields in math (the browser keeps them interactive)."""
        return (
            '<semantics><annotation-xml encoding="application/xhtml+xml">'
            f'<span xmlns="http://www.w3.org/1999/xhtml">{html}</span>'
            "</annotation-xml></semantics>"
        )

    def _mml_mathml(self, code: str, sizes: dict, default_size: int, depth: int = 0) -> str:
        """Recursively render a mathmlinput container to native MathML:
        ``\\begin{…}`` → ``<mtable>``, ``\\left…\\right`` → stretchy ``<mo>``
        fences, ``\\frac`` → ``<mfrac>``, ``\\vec``/``\\overrightarrow`` →
        ``<mover>``; a run of static math + fields becomes one
        ``<annotation-xml>`` HTML chunk (KaTeX + inputs). Handles prefixes,
        suffixes, nesting (frac in a matrix cell) and WIMS' unmatched ``\\left``
        (half-open interval)."""
        out: list[str] = []
        static: list[str] = []

        def flush() -> None:
            s = "".join(static).strip()
            static.clear()
            if s:
                out.append(self._mml_annot(self._mathmlinput_inline(s, sizes, default_size)))

        beg = re.compile(r"\\begin\{(\w+)\}(?:\{[^}]*\})?")
        left = re.compile(r"\\left\s*(" + self._DELIM_TOK + ")")
        right = re.compile(r"\\right\s*(" + self._DELIM_TOK + ")")
        frac = re.compile(r"\\[dt]?frac\b")
        over = re.compile(r"\\(overrightarrow|vec|overline)\b")
        i, n = 0, len(code)
        while i < n:
            if depth < 12 and (m := frac.match(code, i)):
                a = self._mml_brace(code, m.end())
                b = self._mml_brace(code, a[1]) if a else None
                if a and b and re.search(r"reply\d", a[0] + b[0]):
                    flush()
                    out.append(
                        f"<mfrac><mrow>{self._mml_mathml(a[0], sizes, default_size, depth + 1)}</mrow>"
                        f"<mrow>{self._mml_mathml(b[0], sizes, default_size, depth + 1)}</mrow></mfrac>"
                    )
                    i = b[1]
                    continue
            if depth < 12 and (m := over.match(code, i)):
                a = self._mml_brace(code, m.end())
                if a and re.search(r"reply\d", a[0]):
                    flush()
                    acc = "¯" if m.group(1) == "overline" else "→"
                    out.append(
                        '<mover accent="true"><mrow>'
                        f"{self._mml_mathml(a[0], sizes, default_size, depth + 1)}</mrow>"
                        f"<mo>{acc}</mo></mover>"
                    )
                    i = a[1]
                    continue
            if depth < 12 and (m := beg.match(code, i)):
                res = self._mml_find_end(code, m.end(), m.group(1))
                if res:
                    flush()
                    out.append(self._mml_mathml_table(code[m.end():res[0]], m.group(1), sizes, default_size, depth))
                    i = res[1]
                    continue
            if depth < 12 and (m := left.match(code, i)):
                res = self._mml_find_right(code, m.end())
                if res:
                    flush()
                    r_idx, r_end, rtok = res
                    ld = self._DELIM_DISPLAY.get(m.group(1), "")
                    rd = self._DELIM_DISPLAY.get(rtok, "")
                    lo = f'<mo fence="true" stretchy="true">{ld}</mo>' if ld else ""
                    ro = f'<mo fence="true" stretchy="true">{rd}</mo>' if rd else ""
                    inner = self._mml_mathml(code[m.end():r_idx], sizes, default_size, depth + 1)
                    out.append(f"<mrow>{lo}{inner}{ro}</mrow>")
                    i = r_end
                    continue
                # Unmatched \left (WIMS half-open interval [a;b[) → plain operator.
                flush()
                g = self._DELIM_DISPLAY.get(m.group(1), "")
                if g:
                    out.append(f"<mo>{g}</mo>")
                i = m.end()
                continue
            if (m := right.match(code, i)):
                flush()
                g = self._DELIM_DISPLAY.get(m.group(1), "")
                if g:
                    out.append(f"<mo>{g}</mo>")
                i = m.end()
                continue
            static.append(code[i])
            i += 1
        flush()
        return "".join(out)

    def _mml_mathml_table(self, body: str, env: str, sizes: dict, default_size: int, depth: int) -> str:
        """Matrix/array body → MathML ``<mtable>``; a matrix env adds its fences."""
        rows = []
        for row in re.split(r"\\\\", body):
            row = re.sub(r"\\hline", "", row).strip()
            if not row:
                continue
            cells = "".join(
                f"<mtd>{self._mml_mathml(c.strip(), sizes, default_size, depth + 1)}</mtd>"
                for c in re.split(r"&(?!#?\w+;)", row)
            )
            rows.append(f"<mtr>{cells}</mtr>")
        table = f'<mtable>{"".join(rows)}</mtable>'
        md = self._MATRIX_DELIMS.get(env)
        if md and (md[0] or md[1]):
            lo = f'<mo fence="true" stretchy="true">{md[0]}</mo>' if md[0] else ""
            ro = f'<mo fence="true" stretchy="true">{md[1]}</mo>' if md[1] else ""
            return f"<mrow>{lo}{table}{ro}</mrow>"
        return table

    # Matrix env → (left, right) delimiter characters.
    _MATRIX_DELIMS = {
        "pmatrix": ("(", ")"), "bmatrix": ("[", "]"), "Bmatrix": ("{", "}"),
        "vmatrix": ("|", "|"), "Vmatrix": ("‖", "‖"), "matrix": ("", ""),
    }
    # WIMS/TeX delimiter token (after \left / \right) → displayed character.
    # "." is the invisible delimiter (\left. … \right) — no glyph.
    _DELIM_TOK = (
        r"\\lbrace|\\rbrace|\\lbracket|\\rbracket|\\lvert|\\rvert|"
        r"\\langle|\\rangle|\\\{|\\\}|\\\||[()\[\].|]"
    )
    _DELIM_DISPLAY = {
        "(": "(", ")": ")", "[": "[", "]": "]", ".": "", "|": "|",
        "\\{": "{", "\\}": "}", "\\|": "‖", "\\lbrace": "{", "\\rbrace": "}",
        "\\lbracket": "[", "\\rbracket": "]", "\\lvert": "|", "\\rvert": "|",
        "\\langle": "⟨", "\\rangle": "⟩",
    }

    def _mml_find_right(self, code: str, start: int):
        """From ``start`` (just after a ``\\left<delim>``), return
        ``(idx, end, right_token)`` of the matching ``\\right<delim>`` (depth-aware
        over nested ``\\left``/``\\right``), or ``None``."""
        depth = 0
        i, n = start, len(code)
        lo = re.compile(r"\\left\s*(" + self._DELIM_TOK + ")")
        ro = re.compile(r"\\right\s*(" + self._DELIM_TOK + ")")
        while i < n:
            if (m := lo.match(code, i)):
                depth += 1; i = m.end(); continue
            if (m := ro.match(code, i)):
                if depth == 0:
                    return i, m.end(), m.group(1)
                depth -= 1; i = m.end(); continue
            i += 1
        return None

    def _mml_find_end(self, code: str, start: int, env: str):
        """Return ``(idx, end)`` of the ``\\end{env}`` matching the ``\\begin{env}``
        whose body starts at ``start`` (depth-aware), or ``None``."""
        depth = 0
        i, n = start, len(code)
        beg = re.compile(r"\\begin\{" + re.escape(env) + r"\}(?:\{[^}]*\})?")
        end = re.compile(r"\\end\{" + re.escape(env) + r"\}")
        while i < n:
            if (m := beg.match(code, i)):
                depth += 1; i = m.end(); continue
            if (m := end.match(code, i)):
                if depth == 0:
                    return i, m.end()
                depth -= 1; i = m.end(); continue
            i += 1
        return None

    def _mml_brace(self, code: str, start: int):
        """From ``start``, skip spaces and return ``(content, end)`` of the
        ``{…}`` brace group (depth-aware), or ``None`` if no ``{`` follows."""
        i = start
        while i < len(code) and code[i].isspace():
            i += 1
        if i >= len(code) or code[i] != "{":
            return None
        depth = 0
        for j in range(i, len(code)):
            if code[j] == "{":
                depth += 1
            elif code[j] == "}":
                depth -= 1
                if depth == 0:
                    return code[i + 1 : j], j + 1
        return None

    def _mathmlinput_inline(self, code: str, sizes: dict[str, int], default_size: int) -> str:
        """Inline interleave: ``\\(…\\)`` math chunks with native
        ``<input class="oef-input">`` fields, ``^{replyN}`` exponents wrapped in
        ``<sup>``. Stays one HTML segment so the frontend KaTeX-renders the math
        and event-delegation binds the inputs."""
        sup_map: dict[str, str] = {}
        inp_map: dict[str, str] = {}

        def sup_repl(mm: re.Match) -> str:
            key = f"\x00S{len(sup_map)}\x00"
            sup_map[key] = mm.group(1)
            return key

        def inp_repl(mm: re.Match) -> str:
            key = f"\x00I{len(inp_map)}\x00"
            inp_map[key] = mm.group(1)
            return key

        # Mark exponent fields (^{replyN} / ^replyN) first, then the plain ones.
        code = re.sub(r"\^\{\s*(reply\d+)\s*\}", sup_repl, code)
        code = re.sub(r"\^\s*(reply\d+)\b", sup_repl, code)
        # Absorb TeX *grouping* braces around a lone field — `{reply3}` (fonction93's
        # interval bounds). The split would otherwise strand the `{`/`}` in adjacent
        # `\(…\)` spans (unbalanced → KaTeX error). The lookbehind keeps command
        # arguments (`\frac{reply}`, `\sqrt{reply}`, second arg `}{reply}`) intact.
        code = re.sub(r"(?<![A-Za-z}])\{\s*(reply\d+)\s*\}", inp_repl, code)
        code = re.sub(r"\b(reply\d+)\b", inp_repl, code)

        def field(name: str) -> str:
            width = max(sizes.get(name, default_size) + 2, 4)
            return (
                f'<input type="text" class="oef-input" name="{name}" autocomplete="off" '
                f'style="width:{width}ch;min-width:3ch;text-align:center" />'
            )

        out: list[str] = []
        for seg in re.split(r"(\x00[SI]\d+\x00)", code):
            tm = re.match(r"\x00([SI])\d+\x00$", seg)
            if tm:
                name = (sup_map if tm.group(1) == "S" else inp_map)[seg]
                inp = field(name)
                out.append(f"<sup>{inp}</sup>" if tm.group(1) == "S" else inp)
            elif seg.strip():
                out.append(f"\\({seg.strip()}\\)")
        return "".join(out)

    def severite(self) -> dict[str, float]:
        """Les dix réglages du niveau de sévérité, pour cet exercice.

        `qcmlevel` fait foi, et chaque réglage peut être écrasé isolément — c'est
        exactement ce que fait `oef/exo.init` avec ses `!default`. Le niveau par
        défaut est 1, celui de WIMS (`oef/default`).
        """
        def _nombre(nom: str) -> float | None:
            brut = self._subst(str(self.ctx.get(nom, ""))).strip()
            try:
                return float(brut)
            except (TypeError, ValueError):
                return None

        niveau = int(_nombre("qcmlevel") or _NIVEAU_DEFAUT)
        niveau = min(max(niveau, 1), 9)
        out: dict[str, float] = {"qcmlevel": float(niveau)}
        for cle, paliers in _SEVERITE.items():
            pose = _nombre(cle)
            out[cle] = paliers[niveau - 1] if pose is None else pose
        return out

    def _prepare_choices(self, df: "DefFile") -> None:
        """Compose la liste déroulante de chaque `\\choice`, façon `oef/var.prep`.

        `\\choice{titre}{bonne}{mauvaises}` est une construction OEF distincte de
        `\\answer` : elle produit un **menu déroulant**, et 346 exercices du
        corpus en posent au moins un. PAX les ignorait — `\\embed{c1}` rendait
        un champ de saisie libre que rien ne notait, et l'élève devait deviner
        la phrase attendue au lieu de la choisir.

        La composition suit `var.prep` pas à pas :

            cbad = !listcomplement $cgood in !listuniq $(choicebad$i)
            shf  = !shuffle $cgood,$cbad
            cli  = !item 1 to $qcmpresent of $shf
            choicelist$i = !sort nocase list $cli     (ou !shuffle si `shuffle`)
            choicegood$i = !listintersect $cgood and $cli

        Deux détails valent d'être notés. Les mauvaises réponses sont purgées
        de celles qui figurent aussi parmi les bonnes — `OEFpythagore2` liste
        « est rectangle, n'est pas rectangle » comme mauvaises alors que la
        première est la bonne. Et la liste finale est **triée**, non mélangée,
        sauf mention `shuffle` : l'ordre ne doit pas trahir la réponse.
        """
        # ── Niveau de sévérité ────────────────────────────────────────────
        # Chez WIMS, l'enseignant qui pose l'exercice sur une feuille choisit un
        # `qcmlevel` de 1 à 9, et ce seul curseur commande dix réglages
        # (`oef/exo.init`). Deux nous concernent ici :
        #
        #     qcmpresent = !item $qcmlevel of 3,3,4,5,5,6,7,8,8
        #     qcmgood    = !item $qcmlevel of 1,1,1,1,0,0,0,0,0
        #
        # `qcmpresent` est le nombre de propositions montrées — moins il y en
        # a, plus l'exercice est facile. `qcmgood` dit si la bonne réponse est
        # **garantie** parmi elles. PAX n'a pas encore ce curseur côté feuille :
        # il prend le défaut de WIMS, le niveau 1, et le `.def` peut l'écraser.
        sev = self.severite()
        qcmpresent = int(sev["qcmpresent"])
        qcmgood_defaut = int(sev["qcmgood"])

        for cm in df.choice_meta:
            n = cm.get("n")
            if n is None:
                continue
            # La bonne réponse reste **entière**. `choicegood` est une liste
            # WIMS, mais plusieurs exercices y écrivent une seule option qui
            # contient une virgule — « le preterit, le participe passé »
            # (`oefanglais/Verbesirrgulie4`), « les communes de France,les
            # grandes villes de France » (`oefstatproba/bergamo1`). La découper
            # en fabriquait deux, dont aucune n'était la réponse attendue.
            bons = [self._subst(cm.get("good", "")).strip()]
            bons = [x for x in bons if x]
            mauvais = [
                x for x in _uniques(wl.cutitems(self._subst(cm.get("bad", "")).strip()))
                if x not in bons
            ]
            if not bons and not mauvais:
                continue
            rng = random.Random(f"{self.seed}_choice{n}")
            qcmgood = qcmgood_defaut
            if len(bons) <= 1 and qcmgood > 0 and len(mauvais) > 1:
                # `var.prep`, branche « la bonne réponse est garantie » : elle
                # passe **en tête**, et la troncature ne peut donc pas
                # l'emporter. Le premier leurre est lui aussi préservé — WIMS ne
                # mélange que les suivants (`ccbad=!item 2 to -1 of $cbad`),
                # l'auteur ayant souvent mis en premier le piège qu'il tient à
                # montrer.
                reste = mauvais[1:]
                rng.shuffle(reste)
                cli = (bons + [mauvais[0]] + reste)[:qcmpresent]
            else:
                melange = bons + mauvais
                rng.shuffle(melange)
                cli = melange[:qcmpresent]
                if qcmpresent <= len(mauvais):
                    # La bonne réponse a pu disparaître : WIMS offre alors une
                    # échappatoire honnête plutôt que de piéger l'élève.
                    qcmgood = 0
            option = self._subst(cm.get("option", "")).lower()
            if "shuffle" in option.split():
                rng.shuffle(cli)
            else:
                cli = sorted(cli, key=str.casefold)
            # La liste voyage **en Python**, pas en chaîne : la rejoindre par
            # des virgules puis la recouper perdrait les options qui en
            # contiennent une (cf. ci-dessus).
            self._choice_lists[str(n)] = cli
            self._choice_none[str(n)] = qcmgood < 1
            self.ctx[f"choicelist{n}"] = ",".join(cli)
            self.ctx[f"choiceitems{n}"] = str(len(cli))

    def _render_embed(self, args: str) -> str:
        """Render an !read oef/embed.phtml marker as an input span."""
        args = self._subst(args).strip()
        # Parse: "r1,10" or "reply1,$val10" or "r1" etc.
        parts = [p.strip() for p in args.split(",")]
        ref = parts[0] if parts else "reply1"
        size_str = parts[1] if len(parts) > 1 else "10"
        # A-t-on **écrit** un second argument ? `size_str` vaut `"10"` par
        # défaut, et les branches qui y lisent un rang (checkbox, mark) ne
        # savaient pas distinguer ce défaut d'un index voulu. `oefarith/Critere4`
        # écrit `!read oef/embed.phtml reply1`, sans rien : sa palette de douze
        # propositions se réduisait à la seule dixième — 10 tombant dans
        # `1..12`, la garde d'intervalle ne le voyait pas.
        index_donne = len(parts) > 1

        # Le **second** argument porte lui aussi des variables de boucle. Le
        # `.def` compilé garde la forme OEF `\j` là où l'exécution pose `m_j` :
        #
        #     !for m_j=1 to $val16
        #       !read oef/embed.phtml r1,\j
        #
        # Seul le nom de la réponse était résolu (plus bas). L'index restait
        # `\j`, aucun chiffre n'en sortait, et la branche `checkbox` retombait
        # sur « pas d'index → toute la palette » : `patron1` affichait ses trois
        # figures **à chaque tour**, soit neuf cases pour trois choix
        # (`value="1,2,3,1,2,3,1,2,3"`).
        #
        # On garde `\nom` intact quand la variable n'existe pas — contrairement
        # à la résolution du nom de réponse, qui laisse tomber la contre-oblique.
        # Ici le texte peut être une largeur ou une expression, et le mutiler
        # coûterait plus que de le laisser passer.
        def _var_de_boucle(m: re.Match) -> str:
            nom = m.group(1)
            for candidat in (nom, nom.lower(), f"m_{nom}", f"m_{nom.lower()}"):
                if candidat in self.ctx:
                    return str(self.ctx[candidat])
            return m.group(0)

        size_str = re.sub(r"\\(\w+)", _var_de_boucle, size_str)

        # Some .def files write `reply 1,30` (space between word and index)
        # instead of `reply1,30`; collapse internal whitespace so the ref
        # matches the answer's input_name.
        ref = re.sub(r"\s+", "", ref)

        # `\embed{c<n>}` désigne un `\choice`, non une réponse : un menu
        # déroulant dont les options ont été composées par `_prepare_choices`.
        # WIMS nomme le champ `choice$i` (`oef/formc.phtml`), et c'est ce nom
        # que la notation attend.
        mc = re.fullmatch(r"c(\d+)", ref)
        if mc and f"choicelist{mc.group(1)}" in self.ctx:
            import html as _html  # noqa: PLC0415

            nc = mc.group(1)
            etiquette = _html.escape(
                self._subst(self.ctx.get(f"choicename{nc}", "")).strip()
            )
            # Sans cet enregistrement, le filtre par étape écarte le
            # champ : il ne garde que ce que `_render_embed` a posé.
            self._touched_replies.add(f"c{nc}")
            return (
                f'<span class="oef-menu" name="c{nc}" '
                f'data-label="{etiquette}"></span>'
            )

        # Normalise reply ref: r1 → reply1, r\1 → reply1 (loop var refs),
        # reply\h → reply1 (same loop-var substitution, just with the
        # full `reply` prefix the author wrote). `rep1` (tavernier1) is the same
        # reply 1 — WIMS keys the reply off the trailing index regardless of the
        # `reply`/`rep`/`r` spelling. Match the longest prefix first so `reply…`
        # and `rep…` aren't truncated to a bare `r`.
        prefix = None
        for p in ("reply", "rep", "r"):
            if ref.startswith(p):
                prefix = p
                break
        if prefix is not None:
            suffix = ref[len(prefix):]
            # 1. Handle loop variables like \qq in r\qq or reply\h
            def resolve_loop_var(m):
                name = m.group(1)
                # Try exact, then lowercase, then with m_ prefix (compiler artifact)
                for candidate in (name, name.lower(), f"m_{name}", f"m_{name.lower()}"):
                    if candidate in self.ctx:
                        return str(self.ctx[candidate])
                return name

            suffix = re.sub(r"\\(\w+)", resolve_loop_var, suffix)
            # 2. Evaluate bracketed expressions like \[3*\k-2]
            suffix = re.sub(
                r"\\?\[(.+?)\]",
                lambda m: self._eval_arith(m.group(1).replace("\\", "$")),
                suffix,
            )
            suffix_val = self._subst(suffix)
            try:
                # Suffix might still contain a variable reference like $m_qq
                ref = f"reply{int(float(suffix_val))}"
            except (ValueError, TypeError, OverflowError):
                # Le suffixe n'est pas un nombre : WIMS y lit une **expression**.
                # `oef/embed.phtml` ne garde du nom que les chiffres et les
                # opérateurs, puis les évalue —
                #
                #     n_=!text select 0123456789()+-* in $n_
                #     n_=$[$n_]
                #     !bound n_ between integer 1 and 100
                #
                # `oefstatistiques/entreprise` écrit ses soixante champs
                # `!read oef/embed.phtml reply\jj+10`, où `\jj` est l'indice de
                # boucle : le nom se résolvait en « reply1+10 », qui ne
                # correspond à aucune réponse. Les champs s'affichaient bien,
                # l'élève pouvait y écrire, et rien n'était relié — soixante
                # réponses perdues sur un exercice qui en compte soixante-dix-neuf.
                filtre = re.sub(r"[^0-9()+\-*]", "", suffix_val)
                indice = None
                if filtre:
                    try:
                        indice = int(float(self._eval_arith(filtre)))
                    except (ValueError, TypeError, OverflowError, ZeroDivisionError):
                        indice = None
                ref = f"reply{indice}" if indice and 1 <= indice <= 100 else f"reply{suffix}"

        # Handle radio and menu types specially.
        reply_type = ""
        nm = re.match(r"^r(?:eply)?(\d+)$", ref)
        if nm:
            n = nm.group(1)
            # Record that this reply is referenced by the current statement.
            # Used in render() to filter `answers` for dynsteps/course exercises.
            self._touched_replies.add(f"reply{n}")
            reply_type = self._reply_type(n)
            if reply_type == "radio":
                # Inline radio: `reply{n},POS[,CONTENT]` places one choice *here*
                # in the statement (value = POS, label = CONTENT), instead of in
                # the grid zone below. Two author styles:
                #  - couf: explicit CONTENT (the choice text) → inline.
                #  - chgrhyper: `reply 1,1`..`reply 1,4` with NO content, where
                #    the choices are the bare position numbers `1,2,3,4` and each
                #    radio sits in a table next to its graph → inline, empty label.
                # (`ecrdecimal` a longtemps figuré ici comme contre-exemple,
                # son `reply \h,\s` passant pour une *taille*. Mesuré : `\s`
                # y vaut 1, 2, 3, 4 — c'est un rang, posé par un `!for`, comme
                # partout ailleurs.)
                # `size_str`, pas `parts[1]` : c'est lui qui porte la variable
                # de boucle résolue. `oeffonctgen/qcmensdef` écrit
                # `!read oef/embed.phtml reply 1,\t` dans un `!for m_t=2 to 4`,
                # et à relire `parts[1]` la branche voyait encore `\t` — donc
                # pas de rang, donc rien d'affiché : trois choix sur quatre
                # manquaient, dont le bon.
                pos = size_str.strip() if index_donne else ""
                content = ",".join(parts[2:]).strip() if len(parts) > 2 else ""
                inline = bool(pos) and bool(content)
                if pos and not content:
                    choices = self._inline_radio_choices(n)
                    # `reply{n},POS` sans contenu : c'est encore l'auteur qui
                    # place le choix, il en laisse simplement le texte à la
                    # palette. On le reprend de là — `OEFcone/patron00` fait
                    # suivre chaque choix de sa figure (`… : <dessin>`), et
                    # renvoyer le choix dans le bloc du bas laissait la figure
                    # sans étiquette et le « : » orphelin, deux fois de suite.
                    #
                    # La palette purement numérique (`chgrhyper`, où les choix
                    # *sont* les positions) garde son étiquette vide : le
                    # numéro est déjà porté par la figure d'à côté.
                    if pos.isdigit() and 1 <= int(pos) <= len(choices):
                        inline = True
                        numerique = choices == [
                            str(i) for i in range(1, len(choices) + 1)
                        ]
                        if not numerique:
                            # Le libellé peut porter du `\(…)` à la mode WIMS,
                            # que KaTeX ne lit pas tant qu'il n'est pas refermé —
                            # la branche classée le fait pour sa palette, il faut
                            # le faire ici aussi. Sans quoi `oefresolalg/synth1deg`
                            # sortait treize `\(` ouvrants pour cinq fermants.
                            content = _close_inline_math(choices[int(pos) - 1], self.lang)
                if inline:
                    import html as _h  # noqa: PLC0415
                    self._inline_radio = getattr(self, "_inline_radio", set())
                    self._inline_radio.add(str(n))
                    return (
                        f'<span class="oef-radio-inline" name="reply{n}" '
                        f'data-value="{pos}" data-content="{_h.escape(content, quote=True)}"></span>'
                    )
                # Plain radio: choices are rendered by the frontend in a
                # dedicated section below the statement; no widget here.
                return ""
            elif reply_type in ("mark", "click"):
                # mark: clickable choices, reply = the 1-based position clicked.
                # replygood = "correct_pos;choice1,choice2,...".
                # size_str may be a loop variable like "\r" — resolve \varname patterns.
                size_resolved = re.sub(
                    r"\\(\w+)",
                    lambda m: str(
                        self.ctx.get(m.group(1),
                        self.ctx.get(f"m_{m.group(1)}", m.group(0)))
                    ),
                    self._subst(size_str).strip(),
                )
                # Evaluate replygoodN — may still contain $var refs if seeded raw
                good_raw = self._subst(self.ctx.get(f"replygood{n}", ""))
                # Format : "pos;choice1,choice2,…". `oef/embed.phtml` lit ce
                # champ en `!rows2lines` puis `!distribute lines … into ts,tt`
                # (le `;` sépare la position des choix), et prend enfin
                # `!item N of $tt` : les choix se séparent à la virgule.
                if ";" in good_raw:
                    _pos_part, _, choices_part = good_raw.partition(";")
                else:
                    choices_part = good_raw
                choices = [c.strip() for c in wl.cutitems(choices_part) if c.strip()]

                def _mark_span(col: int) -> str:
                    label = self._subst(choices[col - 1]) if 1 <= col <= len(choices) else ""
                    return (
                        f'<span class="oef-mark-choice" name="{ref}" '
                        f'data-pos="{col}">{label}</span>'
                    )

                # A size_str naming a valid 1-based column → this embed is one
                # choice of a "split" group (author placed one \embed per column).
                # Otherwise (no index, or out of range — e.g. the leftover input
                # width "10") the single embed expands to all proposition choices,
                # as WIMS does by default.
                try:
                    col = int(float(size_resolved))
                except (ValueError, TypeError):
                    col = None
                if index_donne and col is not None and choices and 1 <= col <= len(choices):
                    return _mark_span(col)
                if choices:
                    return " ".join(_mark_span(i + 1) for i in range(len(choices)))
                return _mark_span(col or 1)
            elif reply_type in ("checkbox", "multipleclick"):
                # `anstype/multipleclick` a le contrat de `checkbox` : son
                # `replygood` s'écrit `<positions correctes>;<choix…>`, l'élève
                # en désigne plusieurs, et la note est une **égalité
                # d'ensembles** — `menupos=!listintersect $menupos and $good`
                # puis `$poscnt1=$poscnt2 and $poscnt1=$poscnt3`. (Le score
                # partiel n'entre en jeu que sous `split`/`partialscore`, qu'
                # aucun des sept exercices du corpus ne porte.) PAX n'en
                # connaissait pas le type : un seul champ de saisie, et
                # l'attendu gardait la liste d'images entière.
                # The student's reply is the set of checked option *indices*
                # (compared order-insensitively via check_set); the labels come
                # from the proposition list in replygood = "correct;prop1,prop2,…".
                good_raw = self._subst(self.ctx.get(f"replygood{n}", ""))
                labels_part = good_raw.partition(";")[2] if ";" in good_raw else ""
                # Smart comma split: don't break commas inside \(...\) math.
                labels = [
                    c.strip()
                    for c in re.split(r",(?![^(]*\))", labels_part)
                    if c.strip()
                ]

                def _box(i: int, label: str) -> str:
                    lbl = self._subst(label)
                    return (
                        f'<label class="oef-checkbox-label">'
                        f'<input type="checkbox" class="oef-checkbox" '
                        f'name="{ref}" value="{i}" /> {lbl}</label>'
                    )

                # A leading integer in size_str that names a valid 1-based option
                # → this embed is one box of a "split" group (author placed one
                # \embed per option via a \for loop). Otherwise (no index, or out
                # of range — e.g. the leftover input width "10") the single embed
                # expands to the whole proposition list, as WIMS does by default.
                idx_m = re.match(r"-?\d+", self._subst(size_str).strip())
                idx = int(idx_m.group()) if idx_m else None
                if index_donne and idx is not None and labels and 1 <= idx <= len(labels):
                    return _box(idx, labels[idx - 1])
                if labels:
                    return ", ".join(_box(i + 1, lbl) for i, lbl in enumerate(labels))
                # No proposition list available — fall back to a single box.
                value = self._subst(size_str).strip()
                return (
                    f'<input type="checkbox" class="oef-checkbox" '
                    f'name="{ref}" value="{value}" />'
                )
            elif reply_type == "menu":
                # Menus need a placeholder in the HTML for inline positioning
                label = self._subst(self.ctx.get(f"replyname{n}", "")).strip()
                return f'<span class="oef-menu" name="{ref}" data-label="{label}"></span>'
            elif reply_type == "clickfill":
                # Drag-compose answer: emit one target slot per cell. The embed
                # size is "W x H x N" (cell width/height in px, N = slot count,
                # e.g. repgraphint's 60x40x12). Fall back to the length of the
                # correct sequence when N is absent. All slots share `ref`; the
                # frontend composes their ordered, non-empty values into one
                # reply. Entity-safe split (replygood holds &#91;/&#93;/&#59;
                # whose ";" must not be read as the correct;pool separator).
                good_raw = self._subst(self.ctx.get(f"replygood{n}", ""))
                # WIMS treats "|" as a row separator too (anstype/fill.inc:15
                # does `!translate internal | to <newline>`), so `correct|pool`
                # is equivalent to `correct;pool`. Normalise before splitting.
                good_raw = good_raw.replace("|", ";")
                rows = wl.cutrows(good_raw)
                correct_items = [c for c in (rows[0].split(",") if rows else []) if c.strip()]
                size_parts = re.split(r"\s*[xX]\s*", self._subst(size_str).strip())
                nslots = 0
                if len(size_parts) >= 3:
                    try:
                        nslots = int(float(size_parts[2]))
                    except (ValueError, TypeError):
                        nslots = 0
                if nslots <= 0:
                    nslots = len(correct_items) or 1
                try:
                    slot_w = int(float(size_parts[0])) if size_parts else 0
                except (ValueError, TypeError):
                    slot_w = 0
                w_attr = f' data-w="{slot_w}"' if slot_w > 0 else ""
                return "".join(
                    f'<cf-slot name="{ref}" data-index="{i}"{w_attr}></cf-slot>'
                    for i in range(nslots)
                )
            elif reply_type == "correspond":
                # `correspond`: bijection between two columns. replygood
                # is "left1,left2,...;right1,right2,..." (rows separated
                # by ``;``, items by ``,`` — same format as `\column N of`).
                # The right column is shuffled at render time; the user
                # reorders it to match. Size is "V x HG x HD" (vertical,
                # left width, right width).
                import json as _json  # noqa: PLC0415
                import random as _random  # noqa: PLC0415
                good_raw = self._subst(self.ctx.get(f"replygood{n}", ""))
                rows = wl.cutrows(good_raw)
                if len(rows) != 2:
                    return ""
                # Close WIMS inline math `\(…)` to KaTeX `\(…\)` so the
                # frontend typesets the labels (e.g. `\(x \mapsto 2x-2)`); a
                # no-op for plain text.
                # Each column is a WIMS list: TAB-separated when items contain
                # commas (e.g. coordinates "(-1,-2)\t(2,-1)"), otherwise
                # comma-separated. Split per-column so the two sides line up;
                # a bare comma split would yield e.g. 3 colours but 1 coord
                # blob, fail the bijection check below, and render nothing.
                lefts = [self._prep_correspond_item(c) for c in self._split_correspond_column(rows[0])]
                rights = [self._prep_correspond_item(c) for c in self._split_correspond_column(rows[1])]
                if not lefts or len(lefts) != len(rights):
                    return ""
                # Deterministic shuffle from the engine seed + reply index
                rng = _random.Random(f"{self.seed}_correspond_{n}")
                rights_shuffled = list(rights)
                rng.shuffle(rights_shuffled)
                # Parse size "V x HG x HD"
                size_raw = self._subst(size_str).strip()
                size_parts = re.split(r"\s*[xX]\s*", size_raw)
                try:
                    sizev = int(size_parts[0]) if len(size_parts) >= 1 else 40
                    sizeh1 = int(size_parts[1]) if len(size_parts) >= 2 else 200
                    sizeh2 = int(size_parts[2]) if len(size_parts) >= 3 else sizeh1
                except (ValueError, TypeError):
                    sizev, sizeh1, sizeh2 = 40, 200, 200
                opt_str = self._subst(self.ctx.get(f"replyoption{n}", "")).lower()
                partial = "split" in opt_str or "partialscore" in opt_str
                config = _json.dumps({
                    "lefts": lefts,
                    "rights": rights_shuffled,
                    "sizev": sizev,
                    "sizeh1": sizeh1,
                    "sizeh2": sizeh2,
                    "partial": partial,
                }, ensure_ascii=False)
                # Stash for _extract_answers so AnswerDef gets the same
                # expected/options without re-parsing.
                self._correspond_meta = getattr(self, "_correspond_meta", {})
                self._correspond_meta[ref] = {
                    "lefts": lefts,
                    "rights_correct": rights,
                    "rights_shuffled": rights_shuffled,
                    "sizev": sizev, "sizeh1": sizeh1, "sizeh2": sizeh2,
                    "partial": partial,
                }
                import html as _html  # noqa: PLC0415
                return (
                    f'<span class="oef-correspond" name="{ref}" '
                    f'data-config="{_html.escape(config)}"></span>'
                )

            elif reply_type == "jsxgraph":
                # `type=jsxgraph`: the answer field *is* an interactive board.
                # Render the board (display) here; the script has commas, so we
                # re-parse the raw args instead of the comma-split `size_str`.
                return self._render_jsxgraph_embed(args, ref)
            elif reply_type == "js2wims1":
                # `type=js2wims1` : WIMS en fait un `<input type=hidden>` que
                # son JavaScript remplit à l'envoi. L'élève n'y écrit jamais —
                # les valeurs viennent du programme joué dans le `runcode`
                # voisin, qui les dépose (cf. `_render_runcode_embed`). Rendre
                # un champ de saisie ici, c'est en offrir un que rien ne peut
                # remplir : les quatorze champs du module en affichaient un.
                return ""
            elif reply_type == "runcode":
                # `type=runcode` : l'éditeur de code **est** le champ. Arguments
                # bruts — le code initial est plein de virgules.
                return self._render_runcode_embed(args, ref, n)
            elif reply_type == "reaction":
                # `type=reaction` : le champ **est** un chronomètre. L'élève
                # appuie sur GO, attend, puis frappe STOP le plus vite
                # possible ; la réponse est la liste des temps mesurés.
                return self._render_reaction_embed(args, ref, n)
            elif reply_type == "jmolclick":
                # `type=jmolclick` : la molécule **est** le champ, et l'élève y
                # clique les atomes. Arguments bruts — le script Jmol qui suit
                # la taille est plein de virgules.
                return self._render_jmolclick_embed(args, ref, n)
            elif reply_type == "geogebra":
                # `type=geogebra` : le champ de réponse *est* une applet, que
                # l'élève manipule. Arguments bruts — la configuration est
                # pleine de virgules (`setCoordSystem(-10,10,-10,10)`).
                return self._render_geogebra_answer_embed(args, ref, n)
            elif reply_type == "jsxgraphobjet":
                # Même figure, autre geste : ici l'élève *clique* des objets
                # nommés plutôt que d'en déplacer un. Les arguments bruts pour
                # la même raison — le script est plein de virgules.
                return self._render_jsxgraphobjet_embed(args, ref, n)
            elif reply_type == "coord":
                # `type=coord`: the field is a clickable repère image (WIMS'
                # `<input type=image>`). `replygood{n}` = "<image_url>;<zone>"
                # (rows split on ';'); the first row is the background to click.
                good = self._subst(self.ctx.get(f"replygood{n}", "")).strip()
                img = good.split(";", 1)[0].strip()
                if img:
                    return f'<span class="oef-coord" name="reply{n}" data-img="{img}"></span>'
                return ""
            elif reply_type == "draw":
                # Comme `jsxgraph` : le paramètre porte une figure entière,
                # virgules comprises, que le découpage sur `,` de `_render_embed`
                # aurait tronquée à `[xrange -10`. On repart des arguments bruts.
                _, _, apres_ref = args.partition(",")
                return self._render_draw_embed(n, apres_ref)

        # `anstype/inputcss.inc` : le paramètre de taille peut porter des lignes
        # supplémentaires (tabulations promues en sauts de ligne) qui sont des
        # *attributs HTML* du champ, pas des chiffres — `\embed{reply 1,30
        # autofocus}` compile en `r1,30<TAB>autofocus`. Sans ce découpage,
        # `30<TAB>autofocus` n'était pas numérique et la taille retombait
        # silencieusement sur le défaut : ~370 champs du corpus (355
        # `autofocus`, 17 `autocomplete="off"`) étaient rendus trop étroits.
        size_raw, _, attr_tail = (
            self._subst(size_str).replace("\t", "\n").partition("\n")
        )
        size_raw = size_raw.strip()
        attrs = _parse_input_attributes(attr_tail)
        extra = ""
        if attrs:
            import html as _html  # noqa: PLC0415
            import json as _json  # noqa: PLC0415
            extra = f' data-attrs="{_html.escape(_json.dumps(attrs), quote=True)}"'
        # `type=draw` — WIMS y ouvre un canevas de `W×H` **pixels** sur lequel
        # l'élève trace sa figure. PAX ne porte pas ce type (cf.
        # `types-exercices-reponses.md`) ; sa taille n'est donc pas une
        # géométrie de `textarea`, et la lire comme telle donnait un champ de
        # 543 lignes sur 400 colonnes. Faute de canevas, on rend le champ
        # simple qu'il rendait déjà — mais pour une raison dite.
        textarea_m = (
            None
            if reply_type == "draw"
            else re.match(r"^(\d+)\s*[xX]\s*(\d+)$", size_raw)
        )
        if textarea_m:
            span = (
                f'<span class="oef-input" name="{ref}" '
                f'data-size="{size_raw}"{extra}></span>'
            )
        else:
            try:
                size = int(round(float(self._eval_arith(size_raw))))
            except (ValueError, TypeError):
                size = 10
            if not index_donne:
                # Sans second argument à l'`\embed`, la largeur vient du type :
                # chaque `anstype/<type>.input` de WIMS borne `inputsize` et
                # pose son défaut (`!bound inputsize between integer 1 and 100
                # default 20` pour `numeric`). PAX mettait 10 partout.
                size = _TAILLE_DEFAUT.get(reply_type, 30)
            span = (
                f'<span class="oef-input" name="{ref}" '
                f'data-size="{size}"{extra}></span>'
            )

        # Les trois `.input` de la famille encadrent le champ d'accolades
        # littérales : la réponse attendue est un **ensemble**, et c'est ainsi
        # qu'on l'écrit. `set.input`, `fset.input` et `aset.input` posent le `{`
        # avant le champ et le `}` après, dans les deux branches (avec ou sans
        # `distinct_inputs`) et quelle que soit la place du champ — le
        # `noprompt` de l'embed n'en saute que le libellé, jamais les accolades.
        if reply_type in ("set", "fset", "aset"):
            return f'<span class="oef-set-brace">{{</span>{span}<span class="oef-set-brace">}}</span>'
        return span

    def _render_draw_embed(self, n: int, size_str: str) -> str:
        """`type=draw` — la figure sur laquelle l'élève trace sa réponse.

        Port d'`anstype/draw.input`. WIMS y ouvre un canevas `canvasdraw` de
        `xsize × ysize` **pixels** portant un fond, et arme `userdraw <type>,
        <couleur>` : l'élève y pose des objets, que JavaScript relit en une
        liste de coordonnées (dans le repère du dessin, non en pixels) et
        dépose dans un champ caché.

        Trois choses à lire, et elles ne viennent pas du même endroit selon la
        forme de la question (`draw.input`, lignes 17-30) :

          taille   première ligne du paramètre d'`embed` (`400x400` à défaut) ;
          type     `$(replygood[2;1])` — sauf si la réponse est déléguée à un
                   analyseur (`?analyze` en tête), où il vient de la deuxième
                   ligne du paramètre d'`embed` ;
          fond     `$(replygood[1;])` — ou les lignes 3 et suivantes de ce même
                   paramètre dans le cas `?analyze`.

        Le paramètre d'`embed` porte ses lignes en **tabulations** :
        `r1,500x200<TAB>arrows<TAB>[figure]`.
        """
        lignes = [
            ligne.strip()
            for ligne in self._subst(size_str).replace("\t", "\n").split("\n")
        ]
        taille = lignes[0] if lignes else ""
        m = re.match(r"^(\d+)\s*[xX]\s*(\d+)$", taille)
        largeur, hauteur = (int(m.group(1)), int(m.group(2))) if m else (400, 400)

        good = self._subst(self.ctx.get(f"replygood{n}", ""))
        rangees = _rangees_protegees(good)
        tete = rangees[0].strip() if rangees else ""

        if "?analyze" in tete:
            type_objet = lignes[1].strip() if len(lignes) > 1 else ""
            fond = "\n".join(lignes[2:])
        else:
            deuxieme = rangees[1] if len(rangees) > 1 else ""
            type_objet = (deuxieme.split(",", 1)[0] or "").strip()
            fond = tete
        # `!text remove 0123456789.` : `poly3`…`poly9` désignent un polygone à
        # n sommets, et le compteur ne fait pas partie du nom du type.
        type_objet = re.sub(r"[0-9.]", "", type_objet).strip() or "points"

        fond = _declos(fond)
        if not fond.strip():
            return ""
        # Le fond de `oefpolynet` porte encore sa ligne `size`, dont flydraw ne
        # fait rien : la taille du canevas vient du paramètre d'`embed`.

        couleur = (
            self._cmd_getopt(f"color in {self.ctx.get(f'replyoption{n}', '')}")
            or "blue"
        )

        from ..flydraw import flydraw_to_url  # noqa: PLC0415

        mod_dir = (
            os.path.dirname(os.path.dirname(self.def_path)) if self.def_path else None
        )
        url = flydraw_to_url(largeur, hauteur, fond, base_dir=mod_dir)
        # Le repère du dessin : c'est en **ses** unités que WIMS attend la
        # réponse, non en pixels — `crosshairs,1.596,-0.044,…` chez
        # `oefpolynet/31`, dont le `xrange` va de -3.02 à 2.10.
        xr = self._bornes_repere(fond, "xrange") or f"0,{largeur}"
        yr = self._bornes_repere(fond, "yrange") or f"0,{hauteur}"
        import html as _html  # noqa: PLC0415

        return (
            f'<span class="oef-draw" name="reply{n}" '
            f'data-img="{_html.escape(url, quote=True)}" '
            f'data-size="{largeur}x{hauteur}" '
            f'data-objet="{_html.escape(type_objet, quote=True)}" '
            f'data-couleur="{_html.escape(couleur, quote=True)}" '
            f'data-xrange="{_html.escape(xr, quote=True)}" '
            f'data-yrange="{_html.escape(yr, quote=True)}"></span>'
        )

    def _bornes_repere(self, programme: str, mot: str) -> str:
        """Les deux bornes d'un `xrange`/`yrange`, **évaluées**.

        Elles peuvent être des expressions — `xrange -1*6+1,6*1.5` chez
        `evolmeth` —, et le front en a besoin en nombres pour convertir un clic
        en coordonnées du repère.
        """
        brut = _plage_flydraw(programme, mot)
        if not brut:
            return ""
        parts = [p.strip() for p in brut.split(",")]
        if len(parts) < 2:
            return ""
        try:
            return ",".join(str(float(self._eval_arith(p))) for p in parts[:2])
        except (ValueError, TypeError):
            return ""

    def _render_jsxgraph_embed(self, args: str, ref: str) -> str:
        """Render a `type=jsxgraph` answer embed as an interactive board.

        Mirrors WIMS' ``anstype/jsxgraph.input`` parsing of the embed
        ``inputsize``. After the reply ref (before the first comma), the
        remaining TAB-separated "lines" are:

            <W>x<H>                     ← board pixel size
            <divid> <boardvar> [opts]   ← container id, JS board var, [responsive…]
            <script…>                   ← board-init JS (JSXGraph)
            <name>=<val>; …             ← trailing line: the draggable point
                                          placeholder(s) — a NAME used in the
                                          script and its initial VALUE

        WIMS substitutes each placeholder NAME textually with its VALUE so the
        element consuming it (e.g. ``glider [p2_var1,0,l1]`` or
        ``create('point',jxgbox_var1,…)``) is defined. We do the same, then hand
        the board id + size + script to ``_render_jsxgraph`` (the slib renderer
        used by ``slib/geo2D/jsxgraph``). A plain ``var NAME=VALUE`` would break
        when VALUE isn't a single JS expression (coord2's ``[…],{…}``). Answer
        *capture* (reading the dragged position back) is not wired yet — this
        restores the board display in place of a stray text field.
        """
        _, _, rest = args.partition(",")
        lines = rest.split("\t")
        while lines and not lines[-1].strip():
            lines.pop()
        if not lines:
            return ""

        # Trailing line = draggable-variable initialisation (e.g. "p2_var1=1;").
        var_line = lines[-1].strip()
        body = lines[:-1]

        # Line 1 = board size "WxH" (digits and 'x' only).
        if body and re.fullmatch(r"[\dxX\s]+", body[0].strip()):
            size = body[0].strip()
            body = body[1:]
        else:
            size = "500x500"

        # Next line = "<divid> <boardvar> [responsive …options]".
        jbox_line = body[0].strip() if body else ""
        script_lines = body[1:]
        opts = ""
        mopt = re.search(r"\[([^\]]*)\]", jbox_line)
        if mopt:
            opts = mopt.group(1).replace("responsive", "").strip()
            jbox_line = jbox_line[: mopt.start()].strip()
        words = jbox_line.split()
        div_id = words[0] if words else "jsxbox"
        board_var = words[1] if len(words) > 1 else "brd"

        wh = re.search(r"(\d+)\s*[xX]\s*(\d+)", size)
        w, h = (wh.group(1), wh.group(2)) if wh else ("500", "500")

        script = "\t".join(script_lines)
        # Substitute each placeholder NAME with its VALUE in the script (WIMS
        # semantics). Multiple declarations are ";"-separated; split on the
        # first "=" only since VALUE may itself contain "=". Each placeholder
        # also names a draggable element whose coordinates form the reply: WIMS
        # renames `…var…` → `…rep…` (the element actually created in the script)
        # and captures `.X()` (+ `.Y()` for a 2-D point) — dim = item count of
        # the initial value (scalar → 1, `[x,y]` → 2).
        captures: list[tuple[str, int]] = []
        for decl in var_line.split(";"):
            decl = decl.strip()
            if "=" not in decl:
                continue
            vname, vval = (p.strip() for p in decl.split("=", 1))
            if not vname:
                continue
            script = re.sub(rf"\b{re.escape(vname)}\b", lambda _m, v=vval: v, script)
            captures.append((vname.replace("var", "rep"), _jsxgraph_value_dim(vval)))

        full_script = script + self._jsxgraph_capture_js(board_var, captures)
        size_field = f"{w} x {h}" + (f",{opts}" if opts else "")
        proc_args = f"{div_id} {board_var},[{size_field}],{full_script}"
        div = self._render_jsxgraph(proc_args)
        # Tag the board with the reply name so the frontend binds the captured
        # coordinates to this answer field.
        if captures:
            div = div.replace(
                '<div class="pax-jsxgraph"',
                f'<div class="pax-jsxgraph" data-reply="{ref}"', 1,
            )
        return div

    def _render_runcode_embed(self, args: str, ref: str, n: int) -> str:
        """`type=runcode` — le programme Python que l'élève écrit et exécute.

        Le type n'existe pas chez WIMS : huit modules d'`H4/programming` le
        définissent, à quelques lignes près les uns des autres. Son `.input`
        n'assemble rien lui-même — il appelle `slib/runcode`, qui monte
        l'éditeur (`slib/editor`, déjà porté en marqueur `pax-codeeditor`),
        ajoute un bouton d'exécution et une zone de sortie, et charge Skulpt.

        Le paramètre d'embed tient en deux **rangées** :

            [python,[<code initial>]] ; [<id>,<options>,<libellé du bouton>]

        Le reste vient d'ailleurs : `replygood` nomme les variables à relever
        après exécution (`[vi,1],[vf,4]`), et `keyword_python` dans l'option
        exige que certains mots figurent dans le code — « sers-toi d'une
        boucle `for` ». Le composant a besoin des deux, puisque c'est lui qui
        exécute : le correcteur, lui, ne fait que comparer les valeurs reçues.

        Faute de ce rendu, les 99 exercices du type affichaient un champ de
        saisie d'une ligne à la place de l'éditeur.
        """
        import html as _html  # noqa: PLC0415
        import json as _json  # noqa: PLC0415

        _, _, brut = args.partition(",")
        rangees = [r.strip() for r in brut.split(";")]
        code_champ = rangees[0] if rangees else ""
        para = self._declose(rangees[1]) if len(rangees) > 1 else ""
        items = wl.cutitems(para)
        editeur_id = items[0].strip() if items else "0"
        options = items[1].strip() if len(items) > 1 else ""
        libelle = items[2].strip() if len(items) > 2 else "Jouer le code"

        marqueur = self._render_codeeditor(f"{code_champ},{editeur_id},{options}")
        m = re.search(r'data-codeeditor="([^"]*)"', marqueur)
        if not m:
            return ""
        try:
            config = _json.loads(_html.unescape(m.group(1)))
        except ValueError:
            return ""

        # Les variables à relever après exécution, dans l'ordre où le
        # `replygood` les nomme — c'est cet ordre que le correcteur attend.
        good = self._subst(self.ctx.get(f"replygood{n}", ""))
        variables = []
        for couple in wl.cutitems(good):
            champs = wl.cutitems(self._declose(couple))
            if champs and champs[0].strip():
                variables.append(champs[0].strip())

        option = self._subst(self.ctx.get(f"replyoption{n}", ""))
        km = re.search(r"\bkeyword_python\s*=\s*(\S+)", option)
        mots = [k for k in re.split(r"[&,]", km.group(1)) if k.strip()] if km else []

        # Les champs `js2wims1` de l'exercice se nourrissent du **même**
        # programme : leur `.input` relit les variables que celui-ci laisse.
        # On les rattache ici, faute de quoi ils resteraient vides — c'est la
        # dépendance que le relevé de dette annonçait entre les deux types.
        annexes = []
        for cle in sorted(self.ctx):
            m2 = re.fullmatch(r"replytype(\d+)", cle)
            if not m2 or self._subst(self.ctx[cle]).strip().lower() != "js2wims1":
                continue
            n2 = m2.group(1)
            good2 = self._subst(self.ctx.get(f"replygood{n2}", ""))
            vars2 = []
            for couple in wl.cutitems(good2):
                champs = wl.cutitems(self._declose(couple))
                if champs and champs[0].strip():
                    vars2.append(champs[0].strip())
            if vars2:
                annexes.append({"reply": f"reply{n2}", "variables": vars2})

        config["run"] = {
            "reply": ref,
            "label": libelle,
            "variables": variables,
            "keywords": mots,
            "also": annexes,
        }
        charge = _html.escape(_json.dumps(config, ensure_ascii=False), quote=True)
        return f'<div class="pax-codeeditor" data-codeeditor="{charge}"></div>'

    def _render_reaction_embed(self, args: str, ref: str, n: int) -> str:
        """`type=reaction` — le test de temps de réaction d'`oefstatistiques`.

        Le type appartient au module, pas à WIMS. Son `.input` monte un petit
        chronomètre en JavaScript : un bouton **GO** arme un délai aléatoire,
        le bouton devient **STOP**, et l'écart entre l'apparition de la
        consigne et la frappe est le temps de réaction. L'élève recommence
        `nbrtest` fois — quarante, dans `histocap` — et la réponse envoyée est
        la liste de ces temps, en millisecondes.

        Ce script ne pouvait pas s'exécuter : injecté par le `v-html` du front,
        un `<script>` reste inerte. Les trois exercices du module affichaient
        donc « Réaliser 40 tests. » suivi d'un champ de saisie vide, sans dire
        quoi y écrire ni permettre de le mesurer — et comme rien n'était
        recueilli, les cinq étapes suivantes n'avaient aucune donnée à traiter.

        Les réglages tiennent dans la **deuxième rangée** de `replygood`, où le
        `.input` les lit un à un (`$(replygood$i[2;1])`…) : nombre de tests,
        délai avant le départ, attente aléatoire maximale, et le temps au delà
        duquel un essai est rejeté (« Réveillez-vous ! »). Le nombre de
        colonnes du tableau récapitulatif vient de la taille de l'`\embed`.
        """
        import html as _html  # noqa: PLC0415
        import json as _json  # noqa: PLC0415

        _, _, taille = args.partition(",")
        try:
            colonnes = int(float(self._subst(taille).strip().split(",")[0]))
        except (ValueError, IndexError):
            colonnes = 5

        good = self._subst(self.ctx.get(f"replygood{n}", ""))
        rangees = wl.cutrows(good)
        reglages = wl.cutitems(rangees[1]) if len(rangees) > 1 else []

        def _entier(rang: int, defaut: int) -> int:
            try:
                return int(float(reglages[rang].strip()))
            except (IndexError, ValueError):
                return defaut

        config = {
            "reply": ref,
            # Les défauts sont ceux du `.input` du module, à la ligne près.
            "tests": _entier(0, 7),
            "delai": _entier(1, 1000),
            "attenteMax": _entier(2, 6),
            "reactionMax": _entier(3, 1000),
            "colonnes": max(1, colonnes),
        }
        charge = _html.escape(_json.dumps(config, ensure_ascii=False), quote=True)
        return f'<div class="pax-reaction" data-reaction="{charge}"></div>'

    def _render_jmolclick_embed(self, args: str, ref: str, n: int) -> str:
        """`type=jmolclick` — la molécule dont l'élève clique les atomes.

        `anstype/jmolclick.input` monte une applet JSmol, arme son
        `pickcallback` et laisse l'élève basculer la sélection atome par
        atome. Le `replygood` porte les deux choses dont l'applet a besoin,
        séparées par un `;` (`!rows2lines` puis `;` → sauts de ligne) :

            <expression de sélection Jmol> ; <fichier de la molécule>

        L'expression est du Jmol pur — `oxygen and connected(hydrogen) and
        …` —, que l'applet sait évaluer elle-même : c'est ainsi que le
        navigateur compare la sélection de l'élève à la bonne réponse sans
        jamais l'expliciter.

        Le script d'initialisation est celui du `.input`, à ceci près qu'on ne
        reprend pas la queue de `_render_jmol_embed` : elle éteint le picking
        (`set picking off`), ce qui est juste pour une molécule d'énoncé et
        ruinerait celle-ci.

        Faute de ce rendu, l'embed retombait sur le champ générique : l'unique
        exercice du type affichait une zone de texte de 400 × 400 à la place de
        la molécule.
        """
        import html as _html  # noqa: PLC0415
        import json as _json  # noqa: PLC0415

        good = self._subst(self.ctx.get(f"replygood{n}", ""))
        expression, _, fichier = good.partition(";")
        fichier = fichier.strip().split("\t")[0].strip()
        if not expression.strip() or not fichier:
            return ""

        _, _, apres_ref = args.partition(",")
        lignes = apres_ref.split("\t")
        taille = lignes[0].strip() if lignes else ""
        wh = re.search(r"(\d+)\s*[xX]\s*(\d+)", taille)
        largeur, hauteur = (wh.group(1), wh.group(2)) if wh else ("400", "400")
        # `!distribute lines … into size,file,ans_sc0,ans_sc2` : les deux
        # derniers sont des scripts que l'exercice ajoute à l'initialisation
        # (`reconnaissance` y étiquette ses atomes, `select all;label %e`).
        scripts = [l.strip() for l in lignes[2:4] if l.strip() and l.strip() != ";"]

        contenu = self._resoudre_fichier_jmol(fichier)
        if not contenu:
            return ""

        # Le préambule du `.input`, sans ce qui n'a de sens que chez WIMS
        # (`serverURL`, `j2sPath`) : halos bleus sur la sélection, picking
        # armé, menu contextuel et survol désactivés.
        init = (
            "selectionhalos on;select none;color selectionHalos blue;"
            "set antialiasdisplay on;set frank on;set DisablePopupMenu TRUE;"
            "hover off;set picking;console off;"
        )
        cfg = {
            "id": f"jmolApplet_{n}",
            "width": int(largeur),
            "height": int(hauteur),
            "color": "white",
            "data": contenu,
            "script": init + "".join(f"{sc};" if not sc.endswith(";") else sc
                                     for sc in scripts),
            # Ce que le composant doit savoir pour juger la sélection.
            "pick": {"good": expression.strip(), "reply": ref},
        }
        charge = _html.escape(_json.dumps(cfg, ensure_ascii=False), quote=True)
        return (
            f'<div class="pax-jmol" id="{cfg["id"]}" data-reply="{ref}" '
            f'data-w="{largeur}" data-h="{hauteur}" data-jmol="{charge}"></div>'
        )

    def _render_geogebra_answer_embed(self, args: str, ref: str, n: int) -> str:
        """`type=geogebra` — l'applet **est** le champ de réponse.

        `anstype/geogebra.input` ne construit pas la figure lui-même : il
        remet en forme le paramètre d'embed, puis appelle
        `slib/geo2D/geogebra`, celui-là même qui monte les figures d'énoncé et
        que PAX porte déjà (`_render_geogebra_embed`). Il n'y a donc rien à
        réimplémenter — seulement à préparer les options comme lui :

            oef_applet_option = !replace internal <tab> by <NL> in $inputsize
            oef_applet_option = !replace internal ; by <NL> in …
            Inputsize         = !line 1, `x` → `,`
            oef_applet_option = !line 2 to -1
            !if width notin …  → width=$(Inputsize[1])
            !if height notin … → height=$(Inputsize[2])

        La première ligne est la taille (`600 x 600`), le reste les options de
        l'applet et ses commandes de construction (`file=vector.ggb`,
        `setCoordSystem(…)`, `F=(0,0)`, `u=Vector(F,H)`…).

        Le marqueur reçoit en plus un `data-reply` : c'est par lui que le
        composant sait à quel champ rattacher l'état de la figure. Même
        dispositif que `jsxgraphobjet`, et pour la même raison — faute de ce
        rendu, l'embed retombait sur le champ de saisie générique, et les sept
        exercices d'`oefvectdirnorm` affichaient une zone de texte de 600 × 600
        à la place de l'applet.
        """
        import html as _html  # noqa: PLC0415
        import json as _json  # noqa: PLC0415

        _, _, brut = args.partition(",")
        lignes = [
            ligne.strip()
            for morceau in brut.split("\t")
            for ligne in morceau.split(";")
            if ligne.strip()
        ]
        if not lignes:
            return ""

        taille, options = lignes[0], lignes[1:]
        dims = re.findall(r"\d+", taille)
        if not re.fullmatch(r"[\dxX\s*]+", taille) or len(dims) < 2:
            # Pas une taille : l'auteur a commencé par une option.
            options, dims = lignes, []
        if dims:
            if not any(o.startswith("width") for o in options):
                options.append(f"width={dims[0]}")
            if not any(o.startswith("height") for o in options):
                options.append(f"height={dims[1]}")

        garde = self.ctx.get("slib_out")
        self.ctx["slib_out"] = ""
        try:
            self._cmd_readproc("slib/geo2D/geogebra " + ";".join(options))
            marqueur = str(self.ctx.get("slib_out") or "")
        finally:
            if garde is None:
                self.ctx.pop("slib_out", None)
            else:
                self.ctx["slib_out"] = garde
        if not marqueur.startswith('<div class="pax-geogebra"'):
            return ""
        lecture = _html.escape(
            _json.dumps(self._geogebra_lecture_options(n, options), ensure_ascii=False),
            quote=True,
        )
        return marqueur.replace(
            '<div class="pax-geogebra"',
            f'<div class="pax-geogebra" data-reply="{ref}" '
            f'data-ggb-answer="{lecture}"', 1,
        )

    def _geogebra_lecture_options(self, n: int, options: list[str]) -> dict:
        """Ce dont le front a besoin pour relire la figure, tiré de l'option.

        `anstype/geogebra.input` construit son `geogebra2wims()` autour de cinq
        réglages, et c'est tout ce qui distingue une lecture d'une autre :

        - `max` (défaut 10) — au-delà, WIMS refuse d'envoyer et alerte : la
          figure porte plus d'objets que l'exercice n'en attend ;
        - `precision` (défaut 18) — les décimales conservées sur les
          coordonnées ;
        - `ignore` — les objets à passer, quels qu'ils soient ;
        - `object_analysis` — un préfixe qui restreint l'analyse ; à défaut,
          WIMS écarte ce qui commence par `My_`, la marque des objets d'un
          `.ggb` que l'exercice ne veut pas voir ;
        - `enable3d` — la cote entre alors dans les coordonnées.

        Le sixième, `last`, renomme le dernier objet construit ; aucun exercice
        du corpus ne s'en sert, et `last_b` y reste `false`.
        """
        opt = self._subst(self.ctx.get(f"replyoption{n}", ""))

        def mot(cle: str) -> str:
            m = re.search(rf"\b{cle}\s*=\s*(\S+)", opt, re.I)
            return m.group(1).strip() if m else ""

        def entier(cle: str, defaut: int) -> int:
            try:
                return int(float(mot(cle)))
            except ValueError:
                return defaut

        ignore = [x for x in re.split(r"[&,]", mot("ignore")) if x.strip()]
        prefixe = mot("object_analysis").strip()
        trois_d = any(
            re.fullmatch(r"enable3d\s*=\s*(true|yes)", o.strip(), re.I)
            for o in options
        )
        return {
            "max": entier("max", 10),
            "precision": entier("precision", 18),
            "ignore": ignore,
            "prefix": prefixe,
            "is3d": trois_d,
        }

    def _render_jsxgraphobjet_embed(self, args: str, ref: str, n: int) -> str:
        """`type=jsxgraphobjet` — une figure dont l'élève **clique** les objets.

        Le type n'existe pas chez WIMS : il est défini par le module
        `oeftrigoclg1` (`anstype/jsxgraphobjet.input`), qui monte la figure
        comme `slib/geo2D/jsxgraph`, puis attache à chaque objet nommé dans
        `replygood` un `on('up')` qui l'épaissit et l'empile dans
        `jsxbox_objet`. Un second clic le retire. La réponse est la liste,
        dans l'ordre des clics.

        Le paramètre d'embed a la même forme que pour `jsxgraph` — taille,
        `<divid> <boardvar>`, script — moins la ligne de placeholders : rien
        n'est déplacé, donc rien n'est à substituer.

        Faute de ce rendu, l'embed retombait sur le champ de saisie générique :
        les trois exercices affichaient une zone de texte de 199 × 250 à la
        place de la figure.
        """
        _, _, rest = args.partition(",")
        lignes = rest.split("\t")
        while lignes and not lignes[-1].strip():
            lignes.pop()
        if not lignes:
            return ""

        taille = "500x500"
        if re.fullmatch(r"[\dxX\s]+", lignes[0].strip()):
            taille = lignes[0].strip()
            lignes = lignes[1:]
        jbox = lignes[0].strip() if lignes else ""
        script = "\t".join(lignes[1:])
        mots = jbox.split()
        div_id = mots[0] if mots else f"jsxbox{n}"
        board_var = mots[1] if len(mots) > 1 else "brd"
        wh = re.search(r"(\d+)\s*[xX]\s*(\d+)", taille)
        w, h = (wh.group(1), wh.group(2)) if wh else ("500", "500")

        good = self._subst(self.ctx.get(f"replygood{n}", ""))
        script += self._jsxgraphobjet_capture_js(_objets_cliquables(good))
        div = self._render_jsxgraph(f"{div_id} {board_var},[{w} x {h}],{script}")
        return div.replace(
            '<div class="pax-jsxgraph"',
            f'<div class="pax-jsxgraph" data-reply="{ref}"', 1,
        )

    @staticmethod
    def _jsxgraphobjet_capture_js(objets: list[str]) -> str:
        """Les gestionnaires de clic du module, plus le report vers le champ.

        WIMS relit `jsxbox_objet` au moment de l'envoi (`oef_js_submit` appelle
        `capture$i()`), ce que PAX n'a pas : le composant `Jsxgraph.vue` lie la
        réponse par le rappel `__paxReport`, alimenté à chaque clic. Le premier
        appel, à la construction, pose le champ à vide plutôt que de le laisser
        indéfini.
        """
        if not objets:
            return ""
        bouts = [
            "\t;var jsxbox_objet=[];",
            "var __paxObjR=function(){try{if(typeof __paxReport==='function')"
            "__paxReport(jsxbox_objet.toString());}catch(e){}};",
        ]
        for o in objets:
            bouts.append(
                f"try{{{o}.on('up',function(){{"
                f"if({o}.getAttribute('strokeWidth')!=5)"
                f"{{jsxbox_objet.push('{o}');{o}.setAttribute({{strokeWidth:5}});}}"
                f"else{{{o}.setAttribute({{strokeWidth:2}});"
                f"jsxbox_objet.splice(jsxbox_objet.indexOf('{o}'),1);}}"
                f"__paxObjR();}});}}catch(e){{}}"
            )
        bouts.append("__paxObjR();")
        return "".join(bouts)

    @staticmethod
    def _jsxgraph_capture_js(board_var: str, captures: list[tuple[str, int]]) -> str:
        """JS appended to the board script: report the dragged point(s) back to
        the answer field. Reads each element's coordinates on every board update
        (i.e. while dragging) and calls the `__paxReport` callback the frontend
        injects. Reply format mirrors WIMS: rows ";"-separated, a 2-D point's
        coordinates ","-separated — e.g. "7;" or "3,5;"."""
        if not captures:
            return ""
        parts = [
            f"({obj}.X()+','+{obj}.Y())" if dim >= 2 else f"{obj}.X()"
            for obj, dim in captures
        ]
        arr = "[" + ",".join(parts) + "]"
        return (
            "\t;try{var __paxC=function(){return " + arr + ".join(';')+';';};"
            "if(typeof __paxReport==='function'){"
            f"{board_var}.on('update',function(){{__paxReport(__paxC());}});"
            "__paxReport(__paxC());}}"
            "catch(e){if(typeof console!=='undefined')console.error('pax jsx capture',e);}"
        )

    # ── Answer extraction ─────────────────────────────────────────────────────

    @staticmethod
    def _instr_texts(instrs: list):
        """Toutes les chaînes portées par un arbre d'instructions.

        Les instructions du parseur sont des dataclasses dont les champs sont
        soit du texte (`condition`, `value`, `args`…), soit un sous-corps.
        Les aplatir permet de chercher une variable sans énumérer les types.
        """
        for instr in instrs:
            for val in vars(instr).values():
                if isinstance(val, str):
                    yield val
                elif isinstance(val, list):
                    yield from DefEngine._instr_texts(val)

    def _analyze_var_is_graded(self, var_name: str, n: int, df: "DefFile") -> bool:
        """La réponse `?analyze` n° `n` est-elle éprouvée par un test ?

        Une réponse `?analyze` ne porte pas sa correction : elle alimente
        `val<N>`, et c'est `:test` qui décide. Encore faut-il que `:test` la
        regarde. Deux écritures s'y croisent — `$val<N>`, la variable
        d'analyse, et `$m_reply<n>` / `$reply<n>`, la réponse brute
        (`oefresolalg/fill1deg` note ses neuf champs par la seconde). On
        cherche donc les deux, dans `:test` comme dans `:postdef`, ce dernier
        pouvant dériver la valeur vers ce que `:test` compare.

        Quand aucune ne s'y trouve, **rien** ne peut noter ce champ : ni la
        voie `analyze`, qui n'a pas de condition à évaluer, ni la voie
        standard, dont l'attendu est vide. C'est ce que dit `ungraded`.
        """
        motifs = [re.compile(rf"\$\(?\s*(?:m_)?reply{n}\b")]
        if var_name:
            motifs.append(re.compile(rf"\$\(?\s*{re.escape(var_name)}\b"))
        zone = "\n".join(
            self._instr_texts(df.sections.get("test", []))
        ) + "\n" + "\n".join(
            self._instr_texts(df.sections.get("postdef", []))
        )
        return any(m.search(zone) for m in motifs)

    def _resolve_analyze_expected(self, var_name: str, df: "DefFile") -> str:
        """Scan the :test section for an equality involving `$<var_name>`
        and return the evaluated RHS — used by debug/auto-fill for the
        `analyze` answer type.

        Looks for ``$val<N>=<expr>`` (or the symmetric ``<expr>=$val<N>``)
        inside any !if/!ifval condition reachable from :test. Returns
        the first match evaluated against the current ctx, or "" if
        none is found.
        """
        from ..def_parser import IfBlock, Assign  # noqa: PLC0415
        # Accept both `=` and WIMS text comparators (issametext / sametext).
        # The operand is a single value that may be a `$(…)` reference (whose
        # own ")" must not truncate the match); exclude "(" so a parenthesised
        # clause `($val20 issametext $val22)` yields `$val20`, not `($val20`.
        # Word boundaries on the text comparators so `sametext` doesn't match
        # the *suffix* of `issametext` / `notsametext` — which made `_val`
        # capture the leftover "is" (ineqva1interv's union slot bug).
        _op = r"(?:==?|\bissametext\b|\bsametext\b)"
        _val = r"(?:\$\([^()]*\)|[^\s()])+"
        pat_rhs = re.compile(rf"\${re.escape(var_name)}\b\s*{_op}\s*({_val})")
        pat_lhs = re.compile(rf"({_val})\s*{_op}\s*\${re.escape(var_name)}\b")
        # Difference-style check: the reply ($<var>) is compared via a
        # `$<var> - $valX` (or `$valX - $<var>`) whose simplification :test then
        # requires == 0 — so the other operand $valX is the expected value
        # (ineqinterv1's bounds: `val26 = maxima($val23 - $val16)`).
        _ref = r"(?:\$\w+|\$\([^()]*\))"
        pat_sub = re.compile(
            rf"\${re.escape(var_name)}\b\s*-\s*({_ref})"
            rf"|({_ref})\s*-\s*\${re.escape(var_name)}\b"
        )
        # Set-equality check: the reply set is compared to the solution set via
        # maxima ``is({$sol}={$reply})`` (factorcom's eqfactorcom: the reply
        # `$<var>` equals the other braced set, the solutions). The other side
        # is the expected value.
        pat_iseq = re.compile(r"is\(\s*\{([^{}]*)\}\s*=\s*\{([^{}]*)\}\s*\)")

        def _other_set_side(value: str) -> str | None:
            em = pat_iseq.search(value)
            if not em:
                return None
            a, b = em.group(1).strip(), em.group(2).strip()
            targets = {f"${var_name}", f"$({var_name})"}
            if b in targets:
                return self._subst(a).strip()
            if a in targets:
                return self._subst(b).strip()
            return None

        def walk(body: list) -> str | None:
            for instr in body:
                if isinstance(instr, IfBlock):
                    cond = instr.condition
                    m = pat_rhs.search(cond) or pat_lhs.search(cond)
                    if m:
                        return self._subst(m.group(1)).strip()
                    other = _other_set_side(cond)
                    if other is not None:
                        return other
                    sub = walk(instr.then_body) or walk(instr.else_body)
                    if sub:
                        return sub
                elif isinstance(instr, Assign):
                    sm = pat_sub.search(instr.value)
                    if sm:
                        return self._subst(sm.group(1) or sm.group(2)).strip()
                    other = _other_set_side(instr.value)
                    if other is not None:
                        return other
            return None

        # :test holds the comparison for most analyze exercises; ineqinterv1
        # puts it (and the difference assigns) in :postdef, so scan both.
        result = (
            walk(df.sections.get("test", []))
            or walk(df.sections.get("postdef", []))
            or ""
        )
        # Empty inline math `\(\)` (an unused slot in a conditional exercise,
        # e.g. ineqva1interv's 2nd interval for a single-interval answer) is
        # really "no value" — return "" so auto-fill leaves the slot blank.
        if not result.replace("\\(", "").replace("\\)", "").strip():
            return ""
        return result

    def _rational_expand(self, expr: str, depth: int = 0) -> str:
        """Expand `expr` keeping fractions intact: resolve `$(var[i])` indexed
        forms against ctx, and replace each `$var` by its *raw* assignment RHS
        (recursively, unwrapping a `$[…]`) rather than its floated ctx value —
        so a nested `$[3/4]` doesn't collapse to `0.75`. Bounded recursion;
        the caller's strict numeric guard rejects any non-rational expansion."""
        if depth > 6:
            return expr
        expr = self._resolve_indexed_forms(expr)

        def repl(m: "re.Match") -> str:
            name = m.group(1)
            ctx_val = self.ctx.get(name, self.ctx.get(name.lower()))
            # If the stored value is already a clean rational (int or p/q), use
            # it — don't trace back into its (possibly !cmd) assignment, e.g.
            # val12="2/3" from `!exec pari` (0814). Only a floated decimal
            # value warrants recovering the fraction from the raw assignment.
            if ctx_val is not None and re.fullmatch(r"-?\d+(?:/\d+)?", ctx_val.strip()):
                return "(" + ctx_val.strip() + ")"
            raw = self.raw_assigns.get(name) or self.raw_assigns.get(name.lower())
            if raw is None:
                return str(ctx_val if ctx_val is not None else m.group(0))
            inner = re.fullmatch(r"\s*\$\[(.+)\]\s*", raw, re.DOTALL)
            return "(" + self._rational_expand(inner.group(1) if inner else raw, depth + 1) + ")"

        return _DOLLAR_VAR_RE.sub(repl, expr)

    def _expected_as_fraction(self, raw_good: str) -> str | None:
        """If the replygood evaluates to an exact non-integer rational, return
        it as ``"p/q"``; else None. Traces `$var` references back through their
        raw assignments (via `_rational_expand`) so a fraction floated by an
        intermediate `$[…]` — e.g. `replygood=$[$val9]`, `val9=$[$(val8[2])]`,
        `val8[2]=3/4` (1022) — is recovered. Used for numeric answer expected
        so auto-fill inserts the fraction (`3/4`) not the decimal (`0.75`)."""
        from fractions import Fraction  # noqa: PLC0415

        m = re.fullmatch(r"\s*\$\[(.+)\]\s*", raw_good, re.DOTALL)
        expr = (m.group(1) if m else raw_good)
        expr = self._rational_expand(expr).replace("^", "**")
        # Pure integer arithmetic with at least one division — no decimals,
        # functions, or symbols (those belong to the float / CAS paths).
        if "/" not in expr or not re.fullmatch(r"[\d\s+\-*/().]+", expr):
            return None
        wrapped = re.sub(r"\d+", lambda mm: f"Fraction({mm.group(0)})", expr)
        try:
            res = eval(wrapped, {"Fraction": Fraction, "__builtins__": {}})  # noqa: S307
        except Exception:
            return None
        # A denominator that is a multiple of 10 is a decimal / unit-conversion
        # artifact (loigp1's `$[$val11/1000]` = 7/1000 L = 0.007 L), not a
        # pedagogical fraction (those use 2,3,4,6,7,8,…). Keep those decimal.
        #
        # Le test porte sur le dénominateur **réduit**, et la réduction efface
        # justement ce qu'il cherche : l'arrondi `rint(x*10^3)/10^3` des
        # balayages d'`oefalgopython` donne `1424/1000`, que `Fraction` ramène
        # à `178/125` — dénominateur non multiple de 10, donc pris pour une
        # fraction, et l'élève lisait `178/125` au lieu de `1.424`. D'où le
        # second test, sur l'**expression** : diviser par une puissance de 10
        # est une mise à l'échelle décimale, quoi que la réduction en fasse.
        if _DIVISION_DECIMALE_RE.search(expr):
            return None
        if (
            isinstance(res, Fraction)
            and res.denominator != 1
            and res.denominator % 10 != 0
        ):
            return f"{res.numerator}/{res.denominator}"
        return None

    # Answer types whose `expected` is one of the *displayed* choices (compared
    # as text by check_radio / check_clickfill), so it must be closed in lockstep
    # with the choices. Free-input types (numeric/litexp/…) keep `expected` raw
    # for the CAS/numeric checker; checkbox/mark `expected` is an index (closing
    # is a no-op); correspond has its own display path (_prep_correspond_item).
    _CHOICE_EXPECTED_TYPES = frozenset({"radio", "menu", "mark", "clickfill", "click"})

    def _finalize_answer_math(self, answers: list[AnswerDef]) -> None:
        """Single guarantee point for inline-math closing on answer fields.

        Closes WIMS `\\(…)` → KaTeX `\\(…\\)` on every user-facing answer field
        (label, choices, and choice-type `expected`). Idempotent — a span already
        closed as `\\(…\\)` is left untouched — so it safely re-covers the fields
        the type-specific code closes inline (radio/clickfill, where closing is
        interleaved with de-dup/shuffle and must stay there) *and* covers the ones
        historically missed (menu, mark), without any path having to remember.
        """
        for a in answers:
            if a.label:
                a.label = _close_inline_math(a.label, self.lang)
            ch = a.options.get("choices")
            if isinstance(ch, list):
                a.options["choices"] = [_close_inline_math(c, self.lang) for c in ch]
            if a.answer_type in self._CHOICE_EXPECTED_TYPES and a.expected:
                a.expected = _close_inline_math(a.expected, self.lang)

    def _wims_range(self, df: DefFile) -> tuple[float, float]:
        """`\\range{a,b}` → `(a, b)`, défaut `(-5, 5)` comme `oef/var.prep`."""
        out = []
        for cle, defaut in (("leftrange", -5.0), ("rightrange", 5.0)):
            raw = self._subst(str(self.ctx.get(cle) or df.meta.get(cle) or "")).strip()
            try:
                out.append(float(raw) if raw else defaut)
            except ValueError:
                out.append(defaut)
        return (out[0], out[1])

    def _wims_precision(self, df: DefFile) -> float:
        """Précision numérique WIMS (`\\precision{M}`) de l'exercice.

        WIMS pose `wims_compare_precision = precision`, borné entre 20 et 1e8,
        défaut 10000 (cf. `scripts/oef/var.prep`). La valeur peut référencer une
        variable (`\\precision{\\prec}`), donc on substitue puis on évalue avant
        de borner. Renvoyée aux checkers via `options["precision"]`."""
        raw = self.ctx.get("precision") or df.meta.get("precision") or ""
        raw = self._subst(str(raw)).strip()
        if raw and not re.fullmatch(r"-?\d+(?:\.\d+)?", raw):
            raw = self._eval_arith(raw).strip()
        try:
            prec = float(raw)
        except (TypeError, ValueError):
            return 10000.0
        if prec < 20:
            return 20.0
        if prec > 1e8:
            return 1e8
        return prec

    def _extract_answers(self, df: DefFile) -> list[AnswerDef]:
        """Thin wrapper: build the answers, then close inline math on their
        display fields in one place (see :meth:`_finalize_answer_math`)."""
        answers = self._extract_answers_raw(df)
        self._finalize_answer_math(answers)
        return answers

    def _extract_answers_raw(self, df: DefFile) -> list[AnswerDef]:
        answers: list[AnswerDef] = []
        wims_prec = self._wims_precision(df)
        plage_exo = self._wims_range(df)
        compute_answer = self._subst(str(df.meta.get("computeanswer", ""))).strip().lower()

        # When replycnt=0 but choicecnt>0, synthesise implicit radio replies from
        # choice_meta (WIMS creates an implicit reply slot in this case).
        # Un `\choice{}` porte sa propre réponse, et WIMS lui réserve un champ
        # à part : `c<N>`, tel qu'il apparaît dans `oefsteps` et dans un
        # `\embed{}`. PAX ne la fabriquait que pour un exercice **sans aucune
        # `reply`**, ce qui laissait sans réponse ceux qui mêlent les deux —
        # `cosinus` est un `course` dont `oefsteps` vaut `c1\tr1,r2,r3` : à
        # l'étape 1 le filtre ne gardait que le champ `c1`, qui n'existait pas,
        # et l'exercice s'affichait avec un champ que rien ne notait.
        if df.choice_meta:
            for cm in df.choice_meta:
                n = cm["n"]
                # Seul un exercice qui n'a que des choix les expose en `reply`.
                nom_champ = f"reply{n}" if not df.reply_meta else f"c{n}"
                correct = self._subst(cm.get("good", ""))
                # La palette vient de `_prepare_choices`, qui suit
                # `oef/var.prep` : mauvaises réponses purgées de celles qui
                # figurent aussi parmi les bonnes, liste tronquée à
                # `qcmpresent`, puis **triée** — mélangée seulement si
                # l'auteur a écrit `shuffle`. L'ancien calcul mélangeait
                # toujours, ce qui contredisait WIMS et rendait l'ordre
                # imprévisible d'un rendu à l'autre.
                choices = list(self._choice_lists.get(str(n), []))
                seen_set = set(choices)
                # `oef/formc.phtml` tranche entre deux présentations :
                #
                #     !if $choicecnt<=1 and $replycnt<1  → boutons radio
                #     !else                               → menu déroulant
                #
                # PAX ne connaissait que la première.
                # `OEFpythagore2/enchainement` pose deux choix **et** une
                # réponse : ses phrases à choisir manquaient de la phrase,
                # là où WIMS y glisse deux menus.
                en_menu = len(df.choice_meta) > 1 or bool(df.reply_meta)
                # Les deux échappatoires de `formc.phtml`, toujours en
                # queue de liste. « Aucune de ces réponses » n'apparaît que
                # si la bonne peut manquer (`qcmgood<1`) : la proposer
                # autrement offrirait une réponse qui n'est jamais juste.
                if self._choice_none.get(str(n)):
                    aucune = "Aucune de ces réponses"
                    if aucune not in seen_set:
                        choices.append(aucune)
                jnsp = "Je ne sais pas"
                if jnsp not in seen_set:
                    choices.append(jnsp)
                # Close WIMS inline math `\(…)` → KaTeX `\(…\)` so the frontend
                # renders the labels (choices here carry texmath output like
                # `\(y < \frac{9}{3})`). Mirrors the reply_meta path below;
                # `expected` is one of the choices, so close it the same way to
                # keep the reply comparison consistent.
                choices = [_close_inline_math(c, self.lang) for c in choices]
                # `choicename` is internal metadata in WIMS (field id / answer
                # summary), not a visible prompt: when the choice isn't embedded
                # inline the buttons are shown without it (e.g. ineqequi4's
                # "Intru"). Leave the label empty so the frontend falls back to
                # its neutral "choose an answer" prompt instead of surfacing it.
                # Le titre n'est un intitulé visible que dans un menu ; en
                # boutons radio WIMS ne le montre pas.
                titre = self._subst(cm.get("name", "")).strip() if en_menu else ""
                try:
                    poids_c = float(self._subst(cm.get("weight", "1")) or 1)
                except (TypeError, ValueError):
                    poids_c = 1.0
                answers.append(
                    AnswerDef(
                        label=titre,
                        expected=_close_inline_math(correct, self.lang),
                        answer_type="menu" if en_menu else "radio",
                        options={"choices": choices},
                        weight=poids_c,
                        input_name=nom_champ,
                        logical_name=titre or nom_champ,
                    )
                )
            if not df.reply_meta:
                return answers

        for rm in df.reply_meta:
            n = rm["n"]
            # Sans `replytypeN`, WIMS pose `default` (`!default replytype$i=default`,
            # `oef/replytype.proc`), pas `numeric` : `anstype/default` est un
            # aiguilleur qui regarde l'attendu avant de choisir. Le défaut
            # `numeric` de PAX notait faux toute réponse algébrique non typée —
            # `2*b` de `distrired`, `1-p` de `pairs4`, `15*x/2 - 23/2` de
            # `fnctaff1`. Cela ne concerne que 211 des 12414 réponses du corpus,
            # les autres déclarant leur type.
            ans_type = self._subst(rm.get("type", "default")).strip()
            # `type=draft` (brouillon WIMS) : champ de saisie libre où l'élève
            # pose son calcul. Non noté et facultatif. Le type d'origine est
            # ensuite masqué en "analyze" (good=?analyze) ; on le capte ici pour
            # marquer la réponse comme brouillon (cf. options["draft"]).
            is_draft = ans_type.lower() == "draft"
            # `dragfill` est le `clickfill` dont chaque étiquette ne sert qu'une
            # fois : même widget, même `replygood`, contrainte reportée plus bas
            # dans `options["single_use"]`.
            is_dragfill = ans_type.strip().lower() == "dragfill"
            if is_dragfill:
                ans_type = "clickfill"
            label = _close_inline_math(self._subst(rm.get("name", "")), self.lang)
            good_raw = self._eval_value(rm.get("good", ""))
            weight = float(self._subst(rm.get("weight", "1")) or "1")
            option = self._subst(rm.get("option", ""))
            # `slib/commutesom` (réduire family) accepts the reduced sum in any
            # term order. Mark such litexp/algexp answers `expand` so the checker
            # requires the reduced form but exempts term order (see
            # _slib_commutesom / check_answer's term_order gate). Only when the
            # author set no explicit form option of their own.
            # …et seulement si l'attendu est lui-même développé. Le flag est
            # posé dès l'appel de `commutesom`, sans regarder ce que l'exercice
            # en fait : `oeffac3b` s'en sert pour son énoncé mais attend une
            # **factorisation**, `(2 y + 13)^2`. Le marquer `expand` faisait
            # exiger la forme développée, et l'attendu se voyait refusé
            # lui-même — trois exercices de factorisation notés faux à coup sûr.
            if (
                self.ctx.get("_commutesom_anyorder")
                and ans_type.lower() in ("litexp", "algexp", "formal")
                and not re.search(r"\b(polexpand|expand|polfactor)\b", option)
                and _expected_is_developed(good_raw)
            ):
                option = (option + " expand").strip()
            options: dict = {"option": option} if option else {}
            if is_dragfill:
                options["single_use"] = True
            # Précision WIMS de l'exercice → checkers numériques (numeric,
            # numexp, units, fset). Jusqu'ici figée à 1e-4 côté checker ; on
            # transmet désormais `\precision{M}` (cf. _wims_precision).
            options["precision"] = wims_prec
            # `\range{a,b}` — l'intervalle où `function` compare numériquement
            # (`leftrange`/`rightrange`, défaut `-5,5` dans `oef/var.prep`).
            # Lu par le parseur depuis toujours, jamais transmis jusqu'ici.
            # Seul `function` s'en sert : le poser partout ne ferait que
            # bouger 3978 snapshots pour rien.
            if ans_type.lower() == "function":
                # En liste : les options traversent le JSON des snapshots, et
                # un tuple n'en revient pas égal à lui-même.
                options["range"] = list(plage_exo)
            # `\computeanswer{no}` (défaut) : réponse numérique = valeur, pas un
            # calcul. Transmis au checker numeric.
            if compute_answer:
                options["computeanswer"] = compute_answer

            # Expose to ctx so _render_embed can access them during statement rendering
            self.ctx[f"replygood{n}"] = good_raw
            self.ctx[f"replytype{n}"] = ans_type

            expected = good_raw
            # `analyze_choices` holds the choice list when a radio/menu is
            # *displayed* normally but *checked* via ?analyze (ecrdecimal).
            analyze_choices: str | None = None
            # ?analyze N — réponse vérifiée via :postdef + :test
            analyze_m = re.match(r"^\?analyze\s*(\d+)(?:;(.+))?", good_raw.strip(), re.I)
            if analyze_m:
                var_name = f"val{analyze_m.group(1)}"
                options["analyze_var"] = var_name
                rest = analyze_m.group(2)
                if ans_type in ("radio", "menu"):
                    # radio/menu DISPLAY + analyze-based checking: the part
                    # after ";" is the comma-separated choice list, and the
                    # correct choice comes from the matching :test condition
                    # (e.g. `$val25 issametext $(val11[1;])`). Keep the radio/
                    # menu type so the choices actually render — overriding to
                    # "analyze" here dropped them, leaving an empty <ol>.
                    analyze_choices = rest or ""
                    expected = self._resolve_analyze_expected(var_name, df) or ""
                elif ans_type in ("clickfill", "checkbox", "mark",
                                  "jsxgraph", "reaction"):
                    # Widget DISPLAY + analyze CHECK: keep the widget type so it
                    # renders (draggable labels / boxes) — the pool is in `rest`
                    # and parsed by the widget branch below. The student's value
                    # is fed to val<N> in :test (see run_feedback), so keep
                    # `analyze_var`. `good_raw` keeps "?analyze N;<pool>" which the
                    # clickfill branch splits into correct ("?analyze N") + pool.
                    # ineqinterv1: drag `[`/`]` brackets into the interval slots.
                    #
                    # `jsxgraph` et `reaction` ont rejoint la liste le
                    # 2026-09-05. Leur `rest` est la **configuration** du
                    # widget — la liste des objets à lire
                    # (`\jsq1;\jsme;\jsq3;\jsmax`) ou les dimensions du
                    # dessin (`$val7,$val10,$val12,$val11` → `40,1000,6,1000`)
                    # — et non une réponse. La brancher dans `expected` faisait
                    # d'un réglage un attendu : les cinq `oefstatistiques`
                    # notaient une bonne réponse 0,83 à 0,94, et le corrigé
                    # affichait `\jsq1;\jsme;…` à l'élève.
                    pass
                else:
                    # Remember the author's original reply type before we mask
                    # it as "analyze". The check path needs it to know whether a
                    # comma in the reply is a decimal separator (numeric/numexp)
                    # — so `0,7` in an fr/nl exercise normalises to `0.7` before
                    # being fed to :test (otherwise WIMS' eval reads it as a tuple).
                    options["analyze_input_type"] = ans_type
                    ans_type = "analyze"
                    if rest:
                        expected = rest
                    else:
                        # `$val<N>` is the student's reply, not a stored answer
                        # — the check path uses options["analyze_var"] to feed
                        # the :test section. For debug / auto-fill, peek into
                        # :test for an equality like `$val<N>=<rhs>` and
                        # evaluate `<rhs>` against the current ctx.
                        expected = self._resolve_analyze_expected(var_name, df) or ""

            if ans_type == "radio" and str(n) in getattr(self, "_inline_radio", set()):
                # Inline radio (couf): choices are laid out in the statement by
                # the author (oef-radio-inline spans, value = position). No grid
                # choices; the reply is the selected position and the correct
                # one is the part before ";" in replygood (e.g. "3;2,3,1,4").
                options["inline"] = True
                # Le rang correct est ce qui précède le `;` — **quand c'en est
                # un**. `OEFevalwimsgrph/ineqalghyper1` écrit
                # `replygood1=?analyze 114;$val111` : la notation passe par
                # l'analyse, qui a déjà résolu `expected` plus haut. L'écraser
                # par « ?analyze 114 » donnait un attendu que rien ne peut
                # satisfaire, et refuser d'inliner pour autant faisait
                # disparaître les huit choix que l'auteur avait posés.
                rang = good_raw.split(";", 1)[0].strip() if ";" in good_raw else good_raw.strip()
                if rang.isdigit():
                    expected = rang
                # La palette est posée dans l'énoncé, mais on la garde ici : le
                # corrigé en a besoin pour nommer le choix. Sans elle il annonce
                # « la bonne réponse est 1 » — un rang nu, là où le radio classé
                # dit « Oui, 5 est solution de l'équation ». C'est
                # `options["inline"]` qui empêche le front de dresser la grille,
                # pas une palette vide (cf. `StandardExercise.hasRadioAnswers`).
                if ";" in good_raw:
                    brutes = self._inline_radio_choices(n)
                    palette = [
                        _close_inline_math(c, self.lang) for c in brutes
                    ]
                    if palette:
                        options["choices"] = palette
                        # La forme **d'origine**, telle que l'exercice la range
                        # dans ses variables. Le corrigé et la notation par
                        # analyse en ont besoin : un `:postdef` cherche
                        # couramment le rang de la réponse dans sa propre liste
                        # (`!positionof item $m_reply1 in $val111`), et ce que
                        # le front renvoie est la forme *affichée* — math
                        # refermé pour KaTeX, entité HTML restée en clair.
                        # Aucune des deux ne se retrouve dans la liste brute.
                        if brutes != palette:
                            options["choices_raw"] = brutes

            elif ans_type == "radio":
                choices: list[str] = []
                if analyze_choices is not None:
                    # Choices in author order (they already include "Je ne
                    # sais pas"); the correct one was resolved above via the
                    # analyze condition, so no index/shuffle handling here.
                    choices = [c.strip() for c in analyze_choices.split(",") if c.strip()]
                else:
                    for cm in df.choice_meta:
                        if cm["n"] == n:
                            correct = self._subst(cm.get("good", ""))
                            wrong_raw = self._subst(cm.get("bad", ""))
                            wrong = [w.strip() for w in wrong_raw.split(",") if w.strip()]
                            # Dedup: remove duplicates (correct may already be in wrong)
                            seen_set: set[str] = set()
                            choices = []
                            for c in [correct] + wrong:
                                if c not in seen_set:
                                    seen_set.add(c)
                                    choices.append(c)
                            jnsp = "Je ne sais pas"
                            rng = random.Random(f"{self.seed}_{n}")
                            rng.shuffle(choices)
                            # WIMS always presents "I don't know" as the last
                            # option — append it after shuffling the real choices.
                            if jnsp not in seen_set:
                                choices.append(jnsp)
                            expected = correct
                            break

                    if not choices and ";" in good_raw:
                        # Indexed format: "correct_idx;choice1,choice2,..." (like !menu)
                        # Display order = order in the .def. Authors who want
                        # randomisation do it explicitly (e.g. !shuffle on the valN
                        # used for the choices). Re-shuffling here would double up.
                        idx_str, choices_str = good_raw.split(";", 1)
                        try:
                            correct_idx = int(idx_str.strip())
                            choices = [c.strip() for c in choices_str.split(",") if c.strip()]
                            if 1 <= correct_idx <= len(choices):
                                expected = choices[correct_idx - 1]
                        except (ValueError, IndexError):
                            pass

                # Choices may carry WIMS inline math `\(…)` (e.g. sdlectgraph1's
                # factored forms) — close it to KaTeX `\(…\)` so the frontend
                # renders them instead of showing the raw delimiters. No-op for
                # plain-text choices. `expected` is one of the choices, so close
                # it the same way to keep the reply comparison consistent.
                choices = [_close_inline_math(c, self.lang) for c in choices]
                expected = _close_inline_math(expected, self.lang)
                options["choices"] = choices

            elif ans_type == "menu":
                # WIMS menu format: "correct_index;choice1,choice2,..."
                if analyze_choices is not None:
                    # menu DISPLAY + analyze checking (see the radio branch).
                    options["choices"] = [
                        c.strip() for c in analyze_choices.split(",") if c.strip()
                    ]
                elif ";" in good_raw:
                    idx_str, choices_str = good_raw.split(";", 1)
                    try:
                        correct_idx = int(idx_str.strip())
                        choices = [c.strip() for c in choices_str.split(",") if c.strip()]
                        if 1 <= correct_idx <= len(choices):
                            expected = choices[correct_idx - 1]
                        if "shuffle" in option.lower():
                            rng = random.Random(f"{self.seed}_{n}")
                            rng.shuffle(choices)
                        options["choices"] = choices
                    except (ValueError, IndexError):
                        pass

            elif ans_type in ("checkbox", "multipleclick"):
                # Format: "correct_indices;all_indices" (e.g. "1,3;1,2,3,4").
                # The student's reply is the set of checked option indices;
                # expected is the correct subset, compared order-insensitively
                # (check_set). The checkboxes themselves are emitted inline by
                # _render_embed; no choices list is needed here.
                correct_part = good_raw.split(";", 1)[0] if ";" in good_raw else good_raw
                expected = ",".join(
                    c.strip() for c in correct_part.split(",") if c.strip()
                )

            elif ans_type in ("mark", "click"):
                # Format: "correct_pos;choice1,choice2,..." (WIMS mark / click-in-table)
                # The student's reply is the 1-based column they clicked.
                # expected = that column index as a string.
                if ";" in good_raw:
                    pos_str, _, choices_str = good_raw.partition(";")
                    expected = pos_str.strip()
                    # Les choix se séparent à la virgule (`!item N of $tt`
                    # dans `oef/embed.phtml`) : un `;` qui subsisterait dans un
                    # choix serait de la donnée, pas une frontière.
                    choices = [
                        c.strip()
                        for c in wl.cutitems(choices_str)
                        if c.strip()
                    ]
                    options["choices"] = choices
                else:
                    expected = good_raw.strip()

            elif ans_type == "correspond":
                # Bijection between two columns. expected is the right-column
                # items in their *correct* order (joined by ``,``); the
                # widget config (lefts, shuffled rights, sizes) is exposed
                # via the data-config attribute by _render_embed and also
                # mirrored into options for direct access.
                meta = getattr(self, "_correspond_meta", {}).get(f"reply{n}")
                if meta:
                    expected = ",".join(meta["rights_correct"])
                    options["lefts"] = meta["lefts"]
                    options["rights_shuffled"] = meta["rights_shuffled"]
                    options["partial"] = meta["partial"]
                    options["sizes"] = {
                        "v": meta["sizev"],
                        "hg": meta["sizeh1"],
                        "hd": meta["sizeh2"],
                    }
                else:
                    # _render_embed wasn't called (no \embed{} in statement).
                    # Parse replygood directly to still produce a usable
                    # expected value.
                    rows = wl.cutrows(good_raw)
                    if len(rows) == 2:
                        rights = [
                            self._subst(c.strip())
                            for c in wl.cutitems(rows[1]) if c.strip()
                        ]
                        expected = ",".join(rights)

            elif ans_type == "clickfill":
                # Format: "correct;pool". Split entity-safe — the parts hold
                # HTML entities (&#91; [ , &#93; ] , &#59; ;) whose trailing ";"
                # must not be mistaken for the correct;pool separator. WIMS also
                # accepts "|" as the separator (anstype/fill.inc:15 translates it
                # to a newline/row break), so normalise "|" → ";" first.
                good_raw = good_raw.replace("|", ";")
                # `anstype/fill.inc` : `!rows2lines` puis `!nonempty lines`.
                # La ligne 1 porte la réponse, les suivantes le vivier — un
                # `replygood` qui finit par `;` n'a donc **pas** de vivier, et
                # non un vivier vide qu'il faudrait deviner.
                rows = [r for r in wl.cutrows(good_raw) if r.strip()]
                correct_str = rows[0] if rows else ""
                pool_str = ",".join(rows[1:])
                # La forme affichée et la forme rangée diffèrent : PAX referme
                # le math pour KaTeX (`\(A')` → `\(A'\)`) et développe les
                # délimiteurs (`(d)` → `\left(d\right)`). Un `:test` qui
                # compare la réponse à sa propre liste — `$val9 issametext
                # $(val7[1])` — travaille sur la forme rangée : il faut garder
                # les deux, et savoir passer de l'une à l'autre.
                _brut_par_affiche: dict[str, str] = {}

                def _afficher(brut: str) -> str:
                    vu = _close_inline_math(brut, self.lang)
                    _brut_par_affiche.setdefault(vu, brut)
                    return vu

                correct_items = [
                    _afficher(c.strip()) for c in correct_str.split(",") if c.strip()
                ]
                pool_items = [
                    _afficher(p.strip()) for p in pool_str.split(",") if p.strip()
                ]
                rng = random.Random(f"{self.seed}_{n}")
                # `$wims_fill_option` = `replyoption$i` (`fill.inc:1`) : c'est
                # lui qui décide de l'ordre final de la palette (`fill.after`).
                fill_words = self._subst(
                    self.ctx.get(f"replyoption{n}", "")
                ).lower().split()
                if is_dragfill and correct_items and "analyze_var" not in options:
                    # `fill.inc` compose la palette d'un dragfill autrement que
                    # celle d'un clickfill : ligne 1 (la bonne réponse) **puis**
                    # le complément des lignes suivantes (`!listcomplement`),
                    # sans `!listuniq` — un mot à lettre répétée a besoin d'une
                    # carte par occurrence. Un vivier absent est donc licite :
                    # la palette est alors la réponse elle-même mélangée (les
                    # anagrammes de `oefdeutsch`, où l'on rassemble « Hamburg »
                    # lettre à lettre).
                    choices = list(correct_items)
                    known = set(correct_items)
                    for p in pool_items:
                        if p not in known:
                            choices.append(p)
                            known.add(p)
                    _order_fill_choices(
                        choices, fill_words, rng,
                        is_dragfill=True, slots=len(correct_items),
                    )
                    options["choices"] = choices
                    options["slots"] = len(correct_items)
                    expected = ",".join(correct_items)
                elif "analyze_var" in options:
                    # Analyze-based clickfill (ineqinterv1): the "correct" part is
                    # "?analyze N" — a checking ref, NOT a draggable label. The
                    # palette is the pool only; scoring is via the :test section.
                    seen0: set[str] = set()
                    choices = [c for c in pool_items if not (c in seen0 or seen0.add(c))]  # type: ignore[func-returns-value]
                    _order_fill_choices(choices, fill_words, rng,
                                        is_dragfill=False, slots=1)
                    options["choices"] = choices
                    # Sans ceci, la bonne réponse notait 0 sur les six
                    # `OEFevalwimsgeplan` : l'élève renvoie le libellé affiché,
                    # le `:test` cherche la forme rangée, et `issametext` ne les
                    # rapproche jamais. `_forme_brute` fait la conversion, mais
                    # seulement si on lui donne les deux listes.
                    brutes = [_brut_par_affiche.get(c, c) for c in choices]
                    if brutes != choices:
                        options["choices_raw"] = brutes
                    expected = self._resolve_analyze_expected(options["analyze_var"], df) or ""
                elif len(correct_items) > 1:
                    # Multi-slot drag-compose (e.g. repgraphint): the student
                    # arranges labels from the pool into an ordered sequence.
                    # expected = the ordered sequence (comma-joined); choices =
                    # the pool (it already contains every needed label).
                    seen: set[str] = set()
                    choices = [c for c in pool_items if not (c in seen or seen.add(c))]  # type: ignore[func-returns-value]
                    _order_fill_choices(choices, fill_words, rng,
                                        is_dragfill=False, slots=len(correct_items))
                    options["choices"] = choices
                    options["slots"] = len(correct_items)
                    expected = ",".join(correct_items)
                elif correct_items:
                    # Single-slot: pick the one correct label among distractors.
                    correct = correct_items[0]
                    choices = [correct] + pool_items
                    seen2: set[str] = set()
                    choices = [c for c in choices if not (c in seen2 or seen2.add(c))]  # type: ignore[func-returns-value]
                    _order_fill_choices(choices, fill_words, rng,
                                        is_dragfill=False, slots=1)
                    expected = correct
                    options["choices"] = choices

            # Keep an exact non-integer rational answer as a fraction so the
            # auto-fill inserts e.g. `2/3` rather than the lossy decimal
            # `0.666…` (replygood `$[$val12]` floats it via `$[…]`). Scoped to
            # numeric answers: text rendering still prints `$[2/3]` as a decimal
            # like WIMS. The numeric checker accepts the fraction either way.
            # `default`/`auto` compris : `anstype/default` aiguille vers
            # `numeric` dès que l'attendu s'évalue en nombre, et un attendu qui
            # ne s'évalue pas laisse `_expected_as_fraction` rendre None.
            if (ans_type in ("numeric", "numexp", "default", "auto")
                    and "analyze_var" not in options):
                _frac = self._expected_as_fraction(rm.get("good", ""))
                if _frac is not None:
                    expected = _frac

            if ans_type == "coord":
                # replygood = "<image_url>;<click-zone>" (rows split on ';').
                # Row 1 is the clickable background; the rest is the target zone
                # (e.g. "point,Ax,Ay") the checker compares the click against.
                rows = [r.strip() for r in good_raw.split(";")]
                if rows:
                    options["image"] = rows[0]
                expected = ";".join(rows[1:]).strip()
                # Une zone `bound` ne se décide pas au calcul mais **dans
                # l'image** : `clickzone.c` y remplit la région du clic et
                # regarde si le point de référence a été atteint. Le checker a
                # donc besoin du fichier, que seul le moteur sait situer.
                if re.search(r"(^|;)\s*b(ound)?\s*,", expected, re.I):
                    # Relatif à la racine des ressources, non absolu : cette
                    # option entre dans les snapshots, qu'un chemin absolu
                    # rendrait dépendants de l'endroit où le corpus est monté.
                    images = os.path.join(
                        os.path.dirname(os.path.dirname(self.def_path)), "images"
                    )
                    options["images_dir"] = os.path.relpath(images, _RESSOURCES_ROOT)
                # The pixel↔repère transform (from slib/draw/repere) lets the
                # feedback report the click in repère units instead of pixels.
                xform = self.ctx.get("_repere_transform")
                if xform:
                    options["transform"] = xform

            # `?analyze N` n'est pas une réponse : c'est la référence de la
            # variable que `:test` examinera. Le laisser dans `expected` fait
            # passer un marqueur pour un attendu — le bouton « Réponse auto »
            # écrivait `?analyze 80` dans le champ, et la suite lente soumettait
            # la même chose en croyant soumettre la bonne réponse (25 échecs en
            # biologie, le 2026-09-05). On tente donc de le résoudre depuis
            # `:test`, comme le fait déjà `clickfill`, et on le vide à défaut :
            # la note de ces champs vient des conditions, jamais d'ici.
            if "analyze_var" in options and re.match(
                r"^\?analyze\b", (expected or "").strip(), re.I
            ):
                expected = self._resolve_analyze_expected(
                    options["analyze_var"], df
                ) or ""

            # Champ non noté ni obligatoire (« ungraded ») :
            #  - brouillon `type=draft` (l'élève y pose son calcul) ;
            #  - champ `analyze` que **rien ne peut noter** : son attendu est
            #    vide, et aucun test ne regarde sa valeur. Le laisser actif
            #    force tout l'exercice sur `run_analyze`, dont le score se
            #    calcule sur les conditions de `:test` — absentes ici, d'où un
            #    total nul et la note 0 quoi que l'élève écrive. Les cinq
            #    `OEFevalwimsgrph/eqalghyper*` en étaient insolubles : leur
            #    zone de brouillon 10×30 (`default=empty`) emportait la note du
            #    QCM qui la précède.
            # Le critère porte sur la **structure**, non sur le mot `default` :
            # `default=vide` et `default=empty` nomment la valeur substituée à
            # un champ laissé vide, et sur une vraie réponse (fset, numeric…)
            # `default=vide` signifie « vide = ensemble ∅ » — cf. oefresolalg
            # synth*, qui doit rester noté. C'est l'absence de test, pas le
            # libellé, qui distingue le brouillon.
            if is_draft or (
                ans_type.lower() == "analyze"
                and not (expected or "").strip()
                and not self._analyze_var_is_graded(
                    options.get("analyze_var", ""), n, df
                )
            ):
                options["ungraded"] = True

            answers.append(
                AnswerDef(
                    label=label,
                    expected=expected,
                    answer_type=ans_type,
                    options=options,
                    weight=weight,
                    input_name=f"reply{n}",
                    logical_name=label if label else f"reply{n}",
                )
            )

        # Optional-separator slots (e.g. the ∪ between two intervals in
        # ineqva2interv). Such a slot is a clickfill+analyze whose pool is a
        # single fixed symbol and whose :test condition fixes it via
        # `<symbol> issametext $val<N>` in the *union* case only. It is
        # ambiguous to resolve in isolation (the single-interval branch leaves
        # it blank), so _resolve_analyze_expected returns "". Resolve it here:
        # the symbol belongs in the slot iff there *is* a second interval —
        # i.e. some later reply has a non-empty expected.
        for i, a in enumerate(answers):
            if (
                a.answer_type == "clickfill"
                and "analyze_var" in a.options
                and not a.expected
                and len(a.options.get("choices", [])) == 1
                and self._slot_fixed_to_pool_literal(a.options["analyze_var"], df)
            ):
                if any(later.expected for later in answers[i + 1 :]):
                    a.expected = a.options["choices"][0]

        return answers

    def _slot_fixed_to_pool_literal(self, var_name: str, df: "DefFile") -> bool:
        """True if :test/:postdef contains `<literal> sametext $<var>` (or the
        mirror) where the other operand is a *fixed literal*, not a `$ref`.
        Marks an optional-separator slot (e.g. the ∪ symbol) whose presence is
        case-dependent — see the post-pass in `_extract_answers`."""
        from ..def_parser import IfBlock  # noqa: PLC0415
        op = r"(?:is|not)?sametext"
        pat = re.compile(
            rf"(\S+)\s+{op}\s+\${re.escape(var_name)}\b"
            rf"|\${re.escape(var_name)}\b\s+{op}\s+(\S+)"
        )

        def walk(body: list) -> bool:
            for instr in body:
                if isinstance(instr, IfBlock):
                    for m in pat.finditer(instr.condition):
                        other = (m.group(1) or m.group(2) or "").strip("()")
                        if other and not other.startswith("$"):
                            return True
                    if walk(instr.then_body) or walk(instr.else_body):
                        return True
            return False

        return walk(df.sections.get("test", [])) or walk(
            df.sections.get("postdef", [])
        )

    def _cmd_mathsubst(self, args: str) -> str:
        """!mathsubst x=1 in x^2+x -> 1^2+1"""
        # (This is already handled inline in _eval_cmd, but keeping the method stub
        # if other parts of the engine call it directly)
        return self._eval_cmd("mathsubst", args)


def _jsxgraph_value_dim(value: str) -> int:
    """Dimension of a jsxgraph draggable's initial value: a bracketed
    ``[x,y]`` → the number of top-level items inside (2 here); anything else
    (a scalar like ``1``) → 1. Used to decide whether the reply captures just
    ``.X()`` or both ``.X()`` and ``.Y()``."""
    v = value.strip()
    if not v.startswith("["):
        return 1
    depth = 0
    items = 1
    for ch in v:
        if ch in "([{":
            depth += 1
        elif ch in ")]}":
            depth -= 1
            if depth == 0:
                break
        elif ch == "," and depth == 1:
            items += 1
    return items


# Les identifiants d'une expression arithmétique — cf. `_eval_arith`, qui s'en
# sert pour ne convertir du contexte que ce qu'il va lire.
_IDENT_RE = re.compile(r"[A-Za-z_]\w*")


# ── Les neuf niveaux de sévérité de WIMS (`oef/exo.init`) ────────────────────
#
# L'enseignant qui pose un exercice sur une feuille choisit un `qcmlevel` de 1 à
# 9 ; ce seul curseur commande dix réglages. Les voici, ligne par ligne, dans
# l'ordre des niveaux. Le défaut de WIMS est le niveau 1 (`oef/default` :
# `default_choice=1,1,1,4,1,1,1`, deuxième valeur).
_SEVERITE: dict[str, tuple[float, ...]] = {
    # Combien de propositions une palette montre.
    "qcmpresent": (3, 3, 4, 5, 5, 6, 7, 8, 8),
    # La bonne réponse est-elle garantie parmi elles ?
    "qcmgood": (1, 1, 1, 1, 0, 0, 0, 0, 0),
    # Une réponse fausse coûte-t-elle des points ?
    "penalty": (0, 0, 0, 0, 0, 1, 1, 1, 1),
    # Montre-t-on la bonne réponse après coup ?
    "givegood": (1, 1, 1, 1, 1, 1, 0, 0, 0),
    # Montre-t-on le corrigé ?
    "givesol": (1, 1, 1, 0, 0, 0, 0, 0, 0),
    # Montre-t-on le commentaire de correction ?
    "givefeed": (1, 1, 1, 1, 1, 1, 1, 1, 1),
    # Montre-t-on l'indication ?
    "givehint": (1, 1, 1, 1, 1, 0, 0, 0, 0),
    # Exposant appliqué à la note finale.
    "scorepower": (1, 1, 1, 1.1, 1.3, 1.5, 1.7, 2, 2.6),
    # Exposant de la pénalité : `((n-j)/n)^freepower` pour j essais faux.
    "freepower": (1, 1.5, 2, 2.5, 3, 3.5, 4, 4.5, 5),
    # Crédit d'une réponse juste « à la précision près ».
    "precweight": (0.9, 0.8, 0.7, 0.55, 0.4, 0.25, 0.1, 0, 0),
}

# Le niveau que PAX applique faute de mieux.
#
# `oef/default` donne 1, mais c'est le défaut du *menu* de création d'une
# feuille, pas celui des feuilles réelles. Trois mesures faites sur un WIMS de
# référence (`OEFevalwimsfctref/valtrigo1`, cf. `check_numeric`) le placent au
# **niveau 3** :
#
#     deux réponses approchées    4,9/10 = 0,7²
#     une juste, une approchée    7,2/10 = 0,85²
#     une juste, une fausse       2,5/10 = 0,5²
#
# C'est donc le niveau 3 que PAX prend, jusqu'à ce que la feuille porte le
# réglage — il vit là chez WIMS, et n'a rien à faire dans le moteur.
_NIVEAU_DEFAUT = 3

# Largeur par défaut du champ de saisie de chaque type, en caractères, relevée
# dans les `anstype/<type>.input` de WIMS (`!bound inputsize … default N`).
# `default` — le type des réponses non typées — vaut 30 ; c'est aussi le repli
# pour un type qui n'y figurerait pas.
_TAILLE_DEFAUT: dict[str, int] = {
    "algexp": 40, "aset": 30, "atext": 40, "case": 40, "chembrut": 40,
    "chemformula": 40, "chset": 18, "complex": 20, "default": 30, "equation": 40,
    "formal": 40, "fset": 30, "function": 40, "litexp": 40, "nocase": 40,
    "numeric": 20, "numexp": 20, "range": 20, "raw": 40, "reorder": 10,
    "set": 30, "sigunits": 25, "units": 25, "vector": 30, "wlist": 40,
}


def _uniques(items: list[str]) -> list[str]:
    """`!listuniq` : les doublons partent, l'ordre d'apparition reste."""
    vus: set[str] = set()
    out: list[str] = []
    for x in items:
        x = x.strip()
        if x and x not in vus:
            vus.add(x)
            out.append(x)
    return out


def _find_matching_bracket(s: str, start: int, open_c: str, close_c: str) -> int:
    """Find the index of the closing bracket matching s[start] = open_c."""
    depth = 0
    for i in range(start, len(s)):
        if s[i] == open_c:
            depth += 1
        elif s[i] == close_c:
            depth -= 1
            if depth == 0:
                return i
    return len(s) - 1


# _wims_* functions and _WIMS_* constants → compare.py (voir re-export en tête)

