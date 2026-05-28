import type { Chrono } from '~/composables/useExerciseLogic'

/**
 * Cross-component chronometer state.
 *
 * The chrono itself is owned by the rendered exercise (returned by
 * `/api/render`), but the **display** belongs in the global topbar so it
 * stays visible regardless of scroll. ExercisePlayer publishes the active
 * chrono into this shared state on render; the dashboard layout subscribes
 * and renders <ExerciseTimer> when it's non-null.
 *
 * `useState` (Nuxt) gives us a per-request reactive ref that's safe across
 * SSR-disabled SPA navigation — we don't have to manage Pinia plumbing for
 * something this narrow.
 */
export function useChronoState() {
  const chrono = useState<Chrono | null>('pax:chrono', () => null)
  const frozen = useState<boolean>('pax:chrono-frozen', () => false)

  function set(c: Chrono | null) {
    chrono.value = c
    frozen.value = false  // re-arm on every new exercise / step
  }

  function freeze() {
    frozen.value = true
  }

  function clear() {
    chrono.value = null
    frozen.value = false
  }

  return { chrono, frozen, set, freeze, clear }
}
