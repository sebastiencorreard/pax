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
    class="cz"
    :class="{ 'cz--over': isOver, 'cz--submitted': submitted }"
    role="button"
    tabindex="0"
    :aria-disabled="submitted || undefined"
    :aria-label="nomAccessible"
    @dragover.prevent="isOver = true"
    @dragenter.prevent="isOver = true"
    @dragleave="isOver = false"
    @drop.prevent="onDrop"
    @click="onZoneClick"
    @keydown.enter.stop.prevent="onZoneClick"
    @keydown.space.stop.prevent="onZoneClick">
    <template v-for="(frag, i) in placed" :key="i">
      <span v-if="i > 0 && linkword" class="cz-link">{{ linkword }}</span>
      <!-- Le `×` retire, le reste du fragment dépose comme le fond de la zone.
           Confondre les deux se paie tout de suite : la zone se remplissant,
           sa partie vide se réduit, et un clic destiné à déposer retirait le
           fragment qu'il touchait. Vu au navigateur sur `geobase/phradroit`. -->
      <span
        class="cz-frag"
        :class="fragClass(i)"
        @click.stop="onZoneClick">
        <span v-html="html(frag)"/>
        <button
          v-if="!submitted"
          type="button"
          class="cz-x"
          :title="t('exercise.composeRemove')"
          :aria-label="t('exercise.composeRemove')"
          @click.stop="remove(i)">×</button>
      </span>
    </template>
    <span v-if="!placed.length" class="cz-empty">{{ t('exercise.composeDrop') }}</span>
  </span>
</template>

<script setup lang="ts">
const props = defineProps<{
  name: string
  value: string
  linkword: string
  choicesHtml: Array<{ raw: string; html: string }>
  pending: string | null
  submitted: boolean
  state?: '' | 'correct' | 'incorrect'
}>()

const emit = defineEmits<{ update: [name: string, value: string] }>()

const { t } = useI18n()
const { renderMath } = useKatex()
const isOver = ref(false)

// La réponse est la suite des fragments jointe par une virgule — c'est ce que
// `check_compose` relit (« la virgule vaut espace », `!items2words`). Un
// fragment qui contient lui-même une virgule la porte échappée (`&#44;`),
// comme le `replygood` de `oefencad/inequation` : on ne la décode donc pas
// ici, sans quoi elle se confondrait avec le séparateur.
const placed = computed(() => (props.value ? props.value.split(',') : []))

// La zone se lit comme une phrase en cours : sa longueur et ce qu'elle porte.
// Vide, elle n'aurait annoncé que son texte d'invite.
const nomAccessible = computed(() =>
  placed.value.length
    ? t('exercise.composeZoneFilled', {
        n: placed.value.length,
        v: placed.value.map(texteBrut).join(', '),
      })
    : t('exercise.composeDrop'),
)

function texteBrut(frag: string): string {
  const alts = [...frag.matchAll(/<img[^>]*\balt="([^"]*)"/gi)]
    .map(m => m[1]).filter(Boolean)
  if (alts.length) return alts.join(' ')
  return frag.replace(/<[^>]+>/g, ' ').replace(/\s+/g, ' ').trim() || frag
}

const rendus = ref<Record<string, string>>({})
function html(frag: string): string {
  const connu = props.choicesHtml.find(c => c.raw === frag)
  if (connu) return connu.html
  if (rendus.value[frag] === undefined) {
    rendus.value[frag] = frag
    renderMath(frag).then(h => { rendus.value = { ...rendus.value, [frag]: h } })
  }
  return rendus.value[frag]
}

function pousser(raw: string) {
  if (props.submitted || !raw) return
  emit('update', props.name, [...placed.value, raw].join(','))
}

function remove(i: number) {
  if (props.submitted) return
  const suite = placed.value.slice()
  suite.splice(i, 1)
  emit('update', props.name, suite.join(','))
}

function onDrop(e: DragEvent) {
  isOver.value = false
  const raw = e.dataTransfer?.getData('text/plain')
  if (raw) pousser(raw)
}

// Un clic sur la zone dépose la carte en attente : c'est la voie sans
// glisser-déposer, celle qui marche au doigt comme à la souris. `CfSlot` offre
// déjà ce double mode, on le reprend à l'identique.
function onZoneClick() {
  if (props.pending) pousser(props.pending)
}

// Après correction, seul le verdict d'ensemble est connu — `check_compose`
// juge la suite entière, pas fragment par fragment. On colore donc toute la
// zone, et non chaque carte : prétendre situer l'erreur serait inventer.
function fragClass(_i: number) {
  if (!props.submitted) return ''
  return props.state === 'correct' ? 'cz-frag--ok'
    : props.state === 'incorrect' ? 'cz-frag--ko' : ''
}
</script>

<style scoped>
.cz {
  display: inline-flex;
  flex-wrap: wrap;
  align-items: center;
  gap: 0.25rem;
  min-width: 12rem;
  min-height: 2.5rem;
  padding: 0.35rem 0.5rem;
  border: 2px dashed var(--cz-border, #93c5fd);
  border-radius: 0.5rem;
  vertical-align: middle;
}
.cz--over { background: rgba(59, 130, 246, 0.12); border-style: solid; }
/* Le parcours au clavier doit se voir : sans cet anneau, la zone prend le
   focus sans rien montrer, ce qui revient à ne pas être atteignable. */
.cz:focus-visible { outline: 2px solid #2563eb; outline-offset: 2px; }
.cz--submitted { border-style: solid; }
.cz-empty { color: #6b7280; font-style: italic; font-size: 0.9em; }
.cz-frag {
  display: inline-flex;
  align-items: center;
  gap: 0.2rem;
  padding: 0.2rem 0.5rem;
  border: 1px solid #60a5fa;
  border-radius: 0.375rem;
  background: rgba(59, 130, 246, 0.1);
  cursor: pointer;
}
.cz--submitted .cz-frag { cursor: default; }
.cz-frag--ok { border-color: #16a34a; background: rgba(22, 163, 74, 0.12); }
.cz-frag--ko { border-color: #dc2626; background: rgba(220, 38, 38, 0.12); }
.cz-x {
  color: #6b7280;
  font-weight: 700;
  line-height: 1;
  padding: 0 0.15rem;
  background: none;
  border: 0;
  cursor: pointer;
}
.cz-x:hover { color: #dc2626; }
.cz-link { color: #6b7280; }
@media (prefers-color-scheme: dark) {
  .cz { --cz-border: #3b82f6; }
  .cz-empty, .cz-x, .cz-link { color: #9ca3af; }
}
</style>
