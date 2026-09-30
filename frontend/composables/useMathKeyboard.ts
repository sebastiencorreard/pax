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
  | 'annuler' | 'refaire' | 'entree' | 'vider' | 'debut' | 'fin'

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
  /** La variante sous la majuscule (virtuelle, ou celle du clavier physique). */
  maj?: ToucheMath
  /** Une case vide, pour aligner les blocs. */
  vide?: boolean
  /**
   * Taire l'indice de la variante (le petit `ⁿ√` dans le coin de `√`) : la
   * variante reste sous la majuscule, mais l'annoncer sur la touche prêterait
   * à confusion — une racine n-ième lue au-dessus d'une racine carrée, un
   * exposant au-dessus de chaque chiffre.
   */
  discret?: boolean
}

export type OngletClavier = '123' | 'fx' | 'abc' | 'grec'

// Les onglets de MathLive, ramenés à ce que la syntaxe WIMS écrit : l'onglet
// des relations a disparu, ses touches vivent désormais sous la majuscule.
export const ONGLETS: { id: OngletClavier, libelle: string }[] = [
  { id: '123', libelle: '123' },
  { id: 'fx', libelle: 'f(x)' },
  { id: 'abc', libelle: 'abc' },
  { id: 'grec', libelle: 'αβγ' },
]

const c = (x: string): ToucheMath => ({ libelle: x, texte: x, famille: 'chiffre' })
const v = (x: string): ToucheMath => ({ latex: x, texte: x, famille: 'variable' })
// Un caractère seul (`+`, `(`, `<`) s'affiche en texte : KaTeX rend un `+`
// isolé comme un opérateur binaire sans opérandes, c'est-à-dire rien.
const simple = (x: string) => /^[^\\^_]$/.test(x)
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
// La réciproque, notée `cos⁻¹` comme sur une calculatrice ; elle écrit la
// fonction que WIMS connaît (`arccos`) — `cos^-1(x)` y serait une puissance.
// L'étiquette en texte (`cos⁻¹`), sans empattement comme `sin` et `ln`.
const recip = (nom: string): ToucheMath =>
  ({ libelle: `${nom}⁻¹`, texte: `arc${nom}()`, recul: 1, famille: 'fonction', aria: `arc${nom}` })
/** `t`, et sa variante sous la majuscule. */
const m = (t: ToucheMath, maj: ToucheMath): ToucheMath => ({ ...t, maj })
const discret = (t: ToucheMath): ToucheMath => ({ ...t, discret: true })
const VIDE: ToucheMath = { vide: true }
const EXPOSANTS = ['⁰', '¹', '²', '³', '⁴', '⁵', '⁶', '⁷', '⁸', '⁹']

const MAJ: ToucheMath = { libelle: '⇧', action: 'maj', famille: 'action', aria: 'keyboard.shift', largeur: 2 }
// Sous la majuscule, les flèches vont au début et à la fin du champ.
const GAUCHE: ToucheMath = {
  libelle: '‹', action: 'gauche', famille: 'action', aria: 'keyboard.left', discret: true,
  maj: { libelle: '⇤', action: 'debut', famille: 'action', aria: 'keyboard.home' },
}
const DROITE: ToucheMath = {
  libelle: '›', action: 'droite', famille: 'action', aria: 'keyboard.right', discret: true,
  maj: { libelle: '⇥', action: 'fin', famille: 'action', aria: 'keyboard.end' },
}
// Sous la majuscule, « retour arrière » devient « effacer le champ ».
const VIDER: ToucheMath = { libelle: '🗑', action: 'vider', famille: 'action', aria: 'keyboard.clear' }
const EFFACER: ToucheMath = { libelle: '⌫', action: 'effacer', famille: 'action', aria: 'keyboard.delete', maj: VIDER, discret: true }
const ENTREE: ToucheMath = { libelle: '↵', action: 'entree', famille: 'action', aria: 'keyboard.enter' }
const NTH_RACINE: ToucheMath =
  { latex: '\\sqrt[n]{\\square}', texte: '^(1/)', recul: 1, famille: 'operation', aria: '^(1/n)' }

/** Une disposition : ses colonnes (gabarit CSS) et ses rangées. */
export interface Disposition {
  colonnes: string
  rangees: ToucheMath[][]
}

// Dix colonnes égales, ou trois blocs séparés d'un filet (`123`, comme
// MathLive : variables · pavé · puissances et navigation).
const DIX = 'repeat(10, minmax(0, 1fr))'
const TROIS_BLOCS = 'repeat(2, minmax(0, 1fr)) 0.4rem repeat(4, minmax(0, 1fr)) 0.4rem repeat(3, minmax(0, 1fr))'

/**
 * L'onglet `123`, à la manière de MathLive. `decimal` est le séparateur de la
 * langue de l'interface (`,` en français) ; l'autre est sous sa majuscule.
 */
