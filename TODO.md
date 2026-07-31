# I. Moteur def

## 1. Comprendre mieux

- [ ] Lister tous les types de réponses attendus, voir à quoi ils correspondent

- [ ] Lister tout ce qui manque dans l'implémentation du moteur

## 2. paramétrage des exercices

$\rightarrow$ comment sont-ils pris en compte ? (implémenté ou pas ?)

$\rightarrow$ où régler les paramètres ?

## 3. Conformité WIMS (réf. docOEF4, audit 2026-06-12)

### a) Notation / précision (prioritaire)

- [x] **Brancher `\precision{M}`** : injecté par `def_engine._wims_precision` (borné 20..1e8, défaut 10000) dans `options["precision"]`, consommé par `check_numeric/numexp/unit/fset`. Formule exacte de `compare.c` : `|d1-d2|*prec ≤ |d1+d2| + 1/prec`, avec 2ᵉ passage à `sqrt(prec)` → crédit partiel 0.5 (« bonne à précision près »). Option `absolute` gérée. (`checkers.py` `_wims_num_equal`)
- [x] **`numexp` formel** : réécrit en comparaison **rationnelle exacte** (`_parse_exact_rational` → `Fraction`) — rejette `2/8` pour `1/4` (non réduit, sauf option `noreduction`), `0.333` pour `1/3` (pas de tolérance), les expressions composées (`nocompute`) et le mélange `/`+`.` (`badform`). Repli flottant (précision WIMS) quand un côté n'est pas un rationnel simple (attendu composé/non évalué). Cohérence corpus vérifiée : 3475/3573 `expected` round-trip ; les 98 restants ont un `expected` malformé (listes, `rint(GCD())` non évalué, `NaN`) — bugs d'évaluation préexistants, pas de régression.
- [x] **`\condition` multiples** : **déjà géré dans le chemin live** (le `engine.py:622` du constat était le pipeline legacy, mort pour le corpus compilé). Les `\condition{}` compilent vers la section `:test` (`condtestN`/`condweightN`/`condnameN`) ; `check_analyze`/`run_analyze` évaluent **chaque** condition et notent `Σ(condtestN·condweightN)/ΣcondweightN` (fraction pondérée, cf. test `test_cant_irreducible_fraction_scoring` → 0.75). L'affichage par condition passe par la section `:feedback` (exécutée par `render_feedback`). Reste différé : `\conditions{}` (sélection dynamique, 1 usage corpus) et le flag `hide`. NB : 14 exos `conditioncnt≥2` ne routent pas vers run_analyze mais c'est un problème distinct (0 réponse extraite : widgets jsxgraph/canvas/runcode), pas d'extraction de condition.
- [x] **`option=default=xxx`** : réponse vide → substituée par xxx puis vérifiée (WIMS `step.proc`). Couvre `default=vide` (fset : vide = ensemble ∅, cf. oefresolalg synth*) et `default=$valN`. **Bug corrigé au passage** : l'ancien `default=vide` excluait de la notation *toutes* les réponses le portant — donc les vrais ensembles-solutions des synth n'étaient pas notés, et eqalgpara/ineqalgpara (brouillon `default=empty`) étaient insolubles (run_analyze forcé, bonne réponse → 0).
- [x] **Type `draft` (brouillon) + marqueur `options["ungraded"]`** : champs `type=draft` (et `analyze`+`default=vide` sans `:test`, ex. dev2fact) désormais ni notés ni obligatoires, keyés sur le TYPE et non sur la chaîne `default=vide`. Consommé par `check.py` (exclusion) et le front (`allFilled`). Corrige synth1deg/2deg/synthquot, eqalgpara1-5, ineqalgpara1-5 ; préserve dev2fact1/2.
- [x] `\computeanswer{no}` : injecté dans `options`, refuse une réponse `numeric` composée (`5*5` pour `25`) via `_wims_has_compound_arith` (règle exacte d'`anstype/numeric` : opérateurs `+-*^(` ou `.`+`/`) ; `computeanswer=yes` autorise le calcul. Fractions simples/décimaux acceptés.
- [~] `sc_reply` : « bonne à précision près » → 0.5 fait pour numeric/numexp (2ᵉ passage sqrt) ; reste le « partiellement juste » d'autres types

### b) Types litexp / algexp / formal (§1.4.5, testés)

PAX rabat les trois sur `check_algexp` (SymPy) + pré-checks de forme :

- [x] **`formal`** : retiré de l'auto-classification développé/factorisé → équivalence CAS pure (`(x+1)(x-1)` accepté pour `x^2-1`, `2*(x+3)` pour `2*x+6`). Options explicites `polexpand`/`polfactor` toujours honorées. (12/428 self-checks échouent encore = limites CAS sympy sur formules physiques `sqrt`, préexistant.)
- [x] **`litexp`** : `check_litexp` = égalité CAS + forme **rawmath conforme** (`_rawmath_normalize` : nospace + `*` implicite + `**`→`^`, sans simplification). `6/4`/`x*x+3`/`1.5` → `badform` ; `2x+3`=`2*x+3` OK ; alternatives virgulées gérées. Options explicites `expand`/`polfactor` gardent la voie check_algexp. Corpus : 268 formes stockées, 0 régression.
- [x] **`algexp`** : équivalence **rationnelle** (`check_algexp(rational_only=True)` → `cancel`, sans trig) → `sin²+cos²` refusé pour `1`/`x²+1` ; retiré de l'auto-classification de forme → coefficients non simplifiés acceptés (`(24+4)*x-53`, `2*x+3*x` pour `5*x`, `x*x` pour `x²`). Options explicites `expand`/`polfactor` gardent la voie check_algexp. Corpus : 204 formes, 19 refus tous préexistants (expected malformés `print(print(...`, matrices `f=c in`, edge polfactor).
- [x] **Fonctions maxima `coeff`/`hipow` imbriquées** : fournies à sympy (`cas.py:_sympify_arg`) → `coeff(P,b,2)*(b^2)` s'évalue au lieu de fuir. Répare `developper.def` (litexp expected `coeff(...)` non évalué → `c e f f o \left(` mangé).

### c) Autres types de réponse

- [x] **`nocase`** : `check_nocase` — match exact après normalisation (ponctuation→espace, accents/casse/espaces ignorés) contre toute alternative `|`. Self-check corpus 40/0.
- [x] **`atext`** : `check_atext` — normalisation nocase + **suppression des mots vides** (articles, via `atext.dic`) + **racinisation pluriel/genre** (via `suffix.<lang>`, algorithme WIMS : mot inversé, plus longue clé-préfixe remplacée) + alternatives `|`. « les triangles » = « un triangle » = « triangle » ; « carrés » = « carré ». Dictionnaires WIMS copiés dans `backend/core/answer/data/atext/` (fr/nl/en). Self-check 39/0.
- [~] **`dragfill`** (~25 exo) : actuellement routé vers `check_text` (fallback) ; self-check corpus 385/0 (l'`expected` round-trip). **Reste à vérifier/corriger** : (a) le format exact sérialisé par le composant front pour les étiquettes glissées (séparateurs, entités HTML `&#91;`) doit matcher l'`expected` ; (b) alternatives `|` non découpées (chform1) ; (c) contrainte « chaque étiquette une seule fois ». Nécessite une investigation frontend → item dédié.
- [x] **`units`** : moteur `sympy.physics.units` (zéro dépendance) — `_unit_to_si` couvre préfixes, puissances, unités **dérivées** (N, J, Ω…) et **non-métriques** (h, min, °). Accepte `36 km/h`=`10 m/s`, `90 min`=`5400 s`, `1 kOhm`=`1000 Ohm`, `400 dm²`=`4 m²`. Comparaison valeur+dimension+précision WIMS conservée. **Bugs corrigés** : notation scientifique (`3.34e-26 kg` : split valeur/unité, `_parse_number`, et `_wims_has_compound_arith` qui prenait le `-` de l'exposant pour un calcul). 101 unités corpus parsées ; 30 refus = expected malformés préexistants (HTML/rint).
- [x] `click` : **déjà fonctionnel** — mappé vers `clickfill` (matching par contenu du choix, pas par position `~k`). formule1-5 et compTrinomeSign* notent correctement (self-check OK). La note « non câblé » était obsolète.
- [x] **`raw`** : `check_raw` — comparaison exacte de chaîne après filtres pilotés par option (`nospace`, `nocase`, `deaccent`, `nodigit`, `nopunct`, `noparenthesis`, `nomathop`, `noquote`). Routé depuis le dispatch. 585 tests core.
- [ ] `range`, `matrix`, `vector`, `complex`, `equation`, `reorder`, `compose`, `flashcard` : absents, 0 usage corpus → différé

### d) Étapes, rendu, moteur

- [ ] **`\nextstep`** (étapes dynamiques selon réponses, §4.3.3-4) : traité comme course ordinaire — vérifier sur `moles.nl/masse1-2`, `numeration.fr/convertir10`, `oefspeed.nl/*` ; option `nonstop` non gérée ; heuristique `total_steps` fragile
- [ ] **`\special`** : seul `mathmlinput` rendu ; `help` contextuel (`help_subject`), `tooltip`, `imagefill` (champs sur image), `codeinput` ignorés en silence
- [ ] `\embed` lignes supplémentaires (`style="…"`, mot-clé `default` → classe `wims_oef_input`)
- [ ] `exec` : maxima/pari seulement ; `octave`/`gap`/`float_calc` → vide silencieux (§2.5)
- [ ] **PARI impératif** : `_call_pari` (`cas.py`) n'évalue qu'une **expression** unique (`gcd(...)`, `polcoeff(...)`, `print(expr)`). Les **programmes** `!exec pari { i=…; l=[…]; for(j=1,4,…print(l[j])) }` (affectations, `for(...)`, `print` multiples, indexation/mutation de listes) ne sont pas exécutés → la source brute fuite dans la valeur calculée (mêmes symptômes que le bug GCD). Débloque les 21 derniers `expected` numexp malformés : `liste_portee1/2` (oefpython.fr, ~18) et `bergamo6`/`slib/stat/variance` (branche pondérée, 3). Chantier = mini-interpréteur PARI/GP (parser d'affectations + boucle `for` + `print` accumulant la sortie + listes). NB : `bergamo6` a aussi un `!endif weight` (endif à commentaire) non géré.
- [ ] Flydraw : manquent `levelcurve`, `affine`, `copyresized`, `plotjump`/`plotstep`, `filltoborder`, `diamondfill`/`dotfill`, `rays` — 0 usage corpus → différé
- [ ] Corriger `docs/types-exercices-reponses.md:82` : `symbols=` n'est pas « variables autorisées de formal » mais une option d'UI transverse (palette de boutons insérant au caret, cf. `wims/.../anstype/symbols.inc`)

Conforme (vérifié) : opérateurs compare.c, indices négatifs/tranches, `\for`/`\while`, alias `r1`/`reply1`/`rep1`, `\feedback` + `sc_reply`/`m_reply`, bonnes réponses multiples, `case` avec `|`, `correspond`+`split`, virgule décimale, `\hint`/`\help`/`\solution`, `\css`.

# II. Fonctionnalités PAX

## 1. Feuilles ?

## 2. Statistiques d'utilisation du site

## 3. Clavier virtuel mathématique

Barre en bas d'écran, masquable, compacte (touches de base + extension), mobile et desktop.
Contrainte : les réponses sont des `<input>` texte brut (syntaxe WIMS, virgule décimale) — un clavier produisant du LaTeX ne se branche pas directement.

Options :
- [ ] **Composant maison** (recommandé) — mini-clavier Vue (~150 lignes) insérant des tokens au caret de l'input focalisé ; zéro dépendance, KaTeX déjà là pour les étiquettes
- [ ] **simple-keyboard** (hodgef) — léger, layout custom, insère dans les inputs existants ; mais layout math à construire soi-même, dépendance peu justifiée pour ~20 touches
- [ ] **MathLive** — clavier intégré excellent (layouts compact/minimalist, politique manual) mais couplé aux `<math-field>` (valeur LaTeX) → conversion LaTeX→WIMS à écrire, bundle lourd ; à considérer seulement si on veut la saisie WYSIWYG 2D
- [ ] **MathQuill** — écarté : jQuery, maintenance sporadique, pas de clavier intégré

# III. Mentions légales

## 1. Créer des CGU

## 2. Page sur les licences

## 3. Manifeste et remerciements à WIMS

# IV. Sécurité

## 1. Retirer la possibilité de créer des user admin et super-admin depuis l'API

## 2. Supprimer les scripts de création d'utilisateurs + reset mdp ?

