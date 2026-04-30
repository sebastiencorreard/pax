target=eqvectdir1 eqvectdir2 eqvectdir3 eqvectdir4 eqvectdir5
#include "author.inc"
\keywords{line, line_equation, vectors}

#define TITRE Droite de vecteur directeur donné
#if defined TARGET_eqvectdir1
\title{TITRE I}
\integer{a=random(1..9)*randint(1,-1)}
\integer{b=random(1..9)*randint(1,-1)}
\integer{b=\b=\a?-1*\b}
\integer{xA=0}
\integer{yA=\b}
\integer{ux=1}
\integer{uy=\a}
\text{rep=y=\a*x+\b}
#endif
#if defined TARGET_eqvectdir2
\title{TITRE II}
\integer{a=random(1..9)*randint(1,-1)}
\integer{b=random(1..9)*randint(1,-1)}
\integer{b=\b=\a?-1*\b}
\integer{xA=1}
\integer{yA=\a+(\b)}
\integer{ux=1}
\integer{uy=\a}
\text{rep=y=\a*x+\b}
#endif


#if (defined TARGET_eqvectdir3  || defined TARGET_eqvectdir5 )
#if defined TARGET_eqvectdir5
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
\integer{ux=random(1..9)*randint(1,-1)}
\integer{uy=\a*\ux}
\if{\k=4}
  {
  \text{rep=x=\b}
  \integer{xA=\b}
  \integer{ux=0}
  }
  {
   \if{\a=0}
    {
    \text{rep=y=\b}
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
    }
  }
#if defined TARGET_eqvectdir5
\integer{k2=randint(1,2)}
\integer{yB=\a*(\xB)+(\b)}
\if{\k2=1}
  {
## le point appartient
  \integer{rep2=1}
  \integer{xB=\k=4?\xA}
  }
  {
## le point n'appartient pas
  \integer{rep2=2}
  \integer{yB=\yB=0?randint(1..9)*randint(1,-1):randint(-\yB,\yB+randint(1..4)*randint(1,-1))}
  }
#endif
#endif

#if defined TARGET_eqvectdir4
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
\integer{ux=random(1..9)*randint(1,-1)}
\rational{uy=\a*\ux}
\if{\k=4}
  {
  \text{rep=x=\b}
  \rational{xA=\b}
  \integer{ux=0}
  }
  {
   \if{\a=0}
    {
    \text{rep=y=\b}
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
    }
  }
#endif


\statement{
  Déterminer une équation de la droite \(D\) passant par le point \(A(\xA,\yA))
  et de vecteur directeur \(\overrightarrow{u}(\ux,\uy)).
<div class="wimscenter">
  Équation de \(D\) :\embed{reply1}</div>
#if defined TARGET_eqvectdir5
<p>
  Le point \(B(\xB,\yB)) appartient-il à cette droite ?</p>
<div class="wimscenter">\embed{reply2}</div>
#endif
}
\answer{Équation de \((D))}{\rep}{type=equation}
#if defined TARGET_eqvectdir5
\answer{Le point B appartient à \((D))?}{\rep2;Oui,Non}{type=radio}
#endif
