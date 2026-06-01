<template>
  <div class="relative">
    <!-- Pièces volantes -->
    <span v-for="c in flyingCoins" :key="c.id"
          class="flying-coin"
          :style="{ left: c.x + 'px', top: c.y + 'px' }">⭐</span>

    <BaseExerciseStatement
      :rendered="rendered"
      :statement-segments="statementSegments"
      :replies="replies"
      @update:replies="val => replies = val"
      :clickfill-choices-html="clickfillChoicesHtml"
      :radio-choices-html="radioChoicesHtml"
      :menu-choices-html="menuChoicesHtml"
      :has-clickfill="hasClickfill"
      :has-radio-answers="hasRadioAnswers"
      :submitted="submitted"
      :loading="checking"
      :check-result="checkResult"
      @submit="submit"
    />

    <!-- Erreurs de format -->
    <div v-if="checkResult?.has_invalid_format" class="px-6 pb-4">
      <div v-for="r in checkResult.results.filter(res => res.status === 'invalid_format')" :key="r.input_name"
           class="rounded-lg px-4 py-3 border flex gap-3"
           style="border-color:#fbbf24;background:color-mix(in srgb, #fbbf24 10%, transparent);color:#92400e">
        <span class="text-lg">⚠️</span>
        <div class="py-0.5">
          <p class="font-medium">{{ r.detail }}</p>
        </div>
      </div>
    </div>

    <!-- Résultats Dynsteps — masqués tant qu'un avertissement de format réclame
         une nouvelle saisie (ex. polexpand « réduisez votre réponse »), sinon le
         bilan/score s'afficherait sous l'avertissement à la dernière étape. -->
    <div v-if="checkResult && !checkResult.has_invalid_format && (stepFailed || (rendered.current_step || 0) >= (rendered.total_steps || 0) || courseStopped)" class="px-6 pb-4">
      <!-- Bilan Global (à la fin ou arrêt course) -->
      <div v-if="(rendered.current_step || 0) >= (rendered.total_steps || 0) || courseStopped" class="space-y-3">
        <div class="rounded-lg px-4 py-3 border"
             :style="scoreRatio >= 0.9
               ? 'border-color:var(--color-success);background:color-mix(in srgb, var(--color-success) 10%, transparent)'
               : scoreRatio === 0
                 ? 'border-color:var(--color-error);background:color-mix(in srgb, var(--color-error) 10%, transparent)'
                 : 'border-color:#d97706;background:color-mix(in srgb, #f59e0b 10%, transparent)'">
          <div class="font-semibold text-lg mb-2">
            {{ $t('exercise.steps_completed') }}
            <span ref="scoreEl" class="font-normal text-sm ml-2">
              {{ $t('feedback.score', { pct: scorePct }) }}
            </span>
          </div>



          <div class="text-sm space-y-1 mt-1">
            <!-- Analyze (oui/non) : pas de détail par champ, juste OUI/NON. -->
            <div v-if="isAnalyzeWhole" class="flex items-baseline gap-2">
              <span class="font-medium" style="color:var(--color-text)">{{ $t('feedback.whole_label') }}</span>
              <span v-if="checkResult.global_score === 1" style="color:var(--color-success)" class="font-medium">{{ $t('feedback.yes') }}</span>
              <span v-else style="color:var(--color-error)" class="font-medium">{{ $t('feedback.no') }}</span>
            </div>
            <template v-else>
              <div v-for="(step, i) in stepsHistory" :key="i"
                   class="flex items-baseline gap-2 flex-wrap">
                <span class="font-medium" style="color:var(--color-text)" v-html="step.labelHtml || step.label || $t('exercise.step_label', { n: step.step }) + ' :'"></span>
                <!-- noanalyzeprint hides the *error* analysis only; a correct
                     step still echoes what the student typed. -->
                <span v-if="step.replyHtml && (!checkResult?.noanalyzeprint || step.correct)" v-html="step.replyHtml"></span>
                <span v-if="checkResult?.noanalyzeprint && !step.correct" class="mx-1" style="color:var(--color-text-muted)">-</span>
                <span v-if="step.correct" style="color:var(--color-success)" class="font-medium">
                  {{ $t('feedback.good') }}
                </span>
                <template v-else>
                  <span style="color:var(--color-error)" class="font-medium">
                    {{ $t('feedback.bad') }}<template v-if="!checkResult?.noanalyzeprint">,</template>
                  </span>
                  <template v-if="!checkResult?.noanalyzeprint">
                    <span style="color:var(--color-text)">
                      {{ $t('feedback.expected') }}
                    </span>
                    <span v-if="step.expectedHtml" v-html="step.expectedHtml" style="color:var(--color-text)"></span>
                  </template>
                </template>
              </div>
            </template>
          </div>

          <div v-if="checkResult?.feedback_html" class="mt-3 text-sm" v-html="checkResult.feedback_html"></div>
          <div v-if="checkResult?.solution_html" class="mt-3 text-sm border-t pt-3"
               style="border-color:var(--color-border)">
            <p class="font-medium mb-1" style="color:var(--color-text-muted)">{{ $t('exercise.solution') }}</p>
            <div v-html="checkResult.solution_html" style="color:var(--color-text)"></div>
          </div>
        </div>
      </div>

      <!-- Retour d'erreur sur une étape (si elle a échoué) -->
      <div v-else-if="stepFailed" class="rounded-lg px-4 py-3 border"
           style="border-color:var(--color-error);background:color-mix(in srgb, var(--color-error) 10%, transparent)">
        <div class="font-semibold text-lg mb-2">
          {{ $t('feedback.incorrect') }}
        </div>
        <div class="text-sm space-y-1 mt-1">
          <div v-for="r in checkResult.results.filter(res => res.input_name === currentStepFailedInputName)" :key="r.input_name"
               class="flex items-baseline gap-2 flex-wrap">
            <span v-html="feedbackHtml[r.input_name]?.reply"></span>
            <span style="color:var(--color-error)">{{ $t('feedback.bad') }}</span>
            <span style="color:var(--color-text-muted)">{{ $t('feedback.expected') }}</span>
            <span v-html="feedbackHtml[r.input_name]?.expected"></span>
            <span>.</span>
          </div>
        </div>
      </div>
    </div>

    <!-- Boutons -->
    <div class="px-6 pb-6 flex items-center gap-3 flex-wrap">
      <button @click="submit" :disabled="checking || submitted || !allFilled"
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

      <button v-if="submitted && ((rendered.current_step || 0) >= (rendered.total_steps || 0) || courseStopped)"
              @click="$emit('reload')"
              class="px-6 py-2.5 rounded-lg font-medium border transition"
              style="border-color:var(--color-border)">
        {{ $t('exercise.new_exercise') }}
      </button>
    </div>
  </div>
