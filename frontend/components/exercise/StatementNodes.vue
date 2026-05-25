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
      />

      <ExerciseCorrespondAnswer v-else-if="node.seg.type === 'correspond'"
        :name="node.seg.name"
        :config="node.seg.config"
        :value="ctx.replies.value[node.seg.name] || ''"
        :expected="ctx.checkResult.value?.results.find(r => r.input_name === node.seg.name)?.expected || ''"
        :submitted="ctx.submitted.value"
        @update:reply="(name, val) => ctx.updateReply(name, val)"
      />

      <ExerciseJsxgraph v-else-if="node.seg.type === 'jsxgraph'"
        :name="node.seg.name"
        :js="node.seg.js"
        :width="node.seg.width"
        :height="node.seg.height"
        :maxw="node.seg.maxw"
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
    </template>
  </template>
</template>

<script setup lang="ts">
import { inject } from 'vue'
import type { SegmentNode } from '~/composables/useExerciseLogic'
import { PAX_STATEMENT_CTX, type PaxStatementCtx } from '~/composables/useExerciseLogic'

defineProps<{ nodes: SegmentNode[] }>()

const ctx = inject(PAX_STATEMENT_CTX) as PaxStatementCtx
</script>
