<template>
  <div class="p-4 sm:p-6 lg:p-8 space-y-6">

    <h1 class="text-2xl font-bold">{{ $t('account.title') }}</h1>

    <!-- Bandeau mot de passe temporaire -->
    <div v-if="auth.user?.must_change_password"
         class="rounded-lg px-4 py-3 text-sm flex items-center justify-between gap-4"
         style="background:color-mix(in srgb,var(--color-error) 15%,transparent);color:var(--color-error)">
      <span>{{ $t('account.must_change_password_banner') }}</span>
      <NuxtLink to="/auth/change-password" class="font-semibold underline shrink-0">
        {{ $t('account.change_password') }}
      </NuxtLink>
    </div>

    <!-- Informations personnelles -->
    <section class="rounded-xl border p-6"
             style="background:var(--color-surface);border-color:var(--color-border)">
      <h2 class="text-base font-semibold mb-4">{{ $t('account.section_info') }}</h2>
      <dl class="grid grid-cols-1 sm:grid-cols-2 gap-y-4 gap-x-8 text-sm">
        <div>
          <dt class="text-xs uppercase tracking-wide mb-0.5" style="color:var(--color-text-muted)">
            {{ $t('admin.field_first_name') }}
          </dt>
          <dd class="font-medium">{{ auth.user?.first_name || '—' }}</dd>
        </div>
        <div>
          <dt class="text-xs uppercase tracking-wide mb-0.5" style="color:var(--color-text-muted)">
            {{ $t('admin.field_last_name') }}
          </dt>
          <dd class="font-medium">{{ auth.user?.last_name || '—' }}</dd>
        </div>
        <div class="sm:col-span-2">
          <dt class="text-xs uppercase tracking-wide mb-0.5" style="color:var(--color-text-muted)">
            {{ $t('account.field_email') }}
          </dt>
          <dd class="font-medium">{{ auth.user?.email || '—' }}</dd>
        </div>
        <div>
          <dt class="text-xs uppercase tracking-wide mb-0.5" style="color:var(--color-text-muted)">
            {{ $t('account.field_role') }}
          </dt>
          <dd class="font-medium">{{ roleLabel }}</dd>
        </div>
        <div>
          <dt class="text-xs uppercase tracking-wide mb-0.5" style="color:var(--color-text-muted)">
            {{ $t('account.field_created_at') }}
          </dt>
          <dd class="font-medium">{{ formattedDate }}</dd>
        </div>
        <div v-if="auth.user?.etablissement" class="sm:col-span-2">
          <dt class="text-xs uppercase tracking-wide mb-0.5" style="color:var(--color-text-muted)">
            {{ $t('account.field_etablissement') }}
          </dt>
          <dd class="font-medium">
            {{ auth.user.etablissement.name }}
            <span v-if="isTeacherLike && auth.user.etablissement.uai"
                  class="ml-1" style="color:var(--color-text-muted)">
              ({{ auth.user.etablissement.uai }})
            </span>
          </dd>
        </div>
      </dl>
    </section>

    <!-- Classes (enseignant / admin) -->
    <section v-if="isTeacherLike"
             class="rounded-xl border p-6"
             style="background:var(--color-surface);border-color:var(--color-border)">
      <h2 class="text-base font-semibold mb-4">{{ $t('account.section_classes') }}</h2>
      <p v-if="teacherClasses.length === 0" class="text-sm" style="color:var(--color-text-muted)">
        {{ $t('account.no_classes') }}
      </p>
      <ul v-else class="space-y-1.5 text-sm">
        <li v-for="cls in teacherClasses" :key="cls.id">
          <NuxtLink :to="`/classes/${cls.id}`"
                    class="hover:underline font-medium"
                    style="color:var(--color-primary)">
            {{ cls.name }}
          </NuxtLink>
          <span class="ml-2 text-xs" style="color:var(--color-text-muted)">
            {{ cls.student_count }} {{ $t('classes.students') }}
          </span>
        </li>
      </ul>
    </section>

    <!-- Classes (élève) -->
    <section v-if="isStudent"
             class="rounded-xl border p-6"
             style="background:var(--color-surface);border-color:var(--color-border)">
      <h2 class="text-base font-semibold mb-4">{{ $t('account.section_classes') }}</h2>
      <p v-if="studentClasses.length === 0" class="text-sm" style="color:var(--color-text-muted)">
        {{ $t('account.no_classes') }}
      </p>
      <ul v-else class="space-y-1 text-sm font-medium">
        <li v-for="cls in studentClasses" :key="cls.id">{{ cls.name }}</li>
      </ul>
    </section>

    <!-- Professeurs (élève) -->
    <section v-if="isStudent && teachers.length > 0"
             class="rounded-xl border p-6"
             style="background:var(--color-surface);border-color:var(--color-border)">
      <h2 class="text-base font-semibold mb-4">{{ $t('account.section_teachers') }}</h2>
      <ul class="space-y-1 text-sm font-medium">
        <li v-for="teacher in teachers" :key="teacher.key">
          {{ teacher.first_name }} {{ teacher.last_name }}
        </li>
      </ul>
    </section>

    <!-- Paramètres -->
    <section class="rounded-xl border p-6"
             style="background:var(--color-surface);border-color:var(--color-border)">
      <h2 class="text-base font-semibold mb-4">{{ $t('account.section_settings') }}</h2>
      <div class="flex items-center gap-3 text-sm">
        <span class="text-xs uppercase tracking-wide" style="color:var(--color-text-muted)">
          {{ $t('account.language') }}
        </span>
        <select :value="String(locale)"
                @change="setLocale(($event.target as HTMLSelectElement).value as 'fr'|'nl'|'en')"
                class="px-3 py-1.5 rounded-lg border text-sm outline-none"
                style="background:var(--color-bg);border-color:var(--color-border);color:var(--color-text)">
          <option v-for="loc in availableLocales" :key="loc.code" :value="loc.code">
            {{ FLAGS[loc.code] ?? '🌐' }} {{ loc.name }}
          </option>
        </select>
      </div>
    </section>

    <!-- Changer le mot de passe -->
    <NuxtLink to="/auth/change-password"
              class="inline-flex items-center gap-2 px-4 py-2.5 rounded-lg font-medium border transition hover:bg-black/5 dark:hover:bg-white/5"
              style="border-color:var(--color-border);color:var(--color-text)">
      {{ $t('account.change_password') }}
    </NuxtLink>

  </div>
