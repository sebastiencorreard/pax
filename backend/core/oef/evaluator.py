"""
Évaluateur de variables OEF.
Prend les directives parsées, évalue les variables dans l'ordre,
et retourne un contexte (dict) de toutes les variables résolues.
"""
import re
import math
import random
from fractions import Fraction
from .parser import Directive


class OEFEvaluationError(Exception):
    pass


class OEFEvaluator:

    def __init__(self, seed: int | None = None):
        self.rng = random.Random(seed)
        # confparm1..9 sont des paramètres WIMS (configuration externe) ;
        # hors WIMS ils sont toujours vides
        self.ctx: dict[str, str] = {f"confparm{i}": "" for i in range(1, 10)}
        self.meta: dict[str, str] = {}  # title, author, language, etc.

    # ------------------------------------------------------------------ #
    # Point d'entrée                                                       #
    # ------------------------------------------------------------------ #

    def evaluate(self, directives: list[Directive]) -> dict:
        """Évalue toutes les directives et retourne le contexte complet.
        NOTE : n'utilise PAS cette liste pour les \if — voir evaluate_source()."""
        for d in directives:
            try:
                self._eval_directive(d)
            except Exception:
                pass
        return self.ctx

    def evaluate_source(self, source: str) -> dict:
        """
        Évalue le source OEF en respectant les \if{condition}{bloc}.
        Remplace evaluate() pour les fichiers contenant des \if au niveau variables.
        """
        from .parser import _extract_braces
        pos = 0
        n = len(source)

        while pos < n:
            bs = source.find('\\', pos)
            if bs == -1:
                break

            # Ignore les lignes de commentaires
            line_start = source.rfind('\n', 0, bs) + 1
            if source[line_start:bs].strip().startswith('%'):
                pos = source.find('\n', bs)
                if pos == -1:
                    break
                continue

            pos = bs + 1
            name_start = pos
            while pos < n and (source[pos].isalpha() or source[pos].isdigit()):
                pos += 1
            name = source[name_start:pos].lower()
            if not name:
                continue

            while pos < n and source[pos] in ' \t':
                pos += 1

            if pos >= n or source[pos] != '{':
                # Directive sans accolades (ex: \language fr)
                if pos < n and source[pos] != '\n':
                    val_start = pos
                    while pos < n and source[pos] != '\n':
                        pos += 1
                    self._eval_directive(Directive(name=name, content=source[val_start:pos].strip()))
                continue

            # Extraire le premier bloc
            block1 = _extract_braces(source, pos)
            pos += len(block1)
            inner1 = block1[1:-1]

            # Sauter les espaces entre blocs
            while pos < n and source[pos] in ' \t\n':
                pos += 1

            if name == 'if':
                # Extraire bloc vrai
                if pos < n and source[pos] == '{':
                    block_true = _extract_braces(source, pos)
                    pos += len(block_true)
                    inner_true = block_true[1:-1]
                else:
                    inner_true = ''

                # Extraire bloc faux optionnel
                while pos < n and source[pos] in ' \t\n':
                    pos += 1
                inner_false = ''
                if pos < n and source[pos] == '{':
                    block_false = _extract_braces(source, pos)
                    pos += len(block_false)
                    inner_false = block_false[1:-1]

                # Évaluer la condition
                cond_raw = self._substitute_vars(inner1)
                cond_py = _oef_cond_to_py(cond_raw)
                try:
                    eval_ctx = {k: _try_num(v) for k, v in self.ctx.items()}
                    eval_ctx.update({"abs": abs, "min": min, "max": max,
                                     "sqrt": math.sqrt, "True": True, "False": False})
                    cond = bool(eval(cond_py, {"__builtins__": {}}, eval_ctx))
                except Exception:
                    cond = False

                bloc = inner_true if cond else inner_false
                if bloc.strip():
                    self.evaluate_source(bloc)

            elif name == 'while':
                # Extraire le bloc du while (inner1 = condition, bloc suivant = directives)
                if pos < n and source[pos] == '{':
                    block_body = _extract_braces(source, pos)
                    pos += len(block_body)
                    self._eval_while(inner1 + '}' + block_body)
                else:
                    self._eval_while(inner1)

            else:
                self._eval_directive(Directive(name=name, content=inner1))

    # ------------------------------------------------------------------ #
    # Dispatch par type de directive                                        #
    # ------------------------------------------------------------------ #

    def _eval_directive(self, d: Directive):
        match d.name:
            case "integer":
                self._eval_typed(d.content, kind="integer")
            case "real":
                self._eval_typed(d.content, kind="real")
            case "rational":
                self._eval_typed(d.content, kind="rational")
            case "text":
                self._eval_typed(d.content, kind="text")
            case "function":
                self._eval_typed(d.content, kind="function")
            case "title" | "author" | "email" | "language" | "language" \
                 | "format" | "computeanswer" | "precision" | "range" | "keywords":
                self.meta[d.name] = d.content.strip()
            case "while":
                self._eval_while(d.content)
            case "if":
                self._eval_if_directive(d.content)
            case _:
                pass  # statement, answer, hint, etc. traités ailleurs

    def _eval_if_directive(self, content: str) -> None:
        """
        Évalue \if{condition}{bloc_vrai} ou \if{condition}{bloc_vrai}{bloc_faux}
        au niveau des variables (hors statement).
        Le contenu reçu est 'condition' (premier bloc déjà consommé par le parser) ;
        les blocs suivants sont dans le source brut — on les retrouve via le parser
        qui a déjà extrait les directives internes et les a mises dans la liste globale.

        En réalité le parser extrait les \text/\integer internes comme directives
        top-level, donc on ne peut pas les re-évaluer sélectivement ici.
        On utilise une approche différente : on re-parse le source brut de l'OEF
        directement dans evaluate(). Cette méthode est appelée avec le contenu
        de la condition uniquement ; on évalue juste la condition pour décider
        si on doit ignorer les prochaines directives.

        NOTE : Cette méthode sert de marqueur — la vraie logique est dans evaluate()
        via _eval_if_block() qui reçoit tout le contenu brut.
        """
        pass  # Géré par _eval_if_block dans evaluate()

    def _eval_while(self, content: str):
        """Évalue \while{condition}{bloc de directives}.
        Le contenu est 'condition}{directives' (les accolades externes déjà consommées par le parser).
        On ré-évalue le bloc en boucle tant que la condition est vraie (max 50 itérations).
        """
        from .parser import parse
        # Le contenu est de la forme : condition}{directives
        # On cherche la première } pour séparer condition et bloc
        depth = 0
        split = -1
        for i, ch in enumerate(content):
            if ch == '{':
                depth += 1
            elif ch == '}':
                if depth == 0:
                    split = i
                    break
                depth -= 1
        if split == -1:
            return
        cond_raw = content[:split].strip()
        after = content[split + 1:].strip()
        # Retire UNE accolade ouvrante en début et UNE fermante en fin
        if after.startswith('{'):
            after = after[1:]
        if after.endswith('}'):
            after = after[:-1]
        bloc_raw = after
        for _ in range(50):  # protection contre boucle infinie
            cond_subst = self._substitute_vars(cond_raw)
            try:
                eval_ctx = {k: _try_num(v) for k, v in self.ctx.items()}
                eval_ctx.update({"abs": abs, "min": min, "max": max, "True": True, "False": False})
                cond_py = _oef_cond_to_py(cond_subst)
                cond = eval(cond_py, {"__builtins__": {}}, eval_ctx)
            except Exception:
                break
            if not cond:
                break
            self.evaluate_source(bloc_raw)

    def _eval_typed(self, content: str, kind: str):
        """Parse 'varname=expression' et stocke la valeur évaluée."""
        if "=" not in content:
            return
        eq = content.index("=")
        varname = content[:eq].strip().lstrip("\\")
        expr = content[eq + 1:].strip()

        value = self._eval_expr(expr, kind)
        self.ctx[varname] = str(value)

    # ------------------------------------------------------------------ #
    # Évaluation d'expressions                                             #
    # ------------------------------------------------------------------ #

    def _eval_expr(self, expr: str, kind: str = "text") -> str:
        """Évalue une expression OEF en substituant les variables connues."""

        # 1. Substitue les variables \nom et \nom[idx]
        expr = self._substitute_vars(expr)

        # 2. Fonctions OEF spéciales
        expr = self._eval_oef_functions(expr)

        # 3. Évaluation numérique si pertinent
        if kind in ("integer", "real", "rational"):
            return self._eval_numeric(expr, kind)

        return expr.strip()

    def _substitute_vars(self, expr: str) -> str:
        """Remplace \varname et \varname[n] par leur valeur dans ctx."""

        def replace_indexed(m):
            name = m.group(1)
            idx = int(m.group(2)) - 1  # OEF commence à 1
            val = self.ctx.get(name, "")
            items = [x.strip() for x in val.split(",")]
            if 0 <= idx < len(items):
                return items[idx]
            return ""

        def replace_simple(m):
            name = m.group(1)
            return self.ctx.get(name, m.group(0))

        # D'abord les indexés \var[n]
        expr = re.sub(r'\\([A-Za-z]\w*)\[(\d+)\]', replace_indexed, expr)
        # Puis les simples \var — les noms les plus longs en priorité
        # pour éviter que \b remplace le début de \b2.
        # On utilise une regex avec frontière de mot pour éviter que \l
        # ne remplace le \l dans \left, ou \s dans \sqrt, etc.
        names_by_len = sorted(self.ctx.keys(), key=len, reverse=True)
        for name in names_by_len:
            val = self.ctx[name]
            # Remplace \name uniquement si non suivi d'un caractère de mot.
            # Lambda comme remplacement pour que les \ dans val ne soient pas
            # interprétés comme des séquences d'échappement regex.
            expr = re.sub(r'\\' + re.escape(name) + r'(?![A-Za-z0-9_])', lambda m, v=val: v, expr)  # type: ignore[misc]
        # Substitution résiduelle par regex pour les vars non trouvées
        expr = re.sub(r'\\([A-Za-z]\w*)', replace_simple, expr)
        return expr

    def _eval_oef_functions(self, expr: str) -> str:
        """Évalue les fonctions OEF : randint, randitem, random, items, etc."""

        # randint(a..b) ou random(a..b)
        expr = re.sub(
            r'rand(?:int|om)\((-?\d+)\.\.(-?\d+)\)',
            lambda m: str(self.rng.randint(int(m.group(1)), int(m.group(2)))),
            expr
        )

        # randitem(a,b,c,...)
        def eval_randitem(m):
            items = [x.strip() for x in m.group(1).split(",")]
            return self.rng.choice(items)
        expr = re.sub(r'randitem\(([^)]+)\)', eval_randitem, expr)

        # items(\var) ou items(expr,expr,...) → nombre d'éléments (top-level)
        def _count_top_level_items(s: str) -> int:
            """Compte les éléments d'une liste séparée par des virgules au niveau 0."""
            depth = 0
            count = 1
            for ch in s:
                if ch in '({[':
                    depth += 1
                elif ch in ')}]':
                    depth -= 1
                elif ch == ',' and depth == 0:
                    count += 1
            return count

        def eval_items(m):
            arg = m.group(1).strip()
            if re.match(r'^\\?[a-zA-Z]\w*$', arg):
                val = self.ctx.get(arg.lstrip('\\'), "")
            else:
                val = arg
            return str(_count_top_level_items(val)) if val else "0"
        expr = re.sub(r'items\((.+?)\)', eval_items, expr)

        # item(n, \var) → n-ième élément
        def eval_item(m):
            idx = int(m.group(1)) - 1
            val = self.ctx.get(m.group(2), "")
            parts = [x.strip() for x in val.split(",")]
            return parts[idx] if 0 <= idx < len(parts) else ""
        expr = re.sub(r'item\((\d+),\s*\\?(\w+)\)', eval_item, expr)

        # shuffle(\var) ou shuffle(a,b,c)
        def eval_shuffle(m):
            arg = m.group(1)
            if arg.startswith("\\"):
                val = self.ctx.get(arg.lstrip("\\"), arg)
                items = [x.strip() for x in val.split(",")]
            else:
                items = [x.strip() for x in arg.split(",")]
            self.rng.shuffle(items)
            return ",".join(items)
        expr = re.sub(r'shuffle\(([^)]+)\)', eval_shuffle, expr)

        # wims(values EXPR for VAR=START to END) → liste séparée par virgules
        def eval_wims_values(m):
            expr_tmpl = m.group(1).strip()
            var       = m.group(2).strip()
            try:
                start = int(self._eval_numeric(m.group(3).strip(), 'integer'))
                end   = int(self._eval_numeric(m.group(4).strip(), 'integer'))
            except Exception:
                return m.group(0)
            results = []
            for val in range(start, end + 1):
                results.append(expr_tmpl.replace(var, str(val)))
            return ",".join(results)
        expr = re.sub(
            r'wims\(\s*values\s+(.+?)\s+for\s+(\w+)\s*=\s*(-?\d+)\s+to\s+(-?\d+)\s*\)',
            eval_wims_values, expr
        )

        # wims(replace X by Y in expr) — simplifié
        def eval_replace(m):
            old, new, target = m.group(1), m.group(2), m.group(3)
            return target.replace(old, new)
        expr = re.sub(
            r'wims\(replace\s+(.+?)\s+by\s+(.+?)\s+in\s+(.+?)\)',
            eval_replace, expr
        )

        # pari(n) — arrondi à l'entier pair le plus proche (≥ n)
        def eval_pari(m):
            try:
                n = int(float(self._eval_numeric(m.group(1).strip(), 'real')))
                return str(n if n % 2 == 0 else n + 1)
            except Exception:
                return m.group(1)
        expr = re.sub(r'pari\(([^)]+)\)', eval_pari, expr)

        # core(n) — partie sans carré de n (plus grand carré-free divisor)
        def eval_core(m):
            try:
                n = abs(int(float(self._eval_numeric(m.group(1).strip(), 'real'))))
                if n == 0:
                    return '0'
                # Divise n par tous les carrés parfaits
                result = n
                d = 2
                while d * d <= result:
                    while result % (d * d) == 0:
                        result //= (d * d)
                    d += 1
                return str(result)
            except Exception:
                return m.group(1)
        expr = re.sub(r'core\(([^)]+)\)', eval_core, expr)

        # min(a,b) et max(a,b) — évaluation numérique
        def eval_minmax(m: re.Match) -> str:
            fn = m.group(1)
            try:
                args = [float(Fraction(a.strip())) for a in m.group(2).split(',')]
                result = min(args) if fn == 'min' else max(args)
                f = Fraction(result).limit_denominator(10000)
                return str(f.numerator) if f.denominator == 1 else str(f)
            except Exception:
                return m.group(0)
        expr = re.sub(r'\b(min|max)\(([^)]+)\)', eval_minmax, expr)

        # abs(expr) → évalue si numérique, sinon → |expr| en LaTeX
        def eval_abs(inner: str) -> str:
            try:
                val = float(Fraction(inner.strip()))
                f = Fraction(abs(val)).limit_denominator(10000)
                return str(f.numerator) if f.denominator == 1 else str(f)
            except Exception:
                return r'\left|' + inner + r'\right|'
        expr = _apply_func_transform(expr, 'abs', eval_abs)

        # texmath(expr) — convertit une expression algébrique en LaTeX lisible
        def _texmath_transform(inner: str) -> str:
            inner = inner.replace('**', '^')
            # sqrt(...) → \sqrt{...}
            inner = _apply_func_transform(inner, 'sqrt', lambda x: r'\sqrt{' + x + '}')
            # n*x → nx (coefficient entier devant une variable)
            inner = re.sub(r'(-?\d+)\s*\*\s*([a-zA-Z])', r'\1\2', inner)
            # * restant → \cdot
            inner = inner.replace('*', r'\cdot ')
            # Simplification des signes : +-n → -n, --n → +n
            inner = re.sub(r'\+(-\d+(?:\.\d+)?)', r'\1', inner)
            inner = re.sub(r'-(-\d+(?:\.\d+)?)', lambda m: '+' + m.group(1)[1:], inner)
            # Supprime le + en début ou après = < > ≤ ≥ (opérateurs de relation)
            inner = re.sub(r'(^|[=<>≤≥])\+', r'\1', inner.strip())
            return inner
        expr = _apply_func_transform(expr, 'texmath', _texmath_transform)

        # simplify(expr) — évalue comme fraction réduite
        def _simplify_transform(inner: str) -> str:
            try:
                result = eval(inner.replace('^', '**'),
                              {"__builtins__": {}}, {"abs": abs, "sqrt": math.sqrt})
                f = Fraction(result).limit_denominator(10000)
                return str(f) if f.denominator != 1 else str(f.numerator)
            except Exception:
                return inner
        expr = _apply_func_transform(expr, 'simplify', _simplify_transform)

        # maxima(expr) — extrait le contenu en gérant les parenthèses imbriquées
        expr = _strip_function_call(expr, 'maxima')

        # slib(...) → chaîne vide pour l'instant
        expr = _strip_function_call(expr, 'slib', replacement='')

        return expr

    def _eval_numeric(self, expr: str, kind: str) -> str:
        """Évalue une expression arithmétique Python-compatible."""
        # Remplace ^ par ** (OEF utilise ^, Python **)
        expr = expr.replace("^", "**")
        # Opérateur ternaire OEF : cond? val_vrai : val_faux
        expr = self._eval_ternary(expr)

        try:
            result = eval(expr, {"__builtins__": {}}, {
                "abs": abs, "max": max, "min": min,
                "sqrt": math.sqrt, "floor": math.floor, "ceil": math.ceil,
                "gcd": math.gcd,
            })
            if kind == "integer":
                return str(int(round(float(result))))
            elif kind == "rational":
                f = Fraction(result).limit_denominator(10000)
                return str(f) if f.denominator != 1 else str(f.numerator)
            else:
                return str(float(result))
        except Exception:
            return expr

    def _eval_ternary(self, expr: str) -> str:
        """Évalue l'opérateur ternaire OEF : condition? val_vrai : val_faux"""
        m = re.match(r'^(.+?)\?(.+?):(.+)$', expr.strip())
        if not m:
            return expr
        cond_str = m.group(1).strip().replace("^", "**")
        val_true = m.group(2).strip()
        val_false = m.group(3).strip()
        try:
            cond = eval(cond_str, {"__builtins__": {}}, {})
            return val_true if cond else val_false
        except Exception:
            return expr

    # ------------------------------------------------------------------ #
    # Rendu du statement                                                   #
    # ------------------------------------------------------------------ #

    def render_statement(self, raw_statement: str) -> str:
        """
        Substitue les variables dans le \statement et retourne le HTML.
        Les \embed{replyN, size} sont transformés en <input> HTML.
        """
        # 1. Remplace les \embed avant la substitution des variables
        #    pour éviter que \e → "1" ne coupe "\embed" en "1mbed"
        html = self._render_embeds(raw_statement)
        # 2. Substitution des variables
        html = self._substitute_vars(html)
        # 3. Évalue les \if après substitution (les valeurs sont connues)
        html = self._render_if(html)
        # 4. Normalise les délimiteurs LaTeX : convention WIMS \(expr) → standard \(expr\)
        html = self._fix_wims_math_delimiters(html)
        # 5. Amélioration de l'affichage dans les blocs LaTeX
        html = self._prettify_latex(html)
        return html

    @staticmethod
    def _fix_wims_math_delimiters(html: str) -> str:
        """
        Convertit la convention WIMS \(expr) (fermé par ')' seul) vers \(expr\).
        Suit la profondeur des parenthèses pour trouver le ')' fermant du bloc.
        """
        result = []
        i = 0
        n = len(html)
        while i < n:
            if html[i:i+2] == r'\(':
                # Cherche le ')' fermant à profondeur 0, ou '\)' déjà correct
                j = i + 2
                depth = 0
                close_pos = -1
                while j < n:
                    if html[j:j+2] == r'\)':
                        # Déjà bien fermé, pas besoin de corriger
                        close_pos = -1
                        break
                    elif html[j] == '(':
                        depth += 1
                        j += 1
                    elif html[j] == ')':
                        if depth == 0:
                            close_pos = j
                            break
                        else:
                            depth -= 1
                            j += 1
                    else:
                        j += 1
                if close_pos >= 0:
                    # Remplace le ')' fermant par '\)'
                    result.append(html[i:close_pos])
                    result.append(r'\)')
                    i = close_pos + 1
                else:
                    result.append(html[i])
                    i += 1
            else:
                result.append(html[i])
                i += 1
        return ''.join(result)

    def _prettify_latex(self, html: str) -> str:
        """Améliore le rendu dans les blocs LaTeX : × au lieu de *, parenthèses autour des négatifs."""

        def process(expr: str) -> str:
            # * → \times
            expr = expr.replace('*', r'\times ')
            # Simplification des signes : +-2 → -2, --2 → +2
            expr = re.sub(r'\+\s*(-\d+(?:\.\d+)?)', r'\1', expr)
            expr = re.sub(r'-\s*(-\d+(?:\.\d+)?)', lambda m: '+' + m.group(1)[1:], expr)
            # +(-n) → -n,  -(-n) → +n  (nombre négatif entre parenthèses)
            expr = re.sub(r'\+\s*\((-\d+(?:\.\d+)?)\)', r'\1', expr)
            expr = re.sub(r'-\s*\((-\d+(?:\.\d+)?)\)', lambda m: '+' + m.group(1)[1:], expr)
            # Nombre négatif après \times : \times -2 → \times (-2)
            expr = re.sub(r'(\\times\s*)(-\d+(?:\.\d+)?)', r'\1(\2)', expr)
            # 1\times x → x  (coefficient 1 devant une lettre)
            expr = re.sub(r'(?<![0-9])1\\times\s*([a-zA-Z])', r'\1', expr)
            # n\times x → nx  (coefficient entier devant une lettre, pas de signe ×)
            expr = re.sub(r'(\d+)\\times\s*([a-zA-Z])', r'\1\2', expr)
            # )\times( → )( (pas de signe × entre deux parenthèses)
            expr = re.sub(r'\)\\times\s*\(', r')(', expr)
            # n\times( → n( (pas de signe × entre un nombre et une parenthèse)
            expr = re.sub(r'(\d)\\times\s*\(', r'\1(', expr)
            # -\times( → -( (pas de signe × après un signe moins et une parenthèse)
            expr = re.sub(r'(-)\s*\\times\s*\(', r'\1(', expr)
            return expr

        # Traite uniquement le contenu des blocs \(...\) et \[...\]
        html = re.sub(r'\\\((.*?)\\\)', lambda m: r'\(' + process(m.group(1)) + r'\)', html, flags=re.DOTALL)
        html = re.sub(r'\\\[(.*?)\\\]', lambda m: r'\[' + process(m.group(1)) + r'\]', html, flags=re.DOTALL)
        return html

    def _render_embeds(self, html: str) -> str:
        """Transforme \embed{replyN, size} en <input> ou slot clickfill HTML."""
        def make_input(m):
            args = [a.strip() for a in m.group(1).split(",")]
            name = args[0]
            size = args[1] if len(args) > 1 else "10"
            # Détecte le format clickfill : size contient 'x' (ex: "25x25x1")
            if 'x' in size:
                return f'<cf-slot name="{name}"></cf-slot>'
            try:
                width = int(size) * 10  # approximation px
            except ValueError:
                width = 100
            return f'<oef-input name="{name}" width="{width}"></oef-input>'
        return re.sub(r'\\embed\{([^}]+)\}', make_input, html)

    def _render_if(self, html: str) -> str:
        """
        Évalue les \if{cond}{vrai}{faux} dans le statement.
        Pour l'affichage initial, step=1.
        """
        ctx_with_step = dict(self.ctx)
        ctx_with_step.setdefault("step", "1")

        def eval_if(m):
            cond_raw = self._substitute_vars(m.group(1))
            cond_py = _oef_cond_to_py(cond_raw)
            try:
                cond = eval(
                    cond_py,
                    {"__builtins__": {}},
                    {k: _try_num(v) for k, v in ctx_with_step.items()}
                )
                return m.group(2) if cond else (m.group(3) if m.lastindex >= 3 else '')
            except Exception:
                return m.group(2)

        # Traite les \if imbriqués de l'extérieur vers l'intérieur
        # Supporte \if{cond}{vrai}{faux} et \if{cond}{vrai} (sans branche faux)
        pat_3 = re.compile(r'\\if\{([^{}]*)\}\{((?:[^{}]|\{[^{}]*\})*)\}\{((?:[^{}]|\{[^{}]*\})*)\}')
        pat_2 = re.compile(r'\\if\{([^{}]*)\}\{((?:[^{}]|\{[^{}]*\})*)\}')

        def eval_if2(m):
            cond_raw = self._substitute_vars(m.group(1))
            cond_py = _oef_cond_to_py(cond_raw)
            try:
                cond = eval(cond_py, {"__builtins__": {}},
                            {k: _try_num(v) for k, v in ctx_with_step.items()})
                return m.group(2) if cond else ''
            except Exception:
                return ''

        for _ in range(5):
            new_html = pat_3.sub(eval_if, html)
            new_html = pat_2.sub(eval_if2, new_html)
            if new_html == html:
                break
            html = new_html

        return html


