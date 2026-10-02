<template>
  <div
    class="rounded-xl border overflow-hidden mb-6"
    style="background:var(--color-surface);border-color:var(--color-border)">
    <div class="px-5 py-3 border-b font-semibold text-sm" style="border-color:var(--color-border)">
      {{ $t('affectations.title') }}
    </div>

    <p v-if="!loading && !lignes.length" class="px-5 py-6 text-sm text-center" style="color:var(--color-text-muted)">
      {{ $t('affectations.empty') }}
    </p>

    <ul class="divide-y" style="border-color:var(--color-border)">
      <li v-for="l in lignes" :key="l.class_id" class="px-5 py-3 space-y-2">
        <form class="flex flex-wrap items-end gap-3" @submit.prevent="enregistrer(l)">
          <span class="text-sm font-medium min-w-[8rem] self-center">{{ nomClasse(l.class_id) }}</span>
          <label class="text-xs">
            <span class="block mb-1" style="color:var(--color-text-muted)">{{ $t('sheets.field_status') }}</span>
            <select
              v-model="l.status" class="rounded-lg border px-2 py-1 text-sm"
              style="background:var(--color-bg);border-color:var(--color-border);color:var(--color-text)">
              <option v-for="s in [0, 1, 2, 3]" :key="s" :value="s">{{ $t(`affectations.status_${s}`) }}</option>
            </select>
          </label>
          <label class="text-xs">
            <span class="block mb-1" style="color:var(--color-text-muted)">{{ $t('sheets.field_open_at') }}</span>
            <input
              v-model="l.open" type="datetime-local" class="rounded-lg border px-2 py-1 text-sm"
              style="background:var(--color-bg);border-color:var(--color-border);color:var(--color-text)">
          </label>
          <label class="text-xs">
            <span class="block mb-1" style="color:var(--color-text-muted)">{{ $t('sheets.field_close_at') }}</span>
            <input
              v-model="l.close" type="datetime-local" class="rounded-lg border px-2 py-1 text-sm"
              style="background:var(--color-bg);border-color:var(--color-border);color:var(--color-text)">
          </label>
          <button
            type="submit" :disabled="enCours === l.class_id"
            class="px-3 py-1 rounded-lg text-xs font-medium text-white disabled:opacity-50"
            style="background:var(--color-primary)">
            {{ enregistre === l.class_id ? $t('sheets.saved') : $t('sheets.save_item') }}
          </button>
          <button
            type="button" class="text-xs px-2 py-1 rounded border"
            style="border-color:var(--color-border);color:var(--color-text)"
            :aria-expanded="ouverte === l.class_id"
            @click="ouverte = ouverte === l.class_id ? null : l.class_id">
            {{ ouverte === l.class_id ? $t('affectations.notes_hide') : $t('affectations.notes_show') }}
          </button>
          <button
            type="button"
            class="text-xs px-2 py-1 rounded border hover:bg-red-50 dark:hover:bg-red-900/20 transition"
            style="border-color:var(--color-border);color:#dc2626"
            @click="retirer(l)">
            {{ $t('sheets.remove_exercise') }}
          </button>
        </form>
        <SheetsNotesFeuille v-if="ouverte === l.class_id" :sheet-id="sheetId" :class-id="l.class_id" />
      </li>
    </ul>

    <form
      v-if="disponibles.length" class="px-5 py-3 border-t flex gap-2 items-end"
      style="border-color:var(--color-border)" @submit.prevent="affecter">
      <label class="flex-1 text-xs">
        <span class="block mb-1" style="color:var(--color-text-muted)">{{ $t('affectations.add') }}</span>
        <select
          v-model="nouvelle" required class="w-full rounded-lg border px-3 py-1.5 text-sm"
          style="background:var(--color-bg);border-color:var(--color-border);color:var(--color-text)">
          <option :value="null" disabled>{{ $t('affectations.select_class') }}</option>
          <option v-for="c in disponibles" :key="c.id" :value="c.id">{{ c.name }}</option>
        </select>
      </label>
      <button
        type="submit" :disabled="nouvelle === null"
        class="px-3 py-1.5 rounded-lg text-sm font-medium text-white disabled:opacity-50"
        style="background:var(--color-primary)">
        +
      </button>
    </form>
    <p v-else-if="!loading && !classes.length" class="px-5 py-3 border-t text-xs" style="border-color:var(--color-border);color:var(--color-text-muted)">
      {{ $t('affectations.no_class') }}
    </p>

    <p v-if="error" class="px-5 pb-3 text-xs text-red-500">{{ error }}</p>
  </div>
