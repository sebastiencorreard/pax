<template>
  <div>
    <!-- Énoncé -->
    <div class="px-6 py-6">
      <div ref="statementEl"
           class="oef-statement"
           @click="(e) => { handleMarkClick(e); handleCfSlotClick(e) }"
           @input="handleInlineInput"
           @change="handleCheckboxChange"
           @dragover.prevent
           @dragenter="handleCfSlotDragEnter"
           @dragleave="handleCfSlotDragLeave"
           @drop="handleCfSlotDrop"
           @keydown.enter.prevent="(e) => { if (!submitted && !loading && (e.target as HTMLElement)?.tagName !== 'TEXTAREA') emit('submit') }">
        <ExerciseStatementNodes :nodes="segmentTree" />

        <!-- Radio answers, rendered inside the statement so the question frame
             (.wims_question) englobes them. Laid out horizontally, wrapping to
             the next line when there isn't room. -->
        <div v-if="hasRadioAnswers" class="oef-answer-zone">
          <div v-for="ans in rendered.answers" :key="ans.input_name">
            <template v-if="ans.answer_type === 'radio' && ans.options.choices">
              <p class="text-sm font-medium mb-2" style="color:var(--color-text-muted)">
                {{ ans.label || $t('exercise.choose_answer') }}
              </p>
              <div class="flex flex-row flex-wrap items-stretch gap-2">
                <label v-for="choice in (radioChoicesHtml[ans.input_name] ?? [])" :key="choice.raw"
                       class="flex items-center gap-3 px-4 py-3 rounded-lg border cursor-pointer transition"
                       :class="radioClass(ans.input_name, choice.raw)"
                       style="border-color:var(--color-border)">
                  <input type="radio" :name="ans.input_name" :value="choice.raw"
                         :checked="replies[ans.input_name] === choice.raw"
                         @change="updateReply(ans.input_name, choice.raw)"
                         :disabled="submitted" class="accent-blue-500" />
                  <span v-html="choice.html"></span>
                </label>
              </div>
            </template>
          </div>
        </div>
      </div>
    </div>

    <!-- Palette clickfill -->
    <div v-if="hasClickfill && !submitted" class="px-6 pb-4">
      <p class="text-xs mb-2" style="color:var(--color-text-muted)">
        {{ $t('exercise.drag_hint') }}
      </p>
      <div class="flex gap-2 flex-wrap">
        <!-- Clé par rang : un dragfill garde ses doublons (deux étiquettes
             identiques sont deux cartes distinctes). -->
        <div v-for="(choice, ci) in clickfillChoicesHtml" :key="ci"
             :draggable="!choiceUsed(ci)"
             @dragstart="e => { if (choiceUsed(ci)) { e.preventDefault(); return } e.dataTransfer!.setData('text/plain', choice.raw); draggingChoice = choice.raw }"
             @dragend="draggingChoice = null"
             @click="() => { if (!choiceUsed(ci)) pendingChoice = (pendingChoice === choice.raw ? null : choice.raw) }"
             class="px-4 py-2 rounded-lg border font-medium transition select-none text-blue-700 dark:text-blue-200 border-blue-400 bg-blue-50 dark:bg-blue-900/20"
             :class="choiceUsed(ci)
               ? 'opacity-30 cursor-default'
               : (choice.raw === pendingChoice
                 ? 'cursor-grab ring-2 ring-blue-500 border-blue-500 bg-blue-100 dark:bg-blue-900/40'
                 : 'cursor-grab hover:border-blue-500 hover:bg-blue-100 dark:hover:bg-blue-900/30')"
             style="min-width:3rem;text-align:center"
             v-html="choice.html">
        </div>
      </div>
    </div>

  </div>
</template>

<script setup lang="ts">
import { ref, watch, onMounted, computed, provide } from 'vue'
import type { Rendered, Segment, CheckResult } from '~/composables/useExerciseLogic'
import { buildSegmentTree, PAX_STATEMENT_CTX } from '~/composables/useExerciseLogic'
import { hydrateJmolMarkers } from '~/composables/useJsmol'
import { hydrateGeogebraMarkers } from '~/composables/useGeogebra'

