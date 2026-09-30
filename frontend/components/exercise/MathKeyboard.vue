<template>
  <!-- Fermé, il ne reste qu'un bouton d'appel : sur ordinateur c'est la seule
       façon d'ouvrir la planche, et après une fermeture c'est le moyen de la
       rappeler. Il n'apparaît que lorsqu'un champ a le focus. -->
  <!-- Flottant, en bas à droite de l'écran : il ne prend plus de place dans
       l'énoncé, et reste à portée de pouce sur tablette. `mousedown.prevent`
       garde le focus au champ, que la planche alimentera. -->
  <Transition name="pax-mk-fab">
    <button
      v-if="!ouvert && cible"
      type="button"
      class="pax-mk-open"
      :title="$t('keyboard.open')"
      :aria-label="$t('keyboard.open')"
      @mousedown.prevent
      @click="$emit('open')">
      <span class="pax-mk-open-glyphe" aria-hidden="true">π</span>
    </button>
  </Transition>

  <!-- Ancrée en bas de l'écran, comme le clavier d'une tablette. Téléportée
       dans `body` : un ancêtre transformé ferait sinon de `position: fixed`
       un positionnement relatif à lui. -->
  <Teleport to="body">
  <Transition name="pax-mk-panneau">
  <div
    v-if="ouvert"
    ref="panneau"
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
    <button
      type="button" class="pax-mk-close" :title="$t('keyboard.close')" :aria-label="$t('keyboard.close')"
      @mousedown.prevent @click="$emit('close')">
      ✕
    </button>
  </div>
  </Transition>
  </Teleport>
</template>

<script setup lang="ts">
import { nextTick, onBeforeUnmount, onMounted, ref, watch } from 'vue'
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

// ── Place réservée ────────────────────────────────────────────────────────────
// Le panneau recouvre le bas de la page : on réserve sa hauteur en marge basse
// du `body` (la fin de l'énoncé reste atteignable), et le champ actif défile
// au-dessus de lui s'il se retrouvait dessous.
const panneau = ref<HTMLElement | null>(null)
let observateur: ResizeObserver | null = null

function reserve(hauteur: number) {
  const racine = document.documentElement
  if (hauteur > 0) {
    racine.style.setProperty('--pax-mk-hauteur', `${hauteur}px`)
    document.body.classList.add('pax-mk-actif')
  } else {
    racine.style.removeProperty('--pax-mk-hauteur')
    document.body.classList.remove('pax-mk-actif')
  }
}

function degageChamp() {
  const champ = props.cible
  if (!champ || !panneau.value) return
  const bas = champ.getBoundingClientRect().bottom
  const limite = window.innerHeight - panneau.value.offsetHeight - 16
  if (bas > limite) window.scrollBy({ top: bas - limite, behavior: 'smooth' })
}

watch(() => props.ouvert, async (ouvert) => {
  observateur?.disconnect()
  observateur = null
  if (!ouvert) { reserve(0); return }
  await nextTick()
  if (!panneau.value) return
  observateur = new ResizeObserver(() => reserve(panneau.value?.offsetHeight ?? 0))
  observateur.observe(panneau.value)
  reserve(panneau.value.offsetHeight)
  degageChamp()
}, { immediate: true })

watch(() => props.cible, () => { if (props.ouvert) nextTick(degageChamp) })

onBeforeUnmount(() => { observateur?.disconnect(); reserve(0) })

// `mousedown.prevent` sur chaque touche empêche le champ de perdre le focus :
// sans cela, le clic vole le curseur et l'insertion partirait de nulle part.
function frapper(t: ToucheMath) {
  if (props.cible) insere(props.cible, t)
}
</script>

<style scoped>
/* Le panneau, ancré en bas de l'écran comme un clavier de tablette : toute
   la largeur sur un téléphone, centré et borné sur un grand écran. Il ne se
   substitue pas au clavier de l'appareil : il ajoute ce que celui-ci enterre
   dans ses sous-menus. */
.pax-mk {
  position: fixed;
  left: 50%;
  bottom: 0;
  z-index: 50;
  width: min(100%, 56rem);
  transform: translateX(-50%);
  padding: 0.75rem 2.75rem calc(0.75rem + env(safe-area-inset-bottom, 0px)) 0.75rem;
  border: 1px solid var(--color-border);
  border-bottom: 0;
  border-radius: 1rem 1rem 0 0;
  background: var(--color-surface);
  box-shadow: 0 -8px 24px rgb(0 0 0 / 0.12);
}

/* Il glisse depuis le bas de l'écran. */
.pax-mk-panneau-enter-active,
.pax-mk-panneau-leave-active { transition: transform 0.2s ease, opacity 0.2s ease; }
.pax-mk-panneau-enter-from,
.pax-mk-panneau-leave-to { transform: translate(-50%, 100%); opacity: 0; }

@media (prefers-reduced-motion: reduce) {
  .pax-mk-panneau-enter-active,
  .pax-mk-panneau-leave-active { transition: none; }
}

.pax-mk-grid {
  display: flex;
  flex-wrap: wrap;
  justify-content: center;
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
  top: 0.6rem;
  right: 0.75rem;
  padding: 0.15rem 0.35rem;
  border: 0;
  background: transparent;
  color: var(--color-text-muted);
  cursor: pointer;
  line-height: 1;
}

.pax-mk-close:hover { color: var(--color-text); }

/* Le bouton d'appel : rond, flottant, au-dessus du contenu. */
.pax-mk-open {
  position: fixed;
  right: calc(1.25rem + env(safe-area-inset-right, 0px));
  bottom: calc(1.25rem + env(safe-area-inset-bottom, 0px));
  z-index: 40;
  width: 3.25rem;
  height: 3.25rem;
  display: flex;
  align-items: center;
  justify-content: center;
  border: 0;
  border-radius: 9999px;
  background: var(--color-primary);
  color: #fff;
  box-shadow:
    0 6px 16px color-mix(in srgb, var(--color-primary) 35%, transparent),
    0 2px 4px rgb(0 0 0 / 0.15);
  cursor: pointer;
  transition: transform 0.15s ease, box-shadow 0.15s ease;
}

.pax-mk-open:hover {
  transform: translateY(-2px);
  box-shadow:
    0 10px 22px color-mix(in srgb, var(--color-primary) 40%, transparent),
    0 3px 6px rgb(0 0 0 / 0.18);
}

.pax-mk-open:active { transform: translateY(0) scale(0.96); }

.pax-mk-open:focus-visible {
  outline: 3px solid color-mix(in srgb, var(--color-primary) 45%, transparent);
  outline-offset: 3px;
}

.pax-mk-open-glyphe {
  font-family: 'KaTeX_Main', 'Times New Roman', serif;
  font-style: italic;
  font-size: 1.6rem;
  line-height: 1;
  transform: translateY(-1px);
}

/* Apparition : un léger fondu, le bouton monte de quelques pixels. */
.pax-mk-fab-enter-active,
.pax-mk-fab-leave-active { transition: opacity 0.15s ease, transform 0.15s ease; }
.pax-mk-fab-enter-from,
.pax-mk-fab-leave-to { opacity: 0; transform: translateY(8px) scale(0.9); }

@media (prefers-reduced-motion: reduce) {
  .pax-mk-open,
  .pax-mk-fab-enter-active,
  .pax-mk-fab-leave-active { transition: none; }
}
</style>

<style>
/* Hors du `scoped` : la place que le panneau réserve en bas de la page. */
body.pax-mk-actif { padding-bottom: var(--pax-mk-hauteur, 0px); }
</style>
