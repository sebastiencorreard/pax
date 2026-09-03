<template>
  <div ref="host" class="pax-geogebra-wrapper" :style="wrapperStyle"></div>
</template>

<script setup lang="ts">
import { computed, onMounted, ref, watch } from 'vue'
import {
  lireFigureGeogebra,
  mountGeogebra,
  type GeogebraConfig,
  type GeogebraLecture,
} from '~/composables/useGeogebra'

const props = defineProps<{
  config: GeogebraConfig
  /** Champ de réponse lié, quand l'applet *est* la réponse (`type=geogebra`). */
  reply?: string
  /** Les réglages de lecture de la figure ; absents pour une figure d'énoncé. */
  answer?: GeogebraLecture
  submitted?: boolean
}>()

const emit = defineEmits<{ 'update:reply': [name: string, value: string] }>()

const host = ref<HTMLElement | null>(null)

// L'applet se construit à la taille que l'exercice a demandée ; on borne pour
// ne pas déborder sur les fenêtres étroites.
const wrapperStyle = computed(() => {
  const w = Number(props.config?.params?.width) || 300
  return `width:${w}px;max-width:100%;margin-right:auto;`
})

/**
 * Remonte l'état de la figure vers le champ lié.
 *
 * WIMS ne lit l'applet qu'au moment de l'envoi (`oef_js_submit` appelle
 * `geogebra2wims()`), ce que PAX n'a pas : le champ est alimenté en continu,
 * à chaque construction ou déplacement, comme le fait `Jsxgraph.vue` par son
 * rappel `__paxReport`. Un premier appel après le montage pose la figure de
 * départ plutôt que de laisser le champ indéfini — sans quoi l'élève qui ne
 * déplace rien n'enverrait aucune réponse.
 */
function report(api: unknown) {
  if (!props.reply || !props.answer || props.submitted) return
  try {
    const etat = lireFigureGeogebra(api as never, props.answer)
    // `null` : figure vide, ou plus d'objets que l'exercice n'en accepte —
    // WIMS n'envoie alors rien non plus.
    if (etat !== null) emit('update:reply', props.reply, etat)
  } catch (e) {
    console.error('lecture de la figure GeoGebra', e)
  }
}

async function build() {
  if (!import.meta.client || !host.value || !props.config) return
  try {
    const api = await mountGeogebra(host.value, props.config)
    if (!api || !props.reply) return
    const relire = () => report(api)
    // Les trois écoutes que GeoGebra propose : un objet ajouté, retiré, ou
    // déplacé. Un exercice où l'élève construit (`customToolBar`) passe par la
    // première, un exercice où il déplace un point libre par la dernière.
    const ecoutable = api as {
      registerUpdateListener?: (fn: () => void) => void
      registerAddListener?: (fn: () => void) => void
      registerRemoveListener?: (fn: () => void) => void
    }
    ecoutable.registerUpdateListener?.(relire)
    ecoutable.registerAddListener?.(relire)
    ecoutable.registerRemoveListener?.(relire)
    relire()
  } catch (e) {
    console.error('GeoGebra applet init failed', e)
  }
}

onMounted(build)
// Nouvel exercice, nouvelle figure : on reconstruit.
watch(() => props.config, build)
</script>
