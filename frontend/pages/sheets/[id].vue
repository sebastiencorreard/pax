<template>
  <div class="px-6 py-6">
  <div v-if="loading" class="space-y-3">
    <div v-for="i in 4" :key="i" class="h-12 rounded-xl animate-pulse"
         style="background:var(--color-surface)"></div>
  </div>

  <div v-else-if="!sheet" class="text-center py-16"
       style="color:var(--color-text-muted)">
    {{ $t('sheets.not_found') }}
  </div>

  <div v-else>
    <!-- Métadonnées -->
    <form @submit.prevent="saveSheet" class="rounded-xl border p-5 mb-6 space-y-4"
          style="background:var(--color-surface);border-color:var(--color-border)">
      <h1 class="text-xl font-bold mb-2">{{ sheet.title }}</h1>

      <div class="grid grid-cols-1 sm:grid-cols-2 gap-3">
        <div>
          <label class="block text-xs font-medium mb-1">{{ $t('sheets.field_title') }}</label>
          <input v-model="editForm.title" type="text" required
                 class="w-full rounded-lg border px-3 py-1.5 text-sm"
                 style="background:var(--color-bg);border-color:var(--color-border);color:var(--color-text)" />
        </div>
        <div>
          <label class="block text-xs font-medium mb-1">{{ $t('sheets.field_status') }}</label>
          <select v-model="editForm.status"
                  class="w-full rounded-lg border px-3 py-1.5 text-sm"
                  style="background:var(--color-bg);border-color:var(--color-border);color:var(--color-text)">
            <option :value="1">{{ $t('sheets.status_1') }}</option>
            <option :value="0">{{ $t('sheets.status_0') }}</option>
            <option :value="3">{{ $t('sheets.status_3') }}</option>
          </select>
        </div>
        <div>
          <label class="block text-xs font-medium mb-1">{{ $t('sheets.field_level') }}</label>
          <input v-model="editForm.level" type="text"
                 class="w-full rounded-lg border px-3 py-1.5 text-sm"
                 style="background:var(--color-bg);border-color:var(--color-border);color:var(--color-text)" />
        </div>
        <div>
          <label class="block text-xs font-medium mb-1">{{ $t('sheets.field_domain') }}</label>
          <input v-model="editForm.domain" type="text"
                 class="w-full rounded-lg border px-3 py-1.5 text-sm"
                 style="background:var(--color-bg);border-color:var(--color-border);color:var(--color-text)" />
        </div>
        <div class="sm:col-span-2">
          <label class="block text-xs font-medium mb-1">{{ $t('sheets.field_description') }}</label>
          <textarea v-model="editForm.description" rows="2"
                    class="w-full rounded-lg border px-3 py-1.5 text-sm"
                    style="background:var(--color-bg);border-color:var(--color-border);color:var(--color-text)"></textarea>
        </div>
      </div>

      <div class="flex items-center gap-3">
        <button type="submit" :disabled="saving"
                class="px-4 py-1.5 rounded-lg text-sm font-medium text-white disabled:opacity-50"
                style="background:var(--color-primary)">
          {{ saving ? '…' : $t('sheets.save') }}
        </button>
        <button type="button" @click="deleteSheet"
                class="px-4 py-1.5 rounded-lg text-sm border hover:bg-red-50 dark:hover:bg-red-900/20 transition"
                style="border-color:var(--color-border);color:#dc2626">
          {{ $t('sheets.delete') }}
        </button>
      </div>
    </form>

    <!-- Exercices -->
    <div class="rounded-xl border overflow-hidden"
         style="background:var(--color-surface);border-color:var(--color-border)">
      <div
        class="px-5 py-3 border-b flex items-center justify-between gap-3"
        style="border-color:var(--color-border)">
        <span class="font-semibold text-sm">{{ $t('sheets.exercises_section') }}</span>
        <button
          v-if="severity" type="button" class="text-xs underline"
          style="color:var(--color-text-muted)" @click="showSeverity = !showSeverity">
          {{ showSeverity ? $t('sheets.severity_table_hide') : $t('sheets.severity_table_show') }}
        </button>
      </div>
      <!-- Sans ce tableau, un niveau de 1 à 9 ne dit rien de ce qu'il commande. -->
      <div
        v-if="showSeverity && severity" class="px-5 py-3 border-b"
        style="border-color:var(--color-border)">
        <SheetsSeverityTable :table="severity" :highlight="focusLevel" />
      </div>

      <div v-if="sheet.items.length === 0"
           class="px-5 py-8 text-sm text-center"
           style="color:var(--color-text-muted)">
        {{ $t('sheets.no_exercises') }}
      </div>

      <ul v-else class="divide-y" style="border-color:var(--color-border)">
        <li v-for="item in sheet.items" :key="item.id" class="px-5 py-3 space-y-2">
          <div class="flex items-center justify-between gap-4">
          <div class="min-w-0">
            <NuxtLink :to="`/exercise/${item.exercise.id}`"
                      class="text-sm font-medium truncate hover:underline block"
                      style="color:var(--color-text)">
              {{ item.exercise.title }}
            </NuxtLink>
            <span class="text-xs" style="color:var(--color-text-muted)">
              {{ item.points }} {{ $t('sheets.points') }}
              · pos {{ item.position }}
              <template v-if="item.prerequisite"> · prérequis {{ item.prerequisite }}</template>
            </span>
          </div>
          <div class="flex items-center gap-2 flex-shrink-0">
            <NuxtLink
              :to="`/exercise/${item.exercise.id}?sheet_item=${item.id}`"
              class="text-xs px-2 py-1 rounded border transition"
              style="border-color:var(--color-border);color:var(--color-text)">
              {{ $t('sheets.preview') }}
            </NuxtLink>
            <button
              type="button"
              class="text-xs px-2 py-1 rounded border hover:bg-red-50 dark:hover:bg-red-900/20 transition"
              style="border-color:var(--color-border);color:#dc2626"
              @click="removeExercise(item.id)">
              {{ $t('sheets.remove_exercise') }}
            </button>
          </div>
          </div>

          <!-- Ce que WIMS règle en posant l'exercice sur une feuille : le niveau
               de sévérité, et les paramètres que le module expose. -->
          <form
            v-if="drafts[item.id]" class="flex flex-wrap items-end gap-3"
            @submit.prevent="saveItem(item)">
            <label class="text-xs">
              <span class="block mb-1" style="color:var(--color-text-muted)">{{ $t('sheets.severity') }}</span>
              <select
                v-model="drafts[item.id]!.qcmlevel"
                class="rounded-lg border px-2 py-1 text-sm"
                style="background:var(--color-bg);border-color:var(--color-border);color:var(--color-text)"
                @focus="focusLevel = drafts[item.id]!.qcmlevel"
                @change="focusLevel = drafts[item.id]!.qcmlevel">
                <option :value="null">{{ $t('sheets.severity_default', { level: severity?.defaut ?? 3 }) }}</option>
                <option v-for="n in 9" :key="n" :value="n">{{ n }}</option>
              </select>
            </label>
            <label v-for="p in confparms[item.exercise.id] ?? []" :key="p.nom" class="text-xs max-w-xs">
              <span
                class="block mb-1 truncate" style="color:var(--color-text-muted)"
                :title="p.libelle || p.nom">
                {{ p.libelle || p.nom }}
              </span>
              <select
                v-if="p.choix.length" v-model="drafts[item.id]!.confparm[p.nom]"
                class="w-full rounded-lg border px-2 py-1 text-sm"
                style="background:var(--color-bg);border-color:var(--color-border);color:var(--color-text)">
                <option value="">{{ moduleDefault(p) }}</option>
                <option v-for="c in p.choix" :key="c.valeur" :value="c.valeur">{{ c.libelle }}</option>
              </select>
              <input
                v-else v-model="drafts[item.id]!.confparm[p.nom]" type="text" :placeholder="p.defaut"
                class="w-full rounded-lg border px-2 py-1 text-sm"
                style="background:var(--color-bg);border-color:var(--color-border);color:var(--color-text)">
            </label>
            <button
              type="submit" :disabled="savingItem === item.id"
              class="px-3 py-1 rounded-lg text-xs font-medium text-white disabled:opacity-50"
              style="background:var(--color-primary)">
              {{ savedItem === item.id ? $t('sheets.saved') : $t('sheets.save_item') }}
            </button>
          </form>
        </li>
      </ul>

      <!-- Ajouter un exercice -->
      <div class="px-5 py-3 border-t" style="border-color:var(--color-border)">
        <form @submit.prevent="addExercise" class="flex gap-2 items-end">
          <div class="flex-1">
            <label class="block text-xs mb-1" style="color:var(--color-text-muted)">
              {{ $t('sheets.add_exercise') }} (ID)
            </label>
            <input v-model="addForm.exercise_id" type="text" required
                   class="w-full rounded-lg border px-3 py-1.5 text-sm font-mono"
                   style="background:var(--color-bg);border-color:var(--color-border);color:var(--color-text)" />
          </div>
          <div class="w-20">
            <label class="block text-xs mb-1" style="color:var(--color-text-muted)">
              {{ $t('sheets.points') }}
            </label>
            <input v-model.number="addForm.points" type="number" min="1"
                   class="w-full rounded-lg border px-3 py-1.5 text-sm"
                   style="background:var(--color-bg);border-color:var(--color-border);color:var(--color-text)" />
          </div>
          <button type="submit" :disabled="adding"
                  class="px-3 py-1.5 rounded-lg text-sm font-medium text-white disabled:opacity-50"
                  style="background:var(--color-primary)">
            +
          </button>
        </form>
        <p v-if="addError" class="text-xs text-red-500 mt-1">{{ addError }}</p>
      </div>
    </div>

    <p v-if="saveError" class="mt-3 text-sm text-red-500">{{ saveError }}</p>
  </div>
  </div>
