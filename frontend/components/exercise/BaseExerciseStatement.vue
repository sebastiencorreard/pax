<template>
  <div>
    <!-- Énoncé -->
    <div class="px-6 py-6">
      <div ref="statementEl"
           class="oef-statement"
           @keydown.enter.prevent="() => { if (!submitted && !loading) emit('submit') }">
        <template v-for="(seg, i) in statementSegments" :key="i">
          <span v-if="seg.type === 'html'" v-html="seg.content"></span>
          <ExerciseCfSlot v-else-if="seg.type === 'slot'"
            :name="seg.name"
            :value="replies[seg.name] || ''"
            :choices-html="clickfillChoicesHtml"
            :dragging="draggingChoice"
            :pending="pendingChoice"
            :submitted="submitted"
            @place="(name, val) => { updateReply(name, val); pendingChoice = null }"
            @clear="(name) => { updateReply(name, '') }"
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
          <button v-else-if="seg.type === 'mark'"
            type="button"
            class="oef-mark-btn inline-block px-3 py-1 mx-0.5 rounded border transition-colors text-sm font-medium"
            :class="markClass(seg.name, seg.pos)"
            :disabled="submitted"
            @click="!submitted && updateReply(seg.name, String(seg.pos))"
            v-html="seg.content"
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
          <div class="space-y-2">
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
import { ref, watch } from 'vue'
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

const pendingChoice = ref<string | null>(null)
const draggingChoice = ref<string | null>(null)
const statementEl = ref<HTMLElement | null>(null)

function inputClass(name: string) {
  if (!props.submitted || !props.checkResult) return ''
  const r = props.checkResult.results.find(r => r.input_name === name)
  if (!r) return ''
  return r.correct ? 'correct' : 'incorrect'
}

function markClass(name: string, pos: number) {
  const selected = props.replies[name] === String(pos)
  if (!props.submitted) {
    return selected
      ? 'border-blue-500 bg-blue-100 dark:bg-blue-900/30 cursor-pointer'
      : 'border-gray-300 dark:border-gray-600 hover:border-blue-400 hover:bg-blue-50 dark:hover:bg-blue-900/10 cursor-pointer'
  }
  const result = props.checkResult?.results.find(r => r.input_name === name)
  if (!result) return selected ? 'border-blue-400' : 'border-gray-300 dark:border-gray-600'
  if (selected && result.correct) return 'border-green-500 bg-green-100 dark:bg-green-900/30'
  if (selected && !result.correct) return 'border-red-500 bg-red-100 dark:bg-red-900/30'
  return 'border-gray-300 dark:border-gray-600 opacity-60'
}

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