</template>

<script setup lang="ts">
import { ref, computed, watch, onMounted } from 'vue'
import type { Rendered, Segment, CheckResult } from '~/composables/useExerciseLogic'
import BaseExerciseStatement from './BaseExerciseStatement.vue'
import { useExerciseLogic } from '~/composables/useExerciseLogic'

const props = defineProps<{
  rendered: Rendered
  exerciseId: string
  debugAnswers?: Record<string, string> | null
}>()

const emit = defineEmits<{
  reload: []
  'load-step': [m_step: number, replies: Record<string, string>]
}>()

const { apiFetch } = useApi()
const { debugMode: debugOef } = useDebugMode()
const { addCoins } = useCoins()
const { buildSegments, buildFeedbackHtml, prepareChoicesHtml } = useExerciseLogic()
const { renderMath } = useKatex()

const replies = ref<Record<string, string>>({})
const statementSegments = ref<Segment[]>([])
const clickfillChoicesHtml = ref<Array<{ raw: string; html: string }>>([])
const radioChoicesHtml = ref<Record<string, Array<{ raw: string; html: string }>>>({})
const menuChoicesHtml = ref<Record<string, Array<{ raw: string; html: string }>>>({})

const checking = ref(false)
const submitted = ref(false)
const checkResult = ref<CheckResult | null>(null)
const feedbackHtml = ref<Record<string, { reply: string, expected: string }>>({})

const currentMStep = ref<number>(1)
const stepsHistory = ref<Array<{ step: number; correct: boolean; expected: string, input_name?: string, expectedHtml?: string, replyHtml?: string, label?: string }>>([])
const stepFailed = ref(false)
const currentStepFailedInputName = ref('')