</template>

<script setup lang="ts">
definePageMeta({ layout: 'dashboard', middleware: ['teacher'] })

const { apiFetch } = useApi()
const { t } = useI18n()
const route = useRoute()
const id = Number(route.params.id)

interface Exercise { id: string; title: string }
interface SheetItem {
  id: number; position: number; points: number; prerequisite: string | null; exercise: Exercise
  qcmlevel: number | null; confparm: Record<string, string> | null
}
// Un paramètre que le module laisse régler (`GET /api/exercises/{id}/confparm`) ;
// `choix` vide = saisie libre.
interface Confparm {
  nom: string; libelle: string; defaut: string
  choix: { valeur: string; libelle: string }[]
}
interface Severity { defaut: number; reglages: Record<string, number[]> }
// Réglages en cours d'édition ; `''` = la valeur du module.
interface Draft { qcmlevel: number | null; confparm: Record<string, string> }
interface Sheet {
  id: number; title: string; description: string | null; author: string | null
  level: string | null; domain: string | null; status: number; items: SheetItem[]
}

const sheet = ref<Sheet | null>(null)
const loading = ref(true)
const saving = ref(false)
const saveError = ref('')
const adding = ref(false)
const addError = ref('')

const severity = ref<Severity | null>(null)
const showSeverity = ref(false)
const focusLevel = ref<number | null>(null)
const confparms = reactive<Record<string, Confparm[]>>({})
const drafts = reactive<Record<number, Draft>>({})
const savingItem = ref<number | null>(null)
const savedItem = ref<number | null>(null)

