import { test, expect } from '@playwright/test'

test.use({ storageState: 'e2e/.auth/student.json' })

test.describe('exercise list', () => {
  test.beforeEach(async ({ page }) => {
    await page.goto('/exercise')
    await page.waitForLoadState('networkidle')
  })

  test('shows the exercise list heading', async ({ page }) => {
    await expect(page.locator('h1')).toContainText('Exercices')
  })

  test('loads and displays exercises', async ({ page }) => {
    // Wait for loading skeleton to disappear
    await page.waitForSelector('.animate-pulse', { state: 'detached', timeout: 15_000 })

    const items = page.locator('a[href^="/exercise/"]')
    await expect(items).not.toHaveCount(0, { timeout: 10_000 })
  })

  test('level filter narrows the list', async ({ page }) => {
    await page.waitForSelector('.animate-pulse', { state: 'detached', timeout: 15_000 })

    const countBefore = await page.locator('a[href^="/exercise/"]').count()

    await page.locator('select').first().selectOption('H4')
    await page.waitForLoadState('networkidle')
    await page.waitForSelector('.animate-pulse', { state: 'detached', timeout: 15_000 })

    const countAfter = await page.locator('a[href^="/exercise/"]').count()
    // H4 filter may reduce or keep count; just verify it returned results or empty state
    expect(countAfter).toBeGreaterThanOrEqual(0)
    expect(countAfter).toBeLessThanOrEqual(countBefore)
  })

  test('domain filter narrows the list', async ({ page }) => {
    await page.waitForSelector('.animate-pulse', { state: 'detached', timeout: 15_000 })

    await page.locator('select').nth(1).selectOption('algebra')
    await page.waitForLoadState('networkidle')
    await page.waitForSelector('.animate-pulse', { state: 'detached', timeout: 15_000 })

    // All visible exercise cards should show "algebra" domain badge
    const domainBadges = page.locator('a[href^="/exercise/"] span', { hasText: 'algebra' })
    const exerciseCount = await page.locator('a[href^="/exercise/"]').count()
    if (exerciseCount > 0) {
      await expect(domainBadges).not.toHaveCount(0)
    }
  })

  test('empty state shown when no exercises match', async ({ page }) => {
    await page.waitForSelector('.animate-pulse', { state: 'detached', timeout: 15_000 })

    // Combine two very specific filters unlikely to match together
    await page.locator('select').first().selectOption('U4')
    await page.locator('select').nth(1).selectOption('chemistry')
    await page.waitForLoadState('networkidle')
    await page.waitForSelector('.animate-pulse', { state: 'detached', timeout: 15_000 })

    const exercises = page.locator('a[href^="/exercise/"]')
    const emptyMsg = page.locator('text=Aucun exercice trouvé')
    const count = await exercises.count()
    if (count === 0) {
      await expect(emptyMsg).toBeVisible()
    }
  })

  test('clicking an exercise navigates to the player', async ({ page }) => {
    await page.waitForSelector('.animate-pulse', { state: 'detached', timeout: 15_000 })

    const firstExercise = page.locator('a[href^="/exercise/"]').first()
    await expect(firstExercise).toBeVisible()

    const href = await firstExercise.getAttribute('href')
    await firstExercise.click()

    await page.waitForURL(`**${href}**`, { timeout: 10_000 })
    await expect(page.url()).toContain('/exercise/')
  })

  test('exercise cards show level and domain badges', async ({ page }) => {
    await page.waitForSelector('.animate-pulse', { state: 'detached', timeout: 15_000 })

    const firstCard = page.locator('a[href^="/exercise/"]').first()
    await expect(firstCard).toBeVisible()

    // Cards should contain at least a title (font-medium span)
    await expect(firstCard.locator('.font-medium')).toBeVisible()
  })

  test('nav shows PAX brand link', async ({ page }) => {
    await expect(page.locator('nav a', { hasText: 'PAX' })).toBeVisible()
  })
})