const hasClickfill = computed(() =>
  props.rendered?.answers.some(a => a.answer_type === 'clickfill') ?? false
)
// `rendered.answers` is already filtered server-side to the current step's
// active replies, so this is naturally correct per step.
const hasRadioAnswers = computed(() =>
  props.rendered?.answers.some(a => a.answer_type === 'radio' && !a.options?.inline) ?? false
)

const isCourse = computed(() => props.rendered?.exercise_type === 'course')
const courseStopped = ref(false)

// Analyze-checked exercises are all-or-nothing (a single combined :test
// condition), so a per-field breakdown is misleading — show just OUI/NON like
// WIMS, then the correction (feedback_html).
const isAnalyzeWhole = computed(() =>
  !!checkResult.value?.results.length &&
  checkResult.value.results.every(r => r.method === 'analyze')
)

// Score helpers — a "step" may contain several inputs (e.g. csgb Q200 lays
// out a Thales ratio as 4 fields reply10..reply13 inside one step). We must
// dedup by step number so the denominator stays at total_steps and the
// percentage caps at 100 %.
const correctStepsCount = computed(() => {
  const byStep = new Map<number, boolean>()
  for (const entry of stepsHistory.value) {
    const prev = byStep.get(entry.step)
    byStep.set(entry.step, prev === undefined ? entry.correct : prev && entry.correct)
  }
  return Array.from(byStep.values()).filter(Boolean).length
})

const totalStepsForScore = computed(() => {
  if (isCourse.value) return props.rendered?.total_steps || 1
  // dynsteps: number of distinct steps attempted
  return new Set(stepsHistory.value.map(s => s.step)).size || 1
})

const scoreRatio = computed(() => correctStepsCount.value / totalStepsForScore.value)
const scorePct = computed(() => Math.round(scoreRatio.value * 100))

const allFilled = computed(() => {
  if (!props.rendered || courseStopped.value) return false
  // `rendered.answers` is server-filtered to the current step's active replies.
  const answers = props.rendered.answers
  // Analyze-checked exercises validate the whole answer via the :test section,
  // and some zones are meant to stay empty (e.g. a single interval uses 4 of
  // the 9 interval/union slots). Only require *at least one* field filled.
  if (answers.some(a => a.options?.analyze_var)) {
    return answers.some(a => (replies.value[a.input_name] ?? '').trim() !== '')
  }
  return answers.every(a => {
    const val = (replies.value[a.input_name] ?? '').trim()
    if (val !== '') return true
    const opt = (a.options?.option || '').toLowerCase()
    return opt.includes('default=vide')
  })
})

async function init() {
  submitted.value = false
  checkResult.value = null
  feedbackHtml.value = {}
  
  // Only reset history if we are back at step 1
  if (props.rendered.current_step === 1 || !props.rendered.current_step) {
    currentMStep.value = 1
    stepsHistory.value = []
    replies.value = {}
    courseStopped.value = false
  }
  
  stepFailed.value = false
  currentStepFailedInputName.value = ''

  statementSegments.value = await buildSegments(props.rendered.statement_segments)
  
  // Initialize only VISIBLE inputs for this step if not already present
  for (const seg of statementSegments.value) {
    if ('name' in seg && seg.name && !(seg.name in replies.value)) {
      replies.value[seg.name] = ''
    }
  }

  const choices = await prepareChoicesHtml(props.rendered)
  clickfillChoicesHtml.value = choices.clickfillChoicesHtml
  radioChoicesHtml.value = choices.radioChoicesHtml
  menuChoicesHtml.value = choices.menuChoicesHtml
}

watch(replies, () => {
  if (checkResult.value?.has_invalid_format) {
    checkResult.value = null
  }
}, { deep: true })

watch(() => props.rendered, () => init(), { deep: true })
onMounted(() => init())

// Score & Coins
const scoreEl = ref<HTMLElement | null>(null)
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

async function nextStep() {
  if (!props.rendered?.is_dynsteps) return

  const nextMStep = (props.rendered.current_step || 1) + 1
  currentMStep.value = nextMStep
  // Carry the replies submitted so far so the next step's statement can echo
  // each previous reply's verdict ($m_sc_reply{n}, e.g. lebrun5).
  const acc: Record<string, string> = {}
  for (const [k, v] of Object.entries(replies.value)) {
    if (typeof v === 'string' && v.trim() !== '') acc[k] = v
  }
  emit('load-step', nextMStep, acc)
}

