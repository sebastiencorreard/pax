<template>
  <div class="min-h-screen flex flex-col" style="background:var(--color-bg);color:var(--color-text)">
    <!-- Barre de navigation -->
    <nav class="border-b px-6 py-3 flex items-center justify-between"
         style="background:var(--color-surface);border-color:var(--color-border)">

      <NuxtLink to="/" class="font-bold text-xl tracking-tight" style="color:var(--color-primary)">
        PAX
        <span class="font-normal text-sm ml-1" style="color:var(--color-text-muted)">
          Progrès en Automatismes
        </span>
      </NuxtLink>

      <div class="flex items-center gap-4">
        <!-- Sélecteur de langue -->
        <button v-for="loc in availableLocales" :key="loc.code"
                @click="setLocale(loc.code)"
                class="text-xs px-2 py-1 rounded border"
                :style="locale === loc.code
                  ? 'background:var(--color-primary);color:#fff;border-color:var(--color-primary)'
                  : 'border-color:var(--color-border);color:var(--color-text-muted)'">
          {{ loc.code.toUpperCase() }}
        </button>

        <!-- Toggle thème -->
        <button @click="toggleDark()" class="p-2 rounded-lg hover:bg-gray-100 dark:hover:bg-slate-700"
                :title="isDark ? 'Mode clair' : 'Mode sombre'">
          <span v-if="isDark">☀️</span>
          <span v-else>🌙</span>
        </button>

        <template v-if="auth.isLoggedIn">
          <span class="text-sm" style="color:var(--color-text-muted)">
            {{ auth.fullName }}
            <span class="ml-1 px-1.5 py-0.5 rounded text-xs"
                  style="background:var(--color-primary);color:#fff">
              {{ auth.user?.role }}
            </span>
          </span>
          <button @click="auth.logout(); navigateTo('/auth/login')"
                  class="text-sm px-3 py-1.5 rounded border"
                  style="border-color:var(--color-border);color:var(--color-text-muted)">
            {{ $t('auth.logout') }}
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
const isDark = inject('isDark') as Ref<boolean>
const toggleDark = inject('toggleDark') as () => void
const { locale, locales, setLocale } = useI18n()
const availableLocales = locales
</script>
