<template>
  <div>
    <ExercisePlayer ref="playerRef"
                    :exercise-id="exerciseId"
                    :debug-answers="autofillMap"
                    @rendered="onRendered">
    </ExercisePlayer>

    <TagEditor v-if="auth.isTeacher" :exercise-id="exerciseId" class="mt-4" />

    <section v-if="debugOef" class="mt-4 rounded-xl border overflow-hidden"
             style="background:var(--color-surface);border-color:var(--color-border)">
      <header class="px-4 py-2 border-b flex items-center justify-between text-xs"
              style="border-color:var(--color-border);color:var(--color-text-muted)">
        <span class="font-mono">solution · seed {{ debug?.seed ?? '…' }}</span>
        <span>debug · NUXT_PUBLIC_DEBUG_OEF</span>
      </header>
      <pre v-if="debugError" class="px-4 py-3 text-sm text-red-500">{{ debugError }}</pre>
      <div v-else-if="debug" class="px-4 py-3 text-sm space-y-3" style="color:var(--color-text)">
        <div v-if="solutionHtml" v-html="solutionHtml"></div>
        <pre v-if="debug.solution_html"
             class="text-xs p-2 rounded overflow-auto whitespace-pre-wrap"
             style="background:var(--color-bg);color:var(--color-text-muted)">{{ debug.solution_html }}</pre>
        <ul v-if="debug.answers.length" class="space-y-1">
          <li v-for="ans in debug.answers" :key="ans.input_name"
              class="flex items-baseline gap-2 flex-wrap">
            <span class="font-mono text-xs px-1.5 py-0.5 rounded"
                  style="background:var(--color-bg);color:var(--color-text-muted)">
              {{ ans.input_name }}
            </span>
            <span class="text-xs" style="color:var(--color-text-muted)">{{ ans.answer_type }}</span>
            <span style="color:var(--color-text-muted)">→</span>
            <span v-html="expectedHtml[ans.input_name]"></span>
          </li>
        </ul>
        <div v-else style="color:var(--color-text-muted)">{{ $t('exercise.loading') }}</div>
      </div>
      <div v-else class="px-4 py-3 text-xs" style="color:var(--color-text-muted)">…</div>
    </section>

    <section v-if="debugOef" class="mt-4 rounded-xl border overflow-hidden"
             style="background:var(--color-surface);border-color:var(--color-border)">
      <header class="px-4 py-2 border-b flex items-center justify-between text-xs"
              style="border-color:var(--color-border);color:var(--color-text-muted)">
        <span class="font-mono">metadata</span>
        <span>debug · NUXT_PUBLIC_DEBUG_OEF</span>
      </header>
      <dl class="px-4 py-3 text-sm grid grid-cols-[max-content_1fr] gap-x-4 gap-y-1"
          style="color:var(--color-text)">
        <dt class="font-mono text-xs" style="color:var(--color-text-muted)">module</dt>
        <dd class="font-mono text-xs">{{ moduleName || '—' }}</dd>
      </dl>
    </section>

    <section v-if="debugOef" class="mt-4 rounded-xl border overflow-hidden"
             style="background:var(--color-surface);border-color:var(--color-border)">
      <header class="px-4 py-2 border-b flex items-center justify-between text-xs"
              style="border-color:var(--color-border);color:var(--color-text-muted)">
        <span class="font-mono">{{ source?.oef_path || $t('exercise.loading') }}</span>
        <span>debug · NUXT_PUBLIC_DEBUG_OEF</span>
      </header>
      <pre v-if="sourceError" class="px-4 py-3 text-sm text-red-500">{{ sourceError }}</pre>
      <pre v-else-if="source" class="px-4 py-3 text-xs overflow-auto max-h-[60vh] whitespace-pre"
           style="color:var(--color-text)">{{ source.content }}</pre>
      <div v-else class="px-4 py-3 text-xs" style="color:var(--color-text-muted)">…</div>
    </section>
  </div>
</template>

