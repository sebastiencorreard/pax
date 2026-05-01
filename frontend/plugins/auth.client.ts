export default defineNuxtPlugin(async () => {
  const auth = useAuthStore()
  const token = localStorage.getItem('pax_token')
  if (token) {
    auth.token = token
    await auth.fetchMe()
    if (auth.isLoggedIn) return
  }
  try {
    await auth.login('guest@pax.fr', 'guest1234')
  } catch {
    // Guest login failed (user not seeded?) — leave anonymous.
  }
})
