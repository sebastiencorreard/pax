<template>
  <!--
    Widget for replytype="crossword" — `anstype/crossword.input` de WIMS.
    Une case de saisie par lettre, les noirs, les numéros, les définitions.
    Le backend n'envoie que le **masque** de la grille (numéro ≥ 0 pour une
    case à remplir, -1 pour un noir) : les lettres restent dans l'attendu.
    La réponse part comme WIMS la compose (`sendanswer()`) — une rangée par
    ligne, chaque case suivie d'une virgule — et vide tant qu'une case reste
    blanche.
  -->
  <div class="cw">
    <div class="cw-grille-bloc">
      <button
type="button" class="cw-sens" :disabled="submitted"
              :aria-label="$t('exercise.crossword_direction', { sens: sensLabel })"
              @click="sens = sens === 'h' ? 'v' : 'h'">
        <span aria-hidden="true">{{ sens === 'h' ? '→' : '↓' }}</span>
      </button>
      <table class="cw-grille">
        <tbody>
          <tr v-for="(rangee, k) in config.cells" :key="k">
            <template v-for="(num, j) in rangee" :key="j">
              <td v-if="num < 0" class="cw-noir"/>
              <td v-else class="cw-case" :class="etatCase(k, j)">
                <button
v-if="num > 0" type="button" class="cw-num"
                        :class="{ 'is-actif': actif === num }"
                        :title="aideBulle(num)"
                        @click="choisir(num, k, j)">{{ num }}</button>
                <input
:ref="el => poser(k, j, el as HTMLInputElement | null)"
                       class="cw-input" maxlength="1" autocapitalize="none"
                       autocomplete="off" spellcheck="false"
                       :aria-label="$t('exercise.crossword_cell', { r: k + 1, c: j + 1 })"
                       :value="lettre(k, j)" :disabled="submitted"
                       @input="saisie(k, j, $event)"
                       @keydown="touche(k, j, $event)" >
                <span v-if="submitted && corrige(k, j)" class="cw-attendu">{{ corrige(k, j) }}</span>
              </td>
            </template>
          </tr>
        </tbody>
      </table>
    </div>
    <div v-if="config.aide !== 'tooltip'" class="cw-defs">
      <template v-for="bloc in blocs" :key="bloc.sens">
        <div v-if="bloc.items.length" class="cw-defs-bloc">
          <div class="cw-defs-titre">{{ bloc.titre }}</div>
          <div
v-for="[n, texte] in bloc.items" :key="n" class="cw-def"
               :class="{ 'is-actif': actif === n }">
            <span class="cw-def-num">{{ n }}</span>
            <!-- Du HTML d'auteur, comme l'énoncé : `baleine`, `cap` et `vigie`
                 donnent leurs deux sens en `<ol>`, que WIMS insère tel quel. -->
            <!-- eslint-disable-next-line vue/no-v-html -->
            <span class="cw-def-texte" v-html="texte" />
          </div>
        </div>
      </template>
    </div>
  </div>
</template>

<script setup lang="ts">
import { ref, computed, watch } from 'vue'

interface CrosswordConfig {
  rows: number
  cols: number
  cells: number[][]
  horizontal: [number, string][]
  vertical: [number, string][]
  aide: 'allhelp' | 'tooltip' | 'clic'
}

const props = defineProps<{
  name: string
  config: CrosswordConfig
  value: string
  submitted: boolean
  expected?: string
}>()
const emit = defineEmits<{ (e: 'update:reply', name: string, value: string): void }>()
const { t } = useI18n()

const sens = ref<'h' | 'v'>('h')
const actif = ref<number | null>(null)
const sensLabel = computed(() => sens.value === 'h' ? t('exercise.crossword_across') : t('exercise.crossword_down'))

