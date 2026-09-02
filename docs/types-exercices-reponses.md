# Types d'Exercices et de Réponses dans PAX

Ce document répertorie les types d'exercices, les analyseurs de réponses et les widgets visuels supportés ou identifiés dans le corpus OEF/WIMS de PAX.

## 1. Structure des Exercices (`exercise_type`)

Le moteur PAX classifie les exercices selon leur logique de progression et de rendu :

### Types Supportés ✅
| Type | Description |
| :--- | :--- |
| **`standard`** | Exercice classique en une seule étape. Toutes les questions sont posées simultanément. |
| **`dynsteps`** | Exercice à étapes dynamiques (utilisant `\steps` ou `\nextstep`). L'énoncé évolue selon la réussite de l'élève. |
| **`course`** | Exercice séquentiel de type "parcours" (défini via `oefsteps`). Suite de questions indépendantes. |

### Types Identifiés (Non encore supportés) ❌
*   **`deductio`** : Exercice de déduction logique ou démonstration géométrique guidée (très présent en géométrie).
*   **`polymorphe`** : Exercice dont le type de réponse change dynamiquement selon le tirage (ex: bascule `numeric` / `radio`).
*   **`document` / `tool`** : Modules de contenu interactif ou outils de calcul (ex: `adm/tool/any/...`).
*   **`shooting`** : Mode d'interaction de type "tir" ou précision (nécessite `js2wims`).

## 2. Analyseurs de Réponses (`answer_type`)

PAX utilise des "checkers" pour valider les réponses. Cette liste est issue de l'analyse du code source officiel de WIMS (`scripts/help/fr/reply.phtml`).

