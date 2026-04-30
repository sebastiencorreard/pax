export default defineNuxtPlugin(() => {
  const auth = useAuthStore()
  const token = localStorage.getItem('pax_token')
  if (token) {
    auth.token = token
    auth.fetchMe()
  }
})
