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
      <div class="px-5 py-3 border-b flex items-center justify-between"
           style="border-color:var(--color-border)">
        <span class="font-semibold text-sm">{{ $t('sheets.exercises_section') }}</span>
      </div>

      <div v-if="sheet.items.length === 0"
           class="px-5 py-8 text-sm text-center"
           style="color:var(--color-text-muted)">
        {{ $t('sheets.no_exercises') }}
      </div>

      <ul v-else class="divide-y" style="border-color:var(--color-border)">
        <li v-for="item in sheet.items" :key="item.id"
            class="px-5 py-3 flex items-center justify-between gap-4">
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
          <button type="button" @click="removeExercise(item.id)"
                  class="flex-shrink-0 text-xs px-2 py-1 rounded border hover:bg-red-50 dark:hover:bg-red-900/20 transition"
                  style="border-color:var(--color-border);color:#dc2626">
            {{ $t('sheets.remove_exercise') }}
          </button>
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
interface SheetItem { id: number; position: number; points: number; prerequisite: string | null; exercise: Exercise }
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

const editForm = reactive({ title: '', description: '', level: '', domain: '', status: 1 })
const addForm = reactive({ exercise_id: '', points: 10 })

async function load() {
  loading.value = true
  try {
    const s = await apiFetch<Sheet>(`/api/sheets/${id}`)
    sheet.value = s
    Object.assign(editForm, { title: s.title, description: s.description ?? '', level: s.level ?? '', domain: s.domain ?? '', status: s.status })
  } catch {
    sheet.value = null
  } finally {
    loading.value = false
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
