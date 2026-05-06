<script setup lang="ts">
definePageMeta({ middleware: ['admin'] })
await navigateTo('/admin/users', { replace: true })
</script>