def _apply_func_transform(expr: str, func_name: str, transform) -> str:
    """
    Pour chaque occurrence de func_name(...) dans expr,
    remplace par transform(contenu_intérieur).
    Gère les parenthèses imbriquées.
    """
    result = []
    i = 0
    n = len(expr)
    pattern = func_name + '('
    while i < n:
        idx = expr.find(pattern, i)
        if idx == -1:
            result.append(expr[i:])
            break
        result.append(expr[i:idx])
        start = idx + len(pattern)  # position après le (
        depth = 1
        j = start
        while j < n:
            if expr[j] == '(':
                depth += 1
            elif expr[j] == ')':
                depth -= 1
                if depth == 0:
                    inner = expr[start:j]
                    result.append(transform(inner))
                    i = j + 1
                    break
            j += 1
        else:
            result.append(expr[idx:])
            i = n
    return ''.join(result)


def _strip_function_call(expr: str, func_name: str, replacement: str | None = None) -> str:
    """
    Remplace func_name(...) par son contenu intérieur (ou replacement si fourni).
    Gère les parenthèses imbriquées.
    """
    result = []
    i = 0
    n = len(expr)
    pattern = func_name + '('
    while i < n:
        idx = expr.find(pattern, i)
        if idx == -1:
            result.append(expr[i:])
            break
        result.append(expr[i:idx])
        # Extrait le contenu entre les parenthèses
        start = idx + len(pattern) - 1  # position du (
        depth = 0
        j = start
        while j < n:
            if expr[j] == '(':
                depth += 1
            elif expr[j] == ')':
                depth -= 1
                if depth == 0:
                    inner = expr[start + 1:j]
                    if replacement is None:
                        result.append(inner)
                    else:
                        result.append(replacement)
                    i = j + 1
                    break
            j += 1
        else:
            # Pas de ) fermante — on laisse tel quel
            result.append(expr[idx:])
            i = n
    return ''.join(result)


def _oef_cond_to_py(cond: str) -> str:
    """Convertit une condition OEF en expression Python évaluable.
    - = → ==
    - <> → !=
    - expr= (rien à droite) → expr==''  (test d'égalité à vide)
    """
    # <> → !=
    cond = cond.replace('<>', '!=')
    # = → == (sauf !=, <=, >=, ==)
    cond = re.sub(r'(?<![!<>=])=(?!=)', '==', cond)
    # expr== sans rien à droite → expr==''
    cond = re.sub(r'==(\s*)$', r"==''\1", cond.strip())
    # =='' sans opérande gauche → ''==''
    cond = re.sub(r"^==", "''==", cond)
    return cond.replace('^', '**')


def _try_num(val: str):
    """Tente de convertir une chaîne en nombre pour les comparaisons."""
    try:
        return int(val)
    except (ValueError, TypeError):
        try:
            return float(val)
        except (ValueError, TypeError):
            return val
