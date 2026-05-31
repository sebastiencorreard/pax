"""
Moteur OEF principal.
Charge un fichier .oef, l'évalue avec un seed, et retourne un ExerciseRender.
"""

import os
import random
import re
from dataclasses import dataclass, field

from .parser import parse, OEFNode
from .evaluator import OEFEvaluator


@dataclass
class AnswerDef:
    label: str
    expected: str
    answer_type: str  # numeric, algexp, text, radio, clickfill, ...
    options: dict = field(default_factory=dict)
    weight: float = 1.0
    input_name: str = ""  # reply1, reply2, ...
    logical_name: str = ""  # nom de variable OEF (rsymb1, rx1…) utilisé dans \condition


@dataclass
class ExerciseRender:
    title: str
    lang: str
    statement_html: str  # rendu brut, conservé pour tests/scripts/snapshots
    statement_segments: list[dict]  # [{type:"html"|"input"|"slot", ...}] pour l'API
    answers: list[AnswerDef]
    hint_html: str
    solution_html: str
    seed: int
    meta: dict
    condition: dict | None = None
    ev_ctx: dict = field(default_factory=dict)
    check_sections: dict | None = None
    # Dynamic steps info
    exercise_type: str = "standard"
    is_dynsteps: bool = False
    current_step: int | None = None
    total_steps: int | None = None
    type_meta: dict = field(default_factory=dict)
    css: str | None = None


def find_def_path(oef_path: str) -> str | None:
    """Return the compiled .def path for a given .oef path, or None if absent.

    Checks two layouts used in the PAX resource tree:
      1. Same directory: foo/exercise.oef → foo/exercise.def
      2. Sibling def/ dir: foo/src/exercise.oef → foo/def/exercise.def
    """
    base = os.path.splitext(oef_path)[0]
    candidate1 = base + ".def"
    if os.path.isfile(candidate1):
        return candidate1

    src_dir = os.path.dirname(oef_path)
    parent_dir = os.path.dirname(src_dir)
    stem = os.path.basename(base)
    candidate2 = os.path.join(parent_dir, "def", stem + ".def")
    if os.path.isfile(candidate2):
        return candidate2

    return None


def load_and_render(oef_path: str, seed: int | None = None, m_step: int | None = None) -> ExerciseRender:
    """
    Point d'entrée principal.
    Essaie d'abord le pipeline .def compilé ; retombe sur le parser OEF si absent.
    Les résultats sont mis en cache Redis (TTL 10 min) pour éviter le double
    rendu render→check qui serait sinon systématique.
    """
    if not os.path.exists(oef_path):
        raise FileNotFoundError(f"Fichier OEF introuvable : {oef_path}")

    def_path = find_def_path(oef_path)
    effective_path = def_path or oef_path

    # Le seed doit être fixé avant la mise en cache pour que la clé soit stable.
    # On l'attribue ici si absent ; le moteur .def l'utilisera tel quel.
    if seed is None:
        seed = random.randint(0, 2**31)

    from . import render_cache
    key = render_cache.cache_key(effective_path, seed, m_step)
    cached = render_cache.get(key)
    if cached is not None:
        return cached

    if def_path:
        from .def_engine import load_and_render as _def_render

        rendered = _def_render(def_path, seed=seed, m_step=m_step)
        render_cache.set(key, rendered)
        return rendered

    # Fallback: pipeline OEF original

    # Les fichiers OEF sont historiquement en ISO-8859-1 (latin-1)
    try:
        with open(oef_path, encoding="utf-8") as f:
            source = f.read()
    except UnicodeDecodeError:
        with open(oef_path, encoding="cp1252") as f:
            source = f.read()

    directives_ast = parse(source)
    evaluator = OEFEvaluator(seed=seed)
    evaluator.evaluate_ast(directives_ast)

    answers = _extract_answers(directives_ast, evaluator)
    condition = _extract_condition(directives_ast, evaluator)
    statement_html = _extract_statement(directives_ast, evaluator)

    # For clickfill answers: replace oef-input spans with cf-slot markers so
    # the segmenter and frontend treat them as drop targets, not text fields.
    for ans in answers:
        if ans.answer_type != "clickfill":
            continue
        n_match = re.match(r"^reply(\d+)$", ans.input_name)
        refs = [ans.input_name] + ([f"r{n_match.group(1)}"] if n_match else [])
        for ref in refs:
            statement_html = re.sub(
                r'<span\s+class="oef-input"\s+name="' + re.escape(ref) + r'"[^>]*></span>',
                f'<cf-slot name="{ans.input_name}"></cf-slot>',
                statement_html,
            )

    segments = _segment_statement(statement_html)

    # Filtre les réponses dont le champ n'apparaît pas dans le statement rendu,
    # mais seulement si le statement contient des widgets (input/slot).
    # Pour les \choice (radio), il n'y a pas de widget : on garde tout.
    widget_names = {s["name"] for s in segments if s["type"] in ("input", "slot")}
    if widget_names:
        answers = [a for a in answers if a.input_name.replace(" ", "") in widget_names]

    rendered = ExerciseRender(
        title=evaluator.meta.get("title", ""),
        lang=evaluator.meta.get("language", "fr"),
        statement_html=statement_html,
        statement_segments=segments,
        answers=answers,
        hint_html=_extract_block(directives_ast, "hint", evaluator),
        solution_html=_extract_block(directives_ast, "solution", evaluator),
        seed=seed,
        meta={
            k: v for k, v in evaluator.meta.items() if k not in ("title", "language")
        },
        condition=condition,
        ev_ctx=dict(evaluator.ctx),  # contexte complet pour évaluation de \condition
        exercise_type="standard",
        type_meta={},
    )
    render_cache.set(key, rendered)
    return rendered


