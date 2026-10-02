import { test, expect } from '@playwright/test'

test.use({ storageState: 'e2e/.auth/student.json' })

const API = 'http://localhost:8001'

/**
 * Le parcours d'un élève dans une feuille : la liste, le verrou d'un
 * prérequis, le lancement d'un exercice en mode feuille.
 *
 * Classe et feuille sont créées puis supprimées par l'API de l'enseignant :
 * ces tests tournent contre la base de dev. L'exercice est le premier que
 * l'API renvoie — aucun n'est présupposé, d'où l'absence de réponse juste
 * ici : la note après correction est éprouvée par `tests/test_api.py`.
 */
test.describe('feuilles côté élève', () => {
  let prof: Record<string, string> = {}
  let sheetId = 0
  let classId = 0
  const titre = `e2e — feuille élève ${Date.now()}`

  test.beforeEach(async ({ request }) => {
    sheetId = 0
    classId = 0
    const jeton = async (email: string, password: string) => ({
      Authorization: `Bearer ${(await (await request.post(`${API}/api/auth/login`, {
        data: { email, password } })).json()).access_token}`,
    })
    prof = await jeton('prof@pax.fr', 'prof1234')
    const eleve = await (await request.get(`${API}/api/auth/me`, {
      headers: await jeton('eleve@pax.fr', 'eleve1234') })).json()

    const exercices = await (await request.get(`${API}/api/exercises/?limit=1`, { headers: prof })).json()
    test.skip(!exercices.length, 'aucun exercice importé')

    classId = (await (await request.post(`${API}/api/classes/`, {
      headers: prof, data: { name: 'e2e — classe' } })).json()).id
    await request.post(`${API}/api/classes/${classId}/students`, {
      headers: prof, data: { student_id: eleve.id } })
    sheetId = (await (await request.post(`${API}/api/sheets/`, {
      headers: prof, data: { title: titre } })).json()).id
    for (const champs of [{}, { prerequisite: '1:50' }]) {
      await request.post(`${API}/api/sheets/${sheetId}/exercises`, {
        headers: prof, data: { exercise_id: exercices[0].id, ...champs } })
    }
    const r = await request.post(`${API}/api/sheets/${sheetId}/classes`, {
      headers: prof, data: { class_id: classId, status: 1 } })
    expect(r.status()).toBe(201)
  })

  test.afterEach(async ({ request }) => {
    if (sheetId) expect((await request.delete(`${API}/api/sheets/${sheetId}`, { headers: prof })).status()).toBe(204)
    if (classId) expect((await request.delete(`${API}/api/classes/${classId}`, { headers: prof })).status()).toBe(204)
  })

  test('la liste, le verrou, puis l\'exercice en mode feuille', async ({ page }) => {
    await page.goto('/feuilles')
    await page.getByRole('link', { name: new RegExp(titre) }).click()
    await expect(page).toHaveURL(new RegExp(`/feuilles/${sheetId}$`))

    // Le second exercice attend que le premier soit réussi.
    await expect(page.getByText(/Réussissez d'abord l'exercice 1 \(à 50 %\)/)).toBeVisible()
    const lancer = page.getByRole('link', { name: 'Commencer' })
    await expect(lancer).toHaveCount(1)

    await lancer.click()
    await expect(page).toHaveURL(/sheet_item=\d+/)
    await expect(page.locator('.oef-statement')).toBeVisible({ timeout: 20_000 })

    // La graine vient du serveur : « Nouvel énoncé » lui demande un autre
    // tirage, faute de quoi il rendrait le même.
    const rendu = page.waitForRequest(r => r.url().includes('/api/render/') && r.url().includes('nouveau=true'))
    await page.getByRole('button', { name: /Nouvel énoncé/ }).click()
    await rendu

    await page.getByRole('link', { name: /Retour à la feuille/ }).click()
    await expect(page).toHaveURL(new RegExp(`/feuilles/${sheetId}$`))
    await expect(page.getByRole('link', { name: 'Continuer' })).toBeVisible()
  })
})
