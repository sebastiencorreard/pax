<template>
  <!-- Le tableau d'`oef/helpseverity` : neuf niveaux en colonnes, les dix
       réglages qu'ils commandent en lignes. Servi par `/api/sheets/severite`,
       pour que la table n'existe qu'à un endroit, côté moteur. -->
  <div class="overflow-x-auto">
    <table class="text-xs w-full border-collapse">
      <thead>
        <tr>
          <th class="text-left px-2 py-1 font-medium">{{ $t('sheets.severity') }}</th>
          <th
            v-for="n in 9" :key="n" class="px-2 py-1 text-center font-semibold"
            :style="colonne(n)">
            {{ n }}
          </th>
        </tr>
      </thead>
      <tbody>
        <tr
          v-for="(paliers, cle) in table.reglages" :key="cle"
          class="border-t" style="border-color:var(--color-border)">
          <th class="text-left px-2 py-1 font-normal" style="color:var(--color-text-muted)">
            {{ $t(`sheets.severity_rows.${cle}`) }}
          </th>
          <td
            v-for="(valeur, i) in paliers" :key="i" class="px-2 py-1 text-center"
            :style="colonne(i + 1)">
            {{ afficher(String(cle), valeur) }}
          </td>
        </tr>
      </tbody>
    </table>
  </div>
</template>

<script setup lang="ts">
const props = defineProps<{
  table: { defaut: number; reglages: Record<string, number[]> }
  // Colonne mise en évidence ; à défaut, celle du niveau par défaut.
  highlight?: number | null
}>()

const { t, locale } = useI18n()

// Les réglages qui valent oui ou non — `helpseverity` y remplace 0 et 1 par
// les mots, et un nombre ne dirait rien ici.
const BOOLEENS = new Set(['qcmgood', 'penalty', 'givegood', 'givesol', 'givefeed', 'givehint'])

function afficher(cle: string, valeur: number): string {
  if (BOOLEENS.has(cle)) return valeur ? t('sheets.yes') : t('sheets.no')
  return valeur.toLocaleString(locale.value)
}

function colonne(n: number): string {
  return n === (props.highlight ?? props.table.defaut)
    ? 'background:var(--color-bg);font-weight:600'
    : ''
}
</script>
