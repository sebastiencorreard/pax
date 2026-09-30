<template>
  <!-- Fermé — c'est l'état par défaut, au doigt comme à la souris —, il ne
       reste qu'une pastille flottante en bas à droite, visible dès qu'un champ
       a le focus. `mousedown.prevent` garde le focus au champ, que la planche
       alimentera. -->
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
        <div class="pax-mk-grid" :class="{ 'is-abc': onglet === 'abc' }">
          <template v-for="(rangee, r) in planche" :key="onglet + r">
            <button
              v-for="(t, i) in rangee"
              :key="i"
              type="button"
              class="pax-mk-key"
              :class="['is-' + (t.famille || 'symbole'), { 'is-actif': t.action === 'maj' && maj }]"
              :style="t.largeur && t.largeur > 1 ? { gridColumn: `span ${t.largeur}` } : undefined"
              :aria-label="aria(t)"
              @mousedown.prevent
              @click="frapper(t)">
              <span v-if="t.latex && etiquettes[t.latex]" v-html="etiquettes[t.latex]" />
              <span v-else>{{ t.libelle ?? t.latex ?? t.texte }}</span>
            </button>
          </template>
        </div>

        <!-- La rangée d'actions, la même d'un onglet à l'autre (MathLive). -->
        <div class="pax-mk-actions">
          <div class="pax-mk-onglets" role="tablist" :aria-label="$t('keyboard.tabs')">
            <button
              v-for="o in ONGLETS"
              :key="o.id"
              type="button"
              role="tab"
              class="pax-mk-onglet"
              :class="{ 'is-actif': onglet === o.id }"
              :aria-selected="onglet === o.id"
              @mousedown.prevent
              @click="onglet = o.id">
              {{ o.libelle }}
            </button>
          </div>
          <button
            v-for="(t, i) in ACTIONS"
            :key="'a' + i"
            type="button"
            class="pax-mk-key is-action"
            :aria-label="aria(t)"
            @mousedown.prevent
            @click="frapper(t)">
            {{ t.libelle }}
          </button>
          <button
            type="button"
            class="pax-mk-key is-action pax-mk-close"
            :title="$t('keyboard.close')"
            :aria-label="$t('keyboard.close')"
            @mousedown.prevent
            @click="$emit('close')">
            <span aria-hidden="true">⌄</span>
          </button>
        </div>
      </div>
    </Transition>
  </Teleport>
</template>

<script setup lang="ts">
import { computed, nextTick, onBeforeUnmount, ref, watch } from 'vue'
import {
  ACTIONS, ONGLETS, insere, rangees,
  type OngletClavier, type ToucheMath,
} from '~/composables/useMathKeyboard'
import { useKatex } from '~/composables/useKatex'

const props = defineProps<{
  /** Le champ que les touches alimentent. */
  cible: HTMLInputElement | HTMLTextAreaElement | null
  ouvert: boolean
  /** Langue de l'exercice : séparateur décimal, disposition des lettres. */
  lang?: string
}>()

defineEmits<{ close: [], open: [] }>()

const { t: tr } = useI18n()
const { renderMath } = useKatex()

const onglet = ref<OngletClavier>('123')
const maj = ref(false)
const planche = computed(() => rangees(onglet.value, props.lang || 'fr', maj.value))

function aria(t: ToucheMath): string {
  if (t.aria?.startsWith('keyboard.')) return tr(t.aria)
  return t.aria ?? t.texte ?? t.libelle ?? ''
}

// Les étiquettes LaTeX, rendues à la demande et gardées : `renderMath` est
// asynchrone (KaTeX se charge à la demande), le template ne peut l'attendre.
const etiquettes = ref<Record<string, string>>({})
watch(planche, async (p) => {
  const manquantes = [...new Set(p.flat().map(t => t.latex).filter(
    (l): l is string => !!l && !(l in etiquettes.value)))]
  const rendus = await Promise.all(manquantes.map(async (l) => {
    try { return [l, await renderMath('\\(' + l + '\\)')] as const }
    catch { return [l, l] as const }
  }))
  etiquettes.value = { ...etiquettes.value, ...Object.fromEntries(rendus) }
}, { immediate: true })

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
  if (t.action === 'maj') { maj.value = !maj.value; return }
  if (!props.cible) return
  insere(props.cible, t)
  // Une majuscule, comme sur un téléphone : la touche retombe après usage.
  if (maj.value && t.texte) maj.value = false
}
</script>

<style scoped>
/* Le panneau, ancré en bas de l'écran comme un clavier de tablette : toute
   la largeur sur un téléphone, centré et borné sur un grand écran. */
