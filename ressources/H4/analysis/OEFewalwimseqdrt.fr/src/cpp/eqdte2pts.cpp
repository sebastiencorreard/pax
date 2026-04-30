target=eqdte2pts1 eqdte2pts2 eqdte2pts3 eqdte2pts4 eqdte2pts5
#include "author.inc"
\keywords{line_equation}
#define TITRE Droite passant par 2 points
#if defined TARGET_eqdte2pts1
\title{TITRE I}
\integer{a=random(1..9)*randint(1,-1)}
\integer{b=random(1..9)*randint(1,-1)}
\integer{b=\b=\a?-1*\b}
\integer{xA=0}
\integer{yA=\b}
\integer{xB=1}
\integer{yB=\a+(\b)}
\text{rep=y=\a*x+\b}
#endif
#if defined TARGET_eqdte2pts2
\title{TITRE II}
\integer{a=random(1..9)*randint(1,-1)}
\integer{b=random(1..9)*randint(1,-1)}
\integer{b=\b=\a?-1*\b}
\integer{xA=0}
\integer{yA=\b}
\integer{xB=random(1..9)*randint(1,-1)}
\integer{yB=\a*(\xB)+(\b)}
\text{rep=y=\a*x+\b}
#endif


#if (defined TARGET_eqdte2pts3  || defined TARGET_eqdte2pts5 )
#if defined TARGET_eqdte2pts5
\title{TITRE V}
#else
\title{TITRE III}
#endif
\integer{k=randint(1..4)}

\integer{a=\k=1?0:random(1..9)*randint(1,-1)}
\integer{b=\k=2?0:random(0..9)*randint(1,-1)}
\text{xcl=wims(makelist x,-x for x=1 to 9)}
\text{xcl=shuffle(\xcl)}
\integer{xA=\xcl[1]}
\integer{yA=\a*(\xA)+(\b)}
\integer{xB=\xcl[2]}
\integer{yB=\a*(\xB)+(\b)}
\if{\k=4}
  {
  \text{rep=x=\b}
  \integer{xA=\b}
  \integer{xB=\b}
  }
  {
   \if{\a=0}
    {
    \text{rep=y=\b}
    }
    {
    \if{\b=0}
     {
      \text{rep=y=\a*x}
     }
     {
      \text{rep=y=\a*x+\b}
     }
    }
  }
#if defined TARGET_eqdte2pts5
\integer{k2=\a=0?1:randint(1,2)}
\integer{k2=\k=4?2}
\integer{xC=\k=4?\xA:\xcl[3]}
\integer{yC=\a*(\xC)+(\b)}
\if{\k2=1}
  {
  \text{quest2=Déterminer l'ordonnée du point \(C) de cette droite d'abscisse \(x=\xC).}
  \text{titrep2=Ordonnée de \(C)}
  \integer{rep2=\yC}
  }
  {
  \text{quest2=Déterminer l'abscisse du point \(C) de cette droite d'ordonnée \(y=\yC).}
  \text{titrep2=Abscisse de \(C)}
  \integer{rep2=\xC}
  }
#endif
#endif

#if defined TARGET_eqdte2pts4
\title{TITRE IV}
\integer{k=randint(1..4)}

\integer{a=\k=1?0:random(1..9)*randint(1,-1)}
\integer{b=\k=2?0:random(0..9)*randint(1,-1)}
\integer{da=random(2,3,4,5,7)}
\integer{db=random(2,3,4,5,7)}
\rational{a=\a / \da}
\rational{b=\b / \db}
\integer{xA=random(0..9)*randint(1,-1)}
\rational{yA=\a*(\xA)+(\b)}
\integer{xB=random(0..9)*randint(1,-1)}
\integer{xB=\xB=\xA?\xB+3}
\rational{yB=\a*(\xB)+(\b)}
\if{\k=4}
  {
  \text{rep=x=\b}
  \rational{xA=\b}
  \rational{xB=\b}
  }
  {
   \if{\a=0}
    {
    \text{rep=y=\b}
    }{
    \if{\b=0}
     {
      \text{rep=y=\a*x}
     }{
      \text{rep=y=\a*x+\b}
     }
    }
  }
#endif


\statement{
  Déterminer une équation de la droite \((D)) passant par les points A(\xA,\yA) et B(\xB,\yB).
<div class="wimscenter">Équation de \((D)) : \embed{reply1}</div>
#if defined TARGET_eqdte2pts5
<p>
\quest2</p>
<div class="wimscenter">\titrep2 = \embed{reply2,4}</div>
#endif
}
\answer{Équation de \((D))}{\rep}{type=equation}
#if defined TARGET_eqdte2pts5
\answer{\titrep2}{\rep2}{type=numeric}
#endif