function vide(): string[][] {
  return props.config.cells.map(r => r.map(() => ''))
}
// Relire une réponse déjà envoyée (même format que `reponse`).
function lire(v: string): string[][] {
  const g = vide()
  ;(v || '').split('\n').forEach((ligne, k) => {
    const rangee = g[k]
    if (!rangee) return
    ligne.split(',').forEach((c, j) => {
      if (j < rangee.length && estCase(k, j)) rangee[j] = c
    })
  })
  return g
}
const lettres = ref<string[][]>(lire(props.value))
function lettre(k: number, j: number): string {
  return lettres.value[k]?.[j] ?? ''
}
function ecrire(k: number, j: number, c: string) {
  const rangee = lettres.value[k]
  if (rangee && j < rangee.length) rangee[j] = c
}
watch(() => props.value, v => {
  if (v !== reponse()) lettres.value = lire(v)
})

const champs = new Map<string, HTMLInputElement>()
function poser(k: number, j: number, el: HTMLInputElement | null) {
  if (el) champs.set(`${k},${j}`, el)
  else champs.delete(`${k},${j}`)
}
function estCase(k: number, j: number) {
  return (props.config.cells[k]?.[j] ?? -1) >= 0
}
function focus(k: number, j: number) {
  const el = champs.get(`${k},${j}`)
  if (el) { el.focus(); el.select() }
}

function reponse(): string {
  const cells = props.config.cells
  for (let k = 0; k < cells.length; k++)
    for (let j = 0; j < (cells[k]?.length ?? 0); j++)
      if (estCase(k, j) && !lettre(k, j)) return ''
  return lettres.value.map(r => r.map(c => c + ',').join('')).join('\n')
}
function publier() {
  emit('update:reply', props.name, reponse())
}

function saisie(k: number, j: number, e: Event) {
  const el = e.target as HTMLInputElement
  const c = el.value.slice(-1)
  ecrire(k, j, c)
  el.value = c
  publier()
  if (!c) return
  // `posfleche` : la case suivante dans le sens de saisie, si elle existe.
  const [k2, j2] = sens.value === 'h' ? [k, j + 1] : [k + 1, j]
  if (estCase(k2, j2)) focus(k2, j2)
}

function touche(k: number, j: number, e: KeyboardEvent) {
  const pas: Record<string, [number, number]> = {
    ArrowRight: [0, 1], ArrowLeft: [0, -1], ArrowDown: [1, 0], ArrowUp: [-1, 0],
  }
  const d = pas[e.key]
  if (d) {
    const [dk, dj] = d
    if (estCase(k + dk, j + dj)) { e.preventDefault(); focus(k + dk, j + dj) }
    return
  }
  if (e.key === 'Backspace' && !lettre(k, j)) {
    const [k2, j2] = sens.value === 'h' ? [k, j - 1] : [k - 1, j]
    if (estCase(k2, j2)) { e.preventDefault(); ecrire(k2, j2, ''); publier(); focus(k2, j2) }
  }
}

// `showdef(n)` : la définition du numéro, et le sens de saisie qui va avec.
function choisir(n: number, k: number, j: number) {
  const deja = actif.value === n
  actif.value = n
  const h = props.config.horizontal.some(([m]) => m === n)
  const v = props.config.vertical.some(([m]) => m === n)
  if (h && v) sens.value = deja ? (sens.value === 'h' ? 'v' : 'h') : 'h'
  else sens.value = v ? 'v' : 'h'
  focus(k, j)
}

const blocs = computed(() => {
  const filtre = (l: [number, string][]) =>
    props.config.aide === 'allhelp' ? l : l.filter(([n]) => n === actif.value)
  return [
    { sens: 'h', titre: t('exercise.crossword_across'), items: filtre(props.config.horizontal) },
    { sens: 'v', titre: t('exercise.crossword_down'), items: filtre(props.config.vertical) },
  ]
})

function aideBulle(n: number): string | undefined {
  if (props.config.aide !== 'tooltip') return undefined
  const h = props.config.horizontal.find(([m]) => m === n)
  const v = props.config.vertical.find(([m]) => m === n)
  // Un `title` n'affiche pas de HTML : on n'en garde que le texte.
  const brut = (html: string) => html.replace(/<li[^>]*>/gi, ' • ').replace(/<[^>]*>/g, '').replace(/\s+/g, ' ').trim()
  return [h && `→ ${brut(h[1])}`, v && `↓ ${brut(v[1])}`].filter(Boolean).join('\n')
}

