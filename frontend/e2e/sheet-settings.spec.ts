import { test, expect } from '@playwright/test'

test.use({ storageState: 'e2e/.auth/teacher.json' })

const API = 'http://localhost:8001'

/**
 * Régler un exercice posé sur une feuille, puis l'essayer sous ce réglage.
 *
 * La feuille est créée et supprimée par l'API : ces tests tournent contre la
 * base de dev, où ce qu'ils créent resterait. L'exercice est le premier que
 * l'API renvoie — aucun n'est présupposé.
 */
test.describe('réglages d\'un exercice sur une feuille', () => {
  let headers: Record<string, string> = {}
  let sheetId = 0
  let itemId = 0

  test.beforeEach(async ({ request }) => {
    sheetId = 0
    const login = await request.post(`${API}/api/auth/login`, {
      data: { email: 'prof@pax.fr', password: 'prof1234' },
    })
    headers = { Authorization: `Bearer ${(await login.json()).access_token}` }

    const exercices = await (await request.get(`${API}/api/exercises/?limit=1`, { headers })).json()
    test.skip(!exercices.length, 'aucun exercice importé')

    sheetId = (await (await request.post(`${API}/api/sheets/`, {
      headers, data: { title: 'e2e — réglages' },
    })).json()).id
    await request.post(`${API}/api/sheets/${sheetId}/exercises`, {
      headers, data: { exercise_id: exercices[0].id },
    })
    itemId = (await (await request.get(`${API}/api/sheets/${sheetId}`, { headers })).json()).items[0].id
  })

  test.afterEach(async ({ request }) => {
    if (!sheetId) return
    const r = await request.delete(`${API}/api/sheets/${sheetId}`, { headers })
    expect(r.status()).toBe(204)
  })

  test('le niveau choisi est enregistré, et l\'aperçu le montre', async ({ page, request }) => {
    await page.goto(`/sheets/${sheetId}`)
    const niveau = page.getByLabel('Niveau de sévérité')
    await expect(niveau).toBeVisible({ timeout: 15_000 })

    await niveau.selectOption('7')
    const ligne = page.locator('li').filter({ has: niveau })
    await ligne.getByRole('button', { name: 'Enregistrer' }).click()
    await expect.poll(async () => {
      const feuille = await (await request.get(`${API}/api/sheets/${sheetId}`, { headers })).json()
      return feuille.items[0].qcmlevel
    }).toBe(7)

    // Le tableau des neuf niveaux dit ce que le curseur commande.
    await page.getByRole('button', { name: 'Ce que commande chaque niveau' }).click()
    await expect(page.getByRole('row', { name: /Corrigé montré/ })).toBeVisible()

    await ligne.getByRole('link', { name: 'Essayer' }).click()
    await expect(page).toHaveURL(new RegExp(`sheet_item=${itemId}`))
    await expect(page.getByText('Sévérité 7')).toBeVisible({ timeout: 20_000 })
  })
})
