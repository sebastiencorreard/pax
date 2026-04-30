<template>
  <div class="rounded-xl border shadow-sm overflow-hidden"
       style="background:var(--color-surface);border-color:var(--color-border)">

    <!-- Pièces volantes -->
    <span v-for="c in flyingCoins" :key="c.id"
          class="flying-coin"
          :style="{ left: c.x + 'px', top: c.y + 'px' }">🪙</span>

    <!-- En-tête -->
    <div class="px-6 py-4 border-b flex items-center justify-between"
         style="border-color:var(--color-border)">
      <h2 class="font-semibold text-lg" v-html="titleHtml || rendered?.title || $t('exercise.loading')"></h2>
      <div class="flex items-center gap-2">
        <span class="text-xs px-2 py-1 rounded font-semibold"
              style="background:var(--color-bg);color:#b45309"
              :title="$t('exercise.coins_title')">
          🪙 {{ formatCoins(coins) }}
        </span>
        <span class="text-xs px-2 py-1 rounded"
              style="background:var(--color-bg);color:var(--color-text-muted)">
          {{ $t('exercise.seed_label') }}: {{ rendered?.seed }}
        </span>
        <button @click="reload" :disabled="loading"
                class="text-xs px-3 py-1.5 rounded border transition"
                style="border-color:var(--color-border)"
                :title="$t('exercise.new_statement')">
          🔄 {{ $t('exercise.new_statement') }}
        </button>
      </div>
    </div>

    <!-- Énoncé -->
    <div class="px-6 py-6">
      <div v-if="loadError" class="text-red-500 text-sm p-2 border border-red-300 rounded">
        Erreur : {{ loadError }}
      </div>

      <div v-if="loading" class="animate-pulse space-y-3">
        <div class="h-4 rounded" style="background:var(--color-border);width:80%"></div>
        <div class="h-4 rounded" style="background:var(--color-border);width:60%"></div>
        <div class="h-8 rounded" style="background:var(--color-border);width:40%"></div>
      </div>

      <div v-else-if="rendered" ref="statementEl"
           class="oef-statement"
           @keydown.enter.prevent="() => { if (!submitted && !loading) submit() }">
        <template v-for="(seg, i) in statementSegments" :key="i">
          <span v-if="seg.type === 'html'" v-html="seg.content"></span>
          <ExerciseCfSlot v-else-if="seg.type === 'slot'"
            :name="seg.name"
            :value="replies[seg.name] || ''"
            :choices-html="clickfillChoicesHtml"
            :dragging="draggingChoice"
            :pending="pendingChoice"
            :submitted="submitted"
            @place="(name, val) => { replies[name] = val; pendingChoice = null }"
            @clear="(name) => { replies[name] = '' }"
          />
          <input v-else-if="seg.type === 'input'"
            type="text"
            :name="seg.name"
            v-model="replies[seg.name]"
            :style="{ width: seg.width + 'px', minWidth: '6ch' }"
            :disabled="submitted"
            :class="inputClass(seg.name)"
            autocomplete="off"
            @dragover.prevent
            @drop.prevent
            @keydown.enter.prevent="() => { if (!submitted && !loading) submit() }"
          />

        </template>
      </div>
    </div>

    <!-- Palette clickfill -->
    <div v-if="rendered && hasClickfill && !submitted" class="px-6 pb-4">
      <p class="text-xs mb-2" style="color:var(--color-text-muted)">
        {{ $t('exercise.drag_hint') }}
      </p>
      <div class="flex gap-2 flex-wrap">
        <div v-for="choice in clickfillChoicesHtml" :key="choice.raw"
             draggable="true"
             @dragstart="e => { e.dataTransfer!.setData('text/plain', choice.raw); draggingChoice = choice.raw }"
             @dragend="draggingChoice = null"
             @click="pendingChoice = (pendingChoice === choice.raw ? null : choice.raw)"
             class="px-4 py-2 rounded-lg border font-medium transition cursor-grab select-none"
             :class="choice.raw === pendingChoice
               ? 'border-blue-500 bg-blue-50 dark:bg-blue-900/30'
               : 'hover:border-blue-400 hover:bg-blue-50 dark:hover:bg-blue-900/10'"
             style="border-color:var(--color-border);min-width:3rem;text-align:center"
             v-html="choice.html">
        </div>
      </div>
    </div>

    <!-- Zone de réponse (pour les radio) -->
    <div v-if="rendered && hasRadioAnswers" class="px-6 pb-4 space-y-2">
      <div v-for="ans in rendered.answers" :key="ans.input_name">
        <template v-if="ans.answer_type === 'radio' && ans.options.choices">
          <p class="text-sm font-medium mb-2" style="color:var(--color-text-muted)">
            {{ ans.label || $t('exercise.choose_answer') }}
          </p>
          <div class="space-y-2">
            <label v-for="choice in ans.options.choices" :key="choice"
                   class="flex items-center gap-3 px-4 py-3 rounded-lg border cursor-pointer transition"
                   :class="radioClass(ans.input_name, choice)"
                   style="border-color:var(--color-border)">
              <input type="radio" :name="ans.input_name" :value="choice"
                     v-model="replies[ans.input_name]"
                     :disabled="submitted" class="accent-blue-500" />
              <span v-html="choice"></span>
            </label>
          </div>
        </template>
      </div>
    </div>

    <!-- Résultats -->
    <div v-if="checkResult" class="px-6 pb-4">
      <div class="rounded-lg px-4 py-3 border"
           :style="checkResult.global_score === 1
             ? 'border-color:var(--color-success);background:color-mix(in srgb, var(--color-success) 10%, transparent)'
             : checkResult.global_score === 0
               ? 'border-color:var(--color-error);background:color-mix(in srgb, var(--color-error) 10%, transparent)'
               : 'border-color:#d97706;background:color-mix(in srgb, #f59e0b 10%, transparent)'">
        <div class="font-semibold text-lg mb-2">
          <template v-if="checkResult.global_score === 1">{{ $t('feedback.correct') }}</template>
          <template v-else-if="checkResult.global_score === 0">{{ $t('feedback.incorrect') }}</template>
          <template v-else>
            {{ checkResult.results.filter(r => !r.correct).length === 1 ? $t('feedback.one_error') : $t('feedback.many_errors') }}
          </template>
          <span ref="scoreEl" class="font-normal text-sm ml-2">
            {{ $t('feedback.score', { pct: Math.round(checkResult.global_score * 100) }) }}
          </span>
        </div>
        <div class="text-sm space-y-1 mt-1">
          <div v-for="(r, i) in checkResult.results" :key="r.input_name"
               class="flex items-baseline gap-2 flex-wrap">
            <span style="color:var(--color-text-muted)">{{ $t('feedback.index', { n: i + 1 }) }}</span>
            <span v-html="feedbackHtml[r.input_name]?.reply"></span>
            <span v-if="r.correct" style="color:var(--color-success)">{{ $t('feedback.good') }}</span>
            <template v-else>
              <span style="color:var(--color-error)">{{ $t('feedback.bad') }}</span>
              <span style="color:var(--color-text-muted)">{{ $t('feedback.expected') }}</span>
              <span v-html="feedbackHtml[r.input_name]?.expected"></span>
              <span>.</span>
            </template>
          </div>
        </div>
      </div>
    </div>

    <!-- Boutons -->
    <div class="px-6 pb-6 flex items-center gap-3">
      <button @click="submit" :disabled="loading || submitted || !allFilled"
              class="px-6 py-2.5 rounded-lg font-medium transition disabled:opacity-60"
              style="background:var(--color-primary);color:#fff">
        {{ submitted ? $t('exercise.corrected') : $t('exercise.verify') }}
      </button>

      <button v-if="submitted" @click="reload"
              class="px-6 py-2.5 rounded-lg font-medium border transition"
              style="border-color:var(--color-border)">
        {{ $t('exercise.new_exercise') }}
      </button>

      <button v-if="rendered?.hint_html" @click="showHint = !showHint"
              class="px-4 py-2.5 rounded-lg text-sm border transition"
              style="border-color:var(--color-border);color:var(--color-text-muted)">
        {{ showHint ? $t('exercise.hint_hide') : $t('exercise.hint_show') }}
      </button>
    </div>

    <!-- Indice -->
    <div v-if="showHint && rendered?.hint_html"
         class="mx-6 mb-6 px-4 py-3 rounded-lg border text-sm"
         style="border-color:var(--color-border);background:var(--color-bg)"
         v-html="hintHtml">
    </div>
  </div>
