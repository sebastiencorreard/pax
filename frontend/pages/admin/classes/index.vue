<script setup lang="ts">
definePageMeta({ middleware: ['admin'] })
await navigateTo('/classes', { replace: true })
</script>
