<template>
  <div>
    <template v-if="auth.isLoggedIn">
      <h1 class="text-2xl font-bold mb-1">{{ $t('home.greeting', { name: auth.user?.first_name }) }}</h1>
      <p class="mb-8" style="color:var(--color-text-muted)">
        {{ $t('home.question') }}
      </p>

      <div class="grid grid-cols-1 sm:grid-cols-2 gap-4">
        <NuxtLink to="/exercise"
                  class="rounded-xl p-6 border hover:shadow-md transition group"
                  style="background:var(--color-surface);border-color:var(--color-border)">
          <div class="text-3xl mb-3">📐</div>
          <h2 class="font-semibold text-lg group-hover:text-blue-500 transition">{{ $t('nav.exercises') }}</h2>
          <p class="text-sm mt-1" style="color:var(--color-text-muted)">
            {{ $t('home.exercises_desc') }}
          </p>
        </NuxtLink>

        <NuxtLink v-if="auth.isTeacher" to="/sheets"
                  class="rounded-xl p-6 border hover:shadow-md transition group"
                  style="background:var(--color-surface);border-color:var(--color-border)">
          <div class="text-3xl mb-3">📋</div>
          <h2 class="font-semibold text-lg group-hover:text-blue-500 transition">{{ $t('nav.sheets') }}</h2>
          <p class="text-sm mt-1" style="color:var(--color-text-muted)">
            {{ $t('home.sheets_desc') }}
          </p>
        </NuxtLink>
      </div>
    </template>

    <template v-else>
      <div class="text-center py-20">
        <h1 class="text-4xl font-bold mb-4">PAX</h1>
        <p class="text-xl mb-2" style="color:var(--color-text-muted)">
          {{ $t('app.title').replace('PAX — ', '') }}
        </p>
        <p class="mb-8" style="color:var(--color-text-muted)">
          {{ $t('app.subtitle') }}
        </p>
        <NuxtLink to="/auth/login"
                  class="px-6 py-3 rounded-lg font-medium text-lg"
                  style="background:var(--color-primary);color:#fff">
          {{ $t('home.login_cta') }}
        </NuxtLink>
      </div>
    </template>
  </div>
</template>

<script setup lang="ts">
const auth = useAuthStore()
</script>