</template>

<script setup lang="ts">
const props = defineProps<{ exerciseId: number }>()

const { apiFetch } = useApi()
const { renderMath } = useKatex()

interface AnswerDef {
  input_name: string
  label: string
  answer_type: string
  options: Record<string, any>
  weight: number
  logical_name: string
}

interface Rendered {
  exercise_id: number
  title: string
  lang: string
  statement_html: string
  answers: AnswerDef[]
  hint_html: string
  seed: number
  condition: { label: string; expr: string } | null
}

interface CheckResult {
  global_score: number
  results: Array<{
    input_name: string
    correct: boolean
    score: number
    method: string
    reply: string
    expected: string
  }>
  attempt_id: string
}

const shaking = ref(false)
const scoreEl = ref<HTMLElement | null>(null)

// Système de pièces
const coins = ref<number>(parseInt(localStorage.getItem('pax-coins') ?? '0'))
watch(coins, v => localStorage.setItem('pax-coins', String(v)))

function formatCoins(n: number): string {
  if (n >= 1_000_000) return (n / 1_000_000).toFixed(1).replace(/\.0$/, '') + 'M'
  if (n >= 1_000)     return (n / 1_000).toFixed(1).replace(/\.0$/, '') + 'k'
  return String(n)
}

interface FlyingCoin { id: number; x: number; y: number }
const flyingCoins = ref<FlyingCoin[]>([])
let coinId = 0

