// Le clavier mathématique : ce qu'il propose, et comment il l'insère.
//
// Sur PAX, l'élève tape sa réponse **en texte**, au format WIMS — `sqrt(2)`,
// `x^2`, `pi`, `3/7`. Ce n'est pas une formule à composer visuellement : les
// touches écrivent du texte au curseur, et c'est tout.
//
// La disposition s'inspire du clavier virtuel de MathLive, qui a fait ses
// preuves sur tablette :
// - des **onglets** thématiques plutôt qu'une planche unique, chacun d'une
//   grille régulière de dix colonnes — `123` (le quotidien : chiffres,
//   opérations, variables, délimiteurs), `f(x)` (les fonctions), `≤ ∞` (les
//   relations et les ensembles), `abc` (les lettres) ;
// - dans `123`, le pavé numérique au centre, les variables et délimiteurs à
//   gauche, les opérations à droite ;
// - une **rangée d'actions** identique d'un onglet à l'autre : les onglets,
//   les flèches, l'effacement, le masquage ;
// - une planche **complète** : ouverte au doigt, elle remplace le clavier du
//   système (le composant passe les champs en `inputmode="none"`), au lieu de
//   s'empiler dessus. D'où les chiffres et l'onglet des lettres.
//
// WIMS n'offre aucun clavier ; il n'y a pas de disposition de référence à
// respecter, seulement la syntaxe que les touches écrivent.

/** Ce qu'une touche fait, hors écriture de texte. */
export type ActionClavier =
  | 'gauche' | 'droite' | 'effacer' | 'maj'
  | 'annuler' | 'refaire' | 'coller' | 'entree'

/** Une touche. */
export interface ToucheMath {
  /** Étiquette en LaTeX, rendue par KaTeX (sinon `libelle`, en texte). */
  latex?: string
  /** Étiquette en texte simple — chiffres, lettres, noms de fonctions. */
  libelle?: string
  /** Le texte inséré, en syntaxe WIMS. */
  texte?: string
  /**
   * Recul du curseur après insertion, en caractères. Une fonction s'écrit
   * `sqrt()` et l'élève doit taper *dedans* : on le replace entre les
   * parenthèses plutôt qu'après.
   */
  recul?: number
  action?: ActionClavier
  /** Famille visuelle — le ton de la touche, pas sa couleur pleine. */
  famille?: 'chiffre' | 'operation' | 'fonction' | 'variable' | 'symbole' | 'action'
  /** Largeur, en colonnes de la grille (1 par défaut). */
  largeur?: number
  /**
   * Ce que lit un lecteur d'écran. Une clé i18n (`keyboard.*`) pour les
   * actions ; pour les touches d'écriture, le texte inséré par défaut — la
   * syntaxe même que l'élève lirait dans son champ.
   */
  aria?: string
}

export type OngletClavier = '123' | 'fx' | 'rel' | 'abc'

export const ONGLETS: { id: OngletClavier, libelle: string }[] = [
  { id: '123', libelle: '123' },
  { id: 'fx', libelle: 'f(x)' },
  { id: 'rel', libelle: '≤ ∞' },
  { id: 'abc', libelle: 'abc' },
]

const c = (x: string): ToucheMath => ({ libelle: x, texte: x, famille: 'chiffre' })
const v = (x: string): ToucheMath => ({ latex: x, texte: x, famille: 'variable' })
// Un caractère seul (`+`, `(`, `<`) s'affiche en texte : KaTeX rend un `+`
// isolé comme un opérateur binaire sans opérandes, c'est-à-dire rien.
const simple = (x: string) => /^[^\\{}^_]$/.test(x)
const op = (latex: string, texte: string, aria?: string): ToucheMath =>
  simple(latex)
    ? { libelle: latex, texte, famille: 'operation', aria: aria ?? texte }
    : { latex, texte, famille: 'operation', aria: aria ?? texte }
const fn = (libelle: string, texte: string): ToucheMath =>
  ({ libelle, texte: texte + '()', recul: 1, famille: 'fonction', aria: texte })
