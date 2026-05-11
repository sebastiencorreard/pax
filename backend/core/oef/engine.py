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
    """
    if not os.path.exists(oef_path):
        raise FileNotFoundError(f"Fichier OEF introuvable : {oef_path}")

    def_path = find_def_path(oef_path)
    if def_path:
        from .def_engine import load_and_render as _def_render

        return _def_render(def_path, seed=seed, m_step=m_step)

    # Fallback: pipeline OEF original

    # Les fichiers OEF sont historiquement en ISO-8859-1 (latin-1)
    try:
        with open(oef_path, encoding="utf-8") as f:
            source = f.read()
    except UnicodeDecodeError:
        with open(oef_path, encoding="iso-8859-1") as f:
            source = f.read()

    if seed is None:
        seed = random.randint(0, 2**31)

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

    return ExerciseRender(
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


# Reconnaît les trois types de widgets dans le HTML rendu :
#   groupe 1 — slot clickfill : <cf-slot name="…"></cf-slot>
#   groupes 2-3 — champ texte : <span class="oef-input" name="…" data-size="…"></span>
#   groupes 4-5 — menu déroulant : <span class="oef-menu" name="…" data-label="…"></span>
_SEGMENT_PATTERN = re.compile(
    r'<cf-slot name="([^"]+)"></cf-slot>'
    r'|<span\s+class="oef-input"\s+name="([^"]+)"\s+data-size="([^"]*)"></span>'
    r'|<span\s+class="oef-menu"\s+name="([^"]+)"\s+data-label="([^"]*)"></span>'
)
# Balises de bloc converties en <br> pour aplatir le HTML en une seule ligne
# lisible par le front-end (qui n'attend pas de structure imbriquée).
# <div>, <p>, <li>, <ul>, <ol> ouvrants → <br> (séparateur d'item).
_BLOCK_OPEN = re.compile(r"<(?:div|p|li|ul|ol)(?=[\s>])[^>]*>", re.I)
# </div>, </p>, </ul>, </ol> → <br> (fin de bloc) ; </li> → rien (supprimé).
# </li> ne crée pas de saut car le <li> ouvrant suivant y pourvoit déjà via
# _BLOCK_OPEN. En revanche </ul> et </ol> marquent la fin de la liste et
# doivent séparer le dernier item du contenu qui suit (ex : label + champ).
_BLOCK_CLOSE = re.compile(r"</(?:div|p|ul|ol)>", re.I)
_LIST_CLOSE = re.compile(r"</li>", re.I)
# Séquences de plusieurs <br> consécutifs (avec espaces) → un seul <br>.
_BR_RUN = re.compile(r"(?:\s*<br\s*/?>\s*){2,}", re.I)
# <br> en tête de chaîne (artefacts de la conversion div/p → br).
_BR_LEADING = re.compile(r"^(?:\s*<br\s*/?>\s*)+", re.I)


def _segment_statement(html: str) -> list[dict]:
    """
    Découpe le HTML rendu en segments typés consommables tels quels par le front :
      - {type: "html", content: "..."}
      - {type: "input", name: "reply1", size: 10}
      - {type: "slot",  name: "..."}
      - {type: "menu",  name: "reply1", label: "Choix"}
    Aplatit les balises de bloc (<div>, <p>, <li>, <ul>, <ol>) en <br> et
    résout l'alias rN ↔ replyN.
    """
    html = _BLOCK_OPEN.sub("<br>", html)
    html = _BLOCK_CLOSE.sub("<br>", html)
    html = _LIST_CLOSE.sub("", html)
    html = _BR_RUN.sub("<br>", html)
    html = _BR_LEADING.sub("", html)

    segments: list[dict] = []
    last = 0
    in_sup = 0
    for m in _SEGMENT_PATTERN.finditer(html):
        if m.start() > last:
            content = html[last : m.start()]
            segments.append({"type": "html", "content": content})
            in_sup += content.lower().count("<sup") - content.lower().count("</sup")
            
        is_sup = in_sup > 0

        if m.group(1) is not None:
            # Slot clickfill
            segments.append({"type": "slot", "name": m.group(1).strip(), "is_sup": is_sup})
        elif m.group(4) is not None:
            # Menu déroulant
            name = m.group(4).strip()
            alias = re.match(r"^r(\d+)$", name)
            if alias:
                name = f"reply{alias.group(1)}"
            label = m.group(5).strip()
            segments.append({"type": "menu", "name": name, "label": label, "is_sup": is_sup})
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
    return segments


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
                        # Format: "correct_answer;wrong1,wrong2,..."
                        if ";" in expected:
                            correct_part, wrongs_str = expected.split(";", 1)
                            correct_part = correct_part.strip()
                            wrong_items = [w.strip() for w in wrongs_str.split(",") if w.strip()]
                        else:
                            correct_part = expected.strip()
                            wrong_items = []
                        if correct_part:
                            from .def_engine.presentation import _close_inline_math as _cf_close  # noqa: PLC0415
                            correct_part = _cf_close(correct_part)
                            wrong_items = [_cf_close(w) for w in wrong_items]
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
