export function useApi() {
  const config = useRuntimeConfig()
  const auth = useAuthStore()

  async function apiFetch<T>(path: string, options: any = {}): Promise<T> {
    const url = `${config.public.apiBase}${path}`
    const start = performance.now()
    try {
      const result = await $fetch<T>(url, {
        ...options,
        headers: {
          ...(options.headers || {}),
          ...(auth.token ? { Authorization: `Bearer ${auth.token}` } : {}),
        },
      })
      const ms = (performance.now() - start).toFixed(0)
      console.log(`[API] ${options.method || 'GET'} ${path} — ${ms}ms`)
      return result
    } catch (err: any) {
      const ms = (performance.now() - start).toFixed(0)
      console.warn(`[API] ${options.method || 'GET'} ${path} — ${ms}ms — ERROR ${err?.status ?? err}`)
      throw err
    }
  }

  return { apiFetch }
}
