// Loads the JSXGraph library once from a CDN. The ExerciseJsxgraph component
// awaits this, then runs each board's init JS (authored server-side from the
// exercise definition, run via `new Function`).

const JSXGRAPH_VERSION = '1.11.1'
const CDN = `https://cdn.jsdelivr.net/npm/jsxgraph@${JSXGRAPH_VERSION}/distrib`

let loadPromise: Promise<void> | null = null

export function loadJsxgraph(): Promise<void> {
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
