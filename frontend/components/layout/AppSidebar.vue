<template>
  <!-- Overlay mobile -->
  <Transition name="fade">
    <div v-if="open"
         class="fixed inset-0 z-20 bg-black/40 lg:hidden"
         @click="$emit('close')" />
  </Transition>

  <!-- Panneau -->
  <aside :class="['fixed inset-y-0 left-0 z-30 flex flex-col w-56 border-r transition-transform duration-200 lg:static lg:translate-x-0 lg:z-auto lg:flex-shrink-0',
                   open ? 'translate-x-0' : '-translate-x-full']"
         style="background:var(--color-surface);border-color:var(--color-border)">

    <!-- Logo -->
    <div class="h-14 flex items-center px-5 border-b flex-shrink-0 gap-3"
         style="border-color:var(--color-border)">
      <NuxtLink to="/" aria-label="PAX" class="flex-1">
        <img src="/pax.svg" alt="PAX" class="h-6 w-auto" />
      </NuxtLink>
      <button v-if="isDev"
              type="button"
              @click="debugMode = !debugMode"
              :title="debugMode ? 'Masquer le debug' : 'Afficher le debug'"
              class="text-xs px-1.5 py-0.5 rounded font-mono border transition"
              :style="debugMode
                ? 'background:var(--color-primary);color:#fff;border-color:var(--color-primary)'
                : 'border-color:var(--color-border);color:var(--color-text-muted)'">
        dbg
      </button>
    </div>

    <!-- Navigation -->
    <nav class="flex-1 overflow-y-auto py-3 px-2">
      <LayoutSidebarLink to="/exercise" icon="📐" :label="$t('nav.exercises')" @click="$emit('close')" />

      <template v-if="auth.isTeacher">
        <LayoutSidebarLink to="/library" icon="🏷️" :label="$t('nav.library')" @click="$emit('close')" />

        <div class="my-2 mx-2 border-t" style="border-color:var(--color-border)" />

        <LayoutSidebarLink to="/sheets" icon="📋" :label="$t('nav.sheets')" @click="$emit('close')" />

        <div class="my-2 mx-2 border-t" style="border-color:var(--color-border)" />

        <LayoutSidebarLink to="/classes" icon="👥" :label="$t('nav.classes')" @click="$emit('close')" />
        <LayoutSidebarLink v-if="auth.isAdmin"
                     to="/admin/users" icon="👤" :label="$t('nav.users')" @click="$emit('close')" />
      </template>

      <div class="my-2 mx-2 border-t" style="border-color:var(--color-border)" />
      <LayoutSidebarLink to="/account" icon="🙍" :label="$t('nav.account')" @click="$emit('close')" />
    </nav>

  </aside>
</template>

<script setup lang="ts">
defineProps<{ open: boolean }>()
defineEmits<{ close: [] }>()

const auth = useAuthStore()
const { debugMode } = useDebugMode()
const isDev = import.meta.dev
</script>

<style scoped>
.fade-enter-active, .fade-leave-active { transition: opacity 0.15s; }
.fade-enter-from, .fade-leave-to { opacity: 0; }
</style>
