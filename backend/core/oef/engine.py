"""
Moteur OEF principal.
Charge un fichier .oef, l'évalue avec un seed, et retourne un ExerciseRender.
"""
import os
import random
from dataclasses import dataclass, field

from .parser import parse, Directive
from .evaluator import OEFEvaluator


@dataclass
class AnswerDef:
    label: str
    expected: str
    answer_type: str        # numeric, algexp, text, radio, clickfill, ...
    options: dict = field(default_factory=dict)
    weight: float = 1.0
    input_name: str = ""    # reply1, reply2, ...
    logical_name: str = ""  # nom de variable OEF (rsymb1, rx1…) utilisé dans \condition


@dataclass
class ExerciseRender:
    title: str
    lang: str
    statement_html: str
    answers: list[AnswerDef]
    hint_html: str
    solution_html: str
    seed: int
    meta: dict              # author, email, etc.
    condition: dict | None = None  # \condition{label}{expr} pour la vérification globale
    ev_ctx: dict = field(default_factory=dict)  # contexte de l'évaluateur (variables)


def load_and_render(oef_path: str, seed: int | None = None) -> ExerciseRender:
    """
    Point d'entrée principal.
    Lit le fichier .oef, évalue les variables, retourne un ExerciseRender.
    """
    if not os.path.exists(oef_path):
        raise FileNotFoundError(f"Fichier OEF introuvable : {oef_path}")

    # Les fichiers OEF sont historiquement en ISO-8859-1 (latin-1)
    try:
        with open(oef_path, encoding="utf-8") as f:
            source = f.read()
    except UnicodeDecodeError:
        with open(oef_path, encoding="iso-8859-1") as f:
            source = f.read()

    if seed is None:
        seed = random.randint(0, 2**31)

    directives = parse(source)
    evaluator = OEFEvaluator(seed=seed)
    evaluator.evaluate_source(source)

    answers = _extract_answers_from_source(source, evaluator)
    condition = _extract_condition_from_source(source, evaluator)
    statement_html = _extract_statement(directives, evaluator)

    # Filtre les réponses dont le champ n'apparaît pas dans le statement rendu,
    # mais seulement si le statement contient des \embed (oef-input/cf-slot).
    # Pour les \choice (radio), il n'y a pas d'embed : on garde tout.
    if 'oef-input' in statement_html or 'cf-slot' in statement_html:
        import re as _re
        # Noms effectivement présents dans le HTML (name="r1", name="reply1", etc.)
        html_names = set(_re.findall(r'name="([^"]+)"', statement_html))

        def _answer_in_statement(input_name: str) -> bool:
            name_nospace = input_name.replace(" ", "")
            if name_nospace in html_names:
                return True
            name_spaced = _re.sub(r'(reply)(\d+)', r'\1 \2', name_nospace)
            if name_spaced in html_names:
                return True
            # r1 est l'alias court de reply1
            m = _re.match(r'^reply(\d+)$', name_nospace)
            if m and f"r{m.group(1)}" in html_names:
                return True
            return False

        answers = [a for a in answers if _answer_in_statement(a.input_name)]

    return ExerciseRender(
        title=evaluator.meta.get("title", ""),
        lang=evaluator.meta.get("language", "fr"),
        statement_html=statement_html,
        answers=answers,
        hint_html=_extract_block(directives, "hint", evaluator),
        solution_html=_extract_block(directives, "solution", evaluator),
        seed=seed,
        meta={k: v for k, v in evaluator.meta.items() if k not in ("title", "language")},
        condition=condition,
        ev_ctx=dict(evaluator.ctx),  # contexte complet pour évaluation de \condition
    )


def _extract_statement(directives: list[Directive], ev: OEFEvaluator) -> str:
    for d in directives:
        if d.name == "statement":
            return ev.render_statement(d.content)
    return ""


