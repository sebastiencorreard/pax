<template>
  <NuxtLink :to="to"
            class="flex items-center gap-3 px-3 py-2 rounded-lg text-sm transition-colors"
            :class="isActive
              ? 'font-medium'
              : 'hover:bg-black/5 dark:hover:bg-white/5'"
            :style="isActive
              ? 'background:color-mix(in srgb,var(--color-primary) 12%,transparent);color:var(--color-primary)'
              : 'color:var(--color-text-muted)'"
            @click="$emit('click')">
    <span class="text-base leading-none w-5 text-center">{{ icon }}</span>
    <span>{{ label }}</span>
  </NuxtLink>
</template>

<script setup lang="ts">
const props = defineProps<{ to: string; icon: string; label: string }>()
defineEmits<{ click: [] }>()

const route = useRoute()
const isActive = computed(() => route.path === props.to || route.path.startsWith(props.to + '/'))
</script>
