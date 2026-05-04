# PAX — Progrès en Automatismes par les eXercices

Clone de WIMS, rétro-compatible avec le format OEF, orienté mathématiques.

## Stack

- **Backend** : Python 3.12 + FastAPI
- **Frontend** : Nuxt.js (Vue 3)
- **Base de données** : PostgreSQL
- **Cache** : Redis
- **Auth** : Keycloak (compatible GAR/ENT)
- **CAS** : SymPy + Maxima

## Lancer le projet en développement

Tout est dans des containers docker : backend, frontend et postgresql.
Il suffit de lancer, la première fois, la commande suivante :

```bash
docker compose up --build
```

Docker se charge de télécharger tous les composants (au premier lancement) et de construire les trois containers (~5 min en tout).
Le site est ensuite accessible dans un navigateur à l'adresse localhost:3000


En cas de changement important dans le backend, le frontend ou bien la base de données, on peut relancer les 3 serveurs avec ces deux commandes
```bash
docker compose down
docker compose up --build
```

## Licence

AGPL-3.0