const sym = (latex: string, texte: string, aria?: string): ToucheMath =>
  simple(latex)
    ? { libelle: latex, texte, famille: 'symbole', aria: aria ?? texte }
    : { latex, texte, famille: 'symbole', aria: aria ?? texte }
// Une fonction dont l'étiquette est une formule à trou (`√□`, `|□|`), comme
// les touches de MathLive.
const fnx = (latex: string, texte: string): ToucheMath =>
  ({ latex, texte: texte + '()', recul: 1, famille: 'fonction', aria: texte })
const chiffres = (): ToucheMath[] => [...'1234567890'].map(c)

/**
 * Les rangées de l'onglet `123`. `decimal` est le séparateur de la langue de
 * l'exercice (`,` en français, `.` en anglais) — celui que le correcteur
 * attend, et que l'élève chercherait sinon.
 */
function onglet123(decimal: string): ToucheMath[][] {
  const autre = decimal === ',' ? '.' : ','
  // `\lbrack … \rbrack` : `[` seul passerait, mais une paire `[…;…]` est une
  // matrice pour `renderMath`, qui l'afficherait entre parenthèses.
  return [
    [v('x'), v('y'), op('(', '('), op(')', ')'), c('7'), c('8'), c('9'),
      op('\\div', '/'), op('\\square^{n}', '^'), op('\\square^{2}', '^2')],
    [v('a'), v('b'), op('\\lbrack', '['), op('\\rbrack', ']'), c('4'), c('5'), c('6'),
      op('\\times', '*'), fnx('\\sqrt{\\square}', 'sqrt'), fnx('|\\square|', 'abs')],
    [v('n'), v('t'), op('\\{', '{'), op('\\}', '}'), c('1'), c('2'), c('3'),
      op('−', '-'), sym('\\pi', 'pi'), sym('\\infty', 'infinity')],
    // `;` sépare les éléments d'une liste là où la virgule est décimale ;
    // la quatrième touche porte l'**autre** séparateur, pour ne pas montrer
    // deux virgules en français.
    [sym('<', '<'), sym('>', '>'), sym(';', ';'), sym(autre, autre),
      c('0'), c(decimal), sym('=', '='),
      op('+', '+'), sym('\\le', '<='), sym('\\ge', '>=')],
  ]
}

const ONGLET_FX: ToucheMath[][] = [
  [fn('sin', 'sin'), fn('cos', 'cos'), fn('tan', 'tan'), fn('ln', 'ln'), fn('exp', 'exp'),
    fnx('\\sqrt{\\square}', 'sqrt'), fnx('|\\square|', 'abs'),
    op('\\square^{n}', '^'), op('(', '('), op(')', ')')],
  [fn('arcsin', 'arcsin'), fn('arccos', 'arccos'), fn('arctan', 'arctan'), fn('log', 'log'),
    sym('e', 'e'), sym('\\pi', 'pi'), v('x'),
    op('\\square^{-1}', '^(-1)'), op('\\square!', '!'), op('\\square^{2}', '^2')],
  [fn('sinh', 'sinh'), fn('cosh', 'cosh'), fn('tanh', 'tanh'), fnx('\\lfloor\\square\\rfloor', 'floor'),
    fnx('\\lceil\\square\\rceil', 'ceil'), op('e^{\\square}', 'e^'), op('10^{\\square}', '10^'),
    { latex: '\\sqrt[n]{\\square}', texte: '^(1/)', recul: 1, famille: 'operation', aria: '^(1/n)' },
    fn('min', 'min'), fn('max', 'max')],
  chiffres(),
]

