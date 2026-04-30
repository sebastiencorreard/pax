/**
 * Rendu des formules LaTeX avec KaTeX.
 * Remplace \(...\) et \[...\] dans le HTML de l'énoncé.
 */
export function useKatex() {
  async function renderMath(html: string): Promise<string> {
    if (!import.meta.client) return html

    const katex = await import('katex')

    // Remplace \[...\] par du rendu display
    html = html.replace(/\\\[([\s\S]*?)\\\]/g, (_, expr) => {
      try {
        return katex.default.renderToString(expr.trim(), { displayMode: true, throwOnError: false })
      } catch {
        return `<span class="text-red-500">[erreur LaTeX: ${expr}]</span>`
      }
    })

    // Remplace \(...\) par du rendu inline
    html = html.replace(/\\\(([\s\S]*?)\\\)/g, (_, expr) => {
      try {
        return katex.default.renderToString(expr.trim(), { displayMode: false, throwOnError: false })
      } catch {
        return `<span class="text-red-500">[erreur LaTeX: ${expr}]</span>`
      }
    })

    return html
  }

  return { renderMath }
}
