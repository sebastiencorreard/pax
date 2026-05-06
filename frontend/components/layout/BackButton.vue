<template>
  <button type="button"
          @click="router.back()"
          class="text-sm hover:underline"
          style="color:var(--color-text-muted)">
    ← {{ label }}
  </button>
</template>

<script setup lang="ts">
defineProps<{ label: string }>()
const router = useRouter()
</script>
