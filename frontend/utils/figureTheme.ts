/**
 * Passe DOM qui applique `adapteCouleur` aux figures d'un sous-arbre.
 *
 * Deux principes :
 *
 * - **réversible** : la couleur d'origine est mise de côté dans un attribut
 *   `data-pax-<propriété>` avant d'être remplacée, si bien qu'un retour au
 *   thème clair rend la figure exactement telle que le moteur l'a produite ;
 * - **non destructive** : on ne touche qu'aux couleurs dont le contraste
 *   l'exige, et jamais aux figures que PAX dessine lui-même (`.pax-*`), déjà
 *   écrites en variables de thème.
 */
import { adapteCouleur, versRvb, type Rvb } from './figureColors'

/** Propriétés SVG qui portent une couleur. */
const PROPRIETES = ['fill', 'stroke', 'stop-color', 'flood-color', 'lighting-color'] as const

const FOND_PAR_DEFAUT: Rvb = { r: 15, g: 23, b: 42 } // #0f172a, le fond sombre du thème

/** Le fond réel, lu dans la variable de thème — il n'est pas figé ici. */
export function fondCourant(): Rvb {
  if (typeof window === 'undefined') return FOND_PAR_DEFAUT
  const brut = getComputedStyle(document.documentElement)
    .getPropertyValue('--color-bg')
    .trim()
  return versRvb(brut) ?? FOND_PAR_DEFAUT
}

function cleDonnee(propriete: string): string {
  return `data-pax-${propriete}`
}

/** Les overlays de PAX suivent déjà le thème : on les laisse tranquilles. */
function estOverlayPax(svg: Element): boolean {
  const classes = svg.getAttribute('class') || ''
  return /\bpax-[\w-]*mark\b/.test(classes)
}

/**
 * Adapte (ou restaure) toutes les figures sous `racine`.
 *
 * Idempotent : rejouée à chaque bascule de thème, elle repart toujours de la
 * couleur d'origine mise de côté au premier passage.
 */
export function adapteFigures(racine: Element | null, sombre: boolean): void {
  if (!racine) return
  const fond = sombre ? fondCourant() : null
  const svgs: Element[] = []
  if (racine.tagName?.toLowerCase() === 'svg') svgs.push(racine)
  svgs.push(...Array.from(racine.querySelectorAll('svg')))

  for (const svg of svgs) {
    if (estOverlayPax(svg)) continue
    const elements: Element[] = [svg, ...Array.from(svg.querySelectorAll('*'))]
    for (const el of elements) {
      for (const propriete of PROPRIETES) {
        const cle = cleDonnee(propriete)
        const memorisee = el.getAttribute(cle)
        const origine = memorisee ?? el.getAttribute(propriete)
        if (origine === null) continue

        if (!sombre || !fond) {
          if (memorisee !== null) {
            el.setAttribute(propriete, memorisee)
            el.removeAttribute(cle)
          }
          continue
        }
        const adaptee = adapteCouleur(origine, fond)
        if (adaptee === null) {
          // Rien à changer : si un passage précédent avait modifié la valeur,
          // on la remet — le fond a pu changer entre-temps.
          if (memorisee !== null) {
            el.setAttribute(propriete, memorisee)
            el.removeAttribute(cle)
          }
          continue
        }
        if (memorisee === null) el.setAttribute(cle, origine)
        el.setAttribute(propriete, adaptee)
      }
    }
  }
}
