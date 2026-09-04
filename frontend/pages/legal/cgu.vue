<template>
  <article class="space-y-6">
    <header>
      <h1 class="text-2xl font-bold">{{ $t('legal.cgu.title') }}</h1>
      <p class="mt-2 text-sm" style="color:var(--color-text-muted)">
        {{ $t('legal.cgu.lead') }}
      </p>
    </header>

    <!-- Les informations d'identification sont propres à l'installation : qui
         édite le site, qui l'héberge, à qui l'on écrit. Elles ne peuvent pas
         être devinées depuis le code, d'où ce bandeau tant qu'elles ne sont pas
         renseignées dans les traductions (`legal.cgu.editeur_*`). -->
    <div
      v-if="aCompleter.length"
      class="rounded-lg px-4 py-3 text-sm"
      style="background:color-mix(in srgb,var(--color-warning,#b45309) 15%,transparent);
      color:var(--color-warning,#b45309)">
      {{ $t('legal.cgu.a_completer') }} {{ aCompleter.join(', ') }}
    </div>

    <section
      v-for="s in sections" :key="s"
      class="rounded-xl border p-6 space-y-3"
      style="background:var(--color-surface);border-color:var(--color-border)">
      <h2 class="text-base font-semibold">{{ $t('legal.cgu.' + s + '_title') }}</h2>
      <p class="text-sm whitespace-pre-line">{{ $t('legal.cgu.' + s + '_body') }}</p>
    </section>

    <p class="text-xs" style="color:var(--color-text-muted)">
      {{ $t('legal.cgu.maj') }} {{ maj }}
    </p>
  </article>
</template>

<script setup lang="ts">
import { computed } from 'vue'
const { t } = useI18n()

// L'ordre de lecture : qui édite, ce que fait le service, ce qu'on attend de
// la personne qui l'utilise, ce qu'il advient de ses données, ce que vaut le
// contenu, et à qui appartient quoi.
const sections = [
  'editeur', 'objet', 'acces', 'compte', 'donnees',
  'contenus', 'propriete', 'responsabilite', 'modification',
]

// Un marqueur `…` dans une traduction signale une information que l'exploitant
// du site doit renseigner. On les liste plutôt que de publier un document
// troué sans le dire.
const aCompleter = computed(() => {
  const champs: Record<string, string> = {
    editeur_body: t('legal.cgu.editeur_title'),
    donnees_body: t('legal.cgu.donnees_title'),
  }
  return Object.entries(champs)
    .filter(([cle]) => t('legal.cgu.' + cle).includes('…'))
    .map(([, libelle]) => libelle)
})

const maj = '2026-09-04'
</script>
