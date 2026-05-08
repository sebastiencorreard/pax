# PAX — Progrès en Automatismes par les eXercices

Clone de WIMS, rétro-compatible avec le format OEF / DEF, orienté mathématiques.

## Stack

- **Backend** : Python 3.12 + FastAPI
- **Frontend** : Nuxt.js (Vue 3)
- **Base de données** : PostgreSQL
- **Cache** : Redis
- **Auth** : Keycloak (compatible GAR/ENT)
- **CAS** : SymPy

## Lancer le projet en développement

Tout est dans des containers docker : backend, frontend et postgresql.
Il suffit de lancer, la première fois, la commande suivante :

```bash
docker compose up --build
```

Docker se charge de télécharger tous les composants (au premier lancement) et de construire les trois containers (~5 min en tout).
Le site est ensuite accessible dans un navigateur à l'adresse localhost:3000

### Attention : premier lancement

Il faut peupler les base de données. Pour le moment, à la main :

Table des académies :
docker compose exec backend python scripts/import_academies.py /ressources/a_integrer_dans_db/academies_france.csv

Table des établissements (Aix-Marseille seulement, pour le moment) :
docker compose exec backend python scripts/import_etablissements.py ac-aix-marseille.fr /ressources/a_integrer_dans_db/etablissements_aix_marseille.csv

Tables des utilisateurs :
./create_user.sh --email admin@pax.fr --first-name Jane --last-name Goodall --role admin

## Hot reload

Normalement, tout changement dans le backend, frontend ou la base de données est répercuté "à chaud", càd sans commande particulière.

Si ce "hot reload" ne fonctionne pas bien, on peut toujours relancer les 3 serveurs avec ces deux commandes
```bash
docker compose down
docker compose up --build
```

## Licence

AGPL-3.0
