import { test, expect } from '@playwright/test'
import {
  adapteCouleur, contraste, versRvb, estNeutre, CONTRASTE_VISE,
} from '../utils/figureColors'

const FOND_SOMBRE = { r: 15, g: 23, b: 42 }   // #0f172a
const FOND_CLAIR = { r: 248, g: 250, b: 252 } // #f8fafc

// La transformation elle-même : elle tourne en Node, sans navigateur.
test.describe('adaptation des couleurs de figure', () => {
  test('un gris se renverse', () => {
    // Le noir d'un tracé devient un blanc cassé — jamais le blanc pur, qui
    // éblouit sur un fond sombre.
    const noir = adapteCouleur('#000000', FOND_SOMBRE)!
    expect(noir).toBeTruthy()
    expect(contraste(versRvb(noir)!, FOND_SOMBRE)).toBeGreaterThan(CONTRASTE_VISE)
    expect(estNeutre(versRvb(noir)!)).toBe(true)

    // Un aplat blanc devient un fond sombre.
    const blanc = versRvb(adapteCouleur('#ffffff', FOND_SOMBRE)!)!
    expect(blanc.r).toBeLessThan(60)
  })

  test('une couleur saturée garde sa teinte', () => {
    // Un bleu marine est illisible sur fond sombre : on l'éclaircit, sans le
    // dénaturer — « le vecteur bleu » doit rester bleu.
    const marine = '#00008b'
    expect(contraste(versRvb(marine)!, FOND_SOMBRE)).toBeLessThan(CONTRASTE_VISE)
    const adapte = versRvb(adapteCouleur(marine, FOND_SOMBRE)!)!
    expect(contraste(adapte, FOND_SOMBRE)).toBeGreaterThanOrEqual(CONTRASTE_VISE)
    expect(adapte.b).toBeGreaterThan(adapte.r)
    expect(adapte.b).toBeGreaterThan(adapte.g)
  })

  test('une couleur déjà lisible n’est pas touchée', () => {
    // `null` est la réponse la plus fréquente, et la plus importante : une
    // figure qui se lit déjà ne doit pas changer d'aspect.
    expect(adapteCouleur('#ffff00', FOND_SOMBRE)).toBeNull()   // jaune, contraste 16,6
    expect(adapteCouleur('#ff6b6b', FOND_SOMBRE)).toBeNull()   // rouge clair, 7,0
  })

  test('les gris se renversent ensemble, ou pas du tout', () => {
    // Le piège : traiter chaque gris selon son propre contraste. Le blanc a
    // 17 de contraste sur fond sombre — il « se lit » —, mais le conserver
    // pendant qu'on éclaircit les traits noirs les rendrait invisibles sur
    // lui. C'est le papier qui décide, pas chaque couleur.
    expect(adapteCouleur('#000000', FOND_SOMBRE)).not.toBeNull()
    expect(adapteCouleur('#ffffff', FOND_SOMBRE)).not.toBeNull()
    expect(adapteCouleur('#000000', FOND_CLAIR)).toBeNull()
    expect(adapteCouleur('#ffffff', FOND_CLAIR)).toBeNull()
  })

  test('un gris moyen reste où il est', () => {
    // Il se lit sur les deux fonds : le renversement le laisse en place.
    const gris = versRvb(adapteCouleur('#808080', FOND_SOMBRE)!)!
    expect(Math.abs(gris.r - 128)).toBeLessThan(6)
  })

  test('ce qui n’est pas une couleur est laissé tel quel', () => {
    for (const v of ['none', 'currentColor', 'url(#grad)', '', 'var(--x)']) {
      expect(adapteCouleur(v, FOND_SOMBRE)).toBeNull()
    }
  })

  test('en thème clair rien ne bouge', () => {
    // La figure a été dessinée pour ce fond-là : elle n'a rien à corriger.
    for (const c of ['#000000', '#ffffff', '#ee0700', '#00008b', '#008000']) {
      expect(adapteCouleur(c, FOND_CLAIR)).toBeNull()
    }
  })
})

// Le câblage : la directive, l'observateur de thème, la réversibilité.
test.describe('les figures suivent le thème', () => {
  test.use({ storageState: 'e2e/.auth/student.json' })

  test('bascule et retour rendent la figure à l’identique', async ({ page }) => {
    await page.goto('/exercise/H4~geometry~oefpolynet.fr~src~31')
    await expect(page.locator('.pax-draw-img svg')).toBeVisible({ timeout: 30000 })

    const lire = () => page.evaluate(() => {
      const t = document.querySelector('.pax-draw-img svg text')
      const p = document.querySelector('.pax-draw-img svg polygon')
      return {
        texte: t?.getAttribute('fill') ?? null,
        memoTexte: t?.getAttribute('data-pax-fill') ?? null,
        trait: p?.getAttribute('stroke') ?? null,
      }
    })

    const clair = await lire()
    expect(clair.texte).toBe('#000000')
    expect(clair.memoTexte).toBeNull()

    await page.evaluate(() => document.documentElement.classList.add('dark'))
    await page.waitForTimeout(300)
    const sombre = await lire()
    expect(sombre.texte).not.toBe('#000000')
    expect(sombre.memoTexte).toBe('#000000')
    expect(sombre.trait).not.toBe('#000000')

    await page.evaluate(() => document.documentElement.classList.remove('dark'))
    await page.waitForTimeout(300)
    const retour = await lire()
    expect(retour).toEqual(clair)
  })
})
