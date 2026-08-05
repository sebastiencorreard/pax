"""Primitive WIMS `imgrename` — port fidèle de `calc_imgrename` (calc.c).

`imgrename(CHEMIN ATTRIBUTS)` construit une balise `<img>` : le premier mot est
le chemin de l'image, tout ce qui suit jusqu'à la parenthèse fermante est
recopié tel quel dans les attributs de la balise.

    imgrename($imagedir/ch4o.png width=150)
    → <img src="pax-img:_/ch4o.png" width=150 alt="">

**Ce que devient `calc_rename`.** Le C fait passer le chemin par `calc_rename`,
qui pose un lien symbolique dans le répertoire de session et rend une URL
`getfile/rename-<alea>` — un moyen de servir un fichier sans exposer son chemin.
PAX n'en a pas besoin : `$imagedir` vaut la sentinelle `pax-img:_`, et
`flydraw.inline_pax_images` réécrit en post-rendu tout `<img src="pax-img:…">`
vers le montage `/api/static`. Le chemin est donc recopié intact ; c'est la
passe `pax-img:` qui tient le rôle de `calc_rename`.
"""

from __future__ import annotations

import re

from .wims_lists import find_matching, find_word_end, find_word_start

# `varchr` cherche le nom en position de *variable* : ni précédé ni suivi d'un
# caractère de nom. Sans cette garde, un `myimgrename(` serait capturé.
_IMGRENAME_RE = re.compile(r"(?<![A-Za-z0-9_])imgrename(?![A-Za-z0-9_])")


def calc_imgrename(text: str) -> str:
    """Développe chaque `imgrename(…)` de `text` en une balise `<img>`.

    Port de `calc_imgrename` (`calc.c`), y compris ses reprises : un nom non
    suivi de `(`, ou une parenthèse jamais refermée, laisse le texte intact et
    la recherche repart après — le C ne renonce pas au reste de la chaîne.

    Un appel sans blanc avant la fermante (`imgrename(a.png)`) rend
    `<img src="a.png)" …>` : le C prélève le chemin par `find_word_end`, qui
    ne s'arrête qu'à un blanc, et copie donc la parenthèse avec. C'est un
    travers de l'original, reproduit tel quel — les 19 `.def` du corpus
    écrivent toujours un attribut ou un espace avant la fermante.
    """
    if "imgrename" not in text:
        return text

    out = text
    pos = 0
    while True:
        m = _IMGRENAME_RE.search(out, pos)
        if not m:
            return out
        start = m.start()
        open_paren = find_word_start(out, m.end())
        if open_paren >= len(out) or out[open_paren] != "(":
            # Pas un appel : on repart d'après le nom, comme `p1=p2`.
            pos = open_paren if open_paren > pos else m.end()
            continue
        close = find_matching(out, open_paren + 1, ")")
        if close < 0:
            # Parenthèse pendante : `p1=p2-1`, la recherche reprend au `(`.
            pos = open_paren
            continue
        path_start = find_word_start(out, open_paren + 1)
        path_end = find_word_end(out, path_start)
        path = out[path_start:path_end]
        # `p4` : de la fin du chemin jusqu'à la fermante — blanc de séparation
        # compris, recopié tel quel entre le `src` et le `alt`.
        attrs = out[path_end:close]
        tag = f'<img src="{path}"{attrs} alt="">'
        out = out[:start] + tag + out[close + 1 :]
        pos = start + len(tag)
