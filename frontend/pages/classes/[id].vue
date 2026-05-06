<template>
  <div class="px-6 py-6">
  <div v-if="loading" class="space-y-3">
    <div v-for="i in 3" :key="i" class="h-12 rounded-xl animate-pulse"
         style="background:var(--color-surface)"></div>
  </div>

  <div v-else-if="!cls" class="text-center py-16" style="color:var(--color-text-muted)">
    {{ $t('classes.not_found') }}
  </div>

  <div v-else>
    <div class="flex items-center justify-between mb-6">
      <h1 class="text-2xl font-bold">{{ cls.name }}</h1>
      <button type="button" @click="deleteClass"
              class="text-sm px-3 py-1.5 rounded-lg border hover:bg-red-50 dark:hover:bg-red-900/20 transition"
              style="border-color:var(--color-border);color:#dc2626">
        {{ $t('classes.delete') }}
      </button>
    </div>

    <!-- Liste des élèves -->
    <div class="rounded-xl border overflow-hidden mb-4"
         style="background:var(--color-surface);border-color:var(--color-border)">
      <div class="px-5 py-3 border-b font-semibold text-sm"
           style="border-color:var(--color-border)">
        {{ $t('classes.students_section') }}
      </div>

      <div v-if="cls.students.length === 0"
           class="px-5 py-8 text-sm text-center"
           style="color:var(--color-text-muted)">
        {{ $t('classes.no_students') }}
      </div>

      <ul v-else class="divide-y" style="border-color:var(--color-border)">
        <li v-for="student in cls.students" :key="String(student.id)"
            class="px-5 py-3 flex items-center justify-between">
          <div>
            <span class="text-sm font-medium">{{ student.first_name }} {{ student.last_name }}</span>
            <span v-if="student.email" class="ml-2 text-xs" style="color:var(--color-text-muted)">
              {{ student.email }}
            </span>
          </div>
          <button type="button" @click="removeStudent(student.id)"
                  class="text-xs px-2 py-1 rounded border hover:bg-red-50 dark:hover:bg-red-900/20 transition"
                  style="border-color:var(--color-border);color:#dc2626">
            {{ $t('classes.remove_student') }}
          </button>
        </li>
      </ul>

      <!-- Ajouter un élève -->
      <div class="px-5 py-3 border-t" style="border-color:var(--color-border)">
        <p class="text-xs font-medium mb-2">{{ $t('classes.add_student') }}</p>
        <div class="flex gap-2">
          <select v-model="selectedStudentId"
                  class="flex-1 rounded-lg border px-3 py-1.5 text-sm"
                  style="background:var(--color-bg);border-color:var(--color-border);color:var(--color-text)">
            <option value="">{{ $t('classes.select_student') }}</option>
            <option v-for="s in availableStudents" :key="String(s.id)" :value="String(s.id)">
              {{ s.last_name }} {{ s.first_name }}
              <template v-if="s.email"> — {{ s.email }}</template>
            </option>
          </select>
          <button type="button" :disabled="!selectedStudentId || adding" @click="addStudent"
                  class="px-3 py-1.5 rounded-lg text-sm font-medium text-white disabled:opacity-50"
                  style="background:var(--color-primary)">
            +
          </button>
        </div>
        <p v-if="addError" class="text-xs text-red-500 mt-1">{{ addError }}</p>
      </div>
    </div>

    <p v-if="error" class="text-sm text-red-500">{{ error }}</p>
  </div>
  </div>
</template>

<script setup lang="ts">
definePageMeta({ layout: 'dashboard', middleware: ['teacher'] })

const { apiFetch } = useApi()
const { t } = useI18n()
const route = useRoute()
const id = Number(route.params.id)

interface Student { id: string; first_name: string | null; last_name: string | null; email: string | null; role: string }
interface ClassDetail { id: number; name: string; students: Student[] }

const cls = ref<ClassDetail | null>(null)
const allStudents = ref<Student[]>([])
const loading = ref(true)
const error = ref('')
const adding = ref(false)
const addError = ref('')
const selectedStudentId = ref('')

const memberIds = computed(() => new Set(cls.value?.students.map(s => String(s.id)) ?? []))
const availableStudents = computed(() => allStudents.value.filter(s => !memberIds.value.has(String(s.id))))

async function load() {
  loading.value = true
  error.value = ''
  try {
    const [classData, students] = await Promise.all([
      apiFetch<ClassDetail>(`/api/classes/${id}`),
      apiFetch<Student[]>('/api/admin/users/?role=student'),
    ])
    cls.value = classData
    allStudents.value = students
  } catch (e: any) {
    error.value = e?.data?.detail || String(e)
    cls.value = null
  } finally {
    loading.value = false
  }
}

async function addStudent() {
  if (!selectedStudentId.value) return
  adding.value = true
  addError.value = ''
  try {
    await apiFetch(`/api/classes/${id}/students`, {
      method: 'POST',
      body: { student_id: selectedStudentId.value },
    })
    selectedStudentId.value = ''
    await load()
  } catch (e: any) {
    addError.value = e?.data?.detail || String(e)
  } finally {
    adding.value = false
  }
}

async function removeStudent(studentId: string) {
  try {
    await apiFetch(`/api/classes/${id}/students/${studentId}`, { method: 'DELETE' })
    if (cls.value) cls.value.students = cls.value.students.filter(s => String(s.id) !== String(studentId))
  } catch (e: any) {
    error.value = e?.data?.detail || String(e)
  }
}

async function deleteClass() {
  if (!cls.value) return
  if (!confirm(t('classes.delete_confirm', { name: cls.value.name }))) return
  try {
    await apiFetch(`/api/classes/${id}`, { method: 'DELETE' })
    await navigateTo('/classes')
  } catch (e: any) {
    error.value = e?.data?.detail || String(e)
  }
}

onMounted(load)
</script>
