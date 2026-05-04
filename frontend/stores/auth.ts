import { defineStore } from 'pinia'

interface User {
  id: string
  email: string
  first_name: string
  last_name: string
  role: string
}

export const useAuthStore = defineStore('auth', {
  state: () => ({
    token: null as string | null,
    user: null as User | null,
  }),

  getters: {
    isLoggedIn: (state) => !!state.token,
    isTeacher: (state) => state.user?.role === 'teacher' || state.user?.role === 'admin',
    fullName: (state) => state.user
      ? `${state.user.first_name} ${state.user.last_name}`
      : '',
  },

  actions: {
    async login(email: string, password: string) {
      const config = useRuntimeConfig()
      const data = await $fetch<{ access_token: string }>(
        `${config.public.apiBase}/api/auth/login`,
        { method: 'POST', body: { email, password } }
      )
      this.token = data.access_token
      // Persist dans localStorage
      if (import.meta.client) {
        localStorage.setItem('pax_token', data.access_token)
      }
      await this.fetchMe()
    },

    async loginAsGuest() {
      // Issues a token for the singleton guest account (no password).
      // Backend returns 503 if the operator hasn't seeded one yet.
      const config = useRuntimeConfig()
      const data = await $fetch<{ access_token: string }>(
        `${config.public.apiBase}/api/auth/guest`,
        { method: 'POST' }
      )
      this.token = data.access_token
      if (import.meta.client) {
        localStorage.setItem('pax_token', data.access_token)
      }
      await this.fetchMe()
    },

    async fetchMe() {
      if (!this.token) return
      const config = useRuntimeConfig()
      try {
        this.user = await $fetch<User>(`${config.public.apiBase}/api/auth/me`, {
          headers: { Authorization: `Bearer ${this.token}` },
        })
      } catch {
        this.logout()
      }
    },

    logout() {
      this.token = null
      this.user = null
      if (import.meta.client) {
        localStorage.removeItem('pax_token')
      }
    },

    // Restaure la session depuis localStorage au démarrage
    restore() {
      if (import.meta.client) {
        const t = localStorage.getItem('pax_token')
        if (t) {
          this.token = t
          this.fetchMe()
        }
      }
    },
  },
})
