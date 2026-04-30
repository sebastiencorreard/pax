<template>
  <div class="max-w-md mx-auto mt-16">
    <div class="rounded-xl p-8 shadow-sm border"
         style="background:var(--color-surface);border-color:var(--color-border)">

      <h1 class="text-2xl font-bold mb-2">{{ $t('auth.title') }}</h1>
      <p class="text-sm mb-6" style="color:var(--color-text-muted)">
        {{ $t('auth.welcome') }}
      </p>

      <form @submit.prevent="submit" class="space-y-4">
        <div>
          <label class="block text-sm font-medium mb-1">{{ $t('auth.email') }}</label>
          <input v-model="email" type="email" required autocomplete="email"
                 class="w-full px-3 py-2 rounded-lg border outline-none transition"
                 style="background:var(--color-bg);border-color:var(--color-border);color:var(--color-text)"
                 placeholder="prof@lycee.fr" />
        </div>

        <div>
          <label class="block text-sm font-medium mb-1">{{ $t('auth.password') }}</label>
          <input v-model="password" type="password" required autocomplete="current-password"
                 class="w-full px-3 py-2 rounded-lg border outline-none transition"
                 style="background:var(--color-bg);border-color:var(--color-border);color:var(--color-text)" />
        </div>

        <div v-if="error" class="text-sm px-3 py-2 rounded-lg"
             style="background:color-mix(in srgb, var(--color-error) 15%, transparent);color:var(--color-error)">
          {{ error }}
        </div>

        <button type="submit" :disabled="loading"
                class="w-full py-2.5 rounded-lg font-medium transition disabled:opacity-60"
                style="background:var(--color-primary);color:#fff">
          {{ loading ? $t('auth.submitting') : $t('auth.submit') }}
        </button>
      </form>
    </div>
  </div>
</template>

<script setup lang="ts">
definePageMeta({ layout: 'default' })

const { t } = useI18n()
const auth = useAuthStore()
const route = useRoute()

const email = ref('')
const password = ref('')
const error = ref('')
const loading = ref(false)

async function submit() {
  error.value = ''
  loading.value = true
  try {
    await auth.login(email.value, password.value)
    const redirect = (route.query.redirect as string) || '/'
    await navigateTo(redirect)
  } catch (e: any) {
    error.value = e?.data?.detail || t('auth.error_default')
  } finally {
    loading.value = false
  }
}
</script>
