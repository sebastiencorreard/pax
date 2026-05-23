# Exercices de type « course »

Les exercices de type **`course`** (« race » en anglais WIMS) sont des séries séquentielles de questions indépendantes. L'élève répond à une question à la fois ; une bonne réponse fait passer à la suivante, une mauvaise réponse arrête la course.

C'est l'un des trois types d'exercices PAX (avec `standard` et `dynsteps`). Voir [`types-exercices-reponses.md`](types-exercices-reponses.md) pour le panorama des trois.

## Détection backend

Dans `DefEngine.render()` (`backend/core/oef/def_engine/__init__.py`) :

```python
oefsteps_val = self.ctx.get("oefsteps", "").strip()
is_dynsteps_var = self.ctx.get("dynsteps", "").strip().lower() == "yes"

if is_dynsteps_var:
    exercise_type = "dynsteps"
elif oefsteps_val:
    exercise_type = "course"
else:
    exercise_type = "standard"
```

`oefsteps` est typiquement assemblé dans le `.def` ainsi :

```
tmp0=!makelist reply x for x in $val265
tmp=!trim $(tmp0)
val266=!translate internal $\t\n$ to ;; in $tmp
oefsteps=$val266
```

→ `oefsteps = "reply1;reply2;…;reply9"` (chaîne `;`-séparée des noms de réponses).

Le nombre d'étapes est dérivé du nombre d'items dans `oefsteps` (ou des variables habituelles `val62`, `val71`, `cnt`, …).

## Filtrage des réponses actives par étape

Le `.def` contient les 9 réponses (`reply1..reply9`) mais à chaque étape (`m_step`), seule UNE réponse est active. Le pattern WIMS :

```
!for m_ii=1 to $val264
  !if $m_step=$m_ii
    [HTML de la question + !read oef/embed.phtml replyN]
  !endif
!next
```

Pour que le backend retourne uniquement la réponse active dans `rendered.answers`, `DefEngine` track les `replyN` rencontrés pendant le rendu :

```python
class DefEngine:
    def __init__(...):
        self._touched_replies: set[str] = set()

    def _render_embed(self, args):
        nm = re.match(r"^r(?:eply)?(\d+)$", ref)
        if nm:
            self._touched_replies.add(f"reply{nm.group(1)}")  # avant tout return
        ...

    def render(self, df):
        ...
        if is_dynsteps_flag and self._touched_replies:
            answers = [a for a in answers if a.input_name in self._touched_replies]
```

Conséquence : `rendered.answers` à l'étape 4 ne contient que `[reply4]`, qu'il s'agisse d'un type `numeric`, `radio`, `mark`, etc. — pas besoin de marqueur HTML invisible pour signaler l'activité d'une réponse.

> **Historique** : une première approche utilisait un span HTML invisible (`<span class="oef-radio-anchor">`) pour signaler la réponse active de type radio (qui n'émet pas de widget visible). Cette approche a été abandonnée car elle disséminait la logique de filtrage en 4 endroits du frontend. Le filtrage côté serveur est plus localisé.

## Frontend : `DynstepsExercise.vue`

Le routing dans `ExercisePlayer.vue` envoie `course` ET `dynsteps` vers le même composant :

```vue
<DynstepsExercise v-if="rendered.exercise_type === 'dynsteps' || rendered.exercise_type === 'course'" />
<StandardExercise v-else />
```

Différences `course` vs `dynsteps` dans `DynstepsExercise.vue` :

| | `course` | `dynsteps` |
|---|---|---|
| Détection | `isCourse = exercise_type === 'course'` | défaut |
| Erreur sur une étape | **arrête la course** : `courseStopped = true` | l'étape peut être retentée |
| Calcul du score final | `correct / total_steps` (toutes les étapes attendues) | `correct / stepsHistory.length` (uniquement les étapes faites) |
| Affichage du bilan | quand `currentStep >= total_steps` OU `courseStopped` | quand toutes les étapes sont passées |

## Lifecycle d'une étape

1. Initial : `GET /api/render/{id}` sans `m_step` → backend renvoie `current_step=1` (initialisé par défaut dans `DefEngine.__init__`)
2. Élève répond → `POST /api/check/{id}` avec `m_step=1, replies=[{input_name: "reply1", value: ...}]`
3. Backend re-rend l'exercice avec le même seed + step pour obtenir l'`expected`, dispatche vers `check_answer`
4. Si correct ET pas la dernière étape : frontend émet `load-step` avec `m_step + 1` → nouvelle requête `GET /api/render/{id}?m_step=2`
5. Si incorrect : `courseStopped = true`, affichage du bilan
6. Étape finale : affichage du bilan global (score sur `total_steps`)

## Patterns connus dans le corpus

### Construction de `oefsteps` via `!makelist for x in list`

```
tmp0=!makelist reply x for x in $val265   ← itère sur une liste, pas une plage
```

Cette forme de `!makelist` (« for var in list ») est nécessaire pour les courses où l'auteur veut un sous-ensemble ordonné de réponses. Voir [`def-engine-commands.md`](def-engine-commands.md) pour la commande `makelist`.

### Concaténation des questions

Toutes les questions ont leur propre bloc dans le `.def` qui assigne `val14` (texte de la question), puis sauvegarde dans `valN` (e.g. `val19=$val14`). À la fin :

```
val14=$val19,$val37,$val52,$val87,$val196,$val206,$val220,$val236,$val249
```

`val14` devient une liste **comma-separated** de 9 questions. L'engine PAX détecte ce pattern `$a,$b,$c,...` dans `_eval_value` et neutralise les tabs internes (qui pollueraient un split par tab) pour garder la liste proprement comma-separated.

## Exemple : `ressources~H3~algebra~oefqcm3.fr~src~csga`

Exercice « Course d'automates DNB SG A » : 9 questions du sujet zéro du DNB.

- `val265 = "1,2,3,4,5,6,7,8,9"` (les indices des questions à inclure)
- `val266 = "reply1;reply2;...;reply9"` (assemblé par `!makelist reply x for x in $val265`)
- `oefsteps = $val266` → détecté comme `course`
- À chaque étape, la question correspondante est rendue avec son champ de réponse (texte, QCM radio, ou autre)
