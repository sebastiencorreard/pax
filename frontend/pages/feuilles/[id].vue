<template>
  <div class="px-6 py-6">
    <NuxtLink
to="/feuilles" class="inline-block mb-4 text-sm hover:underline"
              style="color:var(--color-primary)">
      ← {{ $t('feuilles.title') }}
    </NuxtLink>

    <div v-if="loading" class="h-40 rounded-xl animate-pulse" style="background:var(--color-surface)"/>

    <p v-else-if="error" class="text-sm text-red-500">{{ error }}</p>

    <template v-else-if="feuille">
      <div class="flex items-start justify-between gap-4 mb-2">
        <div class="min-w-0">
          <h1 class="text-2xl font-bold">{{ feuille.title }}</h1>
          <p v-if="feuille.description" class="text-sm mt-1" style="color:var(--color-text-muted)">
            {{ feuille.description }}
          </p>
        </div>
        <div class="flex-shrink-0 text-right">
          <p class="text-2xl font-semibold tabular-nums">
            {{ $t('feuilles.note_sur', { note: nombre(feuille.note) }) }}
          </p>
          <p class="text-xs" style="color:var(--color-text-muted)">
            {{ $t('feuilles.cumul', { pct: nombre(feuille.cumul, 0) }) }}
            · {{ $t('feuilles.qualite', { q: nombre(feuille.qualite, 1) }) }}
          </p>
        </div>
      </div>

      <p class="text-xs mb-4" style="color:var(--color-text-muted)">
        {{ feuille.class_name }}
        <template v-if="feuille.close_at && feuille.note_enregistrable">
          · {{ $t('feuilles.close_at', { date: date(feuille.close_at) }) }}
        </template>
      </p>

      <div
v-if="!feuille.note_enregistrable"
           class="mb-4 px-4 py-3 rounded-lg text-sm"
           style="background:#fef3c7;color:#92400e">
        {{ $t('feuilles.sans_note_detail') }}
      </div>

      <div class="space-y-2">
        <div
v-for="ex in feuille.exercices" :key="ex.id"
             class="rounded-xl border px-5 py-3 flex items-center gap-4"
             :class="{ 'opacity-60': ex.verrouille }"
             style="background:var(--color-surface);border-color:var(--color-border)">
          <span class="w-6 text-sm tabular-nums" style="color:var(--color-text-muted)">{{ ex.numero }}</span>
          <div class="flex-1 min-w-0">
            <p class="font-medium truncate">{{ ex.title || ex.exercise_id }}</p>
            <p class="text-xs mt-0.5" style="color:var(--color-text-muted)">
              <template v-if="ex.verrouille && prerequis(ex.prerequis)">
                🔒 {{ $t('feuilles.verrouille', prerequis(ex.prerequis)!) }}
              </template>
              <template v-else>
                {{ $t('feuilles.points', { points: nombre(ex.points, 1), requis: ex.requis }) }}
                <template v-if="ex.essais">
                  · {{ $t('feuilles.qualite', { q: nombre(ex.qualite, 1) }) }}
                  · {{ $t('feuilles.essais', { n: ex.essais }, ex.essais) }}
                </template>
              </template>
            </p>
          </div>
          <!-- Barre de progression : les points acquis sur les points requis. -->
          <div class="hidden sm:block w-24 h-1.5 rounded-full overflow-hidden" style="background:var(--color-bg)">
            <div
class="h-full rounded-full"
                 :style="{ width: `${Math.min(100, ex.requis ? 100 * ex.points / ex.requis : 0)}%`,
                           background: 'var(--color-success)' }"/>
          </div>
          <NuxtLink
v-if="!ex.verrouille"
                    :to="{ path: `/exercise/${ex.exercise_id}`, query: { sheet_item: ex.id, feuille: feuille.sheet_id } }"
                    class="flex-shrink-0 px-4 py-1.5 rounded-lg text-sm font-medium text-white"
                    style="background:var(--color-primary)">
            {{ ex.tirages ? $t('feuilles.continuer') : $t('feuilles.commencer') }}
          </NuxtLink>
        </div>
      </div>
    </template>
  </div>
</template>

<script setup lang="ts">
import { messageErreur, type FeuilleDetail } from '~/composables/useFeuilles'

definePageMeta({ layout: 'dashboard', middleware: ['student'] })

const route = useRoute()
const { apiFetch } = useApi()
const { t } = useI18n()
const { nombre, date, prerequis } = useFeuilles()

const feuille = ref<FeuilleDetail | null>(null)
const loading = ref(true)
const error = ref('')

onMounted(async () => {
  try {
    feuille.value = await apiFetch<FeuilleDetail>(`/api/feuilles/${route.params.id}`)
  } catch (e) {
    error.value = (e as { status?: number })?.status === 404 ? t('feuilles.not_found') : messageErreur(e)
  } finally {
    loading.value = false
  }
})
</script>
