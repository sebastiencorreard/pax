target=formule
#define NUM
#include "lang_titles.inc"
\langage {fr}
\author{Paul,Byache}
\email{paul@byache.web4me.fr}
\langage{html}
\precision{10000}

\text{lettres=randomrow(H,Z,E ;R,T,Y ;P,Q,S ;D,F,G ;H,J,K ;L,M,W ;X,K,V ;M,N,L) }
\text{sommet=item(1,\lettres)}
\text{lettres2=shuffle(item(2,\lettres),item(3,\lettres))}
\text{lettres3=shuffle(\lettres)}

\text {triangle = wims(nospace wims(items2words \lettres))}

\text{ angle=item(1,\lettres) item(1,\lettres2) item(2,\lettres2) }
\text{angle= wims(nospace \angle)}
\real{A1=randint(1000..2000)/100}
\real{A2=randint(1000..2000)/100}
\real{A3=rint(sqrt(\A1^2+\A2^2)*100)/100}
\real{A=rint(arctan(\A2/\A1)*180/pi*100)/100}
\text{cotes=item(1,\lettres) item(1,\lettres2) , \A1, item(1,\lettres)item(2,\lettres2) , \A2 , item(1,\lettres2) item(2,\lettres2) , \A3}
\text{cotesbis=item(1,\lettres2) item(1,\lettres) , \A1, item(2,\lettres2)item(1,\lettres) , \A2 , item(2,\lettres2) item(1,\lettres2) , \A3}
\text{liste=shuffle(3)}
\text{L1=wims(nospace item((item(1,\liste)-1)*2+1,\cotes))}
\text{L1bis=wims(nospace item((item(1,\liste)-1)*2+1,\cotesbis))}
\text{l1=item((item(1,\liste)-1)*2+2,\cotes)}
\text{L2=wims(nospace item((item(2,\liste)-1)*2+1,\cotes))}
\text{L2bis=wims(nospace item((item(2,\liste)-1)*2+1,\cotesbis))}
\text{l2=item((item(2,\liste)-1)*2+2,\cotes)}

\text{choix=le côté adjacent , le côté opposé , l'hypoténuse}

\text{choix2= tangente = côté opposé / côté adjacent , cosinus = côté
  adjacent / hypoténuse , sinus = côté opposé / hypoténuse}

\integer{rep1=item(1,\liste)}
\integer{rep2=item(2,\liste)}
\integer{rep3=item(1,\liste)+item(2,\liste)-2}

\text{ff=tan , cos , sin}
\text{form=item(\rep3,\ff)}

\if{item(1,\liste)=3 or item(2,\liste)=2}{
   \text{rep5=\L2|\L2bis}
   \real{rep6=\l1}
   \text{typ5=case}
   \text{typ6=numeric}
}
\if{item(1,\liste)=2 or item(2,\liste)=3}{
  \real{rep5=\l1}
  \text{rep6=\L2|\L2bis}
  \text{typ6=case}
  \text{typ5=numeric}
}

\steps{reply1, reply2
  reply3
  reply4, reply5, reply6
}

\statement{On considère un triangle
  \(\triangle\) rectangle en \(\sommet\) et tel que
  <div class="wimscenter">
  \(\widehat{\angle}\) = \A ° et \(\L1\) = \l1 cm.</div>
 On cherche à calculer la longueur \(\L2\).
 <ol>
  \if{\step=1}{
  <li value="1">
    Faites un schéma du triangle sur une feuille et complétez :
  <ul><li>
  \(\L1\) = \l1 \(cm\) est \embed{reply1} par rapport à l'angle \(\widehat{\angle}\) ;
  </li><li>
  \(\L2\) est \embed{reply2} par rapport à l'angle \(\widehat{\angle}\).
  </li></ul>
  }
  \if{\step=2} {
    <li value="2">
    Choisissez la formule de trigonométrie à utiliser :
  \embed{reply3}
    </li>}
  \if{\step=3}{
    <li value="3">
    Complétez la formule <strong>en mettant les valeurs
    numériques lorsqu'elles sont connues</strong> :
  <div class="wimscenter">
  \special{mathmlinput [\form( reply4 ^\circ)=\frac{reply5}{reply6}],4
   reply4
   reply5
   reply6}
  </div>
  }
  </li>
  </ol>
}
\real{range=1.1*max(\A1,\A2)}
\text{centre=2*\A1/3,\A2/3}
\text{R1= -\centre[1],-\centre[2]}
\text{R2=\A1 -\centre[1],-\centre[2]}
\text{R3=\A1-\centre[1],\A2-\centre[2]}
\text{range= -\range,\range}
\text{dessin=xrange \range
yrange \range
linewidth 2
triangle \R1,\R2,\R3,green
arc \R1,10,10,0,\A,red
text black, \R1, medium,\lettres2[1]
text black, \R2, medium,\sommet
text black, \R3, medium,\lettres2[2]}
\feedback{1=1}{Lorsqu'on effectue la fin du calcul, on trouve : \(\L2\) = \l2 cm.
  Voici le dessin qui correspondait à l'énoncé :<div class="wimscenter">
  \draw{200,200}{\dessin}</div>}
\answer{}{\rep1;\choix}{type=menu}
\answer{}{\rep2;\choix}{type=menu}
\answer{}{\rep3;\choix2}{type=menu}
\answer{}{\A}{type=numeric}
\answer{}{\rep5}{type=\typ5}
\answer{}{\rep6}{type=\typ6}