const ONGLET_REL: ToucheMath[][] = [
  [sym('<', '<'), sym('>', '>'), sym('\\le', '<='), sym('\\ge', '>='), sym('=', '='),
    sym('\\ne', '!='), sym('\\infty', 'infinity'), sym('-\\infty', '-infinity'),
    sym(';', ';'), sym(',', ',')],
  [op('(', '('), op(')', ')'), op('\\lbrack', '['), op('\\rbrack', ']'), op('\\{', '{'),
    op('\\}', '}'), sym('\\alpha', 'alpha'), sym('\\beta', 'beta'), sym('\\theta', 'theta'),
    sym('\\lambda', 'lambda')],
  [sym('\\mu', 'mu'), sym('\\sigma', 'sigma'), sym('\\rho', 'rho'), sym('\\omega', 'omega'),
    sym('\\varphi', 'phi'), sym('\\varepsilon', 'epsilon'), sym('\\delta', 'delta'),
    sym('\\Delta', 'Delta'), sym('\\Omega', 'Omega'), sym('\\Sigma', 'Sigma')],
  chiffres(),
]

/** Les lettres, dans la disposition du clavier de la langue. */
function ongletAbc(lang: string, maj: boolean): ToucheMath[][] {
  const azerty = lang === 'fr'
  const rangees = azerty
    ? ['azertyuiop', 'qsdfghjklm', 'wxcvbn']
    : ['qwertyuiop', 'asdfghjkl', 'zxcvbnm']
  const lettre = (l: string): ToucheMath => {
    const x = maj ? l.toUpperCase() : l
    return { libelle: x, texte: x, famille: 'variable' }
  }
  const lignes = rangees.map(r => [...r].map(lettre))
  // La troisième rangée : majuscule, lettres, puis ce qui complète les dix.
  const derniere = lignes[2] ?? []
  lignes[2] = [
    { libelle: '⇧', action: 'maj', famille: 'action', aria: 'keyboard.shift' },
    ...derniere,
    { libelle: "'", texte: "'", famille: 'symbole' },
    { libelle: '␣', texte: ' ', famille: 'symbole', aria: 'keyboard.space', largeur: 10 - derniere.length - 2 },
  ]
  return lignes
}

/** Les rangées d'un onglet. */
export function rangees(onglet: OngletClavier, lang: string, maj = false): ToucheMath[][] {
  switch (onglet) {
    case 'fx': return ONGLET_FX
    case 'rel': return ONGLET_REL
    case 'abc': return ongletAbc(lang, maj)
    default: return onglet123(separateurDecimal(lang))
  }
}

/** Les touches d'édition, dans le clavier complet seulement : la planche
 *  compacte d'un champ numérique n'a pas la place de les porter. */
export const ACTIONS_EDITION: ToucheMath[] = [
  { libelle: '↶', action: 'annuler', famille: 'action', aria: 'keyboard.undo' },
  { libelle: '↷', action: 'refaire', famille: 'action', aria: 'keyboard.redo' },
  { libelle: '⧉', action: 'coller', famille: 'action', aria: 'keyboard.paste' },
]

/** La rangée d'actions, commune à tous les onglets (hors onglets eux-mêmes). */
export const ACTIONS: ToucheMath[] = [
  { libelle: '←', action: 'gauche', famille: 'action', aria: 'keyboard.left' },
  { libelle: '→', action: 'droite', famille: 'action', aria: 'keyboard.right' },
  { libelle: '⌫', action: 'effacer', famille: 'action', aria: 'keyboard.delete' },
]

// Garder en phase avec `backend/core/oef/i18n.py` (COMMA_DECIMAL_LANGS).
const LANGUES_VIRGULE = new Set(['fr', 'nl'])

export function separateurDecimal(lang: string | undefined | null): string {
  return LANGUES_VIRGULE.has((lang || '').toLowerCase()) ? ',' : '.'
}

/** Signale au framework que le champ a changé : le navigateur ne le fait pas
 *  pour une écriture programmatique, et sans cela Vue ne verrait rien. */
function signale(champ: HTMLInputElement | HTMLTextAreaElement) {
  const h = historiques.get(champ)
  if (h) h.derniere = champ.value
  champ.dispatchEvent(new Event('input', { bubbles: true }))
  champ.focus()
}

/**
 * Écrit `touche` dans `champ`, à la position du curseur — ou exécute son
 * action. `setRangeText` remplace la sélection s'il y en a une, insère sinon.
 */
// ── Annuler / refaire ─────────────────────────────────────────────────────────
// Une écriture par programme (`setRangeText`) n'entre pas dans la pile
// d'annulation du navigateur : le clavier tient la sienne, par champ. Chaque
// frappe qui modifie le champ y dépose l'état d'avant.

