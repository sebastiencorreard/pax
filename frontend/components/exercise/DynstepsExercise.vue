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

    <!-- Résultats Dynsteps -->
    <div v-if="checkResult && (stepFailed || (rendered.current_step || 0) >= (rendered.total_steps || 0) || courseStopped)" class="px-6 pb-4">
      <!-- Bilan Global (à la fin ou arrêt course) -->
      <div v-if="(rendered.current_step || 0) >= (rendered.total_steps || 0) || courseStopped" class="space-y-3">
        <div class="rounded-lg px-4 py-3 border"
             :style="(stepsHistory.filter(s => s.correct).length / (isCourse ? rendered.total_steps || 1 : stepsHistory.length || 1)) >= 0.9
               ? 'border-color:var(--color-success);background:color-mix(in srgb, var(--color-success) 10%, transparent)'
               : (stepsHistory.filter(s => s.correct).length / (isCourse ? rendered.total_steps || 1 : stepsHistory.length || 1)) === 0
                 ? 'border-color:var(--color-error);background:color-mix(in srgb, var(--color-error) 10%, transparent)'
                 : 'border-color:#d97706;background:color-mix(in srgb, #f59e0b 10%, transparent)'">
          <div class="font-semibold text-lg mb-2">
            {{ $t('exercise.steps_completed') }}
            <span ref="scoreEl" class="font-normal text-sm ml-2">
              {{ $t('feedback.score', { pct: Math.round((stepsHistory.filter(s => s.correct).length / (isCourse ? rendered.total_steps || 1 : stepsHistory.length || 1)) * 100) }) }}
            </span>
          </div>
          <div class="text-sm space-y-1 mt-1">
            <div v-for="(step, i) in stepsHistory" :key="i"
                 class="flex items-baseline gap-2 flex-wrap">
              <span class="font-medium" style="color:var(--color-text)">
                {{ step.label || $t('exercise.step_label', { n: step.step }) }} :
              </span>
              <span v-if="step.replyHtml" v-html="step.replyHtml"></span>
              <span v-if="step.correct" style="color:var(--color-success)" class="font-medium">
                {{ $t('feedback.good') }}
              </span>
              <template v-else>
                <span style="color:var(--color-error)" class="font-medium">
                  {{ $t('feedback.bad') }},
                </span>
                <span style="color:var(--color-text)">
                  {{ $t('feedback.expected') }}
                </span>
                <span v-if="step.expectedHtml" v-html="step.expectedHtml" style="color:var(--color-text)"></span>
              </template>
            </div>
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
  'load-step': [m_step: number]
}>()

const { apiFetch } = useApi()
const { debugMode: debugOef } = useDebugMode()
const { addCoins } = useCoins()
const { buildSegments, buildFeedbackHtml, prepareChoicesHtml } = useExerciseLogic()

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
const hasRadioAnswers = computed(() =>
  props.rendered?.answers.some(a => a.answer_type === 'radio') ?? false
)

const isCourse = computed(() => props.rendered?.exercise_type === 'course')
const courseStopped = ref(false)

const allFilled = computed(() => {
  if (!props.rendered || courseStopped.value) return false
  const activeNames = new Set(statementSegments.value.map(s => {
    if (s.type === 'input' || s.type === 'textarea' || s.type === 'slot' || s.type === 'menu') {
      return s.name
    }
    return null
  }).filter(Boolean))
  
  const activeAnswers = props.rendered.answers.filter(a => activeNames.has(a.input_name))
  if (activeAnswers.length > 0) {
    return activeAnswers.every(a => (replies.value[a.input_name] ?? '').trim() !== '')
  }
  return true
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

  // Initialize new inputs for this step without wiping existing ones
  for (const ans of props.rendered.answers) {
    if (!(ans.input_name in replies.value)) {
      replies.value[ans.input_name] = ''
    }
  }

  statementSegments.value = await buildSegments(props.rendered.statement_segments)
  
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
  emit('load-step', nextMStep)
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
    feedbackHtml.value = await buildFeedbackHtml(checkResult.value)

    const activeNames = new Set(statementSegments.value.map(s => {
      if (s.type === 'input' || s.type === 'textarea' || s.type === 'slot' || s.type === 'menu') {
        return s.name
      }
      return null
    }).filter(Boolean))
    const activeResults = checkResult.value.results.filter(r => activeNames.has(r.input_name))
    
    // Update history for each active input in this step
    let stepHasError = false
    for (const res of activeResults) {
      const existingIdx = stepsHistory.value.findIndex(s => s.input_name === res.input_name)
      const newItem = {
        step: currentStep,
        correct: res.correct,
        expected: res.expected,
        input_name: res.input_name,
        label: props.rendered.answers.find(a => a.input_name === res.input_name)?.label,
        expectedHtml: feedbackHtml.value[res.input_name]?.expected,
        replyHtml: feedbackHtml.value[res.input_name]?.reply
      }
      if (existingIdx >= 0) {
        stepsHistory.value[existingIdx] = newItem
      } else {
        stepsHistory.value.push(newItem)
      }

      if (!res.correct) {
        stepHasError = true
        stepFailed.value = true
        currentStepFailedInputName.value = res.input_name
        // For dynsteps, we often fill the correct answer on failure to allow moving forward
        // BUT for courses, we stop.
        if (!isCourse.value) {
          replies.value[res.input_name] = res.expected
        }
      }
    }

    if (isCourse.value && stepHasError) {
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
      const correctSteps = stepsHistory.value.filter(s => s.correct).length
      const score = totalSteps > 0 ? correctSteps / totalSteps : 0

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
  const newReplies = { ...replies.value }
  for (const [name, value] of Object.entries(answers)) {
    if (name in newReplies) newReplies[name] = value
  }
  replies.value = newReplies
}

defineExpose({ fillAnswers })
</script>