function spawnCoins(count: number) {
  const rect = scoreEl.value?.getBoundingClientRect()
  const baseX = rect ? rect.right - 20 : window.innerWidth / 2
  const baseY = rect ? rect.top : window.innerHeight / 2

  for (let i = 0; i < count; i++) {
    const id = coinId++
    const x = baseX + (Math.random() - 0.5) * 60
    const y = baseY + (Math.random() - 0.5) * 20
    flyingCoins.value.push({ id, x, y })
    setTimeout(() => {
      flyingCoins.value = flyingCoins.value.filter(c => c.id !== id)
    }, 900)
  }
}

const rendered = ref<Rendered | null>(null)
const hintHtml = ref('')
const titleHtml = ref('')
const loading = ref(false)
const loadError = ref('')
const submitted = ref(false)
const showHint = ref(false)
const checkResult = ref<CheckResult | null>(null)
const replies = ref<Record<string, string>>({})
const statementEl = ref<HTMLElement | null>(null)

const hasRadioAnswers = computed(() =>
  rendered.value?.answers.some(a => a.answer_type === 'radio') ?? false
)

const allFilled = computed(() =>
  rendered.value?.answers.every(a => (replies.value[a.input_name] ?? '').trim() !== '') ?? false
)
const hasClickfill = computed(() =>
  rendered.value?.answers.some(a => a.answer_type === 'clickfill') ?? false
)

// Clickfill
const clickfillChoicesHtml = ref<Array<{ raw: string; html: string }>>([])
const pendingChoice = ref<string | null>(null)
const draggingChoice = ref<string | null>(null)

// Segments de l'énoncé : html statique, slot clickfill, ou input texte
type Segment =
  | { type: 'html';  content: string }
  | { type: 'slot';  name: string }
  | { type: 'input'; name: string; width: number }
