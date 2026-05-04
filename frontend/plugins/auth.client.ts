// Restore an existing session from localStorage on app start.
// No silent guest auto-login: visitors are sent to /auth/login where they
// can either authenticate or click "Continuer en tant qu'invité".
export default defineNuxtPlugin(async () => {
  const auth = useAuthStore()
  const token = import.meta.client ? localStorage.getItem('pax_token') : null
  if (!token) return
  auth.token = token
  await auth.fetchMe()
})
