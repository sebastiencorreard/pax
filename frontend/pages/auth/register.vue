<template>
  <div class="max-w-md mx-auto mt-12">
    <div class="rounded-xl p-8 shadow-sm border"
         style="background:var(--color-surface);border-color:var(--color-border)">

      <h1 class="text-2xl font-bold mb-2">{{ $t('register.title') }}</h1>
      <p class="text-sm mb-6" style="color:var(--color-text-muted)">
        {{ $t('register.subtitle') }}
      </p>

      <form @submit.prevent="register" class="space-y-4">
        <div class="grid grid-cols-2 gap-3">
          <div>
            <label class="block text-sm font-medium mb-1">{{ $t('admin.field_first_name') }} *</label>
            <input v-model="reg.first_name" required type="text"
                   class="w-full px-3 py-2 rounded-lg border outline-none transition"
                   style="background:var(--color-bg);border-color:var(--color-border);color:var(--color-text)" />
          </div>
          <div>
            <label class="block text-sm font-medium mb-1">{{ $t('admin.field_last_name') }} *</label>
            <input v-model="reg.last_name" required type="text"
                   class="w-full px-3 py-2 rounded-lg border outline-none transition"
                   style="background:var(--color-bg);border-color:var(--color-border);color:var(--color-text)" />
          </div>
        </div>

        <div>
          <label class="block text-sm font-medium mb-1">{{ $t('auth.email') }} *</label>
          <input v-model="reg.email" required type="email"
                 placeholder="prenom.nom@ac-aix-marseille.fr"
                 class="w-full px-3 py-2 rounded-lg border outline-none transition"
                 :style="emailError
                   ? 'background:var(--color-bg);border-color:var(--color-error);color:var(--color-text)'
                   : 'background:var(--color-bg);border-color:var(--color-border);color:var(--color-text)'" />
          <p v-if="emailError" class="mt-1 text-xs" style="color:var(--color-error)">{{ emailError }}</p>
        </div>

        <div>
          <label class="block text-sm font-medium mb-1">{{ $t('auth.password') }} *</label>
          <input v-model="reg.password" required type="password" minlength="8"
                 class="w-full px-3 py-2 rounded-lg border outline-none transition"
                 style="background:var(--color-bg);border-color:var(--color-border);color:var(--color-text)" />
          <p class="mt-1 text-xs" style="color:var(--color-text-muted)">
            {{ $t('register.password_hint') }}
          </p>
        </div>

        <div>
          <label class="block text-sm font-medium mb-1">{{ $t('register.etab_label') }} *</label>
          <EtabSearch v-model="reg.etab" />
          <p v-if="etabError" class="mt-1 text-xs" style="color:var(--color-error)">{{ etabError }}</p>
        </div>

        <div v-if="regError" class="text-sm px-3 py-2 rounded-lg"
             style="background:color-mix(in srgb,var(--color-error) 15%,transparent);color:var(--color-error)">
          {{ regError }}
        </div>

        <div v-if="regSuccess" class="text-sm px-3 py-2 rounded-lg"
             style="background:color-mix(in srgb,var(--color-success) 15%,transparent);color:var(--color-success)">
          {{ $t('register.success') }}
        </div>

        <button type="submit" :disabled="regLoading || !!regSuccess"
                class="w-full py-2.5 rounded-lg font-medium transition disabled:opacity-60"
                style="background:var(--color-primary);color:#fff">
          {{ regLoading ? '…' : $t('register.submit') }}
        </button>
      </form>

      <p class="text-center text-sm mt-6" style="color:var(--color-text-muted)">
        {{ $t('register.already_account') }}
        <NuxtLink to="/auth/login"
                  class="font-medium hover:underline"
                  style="color:var(--color-primary)">
          {{ $t('register.back_to_login') }}
        </NuxtLink>
      </p>
    </div>
  </div>
</template>

<script setup lang="ts">
definePageMeta({ layout: 'default' })

const { t } = useI18n()
const config = useRuntimeConfig()

interface Etab { id: number; name: string; commune: string | null }

const reg = reactive({
  first_name: '',
  last_name: '',
  email: '',
  password: '',
  etab: null as Etab | null,
})
const regLoading = ref(false)
const regError = ref('')
const regSuccess = ref(false)
const etabError = ref('')

const emailError = computed(() => {
  if (!reg.email) return ''
  if (!reg.email.toLowerCase().endsWith('@ac-aix-marseille.fr'))
    return t('register.email_domain_error')
  return ''
})

async function register() {
  regError.value = ''
  etabError.value = ''
  if (!reg.etab) { etabError.value = t('register.etab_required'); return }
  if (emailError.value) return

  regLoading.value = true
  try {
    await $fetch(`${config.public.apiBase}/api/auth/register`, {
      method: 'POST',
      body: {
        email: reg.email,
        first_name: reg.first_name,
        last_name: reg.last_name,
        password: reg.password,
        etab_id: reg.etab.id,
      },
    })
    regSuccess.value = true
  } catch (e: any) {
    const detail = e?.data?.detail
    if (Array.isArray(detail)) {
      regError.value = detail.map((d: any) => d.msg).join(' — ')
    } else {
      regError.value = detail || String(e)
    }
  } finally {
    regLoading.value = false
  }
}
</script>
