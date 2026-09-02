// Charge `deployggb.js` une fois, puis construit les applets GeoGebra des
// énoncés. Même forme que `useJsxgraph` et `useJsmol` : la bibliothèque vient
// du réseau, la configuration vient du serveur (segment `geogebra`, traduit
// depuis `slib/geo2D/geogebra` par le moteur .def).
//
// `deployggb.js` n'est qu'un **chargeur** de 37 Ko : il choisit et va chercher
// l'application sur `cdn.geogebra.org`. C'est la voie que GeoGebra prévoit
// pour l'intégration, et la même que JSXGraph — on ne réhéberge rien.
// Le dépôt en garde une copie vendorisée (`wims/public_html/scripts/js/`),
// figée à la version de l'arbre WIMS ; l'URL officielle suit les correctifs.
//
// Tout est dans `DEPLOYGGB` : basculer sur la copie locale, si la question de
// licence devait être tranchée autrement, se réduit à changer cette constante.

const DEPLOYGGB = 'https://www.geogebra.org/apps/deployggb.js'

export interface GeogebraConfig {
  /** L'identifiant du conteneur, et le nom sous lequel les commandes l'appellent. */
  id: string
  /** L'objet `parameters` de `GGBApplet` — largeur, barres, `filename`… */
  params: Record<string, string>
  /** Le drapeau `is3D` de l'objet `views`. */
  is3d?: boolean
  /** Les commandes de l'applet, une par ligne, préfixées de son identifiant. */
  commands?: string
}

interface GGBAppletCtor {
  new (params: Record<string, unknown>, version: string, views?: unknown): {
    inject: (target: string | HTMLElement) => void
  }
}

function ggbCtor(): GGBAppletCtor | null {
  return (window as unknown as { GGBApplet?: GGBAppletCtor }).GGBApplet ?? null
}

let loadPromise: Promise<void> | null = null

export function loadGeogebra(): Promise<void> {
  if (!import.meta.client) return Promise.resolve()
  if (ggbCtor()) return Promise.resolve()
  if (loadPromise) return loadPromise
  loadPromise = new Promise<void>((resolve, reject) => {
    const script = document.createElement('script')
    script.src = DEPLOYGGB
    script.async = true
    script.onload = () => resolve()
    script.onerror = () => reject(new Error('deployggb.js failed to load'))
    document.head.appendChild(script)
  })
  return loadPromise
}

/** Construit une applet GeoGebra dans `el`, d'après la configuration du serveur. */
export async function mountGeogebra(el: HTMLElement, cfg: GeogebraConfig): Promise<void> {
  if (!import.meta.client) return
  await loadGeogebra()
  const GGBApplet = ggbCtor()
  if (!GGBApplet) throw new Error('GGBApplet missing after load')

  // `inject` remplace le contenu de sa cible : on lui donne le conteneur du
  // marqueur. L'identifiant de l'applet ne vient pas du DOM mais de
  // `params.id` — le nom sous lequel les commandes la désignent.
  el.innerHTML = ''
  const params: Record<string, unknown> = { ...cfg.params }

  // L'applet se charge en **asynchrone** ; ses commandes ne valent qu'une fois
  // l'API prête. `appletOnLoad` est le rendez-vous que GeoGebra donne pour
  // cela — c'est aussi lui qui livre l'objet d'API, plutôt que de compter sur
  // la globale `window[id]` que l'applet finit par poser.
  await new Promise<void>(resolve => {
    params.appletOnLoad = (api: unknown) => {
      if (cfg.commands?.trim()) {
        try {
          // Les commandes sont écrites `ggbApplet0.evalCommand('…');` : on lie
          // ce nom-là à l'API, plutôt que d'attendre une globale du même nom.
          // eslint-disable-next-line @typescript-eslint/no-implied-eval
          new Function(cfg.id, cfg.commands)(api)
        } catch (e) {
          console.error('GeoGebra commands failed', e)
        }
      }
      resolve()
    }
    const views = {
      is3D: cfg.is3d ? 1 : 0,
      AV: 0, SV: 0, CV: 0, EV2: 0, CP: 0, PC: 0, DA: 0, FI: 0, PV: 0, macro: 0,
    }
    new GGBApplet(params, '5.0', views).inject(el)
  })
}

/**
 * Hydrate les marqueurs `.pax-geogebra` d'un fragment rendu en `v-html`.
 *
 * Aucun exercice du corpus ne pose aujourd'hui son applet dans un `<table>`
 * — qui resterait un seul segment HTML —, mais le dispositif ne coûte rien et
 * évite qu'un tel exercice rende un conteneur vide sans le dire. Idempotent.
 */
export function hydrateGeogebraMarkers(root: HTMLElement): void {
  root.querySelectorAll<HTMLElement>('.pax-geogebra[data-geogebra]').forEach(el => {
    if (el.dataset.ggbMounted === '1') return
    const brut = el.getAttribute('data-geogebra')
    if (!brut) return
    let cfg: GeogebraConfig
    try {
      cfg = JSON.parse(brut)
    } catch {
      return
    }
    el.dataset.ggbMounted = '1'
    mountGeogebra(el, cfg).catch(e => console.error('GeoGebra applet init failed', e))
  })
}