# Reconnaît les trois types de widgets dans le HTML rendu :
#   groupe 1 — slot clickfill : <cf-slot name="…"></cf-slot>
#   groupes 2-3 — champ texte : <span class="oef-input" name="…" data-size="…"></span>
#   groupes 4-5 — menu déroulant : <span class="oef-menu" name="…" data-label="…"></span>
_SEGMENT_PATTERN = re.compile(
    # cf-slot may carry extra attrs (data-index/data-w for multi-slot
    # clickfill); keep group 1 = name and swallow the rest non-capturingly
    # so the later group numbers (oef-input/menu/correspond) don't shift.
    r'<cf-slot name="([^"]+)"[^>]*></cf-slot>'
    r'|<span\s+class="oef-input"\s+name="([^"]+)"\s+data-size="([^"]*)"></span>'
    r'|<span\s+class="oef-menu"\s+name="([^"]+)"\s+data-label="([^"]*)"></span>'
    r'|<span\s+class="oef-correspond"\s+name="([^"]+)"\s+data-config="([^"]*)"></span>'
    # group 8: a JSXGraph board container (kept last so earlier groups don't shift)
    r'|<div class="pax-jsxgraph"[^>]*data-jsxgraph="([^"]*)"[^>]*></div>'
    # group 9: a CodeMirror editor container. Kept before the generic <div>
    # group below so this self-contained marker isn't split into open/close
    # layout groups (same reasoning as the jsxgraph div above).
    r'|<div class="pax-codeeditor"[^>]*data-codeeditor="([^"]*)"[^>]*></div>'
    # groups 10/11: <div>/<ul>/<ol>/<li> open/close → layout-group segments, so a
    # CSS-flex container (e.g. cof's .container, or fcou's <ul class="inline">
    # row of JSXGraph boards) can wrap its child segments side by side. Tried
    # after group 9 so the jsxgraph/codeeditor divs aren't split.
    # Case-insensitive: OEF HTML mixes case (e.g. Hauteurdunarbr's <uL>).
    r'|((?i:<(?:div|ul|ol|li)\b[^>]*>))'
    r'|((?i:</(?:div|ul|ol|li)\s*>))'
    # groups 12/13/14: an inline radio choice (couf) — name, value, content.
    r'|<span class="oef-radio-inline" name="([^"]+)" data-value="([^"]*)" data-content="([^"]*)"></span>'
)
# Only <p> is flattened to <br> (the front-end renders segments flat). <div>,
# <ul>, <ol> and <li> are NOT flattened — they become layout-group segments
# (see groups 9/10 above) so their class-based styling (flex containers, e.g.
# fcou's `.inline` row of boards) is preserved. Missing </li> tags are
# back-filled by _balance_list_items before grouping.
_BLOCK_OPEN = re.compile(r"<p(?=[\s>])[^>]*>", re.I)
# </p> → <br>.
_BLOCK_CLOSE = re.compile(r"</p\s*>", re.I)

