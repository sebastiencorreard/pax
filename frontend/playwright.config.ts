import { defineConfig, devices } from '@playwright/test'

export default defineConfig({
  testDir: './e2e',
  fullyParallel: false,
  forbidOnly: !!process.env.CI,
  retries: process.env.CI ? 2 : 0,
  reporter: process.env.CI ? 'dot' : 'html',
  use: {
    baseURL: 'http://localhost:3000',
    trace: 'on-first-retry',
    // Les tests affirment une interface en français (« Connexion », « Vérifier »).
    // Or `nuxt.config.ts` ne désactive pas `detectBrowserLanguage`, donc i18n
    // suit la langue du navigateur — et le Chromium de Playwright demande
    // `en-US` par défaut. L'application rendait donc « Log in » et les tests
    // échouaient : c'est la locale du test qu'il faut fixer, pas l'application.
    locale: 'fr-FR',
  },

  projects: [
    {
      name: 'setup',
      testMatch: '**/global.setup.ts',
    },
    {
      name: 'chromium',
      use: { ...devices['Desktop Chrome'] },
      dependencies: ['setup'],
    },
  ],

  // Reuse an already-running dev server or Docker stack.
  // Start `docker compose up -d` before running tests.
  webServer: {
    command: 'npm run dev',
    url: 'http://localhost:3000',
    reuseExistingServer: true,
    timeout: 120_000,
  },
})