def _extract_condition_from_source(source: str, ev: OEFEvaluator) -> dict | None:
    """Extrait \condition{label}{expression} — gère les deux blocs {} séparés."""
    import re
    from .parser import _extract_braces
    pos = 0
    n = len(source)
    while pos < n:
        m = re.search(r'\\condition\s*\{', source[pos:])
        if not m:
            return None
        brace_start = pos + m.end() - 1
        blocks = []
        cur = brace_start
        while cur < n and source[cur] == '{':
            block = _extract_braces(source, cur)
            blocks.append(block[1:-1])
            cur += len(block)
            while cur < n and source[cur] in ' \t\n':
                cur += 1
            if cur >= n or source[cur] != '{':
                break
        if len(blocks) >= 2:
            return {"label": blocks[0].strip(), "expr": blocks[1].strip()}
        pos = cur
    return None


def _extract_block(directives: list[Directive], name: str, ev: OEFEvaluator) -> str:
    for d in directives:
        if d.name == name:
            return ev.render_statement(d.content)
    return ""


def _extract_answers_from_source(source: str, ev: OEFEvaluator) -> list[AnswerDef]:
    """
    Extrait les \answer{}{}{}... et \choice{}{}{} directement depuis le source brut.
    Format OEF : \answer{label}{expected}{type=t}{option=o}{weight=w}
    Chaque paramètre est dans son propre bloc {}.
    """
    import re
    from .parser import _extract_braces

    answers = []
    reply_count = 1
    pos = 0
    n = len(source)

    while pos < n:
        # Cherche \answer ou \choice
        m = re.search(r'\\(answer|reply|choice)\s*\{', source[pos:])
        if not m:
            break
        directive_name = m.group(1)
        # m.end() pointe après le {, donc on recule de 1
        brace_start = pos + m.end() - 1  # position du {

        # Extrait tous les blocs {} consécutifs
        blocks = []
        cur = brace_start
        while cur < n and source[cur] == '{':
            block = _extract_braces(source, cur)
            blocks.append(block[1:-1])  # sans les accolades
            cur += len(block)
            # Saute les espaces entre blocs
            while cur < n and source[cur] in ' \t\n':
                cur += 1
            # S'arrête si le prochain char n'est pas {
            if cur >= n or source[cur] != '{':
                break

        pos = cur

        if directive_name == "choice":
            label = blocks[0].strip() if len(blocks) > 0 else ""
            correct = ev._substitute_vars(blocks[1].strip()) if len(blocks) > 1 else ""
            wrong_raw = blocks[2].strip() if len(blocks) > 2 else ""
            wrong_items = [ev._substitute_vars(w.strip()) for w in wrong_raw.split(",") if w.strip()]
            all_items = [correct] + wrong_items
            import random as _random
            _random.Random(reply_count).shuffle(all_items)
            answers.append(AnswerDef(
                label=label,
                expected=correct,
                answer_type="radio",
                options={"choices": all_items},
                input_name=f"reply{reply_count}",
            ))
        else:
            label = blocks[0].strip() if len(blocks) > 0 else ""
            expected_raw = blocks[1].strip() if len(blocks) > 1 else ""
            expected = ev._substitute_vars(expected_raw)

            answer_type = "numeric"
            weight = 1.0
            opts: dict[str, str | list[str]] = {}
            logical_name = ""
            for block in blocks[2:]:
                b = block.strip()
                if b.startswith("type="):
                    answer_type = b[5:].strip()
                elif b.startswith("option="):
                    opts["option"] = b[7:].strip()
                elif b.startswith("weight="):
                    try:
                        weight = float(b[7:].strip())
                    except ValueError:
                        pass

            # Pour clickfill : expected_raw = "logical_name;choices_var"
            # Ex: \rsymb1;\lsymb  → logical_name=rsymb1, choices=valeur de lsymb
            if answer_type.lower() == "clickfill" and ";" in expected_raw:
                parts_cf = expected_raw.split(";", 1)
                logical_raw = parts_cf[0].strip().lstrip("\\")
                choices_raw = ev._substitute_vars(parts_cf[1].strip())
                logical_name = logical_raw
                # Les choix sont séparés par des virgules
                opts["choices"] = [c.strip() for c in choices_raw.split(",") if c.strip()]
                # L'expected est la valeur OEF correspondante (ex: symb1 pour rsymb1)
                ov_name = logical_raw[1:] if logical_raw.startswith("r") else logical_raw
                expected = ev.ctx.get(ov_name, expected)

            # Pour numexp/numeric avec expected non résolu (\rx1) → logical_name = rx1
            elif expected.startswith("\\") or (expected_raw.startswith("\\") and expected == expected_raw):
                raw_lname = expected_raw.strip().lstrip("\\")
                if raw_lname and raw_lname not in ev.ctx:
                    logical_name = raw_lname
                    ov_name = raw_lname[1:] if raw_lname.startswith("r") else raw_lname
                    expected = ev.ctx.get(ov_name, expected)

            answers.append(AnswerDef(
                label=label,
                expected=expected,
                answer_type=answer_type,
                options=opts,
                weight=weight,
                input_name=f"reply{reply_count}",
                logical_name=logical_name,
            ))

        reply_count += 1

    return answers


