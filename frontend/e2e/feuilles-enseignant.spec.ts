import { test, expect } from '@playwright/test'

test.use({ storageState: 'e2e/.auth/teacher.json' })

const API = 'http://localhost:8001'

/**
 * L'enseignant et ses feuilles (docs/feuilles-eleve.md §3.3, étape 5) :
 * affecter une feuille à une classe, en régler le statut, les dates et la
 * note, puis lire le tableau des notes de la classe.
 *
 * Classe et feuille sont créées puis supprimées par l'API : ces tests
 * tournent contre la base de dev. Les notes elles-mêmes — qu'une correction
 * juste se retrouve au tableau — sont éprouvées par `tests/test_api.py`
 * (`TestNotesEnseignant`) : aucun exercice n'est présupposé ici.
 */
test.describe('feuilles côté enseignant', () => {
  let prof: Record<string, string> = {}
  let sheetId = 0
  let classId = 0
  const classe = `e2e — classe ${Date.now()}`
  const titre = `e2e — feuille enseignant ${Date.now()}`

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
      headers: prof, data: { name: classe } })).json()).id
    await request.post(`${API}/api/classes/${classId}/students`, {
      headers: prof, data: { student_id: eleve.id } })
    sheetId = (await (await request.post(`${API}/api/sheets/`, {
      headers: prof, data: { title: titre } })).json()).id
    await request.post(`${API}/api/sheets/${sheetId}/exercises`, {
      headers: prof, data: { exercise_id: exercices[0].id } })
  })

  test.afterEach(async ({ request }) => {
    if (sheetId) expect((await request.delete(`${API}/api/sheets/${sheetId}`, { headers: prof })).status()).toBe(204)
    if (classId) expect((await request.delete(`${API}/api/classes/${classId}`, { headers: prof })).status()).toBe(204)
  })

  test('affecter, régler statut et dates, puis lire les notes', async ({ page, request }) => {
    await page.goto(`/sheets/${sheetId}`)
    await expect(page.getByText('Cette feuille n\'est encore affectée à aucune classe.')).toBeVisible({ timeout: 15_000 })

    await page.getByLabel('Affecter à une classe').selectOption({ label: classe })
    await page.getByRole('button', { name: '+' }).first().click()
    const ligne = page.locator('li').filter({ hasText: classe })
    await expect(ligne.getByLabel('Statut')).toHaveValue('1')

    await ligne.getByLabel('Statut').selectOption({ label: 'Périmée' })
    await ligne.getByLabel('Fermer le').fill('2026-12-20T18:30')
    await ligne.getByRole('button', { name: 'Enregistrer' }).click()
    await expect(ligne.getByRole('button', { name: 'Enregistré' })).toBeVisible()

    // Le serveur garde l'heure en UTC : la saisie est locale.
    const [aff] = await (await request.get(`${API}/api/sheets/${sheetId}/classes`, { headers: prof })).json()
    expect(aff.status).toBe(2)
    expect(aff.close_at).toBe(new Date('2026-12-20T18:30').toISOString().slice(0, 19))
    // Rechargée, la page relit la même heure locale.
    await page.reload()
    await expect(page.locator('li').filter({ hasText: classe }).getByLabel('Fermer le')).toHaveValue('2026-12-20T18:30')

    // Le détail de la feuille pour cette classe : l'élève, rien de fait.
    await page.locator('li').filter({ hasText: classe }).getByRole('button', { name: 'Notes' }).click()
    await expect(page.locator('li').filter({ hasText: classe }).locator('table')).toContainText('0 %')

    await page.goto(`/classes/${classId}`)
    const tableau = page.locator('table').filter({ hasText: titre })
    await expect(tableau).toBeVisible({ timeout: 15_000 })
    await expect(tableau).toContainText('Périmée')
  })

  test('les réglages de note sont enregistrés', async ({ page, request }) => {
    await page.goto(`/sheets/${sheetId}`)
    await page.getByLabel('Formule').selectOption({ label: 'I·Q' })
    await page.getByLabel('Indicateur I').selectOption({ label: 'Cumul des points' })
    await page.getByLabel('Poids dans la moyenne').fill('3')
    await page.getByRole('button', { name: 'Enregistrer' }).first().click()
    await expect.poll(async () => {
      const s = await (await request.get(`${API}/api/sheets/${sheetId}`, { headers: prof })).json()
      return [s.note_formule, s.note_indicateur, s.note_poids]
    }).toEqual([4, 0, 3])
  })
})
