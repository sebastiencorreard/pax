<template>
  <div>
    <h1 class="text-2xl font-bold mb-6">{{ $t('nav.library') }}</h1>

    <!-- Skeleton -->
    <div v-if="loading" class="space-y-4">
      <div v-for="i in 3" :key="i"
           class="h-32 rounded-xl animate-pulse"
           style="background:var(--color-surface)"></div>
    </div>

    <!-- État vide -->
    <div v-else-if="library.length === 0"
         class="text-center py-16 rounded-xl border"
         style="background:var(--color-surface);border-color:var(--color-border);color:var(--color-text-muted)">
      <p class="text-4xl mb-4">🏷️</p>
      <p class="text-sm">{{ $t('tags.no_tags') }}</p>
      <NuxtLink to="/exercise"
                class="inline-block mt-4 text-sm underline"
                style="color:var(--color-primary)">
        {{ $t('tags.browse_exercises') }}
      </NuxtLink>
    </div>

    <!-- Grille de cartes -->
    <div v-else class="grid grid-cols-1 sm:grid-cols-2 lg:grid-cols-3 gap-4">
      <div v-for="group in library" :key="group.tag.id"
           class="rounded-xl border overflow-hidden flex flex-col"
           style="background:var(--color-surface);border-color:var(--color-border)">

        <!-- En-tête de la carte (cliquable → vue Sélection) -->
        <NuxtLink :to="`/library/${group.tag.id}`"
                  class="px-4 py-3 flex items-center justify-between border-b hover:bg-black/5 dark:hover:bg-white/5 transition"
                  style="border-color:var(--color-border)">
          <div class="flex items-center gap-2 min-w-0">
            <span class="font-semibold truncate">{{ group.tag.name }}</span>
            <span class="text-xs px-2 py-0.5 rounded flex-shrink-0"
                  style="background:var(--color-bg);color:var(--color-text-muted)">
              {{ group.exercises.length }}
            </span>
          </div>
          <div class="flex items-center gap-2 flex-shrink-0 ml-2">
            <button type="button"
                    @click.prevent="confirmDelete(group.tag)"
                    class="text-xs px-2 py-1 rounded border transition hover:opacity-70"
                    style="border-color:var(--color-border);color:var(--color-text-muted)"
                    :title="$t('tags.delete_tag')">
              🗑
            </button>
            <span class="text-sm" style="color:var(--color-text-muted)">›</span>
          </div>
        </NuxtLink>

        <!-- Liste des exercices -->
        <ul class="flex-1 divide-y text-sm"
            style="border-color:var(--color-border)">
          <li v-if="group.exercises.length === 0"
              class="px-4 py-3"
              style="color:var(--color-text-muted)">
            {{ $t('tags.empty_tag') }}
          </li>
          <li v-for="ex in visibleExercises(group)" :key="ex.id">
            <NuxtLink :to="`/exercise/${ex.id}`"
                      class="block px-4 py-2.5 hover:bg-black/5 dark:hover:bg-white/5 transition truncate"
                      style="color:var(--color-text)">
              {{ ex.title }}
            </NuxtLink>
          </li>
          <li v-if="group.exercises.length > MAX_VISIBLE"
              class="px-4 py-2 text-xs"
              style="color:var(--color-text-muted)">
            {{ $t('tags.more_exercises', { n: group.exercises.length - MAX_VISIBLE }) }}
          </li>
        </ul>
      </div>
    </div>

    <p v-if="error" class="mt-4 text-sm text-red-500">{{ error }}</p>
  </div>
</template>

<script setup lang="ts">
import type { LibraryGroup, Tag } from '~/composables/useTags'

definePageMeta({ middleware: ['teacher'] })

const { fetchLibrary, deleteTag } = useTags()

const library = ref<LibraryGroup[]>([])
const loading = ref(true)
const error = ref('')
const MAX_VISIBLE = 5

function visibleExercises(group: LibraryGroup) {
  return group.exercises.slice(0, MAX_VISIBLE)
}

async function load() {
  loading.value = true
  error.value = ''
  try {
    library.value = await fetchLibrary()
  } catch (e: any) {
    error.value = e?.data?.detail || e?.message || String(e)
  } finally {
    loading.value = false
  }
}

async function confirmDelete(tag: Tag) {
  if (!confirm(`Supprimer le tag « ${tag.name} » et tous ses liens ?`)) return
  try {
    await deleteTag(tag.id)
    library.value = library.value.filter(g => g.tag.id !== tag.id)
  } catch (e: any) {
    error.value = e?.data?.detail || e?.message || String(e)
  }
}

onMounted(load)
</script>
