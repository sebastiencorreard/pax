<template>
  <div class="rounded-xl border shadow-sm overflow-hidden"
       style="background:var(--color-surface);border-color:var(--color-border)">

    <!-- Pièces volantes -->
    <span v-for="c in flyingCoins" :key="c.id"
          class="flying-coin"
          :style="{ left: c.x + 'px', top: c.y + 'px' }">⭐</span>

    <!-- En-tête -->
    <div class="px-6 py-4 border-b flex items-center justify-between"
         style="border-color:var(--color-border)">
      <div class="flex items-center gap-3">
        <h2 class="font-semibold text-lg" v-html="titleHtml || rendered?.title || $t('exercise.loading')"></h2>
        <span v-if="rendered?.is_dynsteps && rendered.current_step && rendered.total_steps"
              class="text-sm px-2 py-1 rounded"
              style="background:var(--color-bg);color:var(--color-text-muted)">
          {{ $t('exercise.step_progress', { current: rendered.current_step, total: rendered.total_steps }) }}
        </span>
      </div>
      <div class="flex items-center gap-2">
        <span v-if="debugOef" class="text-xs px-2 py-1 rounded"
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
            :style="{ width: seg.width, minWidth: '6ch' }"
            :disabled="submitted"
            :class="inputClass(seg.name)"
            autocomplete="off"
            @dragover.prevent
            @drop.prevent
            @keydown.enter.prevent="() => { if (!submitted && !loading) submit() }"
          />
          <textarea v-else-if="seg.type === 'textarea'"
            :name="seg.name"
            v-model="replies[seg.name]"
            :rows="seg.rows"
            :cols="seg.cols"
            :disabled="submitted"
            class="rounded border px-2 py-1 text-sm font-mono resize"
            style="background:var(--color-bg);border-color:var(--color-border);color:var(--color-text)"
          />
          <select v-else-if="seg.type === 'menu'"
            v-model="replies[seg.name]"
            :disabled="submitted"
            class="inline-block px-3 py-1.5 rounded border mx-1 transition"
            style="border-color:var(--color-border);background:var(--color-surface)">
            <option value="">{{ seg.label }}</option>
            <option v-for="choice in (menuChoicesHtml[seg.name] ?? [])"
                    :key="choice.raw"
                    :value="choice.raw"
                    v-html="choice.html">
            </option>
          </select>

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
            <label v-for="choice in (radioChoicesHtml[ans.input_name] ?? [])" :key="choice.raw"
                   class="flex items-center gap-3 px-4 py-3 rounded-lg border cursor-pointer transition"
                   :class="radioClass(ans.input_name, choice.raw)"
                   style="border-color:var(--color-border)">
              <input type="radio" :name="ans.input_name" :value="choice.raw"
                     v-model="replies[ans.input_name]"
                     :disabled="submitted" class="accent-blue-500" />
              <span v-html="choice.html"></span>
            </label>
          </div>
        </template>
      </div>
    </div>

    <!-- Résultats -->
    <div v-if="checkResult && (!rendered?.is_dynsteps || stepFailed || (rendered.current_step || 0) >= (rendered.total_steps || 0))" class="px-6 pb-4">
      <!-- Dynamic steps: show summary at the end, single step feedback during -->
      <div v-if="rendered?.is_dynsteps && (rendered.current_step || 0) >= (rendered.total_steps || 0)" class="space-y-3">
        <!-- Global summary -->
        <div class="rounded-lg px-4 py-3 border"
             :style="(stepsHistory.filter(s => s.correct).length / stepsHistory.length) === 1
               ? 'border-color:var(--color-success);background:color-mix(in srgb, var(--color-success) 10%, transparent)'
               : (stepsHistory.filter(s => s.correct).length / stepsHistory.length) === 0
                 ? 'border-color:var(--color-error);background:color-mix(in srgb, var(--color-error) 10%, transparent)'
                 : 'border-color:#d97706;background:color-mix(in srgb, #f59e0b 10%, transparent)'">
          <div class="font-semibold text-lg mb-2">
            {{ $t('exercise.steps_completed') }}
            <span ref="scoreEl" class="font-normal text-sm ml-2">
              {{ $t('feedback.score', { pct: Math.round((stepsHistory.filter(s => s.correct).length / stepsHistory.length) * 100) }) }}
            </span>
          </div>
          <div class="text-sm space-y-1 mt-1">
            <div v-for="(step, i) in stepsHistory" :key="i"
                 class="flex items-baseline gap-2 flex-wrap">
              <span style="color:var(--color-text-muted)">{{ $t('exercise.step_label', { n: step.step }) }}</span>
              <span v-if="step.correct" style="color:var(--color-success)">{{ $t('feedback.good') }}</span>
              <template v-else>
                <span style="color:var(--color-error)">{{ $t('feedback.bad') }}</span>
                <span v-if="step.replyHtml" v-html="step.replyHtml"></span>
                <span style="color:var(--color-text-muted)">{{ $t('feedback.expected') }}</span>
                <span v-if="step.expectedHtml" v-html="step.expectedHtml"></span>
                <span>.</span>
              </template>
            </div>
          </div>
        </div>
      </div>

      <!-- Normal exercise or single step feedback -->
      <div v-else class="rounded-lg px-4 py-3 border"
           :style="(checkResult.global_score === 1 && !rendered?.is_dynsteps)
             ? 'border-color:var(--color-success);background:color-mix(in srgb, var(--color-success) 10%, transparent)'
             : (checkResult.global_score === 0 || (rendered?.is_dynsteps && stepFailed))
               ? 'border-color:var(--color-error);background:color-mix(in srgb, var(--color-error) 10%, transparent)'
               : 'border-color:#d97706;background:color-mix(in srgb, #f59e0b 10%, transparent)'">
        <div class="font-semibold text-lg mb-2">
          <template v-if="checkResult.global_score === 1 && !rendered?.is_dynsteps">{{ $t('feedback.correct') }}</template>
          <template v-else-if="checkResult.global_score === 0 || (rendered?.is_dynsteps && stepFailed)">{{ $t('feedback.incorrect') }}</template>
          <template v-else>
            {{ checkResult.results.filter(r => !r.correct).length === 1 ? $t('feedback.one_error') : $t('feedback.many_errors') }}
          </template>
          <span v-if="!rendered?.is_dynsteps" ref="scoreEl" class="font-normal text-sm ml-2">
            {{ $t('feedback.score', { pct: Math.round(checkResult.global_score * 100) }) }}
          </span>
        </div>
        <div class="text-sm space-y-1 mt-1">
          <div v-for="(r, i) in (rendered?.is_dynsteps ? checkResult.results.filter(res => res.input_name === currentStepFailedInputName) : checkResult.results)" :key="r.input_name"
               class="flex items-baseline gap-2 flex-wrap">
            <span v-if="!rendered?.is_dynsteps" style="color:var(--color-text-muted)">{{ $t('feedback.index', { n: i + 1 }) }}</span>
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
    <div class="px-6 pb-6 flex items-center gap-3 flex-wrap">
      <button v-if="stepFailed"
              @click="advanceFailedStep"
              class="px-6 py-2.5 rounded-lg font-medium transition"
              style="background:var(--color-primary);color:#fff">
        {{ $t('exercise.next_step') }}
      </button>
      <button v-else @click="submit" :disabled="loading || checking || submitted || !allFilled"
              class="px-6 py-2.5 rounded-lg font-medium transition disabled:opacity-60"
              style="background:var(--color-primary);color:#fff">
        {{ submitted ? $t('exercise.corrected') : $t('exercise.verify') }}
      </button>

      <button v-if="debugOef && debugAnswers && !submitted"
              @click="fillAnswers(debugAnswers)"
              class="px-6 py-2.5 rounded-lg font-mono text-xs border border-dashed transition hover:opacity-80"
              style="border-color:var(--color-text-muted);color:var(--color-text-muted)">
        Réponse auto
      </button>

      <button v-if="submitted && (!rendered?.is_dynsteps || (rendered.current_step || 0) >= (rendered.total_steps || 0))"
              @click="reload"
              class="px-6 py-2.5 rounded-lg font-medium border transition"
              style="border-color:var(--color-border)">
        {{ $t('exercise.new_exercise') }}
      </button>

      <button v-if="rendered?.hint_html" @click="showHint = !showHint"
              class="px-4 py-2.5 rounded-lg text-sm border transition"
              style="border-color:var(--color-border);color:var(--color-text-muted)">
        {{ showHint ? $t('exercise.hint_hide') : $t('exercise.hint_show') }}
      </button>

      <!-- Slot pour les tags QA debug (E/R/V), alignés à droite -->
      <div class="ml-auto">
        <slot name="qa" />
      </div>
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
const props = defineProps<{
  exerciseId: string
  debugAnswers?: Record<string, string> | null
}>()
const emit = defineEmits<{ rendered: [{ seed: number; exerciseId: string; currentStep?: number | null }] }>()