### Analyseurs Implémentés ✅
*   **`numeric`**, **`numexp`** : Valeurs numériques et expressions calculables.
*   **`algexp`**, **`litexp`**, **`formal`** : Équivalence algébrique (SymPy).
*   **`function`**, **`fset`** : Fonctions et ensembles de fonctions.
*   **`set`** : Ensembles d'éléments (ordre indifférent).
*   **`radio`**, **`menu`** : Choix unique (boutons / liste déroulante).
*   **`clickfill`** : Glisser-déposer — mono-slot (choisir une étiquette) **ou** multi-slots (composer une séquence ordonnée). Voir [§ 6](#6-clickfill--glisser-déposer).
*   **`text`**, **`case`**, **`nocase`**, **`atext`** : Comparaison de chaînes (gestion de la casse et pluriels).
*   **`default`** : Redirection vers `algexp` ou `text`.
*   **`units`**, **`sigunits`** : Unités physiques et chiffres significatifs.
*   **`equation`**, **`range`**, **`vector`** : Équations, intervalles, vecteurs.
*   **`checkbox`**, **`mark`**, **`click`**, **`multipleclick`** : Choix multiples et pointage.
*   **`correspond`** : Appariement de deux colonnes.
*   **`coord`** : Clic sur une image-repère (port de `clickzone.c`).
*   **`jsxgraph`**, **`jsxgraphcurve`** : Géométrie dynamique (figure et courbe tracée).
*   **`chemeq`** : Équations chimiques — comparaison sémantique, à un facteur
    d'échelle près (`def_engine/chemeq.py`).
*   **`numexp2`** *(défini par le module `OEFevalwimsfrac`)* : le `numexp` **sans
    l'exigence d'irréductibilité** — `6/4` y vaut `3/2`. Six exercices.
*   **`jsxgraphobjet`** *(défini par le module `oeftrigoclg1`)* : les objets
    qu'un élève **clique** sur une figure JSXGraph. Trois exercices. Le rendu du
    champ est produit par le moteur (`_render_jsxgraphobjet_embed`), le module
    n'ayant pas de `.input` que PAX sache exécuter.
*   **`draw`** : **Tracé sur une figure** — l'élève pose des croix, des segments
    ou des flèches sur un canevas, et c'est la liste de leurs coordonnées, dans
    le repère du dessin, qui est corrigée. Port d'`anstype/draw` : appariement
    glouton à `1/precision` près, barème `split` / `eqweight`. Neuf exercices
    (`oefpolynet`, `evolmeth`, `oefvectgraph`).

La liste faisant foi est le `match` de `core/answer/checkers.py:check_answer` ;
`_WIMS_KNOWN_TYPES`, dans le même fichier, dit ce que **WIMS** connaît, ce qui
n'est pas la même question. Le relevé de ce qui manque encore est figé par
`tests/core/answer/test_types_non_portes.py` : porter un type l'oblige à en
sortir, et rien n'y entre sans décision.

### Analyseurs Identifiés (Non encore supportés) ❌
*   **Sciences** :
    *   `chemformula`, `chemdraw`, `chemclick`, `reaction` : Chimie (formules,
        tracés, pointage, réactions).
*   **Géométrie** :
    *   `geogebra` : applet de géométrie dynamique (7 exercices).
*   **Algèbre** :
    *   `matrix`, `aset` : matrices et ensembles « assortis ».
*   **Avancé** :
    *   `symtext`, `textcomp` : Outils avancés d'identification de textes (synonymes).
    *   `runcode` : Validation par exécution de code (Python) — 99 exercices.
    *   `reorder`, `puzzle`, `crossword`, `chessgame` : Jeux et mises en ordre.

## 3. Typage Dynamique (Variables)

Dans le corpus OEF, le type de réponse peut être résolu récursivement. PAX doit supporter :
*   **Variables imbriquées** : `type=\var1` où `\var1=\var2` qui vaut `numeric`.
*   **Tests ternaires** : `(\q2==3)?case:numeric`.
*   **Logique de chaîne** : `checkbox iswordof \option?checkbox:radio`.
*   **Indexation** : `\anstype[\m_step]` (types différents par étape).

## 4. Composants de Saisie (Frontend)

*   **`input`** : Champ de texte classique (support de l'option `is_sup` pour les exposants).
*   **`textarea`** : Zone multi-ligne.
*   **`menu`** : Liste déroulante.
*   **`slot`** : Zone de réception "clickfill" (cible de dépôt). Plusieurs `slot` peuvent partager le même `name` (voir [§ 6](#6-clickfill--glisser-déposer)).
*   **`radio`** : Boutons de sélection (support de l'insertion individuelle via `!embed reply N, M`).
*   **`coord`** (`CoordPlane.vue`) : image-repère cliquable, un point.
*   **`draw`** (`DrawAnswer.vue`) : canevas de tracé — clic pour poser une croix,
    départ puis arrivée pour un segment ou une flèche, bouton d'effacement. Le
    segment porte les bornes du repère : c'est en ses unités, non en pixels, que
    la réponse est envoyée.

## 5. Options de Réponses (`option=`)

### Options Globales
*   **`nonstop`** ❌ : Ne s'arrête pas à la première erreur dans les exercices à étapes.
*   **`noanalyzeprint`** ✅ : Masque l'analyse détaillée de l'erreur.
*   **`nospace`** ✅ : Ignore les espaces dans la saisie.
*   **`nocheck`** ❌ : Désactive les vérifications syntaxiques automatiques.
*   **`split`** (ou `partialscore`) ❌ : Accorde des points partiels pour les réponses multiples.
*   **`eqweight`** ❌ : Poids égal pour chaque élément.

### Options Spécifiques aux Analyseurs
*   **Maths** : 
    *   `absolute` ❌ : Tolérance absolue.
    *   `comma` ❌ : Virgule comme séparateur décimal.
    *   `noreduction` ❌ : N'exige pas de simplification (type `numexp`).
    *   `symbols=[...]` ❌ : **option d'UI transverse**, pas une contrainte de
        vérification — une palette de boutons affichée sous le champ, chacun
        insérant son symbole au caret de l'input (`appendToInput`, cf.
        `wims/public_html/scripts/anstype/symbols.inc`). S'applique à tout type
        de réponse, avec rendu via `chemeq` quand le type l'est.
    *   `vector_left`, `vector_right` ❌ : Délimiteurs de vecteurs.
*   **QCM** : 
    *   `shuffle` ❌ : Mélange l'ordre des choix.
    *   `sort` ❌ : Tri alphabétique.
    *   `multiple` ❌ : Choix multiples dans un `menu`.
*   **Interactivité** : 
    *   `noorder` / `keeporder` ❌ : Gestion de l'ordre dans `clickfill`.
    *   `transparent` ✅ : Fond de widget transparent.
    *   `align=left/right` ❌ : Alignement des étiquettes.
*   **Texte** : 
    *   `noreaccent` ❌ : Ne normalise pas les accents.
    *   `symtext` ❌ : Utilise l'analyseur symtext.

## 6. Clickfill — glisser-déposer

`replytype=clickfill` : l'élève glisse des étiquettes depuis un **pool** vers
une ou plusieurs **cibles** (`slot`). Format de `replygoodN` :

```
replygoodN = <correct> ; <pool>
```

- `<correct>` : la (les) bonne(s) réponse(s), items séparés par `,`.
- `<pool>` : toutes les étiquettes proposées (déplaçables), séparées par `,`.

⚠️ **Séparateur vs entités HTML.** Les items peuvent être des entités
(`&#91;`=`[`, `&#93;`=`]`, `&#59;`=`;`) qui se terminent par `;`. Le découpage
`correct ; pool` doit donc **protéger les entités** (`_split_rows_by_semi`),
sinon le `;` d'un `&#93;` est pris pour le séparateur et la réponse est
tronquée.

### Deux modes (déduits du nombre d'items de `<correct>`)

| Mode | `<correct>` | Cibles | `expected` | `choices` |
|---|---|---|---|---|
| **Mono-slot** | 1 item | 1 `slot` | l'item correct | `[correct] + pool` (distracteurs) |
| **Multi-slots** | ≥ 2 items | N `slot` | la séquence ordonnée (jointe par `,`) | le `pool` (il contient déjà toutes les étiquettes) |

Exemple multi-slots (`repgraphint`, composer `]-2;20[`) :

```
val48 = &#93;,\(-2),&#59;,\(20),&#91;          # séquence correcte (5 items)
val32 = &#91;,&#59;,&#93;,\(\cup),\(\cap),...   # pool (13 étiquettes)
replygood1 = $val48;$val32
```

### Nombre de cibles et taille

L'embed porte la taille `W x H x N` :

```
!read oef/embed.phtml reply1,60x40x12
```

- `W`, `H` : largeur / hauteur d'une cible (px).
- `N` : **nombre de cibles** (`60x40x12` → 12 slots ; `60x40x1` → mono-slot).
  À défaut de 3ᵉ dimension, on prend la longueur de `<correct>`.

`_render_embed` émet un `<cf-slot name="replyN" data-index="i">` par cible.

### Composition et vérification

Côté frontend, les cibles d'un même `name` partagent un tableau ; la réponse
est la liste **ordonnée des valeurs non-vides**, jointe par `,`. Le checker
`check_clickfill` compare deux séquences **dans l'ordre** (les cases vides sont
ignorées) ; il fonctionne aussi pour le mono-slot (un item de chaque côté).

Les étiquettes du pool restent réutilisables (un glisser ne les consomme pas) :
une réponse peut réutiliser une étiquette, p. ex. une réunion
`]-∞;a[ ∪ ]b;+∞[` qui emploie `]`, `[` et `;` plusieurs fois.