function onglet123(decimal: string): Disposition {
  const autre = decimal === ',' ? '.' : ','
  const liste = decimal === ',' ? ';' : ','
  // Sous la majuscule, un chiffre devient la puissance correspondante :
  // `2` → `^2`, comme la rangée des exposants de MathLive.
  // L'exposant en texte (`◻⁷`), sans empattement comme le chiffre lui-même.
  const ch = (n: string) => discret(m(c(n), { libelle: '◻' + EXPOSANTS[Number(n)], texte: `^${n}`, famille: 'operation', aria: `^${n}` }))
  return {
    colonnes: TROIS_BLOCS,
    rangees: [
      [m(v('x'), v('y')), m(v('n'), v('t')), VIDE,
        ch('7'), ch('8'), ch('9'), op('÷', '/'), VIDE,
        m(sym('e', 'e'), fn('ln', 'ln')), sym('\\pi', 'pi'),
        discret(m(fnx('\\sqrt{\\square}', 'sqrt'), NTH_RACINE))],
      [m(sym('<', '<'), sym('≤', '<=')), m(sym('>', '>'), sym('≥', '>=')), VIDE,
        ch('4'), ch('5'), ch('6'), op('×', '*'), VIDE,
        discret(m(op('\\square^{2}', '^2'), op('\\square^{3}', '^3'))),
        discret(m(op('\\square^{n}', '^'), op('\\square^{-1}', '^(-1)'))),
        discret(m(fnx('|\\square|', 'abs'), op('\\square!', '!')))],
      [m(op('(', '('), op('[', '[')), m(op(')', ')'), op(']', ']')), VIDE,
        ch('1'), ch('2'), ch('3'), op('−', '-'), VIDE,
        m(sym(liste, liste), sym(':', ':')), m(sym('\\infty', 'infinity'), sym('-\\infty', '-infinity')),
        EFFACER],
      [MAJ, VIDE,
        ch('0'), m(c(decimal), c(autre)), m(sym('=', '='), sym('≠', '!=')), op('+', '+'), VIDE,
        GAUCHE, DROITE, ENTREE],
    ],
  }
}

/** L'onglet des fonctions : les réciproques (`sin⁻¹`) sous la majuscule. */
function ongletFx(): Disposition {
  return {
    colonnes: 'repeat(9, minmax(0, 1fr))',
    rangees: [
      [m(fn('sin', 'sin'), recip('sin')), m(fn('ln', 'ln'), fn('log', 'log')),
        m(fnx('|\\square|', 'abs'), op('\\square!', '!')),
        discret(m(fnx('\\sqrt{\\square}', 'sqrt'), NTH_RACINE)),
        m(op('\\square^{n}', '^'), op('\\square^{-1}', '^(-1)')),
        m(op('(', '('), op('[', '[')), m(op(')', ')'), op(']', ']')),
        op('{', '{'), op('}', '}')],
      [m(fn('cos', 'cos'), recip('cos')), m(fn('exp', 'exp'), op('e^{\\square}', 'e^')),
        m(fn('min', 'min'), fn('max', 'max')),
        sym('e', 'e'), sym('\\pi', 'pi'), m(sym('\\infty', 'infinity'), sym('-\\infty', '-infinity')),
        m(sym('<', '<'), sym('≤', '<=')), m(sym('>', '>'), sym('≥', '>=')),
        m(sym('=', '='), sym('≠', '!='))],
      [m(fn('tan', 'tan'), recip('tan')), op('10^{\\square}', '10^'),
        m(v('x'), v('y')), m(v('n'), v('t')), m(v('a'), v('b')), v('i'),
        m(sym(';', ';'), sym(',', ',')), { ...EFFACER, largeur: 2 }],
      [MAJ, op('+', '+'), op('−', '-'), op('×', '*'), op('÷', '/'),
        GAUCHE, DROITE, ENTREE],
    ],
  }
}

/** Les lettres, dans la disposition du clavier de la langue ; la majuscule
 *  donne les capitales. */
function ongletAbc(lang: string): Disposition {
  const azerty = lang === 'fr'
  const [r1, r2, r3] = azerty
    ? ['azertyuiop', 'qsdfghjklm', 'wxcvbn']
    : ['qwertyuiop', 'asdfghjkl', 'zxcvbnm']
  // Pas d'indice sur les lettres : qu'une lettre ait sa capitale va de soi.
  const lettre = (l: string): ToucheMath => discret(
    m({ libelle: l, texte: l, famille: 'variable' }, { libelle: l.toUpperCase(), texte: l.toUpperCase(), famille: 'variable' }))
  const ligne = (r: string) => [...r].map(lettre)
  const l2 = ligne(r2)
  const l3 = ligne(r3)
  return {
    colonnes: DIX,
    rangees: [
      ligne(r1),
      l2.length < 10 ? [...l2, sym("'", "'")] : l2,
      [{ ...MAJ, largeur: 1 }, ...l3, ...(l3.length < 7 ? [sym("'", "'")] : []), { ...EFFACER, largeur: 2 }],
      [m(op('(', '('), op('[', '[')), m(op(')', ')'), op(']', ']')), op('+', '+'), op('−', '-'),
        { libelle: '␣', texte: ' ', famille: 'symbole', aria: 'keyboard.space', largeur: 2 },
        sym(',', ','), GAUCHE, DROITE, ENTREE],
    ],
  }
}