</template>

<script setup lang="ts">
import { depuisChampLocal, messageErreur, versChampLocal } from '~/composables/useFeuilles'

/** Les classes qui reçoivent la feuille, chacune avec son statut et ses dates
 * (`/api/sheets/{id}/classes`, cf. docs/feuilles-eleve.md §3.1). */
const props = defineProps<{ sheetId: number }>()

interface Affectation { class_id: number; status: number; open_at: string | null; close_at: string | null }
// En cours d'édition : les dates au format d'un champ `datetime-local`.
interface Ligne { class_id: number; status: number; open: string; close: string }

const { apiFetch } = useApi()
const { t } = useI18n()
const classes = ref<{ id: number; name: string }[]>([])
const lignes = ref<Ligne[]>([])
const loading = ref(true)
const error = ref('')
const nouvelle = ref<number | null>(null)
const enCours = ref<number | null>(null)
const enregistre = ref<number | null>(null)
const ouverte = ref<number | null>(null)

const disponibles = computed(() => {
  const prises = new Set(lignes.value.map(l => l.class_id))
  return classes.value.filter(c => !prises.has(c.id))
})

function nomClasse(id: number): string {
  return classes.value.find(c => c.id === id)?.name ?? `#${id}`
}

function ligne(a: Affectation): Ligne {
  return { class_id: a.class_id, status: a.status, open: versChampLocal(a.open_at), close: versChampLocal(a.close_at) }
}

async function charger() {
  try {
    const [cs, affs] = await Promise.all([
      apiFetch<{ id: number; name: string }[]>('/api/classes/'),
      apiFetch<Affectation[]>(`/api/sheets/${props.sheetId}/classes`),
    ])
    classes.value = cs
    lignes.value = affs.map(ligne)
  } catch (e) {
    error.value = messageErreur(e)
  } finally {
    loading.value = false
  }
}

async function envoyer(l: Ligne): Promise<Affectation> {
  return apiFetch<Affectation>(`/api/sheets/${props.sheetId}/classes`, {
    method: 'POST',
    body: { class_id: l.class_id, status: l.status, open_at: depuisChampLocal(l.open), close_at: depuisChampLocal(l.close) },
  })
}

async function enregistrer(l: Ligne) {
  error.value = ''
  enCours.value = l.class_id
  try {
    Object.assign(l, ligne(await envoyer(l)))
    enregistre.value = l.class_id
    setTimeout(() => { if (enregistre.value === l.class_id) enregistre.value = null }, 1500)
  } catch (e) {
    error.value = messageErreur(e)
  } finally {
    enCours.value = null
  }
}

async function affecter() {
  if (nouvelle.value === null) return
  error.value = ''
  try {
    // Active d'emblée, sans dates : ouverte tout de suite, notée sans limite.
    const a = await envoyer({ class_id: nouvelle.value, status: 1, open: '', close: '' })
    lignes.value.push(ligne(a))
    nouvelle.value = null
  } catch (e) {
    error.value = messageErreur(e)
  }
}

async function retirer(l: Ligne) {
  if (!confirm(t('affectations.remove_confirm', { name: nomClasse(l.class_id) }))) return
  error.value = ''
  try {
    await apiFetch(`/api/sheets/${props.sheetId}/classes/${l.class_id}`, { method: 'DELETE' })
    lignes.value = lignes.value.filter(x => x.class_id !== l.class_id)
  } catch (e) {
    error.value = messageErreur(e)
  }
}

onMounted(charger)
</script>
