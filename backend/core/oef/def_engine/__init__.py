"""
Engine for compiled WIMS .def script files.

Evaluates the variable section, renders the :question section (or the literal
question= text), extracts answer metadata, and returns an ExerciseRender.
"""

from __future__ import annotations

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

# `\nextstep` ne dit jamais combien d'étapes restent : l'exercice s'arrête quand
# la variable devient vide. On rejoue donc `:postdef` jusqu'à cet arrêt, borné
# pour qu'un `.def` mal formé ne parte pas en boucle (le maximum observé sur le
# corpus est 6).
_MAX_NEXTSTEPS = 32

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
from .slib import _SlibExit, _SlibMixin, _split_top_level_commas
from ..numfmt import format_wims_float
from ..i18n import list_separator, uses_comma_decimal
from . import wims_lists as wl
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

# Answer types whose value is an algebraic expression (potentially long), so a
# no-embed fallback reply field gets a wider default than a numeric one.
_WIDE_FALLBACK_TYPES = {
    "litexp", "algexp", "formal", "function", "numexp", "default", "auto",
}

# Detects "$a,$b,$c" pattern (comma-concat of variable references only).
# Used in _eval_value to neutralise tabs in the substituted parts so the
# resulting list stays unambiguously comma-separated.
_COMMA_VARLIST_RE = re.compile(
    r"^\s*(?:\$\w+|\$\([^)]+\))(?:\s*,\s*(?:\$\w+|\$\([^)]+\)))+\s*$"
)

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


