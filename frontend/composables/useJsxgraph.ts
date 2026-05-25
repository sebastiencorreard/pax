// Hydrates `<div class="pax-jsxgraph" data-jsxgraph="…">` containers (emitted
// by the backend slib/geo2D/jsxgraph built-in) into interactive JSXGraph
// boards. JSXGraph is loaded once from a CDN; the per-board init JS is
// authored server-side from the exercise definition (trusted content) and run
// via `new Function`.

const JSXGRAPH_VERSION = '1.11.1'
const CDN = `https://cdn.jsdelivr.net/npm/jsxgraph@${JSXGRAPH_VERSION}/distrib`

let loadPromise: Promise<void> | null = null

function loadJsxgraph(): Promise<void> {
  if (!import.meta.client) return Promise.resolve()
  if ((window as unknown as { JXG?: unknown }).JXG) return Promise.resolve()
  if (loadPromise) return loadPromise
  loadPromise = new Promise<void>((resolve, reject) => {
    if (!document.querySelector('link[data-jsxgraph-css]')) {
      const css = document.createElement('link')
      css.rel = 'stylesheet'
      css.href = `${CDN}/jsxgraph.css`
      css.setAttribute('data-jsxgraph-css', '')
      document.head.appendChild(css)
    }
    const script = document.createElement('script')
    script.src = `${CDN}/jsxgraphcore.js`
    script.async = true
    script.onload = () => resolve()
    script.onerror = () => reject(new Error('JSXGraph failed to load'))
    document.head.appendChild(script)
  })
  return loadPromise
}

export function useJsxgraph() {
  // Find every not-yet-initialised JSXGraph container under `root`, load the
  // library if needed, then run each board's init script.
  async function renderBoards(root: HTMLElement | null): Promise<void> {
    if (!import.meta.client || !root) return
    const boxes = Array.from(
      root.querySelectorAll<HTMLElement>('.pax-jsxgraph[data-jsxgraph]'),
    ).filter(b => !b.dataset.jsxRendered)
    if (!boxes.length) return
    try {
      await loadJsxgraph()
    } catch (e) {
      console.error(e)
      return
    }
    for (const box of boxes) {
      const js = box.dataset.jsxgraph
      if (!js) continue
      box.dataset.jsxRendered = '1'
      try {
        // eslint-disable-next-line @typescript-eslint/no-implied-eval
        new Function(js)()
      } catch (e) {
        console.error('JSXGraph board init failed', e)
        delete box.dataset.jsxRendered
      }
    }
  }

  return { renderBoards }
}
