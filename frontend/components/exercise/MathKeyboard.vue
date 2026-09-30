<template>
  <!-- Fermé, il ne reste qu'une pastille flottante en bas à droite, visible
       dès qu'un champ a le focus — c'est l'état par défaut à la souris ; au
       doigt, le clavier s'ouvre d'office. `mousedown.prevent` garde le focus
       au champ, que la planche alimentera. -->
  <Transition name="pax-mk-fab">
    <button
      v-if="!ouvert && cible"
      type="button"
      class="pax-mk-open"
      :title="$t('keyboard.open')"
      :aria-label="$t('keyboard.open')"
      @mousedown.prevent
      @click="$emit('open')">
      <!-- Un clavier : ce que la pastille ouvre. -->
      <svg
        viewBox="0 0 24 24" width="26" height="26" aria-hidden="true" fill="none"
        stroke="currentColor" stroke-width="1.7" stroke-linecap="round" stroke-linejoin="round">
        <rect x="2" y="5.5" width="20" height="13" rx="2.5" />
        <path d="M6 9.5h.01M9.33 9.5h.01M12.67 9.5h.01M16 9.5h.01M18 9.5h.01M6 12.5h.01M9.33 12.5h.01M12.67 12.5h.01M16 12.5h.01M18 12.5h.01" stroke-width="2.2" />
        <path d="M7.5 15.5h9" />
      </svg>
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
        :class="{ 'is-compact': !!compacte }"
        role="group"
        :aria-label="$t('keyboard.aria')"
        @mousedown.prevent>
        <!-- Clavier complet : la barre des onglets, et à droite les outils
             (annuler, refaire, masquer) — comme la barre de MathLive. -->
        <div v-if="!compacte" class="pax-mk-barre">
          <div class="pax-mk-onglets" role="tablist" :aria-label="$t('keyboard.tabs')">
            <!-- Le retour à la planche du champ, s'il en a une. -->
            <button
              v-if="aUneCompacte"
              type="button"
              class="pax-mk-onglet"
              :title="$t('keyboard.compact')"
              :aria-label="$t('keyboard.compact')"
              @mousedown.prevent
              @click="etendu = false">
              <!-- Une calculatrice : le pavé simple du champ. -->
              <svg
                class="pax-mk-calc"
                viewBox="0 0 24 24" width="20" height="20" aria-hidden="true" fill="none"
                stroke="currentColor" stroke-width="1.8" stroke-linecap="round" stroke-linejoin="round">
                <rect x="5" y="2.5" width="14" height="19" rx="2.5" />
                <rect x="8" y="5.5" width="8" height="3.5" rx="0.8" />
                <path d="M8.75 12.5h.01M12 12.5h.01M15.25 12.5h.01M8.75 15.5h.01M12 15.5h.01M15.25 15.5h.01M8.75 18.5h.01M12 18.5h.01M15.25 18.5h.01" stroke-width="2.4" />
              </svg>
            </button>
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
          <div class="pax-mk-outils">
            <button
              v-for="(t, i) in ACTIONS_EDITION"
              :key="'e' + i"
              type="button"
              class="pax-mk-outil"
              :title="aria(t)"
              :aria-label="aria(t)"
              @mousedown.prevent
              @click="frapper(t)">
              {{ t.libelle }}
            </button>
            <button
              type="button"
              class="pax-mk-outil pax-mk-close"
              :title="$t('keyboard.close')"
              :aria-label="$t('keyboard.close')"
              @mousedown.prevent
              @click="$emit('close')">
              <svg
                viewBox="0 0 24 24" width="20" height="20" aria-hidden="true" fill="none"
                stroke="currentColor" stroke-width="1.6" stroke-linecap="round" stroke-linejoin="round">
                <rect x="2.5" y="3" width="19" height="11" rx="2" />
                <path d="M6 6.5h.01M9 6.5h.01M12 6.5h.01M15 6.5h.01M18 6.5h.01M6 10h.01M18 10h.01M9 10h6" />
                <path d="M8.5 17.5 12 21l3.5-3.5" />
              </svg>
            </button>
          </div>
        </div>

        <div
          class="pax-mk-grid"
          :class="{ 'is-abc': !compacte && onglet === 'abc' }"
          :style="{ gridTemplateColumns: colonnes }">
          <template v-for="(rangee, r) in affichees" :key="(compacte ? `c-${profil}` : onglet) + r">
            <template v-for="(brute, i) in rangee" :key="i">
              <span v-if="brute.vide" class="pax-mk-vide" aria-hidden="true" />
              <button
                v-else
                type="button"
                class="pax-mk-key"
                :class="['is-' + (vue(brute).famille || 'symbole'), {
                  'is-actif': brute.action === 'maj' && majActive,
                }]"
                :style="brute.largeur && brute.largeur > 1 ? { gridColumn: `span ${brute.largeur}` } : undefined"
                :aria-label="aria(vue(brute))"
                @mousedown.prevent
                @click="frapper(vue(brute))">
                <!-- « Effacer le champ » (⌫ sous la majuscule) : une poubelle. -->
                <svg
                  v-if="vue(brute).action === 'vider'"
                  viewBox="0 0 24 24" width="20" height="20" aria-hidden="true" fill="none"
                  stroke="currentColor" stroke-width="1.8" stroke-linecap="square" stroke-linejoin="miter">
                  <!-- Bords droits : couvercle, poignée, cuve rectangulaire et trois rainures. -->
                  <path d="M3.5 6.5h17M9 6.5V3.5h6v3" />
                  <rect x="5.5" y="6.5" width="13" height="14" />
                  <path d="M9.5 10v7M12 10v7M14.5 10v7" />
                </svg>
                <span v-else-if="vue(brute).latex && etiquettes[vue(brute).latex!]" v-html="etiquettes[vue(brute).latex!]" />
                <span v-else>{{ vue(brute).libelle ?? vue(brute).latex ?? vue(brute).texte }}</span>
                <!-- La variante sous la majuscule, annoncée en petit (MathLive).
                     Du HTML de KaTeX pour nos propres étiquettes, ou un texte
                     échappé (`indice`) : rien ne vient de l'exercice. -->
                <!-- eslint-disable vue/no-v-html -->
                <span
                  v-if="brute.maj && !brute.discret && !majActive"
                  class="pax-mk-indice"
                  aria-hidden="true"
                  v-html="indice(brute.maj)" />
                <!-- eslint-enable vue/no-v-html -->
              </button>
            </template>
          </template>
        </div>

        <!-- Planche compacte : sa rangée d'actions, « ⋯ » vers le clavier
             complet à côté des commandes. -->
        <div v-if="compacte" class="pax-mk-actions">
          <button
            type="button"
            class="pax-mk-key is-action pax-mk-plus"
            :title="$t('keyboard.more')"
            :aria-label="$t('keyboard.more')"
            @mousedown.prevent
            @click="etendu = true">
            ⋯
          </button>
          <div class="pax-mk-commandes">
            <button
              v-for="(t, i) in ACTIONS"
              :key="'a' + i"
              type="button"
              class="pax-mk-key is-action"
              :title="aria(t)"
              :aria-label="aria(t)"
              @mousedown.prevent
              @click="frapper(t)">
              {{ t.libelle }}
            </button>
            <button
              type="button"
              class="pax-mk-key is-action pax-mk-entree"
              :title="$t('keyboard.enter')"
              :aria-label="$t('keyboard.enter')"
              @mousedown.prevent
              @click="$emit('entree')">
              ↵
            </button>
            <button
              type="button"
              class="pax-mk-key pax-mk-close"
              :title="$t('keyboard.close')"
              :aria-label="$t('keyboard.close')"
              @mousedown.prevent
              @click="$emit('close')">
              <svg
                viewBox="0 0 24 24" width="22" height="22" aria-hidden="true" fill="none"
                stroke="currentColor" stroke-width="1.6" stroke-linecap="round" stroke-linejoin="round">
                <rect x="2.5" y="3" width="19" height="11" rx="2" />
                <path d="M6 6.5h.01M9 6.5h.01M12 6.5h.01M15 6.5h.01M18 6.5h.01M6 10h.01M18 10h.01M9 10h6" />
                <path d="M8.5 17.5 12 21l3.5-3.5" />
              </svg>
            </button>
          </div>
        </div>
      </div>
    </Transition>
  </Teleport>
