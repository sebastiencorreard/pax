// Lazily loads CodeMirror 5 (the WIMS-compatible version) from a CDN: the core
// once, then language modes / themes / the fullscreen addon on demand. The
// Codemirror component awaits these, then builds each editor from server-side
// config (slib `coding/editor`). Mirrors useJsxgraph's CDN-loading approach.

const CM_VERSION = '5.65.16'
const CDN = `https://cdn.jsdelivr.net/npm/codemirror@${CM_VERSION}`

let corePromise: Promise<void> | null = null
const loaded = new Set<string>()

function loadCss(href: string, marker: string): void {
  if (document.querySelector(`link[data-cm="${marker}"]`)) return
  const l = document.createElement('link')
  l.rel = 'stylesheet'
  l.href = href
  l.setAttribute('data-cm', marker)
  document.head.appendChild(l)
}

function loadScript(src: string): Promise<void> {
  return new Promise<void>((resolve, reject) => {
    const s = document.createElement('script')
    s.src = src
    s.async = false // preserve execution order (core before modes/addons)
    s.onload = () => resolve()
    s.onerror = () => reject(new Error(`CodeMirror asset failed: ${src}`))
    document.head.appendChild(s)
  })
}

export function loadCodemirrorCore(): Promise<void> {
  if (!import.meta.client) return Promise.resolve()
  if ((window as unknown as { CodeMirror?: unknown }).CodeMirror) return Promise.resolve()
  if (corePromise) return corePromise
  loadCss(`${CDN}/lib/codemirror.css`, 'core')
  corePromise = loadScript(`${CDN}/lib/codemirror.js`)
  return corePromise
}

// WIMS lang → CodeMirror mode path. Most map to `<lang>/<lang>`; a few share
// the clike mode.
const MODE_PATH: Record<string, string> = {
  python: 'python/python',
  c: 'clike/clike',
  'c++': 'clike/clike',
  cpp: 'clike/clike',
  java: 'clike/clike',
  javascript: 'javascript/javascript',
  js: 'javascript/javascript',
}

export async function loadCodemirrorMode(lang: string): Promise<string> {
  await loadCodemirrorCore()
  const key = (lang || '').toLowerCase()
  const path = MODE_PATH[key] || `${key}/${key}`
  const mode = path.split('/')[1] || key
  if (!key || loaded.has(`mode:${path}`)) return mode
  loaded.add(`mode:${path}`)
  try {
    await loadScript(`${CDN}/mode/${path}.js`)
  } catch {
    // Unknown language → CodeMirror falls back to plain text.
  }
  return mode
}

export function loadCodemirrorTheme(theme: string): void {
  if (!import.meta.client || !theme || theme === 'default') return
  loadCss(`${CDN}/theme/${theme}.css`, `theme:${theme}`)
}

export async function loadCodemirrorFullscreen(): Promise<void> {
  await loadCodemirrorCore()
  loadCss(`${CDN}/addon/display/fullscreen.css`, 'fullscreen')
  if (loaded.has('addon:fullscreen')) return
  loaded.add('addon:fullscreen')
  try {
    await loadScript(`${CDN}/addon/display/fullscreen.js`)
  } catch {
    // Fullscreen button becomes a no-op if the addon can't load.
  }
}
