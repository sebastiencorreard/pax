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
                 placeholder="prof@ac-aix-marseille.fr" />
        </div>

        <div>
          <label class="block text-sm font-medium mb-1">{{ $t('auth.password') }}</label>
          <div class="relative">
            <input v-model="password" :type="showPassword ? 'text' : 'password'" required
                   autocomplete="current-password"
                   class="w-full px-3 py-2 pr-10 rounded-lg border outline-none transition"
                   style="background:var(--color-bg);border-color:var(--color-border);color:var(--color-text)" />
            <button type="button" @click="showPassword = !showPassword" tabindex="-1"
                    class="absolute inset-y-0 right-0 flex items-center px-3"
                    style="color:var(--color-text-muted)">
              <svg v-if="showPassword" xmlns="http://www.w3.org/2000/svg" class="h-4 w-4" fill="none" viewBox="0 0 24 24" stroke="currentColor">
                <path stroke-linecap="round" stroke-linejoin="round" stroke-width="2" d="M13.875 18.825A10.05 10.05 0 0112 19c-5 0-9-4-9-7s4-7 9-7a10.05 10.05 0 011.875.175M15 12a3 3 0 11-6 0 3 3 0 016 0z" />
                <path stroke-linecap="round" stroke-linejoin="round" stroke-width="2" d="M3 3l18 18" />
              </svg>
              <svg v-else xmlns="http://www.w3.org/2000/svg" class="h-4 w-4" fill="none" viewBox="0 0 24 24" stroke="currentColor">
                <path stroke-linecap="round" stroke-linejoin="round" stroke-width="2" d="M15 12a3 3 0 11-6 0 3 3 0 016 0z" />
                <path stroke-linecap="round" stroke-linejoin="round" stroke-width="2" d="M2.458 12C3.732 7.943 7.523 5 12 5c4.477 0 8.268 2.943 9.542 7-1.274 4.057-5.065 7-9.542 7-4.477 0-8.268-2.943-9.542-7z" />
              </svg>
            </button>
          </div>
        </div>

        <div v-if="error" class="text-sm px-3 py-2 rounded-lg"
             style="background:color-mix(in srgb,var(--color-error) 15%,transparent);color:var(--color-error)">
          {{ error }}
        </div>

        <button type="submit" :disabled="loading"
                class="w-full py-2.5 rounded-lg font-medium transition disabled:opacity-60"
                style="background:var(--color-primary);color:#fff">
          {{ loading ? $t('auth.submitting') : $t('auth.submit') }}
        </button>
      </form>

      <div class="flex items-center my-5 gap-3" style="color:var(--color-text-muted)">
        <div class="flex-1 h-px" style="background:var(--color-border)"></div>
        <span class="text-xs uppercase tracking-wider">{{ $t('auth.or') }}</span>
        <div class="flex-1 h-px" style="background:var(--color-border)"></div>
      </div>

      <button type="button" :disabled="loading" @click="continueAsGuest"
              class="w-full py-2.5 rounded-lg font-medium border transition disabled:opacity-60 hover:bg-black/5 dark:hover:bg-white/5"
              style="border-color:var(--color-border);color:var(--color-text)">
        {{ $t('auth.continue_as_guest') }}
      </button>

      <p class="text-center text-sm mt-6" style="color:var(--color-text-muted)">
        {{ $t('auth.teacher_prompt') }}
        <NuxtLink to="/auth/register"
                  class="font-medium hover:underline"
                  style="color:var(--color-primary)">
          {{ $t('auth.create_teacher_account') }}
        </NuxtLink>
      </p>
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
const showPassword = ref(false)
const error = ref('')
const loading = ref(false)

async function submit() {
  error.value = ''
  loading.value = true
  try {
    await auth.login(email.value, password.value)
    await navigateTo((route.query.redirect as string) || '/')
  } catch (e: any) {
    error.value = e?.data?.detail || t('auth.error_default')
  } finally {
    loading.value = false
  }
}

async function continueAsGuest() {
  error.value = ''
  loading.value = true
  try {
    await auth.loginAsGuest()
    await navigateTo((route.query.redirect as string) || '/')
  } catch (e: any) {
    error.value = e?.data?.detail || t('auth.guest_unavailable')
  } finally {
    loading.value = false
  }
}
</script>
