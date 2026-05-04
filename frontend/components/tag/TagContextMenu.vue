<template>
  <Teleport to="body">
    <div ref="menuEl"
         class="fixed z-50 rounded-xl border shadow-xl overflow-hidden"
         style="background:var(--color-surface);border-color:var(--color-border);min-width:220px;max-width:300px"
         :style="{ left: pos.x + 'px', top: pos.y + 'px' }">

      <!-- En-tête -->
      <div class="px-3 py-2 border-b"
           style="border-color:var(--color-border)">
        <p class="text-xs font-semibold truncate" style="color:var(--color-text)">
          {{ exerciseTitle }}
        </p>
        <p class="text-xs mt-0.5" style="color:var(--color-text-muted)">
          {{ $t('tags.section_title') }}
        </p>
      </div>

      <!-- Corps -->
      <div class="px-3 py-2 space-y-2">

        <!-- Skeleton -->
        <div v-if="loading" class="flex flex-wrap gap-1.5">
          <span v-for="i in 3" :key="i"
                class="h-6 w-16 rounded-full animate-pulse"
                style="background:var(--color-border)"></span>
        </div>

        <!-- Pills -->
        <div v-else class="flex flex-wrap gap-1.5">
          <button v-for="tag in allTags" :key="tag.id"
                  type="button"
                  :disabled="pending.has(tag.id)"
                  @click.stop="toggle(tag)"
                  class="px-2.5 py-0.5 rounded-full text-xs font-medium border transition-all"
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

        <!-- Nouveau tag -->
        <form @submit.prevent="submitNew" class="flex gap-1.5">
          <input v-model="newName"
                 type="text"
                 :placeholder="$t('tags.new_placeholder')"
                 class="flex-1 px-2 py-1 rounded-lg border text-xs min-w-0"
                 style="background:var(--color-bg);border-color:var(--color-border);color:var(--color-text)"
                 @click.stop />
          <button type="submit"
                  :disabled="!newName.trim() || creating"
                  class="px-2 py-1 rounded-lg text-xs border transition flex-shrink-0 disabled:opacity-40"
                  style="border-color:var(--color-border);color:var(--color-text-muted)">
            {{ creating ? '…' : '+' }}
          </button>
        </form>

        <p v-if="error" class="text-xs text-red-500">{{ error }}</p>
      </div>
    </div>
  </Teleport>
</template>

<script setup lang="ts">
import type { TagWithCount } from '~/composables/useTags'

const props = defineProps<{
  exerciseId: string
  exerciseTitle: string
  rawX: number
  rawY: number
}>()

const emit = defineEmits<{ close: [] }>()

const { fetchTags, fetchExerciseTags, addTagToExercise, createAndAddTag, removeTagFromExercise } = useTags()

const allTags = ref<TagWithCount[]>([])
const exerciseTagIds = ref(new Set<number>())
const loading = ref(true)
const creating = ref(false)
const error = ref('')
const newName = ref('')
const pending = ref(new Set<number>())
const menuEl = ref<HTMLElement | null>(null)

// Position ajustée pour ne pas déborder de l'écran
const pos = computed(() => {
  const menuW = 300
  const menuH = 280
  const x = Math.min(props.rawX, window.innerWidth - menuW - 8)
  const y = Math.min(props.rawY, window.innerHeight - menuH - 8)
  return { x: Math.max(4, x), y: Math.max(4, y) }
})

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

  const existing = allTags.value.find(t => t.name.toLowerCase() === name.toLowerCase())
  if (existing) {
    newName.value = ''
    if (!isActive(existing.id)) await toggle(existing)
    return
  }

  creating.value = true
  error.value = ''
  try {
    await createAndAddTag(props.exerciseId, name)
    newName.value = ''
    const [all, exTags] = await Promise.all([fetchTags(), fetchExerciseTags(props.exerciseId)])
    allTags.value = all
    exerciseTagIds.value = new Set(exTags.map(t => t.id))
  } catch (e: any) {
    error.value = e?.data?.detail || e?.message || String(e)
  } finally {
    creating.value = false
  }
}

// Fermer sur clic extérieur ou Échap
function onDocClick(e: MouseEvent) {
  if (menuEl.value && !menuEl.value.contains(e.target as Node)) emit('close')
}
function onKeydown(e: KeyboardEvent) {
  if (e.key === 'Escape') emit('close')
}

onMounted(() => {
  load()
  // Légère temporisation pour ne pas capturer le clic droit d'ouverture
  setTimeout(() => {
    document.addEventListener('click', onDocClick)
    document.addEventListener('keydown', onKeydown)
  }, 50)
})
onBeforeUnmount(() => {
  document.removeEventListener('click', onDocClick)
  document.removeEventListener('keydown', onKeydown)
})
</script>