interface EtatChamp { valeur: string, debut: number, fin: number }
type Champ = HTMLInputElement | HTMLTextAreaElement
const historiques = new WeakMap<Champ, { avant: EtatChamp[], apres: EtatChamp[], derniere?: string }>()
const PROFONDEUR = 100

function etat(champ: Champ): EtatChamp {
  const debut = champ.selectionStart ?? champ.value.length
  return { valeur: champ.value, debut, fin: champ.selectionEnd ?? debut }
}

function historique(champ: Champ) {
  let h = historiques.get(champ)
  if (!h) { h = { avant: [], apres: [] }; historiques.set(champ, h) }
  return h
}

function memorise(champ: Champ) {
  const h = historique(champ)
  const e = etat(champ)
  const dernier = h.avant[h.avant.length - 1]
  if (!dernier || dernier.valeur !== e.valeur) h.avant.push(e)
  if (h.avant.length > PROFONDEUR) h.avant.shift()
  h.apres.length = 0
}

function restaure(champ: Champ, e: EtatChamp) {
  champ.value = e.valeur
  champ.setSelectionRange(e.debut, e.fin)
  historique(champ).derniere = e.valeur
  signale(champ)
}

/** Annuler (`sens` = -1) ou refaire (+1) la dernière modification du clavier. */
export function annule(champ: Champ, sens: -1 | 1): void {
  const h = historique(champ)
  // L'élève a tapé au clavier de l'appareil depuis la dernière frappe du
  // nôtre : annuler revient d'abord à l'état que celle-ci avait laissé, sans
  // effacer d'un coup ce qu'il a tapé.
  if (sens < 0 && h.derniere !== undefined && champ.value !== h.derniere) {
    h.avant.push({ valeur: h.derniere, debut: h.derniere.length, fin: h.derniere.length })
    h.apres.length = 0
  }
  const [depuis, vers] = sens < 0 ? [h.avant, h.apres] : [h.apres, h.avant]
  const cible = depuis.pop()
  if (!cible) { champ.focus(); return }
  vers.push(etat(champ))
  restaure(champ, cible)
}

/** Colle `texte` au curseur — une ligne : les sauts deviennent des espaces. */
export function colle(champ: Champ, texte: string): void {
  insere(champ, { texte: texte.replace(/\s*[\r\n]+\s*/g, ' ') })
}

export function insere(champ: HTMLInputElement | HTMLTextAreaElement, touche: ToucheMath): void {
  if (touche.action === 'annuler' || touche.action === 'refaire') {
    annule(champ, touche.action === 'annuler' ? -1 : 1)
    return
  }
  const debut = champ.selectionStart ?? champ.value.length
  const fin = champ.selectionEnd ?? debut
  if (touche.action === 'gauche' || touche.action === 'droite') {
    const pos = touche.action === 'gauche'
      ? (debut === fin ? Math.max(0, debut - 1) : debut)
      : (debut === fin ? Math.min(champ.value.length, fin + 1) : fin)
    champ.setSelectionRange(pos, pos)
    champ.focus()
    return
  }
  if (touche.action === 'effacer') {
    if (debut === fin && debut === 0) return
    memorise(champ)
    if (debut !== fin) champ.setRangeText('', debut, fin, 'end')
    else if (debut > 0) champ.setRangeText('', debut - 1, debut, 'end')
    else return
    signale(champ)
    return
  }
  if (touche.texte === undefined) return
  memorise(champ)
  champ.setRangeText(touche.texte, debut, fin, 'end')
  if (touche.recul) {
    const pos = (champ.selectionStart ?? 0) - touche.recul
    champ.setSelectionRange(pos, pos)
  }
  signale(champ)
}

/**
 * L'appareil pointe-t-il grossièrement (doigt) plutôt que finement (souris) ?
 *
 * Ne décide plus de l'ouverture — la planche reste fermée tant qu'on ne la
 * demande pas —, mais de ce qu'elle fait du clavier du système : au doigt,
 * elle le remplace (`inputmode="none"`) ; à la souris, il n'y en a pas.
 */
