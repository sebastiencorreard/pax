<template>
  <div class="pax-reaction">
    <div class="pax-reaction-derniers">
      <div class="pax-reaction-titre">{{ $t('reaction.derniers') }}</div>
      <div v-for="(mesure, i) in troisDerniers" :key="i" class="pax-reaction-mesure">
        {{ mesure }} {{ $t('reaction.ms') }}
      </div>
    </div>

    <p class="pax-reaction-consigne" role="status" aria-live="polite">{{ consigne }}</p>

    <div class="pax-reaction-boutons">
      <button
        v-if="phase !== 'fini'"
        type="button"
        class="pax-reaction-bouton"
        :class="phase === 'attente' ? 'is-stop' : 'is-go'"
        :disabled="submitted"
        @click="frapper">
        {{ phase === 'attente' ? $t('reaction.stop') : $t('reaction.go') }}
      </button>
    </div>

    <p class="pax-reaction-avancement">
      {{ $t('reaction.avancement', { faits: temps.length, total: config.tests }) }}
    </p>

    <table v-if="temps.length" class="pax-reaction-table">
      <caption>{{ $t('reaction.tableau') }}</caption>
      <tbody>
        <tr v-for="(ligne, i) in lignes" :key="i">
          <td v-for="(mesure, j) in ligne" :key="j">{{ mesure }}</td>
        </tr>
      </tbody>
    </table>
  </div>
</template>

<script setup lang="ts">
// Le chronomètre de `type=reaction` (module `oefstatistiques`).
//
// L'élève appuie sur GO, attend un délai qu'il ne peut pas anticiper, puis
// frappe STOP dès que la consigne apparaît. L'écart mesuré est son temps de
// réaction ; il recommence `tests` fois — quarante dans `histocap` — et la
// réponse envoyée est la liste de ces temps, en millisecondes, séparés par des
// virgules. C'est cette liste que les étapes suivantes de l'exercice
// dépouillent : moyenne, quartiles, histogramme.
//
// Le `.input` du module fait la même chose en JavaScript inline. Un `<script>`
// injecté par le `v-html` du front ne s'exécute pas : d'où ce composant, comme
// pour l'éditeur de code et les applets.
import { computed, onBeforeUnmount, ref } from 'vue'
import { useI18n } from 'vue-i18n'

const props = defineProps<{
  config: {
    reply: string
    /** Nombre de mesures à réaliser. */
    tests: number
    /** Délai fixe avant le tirage, en millisecondes. */
    delai: number
    /** Attente aléatoire maximale ajoutée au délai, en **secondes**. */
    attenteMax: number
    /** Au delà, l'essai est rejeté : l'élève n'était pas attentif. */
    reactionMax: number
    colonnes: number
  }
  submitted?: boolean
}>()

const emit = defineEmits<{ 'update:reply': [nom: string, valeur: string] }>()
const { t } = useI18n()

type Phase = 'pret' | 'arme' | 'attente' | 'fini'
const phase = ref<Phase>('pret')
const temps = ref<number[]>([])
const consigne = ref(t('reaction.appuyezGo'))

let minuterie: ReturnType<typeof setTimeout> | null = null
let departMesure = 0

onBeforeUnmount(() => {
  if (minuterie) clearTimeout(minuterie)
})

const troisDerniers = computed(() => temps.value.slice(-3))

const lignes = computed(() => {
  const n = Math.max(1, props.config.colonnes)
  const out: number[][] = []
  for (let i = 0; i < temps.value.length; i += n) {
    out.push(temps.value.slice(i, i + n))
  }
  return out
})

function frapper() {
  if (phase.value === 'attente') return arreter()
  if (phase.value === 'pret') return demarrer()
  // Phase « armé » : la consigne n'est pas encore apparue. Frapper maintenant,
  // c'est anticiper — le `.input` d'origine invalide l'essai plutôt que de le
  // compter, et il a raison : un temps mesuré avant le signal ne mesure rien.
  if (minuterie) clearTimeout(minuterie)
  minuterie = null
  phase.value = 'pret'
  consigne.value = t('reaction.tropTot')
}

