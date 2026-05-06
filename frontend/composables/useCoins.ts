const _coins = ref(0)

export function useCoins() {
  const auth = useAuthStore()
  const config = useRuntimeConfig()

  if (import.meta.client) {
    // Sync depuis le store auth à chaque changement d'utilisateur
    watch(
      () => auth.user?.id,
      () => {
        if (auth.user) {
          _coins.value = auth.user.coins ?? 0
        } else {
          _coins.value = parseInt(localStorage.getItem('pax-coins-guest') ?? '0')
        }
      },
      { immediate: true }
    )
  }

  function formatCoins(n: number): string {
    if (n >= 1_000_000) return (n / 1_000_000).toFixed(1).replace(/\.0$/, '') + 'M'
    if (n >= 1_000)     return (n / 1_000).toFixed(1).replace(/\.0$/, '') + 'k'
    return String(n)
  }

  async function addCoins(n: number) {
    if (n <= 0) return
    _coins.value += n

    if (auth.user && auth.token) {
      try {
        const result = await $fetch<{ coins: number }>(
          `${config.public.apiBase}/api/auth/coins/add`,
          {
            method: 'POST',
            headers: { Authorization: `Bearer ${auth.token}` },
            body: { amount: n },
          }
        )
        _coins.value = result.coins
        auth.user.coins = result.coins
      } catch {
        // valeur optimiste conservée
      }
    } else {
      localStorage.setItem('pax-coins-guest', String(_coins.value))
    }
  }

  return { coins: _coins, formatCoins, addCoins }
}
