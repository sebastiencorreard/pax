<template>
  <div class="relative" ref="root">
    <div class="relative">
      <input
        v-model="query"
        type="text"
        :placeholder="$t('register.etab_placeholder')"
        autocomplete="off"
        class="w-full px-3 py-2 pr-10 rounded-lg border outline-none transition"
        :style="{
          background: 'var(--color-bg)',
          borderColor: modelValue ? 'var(--color-success)' : 'var(--color-border)',
          color: 'var(--color-text)'
        }"
        @input="onInput"
        @focus="onFocus"
        @keydown.escape="open = false"
        @keydown.down.prevent="moveFocus(1)"
        @keydown.up.prevent="moveFocus(-1)"
        @keydown.enter.prevent="selectFocused"
      />
      
      <!-- Indicateur de sélection / Clear -->
      <div class="absolute inset-y-0 right-0 flex items-center px-3 gap-2">
        <span v-if="modelValue && !open" class="text-green-600 text-lg">✓</span>
        <button v-if="query" type="button" @click="clear" 
                class="hover:opacity-70 transition"
                style="color:var(--color-text-muted)">
          <svg xmlns="http://www.w3.org/2000/svg" class="h-4 w-4" fill="none" viewBox="0 0 24 24" stroke="currentColor">
            <path stroke-linecap="round" stroke-linejoin="round" stroke-width="2" d="M6 18L18 6M6 6l12 12" />
          </svg>
        </button>
      </div>
    </div>

    <!-- Résultats -->
    <ul v-if="open && results.length"
        class="absolute z-50 w-full mt-1 rounded-lg border shadow-lg overflow-y-auto max-h-64"
        style="background:var(--color-surface);border-color:var(--color-border)">
      <li v-for="(etab, i) in results" :key="etab.id"
          @mousedown.prevent="select(etab)"
          class="px-3 py-2 cursor-pointer text-sm"
          :class="i === focused ? 'font-medium' : 'hover:bg-black/5 dark:hover:bg-white/5'"
          :style="i === focused ? 'background:color-mix(in srgb,var(--color-primary) 10%,transparent)' : ''">
        <span class="font-medium">{{ etab.name }}</span>
        <span class="ml-2 text-xs" style="color:var(--color-text-muted)">
          {{ etab.commune }} {{ etab.code_postal }}
          <span class="ml-1 font-mono">{{ etab.uai }}</span>
        </span>
      </li>
    </ul>

    <p v-if="open && !results.length && query.length >= 2 && !loading"
       class="absolute z-50 w-full mt-1 px-3 py-2 rounded-lg border text-sm"
       style="background:var(--color-surface);border-color:var(--color-border);color:var(--color-text-muted)">
      {{ $t('register.etab_no_result') }}
    </p>
  </div>
</template>

<script setup lang="ts">
interface Etab { id: number; uai: string; name: string; commune: string | null; code_postal: string | null }

const props = defineProps<{ modelValue: Etab | null }>()
const emit = defineEmits<{ 'update:modelValue': [Etab | null] }>()

const config = useRuntimeConfig()
const query = ref('')
const results = ref<Etab[]>([])
const open = ref(false)
const loading = ref(false)
const focused = ref(-1)
const root = ref<HTMLElement | null>(null)

// Initialisation si déjà sélectionné
onMounted(() => {
  if (props.modelValue) query.value = props.modelValue.name
})

// Synchro si modelValue change de l'extérieur
watch(() => props.modelValue, (newVal) => {
  if (newVal) query.value = newVal.name
  else if (!open.value) query.value = ''
})

let debounceTimer: ReturnType<typeof setTimeout> | null = null

function onInput() {
  if (props.modelValue) emit('update:modelValue', null)
  open.value = false
  if (debounceTimer) clearTimeout(debounceTimer)
  if (query.value.length < 2) { results.value = []; return }
  debounceTimer = setTimeout(search, 300)
}

function onFocus() {
  if (results.value.length > 0 && query.value.length >= 2) {
    open.value = true
  }
}

async function search() {
  loading.value = true
  try {
    results.value = await $fetch<Etab[]>(
      `${config.public.apiBase}/api/etablissements/search`,
      { query: { q: query.value } }
    )
    open.value = true
    focused.value = -1
  } catch { results.value = [] }
  finally { loading.value = false }
}

function select(etab: Etab) {
  emit('update:modelValue', etab)
  query.value = etab.name
  open.value = false
}

function clear() {
  emit('update:modelValue', null)
  query.value = ''
  results.value = []
  open.value = false
}

function moveFocus(dir: 1 | -1) {
  if (!open.value) return
  focused.value = Math.max(-1, Math.min(results.value.length - 1, focused.value + dir))
}

function selectFocused() {
  if (focused.value >= 0) select(results.value[focused.value])
}

function onDocClick(e: MouseEvent) {
  if (root.value && !root.value.contains(e.target as Node)) open.value = false
}
onMounted(() => document.addEventListener('click', onDocClick))
onBeforeUnmount(() => document.removeEventListener('click', onDocClick))
</script>
