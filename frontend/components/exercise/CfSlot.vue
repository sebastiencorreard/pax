<template>
  <span
    class="cf-slot"
    :class="{
      'cf-slot--over': isOver,
      'cf-slot--filled': !!value,
      'cf-slot--pending': isPending,
    }"
    @dragover.prevent="isOver = true"
    @dragenter.prevent="isOver = true"
    @dragleave="isOver = false"
    @drop.prevent="onDrop"
    @click="onClick"
  >
    <span v-if="valueHtml" v-html="valueHtml" class="cf-slot-content"></span>
    <span v-else class="cf-slot-placeholder">···</span>
  </span>
</template>

<script setup lang="ts">
const props = defineProps<{
  name: string
  value: string
  choicesHtml: Array<{ raw: string; html: string }>
  dragging: string | null   // valeur raw de la carte en cours de glisser
  pending: string | null    // valeur raw de la carte sélectionnée par clic
  submitted: boolean
}>()

const emit = defineEmits<{
  place: [name: string, value: string]
  clear: [name: string]
}>()

const { renderMath } = useKatex()
const isOver = ref(false)

const valueHtml = computedAsync(async () => {
  if (!props.value) return ''
  const choice = props.choicesHtml.find(c => c.raw === props.value)
  return choice ? choice.html : await renderMath(props.value)
}, '')

// La carte en attente (clic) correspond-elle à ce slot ?
const isPending = computed(() => !props.submitted && !!props.pending)

function onDrop(e: DragEvent) {
  isOver.value = false
  if (props.submitted) return
  const raw = e.dataTransfer?.getData('text/plain')
  if (raw) emit('place', props.name, raw)
}

function onClick() {
  if (props.submitted) return
  if (props.pending) {
    // Une carte est en attente → on la place ici
    emit('place', props.name, props.pending)
  } else if (props.value) {
    // Clic sur slot rempli → vider
    emit('clear', props.name)
  }
}
</script>

<style>
.cf-slot {
  display: inline-flex;
  align-items: center;
  justify-content: center;
  min-width: 3rem;
  min-height: 1.8rem;
  vertical-align: middle;
  margin: 0 0.25rem;
  padding: 0.1rem 0.6rem;
  border: 2px dashed var(--color-border);
  border-radius: 0.375rem;
  cursor: pointer;
  transition: border-color 0.15s, background 0.15s;
  user-select: none;
}
.cf-slot--over {
  border-color: var(--color-primary);
  background: color-mix(in srgb, var(--color-primary) 12%, transparent);
}
.cf-slot--filled {
  border-style: solid;
  border-color: var(--color-primary);
}
.cf-slot--pending {
  border-style: dashed;
  border-color: var(--color-primary);
}
.cf-slot-placeholder {
  color: var(--color-text-muted);
  font-size: 0.85em;
  letter-spacing: 0.05em;
}
.cf-slot-content {
  pointer-events: none;
}
</style>
