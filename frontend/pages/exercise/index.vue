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
        <option v-for="d in availableDomains" :key="d" :value="d">{{ d }}</option>
      </select>
    </div>

    <!-- Skeleton loading -->
    <div v-if="loading" class="space-y-3">
      <div v-for="i in 6" :key="i" class="h-16 rounded-xl animate-pulse"
           style="background:var(--color-surface)"></div>
    </div>

    <!-- Empty state -->
    <div v-else-if="groupedModules.length === 0"
         class="text-center py-16"
         style="color:var(--color-text-muted)">
      {{ $t('exercise.none_found') }}
    </div>

    <!-- Modules groupés par domaine -->
    <div v-else class="space-y-8">
      <div v-for="group in groupedModules" :key="group.domain">
        <!-- En-tête de domaine -->
        <h2 class="text-sm font-semibold uppercase tracking-wider mb-3"
            style="color:var(--color-text-muted)">
          {{ group.domain }}
        </h2>

        <div class="space-y-2">
          <div v-for="mod in group.modules" :key="mod.module"
               class="rounded-xl border overflow-hidden"
               style="background:var(--color-surface);border-color:var(--color-border)">

            <!-- En-tête du module (cliquable) -->
            <button class="w-full flex items-center justify-between px-5 py-4 text-left hover:bg-black/5 dark:hover:bg-white/5 transition"
                    @click="toggle(mod.module)">
              <div class="flex-1 min-w-0">
                <span class="font-medium block truncate">{{ decodeEntities(mod.title) }}</span>
                <div class="flex items-center gap-3 mt-1 flex-wrap">
                  <span v-if="mod.author"
                        class="text-xs"
                        style="color:var(--color-text-muted)">
                    {{ mod.author }}
                  </span>
                  <span class="text-xs px-2 py-0.5 rounded"
                        style="background:var(--color-bg);color:var(--color-text-muted)">
                    {{ mod.exercises.length }} {{ $t('exercise.exercises_count') }}
                  </span>
                </div>
              </div>
              <span class="ml-4 text-lg transition-transform duration-200"
                    :style="openModules.has(mod.module) ? 'transform:rotate(180deg)' : ''"
                    style="color:var(--color-text-muted)">
                ›
              </span>
            </button>

            <!-- Liste d'exercices (accordéon) -->
            <div v-if="openModules.has(mod.module)"
                 class="border-t"
                 style="border-color:var(--color-border)">
              <NuxtLink v-for="ex in mod.exercises"
                        :key="ex.id"
                        :to="`/exercise/${ex.id}`"
                        class="flex items-center justify-between px-6 py-3 hover:bg-black/5 dark:hover:bg-white/5 transition group border-b last:border-b-0"
                        style="border-color:var(--color-border)">
                <span class="text-sm group-hover:text-blue-500 transition truncate">
                  {{ decodeEntities(ex.title || ex.id) }}
                </span>
                <span class="ml-4 text-sm flex-shrink-0"
                      style="color:var(--color-text-muted)">→</span>
              </NuxtLink>
            </div>
          </div>
        </div>
      </div>
    </div>
  </div>
</template>

<script setup lang="ts">
interface ModuleExercise {
  id: string
  title: string | null
}

interface Module {
  module: string
  title: string
  description: string
  author: string
  domain: string
  level: string
  lang: string
  exercises: ModuleExercise[]
}

interface DomainGroup {
  domain: string
  modules: Module[]
}

const { apiFetch } = useApi()

function decodeEntities(s: string): string {
  return (s || '')
    .replace(/&#(\d+);/g, (_, code) => String.fromCharCode(Number(code)))
    .replace(/&amp;/g, '&')
    .replace(/&lt;/g, '<')
    .replace(/&gt;/g, '>')
    .replace(/&nbsp;/g, ' ')
}

const modules = ref<Module[]>([])
const loading = ref(true)
const filterLevel = ref('')
const filterDomain = ref('')
const openModules = ref(new Set<string>())

const levels = ['E1','E2','E3','E4','E5','E6','H1','H2','H3','H4','H5','H6','U1','U2','U3','U4']

const availableDomains = computed(() =>
  [...new Set(modules.value.map(m => m.domain))].sort()
)

const filteredModules = computed(() => {
  return modules.value.filter(m => {
    if (filterLevel.value && m.level !== filterLevel.value) return false
    if (filterDomain.value && m.domain !== filterDomain.value) return false
    return true
  })
})

const groupedModules = computed<DomainGroup[]>(() => {
  const map = new Map<string, Module[]>()
  for (const mod of filteredModules.value) {
    const d = mod.domain || '—'
    if (!map.has(d)) map.set(d, [])
    map.get(d)!.push(mod)
  }
  return [...map.entries()]
    .sort(([a], [b]) => a.localeCompare(b))
    .map(([domain, mods]) => ({ domain, modules: mods }))
})

function toggle(moduleId: string) {
  if (openModules.value.has(moduleId)) {
    openModules.value.delete(moduleId)
  } else {
    openModules.value.add(moduleId)
  }
}

async function fetchModules() {
  loading.value = true
  try {
    const params = new URLSearchParams({ lang: 'fr' })
    modules.value = await apiFetch<Module[]>(`/api/exercises/modules?${params}`)
  } finally {
    loading.value = false
  }
}

onMounted(fetchModules)
</script>
