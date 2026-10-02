/** Les feuilles vues par l'élève (`/api/feuilles`, cf. docs/feuilles-eleve.md). */

export interface FeuilleResume {
  sheet_id: number
  title: string
  description: string | null
  class_id: number
  class_name: string
  status: number
  open_at: string | null
  close_at: string | null
  /** Faux pour une feuille périmée ou fermée : on s'y entraîne, sans note. */
  note_enregistrable: boolean
  note: number
  cumul: number
  qualite: number
  exercices: number
}

export interface ExerciceDeFeuille {
  id: number
  numero: number
  exercise_id: string
  title: string | null
  requis: number
  poids: number
  prerequis: string | null
  verrouille: boolean
  points: number
  qualite: number
  meilleur: number
  niveau: number
  essais: number
  tirages: number
}

export interface FeuilleDetail extends Omit<FeuilleResume, 'exercices'> {
  note_formule: number
  note_indicateur: number
  meilleur: number
  niveau: number
  exercices: ExerciceDeFeuille[]
}

/** Le message d'une erreur de `$fetch` : le `detail` de FastAPI d'abord. */
export function messageErreur(e: unknown): string {
  const err = e as { data?: { detail?: string } }
  return err?.data?.detail || String(e)
}

/**
 * Le serveur garde les dates en UTC **sans fuseau** (`2026-10-12T18:00:00`) ;
 * `new Date` lirait cette chaîne comme une heure locale.
 */
export function instantUtc(iso: string): Date {
  return new Date(/[Zz]|[+-]\d\d:?\d\d$/.test(iso) ? iso : `${iso}Z`)
}

/** Pour un `<input type="datetime-local">` : la date du serveur, à l'heure locale. */
export function versChampLocal(iso: string | null): string {
  if (!iso) return ''
  const d = instantUtc(iso)
  const z = (n: number) => String(n).padStart(2, '0')
  return `${d.getFullYear()}-${z(d.getMonth() + 1)}-${z(d.getDate())}T${z(d.getHours())}:${z(d.getMinutes())}`
}

/** L'inverse : la saisie locale, rendue au serveur en UTC. */
export function depuisChampLocal(local: string): string | null {
  return local ? new Date(local).toISOString() : null
}

export function useFeuilles() {
  const { locale } = useI18n()

  /** Un nombre à la française (ou à la néerlandaise) : `2,87`. */
  function nombre(x: number, chiffres = 2): string {
    return x.toLocaleString(String(locale.value), { maximumFractionDigits: chiffres })
  }

  function date(iso: string | null): string {
    if (!iso) return ''
    return instantUtc(iso).toLocaleDateString(String(locale.value), {
      day: 'numeric', month: 'long', year: 'numeric',
    })
  }

  /** `"1+3:60"` → `{ numeros: "1, 3", seuil: 60 }`, comme `_prerequis`. */
  function prerequis(texte: string | null): { numeros: string; seuil: number } | null {
    if (!texte || !texte.includes(':')) return null
    const [nums = '', seuil] = texte.split(':')
    return { numeros: nums.split('+').filter(Boolean).join(', '), seuil: Number(seuil) }
  }

  return { nombre, date, prerequis }
}
