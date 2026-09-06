<template>
  <div>
    <!-- Ouverte en direct (lien partagé, petit écran), cette page n'offrait
         aucun chemin de retour : la barre du layout `default` ne mène qu'à
         l'accueil et au compte. La clé `exercise.back` existait pourtant dans
         les trois locales, orpheline depuis que le lien avait disparu. -->
    <NuxtLink to="/exercise"
              class="inline-block mb-4 text-sm hover:underline"
              style="color:var(--color-primary)">
      ← {{ $t('exercise.back') }}
    </NuxtLink>
    <ExerciseDetail :exercise-id="exerciseId" />
  </div>
</template>

<script setup lang="ts">
const route = useRoute()
const exerciseId = computed(() => route.params.id as string)
</script>
