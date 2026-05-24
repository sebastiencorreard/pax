<template>
  <!--
    Read-only display of the correct correspond answer, used in the
    feedback area when the student got at least one pair wrong. Shows
    each left aligned with its expected right, joined by the same
    double-arrow as the live widget.
  -->
  <div class="cf-grid">
    <div v-for="(_, i) in lefts" :key="`fb-${i}`" class="cf-row">
      <div class="cf-cell cf-left" v-html="leftHtml[i]"></div>
      <div class="cf-arrow" aria-hidden="true">
        <svg viewBox="0 0 32 12" width="32" height="12">
          <path d="M5 6 L27 6 M5 6 L9 2 M5 6 L9 10 M27 6 L23 2 M27 6 L23 10"
                stroke="currentColor" stroke-width="1.5" fill="none"
                stroke-linecap="round" stroke-linejoin="round"/>
        </svg>
      </div>
      <div class="cf-cell cf-right" v-html="rightHtml[i]"></div>
    </div>
  </div>
</template>

<script setup lang="ts">
import { ref, onMounted, watch } from 'vue'
import { useKatex } from '~/composables/useKatex'

const props = defineProps<{
  lefts: string[]
  rightsCorrect: string[]
}>()

const { renderMath } = useKatex()
const leftHtml = ref<string[]>([])
const rightHtml = ref<string[]>([])

async function renderAll() {
  leftHtml.value = await Promise.all(props.lefts.map(s => renderMath(s)))
  rightHtml.value = await Promise.all(props.rightsCorrect.map(s => renderMath(s)))
}

onMounted(renderAll)
watch(() => [props.lefts, props.rightsCorrect], renderAll, { deep: true })
</script>

<style scoped>
.cf-grid {
  display: table;
  border-collapse: separate;
  border-spacing: 6px;
  margin: 0;
  font-size: 0.875rem;
}
.cf-row { display: table-row; }
.cf-cell {
  display: table-cell;
  vertical-align: middle;
  padding: 6px 10px;
  text-align: center;
  line-height: 1.4;
  border-radius: 6px;
  box-sizing: border-box;
  border: 1px solid var(--color-border);
  background: var(--color-surface);
  color: var(--color-text);
  min-width: 120px;
}
.cf-left {
  background: color-mix(in srgb, var(--color-text) 6%, transparent);
}
.cf-right {
  border-color: var(--color-success, #16a34a);
  background: color-mix(in srgb, var(--color-success, #16a34a) 14%, transparent);
}
.cf-arrow {
  display: table-cell;
  vertical-align: middle;
  text-align: center;
  width: 36px;
  color: var(--color-primary, #3b82f6);
}
</style>
