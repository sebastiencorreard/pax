<template>
  <div>
    <div class="mb-4">
      <NuxtLink to="/exercise"
                class="text-sm hover:underline"
                style="color:var(--color-text-muted)">
        ← Retour aux exercices
      </NuxtLink>
    </div>

    <ExercisePlayer :exercise-id="exerciseId" />

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

interface Source { oef_path: string; content: string }
const source = ref<Source | null>(null)
const sourceError = ref('')

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

watch(exerciseId, loadSource, { immediate: true })
</script>
