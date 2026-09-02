<template>
  <template v-for="(node, i) in nodes" :key="i">
    <!-- Layout group (e.g. a CSS-flex .container): a real <div> wrapping its
         child segments, so the exercise CSS can lay them out. -->
    <div v-if="node.kind === 'group'" :class="node.class" class="pax-group">
      <ExerciseStatementNodes :nodes="node.children" />
    </div>

    <!-- Leaf segments -->
    <template v-else>
      <div v-if="node.seg.type === 'html' && node.seg.content.includes('<table')"
           v-html="node.seg.content"></div>
      <span v-else-if="node.seg.type === 'html'" v-html="node.seg.content"></span>

      <ExerciseCfSlot v-else-if="node.seg.type === 'slot'"
        :name="node.seg.name"
        :index="node.seg.index ?? 0"
        :value="ctx.cfValue(node.seg.name, node.seg.index ?? 0)"
        :state="ctx.cfSlotState(node.seg.name, node.seg.index ?? 0)"
        :choices-html="ctx.clickfillChoicesHtml.value"
        :dragging="ctx.draggingChoice.value"
        :pending="ctx.pendingChoice.value"
        :submitted="ctx.submitted.value"
        @place="(name, val, idx) => { ctx.setCfSlot(name, idx, val); ctx.pendingChoice.value = null }"
        @clear="(name, idx) => { ctx.setCfSlot(name, idx, '') }"
      />

      <input v-else-if="node.seg.type === 'input'"
        type="text"
        :name="node.seg.name"
        :value="ctx.replies.value[node.seg.name]"
        @input="e => ctx.updateReply(node.seg.name, (e.target as HTMLInputElement).value)"
        :style="{ width: node.seg.width, minWidth: '6ch' }"
        :disabled="ctx.submitted.value"
        :class="[ctx.inputClass(node.seg.name), { 'is-sup': node.seg.is_sup }]"
        autocomplete="off"
        v-bind="node.seg.attrs"
        @dragover.prevent
        @drop.prevent
        @keydown.enter.prevent="() => { if (!ctx.submitted.value && !ctx.loading.value) ctx.onSubmit() }"
      />

      <textarea v-else-if="node.seg.type === 'textarea'"
        :name="node.seg.name"
        :value="ctx.replies.value[node.seg.name]"
        @input="e => ctx.updateReply(node.seg.name, (e.target as HTMLTextAreaElement).value)"
        :rows="node.seg.rows"
        :cols="node.seg.cols"
        :disabled="ctx.submitted.value"
        class="rounded border px-2 py-1 text-sm font-mono resize"
        style="background:var(--color-bg);border-color:var(--color-border);color:var(--color-text)"
        v-bind="node.seg.attrs"
      />

      <ExerciseCorrespondAnswer v-else-if="node.seg.type === 'correspond'"
        :name="node.seg.name"
        :config="node.seg.config"
        :value="ctx.replies.value[node.seg.name] || ''"
        :expected="ctx.checkResult.value?.results.find(r => r.input_name === node.seg.name)?.expected || ''"
        :submitted="ctx.submitted.value"
        @update:reply="(name, val) => ctx.updateReply(name, val)"
      />

      <ExerciseCoordPlane v-else-if="node.seg.type === 'coord'"
        :name="node.seg.name"
        :image="node.seg.image"
        :svg="node.seg.svg"
        :value="ctx.replies.value[node.seg.name] || ''"
        :submitted="ctx.submitted.value"
        :correct="ctx.checkResult.value?.results.find(r => r.input_name === node.seg.name)?.correct ?? null"
        @update:reply="(name, val) => ctx.updateReply(name, val)"
      />

      <ExerciseDrawAnswer v-else-if="node.seg.type === 'draw'"
        :name="node.seg.name"
        :image="node.seg.image"
        :svg="node.seg.svg"
        :objet="node.seg.objet"
        :couleur="node.seg.couleur"
        :xrange="node.seg.xrange"
        :yrange="node.seg.yrange"
        :width="node.seg.width"
        :height="node.seg.height"
        :value="ctx.replies.value[node.seg.name] || ''"
        :expected="ctx.checkResult.value?.results.find(r => r.input_name === node.seg.name)?.expected || ''"
        :submitted="ctx.submitted.value"
        :correct="ctx.checkResult.value?.results.find(r => r.input_name === node.seg.name)?.correct ?? null"
        @update:reply="(name, val) => ctx.updateReply(name, val)"
      />

      <ExerciseCodemirror v-else-if="node.seg.type === 'codeeditor'"
        :config="node.seg.config"
      />

      <ExerciseGeogebra v-else-if="node.seg.type === 'geogebra'"
        :config="node.seg.config"
      />

      <ExerciseJmol v-else-if="node.seg.type === 'jmol'"
        :config="node.seg.config"
      />

      <ExerciseJsxgraph v-else-if="node.seg.type === 'jsxgraph'"
        :name="node.seg.name"
        :js="node.seg.js"
        :width="node.seg.width"
        :height="node.seg.height"
        :maxw="node.seg.maxw"
        :minw="node.seg.minw"
        :reply="node.seg.reply"
        :submitted="ctx.submitted.value"
        @update:reply="(name, val) => ctx.updateReply(name, val)"
      />

      <select v-else-if="node.seg.type === 'menu'"
        :value="ctx.replies.value[node.seg.name]"
        @change="e => ctx.updateReply(node.seg.name, (e.target as HTMLSelectElement).value)"
        :disabled="ctx.submitted.value"
        class="inline-block px-3 py-1.5 rounded border mx-1 transition"
        style="border-color:var(--color-border);background:var(--color-surface)">
        <option value="">{{ node.seg.label }}</option>
        <option v-for="choice in (ctx.menuChoicesHtml.value[node.seg.name] ?? [])"
                :key="choice.raw"
                :value="choice.raw"
                v-html="choice.html">
        </option>
      </select>

      <label v-else-if="node.seg.type === 'radio-inline'"
        class="pax-radio-inline" :class="riClass(node.seg)">
        <input type="radio"
          :name="node.seg.name"
          :value="node.seg.value"
          :checked="ctx.replies.value[node.seg.name] === node.seg.value"
          :disabled="ctx.submitted.value"
          @change="ctx.updateReply(node.seg.name, node.seg.value)" />
        <span v-html="node.seg.content"></span>
      </label>
    </template>
  </template>
