<template>
  <!--
    Widget for replytype="correspond". Bijective matching between two
    fixed-position columns: the left column stays in document order, the
    right column items are placed (one per row) so that each is aligned
    with its associated left item. A double-arrow appears between cells
    once the user has explicitly committed the pair (drag-and-drop or
    tap-pair, never right↔right or left↔left).
  -->
  <div class="correspond-grid" :style="gridStyle">
    <div v-for="i in itemCount" :key="`row-${i - 1}`" class="correspond-row">
      <!-- Left cell — index follows the row -->
      <div class="correspond-cell correspond-left"
           :class="{
             'is-selected': selected?.side === 'left' && selected.idx === i - 1,
             'is-dragging': dragSource?.side === 'left' && dragSource.idx === i - 1,
             'is-disabled': submitted,
             'is-drop-target': dragSource?.side === 'right' && hoverRow === i - 1,
           }"
           :style="leftStyle"
           :draggable="!submitted"
           :tabindex="submitted ? -1 : 0"
           role="button"
           :aria-label="$t('exercise.correspond_left_aria', { pos: i })"
           @click="onTap('left', i - 1)"
           @keydown.enter.prevent="onTap('left', i - 1)"
           @keydown.space.prevent="onTap('left', i - 1)"
           @dragstart="onDragStart('left', i - 1, $event)"
           @dragover.prevent="onDragOver('left', i - 1, $event)"
           @dragleave="hoverRow = null"
           @drop.prevent="onDrop('left', i - 1)"
           @dragend="resetDrag()"
           v-html="leftHtml[i - 1]"></div>

      <!-- Connector (double-arrow when committed) -->
      <div class="correspond-arrow" :class="{ 'is-committed': committed.has(i - 1) }">
        <svg v-if="committed.has(i - 1)" viewBox="0 0 32 12" width="32" height="12" aria-hidden="true">
          <path d="M5 6 L27 6 M5 6 L9 2 M5 6 L9 10 M27 6 L23 2 M27 6 L23 10"
                stroke="currentColor" stroke-width="1.5" fill="none" stroke-linecap="round" stroke-linejoin="round"/>
        </svg>
      </div>

      <!-- Right cell — index follows the row, content driven by `order[i-1]` -->
      <div class="correspond-cell correspond-right"
           :class="{
             'is-selected': selected?.side === 'right' && selected.idx === i - 1,
             'is-dragging': dragSource?.side === 'right' && dragSource.idx === i - 1,
             'is-disabled': submitted,
             'is-drop-target': dragSource?.side === 'left' && hoverRow === i - 1,
           }"
           :style="rightStyle"
           :draggable="!submitted"
           :tabindex="submitted ? -1 : 0"
           role="button"
           :aria-label="$t('exercise.correspond_right_aria', { pos: i })"
           @click="onTap('right', i - 1)"
           @keydown.enter.prevent="onTap('right', i - 1)"
           @keydown.space.prevent="onTap('right', i - 1)"
           @dragstart="onDragStart('right', i - 1, $event)"
           @dragover.prevent="onDragOver('right', i - 1, $event)"
           @dragleave="hoverRow = null"
           @drop.prevent="onDrop('right', i - 1)"
           @dragend="resetDrag()"
           v-html="rightHtmlByOriginalIdx[order[i - 1]]"></div>
    </div>
  </div>
</template>

<script setup lang="ts">
import { ref, computed, onMounted, watch } from 'vue'
import { useKatex } from '~/composables/useKatex'

interface CorrespondConfig {
  lefts: string[]
  rights: string[]   // shuffled at backend render time
  sizev: number
  sizeh1: number
  sizeh2: number
  partial: boolean
}

const props = defineProps<{
  name: string
  config: CorrespondConfig
  value: string
  submitted: boolean
}>()

const emit = defineEmits<{
  (e: 'update:reply', name: string, value: string): void
}>()

const { renderMath } = useKatex()

// `order[i]` = which right item (original shuffled index) is currently
// shown on row i. Initial identity = the backend-shuffled order as-is.
const order = ref<number[]>(props.config.rights.map((_, i) => i))
// Rows the user has explicitly associated. Drives the arrow display.
const committed = ref<Set<number>>(new Set())

const itemCount = computed(() => props.config.lefts.length)

const leftHtml = ref<string[]>([])
const rightHtmlByOriginalIdx = ref<string[]>([])

