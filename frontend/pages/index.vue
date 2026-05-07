<template>
  <div class="px-6 py-6">
    <p class="text-2xl font-semibold mb-1">{{ $t('home.greeting', { name: auth.fullName }) }}</p>
    <p class="mb-8 text-sm" style="color:var(--color-text-muted)">{{ $t('home.question') }}</p>

    <div class="grid grid-cols-1 sm:grid-cols-2 gap-4">
      <NuxtLink v-for="tile in tiles" :key="tile.to" :to="tile.to"
                class="group rounded-xl border p-6 flex flex-col gap-3 hover:shadow-md transition"
                style="background:var(--color-surface);border-color:var(--color-border)">
        <span class="text-4xl">{{ tile.icon }}</span>
        <div>
          <p class="font-semibold text-base group-hover:underline">{{ tile.title }}</p>
          <p class="text-sm mt-1" style="color:var(--color-text-muted)">{{ tile.desc }}</p>
        </div>
      </NuxtLink>
    </div>
  </div>
</template>

<script setup lang="ts">
definePageMeta({ layout: 'dashboard', middleware: ['teacher'] })

const auth = useAuthStore()
const { t } = useI18n()

const tiles = computed(() => {
  const base = [
    { icon: '📐', title: t('home.exercises_title'), desc: t('home.exercises_desc'), to: '/exercise' },
    { icon: '🏷️', title: t('home.library_title'),   desc: t('home.library_desc'),   to: '/library'  },
    { icon: '📋', title: t('home.sheets_title'),    desc: t('home.sheets_desc'),    to: '/sheets'   },
    { icon: '👥', title: t('home.classes_title'),   desc: t('home.classes_desc'),   to: '/classes'  },
  ]
  if (auth.isAdmin) {
    base.push({ icon: '👤', title: t('home.users_title'), desc: t('home.users_desc'), to: '/admin/users' })
  }
  base.push({ icon: '🙍', title: t('nav.account'), desc: t('home.account_desc'), to: '/account' })
  return base
})
</script>