const props = defineProps<{
  rendered: Rendered
  statementSegments: Segment[]
  replies: Record<string, string>
  clickfillChoicesHtml: Array<{ raw: string; html: string }>
  radioChoicesHtml: Record<string, Array<{ raw: string; html: string }>>
  menuChoicesHtml: Record<string, Array<{ raw: string; html: string }>>
  hasClickfill: boolean
  // `dragfill` : chaque étiquette ne se dépose qu'une fois (`anstype/dragfill`
  // la retire de `fill_check` dès qu'elle est utilisée), là où un `clickfill`
  // la laisse resservir.
  singleUseFill: boolean
  hasRadioAnswers: boolean
  submitted: boolean
  loading: boolean
  checkResult: CheckResult | null
}>()

const emit = defineEmits<{
  'update:replies': [Record<string, string>]
  'submit': []
}>()

function updateReply(name: string, value: string) {
  emit('update:replies', { ...props.replies, [name]: value })
}

/**
 * Plusieurs champs d'un coup.
 *
 * `updateReply` repart de `props.replies` à chaque appel : deux appels
 * successifs dans la même microtâche partent donc du **même** état, et le
 * second écrase le premier. Un composant qui alimente plusieurs réponses — le
 * `runcode`, qui remplit son champ et les `js2wims1` que le même programme
 * nourrit — doit les émettre ensemble.
 */
function updateReplies(map: Record<string, string>) {
  emit('update:replies', { ...props.replies, ...map })
}

// ── Multi-slot clickfill ─────────────────────────────────────────────────────
// Several drop targets can share one reply name (drag-compose, e.g.
// repgraphint composes ]−2;20[ across slots). Each slot holds one label; the
// reply is their ordered, non-empty values joined by ",". cfSlots is the
// source of truth; replies[name] is derived.
const cfSlots = ref<Record<string, string[]>>({})

const slotCounts = computed<Record<string, number>>(() => {
  const counts: Record<string, number> = {}
  for (const s of props.statementSegments) {
    if (s.type === 'slot') counts[s.name] = (counts[s.name] ?? 0) + 1
    // Cf-slots embedded inside an html segment (e.g. a <table>) aren't `slot`
    // segments — count them too so the replies→slots mirror (debug auto-fill,
    // reset) populates them.
    else if (s.type === 'html' && s.content.includes('<cf-slot')) {
      const re = /<cf-slot\s+name="([^"]+)"/g
      let m: RegExpExecArray | null
      while ((m = re.exec(s.content)) !== null) {
        counts[m[1]] = (counts[m[1]] ?? 0) + 1
      }
    }
  }
  return counts
})

function cfValue(name: string, index: number): string {
  return cfSlots.value[name]?.[index] ?? ''
}

function setCfSlot(name: string, index: number, value: string) {
  const n = slotCounts.value[name] ?? 1
  const arr = (cfSlots.value[name] ?? Array.from({ length: n }, () => '')).slice()
  arr[index] = value
  cfSlots.value = { ...cfSlots.value, [name]: arr }
  updateReply(name, arr.filter(Boolean).join(','))
}

// Per-slot feedback: compare each filled slot (in sequence order) to the
// expected item at the same position.
function cfSlotState(name: string, index: number): '' | 'correct' | 'incorrect' {
  if (!props.submitted || !props.checkResult) return ''
  const r = props.checkResult.results.find(x => x.input_name === name)
  if (!r) return ''
  const expected = (r.expected ?? '').split(',').map(s => s.trim()).filter(Boolean)
  const arr = cfSlots.value[name] ?? []
  const filled = arr.map((v, i) => ({ v, i })).filter(o => o.v)
  const pos = filled.findIndex(o => o.i === index)
  if (pos < 0) return ''
  // Single-slot field, or no usable per-slot expected sequence (e.g. an
  // analyze-checked clickfill whose expected is computed at runtime): colour by
  // the backend's correctness for the whole reply. Only multi-slot drag-compose
  // (expected is an ordered sequence) compares position by position.
  if (filled.length <= 1 || expected.length <= 1) {
    return r.correct ? 'correct' : 'incorrect'
  }
  return filled[pos].v.trim() === (expected[pos] ?? '') ? 'correct' : 'incorrect'
}

// Reset slots when the exercise (segments) changes.
watch(() => props.statementSegments, () => { cfSlots.value = {} })

