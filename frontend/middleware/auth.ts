export default defineNuxtRouteMiddleware((to) => {
  const auth = useAuthStore()
  if (!auth.isLoggedIn) {
    return navigateTo(`/auth/login?redirect=${to.path}`)
  }
})
