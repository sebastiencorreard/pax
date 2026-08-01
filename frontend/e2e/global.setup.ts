import { test as setup } from '@playwright/test'
import { mkdirSync } from 'fs'

mkdirSync('e2e/.auth', { recursive: true })

const STUDENT_FILE = 'e2e/.auth/student.json'
const TEACHER_FILE = 'e2e/.auth/teacher.json'

setup('authenticate as student', async ({ page }) => {
  await page.goto('/auth/login')
  await page.waitForLoadState('networkidle')

  await page.locator('input[type="email"]').fill('eleve@pax.fr')
  await page.locator('input[type="password"]').fill('eleve1234')
  await page.locator('button[type="submit"]').click()

  // La page de connexion redirige vers `route.query.redirect || '/'`
  // (pages/auth/login.vue) : sans paramètre, on atterrit à la racine. Attendre
  // `**/exercise**` était vrai en mai 2026 et ne l'est plus. On attend donc
  // simplement d'avoir quitté la page de connexion.
  await page.waitForURL(url => !url.pathname.startsWith('/auth/login'),
                        { timeout: 15_000 })
  await page.context().storageState({ path: STUDENT_FILE })
})

setup('authenticate as teacher', async ({ page }) => {
  await page.goto('/auth/login')
  await page.waitForLoadState('networkidle')

  await page.locator('input[type="email"]').fill('prof@pax.fr')
  await page.locator('input[type="password"]').fill('prof1234')
  await page.locator('button[type="submit"]').click()

  // La page de connexion redirige vers `route.query.redirect || '/'`
  // (pages/auth/login.vue) : sans paramètre, on atterrit à la racine. Attendre
  // `**/exercise**` était vrai en mai 2026 et ne l'est plus. On attend donc
  // simplement d'avoir quitté la page de connexion.
  await page.waitForURL(url => !url.pathname.startsWith('/auth/login'),
                        { timeout: 15_000 })
  await page.context().storageState({ path: TEACHER_FILE })
})
