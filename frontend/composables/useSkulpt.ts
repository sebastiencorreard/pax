// Charge Skulpt depuis un CDN et exécute le programme Python de l'élève dans
// le navigateur. Même forme que `useCodemirror` et `useJsxgraph` : rien n'est
// vendorisé, tout vient du réseau à la demande.
//
// C'est le type `runcode` qui l'emploie — huit modules d'`H4/programming` le
// définissent, et leur `.input` déclare `ans_require=skulpt,codemirror`. Le
// choix de Skulpt ne nous appartient pas : il est inscrit dans les exercices,
// jusque dans la façon dont ils relèvent les variables
// (`Sk.ffi.remapToJs(Sk.globals["…"])`).
//
// Skulpt est un interpréteur Python 3 **en JavaScript** : le code de l'élève
// ne quitte jamais son navigateur, et le serveur ne reçoit que les valeurs des
// variables — c'est tout ce que le correcteur compare.

const SKULPT_VERSION = '1.2.0'
const CDN = `https://cdn.jsdelivr.net/npm/skulpt@${SKULPT_VERSION}/dist`

interface SkulptNs {
  configure: (options: Record<string, unknown>) => void
  importMainWithBody: (name: string, dump: boolean, body: string, canSuspend: boolean) => unknown
  misceval: { asyncToPromise: (fn: () => unknown) => Promise<unknown> }
  builtinFiles?: { files: Record<string, string> }
  globals?: Record<string, unknown>
  ffi: { remapToJs: (v: unknown) => unknown }
  python3?: unknown
  TurtleGraphics?: { target?: string }
}

function skulptNs(): SkulptNs | null {
  return (window as unknown as { Sk?: SkulptNs }).Sk ?? null
}

let loadPromise: Promise<void> | null = null

function loadScript(src: string): Promise<void> {
  return new Promise<void>((resolve, reject) => {
    const s = document.createElement('script')
    s.src = src
    s.async = false // le noyau avant la bibliothèque standard
    s.onload = () => resolve()
    s.onerror = () => reject(new Error(`Skulpt asset failed: ${src}`))
    document.head.appendChild(s)
  })
}

export function loadSkulpt(): Promise<void> {
  if (!import.meta.client) return Promise.resolve()
  if (skulptNs()?.importMainWithBody) return Promise.resolve()
  if (loadPromise) return loadPromise
  // `skulpt-stdlib.js` porte les modules Python (`math`, `random`, `turtle`) ;
  // sans lui, tout `import` du programme échoue.
  loadPromise = loadScript(`${CDN}/skulpt.min.js`)
    .then(() => loadScript(`${CDN}/skulpt-stdlib.js`))
  return loadPromise
}

export interface ResultatExecution {
  /** Ce que le programme a affiché — le `print` de Python. */
  sortie: string
  /** L'erreur levée, s'il y en a une. */
  erreur: string | null
  /** Les variables demandées, dans l'ordre, telles que Skulpt les rend. */
  valeurs: unknown[]
}

/**
 * Exécute `code` et relève les variables nommées.
 *
 * Le port de `playcode()` et de `capture()`, que le slib et le `.input` du
 * module injectent chacun de leur côté dans la page WIMS. La sortie standard
 * est captée par la fonction `output` que `Sk.configure` réclame, et les
 * variables sont lues **après** coup dans `Sk.globals`, converties en valeurs
 * JavaScript par `Sk.ffi.remapToJs` — un entier Python devient un nombre, une
 * liste une liste.
 *
 * Une erreur d'exécution n'est pas un échec du dispositif : c'est une réponse
 * fausse, et l'élève doit la lire. On la rend plutôt que de la lever.
 */
export async function executerPython(
  code: string,
  variables: string[],
): Promise<ResultatExecution> {
  await loadSkulpt()
  const Sk = skulptNs()
  if (!Sk) return { sortie: '', erreur: 'Skulpt indisponible', valeurs: [] }

  let sortie = ''
  Sk.configure({
    output: (texte: string) => { sortie += texte },
    read: (x: string) => {
      const f = Sk.builtinFiles?.files[x]
      if (f === undefined) throw new Error(`File not found: '${x}'`)
      return f
    },
    __future__: Sk.python3,
  })

  let erreur: string | null = null
  try {
    await Sk.misceval.asyncToPromise(
      () => Sk.importMainWithBody('<stdin>', false, code, true),
    )
  } catch (e) {
    erreur = String((e as { toString?: () => string })?.toString?.() ?? e)
  }

  const valeurs = variables.map(nom => {
    // `print` n'est pas une variable : le module s'en sert pour désigner la
    // **sortie** du programme, et c'est elle qu'il faut alors comparer.
    if (nom === 'print') return sortie.replace(/\n/g, ':')
    try {
      const v = Sk.globals?.[nom]
      return v === undefined ? '' : Sk.ffi.remapToJs(v)
    } catch {
      return ''
    }
  })
  return { sortie, erreur, valeurs }
}

/**
 * La réponse dans la forme que le correcteur attend.
 *
 * `capture()` compose `"["+sc+"],"` puis `"["+variable+"],"` pour chacune —
 * un tableau JavaScript s'y interpole de lui-même en `1,2,3`, ce dont le
 * découpage en items du serveur tient compte. Les sauts de ligne du code
 * deviennent `@@@@`, faute de quoi ils couperaient la réponse en morceaux.
 */
export function composerReponseRuncode(code: string, valeurs: unknown[]): string {
  const source = code.replace(/\n/g, '@@@@')
  return [`[${source}]`, ...valeurs.map(v => `[${v}]`)].join(',')
}

/**
 * Les mots-clés que l'exercice exige dans le code (option `keyword_python`).
 *
 * Le module en fait un test JavaScript (`/for/igm.test(sc)`) et refuse
 * d'envoyer la réponse quand il manque : « sers-toi d'une boucle `for` » n'est
 * pas une suggestion. Rend le premier mot absent, ou `null`.
 */
export function motCleManquant(code: string, mots: string[]): string | null {
  for (const mot of mots) {
    if (!mot.trim()) continue
    if (!new RegExp(mot.trim(), 'im').test(code)) return mot.trim()
  }
  return null
}
