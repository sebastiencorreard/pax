target=eqdtepar1 eqdtepar2 eqdtepar3 eqdtepar4 eqdtepar5
#include "author.inc"
\keywords{line_equation}
#define TITRE Droite de direction donnée
#if defined TARGET_eqdtepar1
\title{TITRE I}
\integer{a=random(1..9)*randint(1,-1)}
\integer{b=random(1..9)*randint(1,-1)}
\integer{c=\b+random(1..9)*randint(1,-1)}
\integer{b=\b=\a?-1*\b}
\integer{xA=0}
\integer{yA=\b}
\text{rep=y=\a*x+\b}
\text{eqdte=\(texmath(y=\a*x+\c))}
#endif
#if defined TARGET_eqdtepar2
\title{TITRE II}
\integer{a=random(1..9)*randint(1,-1)}
\integer{b=random(1..9)*randint(1,-1)}
\integer{c=\b+random(1..9)*randint(1,-1)}
\integer{b=\b=\a?-1*\b}
\integer{xA=1}
\integer{yA=\a+(\b)}
\text{rep=y=\a*x+\b}
\text{eqdte=\(texmath(y=\a*x+\c))}
#endif

#if (defined TARGET_eqdtepar3  || defined TARGET_eqdtepar5 )
#if defined TARGET_eqdtepar5
\title{TITRE V}
\integer{k=3}
#else
\title{TITRE III}
\integer{k=randint(1..4)}
#endif


\integer{a=\k=1?0:random(1..9)*randint(1,-1)}
\integer{b=\k=2?0:random(0..9)*randint(1,-1)}
\integer{c=\b+random(1..9)*randint(1,-1)}
\integer{xA=random(0..9)*randint(1,-1)}
\integer{yA=\a*(\xA)+(\b)}
\integer{ux=random(1..9)*randint(1,-1)}
\integer{uy=\a*\ux}
\if{\k=4}
  {
  \text{rep=x=\b}
  \text{eqdte=\(texmath(x=\c))}
  \integer{xA=\b}
  \integer{ux=0}
  }
  {
   \if{\a=0}
    {
    \text{rep=y=\b}
    \text{eqdte=\(texmath(y=\c))}
    \text{uy=0}
    }
    {
    \if{\b=0}
     {
      \text{rep=y=\a*x}
     }
     {
      \text{rep=y=\a*x+\b}
     }
     \text{eqdte=\(texmath(y=\a*x+\c))}

    }
  }
#if defined TARGET_eqdtepar5
    \rational{xI=-\b / \a}
    \integer{yI=0}
    \integer{xJ=0}
    \integer{yJ=\b}
#endif
#endif

#if defined TARGET_eqdtepar4
\title{TITRE IV}
\integer{k=randint(1..4)}

\integer{a=\k=1?0:random(1..9)*randint(1,-1)}
\integer{b=\k=2?0:random(0..9)*randint(1,-1)}
\integer{c=\b+random(1..9)*randint(1,-1)}
\integer{da=random(2,3,4,5,7)}
\integer{db=random(2,3,4,5,7)}
\rational{a=\a / \da}
\rational{b=\b / \db}
\integer{xA=random(0..9)*randint(1,-1)}
\rational{yA=\a*(\xA)+(\b)}
\integer{ux=random(1..9)*randint(1,-1)}
\rational{uy=\a*\ux}
\if{\k=4}
  {
  \text{rep=x=\b}
  \rational{xA=\b}
  \integer{ux=0}
  \text{eqdte=\(texmath(x=\c))}
  }
  {
   \if{\a=0}
    {
    \text{rep=y=\b}
    \text{uy=0}
    \text{eqdte=\(texmath(y=\c))}
    }
    {
    \if{\b=0}
     {
      \text{rep=y=\a*x}
     }
     {
      \text{rep=y=\a*x+\b}
     }
     \text{eqdte=\(texmath(y=\a*x+\c))}
    }
  }
#endif


\statement{
  Déterminer une équation de la droite \((D))
  passant par le point \(A(\xA,\yA))
 et parallèle à la droite \(\Delta) d'équation \eqdte.
 <div class="wimscenter">
  Équation de \((D)):\embed{reply1}</div>
#if defined TARGET_eqdtepar5
  Déterminer les coordonnées du point d'intersection \(I\) de \((D)) avec l'axe \((Ox)).
<ul><li>
Abscisse de \(I\) = \embed{reply2,4}
</li><li>
Ordonnée de \(I\) =\embed{reply3,4}
</li></ul>
<p>
  Déterminer les coordonnées du point d'intersection \(J\) de \((D)) avec l'axe \((Oy)).
</p>
<ul><li>
Abscisse de \(J\) = \embed{reply4,4}
</li><li>
Ordonnée de \(J\) = \embed{reply5,4}
</li></ul>
#endif
}
\answer{Équation de \((D))}{\rep}{type=equation}
#if defined TARGET_eqdtepar5
\answer{xI}{\xI}{type=numeric}
\answer{yI}{\yI}{type=numeric}
\answer{xJ}{\xJ}{type=numeric}
\answer{yJ}{\yJ}{type=numeric}
#endif
