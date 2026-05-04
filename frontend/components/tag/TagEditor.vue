<template>
  <section class="rounded-xl border overflow-hidden"
           style="background:var(--color-surface);border-color:var(--color-border)">
    <header class="px-4 py-2 border-b"
            style="border-color:var(--color-border)">
      <span class="text-sm font-medium">{{ $t('tags.section_title') }}</span>
    </header>

    <div class="px-4 py-3 space-y-3">

      <!-- Skeleton -->
      <div v-if="loading" class="flex flex-wrap gap-2">
        <span v-for="i in 3" :key="i"
              class="h-7 w-20 rounded-full animate-pulse"
              style="background:var(--color-border)"></span>
      </div>

      <!-- Grille de pills (tous les tags de l'utilisateur) -->
      <div v-else class="flex flex-wrap gap-2">
        <button v-for="tag in allTags" :key="tag.id"
                type="button"
                :disabled="pending.has(tag.id)"
                @click="toggle(tag)"
                class="px-3 py-1 rounded-full text-xs font-medium border transition-all"
                :style="isActive(tag.id)
                  ? 'background:var(--color-primary);border-color:var(--color-primary);color:#fff'
                  : 'background:transparent;border-color:var(--color-border);color:var(--color-text-muted)'"
                :class="pending.has(tag.id) ? 'opacity-50 cursor-wait' : 'cursor-pointer hover:opacity-80'">
          {{ tag.name }}
        </button>

        <span v-if="allTags.length === 0"
              class="text-xs"
              style="color:var(--color-text-muted)">
          {{ $t('tags.no_tags_yet') }}
        </span>
      </div>

      <!-- Création d'un nouveau tag -->
      <form @submit.prevent="submitNew" class="flex gap-2">
        <input v-model="newName"
               type="text"
               :placeholder="$t('tags.new_placeholder')"
               class="flex-1 px-3 py-1.5 rounded-lg border text-sm min-w-0"
               style="background:var(--color-bg);border-color:var(--color-border);color:var(--color-text)" />
        <button type="submit"
                :disabled="!newName.trim() || creating"
                class="px-3 py-1.5 rounded-lg text-sm border transition flex-shrink-0 disabled:opacity-40"
                style="border-color:var(--color-border);color:var(--color-text-muted)">
          {{ creating ? '…' : $t('tags.new_add') }}
        </button>
      </form>

      <p v-if="error" class="text-xs text-red-500">{{ error }}</p>
    </div>
  </section>
</template>

<script setup lang="ts">
import type { TagWithCount } from '~/composables/useTags'

const props = defineProps<{ exerciseId: string }>()

const { fetchTags, fetchExerciseTags, addTagToExercise, createAndAddTag, removeTagFromExercise } = useTags()

const allTags = ref<TagWithCount[]>([])
const exerciseTagIds = ref(new Set<number>())
const loading = ref(true)
const creating = ref(false)
const error = ref('')
const newName = ref('')
// IDs des tags dont le toggle est en cours (évite les double-clics)
const pending = ref(new Set<number>())

function isActive(tagId: number): boolean {
  return exerciseTagIds.value.has(tagId)
}

async function load() {
  loading.value = true
  error.value = ''
  try {
    const [all, exTags] = await Promise.all([
      fetchTags(),
      fetchExerciseTags(props.exerciseId),
    ])
    allTags.value = all
    exerciseTagIds.value = new Set(exTags.map(t => t.id))
  } catch (e: any) {
    error.value = e?.data?.detail || e?.message || String(e)
  } finally {
    loading.value = false
  }
}

async function toggle(tag: TagWithCount) {
  if (pending.value.has(tag.id)) return
  pending.value = new Set(pending.value).add(tag.id)
  error.value = ''

  const wasActive = isActive(tag.id)
  // Mise à jour optimiste
  const next = new Set(exerciseTagIds.value)
  wasActive ? next.delete(tag.id) : next.add(tag.id)
  exerciseTagIds.value = next

  try {
    if (wasActive) {
      await removeTagFromExercise(props.exerciseId, tag.id)
      tag.exercise_count--
    } else {
      await addTagToExercise(props.exerciseId, tag.id)
      tag.exercise_count++
    }
  } catch (e: any) {
    // Rollback
    const rollback = new Set(exerciseTagIds.value)
    wasActive ? rollback.add(tag.id) : rollback.delete(tag.id)
    exerciseTagIds.value = rollback
    error.value = e?.data?.detail || e?.message || String(e)
  } finally {
    const p = new Set(pending.value)
    p.delete(tag.id)
    pending.value = p
  }
}

async function submitNew() {
  const name = newName.value.trim()
  if (!name) return

  // Si le tag existe déjà (insensible à la casse), on le bascule simplement
  const existing = allTags.value.find(t => t.name.toLowerCase() === name.toLowerCase())
  if (existing) {
    newName.value = ''
    if (!isActive(existing.id)) await toggle(existing)
    return
  }

  // Sinon : créer + ajouter
  creating.value = true
  error.value = ''
  try {
    await createAndAddTag(props.exerciseId, name)
    newName.value = ''
    // Recharger la liste complète pour récupérer le nouvel id
    const [all, exTags] = await Promise.all([fetchTags(), fetchExerciseTags(props.exerciseId)])
    allTags.value = all
    exerciseTagIds.value = new Set(exTags.map(t => t.id))
  } catch (e: any) {
    error.value = e?.data?.detail || e?.message || String(e)
  } finally {
    creating.value = false
  }
}

onMounted(load)
</script>
