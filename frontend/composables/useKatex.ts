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
  function decodeHtmlEntitiesForLatex(expr: string): string {
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

  // Compte les ``-`` empilés au début d'une expression numérique simple
  // (gère ``--``, ``-(-x)``, ``-x``). Renvoie [n_negs, body_sans_signes].
  function countLeadingNegs(s: string): [number, string] {
    s = s.trim()
    let n = 0
    while (true) {
      if (s.startsWith("--")) { n += 2; s = s.slice(2); continue }
      if (s.startsWith("-(-") && s.endsWith(")")) { n += 2; s = s.slice(3, -1).trim(); continue }
      if (s.startsWith("-(") && s.endsWith(")")) {
        // -(X) where X has its own potential signs: keep one neg and recurse on X
        const inner = s.slice(2, -1).trim()
        const [m, body] = countLeadingNegs(inner)
        return [n + 1 + m, body]
      }
      if (s.startsWith("-")) { n += 1; s = s.slice(1).trim(); break }
      break
    }
    return [n, s]
  }

  // Simplifie les signes ``-`` accumulés au numérateur et dénominateur d'une
  // ``\dfrac{a}{b}`` : ``\dfrac{-11}{-10}`` → ``\dfrac{11}{10}`` ;
  // ``\dfrac{-15}{-(-7)}`` → ``-\dfrac{15}{7}``.
  function simplifyFracSign(expr: string): string {
    return expr.replace(
      /\\dfrac\{([^{}]+)\}\{([^{}]+)\}/g,
      (_m, num, den) => {
        const [nNum, bodyNum] = countLeadingNegs(num)
        const [nDen, bodyDen] = countLeadingNegs(den)
        const total = nNum + nDen
        const sign = total % 2 === 1 ? "-" : ""
        return `${sign}\\dfrac{${bodyNum}}{${bodyDen}}`
      }
    )
  }

  // Retire les parenthèses inutiles autour d'une ``\dfrac`` : ``(\dfrac{a}{b})``
  // est visuellement déjà un bloc unique, les parens autour sont redondantes.
  function stripRedundantFracParens(expr: string): string {
    return expr.replace(
      /\((-?\\dfrac\{[^{}]+\}\{[^{}]+\})\)/g,
      (_m, frac) => frac
    )
  }

  // Normalise une expression OEF/SymPy en LaTeX : ** → ^, * → \times (croix),
  // sauf devant une lettre ou une parenthèse ouvrante où la multiplication
  // est implicite : 5*v → 5v, )*( → )(, mais 2*3 → 2 \times 3.
  function normalizeMath(expr: string): string {
    expr = decodeHtmlEntitiesForLatex(expr)
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
    expr = expr.replace(/^\s*\+\s*/, '')
    expr = expr.replace(/\s*\*\s*(?=[a-zA-Z(])/g, '')
    expr = expr.replace(/\s*\*\s*/g, ' \\times ')
    expr = slashToFrac(expr)
    expr = simplifyFracSign(expr)
    expr = stripRedundantFracParens(expr)
    expr = wrapNegativeOperands(expr)
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
