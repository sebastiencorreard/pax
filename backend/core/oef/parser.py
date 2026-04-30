"""
Parseur de fichiers .oef.
Extrait les directives OEF sous forme de liste ordonnée de (nom, contenu).
"""
from dataclasses import dataclass


@dataclass
class Directive:
    name: str     # integer, text, real, statement, answer, title, ...
    content: str  # contenu brut entre les accolades extérieures


def parse(source: str) -> list[Directive]:
    """
    Lit un fichier .oef et retourne la liste ordonnée des directives.
    Stratégie : on cherche les \nom{ et on extrait le bloc {...} correspondant.
    """
    source = source.replace('\r\n', '\n').replace('\r', '\n')
    directives = []
    pos = 0
    n = len(source)

    while pos < n:
        # Cherche le prochain antislash
        bs = source.find('\\', pos)
        if bs == -1:
            break

        # Vérifie que ce n'est pas dans un commentaire (ligne commençant par %)
        line_start = source.rfind('\n', 0, bs) + 1
        line_prefix = source[line_start:bs].strip()
        if line_prefix.startswith('%'):
            pos = source.find('\n', bs)
            if pos == -1:
                break
            continue

        pos = bs + 1

        # Lit le nom de la directive (lettres et chiffres)
        name_start = pos
        while pos < n and (source[pos].isalpha() or source[pos].isdigit()):
            pos += 1
        name = source[name_start:pos].lower()

        if not name:
            continue

        # Saute les espaces/tabs entre le nom et {
        while pos < n and source[pos] in ' \t':
            pos += 1

        if pos >= n:
            break

        if source[pos] == '{':
            # Extrait le bloc {...} en gérant les accolades imbriquées
            block_start = pos
            content = _extract_braces(source, block_start)
            pos = block_start + len(content)
            # Retire les accolades extérieures
            inner = content[1:-1]
            directives.append(Directive(name=name, content=inner))
        elif source[pos] == '\n' or pos == n:
            # Directive sans contenu, on ignore
            pass
        else:
            # Valeur jusqu'à fin de ligne (ex: \language fr)
            val_start = pos
            while pos < n and source[pos] != '\n':
                pos += 1
            directives.append(Directive(name=name, content=source[val_start:pos].strip()))

    return directives


def _extract_braces(source: str, start: int) -> str:
    """
    Extrait le contenu d'un bloc {...} en gérant les accolades imbriquées.
    Retourne la chaîne incluant les accolades extérieures.
    """
    assert source[start] == '{', f"Expected '{{' at pos {start}, got {source[start]!r}"
    depth = 0
    pos = start
    n = len(source)
    while pos < n:
        ch = source[pos]
        if ch == '{':
            depth += 1
        elif ch == '}':
            depth -= 1
            if depth == 0:
                return source[start:pos + 1]
        pos += 1
    # Accolade non fermée — on retourne ce qu'on a
    return source[start:]
