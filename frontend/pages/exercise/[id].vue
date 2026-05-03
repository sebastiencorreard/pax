<template>
  <div>
    <div class="mb-4">
      <NuxtLink to="/exercise"
                class="text-sm hover:underline"
                style="color:var(--color-text-muted)">
        ← Retour aux exercices
      </NuxtLink>
    </div>

    <ExercisePlayer :exercise-id="exerciseId" @rendered="onRendered" />

    <section v-if="debugOef" class="mt-6 rounded-xl border overflow-hidden"
             style="background:var(--color-surface);border-color:var(--color-border)">
      <header class="px-4 py-2 border-b flex items-center justify-between text-xs"
              style="border-color:var(--color-border);color:var(--color-text-muted)">
        <span class="font-mono">QA status</span>
        <span>debug · NUXT_PUBLIC_DEBUG_OEF</span>
      </header>
      <div class="px-4 py-3 text-sm flex flex-wrap gap-4" style="color:var(--color-text)">
        <label v-for="flag in qaFlags" :key="flag"
               class="inline-flex items-center gap-2 cursor-pointer">
          <input type="checkbox"
                 :checked="qa[flag] === true"
                 :disabled="qaSaving[flag]"
                 @change="onQaToggle(flag, ($event.target as HTMLInputElement).checked)" />
          <span class="font-mono text-xs">{{ flag }}</span>
          <span v-if="qaSaving[flag]" class="text-xs"
                style="color:var(--color-text-muted)">…</span>
        </label>
        <span v-if="qaError" class="text-xs text-red-500">{{ qaError }}</span>
      </div>
    </section>

    <section v-if="debugOef" class="mt-6 rounded-xl border overflow-hidden"
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

    <section v-if="debugOef" class="mt-6 rounded-xl border overflow-hidden"
             style="background:var(--color-surface);border-color:var(--color-border)">
      <header class="px-4 py-2 border-b flex items-center justify-between text-xs"
              style="border-color:var(--color-border);color:var(--color-text-muted)">
        <span class="font-mono">solution · seed {{ debug?.seed ?? '…' }}</span>
        <span>debug · NUXT_PUBLIC_DEBUG_OEF</span>
      </header>
      <pre v-if="debugError" class="px-4 py-3 text-sm text-red-500">{{ debugError }}</pre>
      <div v-else-if="debug" class="px-4 py-3 text-sm space-y-3" style="color:var(--color-text)">
        <div v-if="solutionHtml" v-html="solutionHtml"></div>
        <ul v-if="debug.answers.length" class="space-y-1">
          <li v-for="ans in debug.answers" :key="ans.input_name" class="flex items-baseline gap-2 flex-wrap">
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

    <section v-if="debugOef" class="mt-6 rounded-xl border overflow-hidden"
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
const route = useRoute()
const exerciseId = computed(() => route.params.id as string)

const debugOef = useRuntimeConfig().public.debugOef
const { apiFetch } = useApi()
const { renderMath } = useKatex()

interface Source { oef_path: string; content: string }
const source = ref<Source | null>(null)
const sourceError = ref('')

type QAFlag = 'statement_ok' | 'answer_ok' | 'check_ok'
const qaFlags: QAFlag[] = ['statement_ok', 'answer_ok', 'check_ok']
interface ExerciseMeta {
  id: string
  oef_path: string
  module: string | null
  module_title: string | null
  statement_ok: boolean | null
  answer_ok: boolean | null
  check_ok: boolean | null
}
const exercise = ref<ExerciseMeta | null>(null)
// Prefer the title from the module's INDEX file; fall back to the module
// directory name (parts[len-3] of /ressources/.../<module>/src/<file>.oef)
// if no INDEX is found.
const moduleName = computed(() => {
  if (exercise.value?.module_title) return exercise.value.module_title
  if (exercise.value?.module) return exercise.value.module
  const path = exercise.value?.oef_path || ''
  const parts = path.split('/').filter(Boolean)
  return parts.length >= 3 ? parts[parts.length - 3] : ''
})
const qa = ref<Record<QAFlag, boolean | null>>({
  statement_ok: null, answer_ok: null, check_ok: null,
})
const qaSaving = ref<Record<QAFlag, boolean>>({
  statement_ok: false, answer_ok: false, check_ok: false,
})
const qaError = ref('')

async function loadQa() {
  if (!debugOef) return
  qaError.value = ''
  try {
    const ex = await apiFetch<ExerciseMeta>(`/api/exercises/${exerciseId.value}`)
    exercise.value = ex
    qa.value = {
      statement_ok: ex.statement_ok,
      answer_ok: ex.answer_ok,
      check_ok: ex.check_ok,
    }
  } catch (e: any) {
    qaError.value = e?.data?.detail || e?.message || String(e)
  }
}

async function onQaToggle(flag: QAFlag, checked: boolean) {
  const prev = qa.value[flag]
  qa.value[flag] = checked
  qaSaving.value[flag] = true
  qaError.value = ''
  try {
    const updated = await apiFetch<ExerciseMeta>(
      `/api/exercises/${exerciseId.value}/qa`,
      { method: 'PATCH', body: { [flag]: checked } },
    )
    qa.value[flag] = updated[flag]
  } catch (e: any) {
    qa.value[flag] = prev
    qaError.value = e?.data?.detail || e?.message || String(e)
  } finally {
    qaSaving.value[flag] = false
  }
}

interface DebugAnswer { input_name: string; label: string; answer_type: string; expected: string }
interface Debug { exercise_id: string; seed: number; solution_html: string; answers: DebugAnswer[] }
const debug = ref<Debug | null>(null)
const debugError = ref('')
const solutionHtml = ref('')
const expectedHtml = ref<Record<string, string>>({})

async function loadSource() {
  if (!debugOef) return
  source.value = null
  sourceError.value = ''
  try {
    source.value = await apiFetch<Source>(`/api/exercises/${exerciseId.value}/source`)
  } catch (e: any) {
    sourceError.value = e?.data?.detail || e?.message || String(e)
  }
}

function expectedToLatex(s: string): string {
  if (!s) return '—'
  if (s.startsWith('\\(') || s.startsWith('\\[')) return s
  return `\\(${s.replace(/\*\*/g, '^').replace(/\*/g, '')}\\)`
}

async function onRendered(payload: { seed: number; exerciseId: string }) {
  if (!debugOef) return
  debug.value = null
  debugError.value = ''
  solutionHtml.value = ''
  expectedHtml.value = {}
  try {
    const data = await apiFetch<Debug>(
      `/api/render/${payload.exerciseId}/debug?seed=${payload.seed}`
    )
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

watch(exerciseId, () => { loadSource(); loadQa() }, { immediate: true })
</script>
