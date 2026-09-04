export default defineNuxtRouteMiddleware((to) => {
  const auth = useAuthStore()
  
  // Skip middleware for public auth pages to avoid redirect loops
  const publicRoutes = ['/auth/login', '/auth/register']
  // Les mentions légales s'adressent aussi à qui n'a pas de compte : conditions
  // d'utilisation, licences et manifeste doivent se lire sans se connecter —
  // les exiger derrière l'authentification vide la publication de son sens.
  if (to.path.startsWith('/legal/')) {
    return
  }
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
