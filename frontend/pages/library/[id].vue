<template>
  <div>
    <div class="mb-6">
      <NuxtLink to="/library"
                class="text-sm hover:underline"
                style="color:var(--color-text-muted)">
        ← {{ $t('nav.library') }}
      </NuxtLink>
    </div>

    <!-- Skeleton -->
    <div v-if="loading">
      <div class="h-8 w-48 rounded animate-pulse mb-6"
           style="background:var(--color-surface)"></div>
      <div class="space-y-2">
        <div v-for="i in 5" :key="i"
             class="h-12 rounded-xl animate-pulse"
             style="background:var(--color-surface)"></div>
      </div>
    </div>

    <template v-else-if="group">
      <!-- En-tête -->
      <div class="flex items-center gap-3 mb-6">
        <h1 class="text-2xl font-bold">{{ group.tag.name }}</h1>
        <span class="text-sm px-2.5 py-1 rounded-full"
              style="background:var(--color-primary);color:#fff">
          {{ group.exercises.length }}
        </span>
      </div>

      <!-- Liste vide -->
      <p v-if="group.exercises.length === 0"
         class="text-sm"
         style="color:var(--color-text-muted)">
        {{ $t('tags.empty_tag') }}
      </p>

      <!-- Exercices -->
      <div v-else class="rounded-xl border overflow-hidden"
           style="background:var(--color-surface);border-color:var(--color-border)">
        <div v-for="ex in group.exercises" :key="ex.id"
             class="flex items-center justify-between px-5 py-3 border-b last:border-b-0 group"
             style="border-color:var(--color-border)">
          <NuxtLink :to="`/exercise/${ex.id}`"
                    class="flex-1 min-w-0 text-sm hover:underline truncate"
                    style="color:var(--color-text)">
            {{ ex.title }}
            <span v-if="ex.domain"
                  class="ml-2 text-xs"
                  style="color:var(--color-text-muted)">
              {{ ex.domain }}
            </span>
          </NuxtLink>
          <button type="button"
                  @click="untag(ex)"
                  :disabled="removingId === ex.id"
                  class="ml-4 flex-shrink-0 text-xs px-2 py-0.5 rounded border opacity-0 group-hover:opacity-100 transition disabled:opacity-30"
                  style="border-color:var(--color-border);color:var(--color-text-muted)"
                  :title="$t('tags.remove_from_tag')">
            {{ removingId === ex.id ? '…' : '×' }}
          </button>
        </div>
      </div>
    </template>

    <p v-if="error" class="mt-4 text-sm text-red-500">{{ error }}</p>
  </div>
</template>

<script setup lang="ts">
import type { LibraryGroup, LibraryExercise } from '~/composables/useTags'

definePageMeta({ middleware: ['teacher'] })

const route = useRoute()
const tagId = computed(() => Number(route.params.id))

const { fetchTagExercises, removeTagFromExercise } = useTags()

const group = ref<LibraryGroup | null>(null)
const loading = ref(true)
const error = ref('')
const removingId = ref<string | null>(null)

async function load() {
  loading.value = true
  error.value = ''
  try {
    group.value = await fetchTagExercises(tagId.value)
  } catch (e: any) {
    error.value = e?.data?.detail || e?.message || String(e)
  } finally {
    loading.value = false
  }
}

async function untag(ex: LibraryExercise) {
  if (!group.value) return
  removingId.value = ex.id
  try {
    await removeTagFromExercise(ex.id, group.value.tag.id)
    group.value.exercises = group.value.exercises.filter(e => e.id !== ex.id)
  } catch (e: any) {
    error.value = e?.data?.detail || e?.message || String(e)
  } finally {
    removingId.value = null
  }
}

onMounted(load)
</script>
