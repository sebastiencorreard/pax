r"""Banc Maxima : le vrai `maxima` sous l'interface de WIMS (`src/Interfaces/maxima.c`).

L'arbitre de l'émulation Maxima (`def_engine/cas.py:_call_maxima`), comme
`banc_pari` l'est de PARI. Maxima 5.47.0 sur GCL, la version de WIMS 4.32.

    docker build -t pax-banc-maxima backend/scripts/banc_maxima
    echo '["expand((x+1)^2)", "integrate(x^2,x)"]' | \
      docker run --rm -i -v "$PWD/backend/scripts/banc_maxima:/banc" \
      pax-banc-maxima python3 /banc/banc_maxima.py

Ce qui est repris de WIMS, et d'où :

- **l'entrée** (`common.c:putheader`, `putparm` ; `maxima.c:dynsetup`,
  `check_parm`) : `fpprec:20;`, l'en-tête (`display2d:false`, `keepfloat`,
  alias `ln`, `ch`, `arctan`…), puis la commande — `_` changé en `K`, `?` en
  blanc, **tout en minuscules**, un `;` ajouté s'il manque, les noms interdits
  brouillés (`find_illegal`) — encadrée de deux chaînes repères ;
- **la sortie** (`common.c:readresult`, `maxima.c:output`) : ce qui suit la
  dernière chaîne de départ, jusqu'à la chaîne de fin ; une ligne par sortie
  `(%oN)`, une ligne vide pour une entrée sans sortie ; `\n` et `%` changés en
  blancs, minuscules, crochets englobants ôtés, flottants longs `1.5b-3` →
  `1.5E-3`.

Limite : chaque expression tourne dans son propre `maxima`. WIMS peut garder
un processus pour plusieurs appels (`multiexec`) ; une expression qui lit
l'état d'un appel antérieur n'a pas de sens ici. Le hasard (`random`) ne se
compare pas non plus.

Entrée : JSON, liste d'expressions. Sortie : JSON, liste des sorties telles
que `!exec maxima` les rendrait, ou None si Maxima échoue ou dépasse le délai.
"""
import json
import re
import subprocess
import sys
from concurrent.futures import ThreadPoolExecutor

# `maxima.c:header`, précédé de ce que `dynsetup` pose (`fpprec`, défaut 20).
ENTETE = """fpprec:20;

display2d:false;
letrat:true;
keepfloat:true;
rombergmin:5;
rombergtol:1.E-6;
rombergit:13;
simpsum:true;
triginverses:true; logabs:true;
e:%e;pi:%pi;Pi:%pi;PI:%pi;I:%i;i:%i;
ln:log;sh:sinh;ch:cosh;th:tanh;
arctan:atan;arcsin:asin;arccos:acos;
tg:tan;arctg:atan;
argsh:asinh;argch:acosh;argth:atanh;
Argsh:asinh;Argch:acosh;Argth:atanh;
cotan:cot;ctg:cot;
log10(x):=block([],return(log(x)/log(10)));
log2(x):=block([],return(log(x)/log(2)));
lg(x):=log10(x);
sgn:sign;
nolabels:true; kill(labels);
"""
DEBUT = "Start line maxima 1 2 3 4"
FIN = "End line maxima 1 2 3 4"

ILLEGAL = ["system", "describe", "example", "save", "fassave", "stringout", "batcon",
           "batcount", "cursordisp", "direc", "readonly", "with_stdout", "pscom",
           "demo", "ttyintfun", "bug"]
ILLPART = ["file", "debug", "plot", "load", "store", "batch"]


def find_illegal(p: str) -> str:
    """`common.c:find_illegal`, après la mise en minuscules de `check_parm`."""
    s = list("".join(" " if (c < " " and c not in "\n\t") or ord(c) >= 127 else c for c in p))

    def brouiller(i):
        s[i + 1] = "J" if s[i + 1] not in "jJ" else "Z"

    for pe in ILLPART:
        i = "".join(s).find(pe)
        while i >= 0:
            # `!isupper(pe[0])` est toujours vrai ici : tout est en minuscules.
            brouiller(i)
            i = "".join(s).find(pe, i + 1)
    for pe in ILLEGAL:
        i = "".join(s).find(pe)
        while i >= 0:
            t = "".join(s)
            avant = i == 0 or not t[i - 1].isalnum()
            apres = i + len(pe) >= len(t) or not t[i + len(pe)].isalnum()
            if avant and apres:
                brouiller(i)
            i = "".join(s).find(pe, i + 1)
    return "".join(s)


