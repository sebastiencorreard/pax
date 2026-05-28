<template>
  <!-- The countdown stays mounted at zero so the layout doesn't reflow when
       the visible portion ends; we just dim it. Past T2 we hide it entirely
       (server has already locked the score to 0). -->
  <div v-if="!hidden" class="pax-timer" :class="{ 'is-overshot': overshot }">
    <span class="pax-timer-label">{{ overshot ? '+' : '' }}{{ formatted }}</span>
  </div>
</template>

<script setup lang="ts">
import { computed, onMounted, onBeforeUnmount, ref } from 'vue'
import type { Chrono } from '~/composables/useExerciseLogic'

const props = defineProps<{
  chrono: Chrono
  // When the exercise is submitted, freeze the countdown so the student can
  // read the value the server scored against. Server-side the chrono session
  // is read once at submit-time and not consulted again.
  frozen?: boolean
}>()

// Local "now" tick. We don't trust the client clock for scoring — that's the
// server's job — but we DO use it to animate the countdown smoothly. Clock
// skew is corrected with the server_now/started_at offset received at render.
const now = ref(Date.now())
let tickHandle: number | null = null

onMounted(() => {
  tickHandle = window.setInterval(() => {
    if (!props.frozen) now.value = Date.now()
  }, 1000)
})

onBeforeUnmount(() => {
  if (tickHandle !== null) window.clearInterval(tickHandle)
})

// elapsed = (clientNow - clientNowAtRender) + (serverNowAtRender - startedAt)
// The first term is what local time has measured since the API call, the
// second is the offset between server's view of "now" and the canonical
// start. Together they survive clock-skew without trusting the client.
const elapsedSeconds = computed(() => {
  const startedAtMs = Date.parse(props.chrono.started_at)
  const serverNowMs = Date.parse(props.chrono.server_now)
  const serverOffset = (serverNowMs - startedAtMs) / 1000
  const localElapsed = (now.value - mountedAt) / 1000
  return serverOffset + localElapsed
})

const mountedAt = Date.now()

// Countdown from T1 to 0. Past T1 (the "blind zone" between T1 and T2),
// hide the timer — WIMS does the same. Past T2 we keep it hidden since the
// score is already locked to 0; no value to flag.
const remaining = computed(() => Math.max(0, props.chrono.soft - elapsedSeconds.value))
const hidden = computed(() => elapsedSeconds.value > props.chrono.soft)
const overshot = computed(() => false)  // T1 → 0 only, no overshoot display

function pad(n: number) { return n.toString().padStart(2, '0') }
const formatted = computed(() => {
  const s = Math.ceil(remaining.value)
  return `${pad(Math.floor(s / 60))}:${pad(s % 60)}`
})
</script>

<style scoped>
/* Lives in the topbar — sized to match the neighbouring coins chip and
   logout button. Variables drive the theme so dark/light mode follows the
   global palette without rule duplication. */
.pax-timer {
  display: inline-flex;
  align-items: center;
  gap: 0.4rem;
  padding: 0.35rem 0.7rem;
  border-radius: 0.5rem;
  border: 1px solid var(--color-border);
  background: color-mix(in srgb, var(--color-text-muted) 8%, transparent);
  color: var(--color-text);
  font-variant-numeric: tabular-nums;
  font-size: 0.875rem;
  font-weight: 600;
  user-select: none;
  white-space: nowrap;
}
.pax-timer-label::before {
  /* Stopwatch glyph — neutral, no emoji deps. */
  content: '⏱ ';
  margin-right: 0.15rem;
  color: var(--color-text-muted);
}
</style>
