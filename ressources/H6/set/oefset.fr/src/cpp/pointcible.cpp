target=pointcible
23/1/06 Version avec une etape
9/04/13 correction xhtml
#define GGG D4 -
\title{GGG Positions de points aléatoires}
\description{il s'agit de déterminer si un événement est réalisé ou non. }
\observation{exercice  faisant travailler sur les notations ensemblistes à partir d'un exemple concret d'événement. Suivant la valeur du paramètre "Complexité des ensembles", la question portera sur un, deux ou au moins 3 ensembles. }
\keywords{set_theory,events}
\language{fr}
\format{html}
\author{Sophie, Lemaire}
\email{sophie.lemaire@universite-paris-saclay.fr}
\computeanswer{yes}
\precision{1000}
#include "common.inc"
\integer{ nivex = \confparm1= ? randint(1..3)}
\if{\confparm1=1}{\integer{nivex=1}}
\if{\confparm1=2}{\integer{nivex=2}}
\if{\confparm1>2}{\integer{nivex=3}}
\integer{rayon=50+randint(0..10)*5} rayon de la cible ou demi-cote
\integer{diam=2*\rayon}
\integer{k=random(1,2)} choix du domaine

description de la cible
\if{\k=1}{
  \text{domaine=fcircle 110,110,\diam,antiquewhite}
  \text{domaine=\domaine,
  circle 110,110,\diam,brown}
         text{t0=cercle}
         text{t1= diamètre }
         \real{a1= pi*\rayon*\rayon}
  }{
  \integer{coin=110-\rayon}
  \text{domaine=fsquare \coin,\coin,\diam,antiquewhite}
   \text{domaine=\domaine,
                     square \coin,\coin,\diam,brown}
  text{t0=carré}
  text{t1= côté}
  \real{a1=\diam*\diam }
  }

Nombre de points a tirer
\if{\nivex=1}{\integer{n=1}}
\if{\nivex=2}{\integer{n=2}}
\if{\nivex=3}{\integer{n=randint(3..5)}}

Tirage des points
\integer{ray1=\rayon-4}
\if{\k=1}{\text{U=slib(stat/random 2*\n,0,1,R)}
  \integer{X=10*\ray1*sqrt(item(1,\U))*cos(2*pi*item(2,\U))}
  \integer{Y=10*\ray1*sqrt(item(1,\U))*sin(2*pi*item(2,\U))}
  \real{X=\X/10}
  \real{Y=\Y/10}
  \real{X1=\X+110}
  \real{Y1=110-\Y}
  \text{M=\X,\Y}
  \text{Md=\X1,\Y1}
  \for{i=2 to \n}{
    \integer{X=10*\ray1*sqrt(item(2*\i-1,\U))*cos(2*pi*item(2*\i,\U))}
    \integer{Y=10*\ray1*sqrt(item(2*\i-1,\U))*sin(2*pi*item(2*\i,\U))}
    \real{X=\X/10}
    \real{Y=\Y/10}
    \real{X1=\X+110}
    \real{Y1=110-\Y}
    \text{M=\M,\X,\Y}
    \text{Md=\Md,\X1,\Y1}
  }
}{
  \text{M=slib(stat/random 2*\n, -\ray1,\ray1,Z)}
  \integer{X1=110+item(1,\M)}
  \integer{Y1=110-item(2,\M)}
  \text{Md=\X1,\Y1}
  \for{i=2 to \n}{
    \integer{X1=110+item(2*\i-1,\M)}
    \integer{Y1=110-item(2*\i,\M)}
    \text{Md=\Md,\X1,\Y1}
  }
}
Tableau avec les coordonnées des points :
\text{coord1=M1 (item(1,\M), item(2,\M))}
\text{coord=text navy, 222, 12,medium,\coord1}
\for{i=2 to \n}{
  \text{coord1=M\i (item(2*\i-1,\M), item(2*\i,\M))}
  \text{coord=\coord
  text navy, 222, 12*\i,medium,\coord1}
}

Description de la question
\integer{d=randint(10..(\rayon-5))}
\integer{d0=randint(1..(\d-1))}
\integer{d0r=\d0}
\integer{dr=\d}
\integer{m1=randint(1..4)} choix de l'event
\integer{m3=randint(1,2)} choix
\integer{m4=randint(1,2,3)} choix

#include "lang_pointcible_fr.inc"
\if{\lang=it}{
#include "lang_pointcible_it.inc"
}
\if{\lang=es}{
#include "lang_pointcible_es.inc"
}
\if{\n>2}{
  \text{pointpos=\name_pointbleu[2;]}
  \text{notat=\name_event[1;]}
  \if{\m4=2}{\text{choixevent=\cup_{i=1}^{\n}A_{i}^{c},\cap_{i=1}^{\n}A_{i}^{c},
       \cap_{i=1}^{\n}A_{i},\cup_{i=1}^{\n}A_{i} }}
  {\text{choixevent=\cup_{i=1}^{\n}A_{i},\cap_{i=1}^{\n}A_{i},
  \cap_{i=1}^{\n}A_{i}^{c},\cup_{i=1}^{\n}A_{i}^{c} }}
}{
  \if{\n=1}{
  \text{pointpos=\name_pointbleu[1;]}
  \text{notat=\name_event[2;]}
  \if{\m4=2}{
    \text{choixevent=A^{c}, A^{c}, A, A}}{\text{choixevent=A, A, A^{c}, A^{c}}}
   }{
    \text{pointpos=\name_pointbleu[2;]}
    \text{notat=\name_event[3;]}
    \if{\m4=2}{
      \text{choixevent=A_{1}^{c} \cup A_{2}^{c}, A_{1}^{c} \cap A_{2}^{c}, A_{1} \cap A_{2} ,  A_{1} \cup A_{2} }}
      {\text{choixevent=A_{1} \cup A_{2}, A_{1} \cap A_{2}, A_{1}^{c} \cap A_{2}^{c}, A_{1}^{c} \cup A_{2}^{c}}}
}}
\if{\m3=2}{
  \if{\m4<3}{
    \integer{m4=3-\m4}
    \integer{dr=\rayon-\d}
    \integer{d0r=\rayon-\d0}}{
    \integer{dr=\rayon-\d0}
    \integer{d0r=\rayon-\d}
  }
}
\text{quest1= \(\choixevent[\m1]\)}

Comptage
\integer{s=0}
\integer{s0=0} ne sert que pour le cas m4=3 : compris entre d et d0
\if{\m3=1 or \k=1}{
  \for{i=1 to \n}{
    \real{dist=item(2*\i-1,\M)*item(2*\i-1,\M)+item(2*\i,\M)*item(2*\i,\M)}
    \if{\dist<=\dr^2}{
      \integer{s=\s+1}
      \if{\dist>=\d0r^2}{\integer{s0=\s0+1}}
    }
  }
  \real{p1=pi*\dr*\dr/\a1}
  \if{\s=0}{\text{pos4=0,0,1,1}}
    {
      \if{\s=\n}{\text{pos4=1,1,0,0}}{\text{pos4=1,0,0,1}}
    }
  \if{\m4=3}{
    \real{p1=pi*(\dr*\dr-\d0r*\d0r)/\a1}
    \if{\s0=0}{\text{pos4=0,0,1,1}}{
      \if{\s0=\n}{\text{pos4=1,1,0,0}}{\text{pos4=1,0,0,1}}
    }
  }
}

\if{\m3=2 and \k=2}{
  \for{i=1 to \n}{
    \real{dist=max(abs(item(2*\i-1,\M)),abs(item(2*\i,\M)))}
    \if{\dist<=\dr}{
      \integer{s=\s+1}
      \if{\dist>=\d0r}{\integer{s0=\s0+1}}
    }
  }
  \real{p1=4*\dr*\dr/\a1}
   \if{\s=0}{\text{pos4=0,0,1,1}}{
      \if{\s=\n}{\text{pos4=1,1,0,0}}{\text{pos4=1,0,0,1}}
      }
    \if{\m4=3}{
        \if{\s0=0}{\text{pos4=0,0,1,1}}
           {\if{\s0=\n}{\text{pos4=1,1,0,0}}
               {\text{pos4=1,0,0,1}}
           }
        \real{p1=4*(\dr*\dr-\d0r*\d0r)/\a1}
        }
}
\integer{posrep=1+item(\m1,\pos4)}
 \real{pn2=\p1^(\n)}
\real{pn3=(1-\p1)^(\n)}
\real{pn1=1-\pn3}
\real{pn4=1-\pn2}
 \text{prob=\pn1,\pn2,\pn3,\pn4}
\real{rep=item(\m1,\prob)}
\if{\posrep=1}{\text{sol1=\name_rep[1]}}{\text{sol1=\name_rep[2]}}
\text{axes=arrow 0,110,220,110,10,gray}
\text{axes=\axes
arrow 110,220,110,0,10,gray
text gray, 100,110,,0
}
\for{i=1 to 10}{\text{axes=\axes
segment 110+10*\i, 108, 110+10*\i, 112, gray
segment 110-10*\i, 108, 110-10*\i, 112, gray
segment 108,110+10*\i, 112, 110+10*\i, gray
segment 108,110-10*\i, 112, 110-10*\i, gray}}

Dessin pour le feedback
\if{\k=2 and \m3=2}{
   \text{deszone=square \coin+\d, \coin+\d,\diam-2*\d,green}
   \if{\m4=3}{
        \text{deszone=\deszone
        square \coin+\d0, \coin+\d0,\diam-2*\d0,green
        fill \coin+(\d+\d0)/2, 110, aquamarine}
      }
     {\if{\m4=1}{\text{deszone=\deszone
        fill 110+\rayon-\d/2, 110, aquamarine
        square \coin, \coin,\diam,green}
       }
      {
       \text{deszone=\deszone
        fill 110, 110, aquamarine}
       } }
  }
{
  \if{\m3=2}{\real{df=\rayon-\d}\real{df0=\rayon-\d0}}
  {\real{df=\d}\real{df0=\d0}}
  \text{deszone=circle 110,110,2*\df,green}
  \if{\m4=3}{
             \text{deszone=\deszone
circle 110,110,2*\df0,green
fill 110+(\df+\df0)/2, 110, aquamarine}
}
{\if{(\m4=1 and \m3=1) or (\m4=2 and \m3=2)}{
   \text{deszone=\deszone
fill 110,110,aquamarine}
  }{
   \text{deszone=\deszone
fill 110+(\df+\rayon)/2,110,aquamarine}
    \if{\k=1}{\text{deszone=\deszone
circle 110,110,\diam,green}}{
 \text{deszone=\deszone
 square \coin,\coin,\diam,green}}
  }
 }
}

\text{NB2=wims(record 2 of notations.\lang)}
\steps{reply1}

\statement{
\name_instruction
\notat
<div class="instruction wimscenter" style="font-style:italic;">\choixA[1;] \poss1[\m3] \choixA[2;] \poss2[\m4]
\choixA[3;].</div>
<div class="wimscenter">
\draw{350,230}{
\domaine
segments blue,221,100,241,100,221,99,221,101,231,99,231,101,241,99,241,101
text navy,220,85,medium, 20 mm
\axes
arrow 0,110,220,110,10,gray
arrow 110,220,110,0,10,gray
text gray, 100,110,,0
linewidth 3
points navy, \Md
\coord
}
</div>
\pointpos

<div class="wims_question">
\name_question[1] \quest1 \name_question[2]? \embed{reply1}.
</div>
}

\answer{}{\posrep;\poss}{type=radio}
\answer{La probabilité est}{\rep}{type=numeric}
\integer{posrep2=position(\reply1,\poss)}
\real{err0= \reply2<0 or \reply2>1 ? 1:0}
\real{err1=abs(\reply2-(1-\rep))}
\real{err2=abs(\reply2-\rep)}

\hint{<ul>
<li>\NB2</li>
<li>\name_help1</li>
<li> \name_help2
<div class="wimscenter"> \(d(m,E)\) = \(\inf(d(m,e),\ e\in E)\). </div>
</li>
</ul>}

\feedback{\posrep2!=\posrep}{
<span class="oef_indbad">\name_remark</span>: \comdess \poss1[\m3]
\choixA[2;] \poss2[\m4] \choixA[3;].
<div class="wimscenter">
\draw{350,230}{
\domaine
\deszone
\axes
linewidth 3
points navy, \Md
}</div>
}
