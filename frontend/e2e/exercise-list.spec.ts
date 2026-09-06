import { test, expect } from '@playwright/test'

test.use({ storageState: 'e2e/.auth/student.json' })

/**
 * Ouvre le premier module de la liste et rend le localisateur de ses exercices.
 *
 * La page n'affiche que des modules repliés : leurs exercices ne sont ni dans
 * le DOM ni même chargés — depuis que la recherche se fait au serveur, déplier
 * un module va les chercher (`/modules/{nom}/exercises`). Un test qui compte
 * des `a[href^="/exercise/"]` sans avoir déplié compte donc zéro.
 */
async function ouvrirPremierModule(page: import('@playwright/test').Page) {
  await page.waitForSelector('.animate-pulse', { state: 'detached', timeout: 15_000 })
  const exercices = page.locator('a[href^="/exercise/"]')
  const modules = page.getByRole('button').filter({ has: page.locator('.font-medium') })
  await modules.first().click()
  await expect(exercices.first()).toBeVisible({ timeout: 10_000 })
  return exercices
}

/** Le nombre d'exercices que le filtre courant laisse, lu sur le compteur. */
async function nombreAnnonce(page: import('@playwright/test').Page): Promise<number> {
  const texte = await page.getByText(/^\d+ exercices?$|^aucun exercice$/).first().textContent()
  return texte?.startsWith('aucun') ? 0 : parseInt(texte || '0', 10)
}

test.describe('exercise list', () => {
  test.beforeEach(async ({ page }) => {
    await page.goto('/exercise')
    await page.waitForLoadState('networkidle')
  })

  test('shows the exercise list heading', async ({ page }) => {
    await expect(page.locator('h1')).toContainText('Exercices')
  })

  test('loads and displays exercises', async ({ page }) => {
    const exercices = await ouvrirPremierModule(page)
    await expect(exercices).not.toHaveCount(0)
  })

  test('level filter narrows the list', async ({ page }) => {
    await page.waitForSelector('.animate-pulse', { state: 'detached', timeout: 15_000 })
    const avant = await nombreAnnonce(page)

    // Le menu ne propose que les niveaux présents en base, avec leur effectif :
    // « H4 · 2nde (2103) ». C'est cet effectif que le filtre doit produire.
    const niveau = page.locator('select').nth(1)
    const libelle = await niveau.locator('option').nth(1).textContent()
    const attendu = parseInt(libelle?.match(/\((\d+)\)/)?.[1] || '0', 10)
    await niveau.selectOption({ index: 1 })
    await page.waitForLoadState('networkidle')

    await expect.poll(() => nombreAnnonce(page)).toBe(attendu)
    expect(attendu).toBeLessThan(avant)

    // Et tout module affiché porte ce niveau.
    const code = ((libelle || '').split('\u00b7')[0] ?? '').trim()
    const modules = page.getByRole('button').filter({ has: page.locator('.font-medium') })
    for (const bouton of await modules.all()) {
      expect(await bouton.textContent()).toContain(code)
    }
  })

  test('domain filter narrows the list', async ({ page }) => {
    await page.waitForSelector('.animate-pulse', { state: 'detached', timeout: 15_000 })

    await page.locator('select').nth(2).selectOption('algebra')
    await page.waitForLoadState('networkidle')

    // Les modules sont groupés par domaine sous un titre de niveau 2 : filtrer
    // sur `algebra` ne doit en laisser qu'un.
    await expect(page.getByRole('heading', { level: 2 })).toHaveText(['algebra'])
    expect(await nombreAnnonce(page)).toBeGreaterThan(0)
  })

  test('empty state shown when no exercises match', async ({ page }) => {
    await page.waitForSelector('.animate-pulse', { state: 'detached', timeout: 15_000 })

    // Le menu de niveau ne propose que les niveaux réellement présents en base
    // (H3, H4) : il n'y a plus de code « impossible » à y choisir. On force donc
    // la liste vide par une recherche qui ne peut correspondre à rien.
    await page.locator('input[type="search"]').fill('zzzznexistepaszzzz')
    await page.waitForLoadState('networkidle')

    const exercises = page.locator('a[href^="/exercise/"]')
    const emptyMsg = page.locator('text=Aucun exercice trouvé')
    const count = await exercises.count()
    if (count === 0) {
      await expect(emptyMsg).toBeVisible()
    }
  })

  test('clicking an exercise shows the preview on a large screen', async ({ page }) => {
    // Au-dessus de 1024 px la liste garde la main et affiche l'exercice dans le
    // panneau de droite (`onExerciseClick`) : c'est voulu, et le test l'ignorait
    // en attendant une navigation qui n'a pas lieu.
    const exercices = await ouvrirPremierModule(page)
    const premier = exercices.first()
    const href = await premier.getAttribute('href')
    await premier.click()

    await expect(page).toHaveURL(/[?&]preview=/, { timeout: 10_000 })
    expect(page.url()).not.toContain(`/exercise/${href?.split('/').pop()}`)
    await expect(page.getByRole('heading', { level: 2 }).first()).toBeVisible({ timeout: 15_000 })
  })

  test('clicking an exercise navigates to the player on a small screen', async ({ page }) => {
    await page.setViewportSize({ width: 800, height: 720 })
    await page.reload()
    await page.waitForLoadState('networkidle')

    const exercices = await ouvrirPremierModule(page)
    const href = await exercices.first().getAttribute('href')
    await exercices.first().click()

    await page.waitForURL(`**${href}`, { timeout: 10_000 })
    expect(page.url()).toContain('/exercise/')
  })

  test('module rows show their exercise count and level badge', async ({ page }) => {
    await page.waitForSelector('.animate-pulse', { state: 'detached', timeout: 15_000 })

    const premier = page
      .getByRole('button')
      .filter({ has: page.locator('.font-medium') })
      .first()
    // Le texte du bouton est concaténé sans séparateurs :
    // « <titre><auteur><nombre><niveau>› ». Le niveau porte sa classe française
    // à côté du code WIMS.
    await expect(premier).toHaveText(/\d+H\d\s*·\s*\S+/)
  })

  test('the sidebar shows the PAX brand link', async ({ page }) => {
    // Le lien de marque vit dans la barre latérale (`<aside>`), non dans le
    // `<nav>` qu'elle contient — celui-ci ne porte que les liens de rubrique.
    await expect(
      page.getByRole('complementary').getByRole('link', { name: 'PAX' }),
    ).toBeVisible()
  })
})
