<template>
  <div>
    <ExerciseDetail :exercise-id="exerciseId" />
  </div>
</template>

<script setup lang="ts">
const route = useRoute()
const exerciseId = computed(() => route.params.id as string)
</script>
