target=perm2 perm3 perm4 permlist

#include "codeperm.inc"

\matrix{theme=ambiance,neat;3024-night,3024-day}
\text{enonce=À l'aide des différentes instructions, construire le programme suivant écrit en langage Python.}
\text{consigne=Sélectionner les 3 symboles dièses (#)  et cliquer sur les
 différentes instructions sous forme de boutons. \consignepl
<br>N'oublier pas de cliquer sur "jouer le code" avant de valider.}

\integer{alea=randint(1..2)}
\text{dl=2,3,5}
\integer{d=randitem(\dl)}
\integer{a=(\alea==1)?\d*randint(100..200):\d*randint(100..200)+1}
\integer{b=(\alea==1)?\d*randint(100..200)+1:\d*randint(100..200)}

#if defined TARGET_perm2
#include "perm2.inc"
#endif

#if defined TARGET_perm3
#include "perm3.inc"
#endif

#if defined TARGET_perm4
#include "perm4.inc"
#endif

#if defined TARGET_permlist
#include "permlist.inc"
#endif

#include "prog.inc"
