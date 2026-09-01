<template>
  <!-- Canevas `type=draw` (WIMS `userdraw`) : le fond est la figure, l'élève y
       pose des objets dont la liste de coordonnées — dans le repère du dessin,
       non en pixels — devient la réponse. -->
  <span class="pax-draw" :class="{ 'pax-draw--done': submitted }">
    <span ref="frame" class="pax-draw-frame" @click="onClick">
      <span v-if="svg" class="pax-draw-img" v-html="svg"></span>
      <img v-else :src="image" alt="figure" class="pax-draw-img" draggable="false" />
      <svg class="pax-draw-mark" :viewBox="`0 0 ${natW} ${natH}`"
           preserveAspectRatio="none" aria-hidden="true">
        <template v-for="(o, i) in objets" :key="i">
          <!-- Un objet à deux coordonnées : une croix. -->
          <template v-if="taille === 2">
            <line :x1="px(o[0]) - 7" :y1="py(o[1])" :x2="px(o[0]) + 7" :y2="py(o[1])"
                  :stroke="trait" stroke-width="2" />
            <line :x1="px(o[0])" :y1="py(o[1]) - 7" :x2="px(o[0])" :y2="py(o[1]) + 7"
                  :stroke="trait" stroke-width="2" />
          </template>
          <!-- Deux points : un segment, fléché si le type l'est. -->
          <line v-else :x1="px(o[0])" :y1="py(o[1])" :x2="px(o[2])" :y2="py(o[3])"
                :stroke="trait" stroke-width="2"
                :marker-end="flechee ? `url(#${idFleche})` : undefined" />
        </template>
        <!-- Après correction, les objets attendus, en pointillé : c'est ce que
             WIMS redessine quand le corrigé est montré (`anstype/draw`). -->
        <template v-if="submitted" v-for="(o, i) in objetsAttendus" :key="`g${i}`">
          <template v-if="taille === 2">
            <line :x1="px(o[0]) - 7" :y1="py(o[1])" :x2="px(o[0]) + 7" :y2="py(o[1])"
                  stroke="#2563eb" stroke-width="2" stroke-dasharray="3 2" />
            <line :x1="px(o[0])" :y1="py(o[1]) - 7" :x2="px(o[0])" :y2="py(o[1]) + 7"
                  stroke="#2563eb" stroke-width="2" stroke-dasharray="3 2" />
          </template>
          <line v-else :x1="px(o[0])" :y1="py(o[1])" :x2="px(o[2])" :y2="py(o[3])"
                stroke="#2563eb" stroke-width="2" stroke-dasharray="3 2" />
        </template>
        <!-- Le premier point d'un objet en cours de tracé. -->
        <circle v-if="attente" :cx="px(attente[0])" :cy="py(attente[1])" r="4"
                :fill="trait" fill-opacity="0.5" />
        <defs v-if="flechee">
          <marker :id="idFleche" markerWidth="8" markerHeight="8" refX="7" refY="3"
                  orient="auto">
            <path d="M0,0 L7,3 L0,6 z" :fill="trait" />
          </marker>
        </defs>
      </svg>
    </span>
    <span class="pax-draw-barre">
      <button type="button" class="pax-draw-effacer" :disabled="submitted" @click.stop="effacer">
        Effacer
      </button>
      <span class="pax-draw-aide">{{ aide }}</span>
    </span>
  </span>
</template>

<script setup lang="ts">
import { ref, computed, onMounted } from 'vue'

const props = defineProps<{
  name: string
  image: string
  svg?: string
  objet?: string
  couleur?: string
  xrange?: string
  yrange?: string
  width?: number | string
  height?: number | string
  value?: string
  expected?: string
  submitted?: boolean
  correct?: boolean | null
}>()

const emit = defineEmits<{ 'update:reply': [name: string, value: string] }>()

const frame = ref<HTMLElement | null>(null)
const natW = ref(Number(props.width) || 400)
const natH = ref(Number(props.height) || 400)

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

// Bornes du repère : c'est en ses unités que WIMS attend la réponse.
function bornes(s: string | undefined, defaut: [number, number]): [number, number] {
  const m = (s || '').split(',').map(x => parseFloat(x))
  return m.length >= 2 && m.every(Number.isFinite) ? [m[0], m[1]] : defaut
}
const [xmin, xmax] = bornes(props.xrange, [0, natW.value])
const [ymin, ymax] = bornes(props.yrange, [0, natH.value])

