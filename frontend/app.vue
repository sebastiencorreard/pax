<template>
  <div :class="{ dark: isDark }">
    <NuxtLayout>
      <NuxtPage />
    </NuxtLayout>
  </div>
</template>

<script setup lang="ts">
const isDark = ref(false)

// Respecte la préférence système
onMounted(() => {
  isDark.value = window.matchMedia('(prefers-color-scheme: dark)').matches
  const stored = localStorage.getItem('pax_theme')
  if (stored) isDark.value = stored === 'dark'
})

// Expose le toggle pour les composants enfants
provide('toggleDark', () => {
  isDark.value = !isDark.value
  localStorage.setItem('pax_theme', isDark.value ? 'dark' : 'light')
})
provide('isDark', isDark)
</script>