</template>

<script setup lang="ts">
import { inject } from 'vue'
import type { SegmentNode } from '~/composables/useExerciseLogic'
import { PAX_STATEMENT_CTX, type PaxStatementCtx } from '~/composables/useExerciseLogic'

defineProps<{ nodes: SegmentNode[] }>()

const ctx = inject(PAX_STATEMENT_CTX) as PaxStatementCtx

// Selected / correct / incorrect state of an inline radio choice.
function riClass(seg: { name: string; value: string }): string {
  const selected = ctx.replies.value[seg.name] === seg.value
  if (!ctx.submitted.value) return selected ? 'is-selected' : ''
  const r = ctx.checkResult.value?.results.find(x => x.input_name === seg.name)
  if (!r) return ''
  if (seg.value === r.expected) return 'is-correct'
  if (selected && !r.correct) return 'is-incorrect'
  return ''
}
</script>

<style scoped>
.pax-radio-inline {
  display: flex;
  align-items: center;
  gap: 0.6rem;
  padding: 0.4rem 0.8rem;
  border: 1px solid var(--color-border);
  border-radius: 0.5rem;
  cursor: pointer;
  transition: border-color 0.15s, background 0.15s;
}
.pax-radio-inline:hover { border-color: var(--color-primary); }
.pax-radio-inline input { accent-color: var(--color-primary); }
.pax-radio-inline.is-selected {
  border-color: var(--color-primary);
  background: color-mix(in srgb, var(--color-primary) 8%, transparent);
}
.pax-radio-inline.is-correct {
  border-color: var(--color-success);
  background: color-mix(in srgb, var(--color-success) 12%, transparent);
}
.pax-radio-inline.is-incorrect {
  border-color: var(--color-error);
  background: color-mix(in srgb, var(--color-error) 12%, transparent);
}
</style>
