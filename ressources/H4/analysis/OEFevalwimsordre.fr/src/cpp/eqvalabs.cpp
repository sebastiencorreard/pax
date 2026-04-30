target=eqvalabs1 eqvalabs2 eqvalabs3 eqvalabs4 eqvalabs5
\language{fr}
\range{-5..5}
#include "author.inc"
\computeanswer{no}
\format{html}
\precision{100}
#define TITRE Équation avec valeur absolue
\integer{ord=randint(1,2)}
%%%% Choix des coefficients ##
\integer{a=random(1..10)*random(1,-1)}
\integer{b=\a+random(1..3)*random(1,-1)}
\integer{c=random(1..10)*random(1,-1)}
\integer{d=random(1..10)*random(1,1,1,1,-1)}
\integer{e=random(1..10)*random(1,-1)}
\integer{f=random(1..10)*random(1,-1)}

%%%% borne pour le rayon ##
\integer{rayonmax=20}
%%%% borne pour le centre ##
\integer{centremax=10}

%%%% Choix des bornes ##
\integer{sing1=random(1..\centremax)*randint(1,-1)}
\integer{sing2=random(1..\rayonmax)}


#if defined TARGET_eqvalabs1
 \title{TITRE I}
%%%% Choix de l'hypothèse
\text{eqx=\(abs(texmath(x-(\sing1))) = \sing2) }
\text{eqs1=texmath(x-(\sing1))}

%%%% calcul de la bonne réponse ###
\integer{v1=\sing2+(\sing1)}
\integer{v2=-(\sing2)+(\sing1)}
\integer{rep2=\v2<\v1?\v1:\v2}
\integer{rep1=\v2<\v1?\v2:\v1}
\text{goodrep=\rep1,\rep2}
#endif

#if defined TARGET_eqvalabs2
 \title{TITRE II}
\integer{a=randint(1,-1)}
\integer{b=randint(1,-1)}
%%%% Choix de l'hypothèse
\text{eqx=\ord=1?\(abs(texmath(\a*x-(\c))) = \d):\(abs(texmath(-(\c)+\a*x)) = \d) }
\text{eqs1=texmath(\a*x-(\c))}
\integer{oppc=-(\c)}
%%%% calcul de la bonne réponse ###
\if{\d<0}{
 \text{goodrep=vide}
}{
  \if{\d=0}{
    \rational{v1=\c / (\a)}
    \text{goodrep=\v1}
  }{
    \integer{n1=\d + (\c)}
    \integer{d1=\a}
    \rational{v1= \n1 /(\d1)}

    \integer{n2=\c - (\d)}
    \integer{d2=\a }
    \rational{v2= \n2 /(\d2)}
    \rational{rep1=\v1<\v2?\v1:\v2}
    \rational{rep2=\v1<\v2?\v2:\v1}
    \text{goodrep=\rep1,\rep2}
  }
}
#endif

#if defined TARGET_eqvalabs3
 \title{TITRE III}
%%%% Choix de l'hypothèse
\text{eqx=\(abs(texmath(x-(\c))) = abs(texmath(x-(\d)))\) }
\text{eqs1=texmath(x-(\c))}
\text{eqs2=texmath(x-(\d))}
\text{eqs3=texmath(-x+(\d))}

%%%% calcul de la bonne réponse ###

\integer{n2=\c + (\d)}
\rational{v2= \n2 /2}
\rational{rep1=\v2}
\text{goodrep=\rep1}
#endif

#if defined TARGET_eqvalabs4
 \title{TITRE IV}
\integer{a=randint(1,-1)}
\integer{b=randint(1,-1)}
%%%% Choix de l'hypothèse
\text{eqx=\ord=1?\(abs(texmath(\a * x-(\c))) = abs(texmath(\b * x-(\d)))) :\(abs(texmath(-(\c)+ \a *x)) = abs(texmath(\b * x-(\d)))) }
\text{eqs1=texmath(\a * x-(\c))}
\text{eqs2=texmath(\b * x-(\d))}
\text{eqs3=texmath(-(\b) * x+(\d))}

