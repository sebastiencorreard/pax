<template>
  <div class="px-6 py-6">
    <h1 class="text-2xl font-bold mb-6">{{ $t('feuilles.title') }}</h1>

    <div v-if="loading" class="space-y-3">
      <div
v-for="i in 3" :key="i" class="h-20 rounded-xl animate-pulse"
           style="background:var(--color-surface)"/>
    </div>

    <div
v-else-if="feuilles.length === 0"
         class="text-center py-16 rounded-xl border"
         style="background:var(--color-surface);border-color:var(--color-border);color:var(--color-text-muted)">
      <p class="text-4xl mb-4">📋</p>
      <p class="text-sm">{{ $t('feuilles.empty') }}</p>
    </div>

    <div v-else class="space-y-3">
      <NuxtLink
v-for="f in feuilles" :key="f.sheet_id" :to="`/feuilles/${f.sheet_id}`"
                class="block rounded-xl border px-5 py-4 hover:shadow-sm transition"
                style="background:var(--color-surface);border-color:var(--color-border)">
        <div class="flex items-start justify-between gap-4">
          <div class="min-w-0">
            <p class="font-semibold truncate">{{ f.title }}</p>
            <p
v-if="f.description" class="text-sm truncate mt-0.5"
               style="color:var(--color-text-muted)">{{ f.description }}</p>
          </div>
          <span class="flex-shrink-0 text-lg font-semibold tabular-nums">
            {{ $t('feuilles.note_sur', { note: nombre(f.note) }) }}
          </span>
        </div>
        <div class="flex flex-wrap gap-x-3 gap-y-1 mt-2 text-xs" style="color:var(--color-text-muted)">
          <span>{{ f.class_name }}</span>
          <span>{{ $t('feuilles.nb_exercices', { n: f.exercices }, f.exercices) }}</span>
          <span>{{ $t('feuilles.cumul', { pct: nombre(f.cumul, 0) }) }}</span>
          <span v-if="f.close_at && f.note_enregistrable">{{ $t('feuilles.close_at', { date: date(f.close_at) }) }}</span>
          <span
v-if="!f.note_enregistrable" class="px-1.5 rounded"
                style="background:#fef3c7;color:#92400e">{{ $t('feuilles.sans_note') }}</span>
        </div>
      </NuxtLink>
    </div>

    <p v-if="error" class="mt-4 text-sm text-red-500">{{ error }}</p>
  </div>
</template>

<script setup lang="ts">
import { messageErreur, type FeuilleResume } from '~/composables/useFeuilles'

definePageMeta({ layout: 'dashboard', middleware: ['student'] })

const { apiFetch } = useApi()
const { nombre, date } = useFeuilles()

const feuilles = ref<FeuilleResume[]>([])
const loading = ref(true)
const error = ref('')

onMounted(async () => {
  try {
    feuilles.value = await apiFetch<FeuilleResume[]>('/api/feuilles/mes')
  } catch (e) {
    error.value = messageErreur(e)
  } finally {
    loading.value = false
  }
})
</script>
