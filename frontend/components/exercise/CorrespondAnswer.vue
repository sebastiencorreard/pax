<template>
  <!--
    Widget for replytype="correspond" (formule3, etc.). Two columns:
    - left column is fixed (the labels / texts the author wrote)
    - right column is reorderable by the student
    The j-th left item is aligned with the j-th right item; the student's
    goal is to put each right next to its matching left.

    Interaction: HTML5 drag-and-drop (desktop) or tap-to-select-then-tap-
    to-swap (touch/keyboard). Both reorder by swapping two positions.
  -->
  <div class="correspond-grid" :style="gridStyle">
    <div v-for="i in itemCount" :key="`row-${i - 1}`" class="correspond-row">
      <div class="correspond-cell correspond-left"
           :style="leftStyle"
           v-html="leftHtml[i - 1]"></div>

      <div class="correspond-cell correspond-right"
           :class="{
             'is-selected': selectedIdx === i - 1,
             'is-dragging': draggingIdx === i - 1,
             'is-disabled': submitted,
           }"
           :style="rightStyle"
           :draggable="!submitted"
           :tabindex="submitted ? -1 : 0"
           role="button"
           :aria-label="$t('exercise.correspond_aria', { pos: i })"
           @click="onTap(i - 1)"
           @keydown.enter.prevent="onTap(i - 1)"
           @keydown.space.prevent="onTap(i - 1)"
           @dragstart="onDragStart(i - 1, $event)"
           @dragover.prevent
           @drop.prevent="onDrop(i - 1)"
           @dragend="draggingIdx = null"
           v-html="rightHtml[i - 1]"></div>
    </div>
  </div>
</template>

<script setup lang="ts">
import { ref, computed, onMounted, watch } from 'vue'
import { useKatex } from '~/composables/useKatex'

interface CorrespondConfig {
  lefts: string[]
  rights: string[]   // shuffled
  sizev: number
  sizeh1: number
  sizeh2: number
  partial: boolean
}

const props = defineProps<{
  name: string
  config: CorrespondConfig
  value: string  // CSV of rights in user's chosen order
  submitted: boolean
}>()

const emit = defineEmits<{
  (e: 'update:reply', name: string, value: string): void
}>()

const { renderMath } = useKatex()

// `order` maps each row to the index in config.rights of the item currently
// shown on that row. Initial = identity (shows the shuffled order as-is).
const order = ref<number[]>(props.config.rights.map((_, i) => i))

const itemCount = computed(() => props.config.lefts.length)

const leftHtml = ref<string[]>([])
const rightHtmlByOriginalIdx = ref<string[]>([])

// Re-render the right column whenever the order changes
const rightHtml = computed(() =>
  order.value.map(idx => rightHtmlByOriginalIdx.value[idx] ?? '')
)

const gridStyle = computed(() => ({
  display: 'grid',
  gridTemplateColumns: 'auto',
  gap: '4px',
  margin: '0 auto',
  width: `${props.config.sizeh1 + props.config.sizeh2 + 24}px`,
  maxWidth: '100%',
}))

const leftStyle = computed(() => ({
  minHeight: `${props.config.sizev}px`,
  width: `${props.config.sizeh1}px`,
}))

const rightStyle = computed(() => ({
  minHeight: `${props.config.sizev}px`,
  width: `${props.config.sizeh2}px`,
}))

// State for tap-to-swap and drag-and-drop
const selectedIdx = ref<number | null>(null)
const draggingIdx = ref<number | null>(null)

function emitReply() {
  const csv = order.value.map(idx => props.config.rights[idx]).join(',')
  emit('update:reply', props.name, csv)
}

function swap(i: number, j: number) {
  if (i === j) return
  const o = [...order.value]
  ;[o[i], o[j]] = [o[j], o[i]]
  order.value = o
  emitReply()
}

function onTap(i: number) {
  if (props.submitted) return
  if (selectedIdx.value === null) {
    selectedIdx.value = i
    return
  }
  if (selectedIdx.value === i) {
    selectedIdx.value = null
    return
  }
  swap(selectedIdx.value, i)
  selectedIdx.value = null
}

function onDragStart(i: number, e: DragEvent) {
  if (props.submitted) {
    e.preventDefault()
    return
  }
  draggingIdx.value = i
  selectedIdx.value = null
  e.dataTransfer?.setData('text/plain', String(i))
  e.dataTransfer!.effectAllowed = 'move'
}

function onDrop(i: number) {
  if (props.submitted) return
  if (draggingIdx.value === null) return
  swap(draggingIdx.value, i)
  draggingIdx.value = null
}

// Render KaTeX for left/right items once at mount
async function renderAll() {
  leftHtml.value = await Promise.all(
    props.config.lefts.map(s => renderMath(s))
  )
  rightHtmlByOriginalIdx.value = await Promise.all(
    props.config.rights.map(s => renderMath(s))
  )
}

onMounted(renderAll)
watch(() => props.config, renderAll, { deep: true })

// Emit the initial value so the parent sees the shuffled order from the start
// (if user submits without touching anything, we still send something coherent
// rather than empty).
onMounted(() => {
  if (!props.value) emitReply()
})
</script>

<style scoped>
.correspond-grid {
  font-size: 0.95rem;
}

.correspond-row {
  display: grid;
  grid-template-columns: auto 1fr;
  gap: 16px;
  align-items: center;
  margin-bottom: 4px;
}

.correspond-cell {
  display: flex;
  align-items: center;
  justify-content: center;
  text-align: center;
  padding: 8px 12px;
  border-radius: 8px;
  box-sizing: border-box;
  border: 1px solid var(--color-border);
  background: var(--color-surface);
  color: var(--color-text);
  transition: transform 120ms ease, box-shadow 120ms ease,
              border-color 120ms ease, background 120ms ease;
}

.correspond-left {
  background: color-mix(in srgb, var(--color-text) 6%, transparent);
  cursor: default;
}

.correspond-right {
  cursor: grab;
  user-select: none;
}
.correspond-right:hover:not(.is-disabled) {
  border-color: var(--color-primary, #3b82f6);
  box-shadow: 0 2px 4px rgba(0, 0, 0, 0.06);
}
.correspond-right.is-selected {
  border-color: var(--color-primary, #3b82f6);
  background: color-mix(in srgb, var(--color-primary, #3b82f6) 12%, transparent);
  box-shadow: 0 0 0 2px color-mix(in srgb, var(--color-primary, #3b82f6) 30%, transparent);
}
.correspond-right.is-dragging {
  opacity: 0.4;
  cursor: grabbing;
}
.correspond-right.is-disabled {
  cursor: default;
  opacity: 0.75;
}
</style>