// Nombre de coordonnées par objet — la table `type_cnt` d'`anstype/draw`.
const TAILLES: Record<string, number> = {
  points: 2, crosshairs: 2, polyline: 2, polygon: 2,
  circles: 3,
  segments: 4, arrows: 4, arrows2: 4, rects: 4, lines: 4, demilines: 4,
}
const type = computed(() => (props.objet || 'points').replace(/[0-9.]/g, ''))
const taille = computed(() => TAILLES[type.value] ?? 2)
const flechee = computed(() => type.value.startsWith('arrow'))
const idFleche = `pax-draw-fleche-${props.name}`

const trait = computed(() =>
  props.submitted ? (props.correct ? '#16a34a' : '#dc2626') : (props.couleur || '#2563eb'),
)

const aide = computed(() => {
  if (props.submitted) {
    return objetsAttendus.value.length ? 'En pointillé : la réponse attendue.' : ''
  }
  return taille.value === 2
    ? 'Cliquez pour poser un point.'
    : 'Cliquez le départ, puis l’arrivée.'
})

// La réponse est une liste plate ; on la relit pour afficher les marques.
const nombres = computed<number[]>(() =>
  (props.value || '').split(',').map(x => parseFloat(x)).filter(Number.isFinite),
)
const objets = computed<number[][]>(() => {
  const n = taille.value
  const out: number[][] = []
  for (let i = 0; i + n <= nombres.value.length; i += n) out.push(nombres.value.slice(i, i + n))
  return out
})
// Les objets attendus, pour les reposer sur la figure après correction. Le
// serveur n'envoie que les coordonnées : la figure de fond en est retirée.
const objetsAttendus = computed<number[][]>(() => {
  const n = taille.value
  // Le corrigé arrive groupé — `(3, 3) ; (1, -3)` —, plus lisible qu'une liste
  // plate. On en extrait les nombres, quelle que soit la ponctuation.
  const nums = ((props.expected || '').match(/-?\d+(?:\.\d+)?(?:[eE][-+]?\d+)?/g) || [])
    .map(x => parseFloat(x)).filter(Number.isFinite)
  const out: number[][] = []
  for (let i = 0; i + n <= nums.length; i += n) out.push(nums.slice(i, i + n))
  return out
})

// Coordonnées d'un objet commencé mais pas fini (premier clic d'un segment).
const attente = computed<number[] | null>(() => {
  const reste = nombres.value.length % taille.value
  return reste === 2 ? nombres.value.slice(-2) : null
})

// Repère → pixels du dessin. L'axe des ordonnées est inversé, comme chez flydraw.
const px = (x: number) => ((x - xmin) / (xmax - xmin)) * natW.value
const py = (y: number) => ((ymax - y) / (ymax - ymin)) * natH.value

function onClick(e: MouseEvent) {
  if (props.submitted) return
  const host = frame.value?.querySelector('.pax-draw-img') as HTMLElement | null
  const rect = (host ?? frame.value)?.getBoundingClientRect()
  if (!rect || rect.width === 0 || rect.height === 0) return
  const fx = (e.clientX - rect.left) / rect.width
  const fy = (e.clientY - rect.top) / rect.height
  const x = xmin + fx * (xmax - xmin)
  const y = ymax - fy * (ymax - ymin)
  const arrondi = (v: number) => String(Math.round(v * 1e6) / 1e6)
  const suite = [...(props.value ? props.value.split(',') : []), arrondi(x), arrondi(y)]
  emit('update:reply', props.name, suite.filter(s => s !== '').join(','))
}

function effacer() {
  if (props.submitted) return
  emit('update:reply', props.name, '')
}
</script>

<style scoped>
.pax-draw { display: inline-block; }
.pax-draw-frame {
  position: relative;
  display: inline-block;
  line-height: 0;
  cursor: crosshair;
  border: 1px solid var(--color-border);
  border-radius: 4px;
}
.pax-draw--done .pax-draw-frame { cursor: default; }
.pax-draw-img { display: inline-block; }
.pax-draw-img :deep(svg) { display: block; max-width: 100%; height: auto; }
.pax-draw-mark {
  position: absolute;
  inset: 0;
  width: 100%;
  height: 100%;
  pointer-events: none;
}
.pax-draw-barre {
  display: flex;
  align-items: center;
  gap: 0.75rem;
  margin-top: 0.35rem;
}
.pax-draw-effacer {
  border: 1px solid var(--color-border);
  border-radius: 4px;
  padding: 0.15rem 0.6rem;
  background: transparent;
  cursor: pointer;
  font-size: 0.85em;
}
.pax-draw-effacer:disabled { opacity: 0.5; cursor: default; }
.pax-draw-aide { font-size: 0.85em; opacity: 0.7; }
</style>
