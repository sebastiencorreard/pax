<template>
  <!-- Fermé, il ne reste qu'un bouton d'appel : sur ordinateur c'est la seule
       façon d'ouvrir la planche, et après une fermeture c'est le moyen de la
       rappeler. Il n'apparaît que lorsqu'un champ a le focus. -->
  <button
    v-if="!ouvert && cible"
    type="button"
    class="pax-mk-open"
    :title="$t('keyboard.open')"
    @mousedown.prevent
    @click="$emit('open')">
    π
  </button>

  <div
    v-else-if="ouvert"
    class="pax-mk"
    role="group"
    :aria-label="$t('keyboard.aria')">

    <div class="pax-mk-grid">
      <button
        v-for="(t, i) in touches"
        :key="i"
        type="button"
        class="pax-mk-key"
        :class="'is-' + t.groupe"
        :title="t.texte"
        :aria-label="t.texte"
        @mousedown.prevent
        @click="frapper(t)"
        v-html="etiquettes[i] || t.texte" />
    </div>
    <button type="button" class="pax-mk-close" :title="$t('keyboard.close')" @click="$emit('close')">
      ✕
    </button>
  </div>
</template>

<script setup lang="ts">
import { onMounted, ref } from 'vue'
import { CLAVIER_DEFAUT, insere, type ToucheMath } from '~/composables/useMathKeyboard'
import { useKatex } from '~/composables/useKatex'

const props = defineProps<{
  /** Le champ que les touches alimentent. */
  cible: HTMLInputElement | HTMLTextAreaElement | null
  ouvert: boolean
}>()

defineEmits<{ close: [], open: [] }>()

const { renderMath } = useKatex()
const touches = CLAVIER_DEFAUT

// Les étiquettes sont fixes : on les rend **une fois**, au montage. `renderMath`
// est asynchrone (KaTeX se charge à la demande), donc les calculer dans le
// template rendrait une promesse au lieu du HTML.
const etiquettes = ref<string[]>([])
onMounted(async () => {
  etiquettes.value = await Promise.all(
    touches.map(async t => {
      try {
        return await renderMath('\\(' + t.latex + '\\)')
      } catch {
        return t.texte
      }
    }),
  )
})

// `mousedown.prevent` sur chaque touche empêche le champ de perdre le focus :
// sans cela, le clic vole le curseur et l'insertion partirait de nulle part.
function frapper(t: ToucheMath) {
  if (props.cible) insere(props.cible, t)
}
</script>

<style scoped>
/* Une planche discrète, sous le champ actif. Elle ne se substitue pas au
   clavier de l'appareil : elle ajoute ce qu'il enterre dans ses sous-menus. */
.pax-mk {
  position: relative;
  margin-top: 0.5rem;
  padding: 0.5rem 2rem 0.5rem 0.5rem;
  border: 1px solid var(--color-border);
  border-radius: 0.75rem;
  background: var(--color-surface);
}

.pax-mk-grid {
  display: flex;
  flex-wrap: wrap;
  gap: 0.35rem;
}

.pax-mk-key {
  min-width: 2.75rem;
  min-height: 2.5rem; /* cible tactile confortable */
  padding: 0.25rem 0.5rem;
  border: 1px solid var(--color-border);
  border-radius: 0.5rem;
  background: var(--color-bg);
  color: var(--color-text);
  font-size: 0.95rem;
  line-height: 1;
  cursor: pointer;
  transition: background-color 0.12s, border-color 0.12s;
}

.pax-mk-key:hover { border-color: var(--color-primary); }
.pax-mk-key:active { background: color-mix(in srgb, var(--color-primary) 18%, transparent); }

/* Les trois familles se distinguent au ton, pas à la couleur pleine : la
   planche doit rester lisible sans devenir un damier. */
.pax-mk-key.is-fonction { color: var(--color-primary); }
.pax-mk-key.is-symbole { color: var(--color-text-muted); }

.pax-mk-close {
  position: absolute;
  top: 0.35rem;
  right: 0.4rem;
  padding: 0.15rem 0.35rem;
  border: 0;
  background: transparent;
  color: var(--color-text-muted);
  cursor: pointer;
  line-height: 1;
}

.pax-mk-close:hover { color: var(--color-text); }

/* Le bouton d'appel : discret, mais assez large pour le doigt. */
.pax-mk-open {
  margin-top: 0.5rem;
  min-width: 2.5rem;
  min-height: 2.25rem;
  border: 1px solid var(--color-border);
  border-radius: 0.5rem;
  background: var(--color-surface);
  color: var(--color-text-muted);
  font-size: 1rem;
  cursor: pointer;
}

.pax-mk-open:hover { border-color: var(--color-primary); color: var(--color-text); }
</style>
