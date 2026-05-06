<template>
  <div class="min-h-screen flex items-center justify-center px-4" style="background:var(--color-bg)">
    <div class="w-full max-w-md p-8 rounded-2xl border" style="background:var(--color-surface);border-color:var(--color-border)">
      <h1 class="text-2xl font-bold mb-2">{{ $t('auth.change_password_title') }}</h1>
      <p class="text-sm mb-6" style="color:var(--color-text-muted)">
        {{ $t('auth.change_password_desc') }}
      </p>

      <form @submit.prevent="handleSubmit" class="space-y-4">
        <div v-if="!auth.user?.must_change_password">
          <label class="block text-sm font-medium mb-1">{{ $t('auth.current_password') }}</label>
          <input v-model="form.current_password" type="password" required
                 class="w-full px-4 py-2 rounded-lg border focus:ring-2 outline-none transition"
                 style="background:var(--color-bg);border-color:var(--color-border);color:var(--color-text)" />
        </div>

        <div>
          <label class="block text-sm font-medium mb-1">{{ $t('auth.new_password') }}</label>
          <input v-model="form.new_password" type="password" required
                 class="w-full px-4 py-2 rounded-lg border focus:ring-2 outline-none transition"
                 style="background:var(--color-bg);border-color:var(--color-border);color:var(--color-text)" />
        </div>

        <div>
          <label class="block text-sm font-medium mb-1">{{ $t('auth.confirm_password') }}</label>
          <input v-model="form.confirm_password" type="password" required
                 class="w-full px-4 py-2 rounded-lg border focus:ring-2 outline-none transition"
                 style="background:var(--color-bg);border-color:var(--color-border);color:var(--color-text)" />
        </div>

        <button type="submit" :disabled="loading"
                class="w-full py-2.5 rounded-xl font-semibold text-white transition-all active:scale-95 disabled:opacity-50"
                style="background:var(--color-primary)">
          {{ loading ? '...' : $t('auth.change_password_submit') }}
        </button>

        <p v-if="error" class="text-center text-sm text-red-500 mt-2">{{ error }}</p>
      </form>
    </div>
  </div>
</template>

<script setup lang="ts">
definePageMeta({ layout: false })

const { apiFetch } = useApi()
const auth = useAuthStore()

const form = ref({
  current_password: '',
  new_password: '',
  confirm_password: ''
})
const loading = ref(false)
const error = ref('')

async function handleSubmit() {
  if (form.value.new_password !== form.value.confirm_password) {
    error.value = "Les mots de passe ne correspondent pas"
    return
  }
  
  loading.value = true
  error.value = ''
  try {
    await apiFetch('/api/auth/change-password', {
      method: 'POST',
      body: form.value
    })
    // Mettre à jour le store local
    await auth.fetchMe()
    // Rediriger vers l'accueil
    await navigateTo('/')
  } catch (e: any) {
    error.value = e?.data?.detail || "Une erreur est survenue"
  } finally {
    loading.value = false
  }
}
</script>
