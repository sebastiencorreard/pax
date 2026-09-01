# Static assets (images, gifs)

Les exercices référencent deux familles d'images :
- **Icônes partagées WIMS** : `gifs/domains/general/calculator_not.svg`, `course.svg`, etc.
- **Images de module** : `$imagedir/../q502_e2.png` (propres à un module exercice)

PAX les sert via un endpoint statique unique au lieu de les inliner.

## Endpoint `/api/static`

Mount FastAPI dans `backend/main.py` :

```python
from fastapi.staticfiles import StaticFiles

_RESSOURCES_DIR = os.path.normpath(
    os.path.join(os.path.dirname(__file__), "..", "ressources")
)
if os.path.isdir(_RESSOURCES_DIR):
    app.mount("/api/static", StaticFiles(directory=_RESSOURCES_DIR), name="static")
```

- **Public** (pas d'auth) : le contenu du corpus n'est pas sensible
- **Path traversal bloqué** par FastAPI's `StaticFiles` (les `../` sont résolus avant la lookup)
- **Cache navigateur naturel** (304 Not Modified)

URL résolue : `/api/static/<chemin relatif à ressources/>`.

Exemples :
- `ressources/gifs/calculator_not.svg` → `/api/static/gifs/calculator_not.svg`
- `ressources/H3/algebra/oefqcm3.fr/images/q502_e2.png` → `/api/static/H3/algebra/oefqcm3.fr/images/q502_e2.png`

## Convention `$imagedir`

Les exercices WIMS référencent les images partagées d'un module via le pattern `$imagedir/../<file>`. PAX utilise une sentinelle :

```python
# DefEngine.__init__
self.ctx["imagedir"] = "pax-img:_"
```

Le `_` est un placeholder qui se fait avaler par le `..` suivant. Donc `$imagedir/../<file>` se substitue en `pax-img:_/../<file>` qui se normalise en `pax-img:<file>` lors du post-render.

### Post-render : `inline_pax_images`

Dans `backend/core/oef/flydraw.py` :

```python
_PAX_IMG_RE = re.compile(
    r'<img([^>]*?)\ssrc="pax-img:(?P<path>[^"]+)"([^>]*?)>',
    re.IGNORECASE,
)

def inline_pax_images(html: str, module_dir: str) -> str:
    """Rewrite pax-img:… URLs to point at the /api/static mount."""
    images_dir = os.path.join(module_dir, "images")
    if not os.path.isdir(images_dir):
        return html

    def repl(m):
        raw_path = m.group("path")
        norm = posixpath.normpath("/" + raw_path).lstrip("/")
        filename = posixpath.basename(norm)
        file_path = os.path.join(images_dir, filename)
        if not os.path.isfile(file_path):
            return m.group(0)  # leave unchanged
        rel = os.path.relpath(file_path, _RESSOURCES_ROOT).replace(os.sep, "/")
        return f'<img{m.group(1)} src="/api/static/{rel}"{m.group(3)}>'

    return _PAX_IMG_RE.sub(repl, html)
```

Appelée par `DefEngine.render()` après les autres post-processings, avec `module_dir = dirname(dirname(def_path))`.

### `inline_wims_gifs`

Pour les icônes partagées dans `ressources/gifs/` :

```python
_WIMS_GIF_IMG_RE = re.compile(
    r'<img([^>]*?)\ssrc="gifs/domains/[^/"]+/(?P<file>[^"]+)"([^>]*?)>',
)
```

Les exercices WIMS écrivent `<img src="gifs/domains/general/calculator_not.svg">`. PAX réécrit en `<img src="/api/static/gifs/calculator_not.svg">` (en aplatissant la hiérarchie `domains/general/` que PAX n'utilise pas).

## Frontend : préfixe `apiBase`

Le backend émet des URLs **relatives** (`/api/static/...`). Comme le frontend Nuxt tourne sur le port 3000 et le backend sur 8001, les `<img src>` doivent pointer explicitement vers le backend.

Dans `frontend/composables/useExerciseLogic.ts` :

```typescript
const apiBase = useRuntimeConfig().public.apiBase

function prefixStaticUrls(html: string): string {
  return html.replaceAll(' src="/api/static/', ` src="${apiBase}/api/static/`)
}

// Appliqué à chaque segment HTML lors de buildSegments :
out.push({ type: 'html', content: prefixStaticUrls(await renderMath(s.content ?? '')) })
```

Le navigateur fetche les images directement depuis le backend, sans passer par le `apiFetch` (donc sans bearer token — l'endpoint est public).

## Ajouter une nouvelle image de module

1. La déposer dans `ressources/<level>/<domain>/<module>.<lang>/images/<file>`
2. Dans le `.def` : `<img src="$imagedir/../<file>">` (ou plus souvent, déjà présent dans le `.def` source WIMS)
3. C'est tout — pas d'enregistrement, pas de rebuild

Formats supportés : tout ce que le navigateur sait afficher (PNG, JPG, SVG, GIF, WEBP, …). PAX ne fait rien de spécial sur l'extension côté backend (`StaticFiles` envoie juste l'octet brut avec le bon `Content-Type`).

## Choix : pourquoi pas du base64 inline ?

Une version précédente inlinait les SVG bruts et les images raster en base64. Abandonné parce que :

| | base64 inline | endpoint `/api/static` |
|---|---|---|
| Taille HTML | × 4/3 par image | inchangée |
| Cache navigateur | ❌ re-téléchargé à chaque rendu | ✅ 304 Not Modified |
| Réutilisation entre étapes | ❌ dupliquée | ✅ une seule fois |
| Clic droit / ouvrir dans onglet | ❌ | ✅ |
| Setup | rien | un mount FastAPI |

Pour une image de 80 KB (PNG typique), le base64 ajoute ~107 KB au HTML à chaque rendu. Sur une course de 9 étapes, ça fait ~1 MB transféré inutilement.

## Couleurs des figures et thème sombre

Les figures des exercices sont des SVG produits par flydraw, avec des couleurs
**explicites** : l'auteur écrit `text black,…` ou `arrow …,#EE0700`. Sur le fond
clair pour lequel elles ont été dessinées, elles se lisent ; sur le fond sombre
du thème, un tracé noir disparaît — c'est ainsi que le « sommet marqué par une
croix » d'`oefpolynet/31` était invisible.

**L'ajustement est côté client, et il ne peut pas être ailleurs.** Le rendu d'un
exercice est mis en cache (Redis) et partagé entre des utilisateurs qui n'ont
pas le même thème : la figure servie ne peut porter le choix d'aucun d'eux.

| Pièce | Rôle |
|---|---|
| `utils/figureColors.ts` | la transformation, pure et testable seule |
| `utils/figureTheme.ts` | la passe DOM, réversible |
| `plugins/figures.client.ts` | la directive `v-figures` et l'observateur de thème |

`v-figures` est posée sur `ExercisePlayer` et `ExerciseDetail`. Elle installe un
`MutationObserver` sur son sous-arbre — un `v-html` remplace tout son contenu
sans prévenir la directive — et un second sur la classe `dark` de `<html>`, par
où `useTheme` signale une bascule.

### Ce que la transformation préserve

La couleur **porte du sens** dans un exercice — « le vecteur rouge », « colorier
en bleu ». On ne touche donc ni la teinte ni la saturation : seule la clarté
monte, et seulement jusqu'à franchir le seuil de contraste AA (4,5) contre le
fond. `#00008b` devient `#7777ff` : toujours bleu, enfin lisible. Une couleur
qui passe déjà le seuil n'est **pas touchée** — c'est le cas le plus fréquent.

Les gris suivent une autre règle, et c'est le point à ne pas manquer : ils se
renversent **ensemble, ou pas du tout**. Les traiter un par un selon leur
contraste serait une faute — le blanc a 17 de contraste sur fond sombre, il
« se lit », mais le conserver pendant qu'on éclaircit les traits noirs les
rendrait invisibles *sur lui*. La question n'est donc pas « ce gris se lit-il ? »
mais « le papier a-t-il changé de camp ? ».

La couleur d'origine est mise de côté dans `data-pax-<propriété>` avant d'être
remplacée : un retour au thème clair rend la figure exactement telle que le
moteur l'a produite, ce que vérifie `e2e/figure-theme.spec.ts`.

### Ce qui n'est pas touché

Les overlays que PAX dessine lui-même — les croix de `DrawAnswer` et de
`CoordPlane` (`class="pax-*-mark"`) — sont déjà écrits en couleurs de thème.
Et tout ce qui n'est pas une couleur littérale (`none`, `currentColor`,
`url(#…)`, `var(…)`) est laissé tel quel.

## Limites connues

- **L'auth est nulle**. Si un futur besoin de protéger l'accès (par classe, par rôle), remplacer le `StaticFiles` par une route FastAPI avec auth + lecture fichier manuelle.
- **Pas de hot-reload SVG**. Si un fichier SVG est modifié sur disque, le navigateur peut servir une version cachée (busting via query string si besoin).
- **Pas de support pour les images servies par WIMS lui-même**. Les exercices qui référenceraient `https://wims.unice.fr/wims/gifs/...` ne sont pas réécrits — le navigateur tenterait une requête HTTP externe.
- **L'adaptation au thème ne vaut que pour les SVG.** Une image matricielle (PNG, GIF) garde ses couleurs : on ne sait pas y distinguer un trait d'un aplat. Les photos et schémas scannés des modules restent donc tels quels, ce qui est le bon comportement pour une photo et discutable pour un schéma au trait.