async function submit() {
  if (!props.rendered || submitted.value) return

  checking.value = true
  try {
    const currentStep = props.rendered.current_step || 1
    const totalSteps = props.rendered.total_steps || 1

    const replyList = Object.entries(replies.value)
      .map(([input_name, value]) => ({ input_name, value }))

    checkResult.value = await apiFetch<CheckResult>(`/api/check/${props.exerciseId}`, {
      method: 'POST',
      body: { 
        seed: props.rendered.seed, 
        replies: replyList,
        m_step: currentStep
      },
    })
    
    if (checkResult.value.has_invalid_format) {
      checking.value = false
      return
    }

    submitted.value = true
    const answerTypes = Object.fromEntries(
      props.rendered.answers.map(a => [a.input_name, a.answer_type] as [string, string])
    )
    feedbackHtml.value = await buildFeedbackHtml(checkResult.value, answerTypes)
    
    if (checkResult.value.feedback_html) {
      checkResult.value.feedback_html = await renderMath(checkResult.value.feedback_html, { autoDisplay: true })
    }
    if (checkResult.value.solution_html) {
      checkResult.value.solution_html = await renderMath(checkResult.value.solution_html, { autoDisplay: true })
    }

    // `rendered.answers` is server-filtered to the current step's replies.
    const activeNames = new Set(props.rendered.answers.map(a => a.input_name))
    const activeResults = checkResult.value.results.filter(r => activeNames.has(r.input_name))
    
    // Update history for each active input in this step
    let stepHasBlockingError = false  // wrong AND not `nonstop`
    for (const res of activeResults) {
      const existingIdx = stepsHistory.value.findIndex(s => s.input_name === res.input_name)
      const rawLabel = props.rendered.answers.find(a => a.input_name === res.input_name)?.label || ''
      const labelHtml = rawLabel ? await renderMath(rawLabel) : ''
      const newItem = {
        step: currentStep,
        correct: res.correct,
        expected: res.expected,
        input_name: res.input_name,
        label: rawLabel,
        labelHtml: labelHtml,
        expectedHtml: feedbackHtml.value[res.input_name]?.expected,
        replyHtml: feedbackHtml.value[res.input_name]?.reply
      }
      if (existingIdx >= 0) {
        stepsHistory.value[existingIdx] = newItem
      } else {
        stepsHistory.value.push(newItem)
      }

      if (!res.correct) {
        // WIMS `option=nonstop`: a wrong answer still advances to the next
        // step (oef/step.proc: stop only `if reply!=good and nonstop notwordof
        // replyoption`). lebrun5 puts nonstop on each step's answer.
        const opt = (props.rendered.answers.find(a => a.input_name === res.input_name)?.options?.option || '').toLowerCase()
        const nonstop = /\bnonstop\b/.test(opt)
        if (!nonstop) {
          stepHasBlockingError = true
          stepFailed.value = true
          currentStepFailedInputName.value = res.input_name
          // For dynsteps, fill the correct answer on failure to move forward;
          // for a (blocking) course step we stop instead.
          if (!isCourse.value) {
            replies.value[res.input_name] = res.expected
          }
        }
      }
    }

    // Only a *blocking* wrong answer (no `nonstop`) stops a course; a nonstop
    // wrong answer is recorded as wrong but the course advances.
    if (isCourse.value && stepHasBlockingError) {
      courseStopped.value = true
    }

    // Auto-advance to next step immediately if at least one input was processed
    // and there was no error in a course
    if (activeResults.length > 0 && currentStep < totalSteps && !courseStopped.value) {
      setTimeout(async () => {
        await nextStep()
      }, 0)
    }

    // Only finalize score and show results at the end or if course stopped
    if (currentStep >= totalSteps || courseStopped.value) {
      // Use the same dedup-by-step ratio as the displayed bilan (correctStepsCount
      // counts each step at most once, even when it has multiple input fields).
      const score = scoreRatio.value

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

function fillAnswers(answers: Record<string, string>) {
  // Only fill the current step's active replies.
  const activeNames = new Set(props.rendered.answers.map(a => a.input_name))
  const filteredAnswers = Object.fromEntries(
    Object.entries(answers).filter(([name]) => activeNames.has(name))
  )
  replies.value = { ...replies.value, ...filteredAnswers }
}

defineExpose({ fillAnswers })
</script>
