// Les pages de travail d'une feuille sont celles de l'élève : l'API les
// refuse à un enseignant (403), qui suit ses feuilles depuis `/sheets`.
export default defineNuxtRouteMiddleware(() => {
  const auth = useAuthStore()
  if (!auth.isLoggedIn) return navigateTo('/auth/login')
  if (auth.isTeacher) return navigateTo('/sheets')
})
