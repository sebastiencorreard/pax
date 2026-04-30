<template>
  <div>
    <h1 class="text-2xl font-bold mb-6">{{ $t('nav.exercises') }}</h1>

    <!-- Filtres -->
    <div class="flex gap-3 mb-6 flex-wrap">
      <select v-model="filterLevel"
              class="px-3 py-2 rounded-lg border text-sm"
              style="background:var(--color-surface);border-color:var(--color-border);color:var(--color-text)">
        <option value="">{{ $t('exercise.all_levels') }}</option>
        <option v-for="l in levels" :key="l" :value="l">{{ l }}</option>
      </select>

      <select v-model="filterDomain"
              class="px-3 py-2 rounded-lg border text-sm"
              style="background:var(--color-surface);border-color:var(--color-border);color:var(--color-text)">
        <option value="">{{ $t('exercise.all_domains') }}</option>
        <option v-for="d in domains" :key="d" :value="d">{{ d }}</option>
      </select>
    </div>

    <!-- Liste -->
    <div v-if="loading" class="space-y-3">
      <div v-for="i in 5" :key="i" class="h-16 rounded-xl animate-pulse"
           style="background:var(--color-surface)"></div>
    </div>

    <div v-else-if="exercises.length === 0" class="text-center py-16"
         style="color:var(--color-text-muted)">
      {{ $t('exercise.none_found') }}
    </div>

    <div v-else class="space-y-2">
      <NuxtLink v-for="ex in exercises" :key="ex.id"
                :to="`/exercise/${ex.id}`"
                class="flex items-center justify-between px-5 py-4 rounded-xl border hover:shadow-md transition group"
                style="background:var(--color-surface);border-color:var(--color-border)">
        <div>
          <span class="font-medium group-hover:text-blue-500 transition"
                v-html="titlesHtml[ex.id] || ex.title || ex.oef_path"></span>
          <div class="flex gap-2 mt-1">
            <span v-if="ex.level" class="text-xs px-2 py-0.5 rounded"
                  style="background:var(--color-bg);color:var(--color-text-muted)">
              {{ ex.level }}
            </span>
            <span v-if="ex.domain" class="text-xs px-2 py-0.5 rounded"
                  style="background:var(--color-bg);color:var(--color-text-muted)">
              {{ ex.domain }}
            </span>
          </div>
        </div>
        <span style="color:var(--color-text-muted)">→</span>
      </NuxtLink>
    </div>
  </div>
</template>

<script setup lang="ts">
definePageMeta({ middleware: 'auth' })

const { apiFetch } = useApi()

let katexLib: any = null
async function loadKatex() {
  if (!katexLib) katexLib = (await import('katex')).default
  return katexLib
}

function decodeHtmlEntities(s: string): string {
  return s.replace(/&#(\d+);/g, (_, code) => String.fromCharCode(Number(code)))
          .replace(/&amp;/g, '&').replace(/&lt;/g, '<').replace(/&gt;/g, '>')
}

const titlesHtml = ref<Record<string, string>>({})

async function buildTitles(exList: Exercise[]) {
  const katex = await loadKatex()
  const result: Record<string, string> = {}
  for (const ex of exList) {
    const raw = ex.title || ex.oef_path
    const decoded = decodeHtmlEntities(raw)
    if (!decoded.includes('\\(') && !decoded.includes('\\[')) {
      result[ex.id] = decoded
    } else {
      result[ex.id] = decoded
        .replace(/\\\[([\s\S]*?)\\\]/g, (_, e) => katex.renderToString(e.trim(), { displayMode: true, throwOnError: false }))
        .replace(/\\\(([\s\S]*?)\\\)/g, (_, e) => katex.renderToString(e.trim(), { displayMode: false, throwOnError: false }))
    }
  }
  titlesHtml.value = result
}

interface Exercise {
  id: string
  oef_path: string
  title: string | null
  level: string | null
  domain: string | null
  lang: string
}

const exercises = ref<Exercise[]>([])
const loading = ref(true)
const filterLevel = ref('')
const filterDomain = ref('')

const levels = ['E1','E2','E3','E4','E5','E6','H1','H2','H3','H4','H5','H6','U1','U2','U3','U4']
const domains = ['algebra','analysis','geometry','number','statistics','arithmetic']

async function fetchExercises() {
  loading.value = true
  try {
    const params = new URLSearchParams({ lang: 'fr', limit: '100' })
    if (filterLevel.value) params.set('level', filterLevel.value)
    if (filterDomain.value) params.set('domain', filterDomain.value)
    exercises.value = await apiFetch<Exercise[]>(`/api/exercises/?${params}`)
    await buildTitles(exercises.value)
  } finally {
    loading.value = false
  }
}

watch([filterLevel, filterDomain], fetchExercises)
onMounted(fetchExercises)
</script>
