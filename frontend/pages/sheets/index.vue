<template>
  <div class="px-6 py-6 px-6 py-6">
    <div class="flex items-center justify-between mb-6">
      <h1 class="text-2xl font-bold">{{ $t('sheets.title') }}</h1>
      <NuxtLink to="/sheets/new"
                class="px-4 py-2 rounded-lg text-sm font-medium text-white"
                style="background:var(--color-primary)">
        + {{ $t('sheets.new') }}
      </NuxtLink>
    </div>

    <div v-if="loading" class="space-y-3">
      <div v-for="i in 3" :key="i" class="h-20 rounded-xl animate-pulse"
           style="background:var(--color-surface)"></div>
    </div>

    <div v-else-if="sheets.length === 0"
         class="text-center py-16 rounded-xl border"
         style="background:var(--color-surface);border-color:var(--color-border);color:var(--color-text-muted)">
      <p class="text-4xl mb-4">📋</p>
      <p class="text-sm">{{ $t('sheets.empty') }}</p>
    </div>

    <div v-else class="space-y-3">
      <NuxtLink v-for="sheet in sheets" :key="sheet.id" :to="`/sheets/${sheet.id}`"
                class="block rounded-xl border px-5 py-4 hover:shadow-sm transition"
                style="background:var(--color-surface);border-color:var(--color-border)">
        <div class="flex items-start justify-between gap-4">
          <div class="min-w-0">
            <p class="font-semibold truncate">{{ sheet.title }}</p>
            <p v-if="sheet.description" class="text-sm truncate mt-0.5"
               style="color:var(--color-text-muted)">{{ sheet.description }}</p>
          </div>
          <span class="flex-shrink-0 text-xs px-2 py-1 rounded"
                :style="statusStyle(sheet.status)">
            {{ statusLabel(sheet.status) }}
          </span>
        </div>
        <div class="flex gap-3 mt-2 text-xs" style="color:var(--color-text-muted)">
          <span v-if="sheet.level">{{ sheet.level }}</span>
          <span v-if="sheet.domain">{{ sheet.domain }}</span>
          <span>{{ formatDate(sheet.created_at) }}</span>
        </div>
      </NuxtLink>
    </div>

    <p v-if="error" class="mt-4 text-sm text-red-500">{{ error }}</p>
  </div>
</template>

<script setup lang="ts">
definePageMeta({ layout: 'dashboard', middleware: ['teacher'] })

const { apiFetch } = useApi()
const { t } = useI18n()

interface Sheet {
  id: number
  title: string
  description: string | null
  level: string | null
  domain: string | null
  status: number
  created_at: string
}

const sheets = ref<Sheet[]>([])
const loading = ref(true)
const error = ref('')

async function load() {
  loading.value = true
  error.value = ''
  try {
    sheets.value = await apiFetch<Sheet[]>('/api/sheets/')
  } catch (e: any) {
    error.value = e?.data?.detail || String(e)
  } finally {
    loading.value = false
  }
}

function statusLabel(s: number) {
  if (s === 0) return t('sheets.status_0')
  if (s === 3) return t('sheets.status_3')
  return t('sheets.status_1')
}

function statusStyle(s: number) {
  if (s === 0) return 'background:var(--color-bg);color:var(--color-text-muted)'
  if (s === 3) return 'background:#fef3c7;color:#92400e'
  return 'background:#dcfce7;color:#166534'
}

function formatDate(iso: string) {
  return new Date(iso).toLocaleDateString()
}

onMounted(load)
</script>