</template>

<script setup lang="ts">
import { computed, nextTick, onBeforeUnmount, ref, watch } from 'vue'
import {
  ACTIONS, ACTIONS_EDITION, ONGLETS, disposition, insere, plancheCompacte,
  type OngletClavier, type ProfilClavier, type ToucheMath,
} from '~/composables/useMathKeyboard'
import { useKatex } from '~/composables/useKatex'

const props = defineProps<{
  /** Le champ que les touches alimentent. */
  cible: HTMLInputElement | HTMLTextAreaElement | null
  ouvert: boolean
  /** Langue de l'interface : séparateur décimal, disposition des lettres. */
  lang?: string
  /** Ce que le champ attend (`profilPourType`) : la première planche. */
  profil?: ProfilClavier
}>()

const emit = defineEmits<{ close: [], open: [], entree: [] }>()

const { t: tr } = useI18n()
const { renderMath } = useKatex()

const onglet = ref<OngletClavier>('123')
const planche = computed(() => disposition(onglet.value, props.lang || 'fr'))

// ── La majuscule ──────────────────────────────────────────────────────────────
// Elle module les touches, comme chez MathLive : `x` devient `y`, `<` devient
// `≤`, `sin` devient `sin⁻¹`. Un appui sur ⇧ vaut pour la touche suivante ; la
// touche Maj du clavier physique, tant qu'elle est tenue, fait de même.
const maj = ref(false)
const majPhysique = ref(false)
const majActive = computed(() => maj.value || majPhysique.value)
function vue(t: ToucheMath): ToucheMath {
  return majActive.value && t.maj ? t.maj : t
}
function surTouche(e: KeyboardEvent) {
  if (e.key === 'Shift') majPhysique.value = e.type === 'keydown'
}
function surPerteFenetre() { majPhysique.value = false }
watch(() => props.ouvert, (ouvert) => {
  if (!import.meta.client) return
  if (ouvert) {
    window.addEventListener('keydown', surTouche)
    window.addEventListener('keyup', surTouche)
    window.addEventListener('blur', surPerteFenetre)
  } else {
    window.removeEventListener('keydown', surTouche)
    window.removeEventListener('keyup', surTouche)
    window.removeEventListener('blur', surPerteFenetre)
    maj.value = false
    majPhysique.value = false
  }
}, { immediate: true })