// Mirror an externally-set reply (debug auto-fill / reset) into the slots
// when it can't be reconstructed from the current slot values. Our own
// setCfSlot updates keep ext === cur, so this is a no-op for user input.
watch(() => props.replies, (r) => {
  for (const name of Object.keys(slotCounts.value)) {
    const ext = r[name] ?? ''
    const cur = (cfSlots.value[name] ?? []).filter(Boolean).join(',')
    if (ext !== cur) {
      const vals = ext ? ext.split(',') : []
      const n = slotCounts.value[name]
      cfSlots.value = {
        ...cfSlots.value,
        [name]: Array.from({ length: n }, (_, i) => vals[i] ?? ''),
      }
    }
  }
}, { deep: true })

// Nombre de cases occupées par chaque étiquette — sert à griser, dans un
// dragfill, autant de cartes que d'exemplaires déjà posés.
const placedCounts = computed<Record<string, number>>(() => {
  const counts: Record<string, number> = {}
  for (const vals of Object.values(cfSlots.value)) {
    for (const v of vals) if (v) counts[v] = (counts[v] ?? 0) + 1
  }
  return counts
})

// La carte de rang `idx` est-elle consommée ? Les exemplaires d'une même
// étiquette se consomment dans l'ordre : la carte est grisée si son rang parmi
// ses homonymes est inférieur au nombre d'exemplaires posés.
function choiceUsed(idx: number): boolean {
  if (!props.singleUseFill) return false
  const raw = props.clickfillChoicesHtml[idx]?.raw
  if (!raw) return false
  let rank = 0
  for (let i = 0; i < idx; i++) {
    if (props.clickfillChoicesHtml[i].raw === raw) rank++
  }
  return rank < (placedCounts.value[raw] ?? 0)
}

const pendingChoice = ref<string | null>(null)
const draggingChoice = ref<string | null>(null)
const statementEl = ref<HTMLElement | null>(null)

function inputClass(name: string) {
  if (!props.submitted || !props.checkResult) return ''
  const r = props.checkResult.results.find(r => r.input_name === name)
  if (!r) return ''
  return r.correct ? 'correct' : 'incorrect'
}

// ── Mark choice (replytype=mark) — event delegation + DOM state sync ─────────

// `mark` est une sélection **multiple** : le script WIMS (`anstype/mark.input`)
// bascule chaque étiquette par un XOR (`replist[k-1]^=1`), puis reconstruit la
// réponse en parcourant les rangs dans l'ordre — `vv=vv+','+repval[i]`. Un
// énoncé comme « Cochez les pays limitrophes de l'Allemagne » en attend neuf ;
// nous n'en gardions qu'un, chaque clic effaçant le précédent.
function markPositions(value: string | undefined): string[] {
  return (value ?? '').split(',').map(p => p.trim()).filter(Boolean)
}

function handleMarkClick(event: MouseEvent) {
  if (props.submitted) return
  const target = (event.target as Element)?.closest('.oef-mark-choice')
  if (!target) return
  const name = target.getAttribute('name')
  const pos = target.getAttribute('data-pos')
  if (!name || !pos) return
  const current = markPositions(props.replies[name])
  const next = current.includes(pos)
    ? current.filter(p => p !== pos)
    : [...current, pos]
  // WIMS relit `replist` de gauche à droite : les rangs sortent triés par
  // position, pas par ordre de clic — et l'attendu qu'ils affrontent l'est
  // aussi (`!positionof` parcourt la liste dans l'ordre).
  next.sort((a, b) => Number(a) - Number(b))
  updateReply(name, next.join(','))
}

function syncMarkChoices() {
  const el = statementEl.value
  if (!el) return
  el.querySelectorAll<HTMLElement>('.oef-mark-choice').forEach(span => {
    const name = span.getAttribute('name') ?? ''
    const pos = span.getAttribute('data-pos') ?? ''
    const selected = markPositions(props.replies[name]).includes(pos)
    span.classList.toggle('mark-selected', selected && !props.submitted)
    span.classList.remove('mark-correct', 'mark-incorrect')
    if (props.submitted && props.checkResult) {
      const result = props.checkResult.results.find(r => r.input_name === name)
      if (result && selected) {
        span.classList.add(result.correct ? 'mark-correct' : 'mark-incorrect')
      }
    }
  })
}