const editForm = reactive({ title: '', description: '', level: '', domain: '', status: 1 })
const addForm = reactive({ exercise_id: '', points: 10 })

async function load() {
  loading.value = true
  try {
    const s = await apiFetch<Sheet>(`/api/sheets/${id}`)
    sheet.value = s
    Object.assign(editForm, { title: s.title, description: s.description ?? '', level: s.level ?? '', domain: s.domain ?? '', status: s.status })
    await loadSettings(s)
  } catch {
    sheet.value = null
  } finally {
    loading.value = false
  }
}

// Le tableau des niveaux (une fois), les paramètres de chaque module (une fois
// par exercice), puis un brouillon par exercice posé.
async function loadSettings(s: Sheet) {
  if (!severity.value) {
    severity.value = await apiFetch<Severity>('/api/sheets/severite').catch(() => null)
  }
  const manquants = [...new Set(s.items.map(i => i.exercise.id))].filter(eid => !(eid in confparms))
  await Promise.all(manquants.map(async (eid) => {
    confparms[eid] = await apiFetch<Confparm[]>(`/api/exercises/${eid}/confparm`).catch(() => [])
  }))
  for (const item of s.items) {
    const confparm: Record<string, string> = {}
    for (const p of confparms[item.exercise.id] ?? []) confparm[p.nom] = item.confparm?.[p.nom] ?? ''
    drafts[item.id] = { qcmlevel: item.qcmlevel, confparm }
  }
}

