<template>
  <div>
    <div class="mb-4">
      <NuxtLink to="/exercise"
                class="text-sm hover:underline"
                style="color:var(--color-text-muted)">
        ← Retour aux exercices
      </NuxtLink>
    </div>

    <ExercisePlayer :exercise-id="exerciseId" />
  </div>
</template>

<script setup lang="ts">
const route = useRoute()
const exerciseId = computed(() => route.params.id as string)
</script>