const { apiFetch } = useApi()
const { renderMath } = useKatex()
const { debugMode: debugOef } = useDebugMode()

interface AnswerDef {
  input_name: string
  label: string
  answer_type: string
  options: Record<string, any>
  weight: number
  logical_name: string
}

interface BackendSegment {
  type: 'html' | 'input' | 'textarea' | 'slot' | 'menu'
  content?: string
  name?: string
  size?: number
  rows?: number
  cols?: number
  label?: string
}

interface Rendered {
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
const { coins, addCoins } = useCoins()

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
const checking = ref(false)
const loadError = ref('')
const submitted = ref(false)
const showHint = ref(false)
const checkResult = ref<CheckResult | null>(null)
const replies = ref<Record<string, string>>({})
const statementEl = ref<HTMLElement | null>(null)

// Dynamic steps tracking
const currentMStep = ref<number>(1)
const stepsHistory = ref<Array<{ step: number; correct: boolean; expected: string, input_name?: string, expectedHtml?: string, replyHtml?: string }>>([])
const stepFailed = ref(false)
const currentStepFailedExpected = ref('')
const currentStepFailedInputName = ref('')

const hasRadioAnswers = computed(() =>
  rendered.value?.answers.some(a => a.answer_type === 'radio') ?? false
)

const hasMenuAnswers = computed(() =>
  rendered.value?.answers.some(a => a.answer_type === 'menu') ?? false
)

const allFilled = computed(() => {
  if (!rendered.value) return false
  if (!rendered.value.is_dynsteps) {
    return rendered.value.answers.every(a => (replies.value[a.input_name] ?? '').trim() !== '')
  }
  const activeNames = new Set(statementSegments.value.map(s => 'name' in s ? s.name : null).filter(Boolean))
  const activeAnswers = rendered.value.answers.filter(a => activeNames.has(a.input_name))
  if (activeAnswers.length > 0) {
    return activeAnswers.every(a => (replies.value[a.input_name] ?? '').trim() !== '')
  }
  return true
})
const hasClickfill = computed(() =>
  rendered.value?.answers.some(a => a.answer_type === 'clickfill') ?? false
)

// Clickfill
const clickfillChoicesHtml = ref<Array<{ raw: string; html: string }>>([])
const pendingChoice = ref<string | null>(null)
const draggingChoice = ref<string | null>(null)

// Radio
const radioChoicesHtml = ref<Record<string, Array<{ raw: string; html: string }>>>({})

// Menu
const menuChoicesHtml = ref<Record<string, Array<{ raw: string; html: string }>>>({})


// Segments d'affichage : produits par le backend, le HTML statique passe par KaTeX.
type Segment =
  | { type: 'html';     content: string }
  | { type: 'slot';     name: string }
  | { type: 'input';    name: string; width: string }
  | { type: 'textarea'; name: string; rows: number; cols: number }
  | { type: 'menu';     name: string; label: string }
const statementSegments = ref<Segment[]>([])

async function buildSegments(backendSegments: BackendSegment[]): Promise<Segment[]> {
  const out: Segment[] = []
  for (const s of backendSegments) {
    if (s.type === 'html') {
      out.push({ type: 'html', content: await renderMath(s.content ?? '') })
    } else if (s.type === 'input') {
      const size = s.size ?? 0
      out.push({ type: 'input', name: s.name ?? '', width: size > 0 ? `${size + 2}ch` : '10ch' })
    } else if (s.type === 'textarea') {
      out.push({ type: 'textarea', name: s.name ?? '', rows: s.rows ?? 5, cols: s.cols ?? 30 })
    } else if (s.type === 'slot') {
      out.push({ type: 'slot', name: s.name ?? '' })
    } else if (s.type === 'menu') {
      out.push({ type: 'menu', name: s.name ?? '', label: s.label ?? '' })
    }
  }
  return out
}

async function load(seed?: number, m_step?: number) {
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
  radioChoicesHtml.value = {}
  menuChoicesHtml.value = {}

  // Reset step tracking only if loading a new exercise (no m_step provided)
  if (!m_step) {
    currentMStep.value = 1
    stepsHistory.value = []
  }
  stepFailed.value = false

  try {
    const params = new URLSearchParams()
    if (seed) params.append('seed', seed.toString())
    if (m_step) params.append('m_step', m_step.toString())
    const url = `/api/render/${props.exerciseId}${params.toString() ? '?' + params.toString() : ''}`
    rendered.value = await apiFetch<Rendered>(url)

    if (rendered.value.title) {
      const decodedTitle = rendered.value.title
        .replace(/&#(\d+);/g, (_, code) => String.fromCharCode(Number(code)))
        .replace(/&amp;/g, '&').replace(/&lt;/g, '<').replace(/&gt;/g, '>')
      titleHtml.value = decodedTitle
    }
    if (rendered.value.hint_html) {
      hintHtml.value = await renderMath(rendered.value.hint_html)
    }

    for (const ans of rendered.value.answers) {
      if (ans.answer_type === 'clickfill' && ans.options.choices?.length) {
        clickfillChoicesHtml.value = await Promise.all(
          ans.options.choices.map(async (c: string) => ({ raw: c, html: await renderMath(c) }))
        )
      }
      if (ans.answer_type === 'radio' && ans.options.choices?.length) {
        radioChoicesHtml.value[ans.input_name] = await Promise.all(
          ans.options.choices.map(async (c: string) => ({ raw: c, html: await renderMath(c) }))
        )
      }
      if (ans.answer_type === 'menu' && ans.options.choices?.length) {
        menuChoicesHtml.value[ans.input_name] = await Promise.all(
          ans.options.choices.map(async (c: string) => ({ raw: c, html: await renderMath(c) }))
        )
      }
    }

    statementSegments.value = await buildSegments(rendered.value.statement_segments)

    for (const ans of rendered.value.answers) {
      replies.value[ans.input_name] = ''
    }

    emit('rendered', {
      seed: rendered.value.seed,
      exerciseId: props.exerciseId,
      currentStep: rendered.value.current_step
    })

  } catch (e: any) {
    loadError.value = e?.message || e?.data?.detail || JSON.stringify(e)
  } finally {
    loading.value = false
  }
}

function reload() {
  load()
}

async function nextStep() {
  if (!rendered.value?.is_dynsteps) return

  const nextMStep = (rendered.value.current_step || 1) + 1
  currentMStep.value = nextMStep

  // Reload with the same seed but next step
  await load(rendered.value.seed, nextMStep)
}

async function advanceFailedStep() {
  if (currentStepFailedInputName.value) {
    // Replace with correct answer before moving on
    replies.value[currentStepFailedInputName.value] = currentStepFailedExpected.value
  }
  stepFailed.value = false
  const currentStep = rendered.value?.current_step || 1
  const totalSteps = rendered.value?.total_steps || 1
  
  if (currentStep < totalSteps) {
    await nextStep()
  } else {
    // End of exercise
    const correctSteps = stepsHistory.value.filter(s => s.correct).length
    const score = correctSteps / totalSteps
    if (score === 1) {
      addCoins(10)
      spawnCoins(8)
    } else if (score >= 0.5) {
      addCoins(5)
      spawnCoins(4)
    } else if (score > 0) {
      addCoins(1)
      spawnCoins(1)
    }
    if (score < 1) {
      document.documentElement.classList.add('shake')
      setTimeout(() => document.documentElement.classList.remove('shake'), 300)
    }
  }
}

async function submit() {
  if (!rendered.value || submitted.value) return

  checking.value = true
  try {
    // Dynamic steps mode
    if (rendered.value.is_dynsteps) {
      const currentStep = rendered.value.current_step || 1
      const totalSteps = rendered.value.total_steps || 1

      const replyList = Object.entries(replies.value)
        .map(([input_name, value]) => ({ input_name, value }))

      checkResult.value = await apiFetch<CheckResult>(`/api/check/${props.exerciseId}`, {
        method: 'POST',
        body: { seed: rendered.value.seed, replies: replyList },
      })
      submitted.value = true
      await buildFeedbackHtml()

      const activeNames = new Set(statementSegments.value.map(s => 'name' in s ? s.name : null).filter(Boolean))
      const activeResults = checkResult.value.results.filter(r => activeNames.has(r.input_name))
      const stepResult = activeResults.length > 0 ? activeResults[activeResults.length - 1] : checkResult.value.results[currentStep - 1]

      if (stepResult) {
        stepsHistory.value.push({
          step: currentStep,
          correct: stepResult.correct,
          expected: stepResult.expected,
          input_name: stepResult.input_name,
          expectedHtml: feedbackHtml.value[stepResult.input_name]?.expected,
          replyHtml: feedbackHtml.value[stepResult.input_name]?.reply
        })

        if (!stepResult.correct) {
          stepFailed.value = true
          currentStepFailedExpected.value = stepResult.expected
          currentStepFailedInputName.value = stepResult.input_name
        } else {
          // Auto-advance to next step immediately if correct
          if (currentStep < totalSteps) {
            setTimeout(async () => {
              await nextStep()
            }, 0)
          }
        }
      }

      // If this is the last step and we didn't just fail, calculate global score
      if (currentStep >= totalSteps && (!stepResult || stepResult.correct)) {
        const correctSteps = stepsHistory.value.filter(s => s.correct).length
        const score = correctSteps / totalSteps

        if (score === 1) {
          addCoins(10)
          spawnCoins(8)
        } else if (score >= 0.5) {
          addCoins(5)
          spawnCoins(4)
        } else if (score > 0) {
          addCoins(1)
          spawnCoins(1)
        }
        if (score < 1) {
          document.documentElement.classList.add('shake')
          setTimeout(() => document.documentElement.classList.remove('shake'), 300)
        }
      }
    } else {
      // Normal mode (non-dynsteps)
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
        addCoins(10)
        spawnCoins(8)
      } else if (score >= 0.5) {
        addCoins(5)
        spawnCoins(4)
      } else if (score > 0) {
        addCoins(1)
        spawnCoins(1)
      }
      if (score < 1) {
        document.documentElement.classList.add('shake')
        setTimeout(() => document.documentElement.classList.remove('shake'), 300)
      }
    }
  } finally {
    checking.value = false
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

// Remplit les champs de réponse avec les valeurs fournies (appelé depuis ExerciseDetail en mode debug)
function fillAnswers(answers: Record<string, string>) {
  for (const [name, value] of Object.entries(answers)) {
    if (name in replies.value) replies.value[name] = value
  }
}

defineExpose({ fillAnswers })
</script>

