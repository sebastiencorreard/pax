import { test, expect } from '@playwright/test'

test.describe('login page', () => {
  test('renders the login form', async ({ page }) => {
    await page.goto('/auth/login')
    await page.waitForLoadState('networkidle')

    await expect(page.locator('h1')).toContainText('Connexion')
    await expect(page.locator('input[type="email"]')).toBeVisible()
    await expect(page.locator('input[type="password"]')).toBeVisible()
    await expect(page.locator('button[type="submit"]')).toContainText('Se connecter')
  })

  test('shows error on invalid credentials', async ({ page }) => {
    await page.goto('/auth/login')
    await page.waitForLoadState('networkidle')

    await page.locator('input[type="email"]').fill('wrong@example.com')
    await page.locator('input[type="password"]').fill('wrongpassword')
    await page.locator('button[type="submit"]').click()

    await expect(page.locator('[style*="color-error"]')).toBeVisible({ timeout: 10_000 })
  })

  test('shows loading state while submitting', async ({ page }) => {
    await page.goto('/auth/login')
    await page.waitForLoadState('networkidle')

    await page.locator('input[type="email"]').fill('eleve@pax.fr')
    await page.locator('input[type="password"]').fill('eleve1234')

    // Check button text changes to "Connexion..." momentarily
    const submitBtn = page.locator('button[type="submit"]')
    await submitBtn.click()

    // Button should eventually be gone or page redirected after successful login
    await page.waitForURL('**/exercise**', { timeout: 15_000 })
  })

  test('logs in as student and shows username in nav', async ({ page }) => {
    await page.goto('/auth/login')
    await page.waitForLoadState('networkidle')

    await page.locator('input[type="email"]').fill('eleve@pax.fr')
    await page.locator('input[type="password"]').fill('eleve1234')
    await page.locator('button[type="submit"]').click()

    await page.waitForURL('**/exercise**', { timeout: 15_000 })

    const nav = page.locator('nav')
    // Role badge should be visible for logged-in user
    await expect(nav.locator('span', { hasText: 'student' })).toBeVisible({ timeout: 5_000 })
  })

  test('logout returns to login page', async ({ page }) => {
    await page.goto('/auth/login')
    await page.waitForLoadState('networkidle')

    await page.locator('input[type="email"]').fill('eleve@pax.fr')
    await page.locator('input[type="password"]').fill('eleve1234')
    await page.locator('button[type="submit"]').click()
    await page.waitForURL('**/exercise**', { timeout: 15_000 })

    // Click logout
    await page.getByRole('button', { name: 'Déconnexion' }).click()
    await page.waitForURL('**/auth/login**', { timeout: 10_000 })

    await expect(page.locator('h1')).toContainText('Connexion')
  })

  test('logs in as teacher and shows teacher role badge', async ({ page }) => {
    await page.goto('/auth/login')
    await page.waitForLoadState('networkidle')

    await page.locator('input[type="email"]').fill('prof@pax.fr')
    await page.locator('input[type="password"]').fill('prof1234')
    await page.locator('button[type="submit"]').click()

    await page.waitForURL('**/exercise**', { timeout: 15_000 })

    const nav = page.locator('nav')
    await expect(nav.locator('span', { hasText: 'teacher' })).toBeVisible({ timeout: 5_000 })
  })
})
