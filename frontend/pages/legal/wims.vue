<template>
  <article class="space-y-6">
    <header>
      <h1 class="text-2xl font-bold">{{ $t('legal.wims.title') }}</h1>
      <p class="mt-2 text-sm" style="color:var(--color-text-muted)">
        {{ $t('legal.wims.lead') }}
      </p>
    </header>

    <section
      v-for="bloc in blocs" :key="bloc"
      class="rounded-xl border p-6 space-y-3"
      style="background:var(--color-surface);border-color:var(--color-border)">
      <h2 class="text-base font-semibold">{{ $t('legal.wims.' + bloc + '_title') }}</h2>
      <p class="text-sm whitespace-pre-line">{{ $t('legal.wims.' + bloc + '_body') }}</p>
    </section>

    <section
      class="rounded-xl border p-6 space-y-3"
      style="background:var(--color-surface);border-color:var(--color-primary)">
      <h2 class="text-base font-semibold">{{ $t('legal.wims.merci_title') }}</h2>
      <p class="text-sm whitespace-pre-line">{{ $t('legal.wims.merci_body') }}</p>
      <p class="text-sm">
        <a
          href="https://wims.univ-cotedazur.fr/" target="_blank" rel="noopener"
          class="underline" style="color:var(--color-primary)">
          {{ $t('legal.wims.lien') }}
        </a>
      </p>
    </section>
  </article>
</template>

<script setup lang="ts">
// Ce que PAX doit à WIMS, bloc par bloc. Les chiffres (exercices, modules,
// auteurs) ont été relevés sur le corpus le 2026-10-01 ; les noms sont ceux
// que portent les sources de WIMS elles-mêmes. Le texte vit dans les fichiers
// de traduction : le site est trilingue.
const blocs = ['heritage', 'exercices', 'format', 'source', 'documentation']
</script>
