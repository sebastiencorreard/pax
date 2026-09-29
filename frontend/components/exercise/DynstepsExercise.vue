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
      :single-use-fill="singleUseFill"
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
    <div v-if="checkResult && !checkResult.has_invalid_format && (stepFailed || termine)" class="px-6 pb-4">
      <!-- Bilan Global (à la fin ou arrêt course) -->
      <div v-if="termine" class="space-y-3">
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

      <button v-if="submitted && termine"
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
  'load-step': [m_step: number, replies: Record<string, string>, scores: Record<string, number>]
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
// Les notes que `/api/check` a données aux champs des étapes passées : le rendu
// de l'étape suivante en tire `m_sc_reply` (verdict affiché, champs reposés).
const notesDesEtapes = ref<Record<string, number>>({})
const stepsHistory = ref<Array<{ step: number; correct: boolean; expected: string, input_name?: string, expectedHtml?: string, replyHtml?: string, label?: string }>>([])
const stepFailed = ref(false)
const currentStepFailedInputName = ref('')

const hasClickfill = computed(() =>
  // Le vivier de cartes sert aussi aux `compose`/`textcomp`, qui y puisent
  // leurs fragments : sans eux dans ce test, les cartes ne s'afficheraient pas
  // et la zone libre resterait vide de tout ce qu'on peut y déposer.
  props.rendered?.answers.some(
    a => a.answer_type === 'clickfill'
      || a.answer_type === 'compose'
      || a.answer_type === 'textcomp'
  ) ?? false
)
// `dragfill` : étiquettes à usage unique. WIMS impose que tous les champs à
// remplir d'un exercice soient du même type, d'où un drapeau global.
const singleUseFill = computed(() =>
  props.rendered?.answers.some(a => a.options?.single_use) ?? false
)
// `rendered.answers` is already filtered server-side to the current step's
// active replies, so this is naturally correct per step.
const hasRadioAnswers = computed(() =>
  props.rendered?.answers.some(a => a.answer_type === 'radio' && !a.options?.inline) ?? false
)

// L'exercice est terminé : dernière étape franchie, ou arrêté par une réponse
// fausse sans `nonstop` (`oef/step.proc:66`) — un `course` comme un exercice à
// `\nextstep`.
const termine = ref(false)

// Analyze-checked exercises are all-or-nothing (a single combined :test
// condition), so a per-field breakdown is misleading — show just OUI/NON like
// WIMS, then the correction (feedback_html).
const isAnalyzeWhole = computed(() =>
  !!checkResult.value?.results.length &&
  checkResult.value.results.every(r => r.method === 'analyze')
)

// La note est celle que le serveur rend au dernier envoi : le bilan de
// `oef/var.proc` sur tout le parcours (`core/answer/bilan_etapes.py`), non une
// moyenne des étapes faite ici.
const noteFinale = ref<number | null>(null)
const scoreRatio = computed(() => noteFinale.value ?? 0)
const scorePct = computed(() => Math.round(scoreRatio.value * 100))

