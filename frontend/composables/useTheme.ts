/**
 * Gestion du thème clair/sombre/système.
 *
 * Priorité pour l'initialisation : préférence DB (via store auth) > localStorage > préférence système.
 * Le thème est appliqué via la classe `dark` sur <html> (Tailwind dark mode).
 */

export type ThemeChoice = 'light' | 'dark' | 'system'

const _VALID: ThemeChoice[] = ['light', 'dark', 'system']

// Singletons partagés entre toutes les instances du composable
const _theme = ref<ThemeChoice>('system')
const _isDark = ref(false)

function _resolveSystem(): boolean {
  if (!import.meta.client) return false
  return window.matchMedia('(prefers-color-scheme: dark)').matches
}

function _applyChoice(choice: ThemeChoice) {
  _theme.value = choice
  const dark = choice === 'dark' || (choice === 'system' && _resolveSystem())
  _isDark.value = dark
  if (import.meta.client) {
    document.documentElement.classList.toggle('dark', dark)
  }
}

export function useTheme() {
  const auth = useAuthStore()

  /** Lit la préférence (DB > localStorage > système) et l'applique. */
  function init() {
    const dbTheme = auth.user?.theme as ThemeChoice | undefined
    if (dbTheme && _VALID.includes(dbTheme)) {
      _applyChoice(dbTheme)
      if (import.meta.client) localStorage.setItem('pax_theme', dbTheme)
      return
    }
    if (import.meta.client) {
      const stored = localStorage.getItem('pax_theme') as ThemeChoice | null
      if (stored && _VALID.includes(stored)) {
        _applyChoice(stored)
        return
      }
    }
    _applyChoice('system')
  }

  /** Persiste le choix en DB (si connecté) et localement, puis applique. */
  async function setTheme(choice: ThemeChoice) {
    _applyChoice(choice)
    if (import.meta.client) localStorage.setItem('pax_theme', choice)
    if (auth.user) {
      try {
        const { apiFetch } = useApi()
        const updated = await apiFetch<{ theme: string }>('/api/auth/me', {
          method: 'PATCH',
          body: { theme: choice },
        })
        if (auth.user) auth.user.theme = updated.theme
      } catch {
        // la valeur localStorage reste comme filet de sécurité
      }
    }
  }

  /** À appeler une fois au montage de app.vue pour suivre les changements système. */
  function watchSystem() {
    if (!import.meta.client) return
    window.matchMedia('(prefers-color-scheme: dark)').addEventListener('change', (e) => {
      if (_theme.value === 'system') {
        _isDark.value = e.matches
        document.documentElement.classList.toggle('dark', e.matches)
      }
    })
  }

  return {
    theme: readonly(_theme),
    isDark: readonly(_isDark),
    init,
    setTheme,
    watchSystem,
  }
}
