<template>
  <article class="space-y-6">
    <header>
      <h1 class="text-2xl font-bold">{{ $t('legal.licences.title') }}</h1>
      <p class="mt-2 text-sm" style="color:var(--color-text-muted)">
        {{ $t('legal.licences.lead') }}
      </p>
    </header>

    <section
      class="rounded-xl border p-6 space-y-3"
      style="background:var(--color-surface);border-color:var(--color-border)">
      <h2 class="text-base font-semibold">{{ $t('legal.licences.pax_title') }}</h2>
      <p class="text-sm">{{ $t('legal.licences.pax_body') }}</p>
      <p class="text-sm">
        <a
          href="https://www.gnu.org/licenses/agpl-3.0.html" target="_blank" rel="noopener"
          class="underline" style="color:var(--color-primary)">
          {{ $t('legal.licences.pax_link') }}
        </a>
      </p>
    </section>

    <section
      class="rounded-xl border p-6 space-y-3"
      style="background:var(--color-surface);border-color:var(--color-border)">
      <h2 class="text-base font-semibold">{{ $t('legal.licences.wims_title') }}</h2>
      <p class="text-sm">{{ $t('legal.licences.wims_body') }}</p>
    </section>

    <section
      class="rounded-xl border p-6 space-y-4"
      style="background:var(--color-surface);border-color:var(--color-border)">
      <h2 class="text-base font-semibold">{{ $t('legal.licences.deps_title') }}</h2>
      <p class="text-sm">{{ $t('legal.licences.deps_body') }}</p>
      <div class="overflow-x-auto">
        <table class="w-full text-sm">
          <thead>
            <tr
              class="text-left text-xs uppercase tracking-wide"
              style="color:var(--color-text-muted)">
              <th class="py-2 pr-4">{{ $t('legal.licences.col_name') }}</th>
              <th class="py-2 pr-4">{{ $t('legal.licences.col_role') }}</th>
              <th class="py-2">{{ $t('legal.licences.col_licence') }}</th>
            </tr>
          </thead>
          <tbody>
            <tr
              v-for="d in deps" :key="d.name" class="border-t"
              style="border-color:var(--color-border)">
              <td class="py-2 pr-4 font-medium">{{ d.name }}</td>
              <td class="py-2 pr-4" style="color:var(--color-text-muted)">
                {{ $t('legal.licences.role_' + d.role) }}
              </td>
              <td class="py-2">{{ d.licence }}</td>
            </tr>
          </tbody>
        </table>
      </div>
      <p class="text-xs" style="color:var(--color-text-muted)">
        {{ $t('legal.licences.deps_note') }}
      </p>
    </section>
  </article>
</template>

<script setup lang="ts">
// Les bibliothèques que PAX embarque ou charge, avec leur licence. La liste
// couvre ce qui est visible par la personne qui utilise le site : le socle des
// deux stacks et les bibliothèques chargées dans son navigateur. Les licences
// sont celles publiées par chaque projet ; à revérifier lors d'une montée de
// version majeure (cf. la procédure du skill `dependances`).
const deps = [
  { name: 'FastAPI', role: 'backend', licence: 'MIT' },
  { name: 'SQLAlchemy', role: 'backend', licence: 'MIT' },
  { name: 'Alembic', role: 'backend', licence: 'MIT' },
  { name: 'SymPy', role: 'cas', licence: 'BSD-3-Clause' },
  { name: 'Maxima', role: 'cas', licence: 'GPL-2.0' },
  { name: 'PostgreSQL', role: 'db', licence: 'PostgreSQL' },
  { name: 'Redis', role: 'cache', licence: 'RSALv2 / SSPLv1' },
  { name: 'Nuxt', role: 'front', licence: 'MIT' },
  { name: 'Vue', role: 'front', licence: 'MIT' },
  { name: 'Tailwind CSS', role: 'front', licence: 'MIT' },
  { name: 'KaTeX', role: 'math', licence: 'MIT' },
  { name: 'CodeMirror', role: 'code', licence: 'MIT' },
  { name: 'Skulpt', role: 'code', licence: 'MIT' },
  { name: 'JSXGraph', role: 'figure', licence: 'MIT / LGPL-3.0' },
  { name: 'GeoGebra', role: 'figure', licence: 'proprietaire' },
  { name: 'JSmol', role: 'figure', licence: 'LGPL-2.1' },
]
</script>
