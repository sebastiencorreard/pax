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
        <option v-for="l in levels" :key="l.code" :value="l.code">
          {{ levelLabel(l.code!) }} ({{ l.count }})
        </option>
      </select>

      <select v-model="filterDomain"
              class="px-3 py-2 rounded-lg border text-sm"
              style="background:var(--color-surface);border-color:var(--color-border);color:var(--color-text)">
        <option value="">{{ $t('exercise.all_domains') }}</option>
        <option v-for="d in domains" :key="d.name" :value="d.name">
          {{ d.name }} ({{ d.count }})
        </option>
      </select>
    </div>

    <!-- Ce que le filtre courant laisse : un compte, et l'aveu d'une liste coupée -->
    <div
      class="flex items-center gap-3 mb-4 text-sm min-h-5"
      style="color:var(--color-text-muted)">
      <span v-if="searching">{{ $t('exercise.searching') }}</span>
      <span v-else-if="!loading">{{ $t('exercise.results_count', { n: total }, total) }}</span>
      <span
        v-if="truncated"
        style="color:var(--color-primary)">{{ $t('exercise.refine') }}</span>
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
                        {{ mod.match_count ?? mod.exercise_count }}
                      </span>
                      <span
                        class="text-xs px-1.5 py-0.5 rounded flex-shrink-0"
                        style="background:var(--color-bg);color:var(--color-text-muted)">
                        {{ levelLabel(mod.level) }}
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
                  <NuxtLink v-for="ex in exercisesOf(mod)"
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
  exercise_count: number
  match_count?: number
  exercises: ModuleExercise[]
}

interface Facette { code?: string, name?: string, count: number }

interface Catalogue {
  modules: Module[]
  levels: Facette[]
  domains: Facette[]
  total: number
  searched: boolean
  truncated: boolean
}

interface DomainGroup {
  domain: string
  modules: Module[]
}

const { apiFetch } = useApi()
const { t, te } = useI18n()

const route = useRoute()
const router = useRouter()
const isLarge = useMediaQuery('(min-width: 1024px)')

type SearchScope = 'all' | 'modules' | 'exercises'

const modules = ref<Module[]>([])
const levels = ref<Facette[]>([])
const domains = ref<Facette[]>([])
const total = ref(0)
const truncated = ref(false)
const loading = ref(true)
const searching = ref(false)

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
// Exercices chargés à la demande, un module à la fois : `/modules` n'en renvoie
// plus aucun tant qu'aucune recherche ne les désigne.
const loadedExercises = ref<Record<string, ModuleExercise[]>>({})

/**
 * Le libellé d'un niveau : le code WIMS, suivi de la classe correspondante
 * quand la locale la connaît. La table (`exercise.levels`) ne couvre que les
 * niveaux réellement présents en base — H3 et H4 aujourd'hui ; un niveau
 * ajouté au corpus s'affiche par son code jusqu'à ce qu'on lui donne sa
 * traduction, plutôt que de disparaître ou d'afficher une clé manquante.
 */
function levelLabel(code: string): string {
  const cle = `exercise.levels.${code}`
  return te(cle) ? t('exercise.level_with_code', { code, label: t(cle) }) : code
}

const groupedModules = computed<DomainGroup[]>(() => {
  const map = new Map<string, Module[]>()
  for (const mod of modules.value) {
    const d = mod.domain || '—'
    if (!map.has(d)) map.set(d, [])
    map.get(d)!.push(mod)
  }
  return [...map.entries()]
    .sort(([a], [b]) => a.localeCompare(b))
    .map(([domain, mods]) => ({ domain, modules: mods }))
})

/** Les exercices à afficher sous un module : ceux d'une recherche, ou ceux
 *  qu'un dépliage est allé chercher. */
function exercisesOf(mod: Module): ModuleExercise[] {
  return mod.exercises.length ? mod.exercises : (loadedExercises.value[mod.module] || [])
}

async function toggle(moduleId: string) {
  if (openModules.value.has(moduleId)) {
    openModules.value.delete(moduleId)
    return
  }
  openModules.value.add(moduleId)
  const mod = modules.value.find(m => m.module === moduleId)
  if (mod && !mod.exercises.length && !loadedExercises.value[moduleId]) {
    loadedExercises.value[moduleId] = await apiFetch<ModuleExercise[]>(
      `/api/exercises/modules/${encodeURIComponent(moduleId)}/exercises?lang=fr`,
    )
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

let jeton = 0

async function fetchCatalogue(premierChargement = false) {
  const q = searchQuery.value.trim()
  if (premierChargement) loading.value = true
  else searching.value = true
  const mien = ++jeton
  try {
    const params = new URLSearchParams({ lang: 'fr', scope: searchScope.value })
    if (filterLevel.value) params.set('level', filterLevel.value)
    if (filterDomain.value) params.set('domain', filterDomain.value)
    if (q) params.set('q', q)

    const data = await apiFetch<Catalogue>(`/api/exercises/modules?${params}`)
    // Une réponse doublée par une frappe plus récente est jetée : sans ce
    // jeton, la plus lente des deux écrase la plus fraîche.
    if (mien !== jeton) return

    modules.value = data.modules
    levels.value = data.levels
    domains.value = data.domains
    total.value = data.total
    truncated.value = data.truncated
    // Une recherche renvoie déjà les exercices qui correspondent : on déplie
    // ce qu'elle a trouvé, et rien de plus. Sans recherche, tout reste replié
    // — c'est ce qui évite de jeter des milliers de titres dans le DOM, chacun
    // passant par KaTeX.
    openModules.value = data.searched
      ? new Set(data.modules.filter(m => m.exercises.length).map(m => m.module))
      : new Set()
  } finally {
    if (mien === jeton) {
      loading.value = false
      searching.value = false
    }
  }
}

// Anti-rebond : une frappe ne déclenche pas une requête, une pause si.
let minuteur: ReturnType<typeof setTimeout> | undefined
watch(searchQuery, () => {
  clearTimeout(minuteur)
  minuteur = setTimeout(() => fetchCatalogue(), 250)
})

// Les menus, eux, filtrent tout de suite.
watch([filterLevel, filterDomain, searchScope], () => fetchCatalogue())

onMounted(() => fetchCatalogue(true))
onBeforeUnmount(() => clearTimeout(minuteur))
</script>