// ── Clickfill drop targets embedded inside a <table> ────────────────────────
// Cf-slots rendered as part of a v-html'd table aren't <ExerciseCfSlot>
// components, so (like mark choices) we hydrate the raw `<cf-slot>` elements
// via event delegation + DOM sync. The interactive standalone slots outside
// tables keep using the component; both share the global .cf-slot styles.

function _closestCfSlot(event: Event): HTMLElement | null {
  return (event.target as Element)?.closest('cf-slot') ?? null
}

function handleCfSlotDrop(event: DragEvent) {
  const slot = _closestCfSlot(event)
  slot?.classList.remove('cf-slot--over')
  if (!slot || props.submitted) return
  event.preventDefault()
  const raw = event.dataTransfer?.getData('text/plain') || draggingChoice.value
  const name = slot.getAttribute('name')
  const index = Number(slot.getAttribute('data-index') ?? '0') || 0
  if (raw && name) {
    setCfSlot(name, index, raw)
    pendingChoice.value = null
  }
}

function handleCfSlotClick(event: MouseEvent) {
  if (props.submitted) return
  const slot = _closestCfSlot(event)
  if (!slot) return
  const name = slot.getAttribute('name')
  const index = Number(slot.getAttribute('data-index') ?? '0') || 0
  if (!name) return
  if (pendingChoice.value) {
    setCfSlot(name, index, pendingChoice.value)
    pendingChoice.value = null
  } else if (cfValue(name, index)) {
    setCfSlot(name, index, '')  // click a filled slot → empty it
  }
}

function handleCfSlotDragEnter(event: DragEvent) {
  const slot = _closestCfSlot(event)
  if (slot && !props.submitted) slot.classList.add('cf-slot--over')
}

function handleCfSlotDragLeave(event: DragEvent) {
  _closestCfSlot(event)?.classList.remove('cf-slot--over')
}

function syncCfSlots() {
  const el = statementEl.value
  if (!el) return
  el.querySelectorAll<HTMLElement>('cf-slot').forEach(slot => {
    const name = slot.getAttribute('name') ?? ''
    const index = Number(slot.getAttribute('data-index') ?? '0') || 0
    slot.classList.add('cf-slot')
    const value = cfValue(name, index)
    const choice = props.clickfillChoicesHtml.find(c => c.raw === value)
    slot.innerHTML = value
      ? `<span class="cf-slot-content">${choice?.html ?? value}</span>`
      : '<span class="cf-slot-placeholder">···</span>'
    slot.classList.toggle('cf-slot--filled', !!value)
    const state = cfSlotState(name, index)
    slot.classList.toggle('cf-slot--correct', state === 'correct')
    slot.classList.toggle('cf-slot--incorrect', state === 'incorrect')
  })
}

watch(
  [
    () => props.replies, () => props.submitted, () => props.checkResult,
    () => props.statementSegments, () => props.clickfillChoicesHtml,
  ],
  () => { syncMarkChoices(); syncCfSlots() },
  { deep: true, flush: 'post' }
)

onMounted(() => { syncMarkChoices(); syncCfSlots() })

// ── Inline native inputs (replytype text fields placed inside <table> for
//    fraction-like layouts, e.g. csgb Q200) — bound via event delegation ─────

function handleInlineInput(event: Event) {
  if (props.submitted) return
  const target = event.target as HTMLElement | null
  if (!target || !target.classList?.contains('oef-input')) return
  const name = target.getAttribute('name')
  if (!name) return
  const value = (target as HTMLInputElement | HTMLTextAreaElement).value
  updateReply(name, value)
}

// Checkbox groups (replytype=checkbox): several native checkboxes share one
// `name` (reply{n}); the reply is the comma-set of checked values. Bound via
// event delegation, same pattern as the inline text inputs above.
function handleCheckboxChange(event: Event) {
  if (props.submitted) return
  const target = event.target as HTMLElement | null
  if (!target) return
  const name = target.getAttribute('name')
  if (!name) return
  // Inline radio (chgrhyper): one native radio per choice in the table, sharing
  // a `name`; the reply is the selected value.
  if (target.classList?.contains('oef-radio')) {
    updateReply(name, (target as HTMLInputElement).value)
    return
  }
  if (!target.classList?.contains('oef-checkbox')) return
  const el = statementEl.value
  if (!el) return
  const checked = Array.from(
    el.querySelectorAll<HTMLInputElement>(`.oef-checkbox[name="${name}"]`)
  ).filter(cb => cb.checked).map(cb => cb.value)
  updateReply(name, checked.join(','))
}

