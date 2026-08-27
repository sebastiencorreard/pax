# Paramètres et variables de session

Les exercices `.def` WIMS s'attendent à trouver dans leur contexte un ensemble de variables « système » fournies par l'environnement (utilisateur courant, configuration, séquençage). PAX initialise ces variables dans `DefEngine.__init__` (`backend/core/oef/def_engine/__init__.py`).

## Variables initialisées par défaut

```python
self.ctx: dict[str, str] = {
    "empty": "",
    "m_step": "1",
    "step": "1",
    "m_times": "×",
    "m_div": "÷",
    "m_le": "≤",
    "m_ge": "≥",
    "m_neq": "≠",
    "imagedir": "pax-img:_",
}
```

| Variable | Rôle | Valeur PAX |
|---|---|---|
| `empty` | Sentinelle pour `$empty` (WIMS) | `""` (chaîne vide) |
| `m_step` / `step` | Étape courante d'un exercice dynsteps/course | `"1"` par défaut, écrasé par `load_and_render(m_step=N)` |
| `m_times` | Symbole multiplication | `"×"` |
| `m_div` | Symbole division | `"÷"` |
| `m_le` | Symbole « inférieur ou égal » | `"≤"` |
| `m_ge` | Symbole « supérieur ou égal » | `"≥"` |
| `m_neq` | Symbole « différent » | `"≠"` |
| `imagedir` | URL du dossier d'images du module | `"pax-img:_"` (sentinelle, résolue post-render) |

Voir [`static-assets.md`](static-assets.md) pour la résolution de `imagedir`.

## Paramètres de configuration (`confparm1..4`)

Les exercices WIMS reçoivent jusqu'à 4 paramètres de configuration via `$confparm1`, `$confparm2`, etc. Ces paramètres permettent à l'enseignant de personnaliser un même exercice (sélectionner un sous-ensemble de questions, changer la difficulté, etc.).

Le pattern canonique en début de `.def` :

```
val1=$imagedir
val2=$confparm1
val3=$confparm2
val4=$confparm3
val5=$confparm4
```

> **Note historique** : le parseur PAX skippait à l'origine les assignations `val1`-`val5` (commentaire « WIMS session variables »). Le skip a été levé en mai 2026 : ces assignations s'évaluent maintenant normalement, ce qui permet à `$val1` de fournir l'imagedir et à `$val2..$val5` de propager les confparms.

### État actuel

`confparm1..4` ne sont **pas** initialisés dans le ctx. Une référence comme `$confparm1` se substitue donc en chaîne vide. Pour la plupart des exercices, c'est OK (le `!ifval $val2=` détecte l'absence et applique des valeurs par défaut) :

```
!ifval $val2= 
tmp0=!makelist x for x=1 to 9
val265= $(tmp0)
!else
val265= $val2
!endif
```

#### Les exercices qui n'ont pas ce garde-fou

Quatre exercices bouclent directement sur le paramètre, sans vérifier qu'il est
là — `!for val11 =1 to $val2` où `val2=$confparm1`. La borne étant vide, la
boucle ne tourne pas, et l'exercice se rend **sans aucune question** :

| exercice | ce qu'il attend |
|---|---|
| `H3~algebra~oefpuis.nl~src~decalage` | `\confparm1` = nombre de questions |
| `H3~algebra~oefpuis.nl~src~decalage2` | idem |
| `H3~algebra~oefpuis.nl~src~decimal` | idem |
| `H3~algebra~oefpuis.nl~src~puisdiv` | idem |

Ce n'est pas un défaut du moteur : WIMS ne fournit pas davantage de valeur par
défaut, et l'exercice n'est utilisable qu'une fois posé sur une feuille par un
enseignant qui l'a réglé. Relevé le 2026-08-28, en cherchant pourquoi certains
exercices n'exposent aucune réponse attendue — ils sont les seuls du corpus
dans ce cas, les autres portant bien leur `!ifval $valN=`.

Ils resteront donc invisibles aux tests de notation tant que les confparms ne
seront pas exposés (voir ci-dessous) : `_get_testable_exercises` les écarte,
faute de réponse.

