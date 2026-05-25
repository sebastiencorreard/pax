<template>
  <div>
    <!-- Énoncé -->
    <div class="px-6 py-6">
      <div ref="statementEl"
           class="oef-statement"
           @click="handleMarkClick"
           @input="handleInlineInput"
           @change="handleCheckboxChange"
           @keydown.enter.prevent="(e) => { if (!submitted && !loading && (e.target as HTMLElement)?.tagName !== 'TEXTAREA') emit('submit') }">
        <template v-for="(seg, i) in statementSegments" :key="i">
          <!-- Segments containing <table> must use <div> — <span> can't contain block elements -->
          <div v-if="seg.type === 'html' && seg.content.includes('<table')"
               v-html="seg.content"></div>
          <span v-else-if="seg.type === 'html'" v-html="seg.content"></span>
          <ExerciseCfSlot v-else-if="seg.type === 'slot'"
            :name="seg.name"
            :index="seg.index ?? 0"
            :value="cfValue(seg.name, seg.index ?? 0)"
            :state="cfSlotState(seg.name, seg.index ?? 0)"
            :choices-html="clickfillChoicesHtml"
            :dragging="draggingChoice"
            :pending="pendingChoice"
            :submitted="submitted"
            @place="(name, val, idx) => { setCfSlot(name, idx, val); pendingChoice = null }"
            @clear="(name, idx) => { setCfSlot(name, idx, '') }"
          />
          <input v-else-if="seg.type === 'input'"
            type="text"
            :name="seg.name"
            :value="replies[seg.name]"
            @input="e => updateReply(seg.name, (e.target as HTMLInputElement).value)"
            :style="{ width: seg.width, minWidth: '6ch' }"
            :disabled="submitted"
            :class="[inputClass(seg.name), { 'is-sup': seg.is_sup }]"
            autocomplete="off"
            @dragover.prevent
            @drop.prevent
            @keydown.enter.prevent="() => { if (!submitted && !loading) emit('submit') }"
          />
          <textarea v-else-if="seg.type === 'textarea'"
            :name="seg.name"
            :value="replies[seg.name]"
            @input="e => updateReply(seg.name, (e.target as HTMLTextAreaElement).value)"
            :rows="seg.rows"
            :cols="seg.cols"
            :disabled="submitted"
            class="rounded border px-2 py-1 text-sm font-mono resize"
            style="background:var(--color-bg);border-color:var(--color-border);color:var(--color-text)"
          />
          <ExerciseCorrespondAnswer v-else-if="seg.type === 'correspond'"
            :name="seg.name"
            :config="seg.config"
            :value="replies[seg.name] || ''"
            :expected="checkResult?.results.find(r => r.input_name === seg.name)?.expected || ''"
            :submitted="submitted"
            @update:reply="(name, val) => updateReply(name, val)"
          />
          <ExerciseJsxgraph v-else-if="seg.type === 'jsxgraph'"
            :name="seg.name"
            :js="seg.js"
            :width="seg.width"
            :height="seg.height"
            :maxw="seg.maxw"
          />
          <select v-else-if="seg.type === 'menu'"
            :value="replies[seg.name]"
            @change="e => updateReply(seg.name, (e.target as HTMLSelectElement).value)"
            :disabled="submitted"
            class="inline-block px-3 py-1.5 rounded border mx-1 transition"
            style="border-color:var(--color-border);background:var(--color-surface)">
            <option value="">{{ seg.label }}</option>
            <option v-for="choice in (menuChoicesHtml[seg.name] ?? [])"
                    :key="choice.raw"
                    :value="choice.raw"
                    v-html="choice.html">
            </option>
          </select>
        </template>
      </div>
    </div>

    <!-- Palette clickfill -->
    <div v-if="hasClickfill && !submitted" class="px-6 pb-4">
      <p class="text-xs mb-2" style="color:var(--color-text-muted)">
        {{ $t('exercise.drag_hint') }}
      </p>
      <div class="flex gap-2 flex-wrap">
        <div v-for="choice in clickfillChoicesHtml" :key="choice.raw"
             draggable="true"
             @dragstart="e => { e.dataTransfer!.setData('text/plain', choice.raw); draggingChoice = choice.raw }"
             @dragend="draggingChoice = null"
             @click="pendingChoice = (pendingChoice === choice.raw ? null : choice.raw)"
             class="px-4 py-2 rounded-lg border font-medium transition cursor-grab select-none"
             :class="choice.raw === pendingChoice
               ? 'border-blue-500 bg-blue-50 dark:bg-blue-900/30'
               : 'hover:border-blue-400 hover:bg-blue-50 dark:hover:bg-blue-900/10'"
             style="border-color:var(--color-border);min-width:3rem;text-align:center"
             v-html="choice.html">
        </div>
      </div>
    </div>

    <!-- Zone de réponse (pour les radio) -->
    <div v-if="hasRadioAnswers" class="px-6 pb-4 space-y-2">
      <div v-for="ans in rendered.answers" :key="ans.input_name">
        <template v-if="ans.answer_type === 'radio' && ans.options.choices">
          <p class="text-sm font-medium mb-2" style="color:var(--color-text-muted)">
            {{ ans.label || $t('exercise.choose_answer') }}
          </p>
          <!-- 1 col < sm, 2 cols sm–lg, N cols ≥ lg (one per choice, capped at 4).
               inline-grid: shrinks the group to content width; 1fr columns make
               siblings equal-width (sized to the largest choice). -->
          <div class="inline-grid gap-2 grid-cols-1 sm:grid-cols-2"
               :class="radioGridLgClass(radioChoicesHtml[ans.input_name] ?? [])">
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
</template>

