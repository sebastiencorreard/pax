# Feuilles d'exercices WIMS — référence de format

> Extrait de l'analyse de `ressources/log/` (61 classes, 56 avec des feuilles).  
> Ce document décrit le format tel qu'il existe sur le disque WIMS, et sert de référence
> pour l'implémentation PAX.

---

## 1. Vue d'ensemble

Une **feuille** (*sheet*) est un ensemble nommé et ordonné d'exercices qu'un enseignant
constitue pour ses élèves.  Elle appartient à une **classe** et peut être ouverte ou fermée
selon une date d'expiration.

Hiérarchie de fichiers dans une classe :

```
classes/<id>/
├── .def              — métadonnées de la classe
├── .motd             — message du jour (HTML)
└── sheets/
    ├── .sheets       — index de toutes les feuilles (statut + titre)
    ├── .sheet1       — contenu détaillé de la feuille 1
    ├── .sheet2       — contenu détaillé de la feuille 2
    ├── …             — jusqu'à .sheet45 observé
    ├── .require      — poids de chaque exercice (par feuille)
    ├── .active       — activation de chaque exercice (par feuille)
    └── .weight       — poids alternatif (uniforme ou personnalisé)
```

---

## 2. Métadonnées de classe — `.def`

Format `!set clé=valeur`, une directive par ligne.

| Clé | Exemple | Description |
|-----|---------|-------------|
| `class_supervisor` | `Marina Cazzola` | Nom de l'enseignant |
| `class_institution` | `Scienze della Formazione Primaria` | Établissement |
| `class_description` | `Geometria` | Intitulé court |
| `class_information` | `Geometria per i docenti…` | Description longue |
| `class_email` | `marina.cazzola@unimib.it` | Email de contact |
| `class_lang` | `it`, `fr`, `nl`, `en` | Langue de la classe |
| `class_creation` | `20150611` | Date de création (YYYYMMDD) |
| `class_expiration` | `21001015` | Date d'expiration (YYYYMMDD) |
| `class_limit` | `200` | Nombre maximum d'élèves |
| `class_level` | `H2`, `H4`, `U1`, `U2` | Niveau (H = lycée, U = université) |
| `class_domain` | `mathematics,elementary_geometry` | Domaines séparés par virgule |
| `class_keywords` | `primaria` | Mots-clés libres |
| `class_secure` | `all` | Sécurité d'accès |
| `class_exolog` | `0` (off) à `7` (max) | Niveau de log des exercices |
| `class_examlog` | `7` | Niveau de log des examens |
| `class_scorecolor` | `#f00e1d,#add223,…` | Dégradé de couleur pour les scores |
| `class_defined` | `yes` | Classe initialisée |

---

## 3. Index des feuilles — `.sheets`

Chaque feuille est décrite par un bloc de lignes consécutives.  
Les blocs se suivent sans séparateur explicite ; l'ordre correspond aux numéros `.sheet1`, `.sheet2`, etc.

### Format d'un bloc

```
:<statut>
<date_expiration>
<titre>
<description_html>
```

- **Ligne 1 — statut** : préfixé par `:`.

  | Valeur | Signification (observée) |
  |--------|--------------------------|
  | `:1`   | Visible et active |
  | `:3`   | Visible mais non scorée (mode "testez-vous") |
  | `:0`   | Cachée |

- **Ligne 2 — date d'expiration** : format `YYYYMMDD`.  
  Une date future lointaine (ex. `21000815`) signifie "ouverte indéfiniment".

- **Ligne 3 — titre** : texte brut.

- **Lignes suivantes — description** : HTML arbitraire (peut contenir balises, entités `&#13;`, etc.).  
  La description se termine à la ligne vide précédant le prochain bloc `:`.

### Exemple réel (classe 1000, nl)

```
:1
21000815
Rekenregels I
<ul>&#13;<li>&#13;<font color="green">gebruik ipv een komma een punt…</font>…</ul>
:1
21000815
Breuken-positieve getallen optellen en aftrekken
<ul>&#13;<li>…</ul>
```

---

## 4. Contenu d'une feuille — `.sheetN`

### 4.1 En-tête

Les premières lignes forment l'en-tête de la feuille (aucun marqueur de délimitation
explicite avec les exercices — l'en-tête se termine à la première ligne commençant par `:`).

| Position | Contenu | Exemple |
|----------|---------|---------|
| 1 | Titre | `Formule (2015)` |
| 2 | Description courte | `conoscere e applicare le principali formule` |
| 3 | Auteur, année | `??, 2015` ou `Marina, Cazzola` |
| 4 | Nombre de sections (non utilisé dans PAX) | `2` |
| 5 | Niveau | `U2` |
| 6 | Domaines | `mathematics, elementary_geometry` |
| 7 | Mots-clés | `levelE5, measurement, area, perimeter, volume` |
| 8 | Auteur (nom complet) | `Marina, Cazzola` |
| 9 | Email | `wims@unimib.it` |
| 10+ | Notes pédagogiques libres | `conoscere e applicare…` |

