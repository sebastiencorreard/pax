export default defineNuxtRouteMiddleware((to) => {
  const auth = useAuthStore()
  
  // Skip middleware for the login page to avoid infinite redirect loops
  if (to.path === '/auth/login') {
    return
  }

  if (!auth.isLoggedIn) {
    return navigateTo(`/auth/login?redirect=${to.path}`)
  }
})
