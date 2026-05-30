<template>
  <div class="px-6 py-6">
    <h1 class="text-2xl font-bold mb-6">{{ $t('nav.exercises') }}</h1>

    <!-- Filtres (pleine largeur) -->
    <div class="flex gap-3 mb-6 flex-wrap items-center">
      <div class="flex flex-1 min-w-56 rounded-lg border overflow-hidden"
           style="border-color:var(--color-border)">
        <select v-model="searchScope"
                class="py-2 pl-3 pr-1 border-r text-sm shrink-0 cursor-pointer"
                style="background:var(--color-surface);border-color:var(--color-border);color:var(--color-text-muted)">
          <option value="modules">{{ $t('exercise.scope_modules') }}</option>
          <option value="exercises">{{ $t('exercise.scope_exercises') }}</option>
          <option value="all">{{ $t('exercise.scope_all') }}</option>
        </select>
        <div class="relative flex-1">
          <span class="absolute inset-y-0 left-3 flex items-center pointer-events-none"
                style="color:var(--color-text-muted)">🔍</span>
          <input v-model="searchQuery"
                 type="search"
                 :placeholder="$t('exercise.search_placeholder')"
                 class="w-full pl-9 pr-3 py-2 text-sm"
                 style="background:var(--color-surface);color:var(--color-text)" />
        </div>
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
    </div>

    <!-- Layout : liste seule sur petit écran, liste + preview sur lg+ -->
    <div class="lg:flex lg:gap-6 lg:items-start">

      <!-- Colonne gauche : liste (sticky + scrollable sur lg+) -->
      <div class="lg:w-80 lg:flex-shrink-0 lg:sticky lg:top-4 lg:max-h-[calc(100vh-5rem)] lg:overflow-y-auto">

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
        <div v-else class="space-y-6">
          <div v-for="group in groupedModules" :key="group.domain">
            <h2 class="text-xs font-semibold uppercase tracking-wider mb-2"
                style="color:var(--color-text-muted)">
              {{ group.domain }}
            </h2>

            <div class="space-y-1.5">
              <div v-for="mod in group.modules" :key="mod.module"
                   class="rounded-xl border overflow-hidden"
                   style="background:var(--color-surface);border-color:var(--color-border)">

                <button class="w-full flex items-center justify-between px-4 py-3 text-left hover:bg-black/5 dark:hover:bg-white/5 transition"
                        @click="toggle(mod.module)">
                  <div class="flex-1 min-w-0">
                    <MathText :text="mod.title" class="font-medium text-sm block truncate" />
                    <div class="flex items-center gap-2 mt-0.5">
                      <span v-if="mod.author" class="text-xs truncate"
                            style="color:var(--color-text-muted)">{{ mod.author }}</span>
                      <span class="text-xs px-1.5 py-0.5 rounded flex-shrink-0"
                            style="background:var(--color-bg);color:var(--color-text-muted)">
                        {{ mod.exercises.length }}
                      </span>
                    </div>
                  </div>
                  <span class="ml-2 flex-shrink-0 transition-transform duration-200"
                        :style="openModules.has(mod.module) ? 'transform:rotate(90deg)' : ''"
                        style="color:var(--color-text-muted)">›</span>
                </button>

                <div v-if="openModules.has(mod.module)"
                     class="border-t"
                     style="border-color:var(--color-border)">
                  <NuxtLink v-for="ex in mod.exercises"
                            :key="ex.id"
                            :to="`/exercise/${ex.id}`"
                            class="flex items-center justify-between px-4 py-2.5 transition group border-b last:border-b-0"
                            :class="previewId === ex.id ? '' : 'hover:bg-black/5 dark:hover:bg-white/5'"
                            :style="previewId === ex.id
                              ? 'border-color:var(--color-border);background:color-mix(in srgb,var(--color-primary) 8%,transparent)'
                              : 'border-color:var(--color-border)'"
                            @click="onExerciseClick(ex.id, $event)">
                    <MathText :text="ex.title || ex.id"
                          class="text-xs truncate transition"
                          :style="previewId === ex.id ? 'color:var(--color-primary);font-weight:600' : ''" />
                    <div class="ml-2 flex items-center gap-1.5 flex-shrink-0">
                      <span v-if="!ex.has_def"
                            class="text-xs font-bold px-1 py-0.5 rounded"
                            style="background:#ef4444;color:#fff">OEF</span>
                      <span class="text-xs"
                            :style="previewId === ex.id ? 'color:var(--color-primary)' : 'color:var(--color-text-muted)'">
                        {{ previewId === ex.id ? '▶' : '›' }}
                      </span>
                    </div>
                  </NuxtLink>
                </div>
              </div>
            </div>
          </div>
        </div>
      </div>

      <!-- Colonne droite : preview (invisible sur petit écran) -->
      <div class="hidden lg:block lg:flex-1 lg:sticky lg:top-4 lg:max-h-[calc(100vh-5rem)] lg:overflow-y-auto">
        <ExerciseDetail v-if="previewId"
                        :exercise-id="previewId"
                        :key="previewId" />
        <div v-else
             class="rounded-xl border-2 border-dashed flex flex-col items-center justify-center py-24 text-center"
             style="border-color:var(--color-border)">
          <span class="text-4xl mb-4 opacity-30">📖</span>
          <p class="text-sm" style="color:var(--color-text-muted)">
            {{ $t('exercise.preview_hint') }}
          </p>
        </div>
      </div>

    </div>
  </div>
