<template>
  <div
    class="rounded-xl border overflow-hidden mb-4"
    style="background:var(--color-surface);border-color:var(--color-border)">
    <div class="px-5 py-3 border-b flex items-center justify-between gap-3" style="border-color:var(--color-border)">
      <span class="font-semibold text-sm">{{ $t('notes.title') }}</span>
      <button
        v-if="notes?.feuilles.length && notes.eleves.length" type="button"
        class="text-xs px-2 py-1 rounded border disabled:opacity-50"
        style="border-color:var(--color-border);color:var(--color-text)"
        :disabled="exportEnCours" @click="exporter">
        {{ $t('notes.export_csv') }}
      </button>
    </div>
    <p v-if="exportErreur" class="px-5 pt-3 text-xs text-red-500">{{ exportErreur }}</p>
    <p v-if="error" class="px-5 py-3 text-xs text-red-500">{{ error }}</p>
    <p v-else-if="!notes" class="px-5 py-3 text-xs" style="color:var(--color-text-muted)">…</p>
    <p
      v-else-if="!notes.feuilles.length || !notes.eleves.length"
      class="px-5 py-6 text-sm text-center" style="color:var(--color-text-muted)">
      {{ notes.feuilles.length ? $t('classes.no_students') : $t('notes.no_sheet') }}
    </p>
    <div v-else class="px-5 py-3 overflow-x-auto">
      <table class="text-sm w-full">
        <thead>
          <tr class="text-xs" style="color:var(--color-text-muted)">
            <th class="text-left font-medium py-1 pr-3">{{ $t('notes.eleve') }}</th>
            <th v-for="f in notes.feuilles" :key="f.sheet_id" class="font-medium px-2 text-right">
              <NuxtLink :to="`/sheets/${f.sheet_id}`" class="hover:underline" :title="poids(f)">{{ f.title }}</NuxtLink>
              <span v-if="f.status === 2" class="block font-normal">{{ $t('affectations.status_2') }}</span>
            </th>
            <th class="font-medium pl-2 text-right">{{ $t('notes.moyenne') }}</th>
          </tr>
        </thead>
        <tbody>
          <tr v-for="l in notes.eleves" :key="l.id" class="border-t" style="border-color:var(--color-border)">
            <td class="py-1 pr-3 whitespace-nowrap">{{ l.last_name }} {{ l.first_name }}</td>
            <td
              v-for="f in notes.feuilles" :key="f.sheet_id" class="px-2 text-right tabular-nums"
              :title="detail(l.notes[f.sheet_id])">
              {{ nombre(l.notes[f.sheet_id]?.note ?? 0) }}
            </td>
            <td class="pl-2 text-right font-semibold tabular-nums">{{ nombre(l.moyenne) }}</td>
          </tr>
        </tbody>
      </table>
      <p class="mt-2 text-xs" style="color:var(--color-text-muted)">{{ $t('notes.explication') }}</p>
    </div>
  </div>
</template>

<script setup lang="ts">
import { messageErreur } from '~/composables/useFeuilles'

/** Le tableau des notes d'une classe : élève × feuille, et la moyenne
 * pondérée (`GET /api/classes/{id}/notes`). */
const props = defineProps<{ classId: number }>()

interface Note { note: number; cumul: number; qualite: number }
interface Feuille { sheet_id: number; title: string; status: number; note_poids: number }
interface Notes {
  feuilles: Feuille[]
  eleves: { id: string; first_name: string | null; last_name: string | null; notes: Record<number, Note>; moyenne: number }[]
}

const { apiFetch } = useApi()
const { t, locale } = useI18n()
const { nombre } = useFeuilles()
const notes = ref<Notes | null>(null)
const error = ref('')

function poids(f: Feuille): string {
  return t('notes.poids', { w: nombre(f.note_poids) })
}

function detail(n: Note | undefined): string {
  return n ? `${t('notes.cumul')} ${nombre(n.cumul, 0)} % · ${t('notes.qualite')} ${nombre(n.qualite, 1)}` : ''
}

// Le serveur écrit le fichier dans la langue de l'interface : un tableur
// français attend `;` et la virgule décimale.
const exportEnCours = ref(false)
const exportErreur = ref('')
async function exporter() {
  exportEnCours.value = true
  exportErreur.value = ''
  try {
    const blob = await apiFetch<Blob>(
      `/api/classes/${props.classId}/notes.csv?lang=${String(locale.value)}`, { responseType: 'blob' })
    const lien = document.createElement('a')
    lien.href = URL.createObjectURL(blob)
    lien.download = `notes-${props.classId}.csv`
    lien.click()
    URL.revokeObjectURL(lien.href)
  } catch (e) {
    exportErreur.value = messageErreur(e)
  } finally {
    exportEnCours.value = false
  }
}

onMounted(async () => {
  try {
    notes.value = await apiFetch<Notes>(`/api/classes/${props.classId}/notes`)
  } catch (e) {
    error.value = messageErreur(e)
  }
})
</script>
