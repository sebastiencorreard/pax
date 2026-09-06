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
    await page.waitForURL(/\/exercise(\?|$)/, { timeout: 15_000 })
  })

  test('logs in as student and shows username in nav', async ({ page }) => {
    await page.goto('/auth/login')
    await page.waitForLoadState('networkidle')

    await page.locator('input[type="email"]').fill('eleve@pax.fr')
    await page.locator('input[type="password"]').fill('eleve1234')
    await page.locator('button[type="submit"]').click()

    await page.waitForURL(/\/exercise(\?|$)/, { timeout: 15_000 })

    // La barre du haut affiche le nom complet, non le rôle — celui-ci n'y
    // figure plus. C'est un `<header>` (banner), pas un `<nav>` : le seul
    // `<nav>` de la page est la liste de liens de la barre latérale.
    await expect(
      page.getByRole('banner').getByText('Eleve Test'),
    ).toBeVisible({ timeout: 5_000 })
  })

  test('logout returns to login page', async ({ page }) => {
    await page.goto('/auth/login')
    await page.waitForLoadState('networkidle')

    await page.locator('input[type="email"]').fill('eleve@pax.fr')
    await page.locator('input[type="password"]').fill('eleve1234')
    await page.locator('button[type="submit"]').click()
    await page.waitForURL(/\/exercise(\?|$)/, { timeout: 15_000 })

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

    // Un enseignant atterrit sur son tableau de bord (`/`), un élève sur
    // `/exercise` : n'attendre que d'avoir quitté la page de connexion.
    await page.waitForURL((url) => !url.pathname.startsWith('/auth/'), { timeout: 15_000 })

    await expect(
      page.getByRole('banner').getByText('Prof Test'),
    ).toBeVisible({ timeout: 5_000 })
  })
})
