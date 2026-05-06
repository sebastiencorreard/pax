<template>
  <div class="px-6 py-6 max-w-sm">
    <h1 class="text-2xl font-bold mb-6">{{ $t('classes.new') }}</h1>

    <form @submit.prevent="submit" class="space-y-4">
      <div>
        <label class="block text-sm font-medium mb-1">{{ $t('classes.field_name') }} *</label>
        <input v-model="name" required type="text"
               class="w-full rounded-lg border px-3 py-2 text-sm"
               style="background:var(--color-surface);border-color:var(--color-border);color:var(--color-text)" />
      </div>

      <p v-if="error" class="text-sm text-red-500">{{ error }}</p>

      <button type="submit" :disabled="saving"
              class="w-full py-2 rounded-lg text-sm font-medium text-white disabled:opacity-50"
              style="background:var(--color-primary)">
        {{ saving ? '…' : $t('classes.new') }}
      </button>
    </form>
  </div>
</template>

<script setup lang="ts">
definePageMeta({ layout: 'dashboard', middleware: ['teacher'] })

const { apiFetch } = useApi()

const name = ref('')
const saving = ref(false)
const error = ref('')

async function submit() {
  saving.value = true
  error.value = ''
  try {
    const cls = await apiFetch<{ id: number }>('/api/classes/', { method: 'POST', body: { name: name.value } })
    await navigateTo(`/classes/${cls.id}`)
  } catch (e: any) {
    error.value = e?.data?.detail || String(e)
  } finally {
    saving.value = false
  }
}
</script>
