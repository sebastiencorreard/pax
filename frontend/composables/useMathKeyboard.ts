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
export type ActionClavier = 'gauche' | 'droite' | 'effacer' | 'maj'

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
  champ.dispatchEvent(new Event('input', { bubbles: true }))
  champ.focus()
}

/**
 * Écrit `touche` dans `champ`, à la position du curseur — ou exécute son
 * action. `setRangeText` remplace la sélection s'il y en a une, insère sinon.
 */
export function insere(champ: HTMLInputElement | HTMLTextAreaElement, touche: ToucheMath): void {
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
    if (debut !== fin) champ.setRangeText('', debut, fin, 'end')
    else if (debut > 0) champ.setRangeText('', debut - 1, debut, 'end')
    else return
    signale(champ)
    return
  }
  if (touche.texte === undefined) return
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
