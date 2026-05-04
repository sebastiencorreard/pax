export interface Tag {
  id: number
  name: string
  created_at: string
}

export interface TagWithCount extends Tag {
  exercise_count: number
}

export interface LibraryExercise {
  id: string
  title: string
  domain: string | null
}

export interface LibraryGroup {
  tag: Tag
  exercises: LibraryExercise[]
}

export function useTags() {
  const { apiFetch } = useApi()

  async function fetchTags(): Promise<TagWithCount[]> {
    return apiFetch<TagWithCount[]>('/api/tags/')
  }

  async function createTag(name: string): Promise<Tag> {
    return apiFetch<Tag>('/api/tags/', { method: 'POST', body: { name } })
  }

  async function deleteTag(tagId: number): Promise<void> {
    await apiFetch(`/api/tags/${tagId}`, { method: 'DELETE' })
  }

  async function fetchExerciseTags(exerciseId: string): Promise<Tag[]> {
    return apiFetch<Tag[]>(`/api/tags/exercise/${exerciseId}`)
  }

  async function addTagToExercise(exerciseId: string, tagId: number): Promise<Tag[]> {
    return apiFetch<Tag[]>(`/api/tags/exercise/${exerciseId}`, {
      method: 'POST',
      body: { tag_id: tagId },
    })
  }

  async function createAndAddTag(exerciseId: string, name: string): Promise<Tag[]> {
    return apiFetch<Tag[]>(`/api/tags/exercise/${exerciseId}`, {
      method: 'POST',
      body: { name },
    })
  }

  async function removeTagFromExercise(exerciseId: string, tagId: number): Promise<void> {
    await apiFetch(`/api/tags/exercise/${exerciseId}/${tagId}`, { method: 'DELETE' })
  }

  async function fetchLibrary(): Promise<LibraryGroup[]> {
    return apiFetch<LibraryGroup[]>('/api/tags/library')
  }

  async function fetchTagExercises(tagId: number): Promise<LibraryGroup> {
    return apiFetch<LibraryGroup>(`/api/tags/${tagId}/exercises`)
  }

  return {
    fetchTags,
    createTag,
    deleteTag,
    fetchExerciseTags,
    addTagToExercise,
    createAndAddTag,
    removeTagFromExercise,
    fetchLibrary,
    fetchTagExercises,
  }
}
