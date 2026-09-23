import { test, expect } from '@playwright/test'

// Le bouton « base de temps » de l'oscilloscope (`temps/periodefrequence`) :
// chez WIMS, une carte d'image et un script qui échange les figures. PAX lit
// ce script côté backend (`core/oef/imgswap.py`) et livre les huit vues ; le
// front ne fait que déplacer l'index au clic.
test.describe('figures échangées par une carte d’image', () => {
  test.use({ storageState: 'e2e/.auth/student.json' })

  test('le bouton + / − change l’oscillogramme, dans ses bornes', async ({ page }) => {
    await page.goto('/exercise/H4~physics~temps.fr~src~periodefrequence')
    const moins = page.getByRole('button', { name: 'tourne à gauche' })
    const plus = page.getByRole('button', { name: 'tourne à droite' })
    await expect(plus).toBeVisible({ timeout: 30000 })

    const vues = () => page.evaluate(() =>
      [...document.querySelectorAll('.pax-swap')].map(b =>
        [...b.querySelectorAll(':scope > .pax-swap-frame')].findIndex(f => !(f as HTMLElement).hidden)))

    expect(await vues()).toEqual([0, 0])
    await plus.click()
    await plus.click()
    // L'écran et le bouton avancent ensemble, comme `redraw` les deux `src`.
    expect(await vues()).toEqual([2, 2])

    // `dec_choix` s'arrête à 0, `inc_choix` à 7 : pas de vue vide aux bords.
    for (let i = 0; i < 4; i++) await moins.click()
    expect(await vues()).toEqual([0, 0])
    for (let i = 0; i < 10; i++) await plus.click()
    expect(await vues()).toEqual([7, 7])
  })
})