### 4.2 Exercices

Chaque exercice est un bloc de 5 à 7 lignes commençant par `:chemin/module`.

```
:<niveau>/<domaine>/<module>.<lang>
<paramètres>
<points>
<multiplicité>
<titre_court>
<description>
[<prérequis>]
```

| Champ | Type | Description |
|-------|------|-------------|
| `:<chemin>` | string | Chemin WIMS du module (ex. `H4/algebra/oefcalcullit.fr`) |
| `<paramètres>` | query string | Paramètres de configuration passés au moteur OEF |
| `<points>` | int | Points attribués à cet exercice dans la feuille |
| `<multiplicité>` | int | Nombre d'instances ou d'essais (1, 2, 7, 9 observés) |
| `<titre_court>` | string | Titre court affiché dans la liste |
| `<description>` | string | Description ou consigne |
| `<prérequis>` | string (optionnel) | Condition de déblocage (voir §4.3) |

**Si le champ prérequis est absent**, la ligne de description est la dernière du bloc.
Un exercice sans prérequis est accessible dès l'ouverture de la feuille.

### Exemples réels

**Exercice simple (pas de prérequis)** — classe 1000, nl :
```
:H1/arithmetic/rekenregels-1.nl
subject=1&level=1&total_exos=2&rounding=-1&usage=2&taal=nl
10
1
reken uit I
2 opgaves;
```

**Exercice avec prérequis simple** — classe 1367, it :
```
:U2/geometry/oefgeoprim.it
exo=volumi_cps&qnum=1&qcmlevel=1&scoredelay=&intro_qcmpresent=4&intro_presentsol=1&intro_expert=yes
10
1
Formule #1
applicare una formula
1:90
```
→ déblocage conditionné à ≥ 90 % sur l'exercice 1.

**Exercice avec prérequis cumulatif** — classe 1367, it :
```
:U1/geometry/oefgeo2D.fr
exo=triangle&qnum=2&qcmlevel=1&scoredelay=&intro_presentsol=1&intro_qcmpresent=4&intro_check=1&intro_expert=yes
30
1
Equiestensione
Dalla formula dell'area del triangolo, leggiamo proprietà di equiestensione.
1+2+3:70
```
→ déblocage si la somme des scores des exercices 1, 2 et 3 ≥ 70.

**Exercice avec multiplicité > 1** — classe 1000, nl :
```
:H1/algebra/vergelijkingen-0.nl
subject=17&level=0&total_exos=2&rounding=-1&usage=2&taal=nl
10
7
vergelijkingen oplossen 8
2 opgaves;
```
→ l'élève peut tenter cet exercice 7 fois.

---

## 5. Prérequis — format détaillé

Un prérequis est une **condition de déblocage** exprimée sur les scores d'exercices
précédents de la même feuille (numérotés à partir de 1).

### Syntaxe

```
<expr_exos>:<seuil>
```

| Composant | Format | Signification |
|-----------|--------|---------------|
| `expr_exos` | `N` | Numéro d'un exercice de la feuille |
| `expr_exos` | `N+M+…` | Somme de plusieurs exercices |
| `seuil` | entier 0–100 | Score ou somme de scores minimum requis |

### Exemples observés

| Prérequis | Interprétation |
|-----------|----------------|
| `1:90` | L'exercice 1 doit avoir un score ≥ 90 |
| `2:60` | L'exercice 2 doit avoir un score ≥ 60 |
| `1+2+3:70` | La somme des scores des exercices 1, 2 et 3 doit être ≥ 70 |
| `4+5:80` | La somme des scores 4 et 5 doit être ≥ 80 |

> **Note** : WIMS ne définit pas "score" de façon unique ; selon les modules,
> il peut s'agir d'un pourcentage (0–100) ou de points bruts.
> Dans les exemples observés, les points sont toujours 10, ce qui suggère
> que le seuil est comparé au score normalisé (0–100).

---

## 6. Poids et activation — `.require` / `.active`

### `.require` — poids par exercice

Une ligne par feuille, les poids séparés par des espaces (sans `:` préfixe).

```
10 10 10 10 10 10 10 10 10 10    ← feuille 1 (10 exercices, poids 10 chacun)
10 10 10 10 10 10 10 10          ← feuille 2 (8 exercices)
10 10 10 10 10                   ← feuille 3 (5 exercices)
```

