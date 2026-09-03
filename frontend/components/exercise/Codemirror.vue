<template>
  <div class="pax-codeeditor">
    <div v-if="showToolbar" class="pax-cm-toolbar">
      <button v-if="config.init" type="button" class="pax-cm-btn" @click="reset">{{ T.reset }}</button>
      <button v-if="config.fullscreen" type="button" class="pax-cm-btn" :title="T.fullscreen" @click="toggleFullscreen">⤢</button>
      <button v-if="hasContrast" type="button" class="pax-cm-btn" :title="T.contrast" @click="toggleContrast">{{ dark ? '🌙' : '☀' }}</button>
      <select v-if="config.codes.length > 1" v-model.number="active" class="pax-cm-select" @change="selectBuffer">
        <option v-for="(c, i) in config.codes" :key="i" :value="i">{{ c.name || ('#' + (i + 1)) }}</option>
      </select>
    </div>
    <div v-if="config.instructions.length" class="pax-cm-instructions">
      <button v-for="(ins, i) in config.instructions" :key="i" type="button"
              class="pax-cm-btn pax-cm-instr" @click="insert(ins)">{{ ins }}</button>
    </div>
    <div ref="host" class="pax-cm-host"></div>
    <!-- `type=runcode` : l'éditeur est la réponse. Le programme s'exécute ici,
         dans le navigateur, et seules les valeurs des variables partent au
         serveur. -->
    <div v-if="config.run" class="pax-cm-run">
      <button
        type="button" class="pax-cm-btn pax-cm-play"
        :disabled="busy" @click="executer">
        {{ busy ? '…' : (config.run.label || 'Jouer le code') }}
      </button>
      <p v-if="avertissement" class="pax-cm-warn">{{ avertissement }}</p>
      <pre
        v-if="sortie || erreur" class="pax-cm-output"
        :class="{ 'is-error': !!erreur }">{{ erreur || sortie }}</pre>
    </div>
    <!-- Floating exit button: in fullscreen the toolbar is hidden behind the
         editor, so this stays reachable to leave (Esc/F11 also work). -->
    <button v-if="isFullscreen" type="button" class="pax-cm-exit-fs"
            :title="T.exit" @click="exitFullscreen">⤡</button>
  </div>
</template>

<script setup lang="ts">
import { ref, computed, onMounted, onBeforeUnmount, watch } from 'vue'
import type { CodeEditorConfig } from '~/composables/useExerciseLogic'
import {
  loadCodemirrorCore, loadCodemirrorMode, loadCodemirrorTheme, loadCodemirrorFullscreen,
} from '~/composables/useCodemirror'

import {
  composerReponseRuncode, executerPython, motCleManquant,
} from '~/composables/useSkulpt'

const props = defineProps<{
  config: CodeEditorConfig
  submitted?: boolean
}>()

const emit = defineEmits<{ 'update:replies': [map: Record<string, string>] }>()

const busy = ref(false)
const sortie = ref('')
const erreur = ref<string | null>(null)
const avertissement = ref('')

/**
 * Exécute le programme et remonte ce que le correcteur attend.
 *
 * WIMS sépare les deux gestes — un bouton lance le code, et `capture()` relève
 * les variables au moment de l'envoi. Les réunir vaut mieux ici : le champ
 * suit l'exécution, comme les figures suivent le déplacement d'un point, et
 * l'élève ne peut pas envoyer l'état d'un programme qu'il a modifié depuis.
 */
async function executer() {
  const run = props.config.run
  if (!run || busy.value) return
  const code = cm ? cm.getValue() : (current()?.code ?? '')

  // `keyword_python` : l'exercice exige certains mots dans le code. WIMS
  // refuse alors d'envoyer et le dit — « sers-toi d'une boucle `for` » n'est
  // pas une suggestion.
  const manquant = motCleManquant(code, run.keywords || [])
  if (manquant) {
    avertissement.value = `Il manque « ${manquant} » dans votre code.`
    return
  }
  avertissement.value = ''

  busy.value = true
  try {
    // Une SEULE exécution pour tous les champs : ces programmes tirent au
    // hasard (`randint`), et rejouer le code donnerait au champ `js2wims1` des
    // valeurs différentes de celles du `runcode` — deux réponses incohérentes
    // pour un même programme.
    const annexes = run.also || []
    const noms = [...(run.variables || []), ...annexes.flatMap(a => a.variables)]
    const res = await executerPython(code, noms)
    sortie.value = res.sortie
    erreur.value = res.erreur
    if (!props.submitted) {
      // Toutes les réponses en **une** émission : émises l'une après l'autre,
      // elles repartiraient du même état et la dernière écraserait les autres.
      const propres = res.valeurs.slice(0, (run.variables || []).length)
      const lot: Record<string, string> = {
        [run.reply]: composerReponseRuncode(code, propres),
      }
      let i = (run.variables || []).length
      for (const annexe of annexes) {
        const part = res.valeurs.slice(i, i + annexe.variables.length)
        i += annexe.variables.length
        // Sans le code en tête : `js2wims1` ne reçoit que les valeurs.
        lot[annexe.reply] = part.map(v => `[${v}]`).join(',')
      }
      emit('update:replies', lot)
    }
  } finally {
    busy.value = false
  }
}

const host = ref<HTMLElement | null>(null)
// eslint-disable-next-line @typescript-eslint/no-explicit-any
let cm: any = null
const active = ref(0)
const dark = ref(true)
const isFullscreen = ref(false)

const T = { reset: 'Réinitialiser', fullscreen: 'Plein écran : F11', contrast: 'Nuit / Jour', exit: 'Quitter le plein écran (Échap)' }

