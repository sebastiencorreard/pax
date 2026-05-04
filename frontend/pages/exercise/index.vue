<template>
  <div>
    <h1 class="text-2xl font-bold mb-6">{{ $t('nav.exercises') }}</h1>

    <!-- Filtres -->
    <div class="flex gap-3 mb-6 flex-wrap items-center">
      <!-- Recherche plein texte -->
      <div class="relative flex-1 min-w-48">
        <span class="absolute inset-y-0 left-3 flex items-center pointer-events-none"
              style="color:var(--color-text-muted)">🔍</span>
        <input v-model="searchQuery"
               type="search"
               :placeholder="$t('exercise.search_placeholder')"
               class="w-full pl-9 pr-3 py-2 rounded-lg border text-sm"
               style="background:var(--color-surface);border-color:var(--color-border);color:var(--color-text)" />
      </div>

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

      <div v-if="debugOef" class="ml-auto flex items-center gap-3 text-sm"
           style="color:var(--color-text)">
        <label v-for="flag in qaFlags" :key="flag"
               class="inline-flex items-center gap-1.5 cursor-pointer">
          <input type="checkbox" v-model="qaFilters[flag]" />
          <span class="font-mono text-xs">{{ flag }}</span>
        </label>
      </div>
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
                        style="border-color:var(--color-border)"
                        @contextmenu.prevent="auth.isTeacher && openContextMenu(ex, $event)">
                <span class="text-sm group-hover:text-blue-500 transition truncate">
                  {{ decodeEntities(ex.title || ex.id) }}
                </span>
                <div class="ml-4 flex items-center gap-2 flex-shrink-0">
                  <span v-if="!ex.has_def"
                        class="text-xs font-bold px-1.5 py-0.5 rounded"
                        style="background:#ef4444;color:#fff"
                        title="Fichier .def absent — moteur OEF de secours">
                    OEF
                  </span>
                  <span class="text-sm" style="color:var(--color-text-muted)">→</span>
                </div>
              </NuxtLink>
            </div>
          </div>
        </div>
      </div>
    </div>

    <!-- Menu contextuel tags (clic droit, teachers/admins uniquement) -->
    <TagContextMenu v-if="contextMenu"
                    :exercise-id="contextMenu.exerciseId"
                    :exercise-title="contextMenu.exerciseTitle"
                    :raw-x="contextMenu.x"
                    :raw-y="contextMenu.y"
                    @close="contextMenu = null" />
  </div>
</template>

<script setup lang="ts">
interface ModuleExercise {
  id: string
  title: string | null
  has_def: boolean
  author: string
  keywords: string[]
  statement_ok: boolean | null
  answer_ok: boolean | null
  check_ok: boolean | null
}

type QAFlag = 'statement_ok' | 'answer_ok' | 'check_ok'
const qaFlags: QAFlag[] = ['statement_ok', 'answer_ok', 'check_ok']

interface Module {
  module: string
  title: string
  description: string
  author: string
  keywords: string[]
  domain: string
  level: string
  lang: string
  exercises: ModuleExercise[]
}

interface DomainGroup {
  domain: string
  modules: Module[]
}

const auth = useAuthStore()
const { apiFetch } = useApi()
const debugOef = useRuntimeConfig().public.debugOef

// Menu contextuel (clic droit) — tags
interface ContextMenuState {
  exerciseId: string
  exerciseTitle: string
  x: number
  y: number
}
const contextMenu = ref<ContextMenuState | null>(null)

function openContextMenu(ex: ModuleExercise, event: MouseEvent) {
  contextMenu.value = {
    exerciseId: ex.id,
    exerciseTitle: decodeEntities(ex.title || ex.id),
    x: event.clientX,
    y: event.clientY,
  }
}

function decodeEntities(s: string): string {
  return (s || '')
    .replace(/&#(\d+);/g, (_, code) => String.fromCharCode(Number(code)))
    .replace(/&amp;/g, '&')
    .replace(/&lt;/g, '<')
    .replace(/&gt;/g, '>')
    .replace(/&nbsp;/g, ' ')
}

const route = useRoute()
const router = useRouter()

const modules = ref<Module[]>([])
const loading = ref(true)
const filterLevel = ref((route.query.level as string) || '')
const filterDomain = ref((route.query.domain as string) || '')
const searchQuery = ref((route.query.q as string) || '')
const qaFilters = ref<Record<QAFlag, boolean>>({
  statement_ok: false, answer_ok: false, check_ok: false,
})

// Synchronise les filtres dans l'URL sans créer d'entrée dans l'historique
watch([filterLevel, filterDomain, searchQuery], ([level, domain, q]) => {
  router.replace({
    query: {
      ...(level  ? { level }  : {}),
      ...(domain ? { domain } : {}),
      ...(q      ? { q }      : {}),
    },
  })
}, { flush: 'sync' })
const openModules = ref(new Set<string>())

const levels = ['E1','E2','E3','E4','E5','E6','H1','H2','H3','H4','H5','H6','U1','U2','U3','U4']

const availableDomains = computed(() =>
  [...new Set(modules.value.map(m => m.domain))].sort()
)

const activeQaFlags = computed(() =>
  qaFlags.filter(f => qaFilters.value[f]),
)

function exerciseMatchesQa(ex: ModuleExercise): boolean {
  for (const f of activeQaFlags.value) {
    if (ex[f] !== true) return false
  }
  return true
}

function exerciseMatchesSearch(ex: ModuleExercise, q: string): boolean {
  if ((ex.title || '').toLowerCase().includes(q)) return true
  if (ex.author.toLowerCase().includes(q)) return true
  return ex.keywords.some(k => k.toLowerCase().includes(q))
}

function moduleMatchesSearch(m: Module, q: string): boolean {
  if (m.title.toLowerCase().includes(q)) return true
  if (m.author.toLowerCase().includes(q)) return true
  return m.keywords.some(k => k.toLowerCase().includes(q))
}

const filteredModules = computed(() => {
  const q = searchQuery.value.trim().toLowerCase()

  return modules.value
    .filter(m => {
      if (filterLevel.value && m.level !== filterLevel.value) return false
      if (filterDomain.value && m.domain !== filterDomain.value) return false
      return true
    })
    .map(m => {
      let exercises = m.exercises

      if (activeQaFlags.value.length > 0) {
        exercises = exercises.filter(exerciseMatchesQa)
      }

      if (q) {
        const modMatches = moduleMatchesSearch(m, q)
        if (!modMatches) {
          exercises = exercises.filter(ex => exerciseMatchesSearch(ex, q))
        }
        // If module itself matches, keep all its exercises visible
      }

      return { ...m, exercises }
    })
    .filter(m => m.exercises.length > 0)
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

// Auto-expand all modules when searching, collapse when query cleared
watch(searchQuery, (q) => {
  if (q.trim()) {
    openModules.value = new Set(filteredModules.value.map(m => m.module))
  } else {
    openModules.value = new Set()
  }
})

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
