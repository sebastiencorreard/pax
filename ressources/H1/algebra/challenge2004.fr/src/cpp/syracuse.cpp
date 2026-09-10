target=syracuse1 syracuse2 syracuse3 syracuse4

#include "header.inc"
#define TIT Syracuse

#if defined TARGET_syracuse1
# define LVL 1
 \integer{min=50}
#endif

#if defined TARGET_syracuse2
# define LVL 2
 \integer{min=100}
#endif

#if defined TARGET_syracuse3
# define LVL 3
 \integer{min=200}
#endif

#if defined TARGET_syracuse4
# define LVL 4
 \integer{min=500}
#endif

\title{TIT LVL}
\integer{level=LVL}

\integer{max=\min*2}

\integer{n0=randint(\min..\max)}
\integer{n=\n0}
\for{i=1 to \level}{
 \integer{n=\n%2=0?\n/2:\n*3+1}
}

\statement{Le jeu de Syracuse consiste à partir d'un entier quelconque. S'il
  est pair, on le divise par 2 ; s'il est impair, on le multiplie par 3 et on
  ajoute 1. Puis on recommence avec le nouvel entier obtenu, ainsi de suite.
<p>
  Trouve un entier du départ \(n), entre \min et \max (inclus), qui donne \n après
\level étapes.
</p>
}

\answer{\(n)}{\nn0}{type=number}

\integer{diag=0}
\if{\nn0>=\min and \nn0<=\max}{
 \integer{diag=1}
 \integer{nn=\nn0}
 \for{i=1 to \level}{\integer{nn=\nn%2=0?\nn/2:\nn*3+1}}
 \integer{diag=\nn=\n?2}
}

\condition{Votre nombre donne \n après \level étapes}{\diag>1}

\feedback{\diag=0}{\nn0 n'est pas inclus entre \min et \max !
  Réponse invalide.}

\feedback{\diag=1}{
 Au bout de \level étapes de Syracuse à partir de \nn0, j'obtiens \nn au
 lieu de \n. Désolé mais ce n'est pas bon.
}
