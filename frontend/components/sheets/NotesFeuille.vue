<template>
  <div class="overflow-x-auto">
    <p v-if="error" class="text-xs text-red-500">{{ error }}</p>
    <p v-else-if="!notes" class="text-xs" style="color:var(--color-text-muted)">…</p>
    <p v-else-if="!notes.eleves.length" class="text-xs" style="color:var(--color-text-muted)">
      {{ $t('classes.no_students') }}
    </p>
    <table v-else class="text-xs w-full">
      <thead>
        <tr style="color:var(--color-text-muted)">
          <th class="text-left font-medium py-1 pr-3">{{ $t('notes.eleve') }}</th>
          <th
            v-for="e in exercices" :key="e.id" class="font-medium px-2 text-center"
            :title="e.title ?? e.exercise_id">
            {{ e.numero }}
          </th>
          <th class="font-medium px-2 text-right">{{ $t('notes.cumul') }}</th>
          <th class="font-medium px-2 text-right">{{ $t('notes.qualite') }}</th>
          <th class="font-medium pl-2 text-right">{{ $t('notes.note') }}</th>
        </tr>
      </thead>
      <tbody>
        <tr v-for="l in notes.eleves" :key="l.id" class="border-t" style="border-color:var(--color-border)">
          <td class="py-1 pr-3 whitespace-nowrap">{{ l.last_name }} {{ l.first_name }}</td>
          <td
            v-for="e in exercices" :key="e.id" class="px-2 text-center tabular-nums"
            :title="$t('feuilles.essais', { n: l.exercices[e.id]?.essais ?? 0 })">
            <template v-if="l.exercices[e.id]?.essais">{{ nombre(l.exercices[e.id]!.points, 1) }}/{{ e.requis }}</template>
            <span v-else style="color:var(--color-text-muted)">—</span>
          </td>
          <td class="px-2 text-right tabular-nums">{{ nombre(l.cumul, 0) }} %</td>
          <td class="px-2 text-right tabular-nums">{{ nombre(l.qualite, 1) }}</td>
          <td class="pl-2 text-right font-semibold tabular-nums">{{ nombre(l.note) }}</td>
        </tr>
      </tbody>
    </table>
  </div>
</template>

<script setup lang="ts">
import { messageErreur } from '~/composables/useFeuilles'

/** Le travail d'une classe sur une feuille : élève × exercice
 * (`GET /api/sheets/{id}/classes/{class_id}/notes`). */
const props = defineProps<{ sheetId: number; classId: number }>()

interface NotesFeuille {
  exercices: { id: number; numero: number; exercise_id: string; title: string | null; requis: number; actif: boolean }[]
  eleves: {
    id: string; first_name: string | null; last_name: string | null
    note: number; cumul: number; qualite: number
    exercices: Record<number, { points: number; qualite: number; essais: number; tirages: number }>
  }[]
}

const { apiFetch } = useApi()
const { nombre } = useFeuilles()
const notes = ref<NotesFeuille | null>(null)
const error = ref('')
// Un exercice désactivé ne compte pas : il n'a pas sa colonne.
const exercices = computed(() => notes.value?.exercices.filter(e => e.actif) ?? [])

onMounted(async () => {
  try {
    notes.value = await apiFetch<NotesFeuille>(`/api/sheets/${props.sheetId}/classes/${props.classId}/notes`)
  } catch (e) {
    error.value = messageErreur(e)
  }
})
</script>
