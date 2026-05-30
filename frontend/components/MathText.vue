<!-- Renders a short label/title that may contain inline math (`\(…\)`), e.g.
     exercise titles like `Inéquations du type \(|ax+b|\leq c\)`. KaTeX-renders
     the math; plain text is passed through. Decodes HTML entities first. -->
<template>
  <span v-html="html"></span>
</template>

<script setup lang="ts">
const props = defineProps<{ text?: string | null }>()
const { renderMath } = useKatex()
const html = ref('')

function decodeEntities(s: string): string {
  return s
    .replace(/&#(\d+);/g, (_, code) => String.fromCharCode(Number(code)))
    .replace(/&amp;/g, '&').replace(/&lt;/g, '<').replace(/&gt;/g, '>')
}

watch(
  () => props.text,
  async (t) => { html.value = t ? await renderMath(decodeEntities(t)) : '' },
  { immediate: true },
)
</script>
