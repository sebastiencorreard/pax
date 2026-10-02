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

export function useFeuilles() {
  const { locale } = useI18n()

  /** Un nombre à la française (ou à la néerlandaise) : `2,87`. */
  function nombre(x: number, chiffres = 2): string {
    return x.toLocaleString(String(locale.value), { maximumFractionDigits: chiffres })
  }

  function date(iso: string | null): string {
    if (!iso) return ''
    return new Date(iso).toLocaleDateString(String(locale.value), {
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
