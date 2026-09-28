/**
 * Directive `v-figures` — les figures d'un exercice suivent le thème.
 *
 * Posée sur le conteneur d'un exercice, elle adapte les couleurs des SVG qu'il
 * contient (cf. `utils/figureTheme.ts`) et **rejoue** la passe à chaque fois
 * que le contenu change — un `v-html` remplace tout son sous-arbre sans que la
 * directive en soit avertie — ou que le thème bascule.
 */
import { adapteFigures, adapteFondsClairs } from '~/utils/figureTheme'

/** Les racines montées, pour rejouer la passe quand le thème change. */
const racines = new Set<Element>()
let observateurTheme: MutationObserver | null = null

function estSombre(): boolean {
  return document.documentElement.classList.contains('dark')
}

/** Les deux passes de thème : couleurs des figures, texte sur fonds clairs. */
function adapte(el: Element, sombre: boolean) {
  adapteFigures(el, sombre)
  adapteFondsClairs(el, sombre)
}

function rejoueTout() {
  const sombre = estSombre()
  for (const racine of racines) adapte(racine, sombre)
}

export default defineNuxtPlugin((nuxtApp) => {
  const observateurs = new WeakMap<Element, MutationObserver>()

  nuxtApp.vueApp.directive('figures', {
    mounted(el: Element) {
      racines.add(el)
      adapte(el, estSombre())
      // `v-html` réécrit le sous-arbre : sans observateur, la figure d'un
      // nouvel énoncé — ou celle qu'un corrigé fait apparaître — resterait
      // avec ses couleurs d'origine.
      const obs = new MutationObserver((mutations) => {
        if (mutations.some(m => m.addedNodes.length > 0)) {
          adapte(el, estSombre())
        }
      })
      obs.observe(el, { childList: true, subtree: true })
      observateurs.set(el, obs)
    },
    updated(el: Element) {
      adapte(el, estSombre())
    },
    unmounted(el: Element) {
      racines.delete(el)
      observateurs.get(el)?.disconnect()
      observateurs.delete(el)
    },
  })

  // Un seul observateur pour la classe `dark` de `<html>`, partagé par toutes
  // les racines : c'est ainsi que `useTheme` signale une bascule.
  if (!observateurTheme) {
    observateurTheme = new MutationObserver(rejoueTout)
    observateurTheme.observe(document.documentElement, {
      attributes: true,
      attributeFilter: ['class'],
    })
  }
})
