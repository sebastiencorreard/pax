import { ref, computed } from 'vue'
import type { ComputedRef, InjectionKey, Ref } from 'vue'

// Shared context injected into the recursive StatementNodes renderer, so it
// can render leaf segments without prop-drilling through every layout group.
export interface PaxStatementCtx {
  replies: ComputedRef<Record<string, string>>
  updateReply: (name: string, value: string) => void
  clickfillChoicesHtml: ComputedRef<Array<{ raw: string; html: string }>>
  menuChoicesHtml: ComputedRef<Record<string, Array<{ raw: string; html: string }>>>
  submitted: ComputedRef<boolean>
  loading: ComputedRef<boolean>
  checkResult: ComputedRef<CheckResult | null>
  draggingChoice: Ref<string | null>
  pendingChoice: Ref<string | null>
  cfValue: (name: string, index: number) => string
  setCfSlot: (name: string, index: number, value: string) => void
  cfSlotState: (name: string, index: number) => '' | 'correct' | 'incorrect'
  inputClass: (name: string) => string
  onSubmit: () => void
}
export const PAX_STATEMENT_CTX: InjectionKey<PaxStatementCtx> = Symbol('paxStatementCtx')

export interface AnswerDef {
  input_name: string
  label: string
  answer_type: string
  options: Record<string, any>
  weight: number
  logical_name: string
}

export interface BackendSegment {
  type: 'html' | 'input' | 'textarea' | 'slot' | 'menu' | 'correspond'
  content?: string
  name?: string
  size?: number
  rows?: number
  cols?: number
  label?: string
  is_sup?: boolean
  config?: CorrespondConfig
  index?: number
  width?: number
  height?: number
  maxw?: number
  minw?: number
  js?: string
  class?: string
  value?: string
  reply?: string
}

export interface Chrono {
  soft: number       // T1 in seconds: the displayed countdown ends at 0 here
  hard: number       // T2 in seconds: score is zero past this — not displayed
  started_at: string // ISO 8601 UTC, the server's elapsed-time anchor
  server_now: string // server's clock at render time — for skew correction
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
  chrono?: Chrono | null
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

export interface CorrespondConfig {
  lefts: string[]
  rights: string[]
  sizev: number
  sizeh1: number
  sizeh2: number
  partial: boolean
}

export type Segment =
  | { type: 'html';        content: string }
  | { type: 'slot';        name: string; is_sup?: boolean; index?: number; width?: number }
  | { type: 'input';       name: string; width: string; is_sup?: boolean }
  | { type: 'textarea';    name: string; rows: number; cols: number; is_sup?: boolean }
  | { type: 'menu';        name: string; label: string; is_sup?: boolean }
  | { type: 'correspond';  name: string; config: CorrespondConfig; is_sup?: boolean }
  | { type: 'jsxgraph';    name: string; js: string; width?: number; height?: number; maxw?: number; minw?: number; reply?: string }
  | { type: 'group-open';  class: string }
  | { type: 'group-close' }
  | { type: 'radio-inline'; name: string; value: string; content: string }

// A statement rendered as a tree: leaf segments or layout groups with children.
export type SegmentNode =
  | { kind: 'leaf'; seg: Segment }
  | { kind: 'group'; class: string; children: SegmentNode[] }

// Fold a flat segment list (with group-open/group-close markers) into a tree.
export function buildSegmentTree(segments: Segment[]): SegmentNode[] {
  const root: SegmentNode[] = []
  const stack: SegmentNode[][] = [root]
  const groups: { kind: 'group'; class: string; children: SegmentNode[] }[] = []
  for (const seg of segments) {
    if (seg.type === 'group-open') {
      const node = { kind: 'group' as const, class: seg.class, children: [] }
      stack[stack.length - 1].push(node)
      groups.push(node)
      stack.push(node.children)
    } else if (seg.type === 'group-close') {
      if (stack.length > 1) { stack.pop(); groups.pop() }
    } else {
      stack[stack.length - 1].push({ kind: 'leaf', seg })
    }
  }
  return root
}

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
        out.push({ type: 'html', content: prefixStaticUrls(await renderMath(s.content ?? '', { autoDisplay: true })) })
      } else if (s.type === 'input') {
        const size = s.size ?? 0
        out.push({ type: 'input', name: s.name ?? '', width: size > 0 ? `${size + 2}ch` : '10ch', is_sup: s.is_sup })
      } else if (s.type === 'textarea') {
        out.push({ type: 'textarea', name: s.name ?? '', rows: s.rows ?? 5, cols: s.cols ?? 30, is_sup: s.is_sup })
      } else if (s.type === 'slot') {
        out.push({ type: 'slot', name: s.name ?? '', is_sup: s.is_sup, index: s.index, width: s.width })
      } else if (s.type === 'menu') {
        out.push({ type: 'menu', name: s.name ?? '', label: s.label ?? '', is_sup: s.is_sup })
      } else if (s.type === 'correspond' && s.config) {
        out.push({ type: 'correspond', name: s.name ?? '', config: s.config, is_sup: s.is_sup })
      } else if (s.type === 'jsxgraph') {
        // The board JS is passed through untouched (NOT renderMath'd) — it
        // carries \(…\) labels that KaTeX would otherwise mangle.
        out.push({
          type: 'jsxgraph', name: s.name ?? '', js: s.js ?? '',
          width: s.width, height: s.height, maxw: s.maxw, minw: s.minw,
          reply: s.reply,
        })
      } else if (s.type === 'group-open') {
        out.push({ type: 'group-open', class: s.class ?? '' })
      } else if (s.type === 'group-close') {
        out.push({ type: 'group-close' })
      } else if (s.type === 'radio-inline') {
        // The label is math (a function def); KaTeX-render it now.
        out.push({
          type: 'radio-inline', name: s.name ?? '', value: s.value ?? '',
          content: await renderMath(s.content ?? ''),
        })
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

  // Answer types whose reply/expected is free text (or author-delimited HTML),
  // not a bare math expression. For these we must NOT wrap the whole value in
  // \(...\): a choice like "Infinie périodique" would otherwise be rendered as
  // italic math (spaces stripped → "Infiniepériodique"). renderMath still
  // renders any \(...\) the author embedded inside the choice text.
  const TEXT_ANSWER_TYPES = new Set([
    'radio', 'menu', 'checkbox', 'mark', 'correspond', 'clickfill',
    'atext', 'text', 'nocase', 'case', 'raw',
  ])

  async function renderValue(s: string, answerType?: string): Promise<string> {
    if (!s) return '—'
    if (isLatexString(s)) return renderMath(s)
    if (answerType && TEXT_ANSWER_TYPES.has(answerType.toLowerCase())) {
      // Text/choice answer: render as-is; only embedded \(...\) becomes math.
      return renderMath(s)
    }
    return renderMath(`\\(${toLatex(s)}\\)`)
  }

  async function buildFeedbackHtml(
    checkResult: CheckResult | null,
    answerTypes?: Record<string, string>,
  ): Promise<Record<string, { reply: string, expected: string }>> {
    if (!checkResult) return {}
    const result: Record<string, { reply: string, expected: string }> = {}
    for (const r of checkResult.results) {
      const t = answerTypes?.[r.input_name]
      result[r.input_name] = {
        reply: await renderValue(r.reply, t),
        expected: await renderValue(r.expected, t),
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
