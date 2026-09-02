<template>
  <div ref="host" class="pax-jmol-wrapper" :style="wrapperStyle"></div>
</template>

<script setup lang="ts">
import { computed, onMounted, ref, watch } from 'vue'
import { mountJmol, type JmolConfig } from '~/composables/useJsmol'

const props = defineProps<{ config: JmolConfig }>()

const host = ref<HTMLElement | null>(null)

// L'applet est construite à sa taille en pixels (JSmol pose lui-même la
// largeur sur son conteneur) ; on borne seulement pour ne pas déborder.
const wrapperStyle = computed(() => {
  const w = props.config?.width ?? 200
  return `width:${w}px;max-width:100%;margin-right:auto;`
})

async function build() {
  if (!import.meta.client || !host.value || !props.config) return
  try {
    await mountJmol(host.value, props.config)
  } catch (e) {
    console.error('Jmol applet init failed', e)
  }
}

onMounted(build)
// Nouvel exercice, nouvelle molécule : on reconstruit.
watch(() => props.config, build)
</script>
