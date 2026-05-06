# Les Feuilles d'Exercices WIMS

Ce document synthétise le fonctionnement technique des feuilles d'exercices dans WIMS, basé sur l'analyse du code source (`adm/class/sheet`) et des fichiers de configuration des classes (`log/classes/`).

## 1. Structure Technique

Les feuilles d'exercices sont stockées dans le répertoire `log/classes/<CLASS_ID>/sheets/`.

### Fichiers principaux :
- `.sheets` : Index des feuilles de la classe. Chaque entrée définit l'état (0: en préparation, 1: active, 2: expirée, 3: cachée), la date d'expiration, le titre et la description.
- `.sheetN` : Contenu détaillé de la feuille numéro `N`. Chaque exercice est défini par une ligne commençant par `:` suivie du chemin du module, des paramètres, des points requis, du poids et du titre.
- `.require` : Liste des points à obtenir pour chaque exercice de chaque feuille.
- `.weight` : Liste des poids (importance) de chaque exercice.
- `.severity` : Définit les règles de calcul des notes (formule de sévérité) pour chaque feuille.

## 2. Paramètres des Exercices dans une Feuille

Chaque exercice ajouté à une feuille possède des paramètres spécifiques qui influencent le comportement et la notation :

| Paramètre | Description |
| :--- | :--- |
| **Points requis** (`require`) | Le nombre total de points que l'élève doit accumuler. Généralement fixé à $10 \times n$. L'élève doit "réussir" l'exercice plusieurs fois pour atteindre ce total. |
| **Poids** (`weight`) | Coefficient multiplicateur de l'exercice dans le calcul de la note globale de la feuille. |
| **Tentatives Max** (`exotrymax`) | Nombre maximal de tentatives dont le score est pris en compte pour la note. Une fois ce nombre atteint, l'élève peut continuer à s'entraîner, mais son score n'évolue plus. |
| **Répétition de graine** (`seedrepeat`) | Permet de présenter exactement le même exercice (même tirage aléatoire) $n$ fois avant d'en changer. Utile pour la remédiation immédiate. |
| **Dépendances** (`mod_dep`) | Conditionne l'accès à un exercice à la réussite d'un autre exercice de la feuille. |

## 3. Système de Notation et Indicateurs

WIMS utilise quatre indicateurs de base pour évaluer le travail sur un exercice :

1.  **Cumul ($i_0$)** : Somme des scores obtenus, plafonnée aux points requis. C'est l'indicateur de "quantité" de travail.
2.  **Réussite ($i_1$)** : Moyenne des $n$ meilleurs scores obtenus. C'est l'indicateur de "maîtrise".
3.  **Acquisition ($i_2$)** : Le score le plus bas parmi les $n$ meilleures tentatives. Garantit que l'élève a compris de manière stable.
4.  **Qualité ($q$)** : Moyenne pondérée et incrémentale des scores. Les derniers essais pèsent plus lourd. Elle est pénalisée si l'élève abandonne trop d'exercices en cours (essais non terminés).

### Formules de sévérité (Calcul de la note finale)
Le professeur choisit une règle (0 à 5) qui combine ces indicateurs. Par exemple :
- **Règle 1** : La note dépend uniquement de l'indicateur choisi ($I_0, I_1, I_2$). La qualité n'est pas prise en compte.
- **Règle 2** : La qualité a un faible impact.
- **Règle 4** : Pour avoir 10/10, il faut avoir tous les points requis ET une qualité de 10/10 (aucune erreur).

## 4. Restrictions de Temps et d'Accès

Le paramètre `allow` (ou `IPscore`) gère les restrictions :
- **Temps limité** (`timelimit`) : Définit des plages horaires de scoring (ex: `timelimit=>20240501.08:00 <20240501.10:00`). En dehors de ces plages, l'élève peut faire l'exercice mais son score n'est pas enregistré.
- **Restriction IP** : Limite le scoring à certaines machines (salles de TP).

## 5. Fonctionnements Particuliers

- **Feuilles Individualisées** (`indivtechvar`) : WIMS permet de modifier les exercices ou les paramètres d'une feuille en fonction d'une "Variable Technique" associée à l'élève. Ainsi, des groupes d'élèves différents peuvent voir des exercices différents au sein de la même feuille.
- **Mode Examen** : Bien que distincts des feuilles, les examens utilisent une logique similaire mais avec un temps global chronométré, un nombre de tentatives limité pour toute la session, et la désactivation des aides (solutions, feedback).
- **Testez-vous** : Souvent utilisé comme convention de titre pour des feuilles en mode "auto-évaluation" où le scoring est libre et non bloqué par des tentatives max.