function setFullscreen(on: boolean) {
  if (!cm) return
  cm.setOption('fullScreen', on)
  isFullscreen.value = on
}

const hasContrast = computed(() => props.config.themes.length >= 2)
const showToolbar = computed(() =>
  props.config.init || props.config.fullscreen || hasContrast.value || props.config.codes.length > 1)

function current() { return props.config.codes[active.value] }

async function build() {
  if (!import.meta.client || !host.value) return
  try {
    await loadCodemirrorCore()
    const c = current()
    const mode = await loadCodemirrorMode(c?.lang || '')
    props.config.themes.forEach(loadCodemirrorTheme)
    if (props.config.fullscreen) await loadCodemirrorFullscreen()
    // eslint-disable-next-line @typescript-eslint/no-explicit-any
    const CM = (window as any).CodeMirror
    if (!CM || !host.value) return
    host.value.innerHTML = ''
    // eslint-disable-next-line @typescript-eslint/no-explicit-any
    const opts: any = {
      value: c?.code || '',
      mode,
      lineNumbers: true,
      matchBrackets: true,
      readOnly: c?.readonly ?? false,
      indentUnit: 2,
      viewportMargin: 10,
      theme: props.config.themes[0] || 'default',
    }
    if (props.config.fullscreen) {
      opts.extraKeys = {
        // eslint-disable-next-line @typescript-eslint/no-explicit-any
        F11: (e: any) => setFullscreen(!e.getOption('fullScreen')),
        // eslint-disable-next-line @typescript-eslint/no-explicit-any
        Esc: (e: any) => { if (e.getOption('fullScreen')) setFullscreen(false) },
      }
    }
    cm = CM(host.value, opts)
    dark.value = true
    isFullscreen.value = false
  } catch (e) {
    console.error('CodeMirror init failed', e)
  }
}

function selectBuffer() {
  const c = current()
  if (!cm || !c) return
  loadCodemirrorMode(c.lang).then(m => cm.setOption('mode', m))
  cm.setOption('readOnly', c.readonly)
  cm.setValue(c.code)
}

function reset() { if (cm) cm.setValue(current()?.code || '') }

function toggleFullscreen() { if (cm) setFullscreen(!cm.getOption('fullScreen')) }

function exitFullscreen() { setFullscreen(false) }

function toggleContrast() {
  if (!cm || props.config.themes.length < 2) return
  dark.value = !dark.value
  cm.setOption('theme', dark.value ? props.config.themes[0] : props.config.themes[1])
}

function insert(text: string) {
  if (cm && !cm.getOption('readOnly')) { cm.replaceSelection(text); cm.focus() }
}

onMounted(build)
watch(() => props.config, () => { cm = null; active.value = 0; build() })
onBeforeUnmount(() => { cm = null })
</script>

<style scoped>
/* `type=runcode` : le bouton d'exécution et la sortie du programme, sous
   l'éditeur. WIMS les pose de même — un `<span>` cliquable et un `<pre>`. */
.pax-cm-run { margin-top: 0.5rem; }
.pax-cm-play { font-weight: 600; }
.pax-cm-warn {
  margin: 0.4rem 0 0;
  font-size: 0.85rem;
  color: var(--color-warning, #b45309);
}
.pax-cm-output {
  margin: 0.5rem 0 0;
  padding: 0.5rem 0.75rem;
  border-radius: 0.5rem;
  background: var(--color-surface-2, rgba(127, 127, 127, 0.08));
  font-size: 0.85rem;
  white-space: pre-wrap;
  overflow-x: auto;
  max-height: 16rem;
}
.pax-cm-output.is-error { color: var(--color-danger, #dc2626); }

.pax-codeeditor { margin: 0.5rem 0; }
.pax-cm-toolbar, .pax-cm-instructions {
  display: flex; flex-wrap: wrap; gap: 0.4rem; margin-bottom: 0.4rem; align-items: center;
}
.pax-cm-btn {
  padding: 0.25rem 0.6rem;
  border: 1px solid var(--color-border);
  border-radius: 0.4rem;
  background: var(--color-surface);
  color: var(--color-text);
  cursor: pointer;
  font-size: 0.9rem;
  line-height: 1.2;
  transition: border-color 0.15s, background 0.15s;
}
.pax-cm-btn:hover { border-color: var(--color-primary); }
.pax-cm-instr { font-family: monospace; }
.pax-cm-select {
  padding: 0.25rem 0.5rem; border: 1px solid var(--color-border);
  border-radius: 0.4rem; background: var(--color-surface); color: var(--color-text);
}
/* CodeMirror's own theme CSS paints the editor; just frame it and keep it from
   growing unbounded for long readonly listings. */
.pax-cm-host :deep(.CodeMirror) {
  border: 1px solid var(--color-border);
  border-radius: 0.4rem;
  height: auto;
  max-height: 360px;
}
.pax-cm-host :deep(.CodeMirror-fullscreen) {
  max-height: none;
  z-index: 2000;
}
/* Sits above the fullscreen editor (z-index 2000) so it stays clickable. */
.pax-cm-exit-fs {
  position: fixed;
  top: 1rem;
  right: 1rem;
  z-index: 2001;
  width: 2.5rem;
  height: 2.5rem;
  display: flex;
  align-items: center;
  justify-content: center;
  font-size: 1.1rem;
  border: 1px solid var(--color-border);
  border-radius: 0.5rem;
  background: var(--color-surface);
  color: var(--color-text);
  cursor: pointer;
  box-shadow: 0 2px 8px rgba(0, 0, 0, 0.25);
}
.pax-cm-exit-fs:hover { border-color: var(--color-primary); }
</style>
