<template>
  <div class="px-6 py-6 max-w-sm">
    <h1 class="text-2xl font-bold mb-6">{{ $t('admin.new_user') }}</h1>

    <form @submit.prevent="submit" class="space-y-4">
      <div class="grid grid-cols-2 gap-3">
        <div>
          <label class="block text-sm font-medium mb-1">{{ $t('admin.field_first_name') }} *</label>
          <input v-model="form.first_name" required type="text"
                 class="w-full rounded-lg border px-3 py-2 text-sm"
                 style="background:var(--color-surface);border-color:var(--color-border);color:var(--color-text)" />
        </div>
        <div>
          <label class="block text-sm font-medium mb-1">{{ $t('admin.field_last_name') }} *</label>
          <input v-model="form.last_name" required type="text"
                 class="w-full rounded-lg border px-3 py-2 text-sm"
                 style="background:var(--color-surface);border-color:var(--color-border);color:var(--color-text)" />
        </div>
      </div>
      <div>
        <label class="block text-sm font-medium mb-1">{{ $t('admin.field_email') }} *</label>
        <input v-model="form.email" required type="email"
               class="w-full rounded-lg border px-3 py-2 text-sm"
               style="background:var(--color-surface);border-color:var(--color-border);color:var(--color-text)" />
      </div>
      <div>
        <label class="block text-sm font-medium mb-1">{{ $t('admin.field_role') }} *</label>
        <select v-model="form.role"
                class="w-full rounded-lg border px-3 py-2 text-sm"
                style="background:var(--color-surface);border-color:var(--color-border);color:var(--color-text)">
          <option value="student">{{ $t('admin.role_student') }}</option>
          <option value="teacher">{{ $t('admin.role_teacher') }}</option>
          <option value="admin">{{ $t('admin.role_admin') }}</option>
        </select>
      </div>
      <div>
        <label class="block text-sm font-medium mb-1">{{ $t('admin.field_password') }} *</label>
        <input v-model="form.password" required type="password"
               class="w-full rounded-lg border px-3 py-2 text-sm"
               style="background:var(--color-surface);border-color:var(--color-border);color:var(--color-text)" />
      </div>

      <p v-if="error" class="text-sm text-red-500">{{ error }}</p>

      <button type="submit" :disabled="saving"
              class="w-full py-2 rounded-lg text-sm font-medium text-white disabled:opacity-50"
              style="background:var(--color-primary)">
        {{ saving ? '…' : $t('admin.save') }}
      </button>
    </form>
  </div>
</template>

<script setup lang="ts">
definePageMeta({ layout: 'dashboard', middleware: ['admin'] })

const { apiFetch } = useApi()

const form = reactive({ first_name: '', last_name: '', email: '', role: 'student', password: '' })
const saving = ref(false)
const error = ref('')

async function submit() {
  saving.value = true
  error.value = ''
  try {
    await apiFetch('/api/admin/users/', { method: 'POST', body: { ...form } })
    await navigateTo('/admin/users')
  } catch (e: any) {
    error.value = e?.data?.detail || String(e)
  } finally {
    saving.value = false
  }
}
</script>