</template>

<script setup lang="ts">
definePageMeta({ layout: 'dashboard' })
interface ModuleExercise {
  id: string
  title: string | null
  has_def: boolean
  author: string
  keywords: string[]
}

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

const { apiFetch } = useApi()
const { debugMode: debugOef } = useDebugMode()

const route = useRoute()
const router = useRouter()
const isLarge = useMediaQuery('(min-width: 1024px)')

type SearchScope = 'all' | 'modules' | 'exercises'

const modules = ref<Module[]>([])
const loading = ref(true)
const filterLevel = ref((route.query.level as string) || '')
const filterDomain = ref((route.query.domain as string) || '')
const searchQuery = ref((route.query.q as string) || '')
const searchScope = ref<SearchScope>((route.query.scope as SearchScope) || 'modules')
const previewId = ref<string | null>((route.query.preview as string) || null)

watch([filterLevel, filterDomain, searchQuery, searchScope, previewId], ([level, domain, q, scope, preview]) => {
  router.replace({
    query: {
      ...(level   ? { level }   : {}),
      ...(domain  ? { domain }  : {}),
      ...(q       ? { q }       : {}),
      ...(scope !== 'all' ? { scope } : {}),
      ...(preview ? { preview } : {}),
    },
  })
}, { flush: 'sync' })

const openModules = ref(new Set<string>())

const levels = ['E1','E2','E3','E4','E5','E6','H1','H2','H3','H4','H5','H6','U1','U2','U3','U4']

const availableDomains = computed(() =>
  [...new Set(modules.value.map(m => m.domain))].sort()
)

function exerciseMatchesSearch(ex: ModuleExercise, q: string): boolean {
  if ((ex.title || '').toLowerCase().includes(q)) return true
  if (ex.author.toLowerCase().includes(q)) return true
  return ex.keywords.some(k => k.toLowerCase().includes(q))
}

function moduleMatchesSearch(m: Module, q: string): boolean {
  if (m.title.toLowerCase().includes(q)) return true
  if (m.author.toLowerCase().includes(q)) return true
  if (m.description.toLowerCase().includes(q)) return true
  return m.keywords.some(k => k.toLowerCase().includes(q))
}

const filteredModules = computed(() => {
  const q = searchQuery.value.trim().toLowerCase()
  const scope = searchScope.value

  return modules.value
    .filter(m => {
      if (filterLevel.value && m.level !== filterLevel.value) return false
      if (filterDomain.value && m.domain !== filterDomain.value) return false
      return true
    })
    .map(m => {
      let exercises = m.exercises

      if (q) {
        if (scope === 'modules') {
          if (!moduleMatchesSearch(m, q)) return { ...m, exercises: [] }
        } else if (scope === 'exercises') {
          exercises = exercises.filter(ex => exerciseMatchesSearch(ex, q))
        } else {
          if (!moduleMatchesSearch(m, q)) {
            exercises = exercises.filter(ex => exerciseMatchesSearch(ex, q))
          }
        }
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

function onExerciseClick(id: string, event: MouseEvent) {
  // Ctrl/Cmd+clic : laisser le navigateur ouvrir dans un nouvel onglet
  if (event.ctrlKey || event.metaKey) return
  // Grand écran : afficher dans la preview sans naviguer
  if (isLarge.value) {
    event.preventDefault()
    previewId.value = id
  }
  // Petit écran : navigation normale via NuxtLink
}

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