# Matches list structure tags so _balance_list_items can re-balance them.
_LIST_TAG = re.compile(r"<(/?)(ul|ol|li)\b[^>]*>", re.I)
# Séquences de plusieurs <br> consécutifs (avec espaces) → un seul <br>.
_BR_RUN = re.compile(r"(?:\s*<br\s*/?>\s*){2,}", re.I)
# <br> en tête de chaîne (artefacts de la conversion div/p → br).
_BR_LEADING = re.compile(r"^(?:\s*<br\s*/?>\s*)+", re.I)


_TABLE_OPEN = re.compile(r"<table\b[^>]*>", re.IGNORECASE)
_TABLE_CLOSE = re.compile(r"</table\s*>", re.IGNORECASE)


def _table_ranges(html: str) -> list[tuple[int, int]]:
    """Find (start, end) byte ranges of top-level <table>…</table> blocks.

    Within these ranges, inline widgets must NOT split the HTML into separate
    segments — otherwise the surrounding table structure breaks. Instead the
    backend rewrites such widgets to native <input> tags that the browser
    renders inline (the frontend binds them via event delegation).
    """
    opens = [m.start() for m in _TABLE_OPEN.finditer(html)]
    closes = [m.end() for m in _TABLE_CLOSE.finditer(html)]
    ranges: list[tuple[int, int]] = []
    depth = 0
    start = -1
    o = c = 0
    while o < len(opens) or c < len(closes):
        next_open = opens[o] if o < len(opens) else float("inf")
        next_close = closes[c] if c < len(closes) else float("inf")
        if next_open < next_close:
            if depth == 0:
                start = next_open
            depth += 1
            o += 1
        else:
            depth = max(0, depth - 1)
            if depth == 0 and start != -1:
                ranges.append((start, next_close))
                start = -1
            c += 1
    return ranges


def _inline_input_html(name: str, size_raw: str) -> str:
    """Render a widget as a native <input> for inline placement inside a table."""
    name = re.sub(r"^r(\d+)$", r"reply\1", name)  # rN → replyN
    textarea_m = re.match(r"^(\d+)\s*[xX]\s*(\d+)$", size_raw)
    if textarea_m:
        rows, cols = int(textarea_m.group(1)), int(textarea_m.group(2))
        return (
            f'<textarea class="oef-input" name="{name}" '
            f'rows="{rows}" cols="{cols}"></textarea>'
        )
    try:
        size = int(size_raw)
    except (TypeError, ValueError):
        size = 10
    width = f"{max(size + 2, 6)}ch"
    return (
        f'<input type="text" class="oef-input" name="{name}" '
        f'autocomplete="off" style="width:{width};min-width:6ch" />'
    )


