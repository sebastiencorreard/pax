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

    <!-- Résultats Standard -->
    <div v-if="checkResult && !checkResult.has_invalid_format" class="px-6 pb-4">
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
            <span class="font-medium" style="color:var(--color-text)" v-html="labelsHtml[r.input_name] || rendered.answers.find(a => a.input_name === r.input_name)?.label || $t('feedback.index', { n: i + 1 }) + ' :'">
            </span>
            <span v-if="!checkResult.noanalyzeprint" v-html="feedbackHtml[r.input_name]?.reply"></span>
            <span v-if="checkResult.noanalyzeprint" class="mx-1" style="color:var(--color-text-muted)">-</span>
            <span v-if="r.correct" style="color:var(--color-success)" class="font-medium">
              {{ $t('feedback.good') }}
            </span>
            <template v-else>
              <span style="color:var(--color-error)" class="font-medium">
                {{ $t('feedback.bad') }}<template v-if="!checkResult.noanalyzeprint">,</template>
              </span>
              <template v-if="!checkResult.noanalyzeprint">
                <span style="color:var(--color-text)">
                  {{ $t('feedback.expected') }}
                </span>
                <span v-html="feedbackHtml[r.input_name]?.expected" style="color:var(--color-text)"></span>
              </template>
            </template>
          </div>
        </div>

        <div v-if="checkResult.feedback_html" class="mt-3 text-sm" v-html="checkResult.feedback_html"></div>
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

      <button v-if="submitted"
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
}>()

const { apiFetch } = useApi()
const { debugMode: debugOef } = useDebugMode()
const { addCoins } = useCoins()
const { buildSegments, buildFeedbackHtml, prepareChoicesHtml } = useExerciseLogic()
const { renderMath } = useKatex()

const replies = ref<Record<string, string>>({})
const labelsHtml = ref<Record<string, string>>({})
const statementSegments = ref<Segment[]>([])
const clickfillChoicesHtml = ref<Array<{ raw: string; html: string }>>([])
const radioChoicesHtml = ref<Record<string, Array<{ raw: string; html: string }>>>({})
const menuChoicesHtml = ref<Record<string, Array<{ raw: string; html: string }>>>({})

const checking = ref(false)
const submitted = ref(false)
const checkResult = ref<CheckResult | null>(null)
const feedbackHtml = ref<Record<string, { reply: string, expected: string }>>({})

const hasClickfill = computed(() =>
  props.rendered?.answers.some(a => a.answer_type === 'clickfill') ?? false
)
const hasRadioAnswers = computed(() =>
  props.rendered?.answers.some(a => a.answer_type === 'radio') ?? false
)

const allFilled = computed(() => {
  if (!props.rendered) return false
  return props.rendered.answers.every(a => {
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
  replies.value = {}
  labelsHtml.value = {}
  
  for (const ans of props.rendered.answers) {
    replies.value[ans.input_name] = ''
    if (ans.label) {
      labelsHtml.value[ans.input_name] = await renderMath(ans.label)
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

async function submit() {
  if (!props.rendered || submitted.value) return

  checking.value = true
  try {
    const replyList = Object.entries(replies.value)
      .map(([input_name, value]) => ({ input_name, value }))

    checkResult.value = await apiFetch<CheckResult>(`/api/check/${props.exerciseId}`, {
      method: 'POST',
      body: { 
        seed: props.rendered.seed, 
        replies: replyList,
        m_step: props.rendered.current_step
      },
    })
    
    if (checkResult.value.has_invalid_format) {
      checking.value = false
      return
    }

    submitted.value = true
    feedbackHtml.value = await buildFeedbackHtml(checkResult.value)
    
    if (checkResult.value.feedback_html) {
      checkResult.value.feedback_html = await renderMath(checkResult.value.feedback_html)
    }

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
  } finally {
    checking.value = false
  }
}

function fillAnswers(answers: Record<string, string>) {
  // Filter answers to only fill those currently visible on screen
  const activeNames = new Set(statementSegments.value
    .map(s => (s.type === 'input' || s.type === 'textarea' || s.type === 'slot' || s.type === 'menu') ? s.name : null)
    .filter(Boolean) as string[]
  )
  
  const filteredAnswers = Object.fromEntries(
    Object.entries(answers).filter(([name]) => activeNames.has(name))
  )
  
  const newReplies = { ...replies.value }
  for (const [name, value] of Object.entries(filteredAnswers)) {
    newReplies[name] = value
  }
  replies.value = newReplies
}

defineExpose({ fillAnswers })
</script>