<script setup lang="ts">
import { ref, watch, onMounted, computed } from 'vue'
import type { Rendered, Segment, CheckResult } from '~/composables/useExerciseLogic'

const props = defineProps<{
  rendered: Rendered
  statementSegments: Segment[]
  replies: Record<string, string>
  clickfillChoicesHtml: Array<{ raw: string; html: string }>
  radioChoicesHtml: Record<string, Array<{ raw: string; html: string }>>
  menuChoicesHtml: Record<string, Array<{ raw: string; html: string }>>
  hasClickfill: boolean
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

const pendingChoice = ref<string | null>(null)
const draggingChoice = ref<string | null>(null)
const statementEl = ref<HTMLElement | null>(null)

function inputClass(name: string) {
  if (!props.submitted || !props.checkResult) return ''
  const r = props.checkResult.results.find(r => r.input_name === name)
  if (!r) return ''
  return r.correct ? 'correct' : 'incorrect'
}

// Tailwind-safe map: dynamic class names (`lg:grid-cols-${n}`) aren't picked
// up by JIT, so we materialise them as static strings.
function radioGridLgClass(choices: { raw: string }[]): string {
  const n = Math.max(1, Math.min(choices.length, 4))
  return ['lg:grid-cols-1', 'lg:grid-cols-2', 'lg:grid-cols-3', 'lg:grid-cols-4'][n - 1]
}

// ── Mark choice (replytype=mark) — event delegation + DOM state sync ─────────

function handleMarkClick(event: MouseEvent) {
  if (props.submitted) return
  const target = (event.target as Element)?.closest('.oef-mark-choice')
  if (!target) return
  const name = target.getAttribute('name')
  const pos = target.getAttribute('data-pos')
  if (name && pos) updateReply(name, pos)
}

function syncMarkChoices() {
  const el = statementEl.value
  if (!el) return
  el.querySelectorAll<HTMLElement>('.oef-mark-choice').forEach(span => {
    const name = span.getAttribute('name') ?? ''
    const pos = span.getAttribute('data-pos') ?? ''
    const selected = props.replies[name] === pos
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

watch(
  [() => props.replies, () => props.submitted, () => props.checkResult, () => props.statementSegments],
  syncMarkChoices,
  { deep: true, flush: 'post' }
)

onMounted(syncMarkChoices)

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
  if (!target || !target.classList?.contains('oef-checkbox')) return
  const name = target.getAttribute('name')
  const el = statementEl.value
  if (!name || !el) return
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

// Focus automatique sur le premier input texte après chaque chargement
watch(() => props.statementSegments, () => {
  statementEl.value?.querySelector<HTMLInputElement>('input[type="text"]')?.focus()
}, { flush: 'post' })

</script>

<style scoped>
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
</style>