def _split_protected(s: str, seps: str) -> list[str]:
    """Découpe `s` sur `seps`, en sautant les paires `()`/`[]`/`{}`.

    Port de `strparstr` (`liblines.c`), sur lequel repose `find_item_end` : un
    séparateur ne compte qu'à profondeur zéro. Les segments vides sont
    conservés — c'est à l'appelant de décider s'ils comptent.
    """
    parts, depth, cur = [], 0, []
    for ch in s:
        if ch in "([{":
            depth += 1
        elif ch in ")]}":
            depth = max(0, depth - 1)
        if ch in seps and depth == 0:
            parts.append("".join(cur)); cur = []
        else:
            cur.append(ch)
    parts.append("".join(cur))
    return parts


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
    def __init__(self, seed: int, def_path: str | None = None):
        self.seed = seed
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
        # Variables du mini-interpréteur PARI. WIMS pilote un unique processus
        # `gp` par exécution, donc les `!exec pari` successifs se partagent leur
        # état : oefforpython.fr définit `l=vector(n);for(…)` dans un appel puis
        # l'affiche avec `print(l)` dans le suivant.
        self.pari_session: dict[str, object] = {}
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
        self._deadline = time.monotonic() + _RENDER_TIME_BUDGET
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

        # Budget temps : abandonne le calcul des variables s'il s'emballe
        # (boucle non terminante d'un slib incomplet). On poursuit le rendu avec
        # l'état partiel plutôt que de bloquer plusieurs minutes.
        self._deadline = time.monotonic() + _RENDER_TIME_BUDGET
        try:
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
        for a in answers:
            if a.expected and "/api/render/svg/" in a.expected:
                a.expected = inline_svg_imgs(a.expected)
            choices = a.options.get("choices")
            if choices:
                a.options["choices"] = [
                    inline_svg_imgs(c) if "/api/render/svg/" in c else c
                    for c in choices
                ]

        # If the question text has no input/slot widget but the exercise
        # declares replies, append a default input for each so the frontend
        # has somewhere to type the answer (matches WIMS' fallback behaviour).
        # Skip this for dynamic steps exercises (they control visibility per step).
        segments = _segment_statement(html)
        widget_names = {
            s["name"] for s in segments
            if s["type"] in ("input", "slot", "menu", "textarea", "correspond")
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
            not in ("radio", "menu", "mark", "correspond", "jsxgraph")
        ]
        # Append a default field per reply when the question carries no widget.
        # For dynsteps/course this is reached only when there are no embeds
        # (otherwise widget_names is set); `answers` is already filtered to the
        # active step above, so we add exactly the current step's fields.
        if text_replies and not widget_names:
            # With several fields (e.g. a course step's two replies) prefix each
            # with its label so the student can tell them apart.
            show_labels = len(text_replies) > 1
            for a in text_replies:
                # No embed → WIMS renders a default-width reply field. Algebraic
                # answers (litexp/algexp…) can be long expressions
                # (`162sqrt(6)+567`), so give them room; a bare 10 was too narrow
                # (devred). Numeric-ish answers keep a modest default.
                size = 20 if a.answer_type.lower() in _WIDE_FALLBACK_TYPES else 14
                label = ""
                if show_labels and a.label and a.label.strip():
                    label = _close_inline_math(a.label.strip(), self.lang) + " : "
                html += (
                    f'<br>{label}<span class="oef-input" name="{a.input_name}" '
                    f'data-size="{size}"></span>'
                )
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
                # Run for its side effects (sets ctx['ins_url'], etc.) — the
                # call's textual output is empty for our supported procs.
                self._cmd_readproc(f"{instr.path} {instr.args}".strip())
                if output_buf is not None:
                    output_buf.append("")

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
            items = items_raw.split("\t") if "\t" in items_raw else items_raw.split(",")
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
        try:
            start = int(round(float(self._eval_arith(m.group(1).strip()))))
            end = int(round(float(self._eval_arith(m.group(2).strip()))))
        except (ValueError, TypeError):
            return

        var = loop.var.lstrip("$")
        saved = self.ctx.get(var)
        # Backstop contre une borne géante à corps vide (le budget temps du
        # rendu ne s'arme que si le corps s'exécute) : cap dur d'itérations.
        for i in range(start, min(end, start + 100000) + 1):
            self.ctx[var] = str(i)
            self._exec(loop.body, output_buf)
        if saved is not None:
            self.ctx[var] = saved
        else:
            self.ctx.pop(var, None)

    def _eval_value(self, value: str) -> str:
        """Evaluate the RHS of an assignment."""
        # !cmd — WIMS command
        if value.startswith("!"):
            cmd_line = value[1:].strip()
            cmd, _, args = cmd_line.partition(" ")
            cmd = cmd.lower()
            if cmd == "nosubst":
                return args

            # For other commands, substitute variables first
            args = self._subst(args)
            return self._eval_cmd(cmd, args)

        # $[expr] — arithmetic
        if value.startswith("$["):
            return self._eval_dollar_bracket(value)

        # Pattern: comma-separated list of $var references only
        # (e.g. "val14=$val19,$val37,$val52,...").  Substitute each ref and
        # neutralise any tabs in the substituted content so the resulting
        # comma-separated list is unambiguous to $(var[i]) access.
        if _COMMA_VARLIST_RE.match(value):
            parts = [self._subst(ref) for ref in re.split(r"\s*,\s*", value.strip())]
            # An item that is a comma-laden HTML blob (e.g. a JSXGraph board
            # div) can't be comma-joined without breaking $(var[i]); use a TAB
            # separator. Plain comma-data items (numbers, fractions) keep the
            # flattening comma-join.
            if any("," in p and "<" in p for p in parts):
                return "\t".join(parts)
            # La tabulation interne devient un **saut de ligne**, pas une
            # espace. Elle doit disparaître — `_split_items` la prendrait pour
            # un séparateur d'items et l'indexation `$(liste[n])` s'en
            # trouverait faussée — mais elle sépare aussi les commandes d'une
            # figure : les items d'`oefmolecule/lewis` accumulés par
            # `val26=$val26,$val51` portent `polyline …<TAB>polyline …`. Réduite
            # à une espace, flydraw n'y voyait qu'une seule ligne brisée, d'où
            # des symboles de liaison en zigzag. Le saut de ligne, lui, sépare
            # les commandes sans séparer les items.
            return ",".join(p.replace("\t", "\n") for p in parts)

        # Literal string with variable substitution
        return self._subst(value)

    def _eval_dollar_bracket(self, s: str) -> str:
        """Evaluate $[expr] — find the outermost brackets and eval."""
        # May be embedded in a larger string, e.g. "prefix$[expr]suffix"
        result = []
        i = 0
        while i < len(s):
            if s[i] == "$" and i + 1 < len(s) and s[i + 1] == "[":
                end = _find_matching_bracket(s, i + 1, "[", "]")
                expr = s[i + 2 : end]
                result.append(self._eval_arith(expr))
                i = end + 1
            else:
                result.append(s[i])
                i += 1
        return "".join(result)

    def _eval_arith(self, expr: str) -> str:
        """Evaluate a WIMS arithmetic expression string."""
        # 1. Substitute all variable references
        expr = self._subst_for_arith(expr)
        # 1b. An empty function argument — e.g. `rint()` produced when an
        # undefined/empty variable was substituted into `rint($confparm1)` —
        # is a failed numeric calc. WIMS' `$[…]` yields NaN here; returning the
        # literal `rint()` instead would slip past guards like
        # `!ifval NaN isin $x or $x=` (deve7: confparm1 unset → must fall back).
        if re.search(r"[A-Za-z_]\w*\(\s*\)", expr):
            return "NaN"
        # 2. Replace ^ with ** for Python
        expr = expr.replace("^", "**")
        # 3. Evaluate
        ns = dict(_MATH_NS)
        # Also inject current context for bare variable names
        for k, v in self.ctx.items():
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
        except Exception:
            return expr  # return as-is on failure

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

    @staticmethod
    def _tab_is_separator(value: str) -> bool:
        """Whether the TAB acts as the list separator in ``value``.

        The WIMS list separator is the comma. pax additionally uses a TAB as an
        *internal* separator for lists whose items contain commas (HTML/board
        blobs — see _eval_assignment), where each item ends in a non-comma char
        (``>``/``}``) so the tab follows it. But a tab that merely follows a
        comma (``,\\t``) is cosmetic source whitespace, not a separator: e.g.
        ``val7=… suivante&nbsp;,\\t… suivantes&nbsp;`` is a 2-item *comma* list,
        the tab just padding the source. So a TAB is the separator only when at
        least one tab is preceded (modulo spaces) by a non-comma character.

        Tabs *inside* ``[...]`` don't count: a multi-line code blob stored as
        ``[python,[def f():\\t a=0]]`` keeps its newlines-as-tabs within the
        brackets, so the top-level separator there is still the comma.
        """
        if "\t" not in value:
            return False
        depth = 0
        last = ""
        for ch in value:
            if ch == "[":
                depth, last = depth + 1, ch
            elif ch == "]":
                depth, last = max(0, depth - 1), ch
            elif ch == "\t":
                if depth == 0 and last not in ("", ","):
                    return True
            elif not ch.isspace():
                last = ch
        return False

    def _split_list_items(self, value: str) -> list[str]:
        """Split a WIMS list value into items (TAB- or comma-separated)."""
        if self._tab_is_separator(value):
            return value.split("\t")
        # Comma split, but keep commas nested inside parentheses intact.
        return re.split(r",(?![^(]*\))", value)

    def _split_wims_items(self, value: str) -> list[str]:
        """Split a WIMS list whose items are separated by ``,`` OR ``;`` — at
        bracket depth 0 and outside HTML entities.

        WIMS' ``!append item`` switches to a TAB separator when an item itself
        holds a comma (``\\(\\large 2,5 \\times 10^{19})``); the very common
        ``!translate internal \\t to ;`` idiom then turns that TAB into ``;``. So
        a list with comma-bearing items ends up ``;``-separated (brevet01's QCM
        choices ``\\(25),\\(1000);\\(4·10^{22});\\(2,5·10^{19})``) and a naive
        comma split crams the tail into one item. Entities (``&#44;`` comma,
        ``&alpha;``) and ``()[]{}`` groups are protected, so we scan char by
        char rather than regex-split."""
        if self._tab_is_separator(value):
            return value.split("\t")
        parts: list[str] = []
        depth = 0
        start = 0
        i = 0
        n = len(value)
        while i < n:
            c = value[i]
            if c == "&" and (em := re.match(r"&#?\w+;", value[i:])):
                i += em.end()
                continue
            if c in "([{":
                depth += 1
            elif c in ")]}":
                depth = max(0, depth - 1)
            elif depth == 0 and c in ",;":
                parts.append(value[start:i])
                start = i + 1
            i += 1
        parts.append(value[start:])
        return parts

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
        items = self._split_list_items(value)
        # WIMS indices are 1-based and a negative index counts from the end with
        # -1 = the *last* item, **inclusive** (`[2..-1]` = item 2 through the
        # last). Python's `items[1:-1]` would drop the last, so map a negative
        # end to its inclusive Python bound (-1 → None, -2 → -1, …).
        py_end: int | None = end
        if end < 0:
            py_end = end + 1 or None
        return ",".join(items[start - 1 : py_end])

    def _resolve_indexed1(self, m: re.Match) -> str:
        """Resolve $(var[n]) — 1-indexed item from tab/semicolon/comma-separated list."""
        name, idx_expr = m.group(1), m.group(2)
        value = self.ctx.get(name, self.ctx.get(name.lower(), ""))
        if not value:
            return ""
        idx_s = self._subst_for_arith(idx_expr)

        # A WIMS list item is delimited by `,` or `;` (the `;` arising from the
        # append-tab + `!translate \t→;` idiom for comma-bearing items — brevet01
        # QCM choices). `_split_wims_items` splits on both at bracket depth 0
        # while protecting HTML entities (`&#44;`) — which is why a naive `;`
        # split was previously avoided. TAB-joined lists are handled there too.
        if self._tab_is_separator(value):
            delimiter = "\t"
            items = value.split("\t")
        else:
            delimiter = ","
            items = self._split_wims_items(value)

        # Try to parse as single integer first
        try:
            idx = int(round(float(self._eval_arith(idx_s))))
            if 1 <= idx <= len(items):
                return items[idx - 1].strip()
            # WIMS negative index: -1 = last item, -2 = second-to-last, …
            if -len(items) <= idx <= -1:
                return items[idx].strip()
            return ""
        except (ValueError, TypeError):
            pass

        # Handle list of indices (WIMS feature): $(var[$list]) where $list='5,4'
        # Returns items 5 and 4, separated by same delimiter as source
        idx_list_str = idx_s.strip()
        idx_parts = idx_list_str.split(",") if "," in idx_list_str else idx_list_str.split("\t")
        result_items = []
        for idx_part in idx_parts:
            try:
                idx = int(round(float(self._eval_arith(idx_part.strip()))))
                if 1 <= idx <= len(items):
                    result_items.append(items[idx - 1].strip())
            except (ValueError, TypeError):
                continue
        return delimiter.join(result_items) if result_items else ""

    @staticmethod
    def _split_rows_by_semi(value: str) -> list[str]:
        """Split by ';' at bracket depth 0, mirroring WIMS' rows2lines().

        WIMS (liblines.c rows2lines) treats a ';' as a matrix-row separator
        only when it sits outside any (), [], {} group and outside an HTML
        entity (&alpha; / &#58;). A ';' nested in brackets — e.g. the
        column-vector display ``\\([7;5]\\)`` — or one closing an HTML entity
        is part of the cell, not a separator. Unbalanced brackets fall back to
        a literal ';' (find_matching returns nothing, scan keeps going), again
        matching the C source.
        """
        close_of = {"(": ")", "[": "]", "{": "}"}

        def find_matching(start: int, close: str) -> int:
            """Index of the nesting-aware match for ``close``, or -1."""
            parenth = brak = brace = 0
            for i in range(start, len(value)):
                ch = value[i]
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
                    continue
                if parenth < 0 or brak < 0 or brace < 0:
                    if ch != close or parenth > 0 or brak > 0 or brace > 0:
                        return -1
                    return i
            return -1

        rows: list[str] = []
        n = len(value)
        start = i = 0
        while i < n:
            ch = value[i]
            if ch in close_of:
                j = find_matching(i + 1, close_of[ch])
                i = (j + 1) if j != -1 else (i + 1)
            elif ch == ";":
                rows.append(value[start:i])
                start = i = i + 1
            elif ch == "&" and i + 1 < n and value[i + 1].isalpha():
                j = i + 1
                while j < n and value[j].isalpha() and j - i < 14:
                    j += 1
                i = j + 1  # WIMS skips the entity's terminating ';' too
            elif ch == "&" and i + 1 < n and value[i + 1] == "#":
                j = i + 2
                while j < n and value[j].isdigit() and j - i < 6:
                    j += 1
                i = j + 1
            else:
                i += 1
        rows.append(value[start:])
        return rows

    def _resolve_indexed2(self, m: re.Match) -> str:
        """Resolve $(var[n;m]) — row n, column m. Supports a list of row indices."""
        name, row_expr, col_expr = m.group(1), m.group(2), m.group(3)
        value = self.ctx.get(name, self.ctx.get(name.lower(), ""))
        if not value:
            return ""
        row_s = self._subst_for_arith(row_expr)
        col_s = self._subst_for_arith(col_expr).strip()

        # Row-separator detection. The OEF source frequently writes
        #   \text{list=item1;\nitem2;\nitem3;\nitem4}
        # which compiles to ``item1;\titem2;\titem3;\titem4`` — the tab is the
        # cosmetic newline, the *real* separator is ``;``. Splitting by tab
        # first would leave a stray ";" on each row (Quiz course03_2step's
        # enonceb list). So: when ``;`` is present AND ``[n;]`` asks for a
        # whole row (col_expr empty), prefer ``;``. For genuine 2D matrices
        # with ``[n;m]``, the existing tab-first split is preserved because
        # those typically don't carry inner ``;`` between rows.
        prefer_semi = (not col_s) and (";" in value)
        if prefer_semi:
            row_sep = ";"
            rows = self._split_rows_by_semi(value)
        elif "\t" in value:
            row_sep = "\t"
            rows = value.split("\t")
        else:
            row_sep = ";"
            rows = self._split_rows_by_semi(value)

        # WIMS feature: $(matrix[$list;]) where $list = "2,3,1,4" returns rows
        # 2,3,1,4 joined by the source separator. Used for shuffled matrices.
        def parse_indices(s: str) -> list[int] | None:
            parts = s.split(",") if "," in s else s.split("\t")
            if len(parts) <= 1:
                return None
            indices: list[int] = []
            for p in parts:
                try:
                    indices.append(int(round(float(self._eval_arith(p.strip())))))
                except (ValueError, TypeError):
                    return None
            return indices

        # Plage de lignes `a..b` / `a to b` — même sélecteur que les colonnes.
        # `calc_rowof` la traite au même titre qu'un indice ; sans elle,
        # `$(val13[2..-1;])` (unitecell : « toutes les lignes sauf la taille »)
        # rendait la chaîne vide et l'exercice perdait ses organites.
        if re.search(r"\.\.|\s+to\s+", row_s):
            picked_s = self._select_rows(rows, row_s, row_sep)
            if not col_s:
                return picked_s
            return row_sep.join(
                self._select_cols(_split_protected(r, ";,"), col_s)
                for r in picked_s.split(row_sep) if r
            )

        idx_list = parse_indices(row_s.strip())
        if idx_list is not None:
            picked = [rows[i - 1] for i in idx_list if 1 <= i <= len(rows)]
            if not col_s:
                return row_sep.join(p.strip() for p in picked)
            # Même sélecteur de colonnes que la branche « ligne unique » —
            # sinon `[liste;liste]` (`calc_columnof` appelle `calc_itemof` sur
            # chaque ligne, avec le même analyseur d'indices) ne rendait rien.
            # Une ligne dont la sélection est vide compte quand même : la boucle
            # de `calc_columnof` ajoute un séparateur par ligne, sans condition.
            return row_sep.join(
                self._select_cols(_split_protected(r, ";,"), col_s) for r in picked
            )

        # Empty row spec → column `col` across ALL rows, e.g. $(matrix[;1])
        # (cof builds the correspond's right column this way). Joined by "," so
        # `$lefts;$(m[;1])` stays a 2-part "lefts;rights" with comma items.
        if not row_s.strip():
            if not col_s:
                return value
            try:
                col = int(round(float(self._eval_arith(col_s))))
            except (ValueError, TypeError):
                return ""
            # Les virgules protégées ne coupent pas une cellule : la grille de
            # `oefmolecule/lewis` est faite de `(H,0),(LL,1),…`, et un découpage
            # naïf rendait `As H_3,(H,100,100` pour sa colonne 1 — d'où un
            # nombre de lignes faux et une molécule tronquée.
            out = []
            for r in rows:
                cols = _split_protected(r, ";,")
                if 1 <= col <= len(cols):
                    out.append(cols[col - 1].strip())
            return ",".join(out)

        try:
            row = int(round(float(self._eval_arith(row_s))))
        except (ValueError, TypeError):
            return ""
        if not (1 <= row <= len(rows)):
            return ""

        # If col_expr is empty, return entire row
        if not col_s:
            return rows[row - 1].strip()

        cols = _split_protected(rows[row - 1], ";,")
        return self._select_cols(cols, col_s)

    def _select_rows(self, rows: list[str], row_s: str, sep: str) -> str:
        """Lignes d'une plage `a..b` / `a to b`, bornes négatives comprises.

        Mêmes règles que `_select_cols` — l'indice négatif compte depuis la fin
        et la plage est **inclusive** —, appliquées aux lignes.
        """
        n = len(rows)

        def _norm(i: int) -> int:
            return i + n + 1 if i < 0 else i

        a, _, b = re.split(r"(\.\.|\s+to\s+)", row_s.strip(), maxsplit=1)[:3] or ("", "", "")
        try:
            start = _norm(int(round(float(self._eval_arith(a.strip())))))
            end = _norm(int(round(float(self._eval_arith(b.strip())))))
        except (ValueError, TypeError):
            return ""
        if start > end:
            start, end = end, start
        return sep.join(
            rows[i - 1].strip() for i in range(start, end + 1) if 1 <= i <= n
        )

    def _select_cols(self, cols: list[str], col_s: str) -> str:
        """Select column(s) from a row's cells.

        ``col_s`` is a single 1-based index, a WIMS range ``a..b``, or a
        **comma-separated list** of indices. Bounds may be negative (``-1`` =
        last column), so ``2..-1`` means "from column 2 to the end" (used by
        quizz 0408's ``$(matrix[row;2..-1])`` to collect the divisor columns).
        Returns the selected cells joined by ``,``; empty string if the spec
        can't be parsed.

        The list form is `calc.c`'s `_blockof` else-branch: it evaluates each
        index in turn and **skips** those out of range instead of failing, so a
        shuffled index list can be applied to a shorter row. The range test
        comes first, as it does there.
        """
        n = len(cols)

        def _norm(i: int) -> int:
            # WIMS counts negative indices from the end: -1 → n, -2 → n-1.
            return i + n + 1 if i < 0 else i

        if ".." in col_s:
            a, _, b = col_s.partition("..")
            try:
                start = _norm(int(round(float(self._eval_arith(a.strip())))))
                end = _norm(int(round(float(self._eval_arith(b.strip())))))
            except (ValueError, TypeError):
                return ""
            if start > end:
                start, end = end, start
            sel = [cols[i - 1].strip() for i in range(start, end + 1) if 1 <= i <= n]
            return ",".join(sel)

        if "," in col_s:
            sel = []
            for part in col_s.split(","):
                try:
                    i = _norm(int(round(float(self._eval_arith(part.strip())))))
                except (ValueError, TypeError):
                    continue
                if 1 <= i <= n:
                    sel.append(cols[i - 1].strip())
            return ",".join(sel)

        try:
            col = _norm(int(round(float(self._eval_arith(col_s)))))
        except (ValueError, TypeError):
            return ""
        if 1 <= col <= n:
            return cols[col - 1].strip()
        return ""

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
            # Les items vides comptent : `!item N of` les indexe déjà ainsi
            # (`item 3 of "f'(x),,reply4"` = `reply4`), et WIMS ne fournirait
            # pas `!nonempty items` si `!itemcnt` les ignorait de lui-même. Une
            # liste dont les trous portent du sens — les colonnes sans signe
            # d'un tableau de variation (`x,reply1,,reply2,,reply3`) — était
            # sinon comptée trop court, et `slib/function/tabsignes` bâtissait
            # 4 colonnes au lieu de 7.
            subst_args = self._subst(args)
            if not subst_args.strip():
                return "0"
            # `itemnum` passe par `find_item_end` = `strparstr(p, ",")` : les
            # virgules protégées par `()`/`[]`/`{}` ne séparent pas.
            # Indissociable du séparateur de `!makelist` ci-dessous : seul,
            # ce correctif fait passer `slib/stat/dataproc` dans sa branche
            # pondérée — la bonne — mais celle-ci reçoit alors un
            # `slib_weight` tabulé, invalide en PARI, et `oefstat/mean`
            # ressort son `print((…)` en clair. Les deux ensemble donnent la
            # moyenne juste.
            items = _split_protected(subst_args, ",\t")
            if "\t" in subst_args:
                # Tabulations : ce sont des séparateurs de *lignes*, et une
                # ligne blanche n'est pas un item — les listes multi-lignes des
                # `.def` en intercalent pour aérer (`oefsuites1S/cvgequot`
                # sépare deux groupes d'énoncés par un `\t\t`, et chaque `,<TAB>`
                # produirait sinon un item fantôme). Les compter décalait le
                # tirage aléatoire vers un énoncé vide.
                items = [x for x in items if x.strip()]
            # Séparées par des virgules, au contraire, les cases vides portent
            # du sens : les colonnes sans signe d'un tableau de variation
            # (`x,reply1,,reply2,,reply3`) en sont, et `slib/function/tabsignes`
            # bâtissait 4 colonnes au lieu de 6 quand on les ignorait.
            return str(len(items))

        if cmd in ("rowcnt", "rowcount", "rowno", "rownum"):
            val = self._subst(args)
            return str(len(self._split_rows(val)))

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

        if cmd in ("getopt", "getdef"):
            return self._cmd_getopt(args)

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
            return "\n".join(x.strip() for x in _split_top_level_commas(s) if x.strip())

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

        if cmd in ("randfile",):
            return ""

        if cmd in ("randrecord",):
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

        if cmd in ("advance",):
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

        return f"UNKNOWN_CMD:{cmd}"

    def _cmd_randint(self, args: str) -> str:
        """!randint a, b — random integer in [a, b]; !randint N — in [1, N]."""
        # Split at top-level commas only: a bound may itself be a call with
        # commas, e.g. `!randint 3, min(9,$L)` (0923) — a plain split(",")
        # would shred `min(9,10)` into "min(9" / "10)" and fail → "0".
        parts = [self._subst(p.strip()) for p in _split_top_level_args(args)]
        try:
            if len(parts) == 1:
                # Single-arg form: WIMS returns integer in [1, N]
                n = int(round(float(self._eval_arith(parts[0]))))
                return str(self.rng.randint(1, n))
            a = int(round(float(self._eval_arith(parts[0]))))
            b = int(round(float(self._eval_arith(parts[1]))))
            return str(self.rng.randint(a, b))
        except (ValueError, TypeError):
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

        Le découpage protège les crochets, comme `itemnum`/`fnd_item` dans
        WIMS : `[227,13],[18,120]` vaut deux items, pas quatre. La liste vient
        presque toujours d'une variable, si bien qu'un découpage naïf ne se
        voyait pas dans le `.def` mais coupait les couples de coordonnées de
        `unitecell` en morceaux (`13]`).
        """
        items = [x.strip() for x in self._split_wims_items(self._subst(args)) if x.strip()]
        return self.rng.choice(items) if items else ""

    def _cmd_nonempty(self, args: str) -> str:
        """!nonempty items/rows/lines list — remove empty entries."""
        m = re.match(r"(items?|rows?|lines?|words?)\s*(.*)", args, re.I | re.DOTALL)
        if not m:
            return self._subst(args)
        kind = m.group(1).lower()
        val = self._subst(m.group(2))
        # `lines` : séparateur newline (slib/stat/dataproc). `words` : espaces.
        if kind.startswith("line"):
            items = [x.strip() for x in val.split("\n") if x.strip()]
            return "\n".join(items)
        if kind.startswith("word"):
            return " ".join(w for w in val.split() if w)
        # Same separator logic as _cmd_shuffle: tab first, then smart comma.
        # Do NOT detect ";" — items may contain ";" inside HTML entities.
        if kind.startswith("row") or "\t" in val:
            sep = "\t"
            items = [x.strip() for x in val.split(sep) if x.strip()]
        else:
            sep = ","
            items = [x.strip() for x in re.split(r",(?![^(]*\))", val) if x.strip()]
        return sep.join(items)

    def _cmd_shuffle(self, args: str) -> str:
        """!shuffle list — return list items in random order."""
        val = self._subst(args.strip())
        if val.isdigit():
            items = [str(i) for i in range(1, int(val) + 1)]
            self.rng.shuffle(items)
            return ",".join(items)
        # Detect separator: tab first; otherwise smart comma split.
        # Do NOT use ";" as a separator: items may contain ";" inside HTML
        # entities like &#44; (comma) or &#40; (open paren).
        if "\t" in val:
            sep, items = "\t", val.split("\t")
        else:
            sep = ","
            items = re.split(r",(?![^(]*\))", val)
        items = [x.strip() for x in items if x.strip()]
        self.rng.shuffle(items)
        return sep.join(items)

    @staticmethod
    def _split_items(s: str) -> list[str]:
        """Découpe une liste WIMS en items — le découpage que `!item` indexe.

        La tabulation sépare des *lignes* : quand il y en a, c'est elle qui
        prime, sinon on découpe aux virgules de premier niveau. Mélanger les
        deux séparateurs fabriquerait un item vide à chaque `,<TAB>`, séquence
        banale dans les listes multi-lignes des `.def`.

        NB : WIMS, lui, ne découpe **qu'aux virgules** (`find_item_end` vaut
        `strparstr(p, ",")`), la tabulation n'étant qu'un caractère à élaguer.
        Aligner PAX là-dessus rend à `oefmolecule/lewis` les atomes de sa
        palette — sa liste de directions `0,r,…,rru,<TAB>ull,…` porte une
        tabulation purement cosmétique qui la réduisait à 2 items, faisant
        échouer toute recherche de position — **mais casse `moles.fr`,
        `moles.nl` et `mouvrel.fr`** : leur `val14` passe de `5` à un
        `rint(rint(…))` non évalué, et 30 `expected` se vident. Une autre
        liste y dépend du découpage par tabulation malgré ses virgules. À
        reprendre avec elles. Cf. TODO I.3.d.

        Les virgules protégées par `()`/`[]`/`{}` ne coupent pas : `!item 1 of
        [a,b],[c,d]` rend `[a,b]`, pas `[a` (sortie de slib/stat/effectif|freq).
        """
        if "\t" in s:
            return s.split("\t")
        return _split_top_level_commas(s)

    def _cmd_item(self, args: str) -> str:
        """!item I of list — 1-indexed item, or list of items.

        ``I`` may be a single index, a ``N to M`` range, or a comma-separated
        list of indices.
        """
        m = re.match(r"(.+?)\s+of\s*(.*)", args, re.DOTALL | re.I)
        if not m:
            return ""
        idx_s = self._subst(m.group(1).strip())
        data = self._subst(m.group(2).strip())

        split_items = self._split_items

        # Range: "2 to 5" → items 2 through 5. Bounds may be negative (WIMS
        # ``-1`` = last item), e.g. ``!item 2 to -1 of …`` = "from 2 to the end"
        # (simpquot keeps every accepted form after the displayed expression).
        # Les bornes peuvent être des expressions arithmétiques (`$(val9[1])+1`,
        # cf. moyenneB2) : on les évalue via _eval_arith, sinon la plage échoue
        # et la sous-liste ressort vide.
        range_m = re.match(r"(.+?)\s+to\s+(.+?)\s*$", idx_s)
        if range_m:
            try:
                a = int(round(float(self._eval_arith(range_m.group(1).strip()))))
                b = int(round(float(self._eval_arith(range_m.group(2).strip()))))
            except (ValueError, TypeError):
                range_m = None
        if range_m:
            items = split_items(data)
            n = len(items)
            if a < 0:
                a = n + a + 1
            if b < 0:
                b = n + b + 1
            a, b = max(1, a), min(n, b)
            if a > b:
                return ""
            return ",".join(it.strip() for it in items[a - 1 : b])

        # Comma-separated list of indices → pick each, join with commas
        if "," in idx_s:
            indices: list[int] = []
            for p in idx_s.split(","):
                try:
                    indices.append(int(round(float(self._eval_arith(p.strip())))))
                except (ValueError, TypeError):
                    continue
            items = split_items(data)
            res = []
            for idx in indices:
                if 1 <= idx <= len(items):
                    res.append(items[idx - 1].strip())
            return ",".join(res)

        # Single index. Negative = from the end (WIMS `-1` = last item), e.g.
        # `!item -1 of $slib_w` (slib/stat/effectif). Without this, negative
        # single indices returned empty and cascaded into `max(,)`-style leaks.
        try:
            idx = int(round(float(self._eval_arith(idx_s))))
            items = split_items(data)
            n = len(items)
            if idx < 0:
                idx = n + idx + 1
            if 1 <= idx <= n:
                return items[idx - 1].strip()
        except (ValueError, TypeError):
            pass
        return ""

    @staticmethod
    def _split_rows(data: str) -> list[str]:
        """Sépare les lignes d'une matrice WIMS.

        Priorité : \\n (enregistrements/slib) > \\; > \\t (makelist).
        Correspond à la logique de calc_rowof() dans calc.c.
        Le split par ``;`` protège les entités HTML (&#59;, &amp;, …).
        """
        if "\n" in data:
            return [r for r in data.split("\n") if r.strip()]
        if ";" in data:
            return [r.strip() for r in DefEngine._split_rows_by_semi(data) if r.strip()]
        return [r for r in data.split("\t") if r.strip()]

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
        idx_s = self._subst(m.group(1).strip())
        data = self._subst(m.group(2).strip())
        if "\n" in data:
            sep = "\n"
        elif ";" in data:
            sep = ";"
        else:
            sep = "\t"
        return self._blockof(
            data, lambda s: [r.strip() for r in self._split_rows(s)], sep, idx_s
        )

    def _cmd_replace(self, args: str) -> str:
        """!replace [internal/word] A by B in text."""
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
            # Try shortcut without mode prefix
            m = re.match(r"(.*?)\s+by\s+(.*?)\s+in\s*(.*)", args, re.I | re.DOTALL)
            if m:
                mode, old, new, text = "internal", m.group(1), m.group(2), m.group(3)
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
                    mode, old, new, text = (m.group(1) or "internal"), m.group(2), "", m.group(3)
                else:
                    return self._subst(args)
        
        # Motif vide → aucune occurrence à remplacer. WIMS ne fait rien ; Python
        # insérerait le remplacement entre *chaque* caractère (`"ab".replace("",
        # "X")` vaut `"XaXbX"`). `slib/function/tabsignes` écrit
        # `!replace internal $empty by \qquad \qquad in $slib_cel` pour espacer
        # les cellules vides, ce qui hachait toutes les autres : son marqueur
        # `reply1` ressortait en `\qquad r\qquad e\qquad p\qquad l\qquad y…`.
        if not old:
            return text
        if mode.lower() == "word":
            # Escape old for regex if using word mode
            return re.sub(rf"\b{re.escape(old)}\b", new, text)
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
        """!append item/line/word/semicolon X to list — append with appropriate separator."""
        # Also accepts 'word' (→ space), 'semicolon' (→ ;), 'colon' (→ :).
        m = re.match(r"(items?|lines?|words?|semicolons?|colons?)\s+(.*?)\s+to\s*(.*)",
                     args, re.I | re.DOTALL)
        if not m:
            return self._subst(args)
        kind_raw = m.group(1).lower()
        val = self._subst(m.group(2))
        target = self._subst((m.group(3) or "").strip())

        if kind_raw.startswith("line"):
            sep = "\n"
        elif kind_raw.startswith("word"):
            sep = " "
        elif kind_raw.startswith("semi"):
            sep = ";"
        elif kind_raw.startswith("colon"):
            sep = ":"
        else:
            # item: comma-separated, but switch to TAB when the list can't be
            # comma-joined unambiguously — i.e. the new item (or the list)
            # itself contains a comma/tab (e.g. cof appends JSXGraph
            # `board.create('line',[…],{…})` snippets, comma-laden, into one
            # list then reads them back with $(list[N])).
            sep = "\t" if ("\t" in target or "\t" in val or "," in val) else ","

        if not target:
            return val
        return f"{target}{sep}{val}"

    def _cmd_exec(self, args: str) -> str:
        """!exec maxima expr / !exec pari expr — call external CAS."""
        m = re.match(r"(maxima|pari)\s+(.*)", args, re.DOTALL | re.I)
        if not m:
            return ""
        engine = m.group(1).lower()
        expr = m.group(2).strip()
        if engine == "maxima":
            return _call_maxima(expr)
        if engine == "pari":
            return _call_pari(expr, session=self.pari_session)
        return ""

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
            # Split list by newline, tab, semicolon, or comma. Le newline est le
            # séparateur des listes produites par slib/stat/dataproc (données en
            # lignes) : sans lui, `!sum x for x in $slib_data` voyait un seul
            # item et renvoyait 0 (variance non pondérée fausse).
            if "\n" in list_raw:
                items = list_raw.split("\n")
            elif "\t" in list_raw:
                items = list_raw.split("\t")
            elif ";" in list_raw:
                items = list_raw.split(";")
            else:
                items = re.split(r",(?![^(]*\))", list_raw)
            items = [x.strip() for x in items if x.strip()]
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
        """!positionof item X in $list — 1-indexed position, 0 if absent."""
        m = re.match(r"item\s+(.*?)\s+in\s*(.*)", args, re.DOTALL | re.I)
        if not m:
            return "0"
        needle = self._subst(m.group(1).strip())
        haystack = self._subst(m.group(2).strip())
        # Même découpage que `!item`, et pour la même raison que `isitemof` :
        # les virgules protégées par des crochets ne séparent pas des items.
        # `slib/function/tabsignes` cherche la position d'un couple
        # `[ligne,colonne]` dans sa liste de couples, et un découpage naïf
        # renvoyait 0 — toutes ses cellules-réponses recevaient alors le même
        # numéro (`0 + rang - 1`).
        items = self._split_items(haystack)
        needle_norm = needle.replace(" ", "")
        for i, item in enumerate(items, 1):
            if item.strip().replace(" ", "") == needle_norm:
                return str(i)
        return "0"

    def _cmd_randrow(self, args: str) -> str:
        """!randrow $matrix — ligne aléatoire (séparateur auto)."""
        val = self._subst(args.strip())
        rows = self._split_rows(val)
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
        m = re.match(r"(items?|rows?|list)(?:\s+of)?\s+(.*)", rest, re.I | re.DOTALL)
        if m:
            kind, val = m.group(1).lower(), self._subst(m.group(2))
        else:
            kind, val = "items", self._subst(rest)

        sep = "\t" if kind.startswith("row") else ","
        items = [x.strip() for x in val.split(sep) if x.strip()]

        if numeric:
            def _num_key(s: str) -> float:
                try:
                    return float(self._eval_arith(s))
                except Exception:
                    return 0.0
            items.sort(key=_num_key, reverse=reverse)
        else:
            items.sort(reverse=reverse)

        return sep.join(items)

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
        return [x.strip() for x in self._split_items(value) if x.strip()]

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
        """!declosing text — remove outer parentheses/brackets/braces.

        Uniquement si toute la chaîne est enclose dans UNE paire équilibrée : le
        premier crochet ouvrant doit s'apparier au dernier caractère. Sinon
        `[a,b],[c,d]` verrait ses deux listes fusionnées à tort (dataproc)."""
        s = self._subst(args).strip()
        pairs = [("(", ")"), ("[", "]"), ("{", "}")]
        for open_, close_ in pairs:
            if s.startswith(open_) and s.endswith(close_):
                depth = 0
                for j, ch in enumerate(s):
                    if ch == open_:
                        depth += 1
                    elif ch == close_:
                        depth -= 1
                        if depth == 0:
                            # Le 1er ouvrant se ferme ailleurs qu'à la fin → pas
                            # d'enclosure unique (ex. `[a],[b]`).
                            if j != len(s) - 1:
                                return s
                            break
                return s[1:-1].strip()
        return s

    def _cmd_getopt(self, args: str) -> str:
        """!getopt key in list — extract value from key=value options."""
        m = re.match(r"(.*?)\s+in\s+(.*)", args, re.I | re.DOTALL)
        if not m: return ""
        key, text = m.group(1).strip().lower(), self._subst(m.group(2))
        # Options are split on whitespace/commas, but separators inside [...]
        # are protected so a bracketed value like `theme=[3024-night,3024-day]`
        # (or `instruction=[a :, b :]`) stays whole instead of being truncated.
        parts, cur, depth = [], [], 0
        for ch in text:
            if ch == "[":
                depth += 1
            elif ch == "]":
                depth = max(0, depth - 1)
            if depth == 0 and (ch.isspace() or ch == ","):
                if cur:
                    parts.append("".join(cur))
                    cur = []
            else:
                cur.append(ch)
        if cur:
            parts.append("".join(cur))
        for part in parts:
            if "=" in part:
                k, v = part.split("=", 1)
                if k.strip().lower() == key:
                    return v.strip()
        return ""

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
            n = len([x for x in re.split(r",|\t", text[a + 1 : b - 1]) if x.strip()])
            idx = self.rng.randrange(n) if n else 0
            def pick(content: str) -> str:
                items = [x.strip() for x in re.split(r",|\t", content) if x.strip()]
                return items[idx] if idx < len(items) else ""
        elif op == "randrow":
            def pick(content: str) -> str:
                rows = [r for r in self._split_rows(content) if r.strip()]
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
        idx_tokens = [t for t in re.split(r"[,\s]+", spec) if t]
        try:
            indices = [int(round(float(self._eval_arith(t)))) for t in idx_tokens]
        except (ValueError, TypeError):
            return ""
        if not indices:
            return ""

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
            rows = self._split_rows_by_semi(value)
        all_cols = [re.split(r",(?![^(]*\))", r) for r in rows]
        if all(len(c) == 1 for c in all_cols):
            all_cols = [r.split(";") for r in rows]

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
            items = [x.strip() for x in _split_top_level_commas(self._cmd_declosing(src))]
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
            allowed = [x.strip() for x in self._subst(m.group(2).strip()).split(",")]
            default_s = self._subst(m.group(3).strip()) if m.group(3) else None
            if self.ctx.get(var, "") in allowed:
                return
            self.ctx[var] = default_s if default_s is not None else (allowed[0] if allowed else "")

    def _cmd_default(self, args: str) -> None:
        """!default VAR=VALUE — set VAR to VALUE only if VAR is currently empty/unset."""
        m = re.match(r"(\w+)\s*=\s*(.*)", args, re.DOTALL)
        if not m:
            return
        var, value = m.group(1).strip(), self._subst(m.group(2).strip())
        if not self.ctx.get(var, "").strip():
            self.ctx[var] = value

    def _cmd_advance(self, args: str) -> None:
        """!advance VAR [step] — increment a counter variable."""
        parts = args.split()
        if not parts:
            return
        var = parts[0].strip()
        step = 1
        if len(parts) >= 2:
            try:
                step = int(self._eval_arith(self._subst(parts[1])))
            except (ValueError, TypeError):
                pass
        try:
            self.ctx[var] = str(int(self.ctx.get(var, "0")) + step)
        except (ValueError, TypeError):
            self.ctx[var] = str(step)

    def _cmd_reset(self, args: str) -> None:
        """!reset VAR [VAR2 …] — reset each space-separated variable to empty.

        WIMS accepts several names at once, e.g.
        ``!reset slib_theme1 slib_themecss1 slib_contrast_button1``.
        """
        for var in self._subst(args.strip()).split():
            self.ctx[var] = ""

    def _blockof(self, data: str, split_fn, sep: str, idx_s: str) -> str:
        """Generic N-of-LIST picker (port of _blockof in calc.c).

        split_fn(s) -> list[str]; sep is joined between multiple results.
        idx_s may be a single int, 'A to B' range, or comma-separated indices.
        Negative indices are Python-style from end (-1 = last).
        """
        parts = split_fn(data)
        n = len(parts)

        def resolve(i: int) -> int:
            if i < 0:
                return n + i + 1
            return i

        # Range: "2 to 5" or "2..5"
        range_m = re.match(r"(-?\d+)\s+to\s+(-?\d+)", idx_s) or \
                  re.match(r"(-?\d+)\.\.(-?\d+)", idx_s)
        if range_m:
            a = resolve(int(range_m.group(1)))
            b = resolve(int(range_m.group(2)))
            a = max(1, a); b = min(n, b)
            return sep.join(parts[i - 1] for i in range(a, b + 1))

        # Multiple indices
        raw_indices = [s.strip() for s in idx_s.split(",") if s.strip()]
        if len(raw_indices) > 1:
            res = []
            for s in raw_indices:
                try:
                    i = resolve(int(round(float(self._eval_arith(s)))))
                    if 1 <= i <= n:
                        res.append(parts[i - 1])
                except (ValueError, TypeError):
                    pass
            return sep.join(res)

        # Single index
        try:
            i = resolve(int(round(float(self._eval_arith(idx_s)))))
            if 1 <= i <= n:
                return parts[i - 1]
        except (ValueError, TypeError):
            pass
        return ""

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
        """Lit un fichier relatif au répertoire module ; None si absent."""
        if not self.def_path:
            return None
        module_dir = os.path.dirname(os.path.dirname(self.def_path))
        full = os.path.join(module_dir, filename)
        if not os.path.exists(full):
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
        # `gifs/…` désigne l'arbre partagé de WIMS, vendoré en
        # `ressources/wims-gifs/` (cf. `_find_wims_gifs_dir`).
        if path.startswith("gifs/"):
            rel = f"wims-gifs/{path[len('gifs/'):]}"
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
        """Découpe un fichier WIMS en enregistrements séparés par \\n:.

        Chaque enregistrement inclut son nom comme première ligne
        (sans le ':' initial), conformément au comportement de
        datafile_fnd_record() dans WIMS calc.c.
        """
        chunks = re.split(r"(?:^|\n):", text)
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
        Resolves DATAFILE relative to the module directory (two levels above def).
        """
        m = re.match(r"(.*?)\s+in\s+(\S+)", args, re.I | re.DOTALL)
        if not m:
            return ""
        key = self._subst(m.group(1)).strip()
        filename = self._subst(m.group(2)).strip()
        if not self.def_path or not key:
            return ""
        module_dir = os.path.dirname(os.path.dirname(self.def_path))
        full_path = os.path.join(module_dir, filename)
        if not os.path.exists(full_path):
            return ""
        try:
            try:
                text = open(full_path, encoding="utf-8").read()
            except UnicodeDecodeError:
                text = open(full_path, encoding="cp1252").read()
        except OSError:
            return ""
        # Search for "KEY:" at the start of a line (case-insensitive)
        needle = key.lower() + ":"
        for line in text.splitlines():
            if line.lower().startswith(needle):
                return line[len(needle):].strip()
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
        return out

    def _split_correspond_column(self, row: str) -> list[str]:
        """Split one correspond column into items, robust to HTML-element items.

        ``_split_list_items`` over-splits a column of complete HTML elements
        (assgrhyper's 4 ``<img>`` hyperbola graphs): the multi-line ``<img>``
        markup carries tabs (source newlines) that collide with the tab used as
        the item separator. Such elements end in ``>`` and the next begins with
        ``<``, so a tab that *follows* a closing ``>`` is the only real boundary
        (attribute tabs follow ``"`` or spaces). Fall back to the generic split
        when the column isn't a clean list of elements (CORvect3 coords, text).
        """
        if "<" in row and ">" in row:
            elems = [e.strip() for e in re.split(r"(?<=>)\s*\t\s*", row) if e.strip()]
            if len(elems) >= 2 and all(e.startswith("<") for e in elems):
                return elems
        return [c for c in self._split_list_items(row) if c.strip()]

    def _prep_correspond_item(self, raw: str) -> str:
        """Normalise one correspond cell for display: close WIMS inline math and,
        for a flydraw graph, collapse the multi-line ``<img>`` whitespace and
        inline its SVG (so it travels in the payload, like the rest of the
        rendered statement — the ``/api/render/svg`` cache is in-memory only)."""
        s = _close_inline_math(self._subst(raw.strip()), self.lang)
        if "/api/render/svg/" in s:
            from ..flydraw import inline_svg_imgs  # noqa: PLC0415
            s = re.sub(r"\s+", " ", s)            # flatten the multi-line markup
            s = re.sub(r'src="\s+', 'src="', s)   # trim the URL's leading space
            s = inline_svg_imgs(s)
        return s

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
        return [c.strip() for c in after.split(",") if c.strip()]

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
        rows = [r for r in self._split_rows_by_semi(raw) if r.strip()]
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

    def _render_embed(self, args: str) -> str:
        """Render an !read oef/embed.phtml marker as an input span."""
        args = self._subst(args).strip()
        # Parse: "r1,10" or "reply1,$val10" or "r1" etc.
        parts = [p.strip() for p in args.split(",")]
        ref = parts[0] if parts else "reply1"
        size_str = parts[1] if len(parts) > 1 else "10"

        # Some .def files write `reply 1,30` (space between word and index)
        # instead of `reply1,30`; collapse internal whitespace so the ref
        # matches the answer's input_name.
        ref = re.sub(r"\s+", "", ref)

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
            try:
                # Suffix might still contain a variable reference like $m_qq
                suffix_val = self._subst(suffix)
                ref = f"reply{int(float(suffix_val))}"
            except (ValueError, TypeError, OverflowError):
                ref = f"reply{suffix}"

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
                # A 2nd arg that is a *size* (ecrdecimal `reply \h,\s`) or any
                # reply whose choices carry their own text (vocabaff3) must stay
                # a plain deferred radio — so only treat the bare-position case as
                # inline when the choice list is exactly the sequence 1..N.
                pos = parts[1].strip() if len(parts) >= 2 else ""
                content = ",".join(parts[2:]).strip() if len(parts) > 2 else ""
                inline = bool(pos) and bool(content)
                if pos and not content:
                    choices = self._inline_radio_choices(n)
                    inline = bool(choices) and pos in choices and choices == [
                        str(i) for i in range(1, len(choices) + 1)
                    ]
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
            elif reply_type == "mark":
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
                # Format: "pos;choice1,choice2,..." or "pos;choice1;choice2;..."
                if ";" in good_raw:
                    _pos_part, _, choices_part = good_raw.partition(";")
                else:
                    choices_part = good_raw
                # Choices are separated by `,` OR `;` (the `;` from the
                # append-tab + `!translate \t→;` idiom when a choice holds a
                # comma, e.g. "2,5 × 10^19" — brevet01). Split on both at bracket
                # depth 0, protecting `\(…)` and HTML entities (`&#44;`).
                choices = [c.strip() for c in self._split_wims_items(choices_part) if c.strip()]

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
                if col is not None and choices and 1 <= col <= len(choices):
                    return _mark_span(col)
                if choices:
                    return " ".join(_mark_span(i + 1) for i in range(len(choices)))
                return _mark_span(col or 1)
            elif reply_type == "checkbox":
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
                if idx is not None and labels and 1 <= idx <= len(labels):
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
                rows = self._split_rows_by_semi(good_raw)
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
                rows = self._split_rows_by_semi(good_raw)
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
            elif reply_type == "coord":
                # `type=coord`: the field is a clickable repère image (WIMS'
                # `<input type=image>`). `replygood{n}` = "<image_url>;<zone>"
                # (rows split on ';'); the first row is the background to click.
                good = self._subst(self.ctx.get(f"replygood{n}", "")).strip()
                img = good.split(";", 1)[0].strip()
                if img:
                    return f'<span class="oef-coord" name="reply{n}" data-img="{img}"></span>'
                return ""

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
        textarea_m = re.match(r"^(\d+)\s*[xX]\s*(\d+)$", size_raw)
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
            span = (
                f'<span class="oef-input" name="{ref}" '
                f'data-size="{size}"{extra}></span>'
            )

        # WIMS' fset.input frames the field in literal braces to signal that a
        # *set* is expected (e.g. T1116: the solution set of f(x)=k). Mirror it.
        if reply_type == "fset":
            return f'<span class="oef-set-brace">{{</span>{span}<span class="oef-set-brace">}}</span>'
        return span

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
    _CHOICE_EXPECTED_TYPES = frozenset({"radio", "menu", "mark", "clickfill"})

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
        compute_answer = self._subst(str(df.meta.get("computeanswer", ""))).strip().lower()

        # When replycnt=0 but choicecnt>0, synthesise implicit radio replies from
        # choice_meta (WIMS creates an implicit reply slot in this case).
        if not df.reply_meta and df.choice_meta:
            for cm in df.choice_meta:
                n = cm["n"]
                correct = self._subst(cm.get("good", ""))
                wrong_raw = self._subst(cm.get("bad", ""))
                wrong = [w.strip() for w in wrong_raw.split(",") if w.strip()]
                seen_set: set[str] = set()
                choices: list[str] = []
                for c in [correct] + wrong:
                    if c not in seen_set:
                        seen_set.add(c)
                        choices.append(c)
                jnsp = "Je ne sais pas"
                rng = random.Random(f"{self.seed}_{n}")
                rng.shuffle(choices)
                # WIMS always presents "I don't know" as the last option, so
                # append it *after* shuffling the real choices.
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
                answers.append(
                    AnswerDef(
                        label="",
                        expected=_close_inline_math(correct, self.lang),
                        answer_type="radio",
                        options={"choices": choices},
                        weight=1.0,
                        input_name=f"reply{n}",
                        logical_name=f"reply{n}",
                    )
                )
            return answers

        for rm in df.reply_meta:
            n = rm["n"]
            ans_type = self._subst(rm.get("type", "numeric")).strip()
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
            if (
                self.ctx.get("_commutesom_anyorder")
                and ans_type.lower() in ("litexp", "algexp", "formal")
                and not re.search(r"\b(polexpand|expand|polfactor)\b", option)
            ):
                option = (option + " expand").strip()
            options: dict = {"option": option} if option else {}
            if is_dragfill:
                options["single_use"] = True
            # Précision WIMS de l'exercice → checkers numériques (numeric,
            # numexp, units, fset). Jusqu'ici figée à 1e-4 côté checker ; on
            # transmet désormais `\precision{M}` (cf. _wims_precision).
            options["precision"] = wims_prec
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
                elif ans_type in ("clickfill", "checkbox", "mark"):
                    # Widget DISPLAY + analyze CHECK: keep the widget type so it
                    # renders (draggable labels / boxes) — the pool is in `rest`
                    # and parsed by the widget branch below. The student's value
                    # is fed to val<N> in :test (see run_feedback), so keep
                    # `analyze_var`. `good_raw` keeps "?analyze N;<pool>" which the
                    # clickfill branch splits into correct ("?analyze N") + pool.
                    # ineqinterv1: drag `[`/`]` brackets into the interval slots.
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
                expected = good_raw.split(";", 1)[0].strip() if ";" in good_raw else good_raw.strip()

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

            elif ans_type == "checkbox":
                # Format: "correct_indices;all_indices" (e.g. "1,3;1,2,3,4").
                # The student's reply is the set of checked option indices;
                # expected is the correct subset, compared order-insensitively
                # (check_set). The checkboxes themselves are emitted inline by
                # _render_embed; no choices list is needed here.
                correct_part = good_raw.split(";", 1)[0] if ";" in good_raw else good_raw
                expected = ",".join(
                    c.strip() for c in correct_part.split(",") if c.strip()
                )

            elif ans_type == "mark":
                # Format: "correct_pos;choice1,choice2,..." (WIMS mark / click-in-table)
                # The student's reply is the 1-based column they clicked.
                # expected = that column index as a string.
                if ";" in good_raw:
                    pos_str, _, choices_str = good_raw.partition(";")
                    expected = pos_str.strip()
                    # Choices split on `,` or `;` (the `;` from the append-tab +
                    # translate idiom for comma-bearing choices — brevet01).
                    choices = [
                        c.strip()
                        for c in self._split_wims_items(choices_str)
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
                    rows = self._split_rows_by_semi(good_raw)
                    if len(rows) == 2:
                        rights = [
                            self._subst(c.strip())
                            for c in self._split_list_items(rows[1]) if c.strip()
                        ]
                        expected = ",".join(rights)

            elif ans_type == "clickfill":
                # Format: "correct;pool". Split entity-safe — the parts hold
                # HTML entities (&#91; [ , &#93; ] , &#59; ;) whose trailing ";"
                # must not be mistaken for the correct;pool separator. WIMS also
                # accepts "|" as the separator (anstype/fill.inc:15 translates it
                # to a newline/row break), so normalise "|" → ";" first.
                good_raw = good_raw.replace("|", ";")
                rows = self._split_rows_by_semi(good_raw)
                if len(rows) >= 2:
                    correct_str, pool_str = rows[0], ";".join(rows[1:])
                else:
                    correct_str, pool_str = good_raw, ""
                correct_items = [
                    _close_inline_math(c.strip(), self.lang) for c in correct_str.split(",") if c.strip()
                ]
                pool_items = [
                    _close_inline_math(p.strip(), self.lang) for p in pool_str.split(",") if p.strip()
                ]
                rng = random.Random(f"{self.seed}_{n}")
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
                    # `dragfill.after` : mélange tant que la palette n'excède ni
                    # le nombre de cases ni 12 étiquettes, tri alphabétique
                    # au-delà (une longue liste reste ainsi parcourable).
                    if len(choices) <= max(len(correct_items), 12):
                        rng.shuffle(choices)
                    else:
                        choices.sort()
                    options["choices"] = choices
                    options["slots"] = len(correct_items)
                    expected = ",".join(correct_items)
                elif "analyze_var" in options:
                    # Analyze-based clickfill (ineqinterv1): the "correct" part is
                    # "?analyze N" — a checking ref, NOT a draggable label. The
                    # palette is the pool only; scoring is via the :test section.
                    seen0: set[str] = set()
                    choices = [c for c in pool_items if not (c in seen0 or seen0.add(c))]  # type: ignore[func-returns-value]
                    rng.shuffle(choices)
                    options["choices"] = choices
                    expected = self._resolve_analyze_expected(options["analyze_var"], df) or ""
                elif len(correct_items) > 1:
                    # Multi-slot drag-compose (e.g. repgraphint): the student
                    # arranges labels from the pool into an ordered sequence.
                    # expected = the ordered sequence (comma-joined); choices =
                    # the pool (it already contains every needed label).
                    seen: set[str] = set()
                    choices = [c for c in pool_items if not (c in seen or seen.add(c))]  # type: ignore[func-returns-value]
                    rng.shuffle(choices)
                    options["choices"] = choices
                    options["slots"] = len(correct_items)
                    expected = ",".join(correct_items)
                elif correct_items:
                    # Single-slot: pick the one correct label among distractors.
                    correct = correct_items[0]
                    choices = [correct] + pool_items
                    seen2: set[str] = set()
                    choices = [c for c in choices if not (c in seen2 or seen2.add(c))]  # type: ignore[func-returns-value]
                    rng.shuffle(choices)
                    expected = correct
                    options["choices"] = choices

            # Keep an exact non-integer rational answer as a fraction so the
            # auto-fill inserts e.g. `2/3` rather than the lossy decimal
            # `0.666…` (replygood `$[$val12]` floats it via `$[…]`). Scoped to
            # numeric answers: text rendering still prints `$[2/3]` as a decimal
            # like WIMS. The numeric checker accepts the fraction either way.
            if ans_type in ("numeric", "numexp") and "analyze_var" not in options:
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
                # The pixel↔repère transform (from slib/draw/repere) lets the
                # feedback report the click in repère units instead of pixels.
                xform = self.ctx.get("_repere_transform")
                if xform:
                    options["transform"] = xform

            # Champ non noté ni obligatoire (« ungraded ») :
            #  - brouillon `type=draft` (l'élève y pose son calcul) ;
            #  - champ `analyze` marqué `default=vide` sans test réel (ex.
            #    oefcalcullit dev2fact : reply2 matrix→analyze, `:test` vide —
            #    le forcer dans run_analyze fausserait toute la notation).
            # Les vraies réponses (fset, numeric…) avec `default=vide` restent
            # notées : `default=vide` y signifie « vide = ensemble ∅ » (cf.
            # oefresolalg synth*), géré par la substitution WIMS des checkers.
            if is_draft or (
                ans_type.lower() == "analyze"
                and "default=vide" in option.lower()
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