function demarrer() {
  phase.value = 'arme'
  consigne.value = t('reaction.preparez')
  // Le tirage porte sur des **secondes entières**, comme dans le `.input` du
  // module : `Math.floor(Math.random() * attentemaxapresdepart)`. Sans cette
  // part d'aléa, l'élève apprendrait le rythme et mesurerait son anticipation
  // plutôt que sa réaction.
  const alea = Math.floor(Math.random() * props.config.attenteMax)
  minuterie = setTimeout(() => {
    minuterie = null
    phase.value = 'attente'
    departMesure = performance.now()
    consigne.value = t('reaction.appuyezStop')
  }, props.config.delai + 1000 * alea)
}

function arreter() {
  const mesure = Math.round(performance.now() - departMesure)
  if (mesure > props.config.reactionMax) {
    phase.value = 'pret'
    consigne.value = t('reaction.tropLent', { max: props.config.reactionMax })
    return
  }
  temps.value.push(mesure)
  if (temps.value.length >= props.config.tests) {
    phase.value = 'fini'
    consigne.value = t('reaction.termine', { total: props.config.tests })
  } else {
    phase.value = 'pret'
    consigne.value = t('reaction.appuyezGo')
  }
  // La réponse est remontée à **chaque** mesure, et non à la dernière. Une
  // série interrompue reste ainsi exploitable, et l'élève qui envoie trop tôt
  // voit sa note porter sur ce qu'il a réellement fait.
  emit('update:reply', props.config.reply, temps.value.join(','))
}
</script>

<style scoped>
.pax-reaction {
  display: flex;
  flex-direction: column;
  align-items: center;
  gap: 0.6rem;
  margin: 0.75rem 0;
}

.pax-reaction-derniers {
  min-height: 4.2rem;
  text-align: center;
  color: var(--color-text-muted);
  font-size: 0.9rem;
}

.pax-reaction-titre { font-weight: 600; margin-bottom: 0.2rem; }
.pax-reaction-mesure { font-variant-numeric: tabular-nums; }

.pax-reaction-consigne {
  margin: 0;
  font-weight: 700;
  text-align: center;
  min-height: 1.4rem;
}

/* Une cible large : on mesure un temps de réaction, pas une précision de
   pointage. Un bouton étroit ferait payer la visée dans la mesure. */
.pax-reaction-bouton {
  min-width: 9rem;
  min-height: 3.4rem;
  padding: 0.6rem 1.6rem;
  border: 0;
  border-radius: 0.6rem;
  color: #fff;
  font-size: 1.25rem;
  font-weight: 700;
  letter-spacing: 0.04em;
  cursor: pointer;
  transition: background-color 0.12s, transform 0.06s;
}

.pax-reaction-bouton:disabled { opacity: 0.5; cursor: default; }
.pax-reaction-bouton:active:not(:disabled) { transform: scale(0.98); }
.pax-reaction-bouton.is-go { background: #15803d; }
.pax-reaction-bouton.is-go:hover:not(:disabled) { background: #166534; }
.pax-reaction-bouton.is-stop { background: #b91c1c; }
.pax-reaction-bouton.is-stop:hover:not(:disabled) { background: #991b1b; }

.pax-reaction-avancement {
  margin: 0;
  color: var(--color-text-muted);
  font-size: 0.85rem;
  font-variant-numeric: tabular-nums;
}

.pax-reaction-table {
  border-collapse: collapse;
  font-size: 0.85rem;
  font-variant-numeric: tabular-nums;
}

.pax-reaction-table caption {
  font-weight: 600;
  padding-bottom: 0.3rem;
  color: var(--color-text-muted);
}

.pax-reaction-table td {
  border: 1px solid var(--color-border);
  padding: 0.15rem 0.5rem;
  text-align: right;
}
</style>
