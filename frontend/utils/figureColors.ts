/**
 * Adaptation des couleurs des figures au thème sombre.
 *
 * Les figures des exercices sont des SVG produits par le moteur flydraw, avec
 * des couleurs **explicites** — l'auteur écrit `text black,…`, `arrow …,#EE0700`.
 * Sur le fond clair d'origine, elles se lisent ; sur le fond sombre du thème,
 * un tracé noir disparaît.
 *
 * Pourquoi côté client. Le rendu d'un exercice est mis en cache côté serveur et
 * partagé entre des utilisateurs qui n'ont pas le même thème : la figure servie
 * ne peut pas porter le choix de l'un d'eux. C'est donc au navigateur d'ajuster,
 * à l'affichage, et de revenir en arrière si le thème change.
 *
 * Ce que la transformation préserve. La couleur **porte du sens** dans un
 * exercice — « le vecteur rouge », « colorier en bleu ». On ne touche donc ni la
 * teinte ni la saturation : seule la clarté bouge, et seulement quand le
 * contraste avec le fond l'exige. Les gris, eux, n'ont pas de teinte à
 * préserver : on les renverse, ce qui fait du noir un blanc cassé et d'un fond
 * blanc un fond sombre.
 */

/** Couleurs qu'on ne touche jamais : elles suivent déjà le thème, ou ne sont pas des couleurs. */
const _INTOUCHABLES = new Set(['none', 'transparent', 'currentcolor', 'inherit', ''])

export interface Rvb { r: number; g: number; b: number }

/** `#rgb`, `#rrggbb` ou `rgb(r,g,b)` → composantes 0-255, ou null. */
export function versRvb(couleur: string): Rvb | null {
  const c = (couleur || '').trim().toLowerCase()
  if (_INTOUCHABLES.has(c) || c.startsWith('url(') || c.startsWith('var(')) return null
  let m = /^#([0-9a-f]{3})$/.exec(c)
  if (m) {
    const [a, b, d] = m[1].split('')
    return { r: parseInt(a + a, 16), g: parseInt(b + b, 16), b: parseInt(d + d, 16) }
  }
  m = /^#([0-9a-f]{6})$/.exec(c)
  if (m) {
    return {
      r: parseInt(m[1].slice(0, 2), 16),
      g: parseInt(m[1].slice(2, 4), 16),
      b: parseInt(m[1].slice(4, 6), 16),
    }
  }
  m = /^rgba?\(\s*([\d.]+)[\s,]+([\d.]+)[\s,]+([\d.]+)/.exec(c)
  if (m) return { r: +m[1], g: +m[2], b: +m[3] }
  return null
}

export function versHex({ r, g, b }: Rvb): string {
  const d = (x: number) => Math.round(Math.min(255, Math.max(0, x))).toString(16).padStart(2, '0')
  return `#${d(r)}${d(g)}${d(b)}`
}

/** Luminance relative WCAG — la base du rapport de contraste. */
export function luminance({ r, g, b }: Rvb): number {
  const lin = (v: number) => {
    const s = v / 255
    return s <= 0.03928 ? s / 12.92 : Math.pow((s + 0.055) / 1.055, 2.4)
  }
  return 0.2126 * lin(r) + 0.7152 * lin(g) + 0.0722 * lin(b)
}

/** Rapport de contraste WCAG entre deux couleurs (1 = identiques, 21 = noir/blanc). */
export function contraste(a: Rvb, b: Rvb): number {
  const la = luminance(a)
  const lb = luminance(b)
  return (Math.max(la, lb) + 0.05) / (Math.min(la, lb) + 0.05)
}

export function versHsl({ r, g, b }: Rvb): { h: number; s: number; l: number } {
  const rr = r / 255, gg = g / 255, bb = b / 255
  const max = Math.max(rr, gg, bb), min = Math.min(rr, gg, bb)
  const l = (max + min) / 2
  if (max === min) return { h: 0, s: 0, l }
  const d = max - min
  const s = l > 0.5 ? d / (2 - max - min) : d / (max + min)
  let h: number
  if (max === rr) h = ((gg - bb) / d + (gg < bb ? 6 : 0)) / 6
  else if (max === gg) h = ((bb - rr) / d + 2) / 6
  else h = ((rr - gg) / d + 4) / 6
  return { h, s, l }
}

export function depuisHsl(h: number, s: number, l: number): Rvb {
  if (s === 0) {
    const v = Math.round(l * 255)
    return { r: v, g: v, b: v }
  }
  const q = l < 0.5 ? l * (1 + s) : l + s - l * s
  const p = 2 * l - q
  const canal = (t: number) => {
    if (t < 0) t += 1
    if (t > 1) t -= 1
    if (t < 1 / 6) return p + (q - p) * 6 * t
    if (t < 1 / 2) return q
    if (t < 2 / 3) return p + (q - p) * (2 / 3 - t) * 6
    return p
  }
  return { r: canal(h + 1 / 3) * 255, g: canal(h) * 255, b: canal(h - 1 / 3) * 255 }
}

/** Une couleur est-elle un gris ? (saturation négligeable) */
export function estNeutre(c: Rvb): boolean {
  return Math.max(c.r, c.g, c.b) - Math.min(c.r, c.g, c.b) <= 12
}

/** Le fond est-il sombre, c'est-à-dire le papier a-t-il changé de camp ? */
export function fondEstSombre(fond: Rvb): boolean {
  return luminance(fond) < 0.2
}

/** Contraste minimal visé — le seuil AA de WCAG pour un texte normal. */
export const CONTRASTE_VISE = 4.5
/** Au-delà, une couleur saturée vire au pastel et perd son identité. */
const CLARTE_MAX = 0.78

/**
 * La couleur telle qu'elle doit s'afficher sur `fond`, ou `null` si elle
 * convient déjà. `null` est la réponse la plus fréquente et la plus utile :
 * il ne faut toucher que ce qui l'exige.
 */
export function adapteCouleur(couleur: string, fond: Rvb): string | null {
  const rvb = versRvb(couleur)
  if (!rvb) return null

  if (estNeutre(rvb)) {
    // Les gris se renversent **ensemble**, ou pas du tout. Les traiter un par
    // un selon leur contraste serait une faute : un trait noir éclairci sur un
    // aplat blanc conservé deviendrait invisible. La question n'est donc pas
    // « ce gris se lit-il ? » mais « le papier a-t-il changé de camp ? » — la
    // figure a été dessinée pour du papier blanc.
    if (!fondEstSombre(fond)) return null
    const { l } = versHsl(rvb)
    // Jamais les extrêmes : le blanc pur éblouit sur un fond sombre.
    const cible = Math.min(0.93, Math.max(0.10, 1 - l))
    return versHex(depuisHsl(0, 0, cible))
  }

  if (contraste(rvb, fond) >= CONTRASTE_VISE) return null

  // Couleur saturée trop sombre pour ce fond : on l'éclaircit à teinte et
  // saturation constantes, juste assez pour franchir le seuil.
  const { h, s, l } = versHsl(rvb)
  for (let cl = l + 0.02; cl <= CLARTE_MAX + 1e-9; cl += 0.02) {
    const essai = depuisHsl(h, s, cl)
    if (contraste(essai, fond) >= CONTRASTE_VISE) return versHex(essai)
  }
  const plafond = depuisHsl(h, s, CLARTE_MAX)
  return contraste(plafond, fond) > contraste(rvb, fond) ? versHex(plafond) : null
}
