import { test, expect } from '@playwright/test'

test.use({ storageState: 'e2e/.auth/student.json' })

// `type=draw` : WIMS ouvre un canevas où l'élève pose des objets, et c'est la
// liste de leurs coordonnées — dans le repère du dessin, non en pixels — qui
// fait la réponse. Le rendu était jusqu'ici un champ de saisie, sans figure.
test.describe('canevas de tracé (type=draw)', () => {
  const EX = '/exercise/H4~geometry~oefpolynet.fr~src~31'

  test('affiche la figure et enregistre un clic', async ({ page }) => {
    await page.goto(EX)
    const canevas = page.locator('.pax-draw-frame')
    await expect(canevas).toBeVisible({ timeout: 30000 })
    // Le fond est le patron du polyèdre, tracé en SVG.
    await expect(page.locator('.pax-draw-img svg')).toBeVisible()

    const boite = await canevas.boundingBox()
    if (!boite) throw new Error('canevas sans géométrie')
    await page.mouse.click(boite.x + boite.width * 0.4, boite.y + boite.height * 0.5)

    // Une croix — deux traits — marque le point posé.
    await expect(page.locator('.pax-draw-mark line')).toHaveCount(2)
  })

  test('le bouton Effacer retire les points posés', async ({ page }) => {
    await page.goto(EX)
    const canevas = page.locator('.pax-draw-frame')
    await expect(canevas).toBeVisible({ timeout: 30000 })
    const boite = await canevas.boundingBox()
    if (!boite) throw new Error('canevas sans géométrie')
    await page.mouse.click(boite.x + boite.width * 0.3, boite.y + boite.height * 0.4)
    await page.mouse.click(boite.x + boite.width * 0.6, boite.y + boite.height * 0.7)
    await expect(page.locator('.pax-draw-mark line')).toHaveCount(4)

    await page.getByRole('button', { name: 'Effacer' }).click()
    await expect(page.locator('.pax-draw-mark line')).toHaveCount(0)
  })

  test('une réponse au hasard est corrigée, sans planter', async ({ page }) => {
    await page.goto(EX)
    const canevas = page.locator('.pax-draw-frame')
    await expect(canevas).toBeVisible({ timeout: 30000 })
    const boite = await canevas.boundingBox()
    if (!boite) throw new Error('canevas sans géométrie')
    await page.mouse.click(boite.x + boite.width * 0.5, boite.y + boite.height * 0.5)
    await page.getByRole('button', { name: 'Vérifier' }).click()
    // La correction revient : le canevas reste affiché et le clic n'est plus
    // modifiable (la croix passe au rouge ou au vert selon le verdict).
    await expect(page.locator('.pax-draw--done')).toBeVisible({ timeout: 20000 })
  })
})
