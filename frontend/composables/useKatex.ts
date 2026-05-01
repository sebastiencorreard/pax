/**
 * Rendu des formules LaTeX avec KaTeX.
 * Remplace \(...\) et \[...\] dans le HTML de l'énoncé.
 */
export function useKatex() {
  // Normalise une expression OEF/SymPy en LaTeX : ** → ^, * → \times (croix),
  // sauf devant une lettre ou une parenthèse ouvrante où la multiplication
  // est implicite : 5*v → 5v, )*( → )(, mais 2*3 → 2 \times 3.
  function normalizeMath(expr: string): string {
    expr = expr.replace(/\*\*/g, '^')
    expr = expr.replace(/\s*\*\s*(?=[a-zA-Z(])/g, '')
    expr = expr.replace(/\s*\*\s*/g, ' \\times ')
    return expr
  }

  async function renderMath(html: string): Promise<string> {
    if (!import.meta.client) return html

    const katex = await import('katex')

    // Remplace \[...\] par du rendu display
    html = html.replace(/\\\[([\s\S]*?)\\\]/g, (_, expr) => {
      try {
        return katex.default.renderToString(normalizeMath(expr.trim()), { displayMode: true, throwOnError: false })
      } catch {
        return `<span class="text-red-500">[erreur LaTeX: ${expr}]</span>`
      }
    })

    // Remplace \(...\) par du rendu inline
    html = html.replace(/\\\(([\s\S]*?)\\\)/g, (_, expr) => {
      try {
        return katex.default.renderToString(normalizeMath(expr.trim()), { displayMode: false, throwOnError: false })
      } catch {
        return `<span class="text-red-500">[erreur LaTeX: ${expr}]</span>`
      }
    })

    return html
  }

  return { renderMath }
}
