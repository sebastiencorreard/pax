import { test, expect } from '@playwright/test'

// `\(f^'(0) =\)` (`oefderivee1S/eqtgte2`) : MathJax, chez WIMS, lit le `'`
// comme exposant ; KaTeX le refusait et sortait la formule en rouge.
// `useKatex` réécrit `^'` en `^{\prime}`.
test.describe('prime en exposant', () => {
  test.use({ storageState: 'e2e/.auth/student.json' })

  test('f^\'(0) se rend sans erreur KaTeX', async ({ page }) => {
    await page.goto('/exercise/H5~analysis~oefderivee1S.fr~src~eqtgte2')
    await expect(page.locator('.katex').first()).toBeVisible({ timeout: 30000 })
    await expect(page.locator('.katex-error')).toHaveCount(0)
  })
})