const allFilled = computed(() => {
  if (!props.rendered || termine.value) return false
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
    // Champ non noté (brouillon type=draft, ou analyze optionnel) : vide autorisé.
    return !!a.options?.ungraded
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
    notesDesEtapes.value = {}
    replies.value = {}
    termine.value = false
    noteFinale.value = null
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
  emit('load-step', nextMStep, acc, { ...notesDesEtapes.value })
}

async function submit() {
  if (!props.rendered || submitted.value) return

  checking.value = true
  try {
    const currentStep = props.rendered.current_step || 1
    const totalSteps = props.rendered.total_steps || 1
    // `total_steps` est une **estimation faite au rendu**, avant que l'élève
    // ait répondu. Pour un exercice dont la suite dépend des réponses
    // (`\nextstep`), elle vaut souvent 1 alors qu'il y a six étapes : le
    // moteur rejoue `:postdef` à vide, tourne en rond ou épuise son budget, et
    // le repli annonce une seule étape. Cinquante exercices restaient bloqués
    // sur la première.
    //
    // Le serveur, lui, vient de rejouer `:postdef` **avec** les réponses, comme
    // WIMS le fait après chaque étape : `has_next_step` dit alors s'il en reste
    // une. On ne s'en sert que pour *ajouter* une étape que l'estimation avait
    // manquée — jamais pour en retirer, et `null` (l'exercice n'a pas de
    // `\nextstep`) laisse le comportement d'avant intact.
    const replyList = Object.entries(replies.value)
      .map(([input_name, value]) => ({ input_name, value }))

    checkResult.value = await apiFetch<CheckResult>(`/api/check/${props.exerciseId}`, {
      method: 'POST',
      body: { 
        seed: props.rendered.seed, 
        replies: replyList,
        m_step: currentStep,
        // Corriger sous les réglages du rendu (niveau de sévérité, feuille).
        ...(props.rendered.reglages ?? {}),
      },
    })
    
    if (checkResult.value.has_invalid_format) {
      checking.value = false
      return
    }

    // Calculé **après** la réponse du serveur, et non avant : c'est elle qui
    // porte `has_next_step`.
    // Le serveur tranche (`fin_du_parcours`) ; l'ancienne règle ne sert que
    // s'il ne répond pas à la question.
    const encoreUneEtape = checkResult.value.has_next_step === true
    const finDuParcours = checkResult.value.fin_du_parcours
      ?? (currentStep >= totalSteps && !encoreUneEtape)

    submitted.value = true
    const answerTypes = Object.fromEntries(
      props.rendered.answers.map(a => [a.input_name, a.answer_type] as [string, string])
    )
    const inlineChoices = Object.fromEntries(
      props.rendered.answers
        .filter(a => a.answer_type === 'radio' && a.options?.inline && a.options?.choices?.length)
        .map(a => [a.input_name, a.options.choices as string[]]),
    )
    feedbackHtml.value = await buildFeedbackHtml(checkResult.value, answerTypes, inlineChoices)
    
    if (checkResult.value.feedback_html) {
      checkResult.value.feedback_html = await renderMath(checkResult.value.feedback_html, { autoDisplay: true })
    }
    if (checkResult.value.solution_html) {
      checkResult.value.solution_html = await renderMath(checkResult.value.solution_html, { autoDisplay: true })
    }

    // `rendered.answers` is server-filtered to the current step's replies.
    const activeNames = new Set(props.rendered.answers.map(a => a.input_name))
    const activeResults = checkResult.value.results.filter(r => activeNames.has(r.input_name))
    for (const res of activeResults) notesDesEtapes.value[res.input_name] = res.score
    
    // Update history for each active input in this step
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
    }

    // Une réponse fausse sans `nonstop` arrête l'exercice, `course` ou non
    // (`oef/step.proc:66`) : PAX remplissait la bonne réponse et passait à
    // l'étape suivante, si bien qu'un code de validation faux (`histocap`,
    // « Appel 1 ») laissait l'élève continuer.
    if (checkResult.value.arret) {
      stepFailed.value = true
      currentStepFailedInputName.value = activeResults.find(r => !r.correct)?.input_name ?? ''
    }

    if (activeResults.length > 0 && !finDuParcours) {
      setTimeout(async () => {
        await nextStep()
      }, 0)
    }

    if (finDuParcours) {
      termine.value = true
      // Comme WIMS : l'énoncé final montre le verdict de la dernière étape,
      // que seul le rendu à `m_step` = N+1 connaît (`uniteadn/Aadn`, Q6).
      if (checkResult.value.enonce_final?.length) {
        statementSegments.value = await buildSegments(checkResult.value.enonce_final)
      }
      noteFinale.value = checkResult.value.global_score
      const score = noteFinale.value

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