def check_parm(pm: str) -> str:
    """`maxima.c:check_parm`."""
    pm = pm.replace("_", "K").replace("?", " ").lower().rstrip()
    if pm and not pm.endswith(";"):
        pm += ";"
    return find_illegal(pm)


def fermant(p: str, debut: int, c: str) -> int:
    """`common.c:find_matching2` : l'indice du fermant, ou -1."""
    paren = brak = brace = 0
    k = debut
    while k < len(p):
        ch = p[k]
        if ch == "[": brak += 1
        elif ch == "]": brak -= 1
        elif ch == "(": paren += 1
        elif ch == ")": paren -= 1
        elif ch == "{": brace += 1
        elif ch == "}": brace -= 1
        else:
            k += 1
            continue
        if paren < 0 or brak < 0 or brace < 0:
            if ch != c or paren > 0 or brak > 0 or brace > 0:
                return -1
            return k
        k += 1
    return -1


_PROMPT = re.compile(r"\n\((?:%([io])|([CD]))(\d*)\)")


def output(p: str) -> list[str]:
    """`maxima.c:output` : une ligne par entrée `(%iN)`, vide si rien n'en sort."""
    invites = [(("C" if (m.group(1) or m.group(2)) in "iC" else "D"), m.start(), m.end())
               for m in _PROMPT.finditer(p)]
    entrees = [i for i in invites if i[0] == "C"]
    lignes = []
    for k, (_, debut, _) in enumerate(entrees):
        suivante = entrees[k + 1][1] if k + 1 < len(entrees) else None
        sortie = next((i for i in invites if i[0] == "D" and i[1] > debut), None)
        if sortie is None:
            break
        if suivante is not None and sortie[2] > suivante:
            lignes.append("")
            continue
        corps = p[sortie[2]:suivante] if suivante is not None else p[sortie[2]:]
        corps = "".join(" " if c in "\n%" else c.lower() for c in corps).strip()
        if corps.startswith("[") and corps.endswith("]") and fermant(corps, 1, "]") == len(corps) - 1:
            corps = corps[1:-1]
        # `1.5b-3` → `1.5E-3`, `2.0b0` → `2.0` : le `b` d'un flottant long.
        c = list(corps)
        i = 0
        while i < len(c):
            if c[i] == "b" and i > 0 and c[i - 1].isdigit() and i + 1 < len(c) \
                    and (c[i + 1] == "-" or c[i + 1].isdigit()):
                if c[i + 1] == "0" and (i + 2 >= len(c) or not c[i + 2].isdigit()):
                    del c[i:i + 2]
                    continue
                c[i] = "E"
            i += 1
        lignes.append("".join(c))
    return lignes


def evaluer(expr: str):
    entree = (ENTETE + f'"{DEBUT}";\n' + check_parm(expr) + "\n" + f'"{FIN}";\n' + "\nquit();\n")
    try:
        r = subprocess.run(["maxima"], input=entree, capture_output=True, text=True, timeout=20)
    except subprocess.TimeoutExpired:
        return None
    sortie = r.stdout
    i = sortie.find(DEBUT)
    if i < 0:
        return None
    p = sortie[i + len(DEBUT):]
    j = p.find(FIN)
    if j < 0:
        return None
    # La chaîne de fin s'affiche sur sa propre ligne d'invite : on coupe au
    # saut de ligne qui la précède (`readresult`, 64 caractères au plus).
    k = p.rfind("\n", max(0, j - 64), j)
    p = p[:k] if k >= 0 else p[:j]
    while DEBUT in p:
        p = p[p.find(DEBUT) + len(DEBUT):]
    return "\n".join(output(p))


if __name__ == "__main__":
    exprs = json.load(sys.stdin)
    with ThreadPoolExecutor(8) as pool:
        print(json.dumps(list(pool.map(evaluer, exprs)), ensure_ascii=False))
