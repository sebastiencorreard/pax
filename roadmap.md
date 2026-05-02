# PAX : Roadmap de Développement

PAX est un clone moderne et performant de WIMS, conçu pour éliminer la dette technique historique tout en préservant la richesse pédagogique du format OEF. L'accent est mis sur la durabilité, une expérience utilisateur "mobile-first" et une architecture typée.

## 🎯 Vision & Principes Directeurs

- **Rétrocompatibilité :** Support des fichiers OEF existants via un parser robuste.
- **Modernité :** Transition vers le "PAX-Script" (Python/Markdown/YAML).
- **Didactique :** Centré sur les usages réels (DM WIMS, Courses, Séquences).
- **Gamification :** Engagement des élèves via un système de récompenses (pièces, badges).
- **Qualité de Code :** Backend Python 3.10+ typé et Frontend Nuxt (TypeScript).

---

## 🛠 Stack Technique

### Backend (Python)
- [x] **Framework :** FastAPI (pour l'API-First et la validation Pydantic).
- [x] **Parsing :** Lark (pour l'OEF historique).
- [x] **Calcul Formel :** SymPy.
- [ ] **Sécurité :** Sandboxing pour l'exécution du code professeur.
- [x] **Qualité :** Ruff (lint/format), Mypy (typage), Pytest (tests).

### Frontend (Nuxt 3)
- [ ] **Langage :** TypeScript.
- [ ] **Styles :** Tailwind CSS (Themable, Dark Mode).
- [ ] **State Management :** Pinia (pour la progression et gamification).
- [ ] **Rendu Graphique :** D3.js / JSXGraph (vectoriel interactif).

---

## 📋 Règles de Développement

### Qualité & Standardisation
- **Typage Strict :** Tout le code Python doit être typé. `Any` est proscrit.
- **Auto-formatage :** Utilisation de `pre-commit` hooks pour lancer **Ruff** et **ESLint** avant chaque commit.
- **Documentation :** Docstrings format Google (uniquement pour le "pourquoi"). Le "comment" est porté par le typage.

### Architecture des Données
- **Versionnage Source :** Table `ExerciseVersion` stockant le code OEF indexé par son **Hash**.
- **Persistance des Tentatives :** Table `Attempt` stockant uniquement le triplet `(User_ID, Version_Hash, Seed)`.
- **Versioning Logic :** Logique de création de nouvelle version en DB lors de modifications profondes de l'OEF.
- **Logs Bruts :** On stocke les réponses brutes des élèves. Les scores sont des "vues" calculées à la volée.

---

## 🚀 Phases de la Roadmap

### Phase 1 : Le Cœur (Core Engine)
- [ ] Finaliser le parser Lark pour l'OEF.
- [ ] Créer le service de Sandboxing (Runner) pour exécuter le code côté serveur.
- [ ] Intégrer SymPy pour l'équivalence mathématique ($x^2-1 == (x-1)(x+1)$).
- [ ] Définir les schémas Pydantic pour les contrats d'interface (Exercice/Réponse).

### Phase 2 : Rendu & UX Élève (Nuxt)
- [ ] Mise en place de l'interface Mobile-First.
- [ ] Créer les "Handlers" de rendu : Champs texte, Drag & Drop, Dominos.
- [ ] Système de feedback immédiat et diagnostique (messages d'erreur riches).
- [ ] Gestion du mode sombre et de l'accessibilité (RGAA).

### Phase 3 : Espace Professeur & IDE
- [ ] Intégration de Monaco Editor dans Nuxt avec coloration syntaxique.
- [ ] Système de "Fork" d'exercices (copie locale sur serveur pour modification).
- [ ] Prévisualisation "Hot Reload" via le Runner Backend.
- [ ] Gestionnaire de banque de ressources (fichiers images/data).

### Phase 4 : Logique de Classe & Notations
- [ ] Implémentation des types de feuilles (Entraînement, DM WIMS, Courses).
- [ ] Moteur de séquençage (déblocage d'exercices par date ou réussite).
- [ ] Dashboard de suivi des notes et historique des réponses pour le prof.
- [ ] Authentification CAS/ENT (EduConnect).

### Phase 5 : Gamification (PAX Experience)
- [ ] Système de monnaie virtuelle (pièces) et expérience (XP).
- [ ] Boutique cosmétique pour avatars et thèmes.
- [ ] Moteur de badges (succès basés sur la régularité et la performance).

---

## 🤖 Configuration Automatisée (Projet)

Le projet utilise un fichier `pyproject.toml` pour harmoniser le développement :
```toml
[tool.ruff]
select = ["E", "F", "I", "N", "UP"]
ignore = []
line-length = 88

[tool.mypy]
strict = true
ignore_missing_imports = true

[tool.pytest.ini_options]
testpaths = ["tests"]