<template>
  <div class="pax-jsxgraph-wrapper">
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
}>()

const boxStyle = computed(() => {
  const w = props.width ?? 500
  const h = props.height ?? 500
  const maxw = props.maxw ?? w
  // A *definite* width (not 100%): inside a `flex: 0 1 auto` wrapper a
  // percentage width is circular and collapses the board to 0. max-width
  // keeps it responsive on narrow / stacked layouts.
  return `width:${maxw}px;max-width:100%;aspect-ratio:${w} / ${h};`
})

async function build() {
  if (!import.meta.client || !props.js) return
  try {
    await loadJsxgraph()
    // The init JS is generated server-side from the exercise (trusted) and
    // calls JXG.JSXGraph.initBoard(name, …) on our container.
    // eslint-disable-next-line @typescript-eslint/no-implied-eval
    new Function(props.js)()
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
