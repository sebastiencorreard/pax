import { test, expect } from '@playwright/test'

test.use({ storageState: 'e2e/.auth/student.json' })

/**
 * Le signe d'une fraction reste où le `.def` l'a mis — au numérateur.
 *
 * PAX le sortait : `\dfrac{-11}{6}` devenait `-\dfrac{11}{6}`, d'où des « - - »
 * disgracieux (`A = -6/4 - -10/6`) là où WIMS écrit `\dfrac{-2}{2} - \dfrac{4}{2}`.
 * Et sur `quotient1`, simplifier `\dfrac{-4}{-4}` en `\dfrac{4}{4}` donnait une
 * part de la réponse : `11 ÷ \dfrac{-4}{-4}` attend `11`, et reconnaître que
 * deux négatifs s'annulent *est* l'exercice.
 *
 * La garde porte sur le rendu KaTeX, seul endroit où la transformation vivait :
 * le backend, lui, a toujours émis le bon LaTeX (`\dfrac{-11}{6}`).
 *
 * Elle a été vérifiée dans les deux sens — en réintroduisant la transformation,
 * l'assertion ci-dessous échoue.
 */
test.describe('signe des fractions', () => {
  test('le signe reste au numérateur', async ({ page }) => {
    await page.goto('/exercise/H3~algebra~rational.fr~src~sommesimple1?seed=42')
    await page.waitForSelector('.animate-pulse', { state: 'detached', timeout: 20_000 })

    const enonce = page.locator('.oef-statement')
    await expect(enonce.locator('.mfrac').first()).toBeVisible()

    // KaTeX empile numérateur et dénominateur dans le `.mfrac` ; le premier
    // `.vlist-r` est le numérateur. Sorti de là, le signe se retrouverait
    // *avant* la fraction et aucun numérateur n'en porterait plus.
    const numerateurs = await enonce.locator('.mfrac .vlist-r:first-child').allInnerTexts()
    expect(numerateurs.length).toBeGreaterThan(0)
    expect(numerateurs.some(t => /[-−]/.test(t))).toBe(true)
  })
})