const statementSegments = ref<Segment[]>([])

function parseStatement(html: string): Segment[] {
  // Convert block-level tags to <br> so inline flow is preserved while
  // line breaks between logical sections are kept
  html = html
    .replace(/<div[^>]*>/gi, '<br>')
    .replace(/<\/div>/gi, '')
    .replace(/<p(?=[\s>])[^>]*>/gi, '<br>')   // <p> ou <p class=...> mais pas <path>
    .replace(/<\/p>/gi, '')
    .replace(/^(\s*<br\s*\/?>\s*)+/i, '')  // trim leading breaks

  const segments: Segment[] = []
  // Matches <cf-slot name="..."> et <oef-input name="..." width="...">
  const regex = /<cf-slot name="([^"]+)"><\/cf-slot>|<oef-input name="([^"]+)" width="([^"]+)"><\/oef-input>/g
  let last = 0
  let m: RegExpExecArray | null
  while ((m = regex.exec(html)) !== null) {
    if (m.index > last) segments.push({ type: 'html', content: html.slice(last, m.index) })
    if (m[1] !== undefined) {
      segments.push({ type: 'slot', name: m[1].replace(/\s+/g, '') })
    } else {
      segments.push({ type: 'input', name: m[2].replace(/\s+/g, ''), width: Number(m[3]) || 100 })
    }
    last = m.index + m[0].length
  }
  if (last < html.length) segments.push({ type: 'html', content: html.slice(last) })
  return segments
}

