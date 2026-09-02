<template>
  <div ref="host" class="pax-geogebra-wrapper" :style="wrapperStyle"></div>
</template>

<script setup lang="ts">
import { computed, onMounted, ref, watch } from 'vue'
import { mountGeogebra, type GeogebraConfig } from '~/composables/useGeogebra'

const props = defineProps<{ config: GeogebraConfig }>()

const host = ref<HTMLElement | null>(null)

// L'applet se construit à la taille que l'exercice a demandée ; on borne pour
// ne pas déborder sur les fenêtres étroites.
const wrapperStyle = computed(() => {
  const w = Number(props.config?.params?.width) || 300
  return `width:${w}px;max-width:100%;margin-right:auto;`
})

async function build() {
  if (!import.meta.client || !host.value || !props.config) return
  try {
    await mountGeogebra(host.value, props.config)
  } catch (e) {
    console.error('GeoGebra applet init failed', e)
  }
}

onMounted(build)
// Nouvel exercice, nouvelle figure : on reconstruit.
watch(() => props.config, build)
</script>
