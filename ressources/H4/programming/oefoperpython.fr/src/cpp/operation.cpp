target=add sous mult div addorsous multordiv reste divreste mgg
\text{code=
\#Initialisation des variables#
\
\
\
\#Boucle#
\
\
\
\
\#Fin Boucle#
\#Affichage du résultat#
\
\
\#Fin Affichage#}

\integer{nbtheme=(\confparm1==)?1:\confparm1}
\matrix{theme=ambiance,neat;rubyblue,eclipse;the-matrix,3024-day}
\text{enonce=À l'aide des différentes instructions, réaliser le programme suivant écrit en langage Python.}
\text{consigne=Placer le curseur de la souris dans la zone du programme et cliquer sur les
 différentes instructions sous forme de boutons. Le dernier bouton permet l'indentation du
 texte si nécessaire.
 <br>N'oublier pas de cliquer sur "jouer le code" avant de valider.
 On ne peut pas effacer ligne par ligne, mais on peut tout ré-initialiser...}

\integer{alea=randint(1..2)}

#if defined TARGET_add || defined TARGET_sous || defined TARGET_mult || defined TARGET_addorsous ||defined TARGET_mgg

\text{rr=le résultat}

\text{dl=2,3,5}
\integer{d=randitem(\dl)}

\integer{a=(\alea==1)?\d*randint(100..200):\d*randint(100..200)+1}
\integer{b=(\alea==1)?\d*randint(100..200)+1:\d*randint(100..200)}
#endif

#define FIN de 2 nombres

#if defined TARGET_add
\title{Addition FIN}
#include "add.inc"
#endif

#if defined TARGET_sous
\title{Soustraction FIN}
#include "sous.inc"
#endif

#if defined TARGET_addorsous
\title{Addition ou Soustraction FIN}
#include "addorsous.inc"
#endif

#if defined TARGET_mult
\title{Multiplication FIN}
#include "mult.inc"
#endif

#if defined TARGET_div
\title{Quotient de la Division euclidienne FIN}
\integer{alea1=1}
#include "divres.inc"
#endif

#if defined TARGET_reste
\title{Reste de la Division euclidienne FIN}
\integer{alea1=2}
#include "divres.inc"
#endif

#if defined TARGET_divreste
\title{Division euclidienne FIN}
\integer{alea1=randint(1..2)}
#include "divres.inc"
#endif

#if defined TARGET_multordiv
\title{Multiplication ou division FIN}
\integer{a=(\alea==1)?randint(400..1000):randint(100..200)}
\integer{b=(\alea==1)?randint(100..200):randint(400..1000)}
#include "multordiv.inc"
#endif

\text{prob=Maîtriser la construction des \pr[1]}
\text{instruction=Écrire un script qui permet d'afficher \rr de la \pr[2].
 On attend la valeur entière du résultat de l'opération : \(\pr[3]\).}

#if defined TARGET_mgg
#include "mgg.inc"
#endif



#include "prog.inc"
