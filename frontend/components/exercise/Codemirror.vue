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

const props = defineProps<{ config: CodeEditorConfig }>()

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
