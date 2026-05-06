export default defineNuxtRouteMiddleware((to) => {
  const auth = useAuthStore()
  
  // Skip middleware for public auth pages to avoid redirect loops
  const publicRoutes = ['/auth/login', '/auth/register']
  if (publicRoutes.includes(to.path)) {
    return
  }

  if (!auth.isLoggedIn) {
    return navigateTo(`/auth/login?redirect=${to.path}`)
  }

  // Force password change if required
  if (auth.user?.must_change_password && to.path !== '/auth/change-password') {
    return navigateTo('/auth/change-password')
  }
})
