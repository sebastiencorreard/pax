# Feuilles côté élève — conception

*Rédigé le 2026-10-02. Décisions de l'utilisateur : une feuille peut être
affectée à **plusieurs classes** (choix révisable) ; la note suit **le modèle
de WIMS dès le départ** ; les **graines sont délivrées par le serveur** dans le
même chantier (TODO IV.2 bis).*

## 1. Ce qui existe

- `Class`, `ClassStudent`, `/api/classes` (dont `/mine` pour l'élève).
- `Sheet` (de l'enseignant, non d'une classe) : `status` (0 caché, 1 visible et
  noté, 3 « testez-vous »), `open_at`, `close_at`.
- `SheetExercise` : `points` (les points requis, défaut 10), `weight`,
  `multiplicity`, `prerequisite`, `active`, `qcmlevel`, `confparm`.
- `Attempt` (`sheet_id`, `score`, `seed`, `answers`, `is_graded`), `Grade`.
- `HomeworkAssignment`, `HomeworkPool…` : ébauche du premier commit, jamais
  utilisée.

Manquent : le lien feuille ↔ classe, toute l'interface élève, la note de
feuille, et le contrôle des graines.

## 2. Le modèle de note de WIMS

Sources : `src/Wimslogd/wimslogdscore.c` (état par exercice),
`src/score.c` (pourcentages par feuille, prérequis),
`modules/adm/class/userscore/` et `scripts/adm/class/sheetweights` (formule),
`bases/sys/define.conf` (défauts). Lu sur le WIMS 4.32 local.

### 2.1 L'état d'un élève sur un exercice de feuille

Chaque note enregistrée `s` (0 à 10, bornée à [-10, 10]) met à jour
(`scoreline`) :

| champ | mise à jour | sens |
|---|---|---|
| `user` | `+= s` | somme des notes |
| `user2` | `= 0,85·user2 + s` | qualité : les notes récentes pèsent plus |
| `high[0..N-1]` | les N meilleures notes, N = requis/10 | |
| `best` | somme des `high` | |
| `level` | `high[0]`, la plus faible des N meilleures | |
| `last` | `s` | |
| `try` | `+1` | essais notés |
| `new` | `+1` à chaque nouveau tirage (`new`, `renew`) | tirages, notés ou non |
| `hint` | `+1` à chaque indication demandée | |

Une note n'est comptée que si elle suit un `new` de **la même session, même
feuille, même exercice** (« mesure contre le score simultané ») et n'arrive pas
juste après une rafale.

### 2.2 Ce que `getscore` en tire

- `score` = `min(user, requis)`.
- `quality` = `user2 / (ts·tt)`, avec `ts = (1 - 0,85^try) / (1 - 0,85)` et
  `tt = 1` si `snew < 2·try + 5`, sinon `(snew - 4) / (2·try)` — où
  `snew = new (+1 s'il y a eu une indication)`. Autrement dit : un tirage
  abandonné par essai noté, plus cinq, sont gratuits ; au-delà, la qualité
  baisse.
- Sans essai noté : tout vaut 0.

### 2.3 Les pourcentages d'une feuille (`getscorepercent`)

Sur les exercices **actifs** de la feuille, chacun pondéré par son `weight`
(0 si `requis` = 0) :

- un exercice de qualité `< 1` est ignoré ; de qualité `< 2`, ses points
  (`score`, `best`, `level`) sont divisés par deux ;
- `d = score·weight` ;
- **cumul** `I0 = rint(100·Σd / Σ requis·weight)` ;
- **qualité** `Q = Σ quality·d / Σd` (0 à 10) ;
- **meilleur** `I1 = rint(100·Σ best·weight / Σ requis·weight)` ;
- **niveau** `I2 = rint(10·Σ level·weight / Σ weight)`.

### 2.4 La note de la feuille

Réglages par feuille (`DF_SEVERITY = 1 2 1` par défaut) : poids `w`, formule
`s` (0 à 6), indicateur `ss` (0 à 2 : `I0`, `I1` ou `I2`).

| s | formule |
|---|---|
| 0 | `max(I, Q)` |
| 1 | `I` |
| 2 | `I·Q^0,3` (défaut) |
| 3 | `I·Q^0,5` |
| 4 | `I·Q` |
| 5 | `I²·Q` |
| 6 | `(I·Q)²` |

avec `I = I_ss / 100`, `Q = qualité / 10`.
Note de la feuille = `rint(100·scoremax·f) / 100`, `scoremax` = 10 par défaut.
Note globale = moyenne des notes de feuilles **actives**, pondérée par `w`.

### 2.5 Prérequis (`_depcheck`)

Un exercice porte des dépendances `e1,e2,…:p` : il s'ouvre quand, sur ces
exercices, `Σscore / Σrequis · √(Σquality / (n·10)) · 100 ≥ p`. Ignoré si
`Σrequis < 10`.

### 2.6 Graines (`seed_score`)

WIMS garde, par exercice, les graines tirées et leur note (−1 non notée, −2
« noscore »), au plus 70 (`MAX_SCORESEED`). Les réglages `seedrepeat`
(nombre de fois qu'un même tirage est reproposé) et `exotrymax` (nombre
d'essais notés) s'appuient dessus.

## 3. Ce que PAX en fait

### 3.1 Données

- `sheet_classes (sheet_id, class_id, status, open_at, close_at)` : la feuille
  affectée à une classe, avec ses dates à elle.
- Sur `sheets` : `formula` (0–6, défaut 2), `indicator` (0–2, défaut 1),
  `weight` (défaut 1). `scoremax` par classe (défaut 10).
- `draws` — les tirages délivrés : `(student_id, sheet_item_id, seed,
  issued_at, scored_at, score)`. C'est le `seed_score` de WIMS, et le support
  de la sécurité.
- L'état de l'élève (§2.1) **se recalcule** à partir des tirages notés, dans
  l'ordre — comme `rawscorecalc` relit le journal. Pas de cache au départ.

### 3.2 Graines délivrées par le serveur

- L'élève ne choisit plus sa graine : `/api/sheets/…/items/{id}/draw` en
  délivre une (nouvelle, ou la même tant que `seedrepeat` le permet).
- `/api/check` dans une feuille exige un tirage **délivré à cet élève et non
  encore noté** ; il enregistre la note **une fois** par tirage. Un second
  envoi sur le même tirage est corrigé mais non compté (`noscore`).
- Hors feuille (entraînement libre), rien ne change.

### 3.3 Étapes

1. **Moteur de note** : port de §2.1 à §2.5 en fonctions pures, testées sur
   des cas calculés à la main ; puis confrontées au WIMS local (une classe de
   test, un élève, quelques exercices, notes relevées).
2. **Données et graines** : migration, `draws`, contrôle dans `/api/check`.
3. **API élève** : ses feuilles (via ses classes, statut, dates), le détail
   d'une feuille (par exercice : points, qualité, meilleur, essais ; verrous
   de prérequis ; note de feuille).
4. **Front élève** : liste, page de feuille, lancement d'un exercice en mode
   feuille.
5. **Front enseignant** : affecter une feuille à des classes, dates, réglages
   de note ; tableau des notes de la classe.

Non repris au départ : la **rafale** (`checkrafale`), les examens, les notes
manuelles, `exotrymax`, `multiplicity`, les versions d'exercice
(`techval`). Chacun est noté ici pour ne pas être oublié.