%%%% calcul de la bonne réponse ###
\text{goodrep=}
\integer{n1=\c - (\d)}
\integer{d1=\a - (\b)}
\if{\d1<>0}{
  \rational{v1= \n1 /(\d1)}
  \text{goodrep=wims(append item \v1 to \goodrep)}
}
\integer{n2=\c + (\d)}
\integer{d2=\a + (\b)}
\if{\d2<>0}{
  \rational{v2= \n2 /(\d2)}
  \text{goodrep=wims(append item \v2 to \goodrep)}
}
\text{goodrep=wims(listuniq \goodrep)}
#endif

#if defined TARGET_eqvalabs5
\title{TITRE V}
\integer{a=randint(1,-1)}
\integer{b=randint(1,-1)}
%%%% Choix de l'hypothèse
\text{eqx=\(\e*abs(texmath(\a * x-(\c))) = \f*abs(texmath(\b * x-(\d)))\)}
\text{eqs1=texmath(\a * x-(\c))}
\text{eqs2=texmath(\b * x-(\d))}
\text{eqs3=texmath(-(\b) * x+(\d))}

%%%% calcul de la bonne réponse ###
\real{g=\f / (\e)}
\integer{p1=\a*(\c)-(\b)*(\d)}
\rational{s1=(\a*(\c)+(\b)*(\d))/2}
\if{\g<0}
  {\if{\p1 !=0}
    {\text{goodrep=vide}}
    {\text{goodrep=\s1}}
  }
  {\if{\g=1}
    {\if{\p1=0}
      {\text{goodrep=inf}}
      {\text{goodrep=\s1}}
    }
    {\if{\p1=0}
      {\text{goodrep=\s1}}
      {\rational{v1=(\e*(\c)-(\f)*(\d))/(\e*(\a)-(\f)*(\b))}
       \rational{v2=(\e*(\c)+(\f)*(\d))/(\e*(\a)+(\f)*(\b))}
       \text{goodrep=\v1,\v2}
       \text{goodrep=wims(listuniq \goodrep)}
      }
    }
  }

#endif

\statement{
  Déterminer l'ensemble S des solutions dans \(\mathbb{R}\) de l'équation suivante d'inconnue <span class="nowrap">\(x\) :</span>
  <div class="wimscenter">\eqx</div>

<div class="wimscenter"> <label for="reply1">S= </label>\embed{reply1,10}
</div>
<div class="wims_instruction"> S'il y a plusieurs solutions, les séparer par une virgule.
S'il y a une infinité de solutions, taper <span class="tt">inf</span>.
S'il n'y a pas de solution, taper <span class="tt">vide</span>.</div>
}
\answer{}{\goodrep}{type=fset}

#if defined TARGET_eqvalabs1
\solution{
\eqx équivaut à \(\mathrm{d}(x ,\sing1) = \sing2\)<br>
ce qui équivaut à \(x = \sing1 - \sing2\) ou \(x = \sing1 +\sing2\)<br>
ce qui équivaut encore à \(x = \goodrep[1]\) ou \(x = \goodrep[2]\)
}
#endif
#if defined TARGET_eqvalabs2
\solution{

\eqx équivaut à
\if{\a=1}{\(\mathrm{d}(x ,\c) = \d\)}{\(\mathrm{d}(x ,\oppc) = \d\)}
<br>
\if{\d<0}
  {Une distance étant une grandeur positive, cette équation n'a pas de solution.}
  {\if{d=0}
    {ce qui équivaut à \(x =\goodrep[1]\)}
    {\if{\a=1}
      {ce qui équivaut à \(x = \c - \d\) ou \(x = \c +\d\)<br>
       ce qui équivaut encore à \(x = \goodrep[1]\) ou \(x = \goodrep[2]\)
      }
      {ce qui équivaut à \(x = \oppc - \d\) ou \(x = \oppc +\d\)<br>
       ce qui équivaut encore à \(x = \goodrep[1]\) ou \(x = \goodrep[2]\)
      }
    }
  }
}
#endif
