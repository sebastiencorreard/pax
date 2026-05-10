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


## Licence

AGPL-3.0
