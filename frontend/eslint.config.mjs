// Configuration ESLint — la base officielle de Nuxt, sans surcouche.
//
// Le dépôt vivait sans linter alors que `CLAUDE.md` documentait `npm run lint`.
// La commande existe désormais, mais l'arriéré est réel : voir la ligne de base
// dans `CLAUDE.md`. On juge donc le **delta**, comme pour la suite Playwright.
//
// `.nuxt/` et `.output/` sont générés ; `dist/` et `node_modules/` vont de soi.
import { createConfigForNuxt } from '@nuxt/eslint-config/flat'

export default createConfigForNuxt().append({
  ignores: ['.nuxt/**', '.output/**', 'dist/**', 'node_modules/**'],
})
