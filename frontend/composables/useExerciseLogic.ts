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

export interface CodeEditorCode { lang: string; code: string; name: string; readonly: boolean }
export interface CodeEditorConfig {
  id: string
  themes: string[]
  fullscreen: boolean
  init: boolean
  instructions: string[]
  codes: CodeEditorCode[]
}

export interface BackendSegment {
  type: 'html' | 'input' | 'textarea' | 'slot' | 'menu' | 'correspond'
    | 'jsxgraph' | 'codeeditor' | 'group-open' | 'group-close' | 'radio-inline' | 'coord'
    | 'draw'
  content?: string
  name?: string
  size?: number
  rows?: number
  cols?: number
  label?: string
  is_sup?: boolean
  config?: CorrespondConfig | CodeEditorConfig
  index?: number
  width?: number
  height?: number
  maxw?: number
  minw?: number
  js?: string
  class?: string
  value?: string
  reply?: string
  image?: string
  svg?: string
  // `draw` : le type d'objet à tracer, sa couleur et les bornes du repère —
  // c'est en ses unités que la réponse est attendue, non en pixels. Le fond
  // passe par `image`/`svg`, comme celui de `coord`.
  objet?: string
  couleur?: string
  xrange?: string
  yrange?: string
  // HTML attributes carried by the extra lines of an `\embed` size parameter
  // (`\embed{reply 1,30 autofocus}`), allow-listed backend-side.
  attrs?: Record<string, string | boolean>
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
  | { type: 'input';       name: string; width: string; is_sup?: boolean; attrs?: Record<string, string | boolean> }
  | { type: 'textarea';    name: string; rows: number; cols: number; is_sup?: boolean; attrs?: Record<string, string | boolean> }
  | { type: 'menu';        name: string; label: string; is_sup?: boolean }
  | { type: 'correspond';  name: string; config: CorrespondConfig; is_sup?: boolean }
  | { type: 'jsxgraph';    name: string; js: string; width?: number; height?: number; maxw?: number; minw?: number; reply?: string }
  | { type: 'coord';       name: string; image: string; svg?: string; is_sup?: boolean }
  | { type: 'draw';        name: string; image: string; svg?: string; objet: string; couleur: string
                           xrange: string; yrange: string; width?: number; height?: number; is_sup?: boolean }
  | { type: 'codeeditor';  config: CodeEditorConfig; is_sup?: boolean }
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

// Languages whose decimal separator is a comma. Keep in sync with the backend
// source of truth, `backend/core/oef/i18n.py` (COMMA_DECIMAL_LANGS).
const COMMA_DECIMAL_LANGS = new Set(['fr', 'nl'])

// Localise a choice's *display* string: `0.3` → `0,3` in comma-decimal
// locales. Applied to the rendered label only — the `raw` value kept for
// answer matching stays dotted (clickfill encodes slots comma-separated, so a
// comma inside a value would corrupt both the separator and the comparison).
function localizeChoiceDisplay(s: string, lang: string): string {
  if (!COMMA_DECIMAL_LANGS.has((lang || 'fr').split('-')[0].toLowerCase())) return s
  // Uniquement le texte affiché : jamais l'intérieur d'une balise. Un choix
  // peut être une figure (`oefmolecule/lewis` propose des schémas de liaison
  // en SVG incorporé), et franciser ses coordonnées transformait
  // `points="20.00,33.33"` en `20,00,33,33` — quatre nombres au lieu de deux,
  // donc une ligne brisée en zigzag à la place du trait.
  return s
    .split(/(<[^>]*>)/)
    .map((part, i) => (i % 2 ? part : part.replace(/(?<=\d)\.(?=\d)/g, ',')))
    .join('')
}

export function useExerciseLogic() {
  const { renderMath } = useKatex()
  const apiBase = useRuntimeConfig().public.apiBase

  // Rewrite backend-relative /api/static URLs so images load from the
  // backend (not the frontend dev server) without needing a proxy.
  function prefixStaticUrls(html: string): string {
    // Le guillemet est facultatif : l'OEF écrit couramment `<img src=$val14>`
    // sans en mettre (les drapeaux d'`oefcountries`, via `!rename`).
    return html.replace(
      /(\ssrc=)(["']?)\/api\/static\//g,
      (_m, attr, quote) => `${attr}${quote}${apiBase}/api/static/`,
    )
  }

  async function buildSegments(backendSegments: BackendSegment[]): Promise<Segment[]> {
    const out: Segment[] = []
    for (const s of backendSegments) {
      if (s.type === 'html') {
        out.push({ type: 'html', content: prefixStaticUrls(await renderMath(s.content ?? '', { autoDisplay: true })) })
      } else if (s.type === 'input') {
        const size = s.size ?? 0
        out.push({ type: 'input', name: s.name ?? '', width: size > 0 ? `${size + 2}ch` : '10ch', is_sup: s.is_sup, attrs: s.attrs })
      } else if (s.type === 'textarea') {
        out.push({ type: 'textarea', name: s.name ?? '', rows: s.rows ?? 5, cols: s.cols ?? 30, is_sup: s.is_sup, attrs: s.attrs })
      } else if (s.type === 'slot') {
        out.push({ type: 'slot', name: s.name ?? '', is_sup: s.is_sup, index: s.index, width: s.width })
      } else if (s.type === 'menu') {
        out.push({ type: 'menu', name: s.name ?? '', label: s.label ?? '', is_sup: s.is_sup })
      } else if (s.type === 'correspond' && s.config) {
        // Les colonnes d'un `correspond` sont du HTML rendu tel quel par le
        // composant, donc hors du chemin des segments `html` : elles doivent
        // être préfixées ici (les colonnes d'images d'`oefcountries`).
        const cfg = s.config as CorrespondConfig
        out.push({
          type: 'correspond', name: s.name ?? '', is_sup: s.is_sup,
          config: {
            ...cfg,
            lefts: cfg.lefts.map(prefixStaticUrls),
            rights: cfg.rights.map(prefixStaticUrls),
          },
        })
      } else if (s.type === 'jsxgraph') {
        // The board JS is passed through untouched (NOT renderMath'd) — it
        // carries \(…\) labels that KaTeX would otherwise mangle.
        out.push({
          type: 'jsxgraph', name: s.name ?? '', js: s.js ?? '',
          width: s.width, height: s.height, maxw: s.maxw, minw: s.minw,
          reply: s.reply,
        })
      } else if (s.type === 'coord') {
        // Clickable repère: the SVG travels inline; fall back to the URL
        // (served by the backend, so prefix the relative /api/ path).
        const img = s.image ?? ''
        out.push({
          type: 'coord', name: s.name ?? '',
          image: img.startsWith('/api/') ? apiBase + img : img,
          svg: s.svg, is_sup: s.is_sup,
        })
      } else if (s.type === 'draw') {
        // Canevas `type=draw` : même traitement d'image que `coord` (le SVG
        // voyage en ligne, l'URL sert de repli et doit être préfixée).
        const imgd = s.image ?? ''
        out.push({
          type: 'draw', name: s.name ?? '',
          image: imgd.startsWith('/api/') ? apiBase + imgd : imgd,
          svg: s.svg, objet: s.objet ?? 'points', couleur: s.couleur ?? 'blue',
          xrange: s.xrange ?? '', yrange: s.yrange ?? '',
          width: s.width, height: s.height, is_sup: s.is_sup,
        })
      } else if (s.type === 'codeeditor' && s.config) {
        // Code + options are passed through untouched (NOT renderMath'd) — the
        // CodeMirror widget is built client-side from this config.
        out.push({ type: 'codeeditor', config: s.config as CodeEditorConfig, is_sup: s.is_sup })
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
    // `units`/`sigunits` answers ("7.7 m/s", "1.64e11 km^3") render verbatim —
    // otherwise slashToFrac would turn a unit's "/" into a LaTeX fraction.
    'units', 'unit', 'sigunits',
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

    // `raw` keeps the original (dotted) value for answer matching; `html` is
    // the localised display (comma decimals in comma-decimal locales).
    const disp = (c: string) => renderMath(localizeChoiceDisplay(c, rendered.lang))
    // Multi-slot clickfill: every slot (reply1…replyN) carries the *same* pool,
    // so the palette is the de-duplicated union — one card per distinct label,
    // not N copies.
    // Un `dragfill` (`options.single_use`) se compose au contraire par
    // concaténation, sans `!listuniq` (cf. `anstype/dragfill.after`) : chaque
    // étiquette ne servant qu'une fois, une réponse qui répète un même libellé
    // — un anagramme dont une lettre revient — a besoin d'autant de cartes.
    const seenClickfill = new Set<string>()
    for (const ans of rendered.answers) {
      if (ans.answer_type === 'clickfill' && ans.options.choices?.length) {
        const singleUse = !!ans.options.single_use
        for (const c of ans.options.choices) {
          if (!singleUse) {
            if (seenClickfill.has(c)) continue
            seenClickfill.add(c)
          }
          clickfillChoicesHtml.push({ raw: c, html: await disp(c) })
        }
      }
      if (ans.answer_type === 'radio' && ans.options.choices?.length) {
        radioChoicesHtml[ans.input_name] = []
        for (const c of ans.options.choices) {
          radioChoicesHtml[ans.input_name].push({ raw: c, html: await disp(c) })
        }
      }
      if (ans.answer_type === 'menu' && ans.options.choices?.length) {
        menuChoicesHtml[ans.input_name] = []
        for (const c of ans.options.choices) {
          menuChoicesHtml[ans.input_name].push({ raw: c, html: await disp(c) })
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