/** Les lettres grecques ; la majuscule donne les capitales qui existent en
 *  propre (Γ, Δ, Θ…). WIMS les écrit par leur nom. */
function ongletGrec(): Disposition {
  // Toutes les minuscules ont leur capitale sous la majuscule. Celles qui
  // s'écrivent comme une capitale latine (Α, Β, Ε, Ζ, Η, Μ, Ν, Ρ, Τ, Χ) n'ont
  // pas de commande LaTeX : on les montre en capitale droite, comme le veut la
  // typographie grecque. Toutes écrivent leur nom, `Alpha` comme `Gamma`.
  const LATINES: Record<string, string> = {
    alpha: 'A', beta: 'B', varepsilon: 'E', zeta: 'Z', eta: 'H',
    mu: 'M', nu: 'N', rho: 'P', tau: 'T', chi: 'X',
  }
  const g = (min: string): ToucheMath => {
    const nom = min.replace(/^var/, '')
    const Nom = nom[0]!.toUpperCase() + nom.slice(1)
    const latine = LATINES[min]
    const capitale = latine
      ? sym(`\\mathrm{${latine}}`, Nom)
      : sym(`\\${Nom}`, Nom)
    return discret(m(sym(`\\${min}`, nom), capitale))
  }
  return {
    colonnes: DIX,
    rangees: [
      [g('alpha'), g('beta'), g('gamma'), g('delta'), g('varepsilon'),
        g('zeta'), g('eta'), g('theta'), g('lambda'), g('mu')],
      [g('nu'), g('xi'), g('pi'), g('rho'), g('sigma'), g('tau'),
        g('varphi'), g('chi'), g('psi'), g('omega')],
      [m(op('(', '('), op('[', '[')), m(op(')', ')'), op(']', ']')),
        m(sym('=', '='), sym('≠', '!=')), op('+', '+'), op('−', '-'), op('×', '*'),
        op('÷', '/'), op('\\square^{n}', '^'), { ...EFFACER, largeur: 2 }],
      [MAJ, VIDE, VIDE, VIDE, VIDE, VIDE, GAUCHE, DROITE, ENTREE],
    ],
  }
}

/** La disposition d'un onglet. */
export function disposition(onglet: OngletClavier, lang: string): Disposition {
  switch (onglet) {
    case 'fx': return ongletFx()
    case 'abc': return ongletAbc(lang)
    case 'grec': return ongletGrec()
    default: return onglet123(separateurDecimal(lang))
  }
}

/** Les touches d'édition, dans le clavier complet seulement : la planche
 *  compacte d'un champ numérique n'a pas la place de les porter. */
export const ACTIONS_EDITION: ToucheMath[] = [
  { libelle: '↶', action: 'annuler', famille: 'action', aria: 'keyboard.undo' },
  { libelle: '↷', action: 'refaire', famille: 'action', aria: 'keyboard.redo' },
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

export function insere(champ: HTMLInputElement | HTMLTextAreaElement, touche: ToucheMath): void {
  if (touche.action === 'annuler' || touche.action === 'refaire') {
    annule(champ, touche.action === 'annuler' ? -1 : 1)
    return
  }
  const debut = champ.selectionStart ?? champ.value.length
  const fin = champ.selectionEnd ?? debut
  if (touche.action === 'debut' || touche.action === 'fin') {
    const pos = touche.action === 'debut' ? 0 : champ.value.length
    champ.setSelectionRange(pos, pos)
    champ.focus()
    return
  }
  if (touche.action === 'gauche' || touche.action === 'droite') {
    const pos = touche.action === 'gauche'
      ? (debut === fin ? Math.max(0, debut - 1) : debut)
      : (debut === fin ? Math.min(champ.value.length, fin + 1) : fin)
    champ.setSelectionRange(pos, pos)
    champ.focus()
    return
  }
  if (touche.action === 'vider') {
    if (!champ.value) return
    memorise(champ)
    champ.setRangeText('', 0, champ.value.length, 'end')
    signale(champ)
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
        [c('4'), c('5'), c('6'), op('÷', '/'), fnx('\\sqrt{\\square}', 'sqrt')],
        [c('1'), c('2'), c('3'), op('×', '*'), op('\\square^{2}', '^2')],
        [c('0'), c(decimal), op('−', '-'), op('+', '+'), sym('\\pi', 'pi')],
      ],
    }
  }
  if (profil === 'ensemble') {
    return {
      colonnes: 7,
      rangees: [
        [c('7'), c('8'), c('9'), op('[', '['), op(']', ']'), sym(liste, liste), sym('\\infty', 'infinity')],
        [c('4'), c('5'), c('6'), op('{', '{'), op('}', '}'), op('÷', '/'), fnx('\\sqrt{\\square}', 'sqrt')],
        [c('1'), c('2'), c('3'), op('(', '('), op(')', ')'), op('×', '*'), op('\\square^{2}', '^2')],
        [c('0'), c(decimal), op('−', '-'), op('+', '+'), sym('\\pi', 'pi'), sym('<', '<'), sym('>', '>')],
      ],
    }
  }
  return null
}