def _balance_list_items(html: str) -> str:
    """Back-fill missing </li> (and dangling list closers) so the ul/ol/li
    structure is well balanced before it is turned into layout-group segments.

    OEF/WIMS HTML routinely omits </li> — e.g. ``<ul><li>a<li>b</ul>`` — relying
    on the next <li> or the </ul> to implicitly close the item. Since the front
    end builds its group tree from the raw open/close markers, an unclosed <li>
    would wrongly nest the following sibling items inside it and swallow whatever
    text comes after the list. We close each <li> at the next sibling <li> or the
    enclosing </ul>/</ol>, and close anything still open at end of input.
    """
    out: list[str] = []
    pos = 0
    # Stack of open list contexts. Each entry: [tag, li_open]; tag is "ul"/"ol",
    # or None for a stray <li> opened outside any list.
    stack: list[list] = []
    for m in _LIST_TAG.finditer(html):
        out.append(html[pos:m.start()])
        pos = m.end()
        closing = m.group(1) == "/"
        tag = m.group(2).lower()
        if tag in ("ul", "ol"):
            if closing:
                # Pop any stray <li>s, then this list — closing open items.
                while stack and stack[-1][0] is None:
                    if stack.pop()[1]:
                        out.append("</li>")
                if stack:
                    if stack[-1][1]:
                        out.append("</li>")
                    stack.pop()
                out.append(m.group(0))
            else:
                stack.append([tag, False])
                out.append(m.group(0))
        elif closing:  # </li>
            if stack and stack[-1][1]:
                stack[-1][1] = False
            out.append(m.group(0))
        else:  # <li>
            if stack and stack[-1][1]:
                out.append("</li>")  # close the previous sibling item
            if stack and stack[-1][0] is not None:
                stack[-1][1] = True
            else:
                stack.append([None, True])  # stray <li>, no enclosing list
            out.append(m.group(0))
    out.append(html[pos:])
    # Close whatever is still open at end of input (lists/items lacking a tag).
    tail: list[str] = []
    while stack:
        tag, li_open = stack.pop()
        if li_open:
            tail.append("</li>")
        if tag is not None:
            tail.append(f"</{tag}>")
    return "".join(out) + "".join(tail)


def _strip_group_whitespace(segments: list[dict]) -> list[dict]:
    """Drop whitespace-only html segments sitting against a layout-group border.

    Source lists carry whitespace (tabs/newlines) between </li> and the next
    <li>, and between <ul> and its first <li>. Left in place these become empty
    flex items inside the group and double the gap between boards. Whitespace
    between two inline widgets is kept (it may be a meaningful space) — only
    whitespace adjacent to a group-open/group-close marker is removed.
    """
    def _is_group(seg: dict | None) -> bool:
        return seg is not None and seg.get("type") in ("group-open", "group-close")

    out: list[dict] = []
    n = len(segments)
    for i, seg in enumerate(segments):
        if seg.get("type") == "html" and not seg.get("content", "").strip():
            prev = segments[i - 1] if i > 0 else None
            nxt = segments[i + 1] if i + 1 < n else None
            if _is_group(prev) or _is_group(nxt):
                continue
        out.append(seg)
    return out


