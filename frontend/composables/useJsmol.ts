// Charge JSmol une fois, puis construit les applets Jmol des énoncés.
//
// Même forme que `useJsxgraph` : la bibliothèque vient du réseau, la
// configuration vient du serveur (segment `jmol`, écrit par
// `slib/chemistry/jmolshow` côté moteur .def).
//
// **Pourquoi pas un vrai CDN.** JSmol n'est ni sur cdnjs ni sur jsdelivr : le
// paquet npm `jsmol` est un chargeur de 1,4 Ko qui va lui-même chercher le
// fichier sur jmol.sourceforge.net. On s'adresse donc directement à l'hôte du
// projet Jmol, en HTTPS. Ce n'est pas seulement `JSmol.min.js` qui compte :
// le mode HTML5 charge ses classes à la demande sous `j2s/`, et cet arbre-là
// doit être servi par quelqu'un. C'est aussi l'hôte que le slib WIMS désigne
// (`serverURL: chemapps.stolaf.edu/jmol/jsmol/php/jsmol.php`).
//
// Tout est regroupé dans `JSMOL_BASE` : vendoriser JSmol un jour — la licence
// LGPL le permet — se réduit à changer cette constante.

const JSMOL_BASE = 'https://chemapps.stolaf.edu/jmol/jsmol'

export interface JmolConfig {
  id: string
  width: number
  height: number
  color: string
  /** Le modèle, inline (`.xyz` d'un polyèdre, `.pdb` d'une molécule). */
  data?: string
  /** La commande `load` quand il n'y a pas de modèle inline (voie cactus). */
  load?: string
  /** Le service qui résout un identifiant chimique, interrogé par l'applet. */
  loadFormat?: string
  /** Les commandes Jmol à passer après le chargement. */
  script?: string
}

interface JmolNamespace {
  setDocument: (doc: unknown) => void
  getApplet: (id: string, info: Record<string, unknown>) => unknown
  getAppletHtml: (applet: unknown) => string
  script: (applet: unknown, script: string) => void
}

function jmolNs(): JmolNamespace | null {
  return (window as unknown as { Jmol?: JmolNamespace }).Jmol ?? null
}

let loadPromise: Promise<void> | null = null

export function loadJsmol(): Promise<void> {
  if (!import.meta.client) return Promise.resolve()
  if (jmolNs()) return Promise.resolve()
  if (loadPromise) return loadPromise
  loadPromise = new Promise<void>((resolve, reject) => {
    const script = document.createElement('script')
    script.src = `${JSMOL_BASE}/JSmol.min.js`
    script.async = true
    script.onload = () => resolve()
    script.onerror = () => reject(new Error('JSmol failed to load'))
    document.head.appendChild(script)
  })
  return loadPromise
}

/**
 * Construit une applet Jmol dans `el`, d'après la configuration du serveur.
 *
 * `Jmol.setDocument(false)` est la clef : sans lui, `getApplet` écrit son HTML
 * par `document.write`, ce qui après le chargement de la page efface le
 * document. On récupère donc le HTML et on l'insère soi-même.
 */
export async function mountJmol(el: HTMLElement, cfg: JmolConfig): Promise<void> {
  if (!import.meta.client) return
  await loadJsmol()
  const Jmol = jmolNs()
  if (!Jmol) throw new Error('JSmol namespace missing after load')

  const info: Record<string, unknown> = {
    width: cfg.width,
    height: cfg.height,
    color: cfg.color || 'white',
    use: 'HTML5',
    j2sPath: `${JSMOL_BASE}/j2s`,
    serverURL: `${JSMOL_BASE}/php/jsmol.php`,
    // Les molécules d'`oefmolecule` arrivent en SMILES : c'est l'applet qui
    // les résout, via le service que le serveur a nommé dans `loadFormat`.
    script: [
      cfg.loadFormat ? `set loadFormat "${cfg.loadFormat}";` : '',
      cfg.load ?? '',
    ].filter(Boolean).join(' '),
    disableInitialConsole: true,
    disableJ2SLoadMonitor: true,
    debug: false,
  }

  // L'applet s'initialise en **asynchrone** : insérer son HTML ne suffit pas,
  // et tout `loadInline` lancé dans la foulée se perd sans un mot dans la
  // console. `readyFunction` est le rendez-vous que JSmol donne pour cela —
  // le slib WIMS le prend aussi (`readyFunction: jmol_isReady`).
  let applet: unknown = null
  const pret = new Promise<void>(resolve => {
    info.readyFunction = () => resolve()
  })

  Jmol.setDocument(false)
  applet = Jmol.getApplet(cfg.id, info)
  el.innerHTML = Jmol.getAppletHtml(applet)

  await pret

  // Le modèle voyage **dans le script**, en bloc `load DATA "…" … end "…"` :
  // c'est la seule voie inline que JSmol expose vraiment. Le namespace
  // annonce bien un `loadInline`, mais il n'est pas sur `Jmol` — seulement
  // sur l'objet applet des vieilles API —, et l'appeler lève
  // « Jmol.loadInline is not a function ».
  //
  // Le délimiteur est volontairement improbable : il ne doit apparaître nulle
  // part dans un `.xyz` ni dans un `.pdb`, sans quoi il clôturerait le bloc
  // au milieu du modèle.
  const commandes: string[] = []
  if (cfg.data) {
    commandes.push(`load DATA "paxmodel"\n${cfg.data}\nend "paxmodel";`)
  }
  if (cfg.script) commandes.push(cfg.script)
  if (commandes.length) Jmol.script(applet, commandes.join('\n'))
}

/**
 * Hydrate les marqueurs `.pax-jmol` d'un fragment d'énoncé rendu en `v-html`.
 *
 * Les trois exercices de chimie posent leurs molécules dans un `<table>`, et
 * un tableau reste un seul segment HTML — le découpage le briserait. Ses
 * widgets ne peuvent donc pas être des composants Vue ; ils sont hydratés
 * après coup, comme le sont déjà les champs et les cases à cocher en tableau.
 */
export function hydrateJmolMarkers(root: HTMLElement): void {
  root.querySelectorAll<HTMLElement>('.pax-jmol[data-jmol]').forEach(el => {
    if (el.dataset.jmolMounted === '1') return
    const brut = el.getAttribute('data-jmol')
    if (!brut) return
    let cfg: JmolConfig
    try {
      cfg = JSON.parse(brut)
    } catch {
      return
    }
    el.dataset.jmolMounted = '1'
    mountJmol(el, cfg).catch(e => console.error('Jmol applet init failed', e))
  })
}
