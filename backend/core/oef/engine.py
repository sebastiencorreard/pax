"""
Moteur OEF principal.
Charge un fichier .oef, l'évalue avec un seed, et retourne un ExerciseRender.
"""
import os
import random
from dataclasses import dataclass, field

from .parser import parse, Directive, get_directives_compat, OEFNode
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

    directives_ast = parse(source)
    evaluator = OEFEvaluator(seed=seed)
    evaluator.evaluate_ast(directives_ast)

    answers = _extract_answers(directives_ast, evaluator)
    condition = _extract_condition(directives_ast, evaluator)
    statement_html = _extract_statement(directives_ast, evaluator)

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
        hint_html=_extract_block(directives_ast, "hint", evaluator),
        solution_html=_extract_block(directives_ast, "solution", evaluator),
        seed=seed,
        meta={k: v for k, v in evaluator.meta.items() if k not in ("title", "language")},
        condition=condition,
        ev_ctx=dict(evaluator.ctx),  # contexte complet pour évaluation de \condition
    )


def _extract_statement(ast: OEFNode, ev: OEFEvaluator) -> str:
    """
    Extrait l'énoncé complet en combinant UNIQUEMENT \instruction, \consigne et \statement.
    Le texte brut en dehors de ces commandes est ignoré (métadonnées, etc.).
    """
    parts = []
    if ast.type == "document" and isinstance(ast.content, list):
        for item in ast.content:
            if isinstance(item, OEFNode) and item.name in ("instruction", "consigne", "statement"):
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
                        "expr": ev._to_raw_string(item.args[1]).strip()
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
            if not isinstance(item, OEFNode): continue
            
            if item.name in ("answer", "reply", "choice"):
                # On convertit chaque bloc argument en texte brut
                blocks = [ev._to_raw_string(arg).strip() for arg in item.args]
                
                if item.name == "choice":
                    label = blocks[0] if len(blocks) > 0 else ""
                    correct = ev._substitute_vars(blocks[1]) if len(blocks) > 1 else ""
                    wrong_raw = blocks[2] if len(blocks) > 2 else ""
                    wrong_items = [ev._substitute_vars(w.strip()) for w in wrong_raw.split(",") if w.strip()]
                    all_items = [correct] + wrong_items
                    import random as _random
                    # Utilisation d'un seed local pour la reproductibilité du mélange
                    _random.Random(f"{ev.meta.get('seed', 0)}_{reply_count}").shuffle(all_items)
                    
                    answers.append(AnswerDef(
                        label=label,
                        expected=correct,
                        answer_type="radio",
                        options={"choices": all_items},
                        input_name=f"reply{reply_count}",
                        logical_name=label if label else f"reply{reply_count}"
                    ))
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
                            if k == "type": ans_type = v
                            else: options[k] = v
                        else:
                            # Arguments positionnels par défaut après les 2 premiers
                            if i == 0: ans_type = b # 3ème bloc = type
                            elif i == 1: options["option"] = b # 4ème bloc = option
                            elif i == 2: options["weight"] = b # 5ème bloc = weight

                    answers.append(AnswerDef(
                        label=label,
                        expected=expected,
                        answer_type=ans_type,
                        options=options,
                        input_name=f"reply{reply_count}",
                        logical_name=label if label else f"reply{reply_count}",
                        weight=float(options.get("weight", 1.0)) if "weight" in options else 1.0
                    ))
                reply_count += 1
                
    return answers


def _extract_block(ast: OEFNode, name: str, ev: OEFEvaluator) -> str:
    if ast.type == "document" and isinstance(ast.content, list):
        for item in ast.content:
            if isinstance(item, OEFNode) and item.name == name:
                return ev.render_node(item.args)
    return ""
