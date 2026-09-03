<template>
  <div ref="host" class="pax-jmol-wrapper" :style="wrapperStyle"></div>
</template>

<script setup lang="ts">
import { computed, onMounted, ref, watch } from 'vue'
import {
  armerClicJmol,
  mountJmol,
  noterSelectionJmol,
  type JmolConfig,
} from '~/composables/useJsmol'

const props = defineProps<{
  config: JmolConfig
  /** Champ alimenté quand la molécule **est** la réponse (`type=jmolclick`). */
  reply?: string
  submitted?: boolean
}>()

const emit = defineEmits<{ 'update:reply': [name: string, value: string] }>()

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
    const applet = await mountJmol(host.value, props.config)
    const pick = props.config.pick
    if (!applet || !pick || !props.reply) return
    // WIMS ne lit la sélection qu'à l'envoi (`oef_js_submit` appelle
    // `finalise()`), ce que PAX n'a pas : le champ suit chaque clic, comme
    // pour les figures JSXGraph et GeoGebra. Le premier report pose la note
    // d'une sélection vide plutôt que de laisser le champ indéfini.
    const report = () => {
      if (props.submitted) return
      emit('update:reply', props.reply!, String(noterSelectionJmol(applet, pick.good)))
    }
    armerClicJmol(applet, report)
    report()
  } catch (e) {
    console.error('Jmol applet init failed', e)
  }
}

onMounted(build)
// Nouvel exercice, nouvelle molécule : on reconstruit.
watch(() => props.config, build)
</script>
