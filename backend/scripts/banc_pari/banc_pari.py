r"""Banc PARI : `gp` sous l'interface de WIMS (`src/Interfaces/pari.c`).

L'arbitre de l'émulation PARI (`def_engine/cas.py`, `pari_prog.py`), comme
`banc_rawmath.c` l'est de `rawmath`. `entete.gp` reprend l'en-tête que
`pari.c` envoie à `gp` (alias, `i=I`, `e=exp(1)`…), chaque ligne rendue muette,
puis `\p 20`, la précision par défaut de WIMS.

    docker build -t pax-banc-pari backend/scripts/banc_pari
    echo '["divrem(7,2)~[2]", "digits(215,10)"]' | \
      docker run --rm -i -v "$PWD/backend/scripts/banc_pari:/banc" \
      pax-banc-pari python3 /banc/banc_pari.py

Limite : chaque expression tourne dans son propre `gp`, là où WIMS garde un
processus par exercice — une expression qui lit l'état d'un `!exec pari`
antérieur n'y a pas de sens.

Entrée : JSON, liste d'expressions. Sortie : JSON, liste des sorties telles
que `!exec pari` les rendrait (`output()` + `strip_zeros`), ou None si gp
échoue ou dépasse le délai.
"""
import json, subprocess, sys

ENTETE = open("/banc/entete.gp").read()
PRECISION = 20


def strip_zeros(p: str) -> str:
    s = list(p); i = 0
    while i < len(s):
        if not s[i].isdigit():
            i += 1; continue
        a = i; point = False; j = i
        while j < len(s) and (s[j].isdigit() or s[j] == "."):
            if s[j] == ".": point = True
            j += 1
        if not point:
            i = j; continue
        p2 = j
        while p2 > a and s[p2 - 1] == "0": p2 -= 1
        ee = j
        while ee < len(s) and s[ee].isspace(): ee += 1
        if a + 1 < len(s) and s[a + 1] == "." and ee + 1 < len(s) and s[ee] in "Ee" and s[ee + 1] == "-":
            k = 0; pt = ee + 2
            while pt < len(s) and s[pt].isdigit():
                k = k * 10 + int(s[pt]); pt += 1
            if PRECISION > 8 and (k > PRECISION * 2 or (k > PRECISION and s[a] == "0")):
                s[a:pt] = list("0.0"); i = a + 3; continue
        if s[p2 - 1] == "." and p2 < j: p2 += 1
        if p2 < j:
            del s[p2:j]; j = p2
        i = j
    return "".join(s)


def fermant(p: str, debut: int, c: str) -> int:
    prof = {"(": 0, "[": 0, "{": 0}; k = debut
    ouv = {")": "(", "]": "[", "}": "{"}
    while k < len(p):
        ch = p[k]
        if ch in prof: prof[ch] += 1
        elif ch in ouv:
            if prof[ouv[ch]] == 0: return k if ch == c else -1
            prof[ouv[ch]] -= 1
        k += 1
    return -1


def ligne(p: str) -> str:
    p = p.strip()
    for tete in ("Mat(", "Vecsmall("):
        if p.startswith(tete) and p.endswith(")") and fermant(p, len(tete), ")") == len(p) - 1:
            p = p[len(tete):-1]
    if p.startswith("[") and p.endswith("]") and fermant(p, 1, "]") == len(p) - 1:
        p = p[1:-1]
    return strip_zeros(p)


def evaluer(expr: str):
    commande = expr.replace("_", "K")
    try:
        r = subprocess.run(["gp", "-f", "-q"], input=ENTETE + commande + "\n",
                           capture_output=True, text=True, timeout=10)
    except subprocess.TimeoutExpired:
        return None
    if r.stderr.strip() and not r.stdout.strip():
        return None
    return "\n".join(ligne(l) for l in r.stdout.splitlines() if l.strip())


print(json.dumps([evaluer(e) for e in json.load(sys.stdin)]))
