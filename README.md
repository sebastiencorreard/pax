# PAX — Progrès en Automatismes par les eXercices

Clone de WIMS, rétro-compatible avec le format OEF / DEF, orienté mathématiques.

## Stack

- **Backend** : Python 3.12 + FastAPI
- **Frontend** : Nuxt.js (Vue 3)
- **Base de données** : PostgreSQL
- **Cache** : Redis
- **Calcul symbolique** : SymPy

## Lancer le projet en développement

Tout est dans des containers docker : backend, frontend et postgresql.
Il suffit de lancer, la première fois, la commande suivante :

```bash
docker compose up --build
```

Docker se charge de télécharger tous les composants (au premier lancement) et de construire les trois containers (~5 min en tout).
Le site est ensuite accessible dans un navigateur à l'adresse localhost:3000

### Attention : à faire au premier lancement

1. Installer et configurer docker

- Packages à installer : `sudo apt install docker-ce docker-ce-cli containerd.io docker-buildx-plugin docker-compose-plugin` (pour Ubuntu/Debian/Mint)

- Créer le groupe docker : `sudo groupadd docker` 

- Ajouter son utilisateur au groupe docker `sudo usermod -aG docker $USER`

- Appliquer les changements (ou redémarrer le terminal) `newgrp docker`

2. Peupler les base de données. Pour le moment, à la main :

- Table des exercices : `docker compose exec backend python scripts/import_exercises.py` (pour les H4)
ajouter les H3 :  `docker compose exec backend python scripts/import_exercises.py --level H3`

- Table des académies : `docker compose exec backend python scripts/import_academies.py /ressources/a_integrer_dans_db/academies_france.csv`

- Table des établissements (Aix-Marseille seulement, pour le moment) : `docker compose exec backend python scripts/import_etablissements.py 
ac-aix-marseille.fr /ressources/a_integrer_dans_db/etablissements_aix_marseille.csv`

- Tables des utilisateurs : `./create_user.sh --email admin@pax.fr --first-name Jane --last-name Goodall --role admin`

## Hot reload

Normalement, tout changement dans le backend, frontend ou la base de données est répercuté "à chaud", càd sans commande particulière.

Si ce "hot reload" ne fonctionne pas bien, on peut toujours relancer les 3 serveurs avec ces deux commandes
```bash
docker compose down
docker compose up --build
```

## Utilisateurs

Il existe 4 roles :
- student
- teacher
- admin
- super_admin

1. On peut créer des utilisateurs *dans* le docker :
`exec docker compose exec backend python scripts/create_user.py  --email EMAIL@pax.fr --first-name PRENOM --last-name NOM --role ROLE`

2. On peut aussi faire un reset du mot de passe *dans* le docker :
`docker compose exec backend python scripts/reset_password.py --email VOTRE_EMAIL@pax.fr --password VOTRE_NOUVEAU_MOT_DE_PASSE`


## Dépendances

### Ce qui tourne tout seul

Deux automatismes, une fois `.github/` présent sur la **branche par défaut** —
Dependabot y lit sa configuration et les workflows planifiés n'en partent que
de là. Sur une autre branche, rien ne se déclenche.

- **Dependabot** (`.github/dependabot.yml`) — le lundi matin, ouvre les PR de
  montée (pip, npm, docker, actions), 5 au plus par écosystème. Les mineures et
  correctifs sont **groupés en une seule PR** : FastAPI épingle starlette et
  pydantic suit FastAPI, donc des PR séparées seraient rouges par construction.
  Les majeures de `nuxt`, `pinia` et `@vueuse` sont **ignorées** — ce sont des
  migrations, pas des montées.
- **Workflow « Dépendances »** (`.github/workflows/dependencies.yml`) — le même
  jour, lance `pip-audit` et `npm audit`. Il répond à ce que Dependabot ne dit
  pas : *y a-t-il une faille connue maintenant ?* Un avis peut sortir sans
  qu'aucune montée n'existe. Tourne aussi sur toute PR touchant
  `requirements.txt` / `package.json` / `package-lock.json`, et à la demande.

**Pour être averti**, l'onglet *Actions* ne suffit pas : GitHub n'envoie de
courriel sur échec d'un run planifié qu'à la dernière personne ayant modifié le
workflow. Activez *Watch → Custom → Actions* sur le dépôt.

### Le même contrôle en local

```bash
./scripts/check-deps.sh            # tout
./scripts/check-deps.sh backend    # Python seulement
./scripts/check-deps.sh frontend   # npm seulement
```

Sort en code 1 s'il reste une faille bloquante. Ne dépend pas de GitHub.

`PYSEC-2026-1325` (`ecdsa`, attaque temporelle Minerva sur P-256) est écarté du
script comme du workflow : l'amont considère les canaux auxiliaires hors
périmètre, donc l'avis ne se refermera jamais. Non atteignable tant que les JWT
sont signés en HS256 — **à réactiver si l'on passe un jour à ES256**.

### Appliquer une montée

Le point contre-intuitif : **un `restart` ne suffit jamais, il faut reconstruire
l'image.**

```bash
# Backend — après édition de backend/requirements.txt
docker compose build backend
docker compose up -d backend
docker compose exec -T backend pytest tests/ -q
```

Reconstruire n'est pas du zèle : `pip install` dans un conteneur vivant garde
les paquets déjà présents et masque une dépendance non déclarée. C'est ainsi
qu'`email-validator`, tirée implicitement par FastAPI 0.111 et plus par la
0.141, n'est apparue manquante qu'à la reconstruction complète.

```bash
# Frontend
cd frontend && npm install <paquet>@<version> && cd ..
docker compose build frontend
docker compose down frontend && docker compose up -d frontend   # `restart` NE SUFFIT PAS
```

`/app/node_modules` est un **volume anonyme** (`docker-compose.override.yml`) :
un `restart` conserve les paquets d'origine du conteneur, et l'on croit vérifier
une montée alors qu'on teste l'ancienne. Seul un `down` détruit le volume.

Pour une montée non triviale, ajouter la régression corpus côté backend
(cf. [`docs/def-engine-workflow.md`](docs/def-engine-workflow.md)) et la suite
e2e côté front (`cd frontend && npx playwright test`). Cette dernière rend
aujourd'hui 17 échecs préexistants — elle décrit une page `/exercise` remplacée
depuis — donc c'est **l'écart** qui compte, pas le total.

## Licence

AGPL-3.0