</template>

<script setup lang="ts">
definePageMeta({ layout: 'dashboard' })

const auth = useAuthStore()
const config = useRuntimeConfig()
const { t, locale, locales, setLocale } = useI18n()
const availableLocales = locales

const FLAGS: Record<string, string> = { fr: '🇫🇷', nl: '🇳🇱', en: '🇬🇧' }

interface TeacherClass {
  id: number
  name: string
  student_count: number
}

interface StudentClass {
  id: number
  name: string
  teacher_first_name: string | null
  teacher_last_name: string | null
}

const teacherClasses = ref<TeacherClass[]>([])
const studentClasses = ref<StudentClass[]>([])

const isTeacherLike = computed(() =>
  ['teacher', 'admin', 'super_admin'].includes(auth.user?.role ?? '')
)
const isStudent = computed(() => auth.user?.role === 'student')

const roleLabel = computed(() => {
  const map: Record<string, string> = {
    student: t('admin.role_student'),
    teacher: t('admin.role_teacher'),
    admin: t('admin.role_admin'),
    super_admin: t('admin.role_admin'),
    guest: t('admin.role_guest'),
  }
  return map[auth.user?.role ?? ''] ?? auth.user?.role ?? '—'
})

const formattedDate = computed(() => {
  if (!auth.user?.created_at) return '—'
  return new Date(auth.user.created_at).toLocaleDateString(String(locale.value), {
    year: 'numeric', month: 'long', day: 'numeric',
  })
})

const teachers = computed(() => {
  const seen = new Set<string>()
  return studentClasses.value
    .filter(cls => {
      const key = `${cls.teacher_first_name}|${cls.teacher_last_name}`
      if (seen.has(key)) return false
      seen.add(key)
      return true
    })
    .map(cls => ({
      key: `${cls.teacher_first_name}|${cls.teacher_last_name}`,
      first_name: cls.teacher_first_name,
      last_name: cls.teacher_last_name,
    }))
})

onMounted(async () => {
  if (!auth.token) return
  const headers = { Authorization: `Bearer ${auth.token}` }
  if (isTeacherLike.value) {
    teacherClasses.value = await $fetch<TeacherClass[]>(
      `${config.public.apiBase}/api/classes/`,
      { headers }
    ).catch(() => [])
  } else if (isStudent.value) {
    studentClasses.value = await $fetch<StudentClass[]>(
      `${config.public.apiBase}/api/classes/mine`,
      { headers }
    ).catch(() => [])
  }
})
</script>