def _segment_statement(html: str) -> list[dict]:
    """
    Découpe le HTML rendu en segments typés consommables tels quels par le front :
      - {type: "html", content: "..."}
      - {type: "input", name: "reply1", size: 10}
      - {type: "slot",  name: "..."}
      - {type: "menu",  name: "reply1", label: "Choix"}
    Aplatit <p> en <br> ; <div>/<ul>/<ol>/<li> sont préservés en groupes de
    mise en page (segments group-open/group-close). Résout l'alias rN ↔ replyN.

    Widgets situés à l'intérieur d'une <table> ne déclenchent pas de split :
    leur span <span class="oef-input"> est réécrit en <input> natif et reste
    inline dans le segment html, ce qui préserve la mise en page (utilisé par
    ex. pour les fractions superposées de l'exercice de Thalès csgb Q200).
    """
    html = _BLOCK_OPEN.sub("<br>", html)
    html = _BLOCK_CLOSE.sub("<br>", html)
    html = _balance_list_items(html)
    html = _BR_RUN.sub("<br>", html)
    html = _BR_LEADING.sub("", html)

    tables = _table_ranges(html)

    def in_table(pos: int) -> bool:
        return any(s <= pos < e for s, e in tables)

    # First pass: rewrite oef-input spans inside tables to native <input> tags.
    # Done right-to-left so earlier offsets stay valid.
    matches_in_tables = [
        m for m in _SEGMENT_PATTERN.finditer(html)
        if in_table(m.start()) and m.group(2) is not None
    ]
    for m in reversed(matches_in_tables):
        name = m.group(2).strip()
        size_raw = (m.group(3) or "").strip()
        replacement = _inline_input_html(name, size_raw)
        html = html[: m.start()] + replacement + html[m.end():]
    # Re-compute table ranges since byte offsets shifted.
    tables = _table_ranges(html)

    segments: list[dict] = []
    last = 0
    in_sup = 0
    for m in _SEGMENT_PATTERN.finditer(html):
        # Widgets inside a table were already rewritten above, so nothing left
        # to match there — but skip defensively in case future widgets land here.
        if in_table(m.start()):
            continue

        if m.start() > last:
            content = html[last : m.start()]
            segments.append({"type": "html", "content": content})
            in_sup += content.lower().count("<sup") - content.lower().count("</sup")

        is_sup = in_sup > 0

        if m.group(1) is not None:
            # Slot clickfill — carry the slot index/width when present so the
            # frontend can render an ordered row of drop targets for one reply.
            slot = {"type": "slot", "name": m.group(1).strip(), "is_sup": is_sup}
            idx_m = re.search(r'data-index="(\d+)"', m.group(0))
            if idx_m:
                slot["index"] = int(idx_m.group(1))
            w_m = re.search(r'data-w="(\d+)"', m.group(0))
            if w_m:
                slot["width"] = int(w_m.group(1))
            segments.append(slot)
        elif m.group(4) is not None:
            # Menu déroulant
            name = m.group(4).strip()
            alias = re.match(r"^r(\d+)$", name)
            if alias:
                name = f"reply{alias.group(1)}"
            label = m.group(5).strip()
            segments.append({"type": "menu", "name": name, "label": label, "is_sup": is_sup})
        elif m.group(6) is not None:
            # Widget correspond — config est du JSON HTML-escaped
            import html as _html  # noqa: PLC0415
            import json as _json  # noqa: PLC0415
            name = m.group(6).strip()
            alias = re.match(r"^r(\d+)$", name)
            if alias:
                name = f"reply{alias.group(1)}"
            try:
                config = _json.loads(_html.unescape(m.group(7)))
            except (ValueError, TypeError):
                config = {}
            segments.append({
                "type": "correspond", "name": name, "config": config, "is_sup": is_sup,
            })
        elif m.group(8) is not None:
            # JSXGraph board — the init JS becomes segment *data* (not HTML),
            # so the KaTeX pass never touches its \(…\) labels.
            import html as _html  # noqa: PLC0415
            tag = m.group(0)
            board_id = (re.search(r'id="([^"]+)"', tag) or [None, "jsxbox"])[1]
            seg = {
                "type": "jsxgraph",
                "name": board_id,
                "js": _html.unescape(m.group(8)),
                "is_sup": is_sup,
            }
            for attr, key in (("data-w", "width"), ("data-h", "height"),
                              ("data-maxw", "maxw"), ("data-minw", "minw")):
                am = re.search(rf'{attr}="(\d+)"', tag)
                if am:
                    seg[key] = int(am.group(1))
            # `data-reply` (jsxgraph *answer* boards): binds the captured
            # coordinates to this reply field on the frontend.
            rm = re.search(r'data-reply="([^"]+)"', tag)
            if rm:
                seg["reply"] = rm.group(1)
            segments.append(seg)
        elif m.group(9) is not None:
            # CodeMirror editor — its config (code, mode, themes, …) becomes
            # segment *data* (JSON), rendered client-side by the Codemirror
            # component (inline <script>s can't run via the front-end v-html).
            import html as _html  # noqa: PLC0415
            import json as _json  # noqa: PLC0415
            try:
                config = _json.loads(_html.unescape(m.group(9)))
            except (ValueError, TypeError):
                config = {}
            segments.append({"type": "codeeditor", "config": config, "is_sup": is_sup})
        elif m.group(10) is not None:
            # <div …> → layout group open. Carry the class so the frontend can
            # apply the exercise CSS (flex containers etc.).
            cls_m = re.search(r'class="([^"]*)"', m.group(10))
            segments.append({"type": "group-open", "class": cls_m.group(1) if cls_m else ""})
        elif m.group(11) is not None:
            segments.append({"type": "group-close"})
        elif m.group(12) is not None:
            # Inline radio choice (couf): name, value (position), content.
            import html as _html  # noqa: PLC0415
            name = m.group(12).strip()
            alias = re.match(r"^r(\d+)$", name)
            if alias:
                name = f"reply{alias.group(1)}"
            segments.append({
                "type": "radio-inline",
                "name": name,
                "value": m.group(13).strip(),
                "content": _html.unescape(m.group(14)),
                "is_sup": is_sup,
            })
        else:
            # Input texte ou textarea
            name = m.group(2).strip()
            # Les fichiers OEF utilisent souvent l'alias court "rN" au lieu de "replyN".
            alias = re.match(r"^r(\d+)$", name)
            if alias:
                name = f"reply{alias.group(1)}"
            size_raw = (m.group(3) or "").strip()
            textarea_m = re.match(r"^(\d+)\s*[xX]\s*(\d+)$", size_raw)
            if textarea_m:
                segments.append({
                    "type": "textarea",
                    "name": name,
                    "rows": int(textarea_m.group(1)),
                    "cols": int(textarea_m.group(2)),
                    "is_sup": is_sup
                })
            else:
                try:
                    size = int(size_raw)
                except (TypeError, ValueError):
                    size = 10
                segments.append({"type": "input", "name": name, "size": size, "is_sup": is_sup})
        last = m.end()
    if last < len(html):
        segments.append({"type": "html", "content": html[last:]})
    return _strip_group_whitespace(segments)


