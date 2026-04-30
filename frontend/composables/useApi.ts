export function useApi() {
  const config = useRuntimeConfig()
  const auth = useAuthStore()

  async function apiFetch<T>(path: string, options: any = {}): Promise<T> {
    return $fetch<T>(`${config.public.apiBase}${path}`, {
      ...options,
      headers: {
        ...(options.headers || {}),
        ...(auth.token ? { Authorization: `Bearer ${auth.token}` } : {}),
      },
    })
  }

  return { apiFetch }
}
