"""Boutons qui complètent un champ de réponse — l'idiome `appendToInput`.

`slib/chemistry/chemeq_components` écrit, pour chaque espèce d'une équation,
un bouton qui ajoute son écriture au champ de réponse :

    <input type="button" value="H2O" onclick="appendToInput(1,' H2O ')">

et son aide demande à l'exercice de poser le script qui les rend actifs —
`getInput(n)` retrouve le champ `reply<n>`, `appendToInput(n,msg)` y ajoute
`msg` suivi d'une espace. `redox1`, `redox2` et `piles` le recopient à
l'identique.

PAX n'exécute pas ce script ; il le **reconnaît**. Chaque bouton devient un
`<button class="pax-append">` qui porte le champ visé et le texte à ajouter,
et le front fait l'ajout (`BaseExerciseStatement.vue`). Le script disparaît.
Un script qui diffère de celui de la slib, même d'un caractère, laisse
l'énoncé intact : mieux vaut un bouton inerte qu'un bouton qui fait autre
chose que ce que l'auteur a écrit.
"""

from __future__ import annotations

import html as _html
import re

# Le script de l'aide de `chemeq_components`, blancs réduits à une espace.
_SCRIPT_CANONIQUE = (
    'function getInput(n){ f=window.document.forms[0]; '
    'for(i=0; i<f.elements.length; i=i+1){ '
    'if (f.elements[i].name=="reply"+n) { return f.elements[i]; } } '
    "return null; } "
    "function appendToInput(n,msg){ var i=getInput(n); "
    "i.value=i.value+msg+' '; i.focus(); }"
)

_SCRIPT_RE = re.compile(r"<script\b[^>]*>(.*?)</script>", re.S | re.I)
_BOUTON_RE = re.compile(
    r"<input\s+type=\"button\"\s+value=\"([^\"]*)\"\s+"
    r"onclick=\"appendToInput\((\d+),'([^']*)'\)\">"
)


def port_appendinput(html: str) -> str:
    if "appendToInput" not in html:
        return html
    script = next(
        (m for m in _SCRIPT_RE.finditer(html)
         if " ".join(m.group(1).split()) == _SCRIPT_CANONIQUE),
        None,
    )
    if script is None:
        return html
    html = html[:script.start()] + html[script.end():]

    def bouton(m: re.Match) -> str:
        valeur, n, texte = m.group(1), m.group(2), m.group(3)
        # `i.value+msg+' '` : l'espace finale est celle du script.
        ajout = _html.escape(texte + " ", quote=True)
        return (f'<button type="button" class="pax-append" data-reply="reply{n}" '
                f'data-text="{ajout}">{valeur}</button>')

    return _BOUTON_RE.sub(bouton, html)