.pax-mk {
  position: fixed;
  left: 50%;
  bottom: 0;
  z-index: 50;
  width: min(100%, 44rem);
  transform: translateX(-50%);
  padding: 0.6rem 0.6rem calc(0.6rem + env(safe-area-inset-bottom, 0px));
  border: 1px solid var(--color-border);
  border-bottom: 0;
  border-radius: 1rem 1rem 0 0;
  background: color-mix(in srgb, var(--color-bg) 70%, var(--color-surface));
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

/* Une grille de dix colonnes, quatre rangées de haut quel que soit l'onglet :
   la planche ne saute pas quand on en change. */
.pax-mk-grid {
  display: grid;
  grid-template-columns: repeat(10, minmax(0, 1fr));
  grid-auto-rows: 2.6rem;
  gap: 0.3rem;
  min-height: calc(4 * 2.6rem + 3 * 0.3rem);
  align-content: start;
}

.pax-mk-key {
  display: flex;
  align-items: center;
  justify-content: center;
  min-width: 0;
  padding: 0 0.2rem;
  border: 1px solid var(--color-border);
  border-radius: 0.45rem;
  background: var(--color-surface);
  color: var(--color-text);
  font-size: 1rem;
  line-height: 1;
  white-space: nowrap;
  overflow: hidden;
  cursor: pointer;
  box-shadow: 0 1px 0 rgb(0 0 0 / 0.08);
  transition: background-color 0.1s, border-color 0.1s;
}

.pax-mk-key:hover { border-color: var(--color-primary); }
.pax-mk-key:active { background: color-mix(in srgb, var(--color-primary) 18%, var(--color-surface)); }

/* Les familles se distinguent au ton : chiffres en plein, fonctions et
   opérations en couleur d'accent, symboles et actions en retrait. */
.pax-mk-key.is-chiffre { font-weight: 600; }
.pax-mk-key.is-fonction { color: var(--color-primary); font-size: 0.9rem; }
.pax-mk-key.is-operation { color: var(--color-primary); }
.pax-mk-key.is-variable { font-style: italic; }
.pax-mk-grid.is-abc .pax-mk-key.is-variable { font-style: normal; }
.pax-mk-key.is-action {
  background: color-mix(in srgb, var(--color-text) 8%, var(--color-surface));
  color: var(--color-text-muted);
}
.pax-mk-key.is-actif {
  background: var(--color-primary);
  border-color: var(--color-primary);
  color: #fff;
}

/* La rangée d'actions : les onglets à gauche, les commandes à droite. */
.pax-mk-actions {
  display: grid;
  grid-template-columns: 1fr repeat(4, 2.9rem);
  grid-auto-rows: 2.6rem;
  gap: 0.3rem;
  margin-top: 0.3rem;
}

.pax-mk-onglets {
  display: flex;
  gap: 0.3rem;
  min-width: 0;
}

.pax-mk-onglet {
  flex: 1 1 0;
  min-width: 0;
  border: 1px solid transparent;
  border-radius: 0.45rem;
  background: transparent;
  color: var(--color-text-muted);
  font-size: 0.85rem;
  font-weight: 600;
  cursor: pointer;
}

.pax-mk-onglet:hover { color: var(--color-text); }
.pax-mk-onglet.is-actif {
  background: var(--color-surface);
  border-color: var(--color-border);
  color: var(--color-primary);
}

.pax-mk-close span { font-size: 1.3rem; transform: translateY(-3px); }

/* La pastille d'appel : ronde, flottante, au-dessus du contenu. */
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

/* Petit écran : des touches plus basses, pour que la planche ne mange pas le
   tiers de l'écran — 38 px restent une cible tactile correcte. */
@media (max-width: 480px) {
  .pax-mk { padding: 0.4rem 0.3rem calc(0.4rem + env(safe-area-inset-bottom, 0px)); border-radius: 0.75rem 0.75rem 0 0; }
  .pax-mk-grid { grid-auto-rows: 2.35rem; gap: 0.2rem; min-height: calc(4 * 2.35rem + 3 * 0.2rem); }
  .pax-mk-actions { grid-template-columns: 1fr repeat(4, 2.4rem); grid-auto-rows: 2.35rem; gap: 0.2rem; margin-top: 0.2rem; }
  .pax-mk-key { font-size: 0.9rem; border-radius: 0.35rem; }
  .pax-mk-key.is-fonction { font-size: 0.75rem; }
  .pax-mk-onglet { font-size: 0.75rem; }
}
</style>

<style>
/* Hors du `scoped` : la place que le panneau réserve en bas de la page. */
body.pax-mk-actif { padding-bottom: var(--pax-mk-hauteur, 0px); }
</style>