function syncInlineInputs() {
  const el = statementEl.value
  if (!el) return
  el.querySelectorAll<HTMLInputElement | HTMLTextAreaElement>('.oef-input').forEach(input => {
    const name = input.getAttribute('name') ?? ''
    const expected = props.replies[name] ?? ''
    if (input.value !== expected) input.value = expected
    input.disabled = props.submitted
    // Visual feedback after submission
    input.classList.remove('correct', 'incorrect')
    if (props.submitted && props.checkResult) {
      const r = props.checkResult.results.find(r => r.input_name === name)
      if (r) input.classList.add(r.correct ? 'correct' : 'incorrect')
    }
  })
  // Inline radios (chgrhyper): check the selected value, lock + colour after
  // submit (green = correct choice, red = a wrong pick).
  el.querySelectorAll<HTMLInputElement>('.oef-radio').forEach(radio => {
    const name = radio.getAttribute('name') ?? ''
    radio.checked = (props.replies[name] ?? '') === radio.value
    radio.disabled = props.submitted
    radio.classList.remove('correct', 'incorrect')
    if (props.submitted && props.checkResult) {
      const r = props.checkResult.results.find(r => r.input_name === name)
      if (r) {
        if (radio.value === r.expected) radio.classList.add('correct')
        else if (radio.checked && !r.correct) radio.classList.add('incorrect')
      }
    }
  })
  // Reflect the reply set onto each checkbox of the group + lock after submit.
  el.querySelectorAll<HTMLInputElement>('.oef-checkbox').forEach(cb => {
    const name = cb.getAttribute('name') ?? ''
    const set = new Set(
      (props.replies[name] ?? '').split(',').map(s => s.trim()).filter(Boolean)
    )
    cb.checked = set.has(cb.value)
    cb.disabled = props.submitted
    cb.classList.remove('correct', 'incorrect')
    if (props.submitted && props.checkResult) {
      const r = props.checkResult.results.find(r => r.input_name === name)
      if (r) cb.classList.add(r.correct ? 'correct' : 'incorrect')
    }
  })
}

watch(
  [() => props.replies, () => props.submitted, () => props.checkResult, () => props.statementSegments],
  syncInlineInputs,
  { deep: true, flush: 'post' }
)

onMounted(syncInlineInputs)

// ── Applets Jmol posées dans un <table> ─────────────────────────────────────
// Les trois exercices d'`oefmolecule` alignent leurs molécules en tableau, et
// un tableau reste un seul segment HTML : ses marqueurs `.pax-jmol` ne sont
// donc pas des composants, on les hydrate après le rendu. Hors tableau —
// les patrons de polyèdre d'`oefpolynet` — c'est <ExerciseJmol> qui s'en
// charge. `hydrateJmolMarkers` est idempotent : il saute ce qu'il a déjà monté.
function mountTableJmol() {
  const el = statementEl.value
  if (!el) return
  hydrateJmolMarkers(el)
  hydrateGeogebraMarkers(el)
}

watch(() => props.statementSegments, mountTableJmol, { flush: 'post' })
onMounted(mountTableJmol)

function radioClass(inputName: string, choice: string) {
  if (!props.submitted) {
    return props.replies[inputName] === choice
      ? 'border-blue-400 bg-blue-50 dark:bg-blue-900/20'
      : 'hover:border-blue-300'
  }
  const result = props.checkResult?.results.find(r => r.input_name === inputName)
  if (!result) return ''
  if (choice === result.expected) return 'border-green-400 bg-green-50 dark:bg-green-900/20'
  if (choice === props.replies[inputName] && !result.correct) return 'border-red-400 bg-red-50 dark:bg-red-900/20'
  return ''
}

// Focus automatique après chaque chargement : sur le champ que l'énoncé a
// marqué `autofocus` (attribut hérité du paramètre de taille de `\embed`,
// cf. anstype/inputcss.inc) s'il y en a un, sinon sur le premier champ texte.
// L'attribut HTML seul ne suffit pas : posé sur un élément inséré après le
// parsing du document, il ne donne pas le focus.
watch(() => props.statementSegments, () => {
  const root = statementEl.value
  if (!root) return
  const el = root.querySelector<HTMLInputElement>('input[type="text"][autofocus]')
    ?? root.querySelector<HTMLInputElement>('input[type="text"]')
  el?.focus()
}, { flush: 'post' })