// Après envoi : la grille attendue, pour marquer chaque case (`anstype/crossword`).
const grilleAttendue = computed<string[][]>(() => {
  const m = /^\[([\s\S]*?)\]/.exec(props.expected || '')
  if (!m) return []
  return (m[1] ?? '').split('\n').map(l => l.split(',').map(c => c.trim()))
})
function norm(s: string) {
  return (s || '').normalize('NFKD').replace(/[̀-ͯ]/g, '').trim().toLowerCase()
}
function corrige(k: number, j: number): string {
  const a = grilleAttendue.value[k]?.[j]
  if (!a) return ''
  return norm(a) === norm(lettre(k, j)) ? '' : a
}
function etatCase(k: number, j: number) {
  if (!props.submitted || !grilleAttendue.value.length) return {}
  const juste = !corrige(k, j)
  return { 'is-correct': juste, 'is-wrong': !juste }
}
</script>

<style scoped>
/* Les noirs restent noirs dans les deux thèmes : `--color-text` s'éclaircit en
   sombre, et la grille s'inverserait. */
.cw { --cw-noir: #1e293b; display: flex; flex-wrap: wrap; gap: 1.5rem; align-items: flex-start; margin: 0.75rem 0; }
.cw-grille-bloc { display: flex; flex-direction: column; align-items: flex-start; gap: 0.4rem; }
.cw-sens {
  border: 1px solid var(--color-border); border-radius: 0.375rem; background: var(--color-surface);
  color: var(--color-text); font-size: 1.1rem; line-height: 1; padding: 0.25rem 0.6rem; cursor: pointer;
}
.cw-grille { border-collapse: collapse; }
.cw-grille td { width: 2.2rem; height: 2.2rem; padding: 0; position: relative; }
.cw-noir { background: var(--cw-noir); border: 1px solid var(--cw-noir); }
:global(.dark) .cw { --cw-noir: #020617; }
.cw-case { border: 1px solid var(--color-text-muted); background: var(--color-surface); }
.cw-case.is-correct { background: color-mix(in srgb, var(--color-success) 15%, var(--color-surface)); }
.cw-case.is-wrong { background: color-mix(in srgb, var(--color-error) 15%, var(--color-surface)); }
.cw-num {
  position: absolute; top: 1px; left: 2px; z-index: 1; padding: 0; border: 0; background: none;
  font-size: 0.6rem; line-height: 1; color: var(--color-primary); cursor: pointer;
}
.cw-num.is-actif { font-weight: 700; }
.cw-input {
  width: 100%; height: 100%; border: 0; background: transparent; text-align: center;
  font-size: 1.05rem; text-transform: uppercase; color: var(--color-text); padding: 0;
}
.cw-input:focus { outline: 2px solid var(--color-primary); outline-offset: -2px; }
.cw-attendu {
  position: absolute; right: 2px; bottom: 1px; font-size: 0.6rem; color: var(--color-success);
  text-transform: uppercase;
}
.cw-defs { display: flex; flex-direction: column; gap: 0.75rem; max-width: 28rem; }
.cw-defs-titre { font-weight: 600; margin-bottom: 0.25rem; }
.cw-def { font-size: 0.9rem; padding: 0.1rem 0.3rem; border-radius: 0.25rem; }
.cw-def.is-actif { background: color-mix(in srgb, var(--color-primary) 12%, transparent); }
.cw-def-num { font-weight: 600; color: var(--color-primary); margin-right: 0.3em; }
.cw-def-texte :deep(ol) { list-style: decimal; padding-left: 1.75rem; margin: 0.15rem 0; }
.cw-def-texte :deep(ul) { list-style: disc; padding-left: 1.75rem; margin: 0.15rem 0; }
@media (max-width: 480px) {
  .cw-grille td { width: 1.7rem; height: 1.7rem; }
  .cw-input { font-size: 0.9rem; }
}
</style>