async function load(seed?: number) {
  loading.value = true
  loadError.value = ''
  submitted.value = false
  checkResult.value = null
  feedbackHtml.value = {}
  showHint.value = false
  replies.value = {}
  titleHtml.value = ''
  pendingChoice.value = null
  draggingChoice.value = null
  statementSegments.value = []
  clickfillChoicesHtml.value = []
  try {
    const url = seed
      ? `/api/render/${props.exerciseId}?seed=${seed}`
      : `/api/render/${props.exerciseId}`
    rendered.value = await apiFetch<Rendered>(url)

    if (rendered.value.title) {
      const decodedTitle = rendered.value.title
        .replace(/&#(\d+);/g, (_, code) => String.fromCharCode(Number(code)))
        .replace(/&amp;/g, '&').replace(/&lt;/g, '<').replace(/&gt;/g, '>')
      titleHtml.value = await renderMath(decodedTitle)
    }
    if (rendered.value.hint_html) {
      hintHtml.value = await renderMath(rendered.value.hint_html)
    }

    for (const ans of rendered.value.answers) {
      if (ans.answer_type === 'clickfill' && ans.options.choices?.length) {
        clickfillChoicesHtml.value = await Promise.all(
          ans.options.choices.map(async (c: string) => ({ raw: c, html: await renderMath(c) }))
        )
        break
      }
    }

    const renderedHtml = await renderMath(rendered.value.statement_html)
    statementSegments.value = parseStatement(renderedHtml)

    for (const ans of rendered.value.answers) {
      replies.value[ans.input_name] = ''
    }

  } catch (e: any) {
    loadError.value = e?.message || e?.data?.detail || JSON.stringify(e)
  } finally {
    loading.value = false
  }
}

function reload() {
  load()
}

async function submit() {
  if (!rendered.value || submitted.value) return

  loading.value = true
  try {
    const replyList = Object.entries(replies.value)
      .map(([input_name, value]) => ({ input_name, value }))

    checkResult.value = await apiFetch<CheckResult>(`/api/check/${props.exerciseId}`, {
      method: 'POST',
      body: { seed: rendered.value.seed, replies: replyList },
    })
    submitted.value = true
    await buildFeedbackHtml()

    const score = checkResult.value!.global_score
    if (score === 1) {
      coins.value += 10
      spawnCoins(8)
    } else if (score >= 0.5) {
      coins.value += 5
      spawnCoins(4)
    } else if (score > 0) {
      coins.value += 1
      spawnCoins(1)
    }
    if (score < 1) {
      document.documentElement.classList.add('shake')
      setTimeout(() => document.documentElement.classList.remove('shake'), 300)
    }
  } finally {
    loading.value = false
  }
}

function toLatex(expr: string): string {
  // Convertit la notation SymPy/OEF/élève en LaTeX lisible
  const sups: Record<string, string> = {'⁰':'0','¹':'1','²':'2','³':'3','⁴':'4','⁵':'5','⁶':'6','⁷':'7','⁸':'8','⁹':'9'}
  for (const [sup, digit] of Object.entries(sups)) {
    expr = expr.replaceAll(sup, `^${digit}`)
  }
  return expr
    .replace(/\*\*/g, '^')          // x**2 → x^2
    .replace(/\*/g, '')              // 6*x → 6x
    .replace(/\s+/g, '')            // supprime espaces résiduels
}

const feedbackHtml = ref<Record<string, { reply: string, expected: string }>>({})

function buildFilledLine(which: 'reply' | 'expected'): string {
  const segs = statementSegments.value
  const first = segs.findIndex(s => s.type !== 'html')
  const last = [...segs].map((s, i) => s.type !== 'html' ? i : -1).filter(i => i >= 0).at(-1) ?? -1
  if (first === -1) return ''

  // Préfixe : partie du segment HTML précédant le 1er champ, après le dernier <br>
  let prefix = ''
  if (first > 0 && segs[first - 1].type === 'html') {
    const raw = (segs[first - 1] as { type: 'html'; content: string }).content
    const brIdx = raw.lastIndexOf('<br')
    prefix = brIdx >= 0 ? raw.slice(raw.indexOf('>', brIdx) + 1) : raw
  }

  const line = segs.slice(first, last + 1).map(seg => {
    if (seg.type === 'html') return seg.content
    const fb = feedbackHtml.value[seg.name]
    if (!fb) return ''
    return `<span style="display:inline-block;vertical-align:middle">${fb[which]}</span>`
  }).join('')

  return prefix + line
}

const feedbackReplyLine = computed(() => buildFilledLine('reply'))
const feedbackExpectedLine = computed(() => buildFilledLine('expected'))

function isLatexString(s: string) {
  return s.startsWith('\\(') || s.startsWith('\\[')
}

async function renderValue(s: string): Promise<string> {
  if (!s) return '—'
  if (isLatexString(s)) return renderMath(s)
  return renderMath(`\\(${toLatex(s)}\\)`)
}

async function buildFeedbackHtml() {
  if (!checkResult.value) return
  const result: Record<string, { reply: string, expected: string }> = {}
  for (const r of checkResult.value.results) {
    result[r.input_name] = {
      reply: await renderValue(r.reply),
      expected: await renderValue(r.expected),
    }
  }
  feedbackHtml.value = result
}

function inputClass(name: string) {
  if (!submitted.value || !checkResult.value) return ''
  const r = checkResult.value.results.find(r => r.input_name === name)
  if (!r) return ''
  return r.correct ? 'correct' : 'incorrect'
}

function radioClass(inputName: string, choice: string) {
  if (!submitted.value) {
    return replies.value[inputName] === choice
      ? 'border-blue-400 bg-blue-50 dark:bg-blue-900/20'
      : 'hover:border-blue-300'
  }
  const result = checkResult.value?.results.find(r => r.input_name === inputName)
  if (!result) return ''
  if (choice === result.expected) return 'border-green-400 bg-green-50 dark:bg-green-900/20'
  if (choice === replies.value[inputName] && !result.correct) return 'border-red-400 bg-red-50 dark:bg-red-900/20'
  return ''
}

// Focus automatique sur le premier input texte après chaque chargement
watch(statementSegments, () => {
  statementEl.value?.querySelector<HTMLInputElement>('input[type="text"]')?.focus()
}, { flush: 'post' })

// Charge au montage
onMounted(() => load())
</script>

