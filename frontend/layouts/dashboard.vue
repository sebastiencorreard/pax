<template>
  <div class="flex h-screen overflow-hidden"
       style="background:var(--color-bg);color:var(--color-text)">

    <LayoutAppSidebar :open="sidebarOpen" @close="sidebarOpen = false" />

    <div class="flex flex-col flex-1 min-w-0 overflow-hidden">

      <!-- Topbar -->
      <header class="h-14 flex-shrink-0 flex items-center gap-3 px-4 border-b"
              style="background:var(--color-surface);border-color:var(--color-border)">
        <!-- Burger mobile -->
        <button type="button"
                class="lg:hidden p-1.5 rounded hover:bg-black/5 dark:hover:bg-white/5"
                style="color:var(--color-text-muted)"
                @click="sidebarOpen = true">
          <svg class="w-5 h-5" fill="none" stroke="currentColor" viewBox="0 0 24 24">
            <path stroke-linecap="round" stroke-linejoin="round" stroke-width="2"
                  d="M4 6h16M4 12h16M4 18h16" />
          </svg>
        </button>

        <!-- Retour mobile -->
        <button v-if="route.path !== '/'"
                type="button"
                @click="router.back()"
                class="lg:hidden flex items-center gap-1 px-2 py-1.5 rounded text-sm font-medium hover:bg-black/5 dark:hover:bg-white/5"
                style="color:var(--color-primary)">
          ← {{ $t('nav.back') }}
        </button>

        <span class="flex-1" />

        <!-- Chrono — published by ExercisePlayer via useChronoState() when an
             exercise with a scoredelay is loaded. Living in the topbar keeps
             the countdown in view as the student scrolls a long énoncé. -->
        <ExerciseTimer v-if="chronoState.chrono.value"
                       :chrono="chronoState.chrono.value"
                       :frozen="chronoState.frozen.value" />

        <!-- Langue -->

        <div ref="langPicker" class="relative">
          <button type="button"
                  @click="langOpen = !langOpen"
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

        <!-- Étoiles -->
        <span class="text-xs px-2 py-1 rounded font-semibold"
              style="background:var(--color-bg);color:#b45309"
              :title="$t('exercise.coins_title')">
          ⭐ {{ formatCoins(coins) }}
        </span>

        <!-- Utilisateur + déconnexion -->
        <span class="text-sm hidden sm:block" style="color:var(--color-text-muted)">
          {{ auth.fullName }}
        </span>
        <button type="button"
                @click="auth.logout(); navigateTo('/auth/login')"
                :title="$t('auth.logout')"
                class="text-xl leading-none w-9 h-9 flex items-center justify-center rounded border hover:bg-black/5 dark:hover:bg-white/5"
                style="border-color:var(--color-border);color:var(--color-text-muted)">
          ⎋
        </button>
      </header>

      <!-- Contenu -->
      <main class="flex-1 overflow-y-auto">
        <slot />
      </main>

    </div>
  </div>
</template>

<script setup lang="ts">
import ExerciseTimer from '~/components/exercise/ExerciseTimer.vue'

const auth = useAuthStore()
const route = useRoute()
const router = useRouter()
const { coins, formatCoins } = useCoins()
const { locale, locales, setLocale } = useI18n()
const availableLocales = locales
const chronoState = useChronoState()

const sidebarOpen = ref(false)
const langOpen = ref(false)
const langPicker = ref<HTMLElement | null>(null)

const FLAGS: Record<string, string> = { fr: '🇫🇷', nl: '🇳🇱', en: '🇬🇧' }
function flagFor(code: string) { return FLAGS[code] ?? '🌐' }
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
