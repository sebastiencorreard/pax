<template>
  <article class="space-y-6">
    <header>
      <h1 class="text-2xl font-bold">{{ $t('legal.manifeste.title') }}</h1>
      <p class="mt-2 text-sm" style="color:var(--color-text-muted)">
        {{ $t('legal.manifeste.lead') }}
      </p>
    </header>

    <section
      v-for="bloc in blocs" :key="bloc"
      class="rounded-xl border p-6 space-y-3"
      style="background:var(--color-surface);border-color:var(--color-border)">
      <h2 class="text-base font-semibold">{{ $t('legal.manifeste.' + bloc + '_title') }}</h2>
      <p class="text-sm whitespace-pre-line">{{ $t('legal.manifeste.' + bloc + '_body') }}</p>
    </section>

    <section
      class="rounded-xl border p-6 space-y-3"
      style="background:var(--color-surface);border-color:var(--color-border)">
      <h2 class="text-base font-semibold">{{ $t('legal.manifeste.merci_title') }}</h2>
      <p class="text-sm whitespace-pre-line">{{ $t('legal.manifeste.merci_body') }}</p>
      <p class="text-sm">
        <a
          href="https://wims.univ-cotedazur.fr/" target="_blank" rel="noopener"
          class="underline" style="color:var(--color-primary)">
          {{ $t('legal.manifeste.merci_link') }}
        </a>
      </p>
    </section>
  </article>
</template>

<script setup lang="ts">
// Trois blocs de texte, dans l'ordre où ils se lisent. Le contenu vit dans les
// fichiers de traduction : le manifeste s'adresse aux enseignants comme aux
// élèves, et le site est trilingue.
const blocs = ['pourquoi', 'choix', 'ouvert']
</script>
