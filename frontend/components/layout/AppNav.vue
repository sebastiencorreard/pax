<template>
  <nav class="border-b px-6 py-3 flex items-center justify-between"
       style="background:var(--color-surface);border-color:var(--color-border)">

    <NuxtLink to="/" class="inline-flex items-center" aria-label="PAX">
      <img src="/pax.svg" alt="PAX" class="h-6 w-auto" />
    </NuxtLink>

    <div class="flex items-center gap-4">
      <div ref="langPicker" class="relative">
        <button type="button"
                @click="langOpen = !langOpen"
                :aria-label="$t('lang.choose')"
                :title="$t('lang.choose')"
                class="text-base leading-none p-1 rounded hover:bg-black/5 dark:hover:bg-white/5">
          {{ flagFor(String(locale)) }}
        </button>
        <div v-if="langOpen"
             class="absolute right-0 mt-2 rounded-lg border shadow-lg overflow-hidden z-10 min-w-[10rem]"
             style="background:var(--color-surface);border-color:var(--color-border)">
          <button v-for="loc in availableLocales" :key="loc.code"
                  type="button"
                  @click="pickLocale(loc.code)"
                  class="w-full flex items-center gap-2 px-3 py-2 text-sm text-left hover:bg-black/5 dark:hover:bg-white/5"
                  :class="String(locale) === loc.code ? 'font-semibold' : ''">
            <span class="text-base">{{ flagFor(loc.code) }}</span>
            <span>{{ loc.name }}</span>
          </button>
        </div>
      </div>

      <template v-if="auth.isLoggedIn">
        <NuxtLink to="/account"
                  class="text-sm hover:underline"
                  style="color:var(--color-text-muted)">
          {{ auth.fullName }}
        </NuxtLink>
        <span v-if="auth.user && !ROLES_HIDDEN.has(auth.user.role)"
              class="px-1.5 py-0.5 rounded text-xs"
              style="background:var(--color-primary);color:#fff">
          {{ auth.user.role }}
        </span>
        <button type="button"
                @click="auth.logout(); navigateTo('/auth/login')"
                :aria-label="$t('auth.logout')"
                :title="$t('auth.logout')"
                class="text-xl leading-none w-9 h-9 inline-flex items-center justify-center rounded border hover:bg-black/5 dark:hover:bg-white/5"
                style="border-color:var(--color-border);color:var(--color-text-muted)">
          ⎋
        </button>
      </template>
    </div>
  </nav>
</template>

<script setup lang="ts">
const auth = useAuthStore()
const { locale, locales, setLocale } = useI18n()
const availableLocales = locales
const ROLES_HIDDEN = new Set(['guest', 'student'])

const langOpen = ref(false)
const langPicker = ref<HTMLElement | null>(null)

const FLAGS: Record<string, string> = { fr: '🇫🇷', nl: '🇳🇱', en: '🇬🇧' }
function flagFor(code: string): string { return FLAGS[code] ?? '🌐' }

function pickLocale(code: string) {
  setLocale(code as 'fr' | 'nl' | 'en')
  langOpen.value = false
}

function onDocClick(e: MouseEvent) {
  if (!langOpen.value) return
  if (langPicker.value && !langPicker.value.contains(e.target as Node)) langOpen.value = false
}
onMounted(() => document.addEventListener('click', onDocClick))
onBeforeUnmount(() => document.removeEventListener('click', onDocClick))
</script>
