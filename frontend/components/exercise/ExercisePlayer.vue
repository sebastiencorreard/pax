<template>
  <div class="rounded-xl border shadow-sm overflow-hidden"
       style="background:var(--color-surface);border-color:var(--color-border)">
    <component :is="'style'" v-if="rendered?.css" scoped>{{ rendered.css }}</component>

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

    <!-- Erreur -->
    <div v-if="loadError" class="px-6 py-6">
      <div class="text-red-500 text-sm p-2 border border-red-300 rounded">
        Erreur : {{ loadError }}
      </div>
    </div>

    <!-- Contenu Principal -->
    <div class="relative min-h-[10rem]">
      <!-- Chargement (overlay) -->
      <div v-if="loading" class="absolute inset-0 z-10 flex items-center justify-center bg-white/60 dark:bg-gray-900/60 backdrop-blur-[1px] transition-opacity">
        <div class="flex flex-col items-center gap-3">
          <div class="w-8 h-8 border-4 border-blue-500/30 border-t-blue-500 rounded-full animate-spin"></div>
          <span class="text-xs font-medium text-gray-500">{{ $t('exercise.loading') }}</span>
        </div>
      </div>

      <!-- Router -->
      <template v-if="rendered">
        <DynstepsExercise
          v-if="rendered.exercise_type === 'dynsteps'"
          ref="exerciseComponent"
          :rendered="rendered"
          :exercise-id="exerciseId"
          :debug-answers="debugAnswers"
          @reload="reload"
          @load-step="(m_step) => load(rendered?.seed, m_step)"
        />
        <StandardExercise
          v-else
          ref="exerciseComponent"
          :rendered="rendered"
          :exercise-id="exerciseId"
          :debug-answers="debugAnswers"
          @reload="reload"
        />
      </template>
    </div>

    <!-- Indice -->
    <div v-if="rendered?.hint_html" class="px-6 pb-6 pt-2">
      <button @click="showHint = !showHint"
              class="px-4 py-2.5 rounded-lg text-sm border transition"
              style="border-color:var(--color-border);color:var(--color-text-muted)">
        {{ showHint ? $t('exercise.hint_hide') : $t('exercise.hint_show') }}
      </button>

      <div v-if="showHint"
           class="mt-4 px-4 py-3 rounded-lg border text-sm"
           style="border-color:var(--color-border);background:var(--color-bg)"
           v-html="hintHtml">
      </div>
    </div>

    <!-- Slot QA -->
    <div class="px-6 pb-6 flex justify-end">
      <slot name="qa" />
    </div>

  </div>
</template>

<script setup lang="ts">
import { ref, onMounted } from 'vue'
import StandardExercise from './StandardExercise.vue'
import DynstepsExercise from './DynstepsExercise.vue'
import type { Rendered } from '~/composables/useExerciseLogic'

const props = defineProps<{
  exerciseId: string
  debugAnswers?: Record<string, string> | null
}>()

const emit = defineEmits<{ rendered: [{ seed: number; exerciseId: string; currentStep?: number | null }] }>()

const { apiFetch } = useApi()
const { renderMath } = useKatex()
const { debugMode: debugOef } = useDebugMode()

const rendered = ref<Rendered | null>(null)
const hintHtml = ref('')
const titleHtml = ref('')
const loading = ref(false)
const loadError = ref('')
const showHint = ref(false)

const exerciseComponent = ref<any>(null)

async function load(seed?: number, m_step?: number) {
  loading.value = true
  loadError.value = ''
  showHint.value = false
  titleHtml.value = ''
  hintHtml.value = ''

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

onMounted(() => load())

function fillAnswers(answers: Record<string, string>) {
  if (exerciseComponent.value && exerciseComponent.value.fillAnswers) {
    // Filter answers to only fill those currently visible on screen
    const activeNames = new Set(rendered.value?.statement_segments
      .map(s => (s.type === 'input' || s.type === 'textarea' || s.type === 'slot' || s.type === 'menu') ? s.name : null)
      .filter(Boolean)
    )
    const filteredAnswers = Object.fromEntries(
      Object.entries(answers).filter(([name]) => activeNames.has(name))
    )
    exerciseComponent.value.fillAnswers(filteredAnswers)
  }
}

defineExpose({ fillAnswers })
</script>