// Statement segments folded into a tree (layout groups wrap their children),
// rendered by the recursive ExerciseStatementNodes.
const segmentTree = computed(() => buildSegmentTree(props.statementSegments))

// Shared context for the recursive renderer (avoids prop-drilling).
provide(PAX_STATEMENT_CTX, {
  replies: computed(() => props.replies),
  updateReply,
  updateReplies,
  clickfillChoicesHtml: computed(() => props.clickfillChoicesHtml),
  menuChoicesHtml: computed(() => props.menuChoicesHtml),
  submitted: computed(() => props.submitted),
  loading: computed(() => props.loading),
  checkResult: computed(() => props.checkResult),
  draggingChoice,
  pendingChoice,
  cfValue,
  setCfSlot,
  cfSlotState,
  inputClass,
  onSubmit: () => emit('submit'),
})
</script>

<style scoped>
/* mathmlinput container with answer fields (cercle1 coordinates, intervals,
   sets, systems, fractions): emitted as native MathML by the backend
   (_mml_mathml). The browser stretches the <mo> fences / <mfrac> to the
   content height; the answer <input>s live in <annotation-xml> cells. */
:deep(math.oef-mathml) {
  font-size: 1.05em;
}
:deep(math.oef-mathml mtable) {
  rowspacing: 0.4ex;
}
:deep(.oef-mark-choice) {
  display: inline-block;
  padding: 2px 10px;
  border-radius: 4px;
  border: 1px solid var(--color-border, #d1d5db);
  margin: 1px 2px;
  cursor: pointer;
  transition: border-color 0.15s, background 0.15s;
  background: var(--color-bg, #fff);
  color: var(--color-text, #111);
  /* Keep a choice on one line — KaTeX would otherwise break inline math at a
     binary operator (`2,5 × 10^19` → `2,5 ×` / `10^19`) in a narrow cell. */
  white-space: nowrap;
}
:deep(.oef-mark-choice:hover) {
  border-color: #3b82f6;
  background: #eff6ff;
}
:deep(.oef-mark-choice.mark-selected) {
  border-color: #3b82f6;
  background: #dbeafe;
  font-weight: 600;
  color: #1d4ed8;
}
:deep(.oef-mark-choice.mark-correct) {
  border-color: #16a34a;
  background: #dcfce7;
  color: #15803d;
}
:deep(.oef-mark-choice.mark-incorrect) {
  border-color: #dc2626;
  background: #fee2e2;
  color: #dc2626;
}
/* replytype=checkbox: a native box + its proposition label, clickable as one. */
:deep(.oef-checkbox-label) {
  display: inline-flex;
  align-items: center;
  gap: 4px;
  margin: 1px 4px;
  cursor: pointer;
}
:deep(.oef-checkbox-label:has(.oef-checkbox:disabled)) {
  cursor: default;
}
:deep(.oef-checkbox.correct) {
  accent-color: #16a34a;
}
:deep(.oef-checkbox.incorrect) {
  accent-color: #dc2626;
}
/* Inline radio choices placed in a table next to their figure (chgrhyper). */
:deep(.oef-radio) {
  cursor: pointer;
  width: 1.1em;
  height: 1.1em;
  accent-color: var(--color-primary);
}
:deep(.oef-radio:disabled) {
  cursor: default;
}
:deep(.oef-radio.correct) {
  accent-color: #16a34a;
  outline: 2px solid #16a34a;
  outline-offset: 2px;
}
:deep(.oef-radio.incorrect) {
  accent-color: #dc2626;
  outline: 2px solid #dc2626;
  outline-offset: 2px;
}
:deep(.oef-radio-label) {
  display: inline-flex;
  align-items: center;
  gap: 4px;
  cursor: pointer;
}
/* WIMS per-reply verdict colours (e.g. course step feedback: "reply : BONNE
   REPONSE" green / "MAUVAISE REPONSE" red — lebrun5). */
:deep(.oef_indgood) { color: #16a34a; font-weight: 600; }
:deep(.oef_indbad) { color: #dc2626; font-weight: 600; }
</style>
