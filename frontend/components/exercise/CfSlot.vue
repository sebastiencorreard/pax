<template>
    <!-- `role`/`tabindex` **statiques**, et l'état soumis dit par
         `aria-disabled`. Ce n'est pas un détail de style : liés à une
         expression qui vaut `undefined`, Vue les *retire* au patch, et
         retirer `tabindex` d'un élément focalisé le défocalise. Au clavier,
         chaque dépôt renvoyait donc au début de la tabulation. Mesuré :
         `document.activeElement` passait à `BODY`, et le seul passage en
         statique l'a réglé — une veilleuse qui rendait le focus après coup
         s'est révélée inutile, et a été retirée. -->
  <!-- `.stop` autant que `.prevent` sur les touches : `BaseExerciseStatement`
       pose un `@keydown.enter` qui **soumet l'exercice**, et n'excepte que les
       `<textarea>`. Sans arrêter la remontée, appuyer sur Entrée pour poser une
       carte envoyait la copie. Vu au navigateur, pas déduit. -->
  <span
    class="cf-slot"
    :class="{
      'cf-slot--over': isOver,
      'cf-slot--filled': !!value,
      'cf-slot--pending': isPending,
      'cf-slot--correct': state === 'correct',
      'cf-slot--incorrect': state === 'incorrect',
    }"
    role="button"
    tabindex="0"
    :aria-disabled="submitted || undefined"
    :aria-label="nomAccessible"
    @dragover.prevent="isOver = true"
    @dragenter.prevent="isOver = true"
    @dragleave="isOver = false"
    @drop.prevent="onDrop"
    @click="onClick"
    @keydown.enter.stop.prevent="onClick"
    @keydown.space.stop.prevent="onClick"
  >
    <span v-if="valueHtml" v-html="valueHtml" class="cf-slot-content"></span>
    <span v-else class="cf-slot-placeholder">···</span>
  </span>
</template>

<script setup lang="ts">
const props = defineProps<{
  name: string
  value: string
  choicesHtml: Array<{ raw: string; html: string }>
  dragging: string | null   // valeur raw de la carte en cours de glisser
  pending: string | null    // valeur raw de la carte sélectionnée par clic
  submitted: boolean
  index?: number            // slot position within a multi-slot group
  state?: '' | 'correct' | 'incorrect'  // post-submit feedback
}>()

const emit = defineEmits<{
  place: [name: string, value: string, index: number]
  clear: [name: string, index: number]
}>()

const { t } = useI18n()
const { renderMath } = useKatex()
const isOver = ref(false)

const valueHtml = computedAsync(async () => {
  if (!props.value) return ''
  const choice = props.choicesHtml.find(c => c.raw === props.value)
  return choice ? choice.html : await renderMath(props.value)
}, '')

// La carte en attente (clic) correspond-elle à ce slot ?
const isPending = computed(() => !props.submitted && !!props.pending)

function onDrop(e: DragEvent) {
  isOver.value = false
  if (props.submitted) return
  const raw = e.dataTransfer?.getData('text/plain')
  if (raw) emit('place', props.name, raw, props.index ?? 0)
}

// Sans nom, un emplacement vide ne s'annonce que par ses trois points. On dit
// donc son rang et son contenu — c'est la seule information dont dispose
// quelqu'un qui ne voit pas la ligne.
const nomAccessible = computed(() => {
  const rang = (props.index ?? 0) + 1
  if (!props.value) return t('exercise.slotEmpty', { n: rang })
  return t('exercise.slotFilled', { n: rang, v: texteBrut(props.value) })
})

function texteBrut(v: string): string {
  const alts = [...v.matchAll(/<img[^>]*\balt="([^"]*)"/gi)].map(m => m[1]).filter(Boolean)
  if (alts.length) return alts.join(' ')
  return v.replace(/<[^>]+>/g, ' ').replace(/\s+/g, ' ').trim() || v
}

function onClick() {
  if (props.submitted) return
  if (props.pending) {
    // Une carte est en attente → on la place ici
    emit('place', props.name, props.pending, props.index ?? 0)
  } else if (props.value) {
    // Clic sur slot rempli → vider
    emit('clear', props.name, props.index ?? 0)
  }
}
</script>

<style>
.cf-slot:focus-visible {
  outline: 2px solid #2563eb;
  outline-offset: 2px;
}
.cf-slot {
  display: inline-flex;
  align-items: center;
  justify-content: center;
  min-width: 3rem;
  min-height: 1.8rem;
  vertical-align: middle;
  margin: 0 0.25rem;
  padding: 0.1rem 0.6rem;
  border: 2px dashed var(--color-border);
  border-radius: 0.375rem;
  cursor: pointer;
  transition: border-color 0.15s, background 0.15s;
  user-select: none;
}
.cf-slot--over {
  border-color: var(--color-primary);
  background: color-mix(in srgb, var(--color-primary) 12%, transparent);
}
.cf-slot--filled {
  border-style: solid;
  border-color: var(--color-primary);
}
.cf-slot--pending {
  border-style: dashed;
  border-color: var(--color-primary);
}
.cf-slot--correct {
  border-style: solid;
  border-color: var(--color-success);
  background: color-mix(in srgb, var(--color-success) 12%, transparent);
}
.cf-slot--incorrect {
  border-style: solid;
  border-color: var(--color-error);
  background: color-mix(in srgb, var(--color-error) 12%, transparent);
}
.cf-slot-placeholder {
  color: var(--color-text-muted);
  font-size: 0.85em;
  letter-spacing: 0.05em;
}
.cf-slot-content {
  pointer-events: none;
}
</style>