const gridStyle = computed(() => ({
  margin: '0 auto',
  width: `${props.config.sizeh1 + props.config.sizeh2 + 64}px`,
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

type Side = 'left' | 'right'
interface DragRef { side: Side; idx: number }

const selected = ref<DragRef | null>(null)
const dragSource = ref<DragRef | null>(null)
const hoverRow = ref<number | null>(null)

function emitReply() {
  const csv = order.value.map(idx => props.config.rights[idx]).join(',')
  emit('update:reply', props.name, csv)
}

// Pair left row `li` with right row `rj`: swap `order` so the right
// currently on row rj moves to row li. Only row `li` is committed
// (an arrow appears there). The displaced right ends up on row rj but
// that row was not explicitly associated by the user — its old right
// has been "evicted" by the swap.
function pair(li: number, rj: number) {
  if (li !== rj) {
    const o = [...order.value]
    ;[o[li], o[rj]] = [o[rj], o[li]]
    order.value = o
    // Evicted right is no longer where the user had explicitly placed
    // it; drop its commit so its arrow disappears.
    committed.value.delete(rj)
  }
  committed.value.add(li)
  // Re-trigger reactivity for the Set
  committed.value = new Set(committed.value)
  emitReply()
}

function onDragStart(side: Side, idx: number, e: DragEvent) {
  if (props.submitted) {
    e.preventDefault()
    return
  }
  dragSource.value = { side, idx }
  selected.value = null
  e.dataTransfer?.setData('text/plain', `${side}:${idx}`)
  e.dataTransfer!.effectAllowed = 'move'
}

function onDragOver(targetSide: Side, idx: number, e: DragEvent) {
  // Only highlight & accept the drop if it's a cross-column drag.
  if (!dragSource.value || dragSource.value.side === targetSide) {
    e.dataTransfer!.dropEffect = 'none'
    return
  }
  e.dataTransfer!.dropEffect = 'move'
  hoverRow.value = idx
}

function onDrop(dropSide: Side, dropIdx: number) {
  if (props.submitted || !dragSource.value) return
  const src = dragSource.value
  resetDrag()
  // Reject same-side drops (left→left or right→right).
  if (src.side === dropSide) return
  // Normalize to (leftRowIdx, rightRowIdx).
  const li = src.side === 'left' ? src.idx : dropIdx
  const rj = src.side === 'right' ? src.idx : dropIdx
  pair(li, rj)
}

function resetDrag() {
  dragSource.value = null
  hoverRow.value = null
}

// Tap-to-pair: select one cell on one side, then tap a cell on the
// other side to pair them. Same-side tap clears the selection.
function onTap(side: Side, idx: number) {
  if (props.submitted) return
  if (!selected.value) {
    selected.value = { side, idx }
    return
  }
  if (selected.value.side === side) {
    // Same side: either re-select or unselect if same cell
    selected.value = selected.value.idx === idx ? null : { side, idx }
    return
  }
  // Cross-side: pair them
  const li = selected.value.side === 'left' ? selected.value.idx : idx
  const rj = selected.value.side === 'right' ? selected.value.idx : idx
  selected.value = null
  pair(li, rj)
}

async function renderAll() {
  leftHtml.value = await Promise.all(
    props.config.lefts.map(s => renderMath(s))
  )
  rightHtmlByOriginalIdx.value = await Promise.all(
    props.config.rights.map(s => renderMath(s))
  )
}

// Reset state when a new exercise instance is loaded (config changes).
// Without this, committed arrows from the previous question linger.
watch(() => props.config, () => {
  order.value = props.config.rights.map((_, i) => i)
  committed.value = new Set()
  selected.value = null
  dragSource.value = null
  hoverRow.value = null
  renderAll()
  emitReply()
}, { deep: true })

onMounted(() => {
  renderAll()
  // Initial emit so the parent has a value if the user submits without
  // touching anything (matches the shuffled initial order).
  if (!props.value) emitReply()
})
</script>

<style scoped>
.correspond-grid {
  /* Real CSS table — gives each row the same column widths and lets us
     use vertical-align on cells for centring with inline content. */
  display: table;
  border-collapse: separate;
  border-spacing: 8px;
  font-size: 0.95rem;
  margin: 0 auto;
}

.correspond-row {
  display: table-row;
}

.correspond-cell {
  /* table-cell + vertical-align preserves the inline text+KaTeX flow
     (no flex/grid baseline re-targeting), while still centring multi-
     line content vertically inside the fixed-height cell. */
  display: table-cell;
  vertical-align: middle;
  padding: 12px 14px;
  text-align: center;
  line-height: 1.5;
  border-radius: 8px;
  box-sizing: border-box;
  border: 1px solid var(--color-border);
  background: var(--color-surface);
  color: var(--color-text);
  transition: transform 120ms ease, box-shadow 120ms ease,
              border-color 120ms ease, background 120ms ease, opacity 120ms ease;
}

.correspond-left {
  background: color-mix(in srgb, var(--color-text) 6%, transparent);
}

.correspond-arrow {
  display: table-cell;
  vertical-align: middle;
  text-align: center;
  width: 40px;
  color: var(--color-text-muted);
}
.correspond-arrow.is-committed {
  color: var(--color-primary, #3b82f6);
}

.correspond-cell {
  cursor: grab;
  user-select: none;
}
.correspond-cell.is-disabled {
  cursor: default;
  opacity: 0.85;
}
.correspond-cell:not(.is-disabled):hover {
  border-color: var(--color-primary, #3b82f6);
  box-shadow: 0 2px 4px rgba(0, 0, 0, 0.06);
}
.correspond-cell.is-selected {
  border-color: var(--color-primary, #3b82f6);
  background: color-mix(in srgb, var(--color-primary, #3b82f6) 12%, transparent);
  box-shadow: 0 0 0 2px color-mix(in srgb, var(--color-primary, #3b82f6) 30%, transparent);
}
.correspond-cell.is-dragging {
  opacity: 0.4;
  cursor: grabbing;
}
.correspond-cell.is-drop-target {
  border-color: var(--color-primary, #3b82f6);
  background: color-mix(in srgb, var(--color-primary, #3b82f6) 18%, transparent);
  transform: scale(1.02);
}
</style>