def _embedded_widget_names(html: str) -> set[str]:
    """Reply-widget names present in the rendered statement HTML.

    Detects oef-input / oef-menu / oef-correspond spans and cf-slots
    regardless of whether they sit inside a <table> — where _segment_statement
    rewrites them to a native <input> and emits no input segment. Used to
    decide whether the "append a default input per reply" fallback is needed;
    without the table-embedded names that fallback duplicates every field
    underneath the table (power10: 14 inputs in the table + 14 below).
    """
    names: set[str] = set()
    for m in _SEGMENT_PATTERN.finditer(html):
        nm = m.group(1) or m.group(2) or m.group(4) or m.group(6)
        if nm:
            nm = nm.strip()
            alias = re.match(r"^r(\d+)$", nm)
            names.add(f"reply{alias.group(1)}" if alias else nm)
    # `checkbox` widgets are emitted by _render_embed as native <input> tags
    # (not oef-* spans), so _SEGMENT_PATTERN misses them — scan separately.
    names |= set(re.findall(r'class="oef-checkbox"\s+name="([^"]+)"', html))
    return names


def _extract_statement(ast: OEFNode, ev: OEFEvaluator) -> str:
    """
    Extrait l'énoncé complet en combinant UNIQUEMENT \instruction, \consigne et \statement.
    Le texte brut en dehors de ces commandes est ignoré (métadonnées, etc.).
    """
    parts = []
    if ast.type == "document" and isinstance(ast.content, list):
        for item in ast.content:
            if isinstance(item, OEFNode) and item.name in (
                "instruction",
                "consigne",
                "statement",
            ):
                # On utilise render_node pour un rendu récursif propre
                parts.append(ev.render_node(item.args))

    return "\n".join(parts)


def _extract_condition(ast: OEFNode, ev: OEFEvaluator) -> dict | None:
    """Extrait \condition{label}{expression} via l'AST."""
    if ast.type == "document" and isinstance(ast.content, list):
        for item in ast.content:
            if isinstance(item, OEFNode) and item.name == "condition":
                if len(item.args) >= 2:
                    return {
                        "label": ev._to_raw_string(item.args[0]).strip(),
                        "expr": ev._to_raw_string(item.args[1]).strip(),
                    }
    return None


