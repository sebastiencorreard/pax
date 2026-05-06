<template>
  <div class="px-6 py-6 max-w-xl">
    <h1 class="text-2xl font-bold mb-6">{{ $t('sheets.new') }}</h1>

    <form @submit.prevent="submit" class="space-y-4">
      <div>
        <label class="block text-sm font-medium mb-1">{{ $t('sheets.field_title') }} *</label>
        <input v-model="form.title" required type="text"
               class="w-full rounded-lg border px-3 py-2 text-sm"
               style="background:var(--color-surface);border-color:var(--color-border);color:var(--color-text)" />
      </div>
      <div>
        <label class="block text-sm font-medium mb-1">{{ $t('sheets.field_description') }}</label>
        <textarea v-model="form.description" rows="3"
                  class="w-full rounded-lg border px-3 py-2 text-sm"
                  style="background:var(--color-surface);border-color:var(--color-border);color:var(--color-text)"></textarea>
      </div>
      <div class="grid grid-cols-2 gap-3">
        <div>
          <label class="block text-sm font-medium mb-1">{{ $t('sheets.field_level') }}</label>
          <input v-model="form.level" type="text" placeholder="H4"
                 class="w-full rounded-lg border px-3 py-2 text-sm"
                 style="background:var(--color-surface);border-color:var(--color-border);color:var(--color-text)" />
        </div>
        <div>
          <label class="block text-sm font-medium mb-1">{{ $t('sheets.field_domain') }}</label>
          <input v-model="form.domain" type="text"
                 class="w-full rounded-lg border px-3 py-2 text-sm"
                 style="background:var(--color-surface);border-color:var(--color-border);color:var(--color-text)" />
        </div>
      </div>
      <div>
        <label class="block text-sm font-medium mb-1">{{ $t('sheets.field_author') }}</label>
        <input v-model="form.author" type="text"
               class="w-full rounded-lg border px-3 py-2 text-sm"
               style="background:var(--color-surface);border-color:var(--color-border);color:var(--color-text)" />
      </div>
      <div>
        <label class="block text-sm font-medium mb-1">{{ $t('sheets.field_status') }}</label>
        <select v-model="form.status"
                class="w-full rounded-lg border px-3 py-2 text-sm"
                style="background:var(--color-surface);border-color:var(--color-border);color:var(--color-text)">
          <option :value="1">{{ $t('sheets.status_1') }}</option>
          <option :value="0">{{ $t('sheets.status_0') }}</option>
          <option :value="3">{{ $t('sheets.status_3') }}</option>
        </select>
      </div>

      <p v-if="error" class="text-sm text-red-500">{{ error }}</p>

      <button type="submit" :disabled="saving"
              class="w-full py-2 rounded-lg text-sm font-medium text-white disabled:opacity-50"
              style="background:var(--color-primary)">
        {{ saving ? '…' : $t('sheets.save') }}
      </button>
    </form>
  </div>
</template>

<script setup lang="ts">
definePageMeta({ layout: 'dashboard', middleware: ['teacher'] })

const { apiFetch } = useApi()
const { t } = useI18n()

const form = reactive({ title: '', description: '', author: '', level: '', domain: '', status: 1 })
const saving = ref(false)
const error = ref('')

async function submit() {
  saving.value = true
  error.value = ''
  try {
    const sheet = await apiFetch<{ id: number }>('/api/sheets/', {
      method: 'POST',
      body: {
        title: form.title,
        description: form.description || null,
        author: form.author || null,
        level: form.level || null,
        domain: form.domain || null,
        status: form.status,
      },
    })
    await navigateTo(`/sheets/${sheet.id}`)
  } catch (e: any) {
    error.value = e?.data?.detail || String(e)
  } finally {
    saving.value = false
  }
}
</script>
