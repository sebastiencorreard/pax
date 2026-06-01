<template>
  <!-- Clickable repère (WIMS `type=coord`): the inline SVG is the background;
       clicking records the pixel coordinates of the click as the reply, and a
       crosshair marks the chosen spot. -->
  <span class="pax-coord" :class="{ 'pax-coord--done': submitted }">
    <span ref="frame" class="pax-coord-frame" @click="onClick">
      <span v-if="svg" class="pax-coord-img" v-html="svg"></span>
      <img v-else :src="image" alt="repère" class="pax-coord-img" draggable="false" />
      <!-- Marker at the clicked point (image-pixel → CSS via the frame size). -->
      <svg v-if="point" class="pax-coord-mark" :viewBox="`0 0 ${natW} ${natH}`"
           preserveAspectRatio="none" aria-hidden="true">
        <line :x1="point.x - 7" :y1="point.y" :x2="point.x + 7" :y2="point.y" :stroke="markColor" stroke-width="2" />
        <line :x1="point.x" :y1="point.y - 7" :x2="point.x" :y2="point.y + 7" :stroke="markColor" stroke-width="2" />
      </svg>
    </span>
  </span>
</template>

<script setup lang="ts">
import { ref, computed, onMounted } from 'vue'

const props = defineProps<{
  name: string
  image: string
  svg?: string
  value?: string
  submitted?: boolean
  correct?: boolean | null
}>()

const emit = defineEmits<{ 'update:reply': [name: string, value: string] }>()

const frame = ref<HTMLElement | null>(null)
// Natural (drawing) pixel size — the space Ax,Ay live in. Read from the SVG's
// width/height (flydraw emits explicit attributes, e.g. 400×400).
const natW = ref(400)
const natH = ref(400)

function readNaturalSize() {
  const el = frame.value?.querySelector('svg') as SVGSVGElement | null
  if (el) {
    const w = parseFloat(el.getAttribute('width') || '')
    const h = parseFloat(el.getAttribute('height') || '')
    if (w > 0) natW.value = w
    if (h > 0) natH.value = h
  }
}
onMounted(readNaturalSize)

// Parse "(x,y)" / "x,y" back into a point so a restored reply shows its marker.
const point = computed<{ x: number; y: number } | null>(() => {
  const m = (props.value || '').match(/-?\d+(?:\.\d+)?/g)
  return m && m.length >= 2 ? { x: parseFloat(m[0]), y: parseFloat(m[1]) } : null
})

const markColor = computed(() =>
  props.submitted ? (props.correct ? '#16a34a' : '#dc2626') : '#2563eb',
)

function onClick(e: MouseEvent) {
  if (props.submitted) return
  const host = frame.value?.querySelector('.pax-coord-img') as HTMLElement | null
  const rect = (host ?? frame.value)?.getBoundingClientRect()
  if (!rect || rect.width === 0 || rect.height === 0) return
  // CSS click position → drawing-pixel space (round, like WIMS' rint).
  const x = Math.round(((e.clientX - rect.left) / rect.width) * natW.value)
  const y = Math.round(((e.clientY - rect.top) / rect.height) * natH.value)
  emit('update:reply', props.name, `(${x},${y})`)
}
</script>

<style scoped>
.pax-coord { display: inline-block; }
.pax-coord-frame {
  position: relative;
  display: inline-block;
  line-height: 0;
  cursor: crosshair;
  border: 1px solid var(--color-border);
  border-radius: 4px;
}
.pax-coord--done .pax-coord-frame { cursor: default; }
.pax-coord-img { display: inline-block; }
.pax-coord-img :deep(svg) { display: block; max-width: 100%; height: auto; }
.pax-coord-mark {
  position: absolute;
  inset: 0;
  width: 100%;
  height: 100%;
  pointer-events: none;
}
</style>
