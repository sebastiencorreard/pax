<template>
  <div class="min-h-screen flex flex-col" style="background:var(--color-bg);color:var(--color-text)">
    <!-- Barre de navigation -->
    <nav class="border-b px-6 py-3 flex items-center justify-between"
         style="background:var(--color-surface);border-color:var(--color-border)">

      <NuxtLink to="/" class="inline-flex items-center" aria-label="PAX">
        <img src="/pax.svg" alt="PAX" class="h-8 w-auto" />
      </NuxtLink>

      <div class="flex items-center gap-4">
        <!-- Language picker — flag button opens the dropdown -->
        <div ref="langPicker" class="relative">
          <button type="button"
                  @click="langOpen = !langOpen"
                  :aria-label="$t('lang.choose')"
                  :title="$t('lang.choose')"
                  class="text-2xl leading-none p-1 rounded hover:bg-black/5 dark:hover:bg-white/5">
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
              <span class="text-lg">{{ flagFor(loc.code) }}</span>
              <span>{{ loc.name }}</span>
            </button>
          </div>
        </div>

        <template v-if="auth.isLoggedIn">
          <span class="text-sm" style="color:var(--color-text-muted)">
            {{ auth.fullName }}
            <span class="ml-1 px-1.5 py-0.5 rounded text-xs"
                  style="background:var(--color-primary);color:#fff">
              {{ auth.user?.role }}
            </span>
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

        <template v-else>
          <NuxtLink to="/auth/login"
                    class="text-sm px-4 py-1.5 rounded font-medium"
                    style="background:var(--color-primary);color:#fff">
            {{ $t('home.login_cta') }}
          </NuxtLink>
        </template>
      </div>
    </nav>

    <!-- Contenu -->
    <main class="flex-1 container mx-auto px-4 py-8 max-w-4xl">
      <slot />
    </main>

    <!-- Pied de page -->
    <footer class="border-t py-4 text-center text-xs"
            style="border-color:var(--color-border);color:var(--color-text-muted)">
      PAX · AGPL-3.0 · Progrès en Automatismes par les eXercices
    </footer>
  </div>
</template>

<script setup lang="ts">
const auth = useAuthStore()
const { locale, locales, setLocale } = useI18n()
const availableLocales = locales

const langOpen = ref(false)
const langPicker = ref<HTMLElement | null>(null)

const FLAGS: Record<string, string> = {
  fr: '🇫🇷',
  nl: '🇳🇱',
  en: '🇬🇧',
}
function flagFor(code: string): string {
  return FLAGS[code] ?? '🌐'
}

function pickLocale(code: string) {
  setLocale(code as 'fr' | 'nl' | 'en')
  langOpen.value = false
}

// Close the dropdown when clicking outside.
function onDocClick(e: MouseEvent) {
  if (!langOpen.value) return
  const root = langPicker.value
  if (root && !root.contains(e.target as Node)) langOpen.value = false
}
onMounted(() => document.addEventListener('click', onDocClick))
onBeforeUnmount(() => document.removeEventListener('click', onDocClick))
</script>
