import { test, expect } from '@playwright/test'

// `redox1` : les boutons de `slib/chemistry/chemeq_components` complètent le
// champ de réponse. Chez WIMS, un script `appendToInput` ; ici le backend l'a
// reconnu (`core/oef/appendinput.py`) et le front fait l'ajout.
test.describe('redox — boutons et formules', () => {
  test.use({ storageState: 'e2e/.auth/student.json' })

  test('un bouton ajoute son espèce au champ, suivie d’une espace', async ({ page }) => {
    await page.goto('/exercise/H5~chemistry~redox.fr~src~redox1')
    const boutons = page.locator('.oef-statement .pax-append')
    await expect(boutons.first()).toBeVisible({ timeout: 30000 })
    expect(await boutons.count()).toBeGreaterThan(3)

    const champ = page.locator('.oef-statement input[name="reply1"]')
    const fleche = boutons.filter({ hasText: /^->$/ })
    const electron = boutons.filter({ hasText: /^e\^-$/ })
    await fleche.click()
    await electron.click()
    // Le texte du bouton porte ses espaces (`' -> '`), le script en ajoute une.
    await expect(champ).toHaveValue(' ->   e^-  ')
  })

  test('les formules de chemeq se composent sans erreur', async ({ page }) => {
    // `chemeq -l` écrit `\mathrm{H}_{2}_{(g)}` : un double indice, que KaTeX
    // refusait et affichait brut, en rouge.
    await page.goto('/exercise/H5~chemistry~redox.fr~src~redox1')
    await expect(page.locator('.oef-statement .katex').first()).toBeVisible({ timeout: 30000 })
    await expect(page.locator('.oef-statement .katex-error')).toHaveCount(0)
  })
})