function moduleDefault(p: Confparm): string {
  const valeur = p.choix.find(c => c.valeur === p.defaut)?.libelle ?? p.defaut
  return valeur ? `${t('sheets.module_default')} (${valeur})` : t('sheets.module_default')
}

async function saveItem(item: SheetItem) {
  const draft = drafts[item.id]
  if (!draft) return
  savingItem.value = item.id
  saveError.value = ''
  const confparm = Object.fromEntries(Object.entries(draft.confparm).filter(([, v]) => v !== ''))
  try {
    const updated = await apiFetch<SheetItem>(`/api/sheets/${id}/exercises/${item.id}`, {
      method: 'PATCH',
      body: { qcmlevel: draft.qcmlevel, confparm: Object.keys(confparm).length ? confparm : null },
    })
    item.qcmlevel = updated.qcmlevel
    item.confparm = updated.confparm
    savedItem.value = item.id
    setTimeout(() => { if (savedItem.value === item.id) savedItem.value = null }, 1500)
  } catch (e) {
    saveError.value = (e as { data?: { detail?: string } })?.data?.detail || String(e)
  } finally {
    savingItem.value = null
  }
}

async function saveSheet() {
  saving.value = true
  saveError.value = ''
  try {
    const updated = await apiFetch<Sheet>(`/api/sheets/${id}`, {
      method: 'PATCH',
      body: {
        title: editForm.title,
        description: editForm.description || null,
        level: editForm.level || null,
        domain: editForm.domain || null,
        status: editForm.status,
      },
    })
    if (sheet.value) sheet.value.title = updated.title
  } catch (e: any) {
    saveError.value = e?.data?.detail || String(e)
  } finally {
    saving.value = false
  }
}

async function deleteSheet() {
  if (!sheet.value) return
  if (!confirm(t('sheets.delete_confirm', { title: sheet.value.title }))) return
  try {
    await apiFetch(`/api/sheets/${id}`, { method: 'DELETE' })
    await navigateTo('/sheets')
  } catch (e: any) {
    saveError.value = e?.data?.detail || String(e)
  }
}

async function addExercise() {
  adding.value = true
  addError.value = ''
  try {
    await apiFetch(`/api/sheets/${id}/exercises`, {
      method: 'POST',
      body: { exercise_id: addForm.exercise_id, points: addForm.points, position: sheet.value?.items.length ?? 0 },
    })
    addForm.exercise_id = ''
    await load()
  } catch (e: any) {
    addError.value = e?.data?.detail || String(e)
  } finally {
    adding.value = false
  }
}

async function removeExercise(itemId: number) {
  try {
    await apiFetch(`/api/sheets/${id}/exercises/${itemId}`, { method: 'DELETE' })
    if (sheet.value) sheet.value.items = sheet.value.items.filter(i => i.id !== itemId)
  } catch (e: any) {
    saveError.value = e?.data?.detail || String(e)
  }
}

onMounted(load)
</script>
