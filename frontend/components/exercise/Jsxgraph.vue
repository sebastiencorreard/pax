<template>
  <div class="pax-jsxgraph-wrapper" :style="wrapperStyle">
    <div :id="name" class="jxgbox" :style="boxStyle"></div>
  </div>
</template>

<script setup lang="ts">
import { computed, onMounted, onBeforeUnmount, watch } from 'vue'
import { loadJsxgraph } from '~/composables/useJsxgraph'

const props = defineProps<{
  name: string          // board container id (the init JS calls initBoard(name,…))
  js: string            // board-init JavaScript, authored server-side
  width?: number
  height?: number
  maxw?: number
  minw?: number
  reply?: string        // answer field bound to the dragged point (type=jsxgraph)
  submitted?: boolean   // lock interaction once the answer is checked
}>()

const emit = defineEmits<{ 'update:reply': [name: string, value: string] }>()

// Default display width: the board's natural pixel width (the embed size),
// capped by the spec's `max` bound — this is what WIMS renders. `min` is only
// the responsive floor, not the default. The wrapper is left-aligned and
// capped; the board fills it (width:100%) and its SVG scales with it (see
// <style>), so narrowing the window shrinks the board in place instead of
// clipping/shifting it, down to the `min` floor.
const wrapperStyle = computed(() => {
  const natural = props.width ?? props.maxw ?? 500
  const maxw = props.maxw ?? natural
  const def = Math.min(natural, maxw)
  const floor = props.minw && props.minw > 0 ? `min-width:${props.minw}px;` : ''
  // A *definite* width (not just max-width): inside a `flex: 0 1 auto`
  // wrapper a percentage/auto width is circular and collapses to 0.
  // max-width:100% keeps it responsive; margin-right:auto keeps it left.
  return `width:${def}px;max-width:100%;${floor}margin-right:auto;`
})

const boxStyle = computed(() => {
  const w = props.width ?? 500
  const h = props.height ?? 500
  // Lock dragging once submitted: pointer-events:none freezes the board
  // visually without touching JSXGraph internals.
  const locked = props.submitted ? 'pointer-events:none;' : ''
  return `width:100%;aspect-ratio:${w} / ${h};${locked}`
})

async function build() {
  if (!import.meta.client || !props.js) return
  try {
    await loadJsxgraph()
    // For `type=jsxgraph` answers the server-side script ends with a capture
    // hook that calls `__paxReport(value)` on every drag; forward it to the
    // bound reply field (ignored after submission). Display-only boards never
    // call it. The init JS is trusted (generated server-side) and calls
    // JXG.JSXGraph.initBoard(name, …) on our container.
    const report = (value: string) => {
      if (props.reply && !props.submitted) emit('update:reply', props.reply, value)
    }
    // eslint-disable-next-line @typescript-eslint/no-implied-eval
    new Function('__paxReport', props.js)(report)
  } catch (e) {
    console.error('JSXGraph board init failed', e)
  }
}

function freeBoard() {
  const JXG = (window as unknown as { JXG?: any }).JXG
  const el = import.meta.client ? document.getElementById(props.name) : null
  if (JXG && el) {
    try { JXG.JSXGraph.freeBoard(el) } catch { /* not a board */ }
  }
}

onMounted(build)
// Rebuild when the exercise changes (new init JS / id).
watch(() => props.js, () => { freeBoard(); build() })
onBeforeUnmount(freeBoard)
</script>

<style scoped>
/* Let the JSXGraph SVG scale with its (responsive) container instead of
   keeping the fixed pixel size it was created at — so narrowing the window
   shrinks the board in place rather than clipping or shifting it. */
.pax-jsxgraph-wrapper :deep(.jxgbox svg) {
  width: 100% !important;
  height: 100% !important;
  display: block;
}
</style>