La somme des poids d'une feuille peut différer : elle n'est pas normalisée à 100.
Les poids permettent de pondérer différemment les exercices dans le calcul de la
note globale de la feuille.

### `.active` — activation individuelle

Même format, avec `1` (actif) ou `0` (désactivé).

```
1 1 1 1 1 1 1 1 1 1    ← tous les exercices de la feuille 1 sont actifs
1 1 0 1 1 1 1 1        ← exercice 3 de la feuille 2 désactivé
```

Un exercice désactivé reste visible mais n'est pas scoré.

---

## 7. Paramètres d'exercice

Le champ `<paramètres>` est une *query string* arbitraire passée au module OEF.
Sa structure dépend du module. Paramètres fréquemment observés :

| Paramètre | Description |
|-----------|-------------|
| `exo=nom` | Sous-exercice sélectionné (peut apparaître plusieurs fois pour une liste aléatoire) |
| `qnum=N` | Nombre de questions par session |
| `qcmlevel=N` | Niveau de difficulté QCM |
| `level=N` | Niveau interne au module |
| `subject=N` | Thème interne au module |
| `total_exos=N` | Nombre total d'exercices présentés |
| `random=0/1` | Ordre aléatoire des sous-exercices |
| `scoredelay=` | Délai avant affichage du score (vide = immédiat) |
| `intro_qcmpresent=N` | Nombre de choix affichés dans un QCM |
| `intro_presentsol=0/1` | Afficher la solution après soumission |
| `intro_check=N` | Options d'affichage de correction (peut être répété) |
| `intro_expert=yes` | Mode expert activé |
| `taal=nl` | Langue forcée (pour les modules multi-langue) |
| `lang_choice=it` | Langue alternative |
| `rounding=-1` | Mode d'arrondi (-1 = automatique) |
| `usage=2` | Mode d'utilisation (2 = entraînement) |

Plusieurs `exo=` sur la même ligne signifient que WIMS choisit aléatoirement parmi
la liste à chaque session (équivalent d'un pool).

---

## 8. Niveaux scolaires

Convention utilisée dans les chemins de modules et dans `class_level` :

| Code | Niveau (Belgique/France) |
|------|--------------------------|
| `E1`–`E6` | Primaire (années 1 à 6) |
| `H1`–`H6` | Secondaire (H1 = 1re, H6 = terminale) |
| `U1`–`U4` | Supérieur (licence, master) |

---

## 9. Équivalence avec le modèle PAX

| Concept WIMS | Table PAX actuelle | Champs manquants / à ajouter |
|---|---|---|
| Classe | *(absente)* | Toute la notion de classe/groupe |
| Feuille (`.sheet`) | `sheets` | `open_at`, `close_at` déjà présents ; manque `status` (visible/caché/testez-vous), `keywords`, `author` |
| Exercice dans feuille | `sheet_exercises` | `points`, `multiplicity`, `prerequisite`, `weight`, `active` |
| Activation par exercice | — | Champ `active` dans `sheet_exercises` |
| Prérequis | — | Expression string `1+2:70` à stocker et évaluer |
| Score d'une tentative | `attempts` | Structure compatible |
| Poids | `homework_pools` (partiel) | Sémantique différente |

### Prérequis dans PAX — proposition de stockage

```sql
-- Dans sheet_exercises, ajouter :
prerequisite TEXT   -- ex: "1:90", "1+2+3:70", NULL si aucun
```

Évaluation au moment de l'accès :

```python
def is_unlocked(prerequisite: str, scores: dict[int, int]) -> bool:
    """
    prerequisite: "1+2:70"  ->  scores[1] + scores[2] >= 70
    prerequisite: "1:90"    ->  scores[1] >= 90
    prerequisite: None      ->  True
    """
    if not prerequisite:
        return True
    expr, threshold = prerequisite.split(":")
    indices = [int(i) for i in expr.split("+")]
    total = sum(scores.get(i, 0) for i in indices)
    return total >= int(threshold)
```

---

## 10. Fichiers de référence dans `ressources/log/`

| Fichier | Classe | Particularité |
|---------|--------|---------------|
| `classes/1367/sheets/.sheet1` | it | Exemples riches de prérequis simples et cumulatifs |
| `classes/1127/sheets/.sheets` | fr | Format `.sheets` avec statut `:3` (testez-vous) |
| `classes/1000/sheets/.sheet1` | nl | Feuille sans prérequis, paramètres `subject=/level=` |
| `classes/1000/sheets/.sheet11` | nl | Multiplicité = 1, grande feuille (13 exercices) |
| `classes/1000/sheets/.require` | nl | Poids uniformes (tous à 10) |
| `classes/1152/` | — | Classe avec le plus grand nombre de feuilles (45) |