def _extract_answers(directives: list[Directive], ev: OEFEvaluator) -> list[AnswerDef]:
    answers = []
    reply_count = 1

    for d in directives:
        if d.name not in ("answer", "reply", "choice"):
            continue

        if d.name == "choice":
            # \choice{label}{correct}{incorrect,...}
            # Transformé en type=radio
            parts = _split_top_level(d.content)
            label = parts[0].strip() if len(parts) > 0 else ""
            correct = parts[1].strip() if len(parts) > 1 else ""
            wrong = parts[2].strip() if len(parts) > 2 else ""

            correct = ev._substitute_vars(correct)
            wrong_items = [ev._substitute_vars(w) for w in wrong.split(",")]
            all_items = [correct] + wrong_items
            random.Random(ev.rng.randint(0, 2**31)).shuffle(all_items)

            answers.append(AnswerDef(
                label=label,
                expected=correct,
                answer_type="radio",
                options={"choices": all_items},
                input_name=f"reply{reply_count}",
            ))
        else:
            # \answer{label}{expected}{type=...}{option=...}{weight=...}
            parts = _split_top_level(d.content)
            label = parts[0].strip() if len(parts) > 0 else ""
            expected_raw = parts[1].strip() if len(parts) > 1 else ""
            expected = ev._substitute_vars(expected_raw)

            opts = {}
            answer_type = "numeric"
            weight = 1.0

            for part in parts[2:]:
                part = part.strip()
                if part.startswith("type="):
                    answer_type = part[5:].strip()
                elif part.startswith("option="):
                    opts["option"] = part[7:].strip()
                elif part.startswith("weight="):
                    try:
                        weight = float(part[7:].strip())
                    except ValueError:
                        pass

            answers.append(AnswerDef(
                label=label,
                expected=expected,
                answer_type=answer_type,
                options=opts,
                weight=weight,
                input_name=f"reply{reply_count}",
            ))

        reply_count += 1

    return answers


def _split_top_level(content: str) -> list[str]:
    """
    Découpe une chaîne en segments séparés par } { au niveau le plus haut.
    Ex: "label}{expected}{type=numeric" → ["label", "expected", "type=numeric"]
    """
    # Le contenu arrive sans les accolades extérieures,
    # les séparateurs sont des }{ consécutifs
    parts = []
    depth = 0
    current = []
    i = 0
    while i < len(content):
        ch = content[i]
        if ch == '{':
            depth += 1
            current.append(ch)
        elif ch == '}':
            if depth == 0:
                # Séparateur de niveau haut : on regarde si le suivant est {
                parts.append("".join(current))
                current = []
                # Saute le { suivant s'il est là
                if i + 1 < len(content) and content[i + 1] == '{':
                    i += 1  # saute le {
            else:
                depth -= 1
                current.append(ch)
        else:
            current.append(ch)
        i += 1
    if current:
        parts.append("".join(current))
    return parts
