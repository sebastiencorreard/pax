import { ref, computed } from 'vue'

export interface AnswerDef {
  input_name: string
  label: string
  answer_type: string
  options: Record<string, any>
  weight: number
  logical_name: string
}

export interface BackendSegment {
  type: 'html' | 'input' | 'textarea' | 'slot' | 'menu'
  content?: string
  name?: string
  size?: number
  rows?: number
  cols?: number
  label?: string
  is_sup?: boolean
}

export interface Rendered {
  exercise_id: string
  title: string
  lang: string
  statement_segments: BackendSegment[]
  answers: AnswerDef[]
  hint_html: string
  seed: number
  condition: { label: string; expr: string } | null
  is_dynsteps: boolean
  current_step: number | null
  total_steps: number | null
  css: string | null
  exercise_type?: string
  type_meta?: Record<string, any>
}

export interface CheckResult {
  global_score: number
  results: Array<{
    input_name: string
    correct: boolean
    score: number
    method: string
    reply: string
    expected: string
    status: string
    detail?: string
  }>
  attempt_id: string
  has_invalid_format?: boolean
  noanalyzeprint?: boolean
  feedback_html?: string | null
  solution_html?: string | null
  debug_vars?: Record<string, string>
}

export type Segment =
  | { type: 'html';     content: string }
  | { type: 'slot';     name: string; is_sup?: boolean }
  | { type: 'input';    name: string; width: string; is_sup?: boolean }
  | { type: 'textarea'; name: string; rows: number; cols: number; is_sup?: boolean }
  | { type: 'menu';     name: string; label: string; is_sup?: boolean }

export function useExerciseLogic() {
  const { renderMath } = useKatex()
  const apiBase = useRuntimeConfig().public.apiBase

  // Rewrite backend-relative /api/static URLs so images load from the
  // backend (not the frontend dev server) without needing a proxy.
  function prefixStaticUrls(html: string): string {
    return html.replaceAll(' src="/api/static/', ` src="${apiBase}/api/static/`)
  }

  async function buildSegments(backendSegments: BackendSegment[]): Promise<Segment[]> {
    const out: Segment[] = []
    for (const s of backendSegments) {
      if (s.type === 'html') {
        out.push({ type: 'html', content: prefixStaticUrls(await renderMath(s.content ?? '')) })
      } else if (s.type === 'input') {
        const size = s.size ?? 0
        out.push({ type: 'input', name: s.name ?? '', width: size > 0 ? `${size + 2}ch` : '10ch', is_sup: s.is_sup })
      } else if (s.type === 'textarea') {
        out.push({ type: 'textarea', name: s.name ?? '', rows: s.rows ?? 5, cols: s.cols ?? 30, is_sup: s.is_sup })
      } else if (s.type === 'slot') {
        out.push({ type: 'slot', name: s.name ?? '', is_sup: s.is_sup })
      } else if (s.type === 'menu') {
        out.push({ type: 'menu', name: s.name ?? '', label: s.label ?? '', is_sup: s.is_sup })
      }
    }
    return out
  }

  function toLatex(expr: string): string {
    const sups: Record<string, string> = {'⁰':'0','¹':'1','²':'2','³':'3','⁴':'4','⁵':'5','⁶':'6','⁷':'7','⁸':'8','⁹':'9'}
    for (const [sup, digit] of Object.entries(sups)) {
      expr = expr.replaceAll(sup, `^${digit}`)
    }
    return expr
      .replace(/\*\*/g, '^')
      .replace(/\*/g, '')
      .replace(/\s+/g, '')
  }

  function isLatexString(s: string) {
    return s.startsWith('\\(') || s.startsWith('\\[')
  }

  async function renderValue(s: string): Promise<string> {
    if (!s) return '—'
    if (isLatexString(s)) return renderMath(s)
    return renderMath(`\\(${toLatex(s)}\\)`)
  }

  async function buildFeedbackHtml(checkResult: CheckResult | null): Promise<Record<string, { reply: string, expected: string }>> {
    if (!checkResult) return {}
    const result: Record<string, { reply: string, expected: string }> = {}
    for (const r of checkResult.results) {
      result[r.input_name] = {
        reply: await renderValue(r.reply),
        expected: await renderValue(r.expected),
      }
    }
    return result
  }

  async function prepareChoicesHtml(rendered: Rendered) {
    const clickfillChoicesHtml: Array<{ raw: string; html: string }> = []
    const radioChoicesHtml: Record<string, Array<{ raw: string; html: string }>> = {}
    const menuChoicesHtml: Record<string, Array<{ raw: string; html: string }>> = {}

    for (const ans of rendered.answers) {
      if (ans.answer_type === 'clickfill' && ans.options.choices?.length) {
        for (const c of ans.options.choices) {
          clickfillChoicesHtml.push({ raw: c, html: await renderMath(c) })
        }
      }
      if (ans.answer_type === 'radio' && ans.options.choices?.length) {
        radioChoicesHtml[ans.input_name] = []
        for (const c of ans.options.choices) {
          radioChoicesHtml[ans.input_name].push({ raw: c, html: await renderMath(c) })
        }
      }
      if (ans.answer_type === 'menu' && ans.options.choices?.length) {
        menuChoicesHtml[ans.input_name] = []
        for (const c of ans.options.choices) {
          menuChoicesHtml[ans.input_name].push({ raw: c, html: await renderMath(c) })
        }
      }
    }

    return { clickfillChoicesHtml, radioChoicesHtml, menuChoicesHtml }
  }

  return {
    buildSegments,
    toLatex,
    renderValue,
    buildFeedbackHtml,
    prepareChoicesHtml
  }
}