// La planche du champ (calculatrice, ensembles), tant que l'élève n'a pas
// demandé le clavier complet. Changer de champ — donc peut-être de profil —
// ramène à la planche du nouveau champ.
const etendu = ref(false)
const aUneCompacte = computed(() => !!plancheCompacte(props.profil ?? 'complet', props.lang || 'fr'))
const compacte = computed(() =>
  etendu.value ? null : plancheCompacte(props.profil ?? 'complet', props.lang || 'fr'))
const affichees = computed(() => compacte.value?.rangees ?? planche.value.rangees)
const colonnes = computed(() => compacte.value
  ? `repeat(${compacte.value.colonnes}, minmax(0, 1fr))`
  : planche.value.colonnes)
watch(() => props.cible, () => { etendu.value = false; onglet.value = '123' })

function aria(t: ToucheMath): string {
  if (t.aria?.startsWith('keyboard.')) return tr(t.aria)
  return t.aria ?? t.texte ?? t.libelle ?? ''
}

// Les étiquettes LaTeX, rendues à la demande et gardées : `renderMath` est
// asynchrone (KaTeX se charge à la demande), le template ne peut l'attendre.
const etiquettes = ref<Record<string, string>>({})
watch(affichees, async (p) => {
  const toutes = p.flat().flatMap(t => (t.maj ? [t, t.maj] : [t]))
  const manquantes = [...new Set(toutes.map(t => t.latex).filter(
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
/** La petite étiquette de la variante, en haut à droite de la touche. */
function indice(t: ToucheMath): string {
  if (t.latex && etiquettes.value[t.latex]) return etiquettes.value[t.latex] as string
  const x = t.libelle ?? t.texte ?? ''
  return x.replace(/[&<>]/g, ch => ({ '&': '&amp;', '<': '&lt;', '>': '&gt;' })[ch] as string)
}

function frapper(t: ToucheMath) {
  if (t.action === 'maj') { maj.value = !maj.value; return }
  if (t.action === 'entree') { emit('entree'); return }
  if (!props.cible) return
  insere(props.cible, t)
  // Une majuscule, comme sur un téléphone : elle retombe après la touche
  // suivante, qu'elle écrive ou non (⇤, ⇥, 🗑 aussi).
  maj.value = false
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

/* Quatre rangées de haut quel que soit l'onglet : la planche ne saute pas
   quand on en change. Les colonnes viennent de la disposition (dix égales,
   ou trois blocs pour `123`). */
.pax-mk-grid {
  display: grid;
  grid-auto-rows: 2.6rem;
  gap: 0.3rem;
  min-height: calc(4 * 2.6rem + 3 * 0.3rem);
  align-content: start;
}

.pax-mk-vide { display: block; }

.pax-mk-key {
  position: relative;
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

/* Toutes les touches en noir (couleur du texte) ; les familles ne se
   distinguent qu'à la graisse, à la taille et au fond des actions. */
.pax-mk-key.is-chiffre { font-weight: 600; }
.pax-mk-key.is-fonction { font-size: 0.9rem; }
.pax-mk-key.is-variable { font-style: italic; }
.pax-mk-grid.is-abc .pax-mk-key.is-variable { font-style: normal; }
.pax-mk-key.is-action {
  background: color-mix(in srgb, var(--color-text) 8%, var(--color-surface));
}
/* La variante sous la majuscule, en petit dans le coin (MathLive). */
.pax-mk-indice {
  position: absolute;
  top: 2px;
  right: 4px;
  font-size: 0.6rem;
  font-style: normal;
  font-weight: 400;
  line-height: 1;
  color: var(--color-text-muted);
  pointer-events: none;
}
.pax-mk-indice :deep(.katex) { font-size: 0.95em; }
.pax-mk-key.is-actif {
  background: var(--color-primary);
  border-color: var(--color-primary);
  color: #fff;
}

/* La rangée d'actions : les onglets à gauche, les commandes à droite. */
.pax-mk-actions {
  display: flex;
  flex-wrap: wrap;
  gap: 0.3rem;
  margin-top: 0.3rem;
}
.pax-mk-actions > .pax-mk-onglets { flex: 1 1 8rem; height: 2.6rem; }
/* « ⋯ » se loge à côté des commandes, sur la même rangée : la planche
   compacte n'a ainsi que cinq rangées de haut. */
.pax-mk-actions > .pax-mk-plus { flex: 1 1 2.9rem; min-width: 2.9rem; height: 2.6rem; }
.pax-mk-commandes {
  display: grid;
  grid-auto-flow: column;
  grid-auto-columns: 2.9rem;
  grid-auto-rows: 2.6rem;
  gap: 0.3rem;
  margin-left: auto;
}
.pax-mk-entree { font-size: 1.2rem; }

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

/* La barre du clavier complet : onglets à gauche, outils à droite. */
.pax-mk-barre {
  display: flex;
  align-items: center;
  gap: 0.5rem;
  margin-bottom: 0.35rem;
}
.pax-mk-barre > .pax-mk-onglets { flex: 1 1 auto; height: 2rem; }
.pax-mk-barre .pax-mk-onglet { flex: 0 1 4.5rem; display: flex; align-items: center; justify-content: center; }
.pax-mk-outils { display: flex; gap: 0.3rem; }
.pax-mk-calc { color: var(--color-text); }
.pax-mk-outil {
  width: 2.4rem;
  height: 2rem;
  display: flex;
  align-items: center;
  justify-content: center;
  border: 0;
  border-radius: 0.45rem;
  background: transparent;
  color: var(--color-text-muted);
  font-size: 1.05rem;
  cursor: pointer;
}
.pax-mk-outil:hover { color: var(--color-text); background: var(--color-surface); }
.pax-mk-outil.pax-mk-close { width: 2.9rem; }

/* Compacte : une calculatrice n'a pas à courir toute la largeur. */
.pax-mk.is-compact { width: min(100%, 24rem); }
.pax-mk-plus { font-size: 1.2rem; font-weight: 700; }

.pax-mk-close {
  background: var(--color-primary);
  border-color: var(--color-primary);
  color: #fff;
}
.pax-mk-close:hover { background: var(--color-primary-hover); border-color: var(--color-primary-hover); }
.pax-mk-close:active { background: var(--color-primary-hover); }

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
  .pax-mk-actions { gap: 0.2rem; margin-top: 0.2rem; }
  .pax-mk-actions > .pax-mk-plus { height: 2.35rem; }
  .pax-mk-commandes { grid-auto-columns: minmax(2.2rem, 1fr); grid-auto-rows: 2.35rem; gap: 0.2rem; }
  .pax-mk-barre { gap: 0.25rem; margin-bottom: 0.25rem; }
  .pax-mk-outil { width: 2rem; }
  /* Petit écran : pas d'indice de variante, les touches n'ont pas la place. */
  .pax-mk-indice { display: none; }
  .pax-mk-key { font-size: 0.9rem; border-radius: 0.35rem; }
  .pax-mk-key.is-fonction { font-size: 0.75rem; }
  .pax-mk-onglet { font-size: 0.75rem; }
}
</style>

<style>
/* Hors du `scoped` : la place que le panneau réserve en bas de la page. */
body.pax-mk-actif { padding-bottom: var(--pax-mk-hauteur, 0px); }
</style>