export function pointeurGrossier(): boolean {
  if (!import.meta.client || typeof window.matchMedia !== 'function') return false
  return window.matchMedia('(pointer: coarse)').matches
}

// ── Profils : un clavier à la mesure du champ ─────────────────────────────────
//
// Le type de réponse dit ce que le champ attend ; la première page du clavier
// en suit. Mesuré sur les 21 893 réponses du corpus : les champs numériques
// (`numeric`, `numexp`) en font plus du quart, et une calculatrice leur
// suffit. MathLive fait de même (une disposition par champ).
//
// Un profil étroit ne doit jamais enfermer l'élève : un `numeric` WIMS accepte
// `2/3` ou `sqrt(2)`, d'où `√`, `π` et `/` dans le pavé, et la touche « ⋯ »
// ouvre toujours le clavier complet.

export type ProfilClavier = 'nombre' | 'ensemble' | 'texte' | 'complet'

const TYPES_NOMBRE = new Set(['numeric', 'numexp', 'integer', 'float', 'real'])
const TYPES_ENSEMBLE = new Set(['fset', 'set', 'aset', 'range', 'vector', 'matrix'])
// Des mots : le clavier de l'appareil y suffit, et la pastille n'a rien à
// proposer.
const TYPES_TEXTE = new Set(['case', 'nocase', 'atext', 'raw', 'text', 'symtext', 'wlist'])

/**
 * Le profil d'un champ d'après son type de réponse. `default` et `analyze`
 * ne disent pas ce qu'ils attendent : clavier complet. Les expressions
 * (`formal`, `algexp`…) et les unités (lettres après le nombre) aussi.
 */
export function profilPourType(type: string | undefined | null): ProfilClavier {
  const t = (type || '').toLowerCase()
  if (TYPES_NOMBRE.has(t)) return 'nombre'
  if (TYPES_ENSEMBLE.has(t)) return 'ensemble'
  if (TYPES_TEXTE.has(t)) return 'texte'
  return 'complet'
}

/** Une planche compacte : ses colonnes et ses rangées. */
export interface PlancheCompacte {
  colonnes: number
  rangees: ToucheMath[][]
}

/**
 * La planche compacte d'un profil, `null` pour le clavier complet. Une
 * calculatrice pour un nombre ; la même, flanquée des délimiteurs, pour un
 * ensemble, un intervalle ou un vecteur.
 */
export function plancheCompacte(profil: ProfilClavier, lang: string): PlancheCompacte | null {
  const decimal = separateurDecimal(lang)
  // Là où la virgule est décimale, `;` sépare les éléments (et inversement).
  const liste = decimal === ',' ? ';' : ','
  if (profil === 'nombre') {
    return {
      colonnes: 5,
      rangees: [
        [c('7'), c('8'), c('9'), op('(', '('), op(')', ')')],
        [c('4'), c('5'), c('6'), op('\\div', '/'), fnx('\\sqrt{\\square}', 'sqrt')],
        [c('1'), c('2'), c('3'), op('\\times', '*'), op('\\square^{2}', '^2')],
        [c('0'), c(decimal), op('−', '-'), op('+', '+'), sym('\\pi', 'pi')],
      ],
    }
  }
  if (profil === 'ensemble') {
    return {
      colonnes: 7,
      rangees: [
        [c('7'), c('8'), c('9'), op('\\lbrack', '['), op('\\rbrack', ']'), sym(liste, liste), sym('\\infty', 'infinity')],
        [c('4'), c('5'), c('6'), op('\\{', '{'), op('\\}', '}'), op('\\div', '/'), fnx('\\sqrt{\\square}', 'sqrt')],
        [c('1'), c('2'), c('3'), op('(', '('), op(')', ')'), op('\\times', '*'), op('\\square^{2}', '^2')],
        [c('0'), c(decimal), op('−', '-'), op('+', '+'), sym('\\pi', 'pi'), sym('<', '<'), sym('>', '>')],
      ],
    }
  }
  return null
}
