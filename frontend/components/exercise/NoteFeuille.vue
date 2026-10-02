<template>
  <!-- Dans une feuille, l'élève doit savoir si sa réponse a compté : un
       énoncé déjà noté, ou une feuille périmée, est corrigé sans être noté
       (`note_enregistree`, `api/routes/check.py`). -->
  <p
v-if="visible" class="mt-3 text-xs"
     :style="checkResult!.note_enregistree ? 'color:var(--color-text-muted)' : 'color:#92400e'">
    {{ checkResult!.note_enregistree ? $t('feuilles.note_comptee') : $t('feuilles.note_non_comptee') }}
  </p>
</template>

<script setup lang="ts">
import type { CheckResult, Rendered } from '~/composables/useExerciseLogic'

const props = defineProps<{ rendered: Rendered; checkResult: CheckResult | null }>()
const auth = useAuthStore()

const visible = computed(() =>
  !!props.checkResult && !props.checkResult.has_invalid_format
  && props.rendered.reglages?.sheet_item !== undefined
  && auth.user?.role === 'student')
</script>
