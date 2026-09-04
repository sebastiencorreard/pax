// Le clavier mathématique : ce qu'il propose, et comment il l'insère.
//
// Le besoin est modeste et il vaut d'être posé, parce qu'il gouverne tout le
// reste : sur PAX, l'élève tape sa réponse **en texte**, au format WIMS —
// `sqrt(2)`, `x^2`, `pi`, `3/7`. Ce n'est pas une formule à composer
// visuellement. Le problème est celui du clavier tactile, où `^`, `/`, `_` et
// les parenthèses vivent dans des sous-menus : il faut une vingtaine de
// touches qui écrivent le bon caractère au curseur, pas un éditeur d'équations.
//
// WIMS n'offre aucun clavier ; il n'y a donc pas de disposition de référence à
// suivre, et celle-ci se juge sur le seul usage.
//
// **Ce fichier est prévu pour survivre à son composant.** Le passage éventuel
// à MathLive changerait le champ de saisie (un `<math-field>` qui rend du
// LaTeX) et le rendu du clavier, pas la liste de ce qu'un élève a besoin
// d'écrire : les touches ci-dessous garderaient leur sens, seul `insere`
// deviendrait caduc.

/** Une touche : ce qu'on y lit, ce qu'elle écrit, où va le curseur ensuite. */
export interface ToucheMath {
  /** L'étiquette, en LaTeX — KaTeX est déjà chargé pour les énoncés. */
  latex: string
  /** Le texte inséré, en syntaxe WIMS. */
  texte: string
  /**
   * Recul du curseur après insertion, en caractères. Une fonction s'écrit
   * `sqrt()` et l'élève doit taper *dedans* : on le replace entre les
   * parenthèses plutôt qu'après.
   */
  recul?: number
  /** Regroupement visuel, pour aérer la grille. */
  groupe: 'operation' | 'fonction' | 'symbole'
}

/**
 * La disposition par défaut.
 *
 * Choisie sur ce qui coûte cher au doigt et revient souvent dans le corpus :
 * les puissances et les racines (`algexp`, `litexp`), les fractions, les
 * comparateurs des intervalles, et les délimiteurs que les ensembles-solutions
 * réclament (`{`, `}` pour un `fset`, `[`, `]` pour un `range`).
 *
 * Volontairement courte : une planche de vingt touches se lit d'un coup d'œil,
 * là où un clavier complet oblige à chercher — et ce qui manque reste
 * accessible au clavier de l'appareil, qui n'a pas disparu.
 */
export const CLAVIER_DEFAUT: ToucheMath[] = [
  { latex: 'x^{n}', texte: '^', groupe: 'operation' },
  { latex: '\\frac{a}{b}', texte: '/', groupe: 'operation' },
  { latex: '\\times', texte: '*', groupe: 'operation' },
  { latex: '(\\;)', texte: '()', recul: 1, groupe: 'operation' },
  { latex: '[\\;]', texte: '[]', recul: 1, groupe: 'operation' },
  { latex: '\\{\\;\\}', texte: '{}', recul: 1, groupe: 'operation' },

  { latex: '\\sqrt{\\;}', texte: 'sqrt()', recul: 1, groupe: 'fonction' },
  { latex: '|a|', texte: 'abs()', recul: 1, groupe: 'fonction' },
  { latex: '\\exp', texte: 'exp()', recul: 1, groupe: 'fonction' },
  { latex: '\\ln', texte: 'ln()', recul: 1, groupe: 'fonction' },
  { latex: '\\cos', texte: 'cos()', recul: 1, groupe: 'fonction' },
  { latex: '\\sin', texte: 'sin()', recul: 1, groupe: 'fonction' },

  { latex: '\\pi', texte: 'pi', groupe: 'symbole' },
  { latex: '\\infty', texte: 'infinity', groupe: 'symbole' },
  { latex: '\\le', texte: '<=', groupe: 'symbole' },
  { latex: '\\ge', texte: '>=', groupe: 'symbole' },
  { latex: '\\ne', texte: '!=', groupe: 'symbole' },
  { latex: ';', texte: ';', groupe: 'symbole' },
]

/**
 * Écrit `touche` dans `champ`, à la position du curseur.
 *
 * `setRangeText` fait tout le travail — remplacer la sélection s'il y en a
 * une, insérer sinon — et laisse le champ modifiable derrière lui. L'événement
 * `input` est déclenché à la main : le navigateur ne l'émet pas pour une
 * écriture programmatique, et sans lui Vue ne verrait jamais la réponse
 * changer.
 */
export function insere(champ: HTMLInputElement | HTMLTextAreaElement, touche: ToucheMath): void {
  const debut = champ.selectionStart ?? champ.value.length
  const fin = champ.selectionEnd ?? debut
  champ.setRangeText(touche.texte, debut, fin, 'end')
  if (touche.recul) {
    const pos = (champ.selectionStart ?? 0) - touche.recul
    champ.setSelectionRange(pos, pos)
  }
  champ.dispatchEvent(new Event('input', { bubbles: true }))
  champ.focus()
}

/**
 * L'appareil pointe-t-il grossièrement (doigt) plutôt que finement (souris) ?
 *
 * C'est le critère qui décide de l'ouverture automatique : sur un ordinateur,
 * le clavier physique suffit et une planche permanente encombre l'énoncé ;
 * sur tablette, c'est l'inverse. `pointer: coarse` répond exactement à cette
 * question, là où une détection par la taille de l'écran se tromperait sur un
 * portable tactile.
 */
export function pointeurGrossier(): boolean {
  if (!import.meta.client || typeof window.matchMedia !== 'function') return false
  return window.matchMedia('(pointer: coarse)').matches
}
