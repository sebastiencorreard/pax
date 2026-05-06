<template>
  <div class="px-6 py-6">
    <div class="flex items-center justify-between mb-6">
      <h1 class="text-2xl font-bold">{{ $t('admin.users_title') }}</h1>
      <NuxtLink to="/admin/users/new"
                class="px-4 py-2 rounded-lg text-sm font-medium text-white"
                style="background:var(--color-primary)">
        + {{ $t('admin.new_user') }}
      </NuxtLink>
    </div>

    <!-- Filtre par rôle -->
    <div class="flex gap-2 mb-4 flex-wrap">
      <button v-for="r in roleFilters" :key="r.value" type="button"
              @click="roleFilter = r.value"
              class="px-3 py-1 rounded-full text-xs border transition"
              :style="roleFilter === r.value
                ? 'background:var(--color-primary);color:#fff;border-color:var(--color-primary)'
                : 'background:var(--color-surface);border-color:var(--color-border);color:var(--color-text-muted)'">
        {{ r.label }}
      </button>
    </div>

    <div v-if="loading" class="space-y-2">
      <div v-for="i in 5" :key="i" class="h-12 rounded-xl animate-pulse"
           style="background:var(--color-surface)"></div>
    </div>

    <div v-else-if="filtered.length === 0"
         class="text-center py-12 rounded-xl border text-sm"
         style="background:var(--color-surface);border-color:var(--color-border);color:var(--color-text-muted)">
      {{ $t('admin.empty_users') }}
    </div>

    <div v-else class="rounded-xl border overflow-hidden"
         style="background:var(--color-surface);border-color:var(--color-border)">
      <ul class="divide-y" style="border-color:var(--color-border)">
        <li v-for="user in filtered" :key="String(user.id)"
            class="px-5 py-3 flex items-center justify-between gap-4">
          <div class="min-w-0">
            <span class="font-medium text-sm">{{ user.first_name }} {{ user.last_name }}</span>
            <span v-if="user.email" class="ml-2 text-xs" style="color:var(--color-text-muted)">
              {{ user.email }}
            </span>
          </div>
          <div class="flex items-center gap-3 flex-shrink-0">
            <span class="text-xs px-2 py-0.5 rounded"
                  style="background:var(--color-bg);color:var(--color-text-muted)">
              {{ $t('admin.role_' + user.role) }}
            </span>
            <button type="button" @click="resetPassword(user)"
                    class="text-xs px-2 py-1 rounded border hover:bg-blue-50 dark:hover:bg-blue-900/20 transition"
                    style="border-color:var(--color-border);color:var(--color-primary)">
              {{ $t('admin.reset_password') }}
            </button>
            <button type="button" @click="deleteUser(user)"
                    class="text-xs px-2 py-1 rounded border hover:bg-red-50 dark:hover:bg-red-900/20 transition"
                    style="border-color:var(--color-border);color:#dc2626">
              {{ $t('admin.delete_user') }}
            </button>
          </div>
        </li>
      </ul>
    </div>

    <p v-if="error" class="mt-4 text-sm text-red-500">{{ error }}</p>

    <!-- Modal de succès reset password -->
    <div v-if="resetResult" class="fixed inset-0 bg-black/50 flex items-center justify-center p-4 z-50">
      <div class="w-full max-w-sm p-6 rounded-2xl shadow-xl" style="background:var(--color-surface)">
        <h3 class="text-lg font-bold mb-2">{{ $t('admin.reset_password') }}</h3>
        <p class="text-sm mb-4" style="color:var(--color-text-muted)">
          {{ $t('admin.reset_password_success', { name: resetResult.name }) }}
        </p>
        <div class="p-4 rounded-xl font-mono text-center text-lg mb-6" style="background:var(--color-bg);color:var(--color-primary)">
          {{ resetResult.password }}
        </div>
        <button @click="copyAndClose"
                class="w-full py-2 rounded-xl text-white font-medium"
                style="background:var(--color-primary)">
          {{ $t('admin.reset_password_copy') }}
        </button>
      </div>
    </div>
  </div>
</template>

<script setup lang="ts">
definePageMeta({ layout: 'dashboard', middleware: ['admin'] })

const { apiFetch } = useApi()
const { t } = useI18n()

interface User { id: string; email: string | null; first_name: string | null; last_name: string | null; role: string }

const users = ref<User[]>([])
const loading = ref(true)
const error = ref('')
const roleFilter = ref('all')
const resetResult = ref<{ name: string, password: string } | null>(null)

const roleFilters = computed(() => [
  { value: 'all', label: 'Tous' },
  { value: 'student', label: t('admin.role_student') },
  { value: 'teacher', label: t('admin.role_teacher') },
  { value: 'admin', label: t('admin.role_admin') },
])

const filtered = computed(() =>
  roleFilter.value === 'all' ? users.value : users.value.filter(u => u.role === roleFilter.value)
)

async function load() {
  loading.value = true
  error.value = ''
  try {
    users.value = await apiFetch<User[]>('/api/admin/users/')
  } catch (e: any) {
    error.value = e?.data?.detail || String(e)
  } finally {
    loading.value = false
  }
}

async function deleteUser(user: User) {
  const name = `${user.first_name} ${user.last_name}`.trim() || user.email || String(user.id)
  if (!confirm(t('admin.delete_user_confirm', { name }))) return
  try {
    await apiFetch(`/api/admin/users/${user.id}`, { method: 'DELETE' })
    users.value = users.value.filter(u => String(u.id) !== String(user.id))
  } catch (e: any) {
    error.value = e?.data?.detail || String(e)
  }
}

async function resetPassword(user: User) {
  const name = `${user.first_name} ${user.last_name}`.trim() || user.email || String(user.id)
  if (!confirm(t('admin.reset_password') + ' ?')) return
  
  try {
    const res = await apiFetch<{ temporary_password: string }>(`/api/admin/users/${user.id}/reset-password`, {
      method: 'POST'
    })
    resetResult.value = { name, password: res.temporary_password }
  } catch (e: any) {
    error.value = e?.data?.detail || String(e)
  }
}

async function copyAndClose() {
  if (resetResult.value && import.meta.client) {
    try {
      await navigator.clipboard.writeText(resetResult.value.password)
    } catch (err) {
      console.error('Failed to copy: ', err)
    }
    resetResult.value = null
  }
}

onMounted(load)
</script>
