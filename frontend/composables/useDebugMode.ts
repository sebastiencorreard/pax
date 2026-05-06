const _debug = ref(false)

export function useDebugMode() {
  return { debugMode: _debug }
}
