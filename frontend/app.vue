<template>
  <NuxtLayout>
    <NuxtPage />
  </NuxtLayout>
</template>

<script setup lang="ts">
const auth = useAuthStore()
const { init, watchSystem } = useTheme()

onMounted(() => {
  init()
  watchSystem()
})

// Réapplique le thème dès que le profil utilisateur est chargé (après login / restore)
watch(() => auth.user?.theme, () => init())
</script>