def _extract_answers(ast: OEFNode, ev: OEFEvaluator) -> list[AnswerDef]:
    """
    Extrait les \answer{}{}{}... et \choice{}{}{} via l'AST.
    Gère les arguments positionnels (WIMS standard) et nommés (type=...).
    """
    answers = []
    reply_count = 1

    if ast.type == "document" and isinstance(ast.content, list):
        for item in ast.content:
            if not isinstance(item, OEFNode):
                continue

            if item.name in ("answer", "reply", "choice"):
                # On convertit chaque bloc argument en texte brut
                blocks = [ev._to_raw_string(arg).strip() for arg in item.args]

                if item.name == "choice":
                    label = blocks[0] if len(blocks) > 0 else ""
                    correct = ev._substitute_vars(blocks[1]) if len(blocks) > 1 else ""
                    wrong_raw = blocks[2] if len(blocks) > 2 else ""
                    wrong_items = [
                        ev._substitute_vars(w.strip())
                        for w in wrong_raw.split(",")
                        if w.strip()
                    ]
                    all_items = [correct] + wrong_items
                    import random as _random

                    # Utilisation d'un seed local pour la reproductibilité du mélange
                    _random.Random(f"{ev.meta.get('seed', 0)}_{reply_count}").shuffle(
                        all_items
                    )
                    options_raw = blocks[3] if len(blocks) > 3 else ""
                    if "noidontknow" not in options_raw:
                        _dont_know = {
                            "fr": "Je ne sais pas",
                            "nl": "Ik weet het niet",
                            "en": "I don't know",
                        }
                        lang = ev.meta.get("language", "fr")[:2].lower()
                        all_items.append(_dont_know.get(lang, "Je ne sais pas"))

                    answers.append(
                        AnswerDef(
                            label=label,
                            expected=correct,
                            answer_type="radio",
                            options={"choices": all_items},
                            input_name=f"reply{reply_count}",
                            logical_name=label if label else f"reply{reply_count}",
                        )
                    )
                else:
                    # C'est un \answer ou \reply
                    label = ev._substitute_vars(blocks[0]) if len(blocks) > 0 else ""
                    expected_raw = blocks[1] if len(blocks) > 1 else ""
                    expected = ev._substitute_vars(expected_raw)

                    # Logique de parsing des arguments optionnels {type}{option}{weight}
                    ans_type = "numeric"
                    options = {}

                    # WIMS autorise \answer{label}{expected}{type}{option}{weight}
                    # OU \answer{label}{expected}{type=...}{option=...}
                    for i, b in enumerate(blocks[2:]):
                        if "=" in b:
                            k, v = b.split("=", 1)
                            k, v = k.strip().lower(), v.strip()
                            if k == "type":
                                ans_type = v
                            else:
                                options[k] = v
                        else:
                            # Arguments positionnels par défaut après les 2 premiers
                            if i == 0:
                                ans_type = b  # 3ème bloc = type
                            elif i == 1:
                                options["option"] = b  # 4ème bloc = option
                            elif i == 2:
                                options["weight"] = b  # 5ème bloc = weight

                    if ans_type == "clickfill":
                        # Format: "correct_answer;wrong1,wrong2,...". WIMS also
                        # accepts "|" as the separator (anstype/fill.inc:15
                        # translates it to a newline/row break), so treat it the
                        # same as ";".
                        expected = expected.replace("|", ";")
                        if ";" in expected:
                            correct_part, wrongs_str = expected.split(";", 1)
                            correct_part = correct_part.strip()
                            wrong_items = [w.strip() for w in wrongs_str.split(",") if w.strip()]
                        else:
                            correct_part = expected.strip()
                            wrong_items = []
                        if correct_part:
                            from .def_engine.presentation import _close_inline_math as _cf_close  # noqa: PLC0415
                            _cf_lang = ev.meta.get("language", "fr")
                            correct_part = _cf_close(correct_part, _cf_lang)
                            wrong_items = [_cf_close(w, _cf_lang) for w in wrong_items]
                            choices = [correct_part] + wrong_items
                            seen_cf: set[str] = set()
                            choices = [c for c in choices if not (c in seen_cf or seen_cf.add(c))]  # type: ignore[func-returns-value]
                            _random.Random(f"{ev.meta.get('seed', 0)}_{reply_count}").shuffle(choices)
                            expected = correct_part
                            options["choices"] = choices

                    answers.append(
                        AnswerDef(
                            label=label,
                            expected=expected,
                            answer_type=ans_type,
                            options=options,
                            input_name=f"reply{reply_count}",
                            logical_name=label if label else f"reply{reply_count}",
                            weight=float(options.get("weight", 1.0))
                            if "weight" in options
                            else 1.0,
                        )
                    )
                reply_count += 1

    return answers


def _extract_block(ast: OEFNode, name: str, ev: OEFEvaluator) -> str:
    if ast.type == "document" and isinstance(ast.content, list):
        for item in ast.content:
            if isinstance(item, OEFNode) and item.name == name:
                return ev.render_node(item.args)
    return ""