### Pour exposer des paramètres dans l'API

Si on voulait permettre à l'enseignant d'appeler `GET /api/render/{id}?confparm1=1,2,3` pour personnaliser un exercice, il faudrait :

1. Ajouter `confparm1..4` aux paramètres de la route (`backend/api/routes/render.py`)
2. Les passer à `load_and_render`
3. Dans `DefEngine.__init__`, les seeder dans `self.ctx` AVANT `render()`

Ce n'est pas fait à ce jour.

## Variables de séquençage (course / dynsteps)

| Variable | Rôle | Source |
|---|---|---|
| `m_step` | Étape courante (1-indexed) | Param `m_step` de la route (défaut: `"1"`) |
| `step` | Alias de `m_step` (compat WIMS qui utilise les deux) | Idem |
| `oefsteps` | Liste `;`-séparée des étapes (pour type `course`) | Calculé par le `.def` |
| `dynsteps` | `"yes"` pour activer le type `dynsteps` | Assigné par le `.def` |
| `current_step` (sortie) | Étape rendue, exposée dans `ExerciseRender` | Lu depuis `m_step` |
| `total_steps` (sortie) | Nombre total d'étapes | Compté depuis `oefsteps` ou variables connues (`val62`, `val71`, `cnt`, …) |

Voir [`exercises-course.md`](exercises-course.md) pour les exercices de type course.

## Variables d'état (`status`, `testcondition`, `wims_read_parm`)

Ces variables guident le flux de contrôle en début de `.def` (héritage WIMS) :

```
!if $wims_read_parm!=$empty
 !goto $wims_read_parm
!endif
!if $testcondition=yes
 !goto test
!endif
!if $status=waiting
 !exit
!endif
```

Le parseur PAX **strippe ces IfBlocks** au début de `var_instructions` (voir `_parse_main` dans `def_parser.py`) : aucun goto n'est suivi, l'exercice est toujours rendu en mode « normal ».

Si un exercice avait besoin de tester `$status` ou `$wims_read_parm` dans son corps de variables, il faudrait revoir cette logique.

## Variables de réponse (`replytypeN`, `replygoodN`, …)

Pré-seedées dans `ctx` au début de `render()` pour que `_render_embed` puisse y accéder pendant le rendu de la section `:question` :

```python
for rm in df.reply_meta:
    n = rm.get("n")
    for key in ("type", "name", "good", "option", "weight"):
        if rm.get(key):
            self.ctx[f"reply{key}{n}"] = rm[key]
```

Exemple : `ctx["replytype1"] = "numeric"`, `ctx["replygood1"] = "$val12"`, etc.

> Au moment du rendu de l'énoncé, `$replygood1` est encore brut (les `$valN` à l'intérieur ne sont substitués qu'au moment où l'on lit la variable). Le checker `mark` réévalue `replygood1` au moment de l'extraction des réponses (`_extract_answers`).

## Variables exposées par `_render_embed` (suivi des étapes)

`DefEngine` track les `replyN` rencontrés pendant le rendu pour filtrer `rendered.answers` aux étapes actives (dynsteps/course) :

```python
class DefEngine:
    def __init__(...):
        self._touched_replies: set[str] = set()

    def _render_embed(self, args):
        nm = re.match(r"^r(?:eply)?(\d+)$", ref)
        if nm:
            self._touched_replies.add(f"reply{nm.group(1)}")
```

Cf. [`exercises-course.md`](exercises-course.md) pour la motivation.

## Constantes injectées par d'autres procs

| Variable | Source | Rôle |
|---|---|---|
| `ins_url` | `oef/draw.phtml` (proc) | URL bare d'un graphique flydraw (à wrapper dans `<img>` côté caller) |
| `canvasdraw_out` | `oef/canvasdraw.phtml` (proc) | `<img>` complet d'un graphique flydraw (utilisé tel quel) |
| `slib_out` | `slib/*` (procs) | Sortie générique d'un script slib |
| `nextstep` | course | Liste des prochaines étapes (souvent une copie de `oefsteps`) |