<script setup lang="ts">
const props = defineProps<{ exerciseId: string }>()

const auth = useAuthStore()
const { debugMode: debugOef } = useDebugMode()
const { apiFetch } = useApi()
const { renderMath } = useKatex()

const playerRef = ref<{ fillAnswers: (a: Record<string, string>) => void } | null>(null)

// Convertit la notation Python du backend en notation de saisie : x**2 → x^2, 3*x → 3x
function toInputValue(s: string): string {
  if (!s || s === '—') return ''
  return s.replace(/\*\*/g, '^').replace(/\*/g, '').replace(/\s+/g, '')
}

// Map {reply1: 'valeur brute', ...} transmise à ExercisePlayer pour le bouton fill
const autofillMap = computed<Record<string, string> | null>(() => {
  if (!debug.value?.answers.length) return null
  return Object.fromEntries(debug.value.answers.map(a => {
    if (['menu', 'radio', 'clickfill'].includes(a.answer_type)) {
      return [a.input_name, a.expected]
    }
    return [a.input_name, toInputValue(a.expected)]
  }))
})

interface ExerciseMeta {
  id: string; oef_path: string; module: string | null; module_title: string | null
}
interface Source { oef_path: string; content: string }
interface DebugAnswer { input_name: string; label: string; answer_type: string; expected: string }
interface Debug { exercise_id: string; seed: number; solution_html: string; answers: DebugAnswer[] }

const exercise = ref<ExerciseMeta | null>(null)
const source = ref<Source | null>(null)
const sourceError = ref('')
const debug = ref<Debug | null>(null)
const debugError = ref('')
const solutionHtml = ref('')
const expectedHtml = ref<Record<string, string>>({})

const moduleName = computed(() => {
  if (exercise.value?.module_title) return exercise.value.module_title
  if (exercise.value?.module) return exercise.value.module
  const parts = (exercise.value?.oef_path || '').split('/').filter(Boolean)
  return parts.length >= 3 ? parts[parts.length - 3] : ''
})

async function loadQa() {
  if (!debugOef) return
  try {
    const ex = await apiFetch<ExerciseMeta>(`/api/exercises/${props.exerciseId}`)
    exercise.value = ex
  } catch (e: any) {
    // console.error(e)
  }
}

async function loadSource() {
  if (!debugOef) return
  source.value = null
  sourceError.value = ''
  try {
    source.value = await apiFetch<Source>(`/api/exercises/${props.exerciseId}/source`)
  } catch (e: any) {
    sourceError.value = e?.data?.detail || e?.message || String(e)
  }
}

function expectedToLatex(s: string): string {
  if (!s) return '—'
  if (s.startsWith('\\(') || s.startsWith('\\[')) return s
  return `\\(${s.replace(/\*\*/g, '^').replace(/\*/g, '')}\\)`
}

async function onRendered(payload: { seed: number; exerciseId: string; currentStep?: number | null }) {
  if (!debugOef) return
  debug.value = null
  debugError.value = ''
  solutionHtml.value = ''
  expectedHtml.value = {}
  try {
    const params = new URLSearchParams()
    params.append('seed', payload.seed.toString())
    if (payload.currentStep) params.append('m_step', payload.currentStep.toString())
    const data = await apiFetch<Debug>(`/api/render/${payload.exerciseId}/debug?${params.toString()}`)
    debug.value = data
    if (data.solution_html) solutionHtml.value = await renderMath(data.solution_html)
    const map: Record<string, string> = {}
    for (const a of data.answers) {
      map[a.input_name] = await renderMath(expectedToLatex(a.expected))
    }
    expectedHtml.value = map
  } catch (e: any) {
    debugError.value = e?.data?.detail || e?.message || String(e)
  }
}

watch(() => props.exerciseId, () => {
  // Réinitialise l'état debug quand l'exercice change (navigation dans la preview)
  debug.value = null
  source.value = null
  exercise.value = null
  loadSource()
  loadQa()
}, { immediate: true })
</script>
