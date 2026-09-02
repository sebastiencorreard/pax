/**
 * Rendu des formules LaTeX avec KaTeX.
 * Remplace \(...\) et \[...\] dans le HTML de l'énoncé.
 */
export function useKatex() {
  // Decode HTML entities that may appear inside \(...\), escaping LaTeX
  // active characters (% & # $ _ { }) so KaTeX doesn't treat them as syntax.
  // WIMS exercises encode literal symbols via entities specifically to avoid
  // collision with LaTeX commands — we have to undo that one level down.
  const LATEX_ESCAPE = new Set(['%', '&', '#', '$', '_', '{', '}'])
  // Named HTML entities WIMS authors drop straight into `\(…\)` for relation /
  // set symbols (e.g. `\(f(x)&le; 2\)`). KaTeX can't read `&le;` (the bare `&`
  // is an alignment char) and renders it as a red error, so map each to its
  // LaTeX command. Trailing space keeps the command token from gluing onto the
  // next char (`\le2` → `\le 2`).
  const NAMED_ENTITY_LATEX: Record<string, string> = {
    le: '\\le ', ge: '\\ge ', ne: '\\ne ', infin: '\\infty ',
    cup: '\\cup ', cap: '\\cap ', empty: '\\emptyset ', isin: '\\in ',
    notin: '\\notin ', times: '\\times ', sdot: '\\cdot ', minus: '-',
    plusmn: '\\pm ', rarr: '\\to ', larr: '\\leftarrow ', harr: '\\leftrightarrow ',
    forall: '\\forall ', exist: '\\exists ', radic: '\\sqrt ', prop: '\\propto ',
  }
  function decodeHtmlEntitiesForLatex(expr: string): string {
    expr = expr.replace(/&([a-zA-Z]+);/g, (m, name) =>
      Object.prototype.hasOwnProperty.call(NAMED_ENTITY_LATEX, name)
        ? NAMED_ENTITY_LATEX[name]
        : m,
    )
    expr = expr.replace(/&#(\d+);/g, (_, code) => {
      const ch = String.fromCharCode(Number(code))
      return LATEX_ESCAPE.has(ch) ? '\\' + ch : ch
    })
    expr = expr.replace(/&#x([0-9a-fA-F]+);/g, (_, code) => {
      const ch = String.fromCharCode(parseInt(code, 16))
      return LATEX_ESCAPE.has(ch) ? '\\' + ch : ch
    })
    expr = expr.replace(/&nbsp;/g, '~')  // ~ = non-breaking space in LaTeX
    expr = expr.replace(/&amp;/g, '\\&')
    expr = expr.replace(/&lt;/g, '<').replace(/&gt;/g, '>')
    return expr
  }

  // Convertit les divisions plates ``a/b`` en fraction empilée ``\dfrac{a}{b}``
  // (comportement WIMS standard). ``a`` et ``b`` peuvent être :
  //   - un nombre (avec décimale, signe éventuel)
  //   - un identifiant simple (variable)
  //   - une expression entre parenthèses
  // Les divisions plus complexes (déjà dans \frac, ou avec opérateurs
  // imbriqués) sont laissées au LaTeX existant.
  function slashToFrac(expr: string): string {
    const atom = String.raw`-{0,2}(?:\([^()]*\)|\d+(?:\.\d+)?|[A-Za-z_]\w*)`
    // Lookbehind ``(?<!\^)``: don't pull the numerator out of an exponent —
    // e.g. ``x^2/2`` is ``(x²)/2``, not ``x^(2/2)``. Without it, the atom
    // ``2`` after ``^`` is treated as the numerator and \dfrac eats the
    // whole exponent slot.
    const re = new RegExp(`(?<!\\^)(${atom})\\s*/\\s*(${atom})`)
    // Une seule passe : le résultat ``\dfrac{…}{…}`` ne re-match plus le pattern.
    let prev: string
    do {
      prev = expr
      expr = expr.replace(re, (_m, a, b) => `\\dfrac{${a}}{${b}}`)
    } while (expr !== prev)
    return expr
  }

  // Promeut ``\frac`` en ``\dfrac`` (displaystyle). KaTeX rend ``\frac`` en
  // *textstyle* (petite fraction écrasée) dans un ``\(…\)`` inline, alors que
  // WIMS empile toujours les fractions en taille normale. Le backend émet du
  // ``\frac`` via ``sympy.latex`` (ex. ``\(\frac{3}{4}\)``) ; on l'aligne sur le
  // ``\dfrac`` que ``slashToFrac`` produit déjà pour les divisions plates
  // ``a/b``. La lookbehind ``(?<![\^_])`` épargne les fractions en exposant /
  // indice (``x^\frac{1}{2}``) qui doivent rester petites ; ``\dfrac``/``\tfrac``
  // ne matchent pas (le ``\`` y est suivi de ``d``/``t``, pas de ``f``).
  function fracToDfrac(expr: string): string {
    return expr.replace(/(?<![\^_])\\frac(?![a-zA-Z])/g, '\\dfrac')
  }

  // Enroule "-N" entre parenthèses quand il suit un opérateur binaire
  // (``+``, ``-``, ``\times``) : ``17 - -9`` → ``17 - (-9)``, ``a \times -9``
  // → ``a \times (-9)``. Évite la confusion visuelle des deux signes ``-``
  // consécutifs. Ne touche pas aux ``-`` à l'intérieur d'accolades LaTeX
  // (notamment ``\dfrac{…}{-9}``) car le bloc ``{}`` n'expose pas d'opérateur
  // binaire visible.
  function wrapNegativeOperands(expr: string): string {
    return expr.replace(
      /([+\-]|\\times)(\s*)-(\d+(?:\.\d+)?|[A-Za-z_]\w*|\([^()]*\))/g,
      (_m, op, sp, operand) => `${op}${sp}(-${operand})`
    )
  }

  // Le signe d'une fraction **reste où l'auteur l'a mis**. On a longtemps
  // « simplifié » ici : ``\dfrac{-11}{6}`` devenait ``-\dfrac{11}{6}``, et
  // ``\dfrac{-4}{-4}`` devenait ``\dfrac{4}{4}``. Deux raisons de ne plus le
  // faire, l'une de fidélité, l'autre plus grave :
  //
  //   - WIMS rend ce que le `.def` émet, sans déplacer le signe. Sorti du
  //     numérateur, il produisait des ``- -`` disgracieux :
  //     ``rational.fr/sommesimple1`` affichait ``A = -\dfrac{6}{4} - -\dfrac{10}{6}``
  //     là où WIMS écrit ``\dfrac{-2}{2} - \dfrac{4}{2}``.
  //   - Simplifier ``\dfrac{-4}{-4}`` en ``\dfrac{4}{4}`` **donne une partie
  //     de la réponse** : dans ``rational.fr/quotient1``, ``11 \div \dfrac{-4}{-4}``
  //     attend ``11``, et reconnaître que deux négatifs s'annulent *est*
  //     l'exercice.
  //
  // La fonction invoquait des formes à signes doublés (``\dfrac{-15}{-(-7)}``,
  // ``--``) : mesuré sur les 4278 exercices et trois graines, le corpus n'en
  // produit **aucune**, ni dans un `\frac` du backend ni dans une division
  // plate que ``slashToFrac`` empile. Elle ne faisait donc que déplacer des
  // signes légitimes — 648 numérateurs sur 116 exercices, 208 dénominateurs
  // sur 71, et 59 fractions doublement signées sur 27.

  // Retire les parenthèses inutiles autour d'une ``\dfrac`` : ``(\dfrac{a}{b})``
  // est visuellement déjà un bloc unique, les parens autour sont redondantes.
  function stripRedundantFracParens(expr: string): string {
    return expr.replace(
      /\((-?\\dfrac\{[^{}]+\}\{[^{}]+\})\)/g,
      (_m, frac) => frac
    )
  }

  // Virgule décimale : entre deux chiffres, ``,`` est le séparateur décimal
  // (``2,95``), pas une ponctuation. KaTeX, lui, traite ``,`` comme une
  // ponctuation math et ajoute une espace fine après — d'où le rendu fautif
  // « 2, 95 ». On l'enrobe en ``{,}`` (atome ordinaire, sans espace), solution
  // LaTeX standard pour les décimales (cf. paquet ``icomma``). Le backend émet
  // déjà la virgule selon la locale ; les couples/ensembles des locales à
  // virgule usent du ``;`` comme séparateur, donc un chiffre-virgule-chiffre est
  // ici sans ambiguïté une décimale, quelle que soit la langue.
  function decimalComma(expr: string): string {
    return expr.replace(/(\d)\s*,\s*(\d)/g, '$1{,}$2')
  }

  // Normalise une expression OEF/SymPy en LaTeX : ** → ^, * → \times (croix),
  // sauf devant une lettre ou une parenthèse ouvrante où la multiplication
  // est implicite : 5*v → 5v, )*( → )(, mais 2*3 → 2 \times 3.
  // WIMS matrix notation. In WIMS math (texmath.c, t_onefactor) a bracket
  // group `[…]` that contains a top-level ';' or ',' is a matrix: ';' starts a
  // new row, ',' a new column. A column vector `\([7;5]\)` thus typesets as a
  // 2×1 pmatrix — exactly what e.g. the H3 quizz "vecteurs colinéaires"
  // question expects. Bracket groups without a top-level separator are left
  // as ordinary delimiters. ',' / ';' nested in inner ()/[]/{} are part of a
  // cell, never separators (matches WIMS' nesting-aware find_matching).
  function matchingBracket(s: string, start: number, close: string): number {
    let paren = 0, brak = 0, brace = 0
    for (let i = start; i < s.length; i++) {
      const ch = s[i]
      if (ch === '[') brak++
      else if (ch === ']') brak--
      else if (ch === '(') paren++
      else if (ch === ')') paren--
      else if (ch === '{') brace++
      else if (ch === '}') brace--
      else continue
      if (paren < 0 || brak < 0 || brace < 0)
        return (ch === close && paren <= 0 && brak <= 0 && brace <= 0) ? i : -1
    }
    return -1
  }
  function splitTopLevel(s: string, sep: string): string[] {
    const parts: string[] = []
    let paren = 0, brak = 0, brace = 0, start = 0
    for (let i = 0; i < s.length; i++) {
      const ch = s[i]
      if (ch === '(') paren++
      else if (ch === ')') paren--
      else if (ch === '[') brak++
      else if (ch === ']') brak--
      else if (ch === '{') brace++
      else if (ch === '}') brace--
      else if (ch === sep && paren === 0 && brak === 0 && brace === 0) {
        parts.push(s.slice(start, i)); start = i + 1
      }
    }
    parts.push(s.slice(start))
    return parts
  }
  // Only a *standalone* bracket (the whole math span) is a vector/matrix —
  // `\([7;5]\)`. A bracket embedded in a larger expression is interval/list
  // notation and stays literal: `\(x \in [2;5]\)` (French interval, quizz 1222).
  // KaTeX never reads `[a;b]` as a matrix on its own, so leaving it is correct.
  function wimsMatrix(expr: string): string {
    const s = expr.trim()
    if (!(s.startsWith('[') && s.endsWith(']'))) return expr
    if (matchingBracket(s, 1, ']') !== s.length - 1) return expr  // not a single group
    const inner = s.slice(1, -1)
    const rows = splitTopLevel(inner, ';')
    if (rows.length <= 1 && splitTopLevel(inner, ',').length <= 1) return expr
    const body = rows
      .map(row => splitTopLevel(row, ',').map(c => wimsMatrix(c.trim())).join(' & '))
      .join(' \\\\ ')
    return `\\begin{pmatrix}${body}\\end{pmatrix}`
  }

  function normalizeMath(expr: string): string {
    expr = decodeHtmlEntitiesForLatex(expr)
    // WIMS matrix brackets → pmatrix. Run early so column-separator commas are
    // consumed here, before decimalComma would touch a `\d,\d` pair.
    expr = wimsMatrix(expr)
    // Drop a stray backslash before a lone lowercase variable, e.g. WIMS's
    // `\(\x^2\)` → `x^2`. The lookahead `(?![a-zA-Z])` spares real commands
    // (`\frac`, `\sqrt`, `\left`…), and limiting to lowercase spares the valid
    // single-letter commands `\S` (§) / `\P` (¶). Without this KaTeX renders
    // the unknown `\x` as red error text.
    expr = expr.replace(/\\([a-z])(?![a-zA-Z])/g, '$1')
    expr = expr.replace(/\*\*/g, '^')
    // Remove spurious sign combinations produced by WIMS string concatenation
    expr = expr.replace(/\+-/g, '-').replace(/-\+/g, '-')
    // Strip a leading '+' that may appear when the first term is positive
    // (`+5x` → `5x`). Exception : le `+` isolé suivi de `\phantom` est un
    // OPÉRATEUR de séparation de termes (WIMS émet `\(\signe\phantom{ }\)` entre
    // deux termes d'une somme, cf. factorisat) — le retirer le rend invisible.
    expr = expr.replace(/^\s*\+\s*(?!\\phantom)/, '')
    expr = expr.replace(/\s*\*\s*(?=[a-zA-Z(])/g, '')
    expr = expr.replace(/\s*\*\s*/g, ' \\times ')
    expr = slashToFrac(expr)
    expr = fracToDfrac(expr)
    expr = stripRedundantFracParens(expr)
    expr = wrapNegativeOperands(expr)
    expr = decimalComma(expr)
    return expr
  }

  // WIMS blackboard-bold shortcuts (\RR, \NN, …) that KaTeX doesn't know
  // out of the box — without them an `\insmath \RR` rendered as a red
  // "[erreur LaTeX]". Mapped to \mathbb{} so ℝ/ℕ/ℤ/… typeset correctly.
  const KATEX_MACROS: Record<string, string> = {
    '\\RR': '\\mathbb{R}',
    '\\NN': '\\mathbb{N}',
    '\\ZZ': '\\mathbb{Z}',
    '\\QQ': '\\mathbb{Q}',
    '\\CC': '\\mathbb{C}',
    '\\DD': '\\mathbb{D}',
    '\\KK': '\\mathbb{K}',
    '\\PP': '\\mathbb{P}',
  }

  // Un `\(…\)` est "seul sur sa ligne" si, entre les deux <br> (ou les bords de
  // la chaîne) qui l'encadrent, il ne reste — une fois retirés les autres blocs
  // math, les balises HTML, les entités et les espaces — aucune lettre ni
  // chiffre. Autrement dit : la ligne ne contient que cette formule, pas de
  // texte. Sert à promouvoir une formule isolée en rendu "display" (centré).
  function isAloneOnLine(s: string, start: number, end: number): boolean {
    const brRe = /<br\s*\/?>/gi
    let lineStart = 0
    let m: RegExpExecArray | null
    while ((m = brRe.exec(s)) !== null) {
      if (m.index + m[0].length <= start) lineStart = m.index + m[0].length
      else break
    }
    const after = /<br\s*\/?>/i.exec(s.slice(end))
    const lineEnd = after ? end + after.index : s.length
    const rest = (s.slice(lineStart, start) + s.slice(end, lineEnd))
      .replace(/\\\([\s\S]*?\\\)/g, '')        // autres formules inline
      .replace(/\\\[[\s\S]*?\\\]/g, '')        // formules display
      .replace(/<[^>]*>/g, '')                 // balises (dont spans KaTeX déjà rendus)
      .replace(/&[a-zA-Z]+;|&#\d+;|&#x[0-9a-fA-F]+;/g, '')  // entités (&nbsp;, …)
    return !/[A-Za-z0-9]/.test(rest)
  }

  // `autoDisplay` (énoncés/solutions/indices) : un `\(…\)` seul sur sa ligne est
  // rendu en *displaystyle* (grosses fractions/opérateurs) MAIS reste dans le
  // flux (inline, pas un bloc centré), pour qu'un champ de réponse puisse le
  // suivre sur la même ligne. On obtient ça avec `\displaystyle` + displayMode
  // false ; `displayMode:true` (réservé à `\[…\]`) forcerait un bloc à la ligne.
  // Les formules mêlées à du texte restent en textstyle. Désactivé par défaut
  // pour ne pas affecter les contextes inline (labels, choix, correspondance…).
  async function renderMath(html: string, opts: { autoDisplay?: boolean } = {}): Promise<string> {
    if (!import.meta.client) return html

    const katex = await import('katex')
    const render = (expr: string, { block = false, big = false } = {}) => {
      try {
        const tex = (big ? '\\displaystyle ' : '') + normalizeMath(expr.trim())
        return katex.default.renderToString(tex, { displayMode: block, throwOnError: false, macros: KATEX_MACROS })
      } catch {
        return `<span class="text-red-500">[erreur LaTeX: ${expr}]</span>`
      }
    }

    // \[...\] → vrai display (bloc centré)
    html = html.replace(/\\\[([\s\S]*?)\\\]/g, (_, expr) => render(expr, { block: true }))

    // \(...\) → displaystyle inline si seul sur sa ligne (et autoDisplay actif),
    // sinon inline textstyle
    html = html.replace(/\\\(([\s\S]*?)\\\)/g, (match, expr, offset: number, s: string) =>
      render(expr, { big: !!opts.autoDisplay && isAloneOnLine(s, offset, offset + match.length) }),
    )

    return html
  }

  return { renderMath }
}
