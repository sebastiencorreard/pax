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

/**
 * Construit une applet GeoGebra dans `el`, d'après la configuration du serveur.
 *
 * Rend l'objet d'API que GeoGebra livre à `appletOnLoad` : une figure d'énoncé
 * l'ignore, une figure **de réponse** s'y abonne pour relire son état.
 */
export async function mountGeogebra(
  el: HTMLElement,
  cfg: GeogebraConfig,
): Promise<unknown> {
  if (!import.meta.client) return null
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
  return await new Promise<unknown>(resolve => {
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
      resolve(api)
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

// ── Relire la figure : le port de `geogebra2wims()` ───────────────────────────

/** Les réglages de lecture, tels que le moteur les tire de `replyoption`. */
export interface GeogebraLecture {
  /** Au-delà de ce nombre d'objets, la figure n'est pas envoyée. */
  max: number
  /** Décimales conservées sur les coordonnées. */
  precision: number
  /** Objets à passer, quels qu'ils soient. */
  ignore: string[]
  /** Préfixe restreignant l'analyse ; à défaut, `My_` est écarté. */
  prefix: string
  /** La cote entre alors dans les coordonnées. */
  is3d: boolean
}

/** L'API de l'applet, réduite à ce que la lecture emploie. */
interface GgbApi {
  getObjectNumber: () => number
  getObjectName: (i: number) => string
  getObjectType: (name: string) => string
  getValueString: (name: string) => string
  getCommandString: (name: string, useLocale: boolean) => string
  getXcoord: (name: string) => number
  getYcoord: (name: string) => number
  getZcoord?: (name: string) => number
  registerUpdateListener?: (fn: () => void) => void
  registerAddListener?: (fn: () => void) => void
  registerRemoveListener?: (fn: () => void) => void
}

// Les types d'objets que WIMS sait analyser (`list_of_things`).
const TYPES_LUS = [
  'point', 'line', 'ray', 'circle', 'segment', 'function', 'polynomial',
  'conic', 'ellipse', 'hyperbola', 'parabola', 'vector', 'angle', 'conicpart',
  'numeric', 'text', 'polygon', 'triangle', 'quadrilateral', 'pentagon',
  'hexagon', 'boolean',
]

// Une équation se ramène à « membre gauche moins membre droit ».
const TYPES_EQUATION = new Set([
  'circle', 'line', 'polynomial', 'conic', 'parabola', 'ellipse', 'hyperbola',
  'ray',
])
// Ceux dont la valeur se lit telle quelle, après le `=`.
const TYPES_VALEUR = new Set([
  'text', 'numeric', 'segment', 'function', 'conicpart', 'boolean',
])
// Tous les polygones se rendent sous le nom `polygon`.
const TYPES_POLYGONE = new Set([
  'polygon', 'triangle', 'quadrilateral', 'pentagon', 'hexagon',
])

const GRECQUES = [
  'alpha', 'beta', 'gamma', 'delta', 'epsilon', 'zeta', 'eta', 'theta',
  'iota', 'kappa', 'lambda', 'mu', 'nu', 'xi', 'omicron', 'pi', 'rho',
  'sigmaf', 'sigma', 'tau', 'upsilon', 'phi', 'khi', 'psi', 'omega',
]

/** Le nom d'un objet, une lettre grecque étant écrite en toutes lettres. */
function nomLisible(nom: string, prefixe: string): string {
  const rang = nom.charCodeAt(prefixe.length ? prefixe.length : 0)
  if (rang > 944 && rang - 945 < GRECQUES.length) {
    return prefixe + GRECQUES[rang - 945]
  }
  return nom
}

function arrondi(v: number, decimales: number): number {
  const f = Math.pow(10, decimales)
  return Math.round(v * f) / f
}

/**
 * L'état de la figure, dans la forme que le correcteur WIMS attend.
 *
 * `anstype/geogebra.input` injecte dans la page un `geogebra2wims()` qui
 * parcourt les objets de l'applet et en compose une chaîne à deux parties,
 * séparées par `;` :
 *
 *     <nom>=<type>,<données>&&…  ;  <nom>=<commande>&&…
 *
 * La première porte les **valeurs** — les coordonnées d'un point ou d'un
 * vecteur, l'équation ramenée à zéro d'une conique, la valeur d'un texte ou
 * d'un booléen —, la seconde les **définitions** (`getCommandString`), par
 * lesquelles le correcteur vérifie qu'un objet a bien été *construit* et non
 * posé à la main.
 *
 * Rend `null` quand la figure ne doit pas être envoyée : aucun objet, ou plus
 * que le `max` de l'exercice — WIMS y alerte l'élève et n'envoie rien.
 */
export function lireFigureGeogebra(
  api: GgbApi,
  reglages: GeogebraLecture,
): string | null {
  const ignores = new Set(reglages.ignore)
  const valeurs: string[] = []
  const definitions: string[] = []
  let comptes = 0

  const nombre = api.getObjectNumber()
  for (let i = 0; i < nombre; i++) {
    const objet = api.getObjectName(i)
    if (ignores.has(objet)) continue
    const type = api.getObjectType(objet)
    if (!TYPES_LUS.includes(type)) continue

    let brut = api.getValueString(objet)
    // WIMS remonte l'exposant que GeoGebra écrit en Unicode (`²` → `^2`).
    brut = decodeURIComponent(encodeURIComponent(brut).replace(/%C2%B/g, '^'))

    // `object_analysis` restreint l'analyse à un préfixe ; à défaut, WIMS
    // écarte les objets marqués `My_`, ceux d'un `.ggb` qu'on ne veut pas voir.
    const retenu = reglages.prefix
      ? brut.substr(0, reglages.prefix.length) === reglages.prefix
      : brut.substr(0, 3) !== 'My_'
    if (!retenu) continue

    comptes++
    const nom = nomLisible(objet, reglages.prefix)
    let donnee: string

    if (type === 'point' || type === 'vector') {
      const x = arrondi(api.getXcoord(objet), reglages.precision)
      const y = arrondi(api.getYcoord(objet), reglages.precision)
      const coords = [x, y]
      if (reglages.is3d && api.getZcoord) {
        coords.push(arrondi(api.getZcoord(objet), reglages.precision))
      }
      donnee = `${nom}=${type},${coords.join(',')}`
    } else if (TYPES_EQUATION.has(type)) {
      // `c:(x - 5.73)^2 + (y - 1.53)^2 = 16` → `c=circle,(x-5.73)^2+… -((16))`
      const deuxPoints = brut.indexOf(':')
      const egal = brut.indexOf('=')
      const gauche = brut.substring(deuxPoints + 1, egal - 1)
      const droite = brut.substring(egal + 1)
      donnee = `${nom}=${type},${gauche}-((${droite}))`
    } else if (type === 'angle') {
      // Le degré que GeoGebra suffixe (`^0`) n'a rien à faire dans la valeur.
      const sansDegre = decodeURIComponent(
        encodeURIComponent(brut).replace(/%5E0/g, ''),
      )
      const coupe = sansDegre.split('=')
      donnee = `${nomLisible(coupe[0] ?? nom, reglages.prefix)}=angle,${coupe.slice(1).join('=')}`
    } else if (TYPES_VALEUR.has(type)) {
      donnee = `${nom}=${type},${brut.split('=').slice(1).join('=')}`
    } else if (TYPES_POLYGONE.has(type)) {
      const coupe = brut.split('=')
      donnee = `${coupe[0] ?? nom}=polygon,${coupe.slice(1).join('=')}`
    } else {
      continue
    }

    valeurs.push(donnee)
    definitions.push(`${nom}=${api.getCommandString(objet, false) || type}`)
  }

  if (comptes === 0 || comptes > reglages.max) return null
  const tot = `${valeurs.join('&&')};${definitions.join('&&')}`
  return tot.replace(/undefined/g, '')
}
