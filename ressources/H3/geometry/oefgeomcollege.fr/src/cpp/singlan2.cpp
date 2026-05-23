target=singlan2

\author{Gaëlle, Singlan}
\email{gaelle.singlan@orange.fr}
#include "author.inc"
#include "lang_singlan2.inc"

\title{TITLE}
\title_en{TITLE_en}

\computeanswer{no}
\range{-5..5}
\precision{10000}

\text{l=A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P,K,R,S,T,U,V,W,X,Y,Z}
\text{L=shuffle(\l)}
\integer{a=randint(2..10)}
\integer{b=randint(2..10)}
\integer{s=\a+\b}
\integer{m=max(\a,\b)}
\text{z=randitem(1,2)}
\if{\z=1}{
  \integer{c=randint((\s+1)..25)}
  \text{rep=\name_rep[2]}
 }{
  \integer{c=randint(\m..(\s-1))}
  \text{rep=\name_rep[1]}
  \text{C=
    fcircle (1+\a+(\a^2-\b^2+\c^2)/(2*\c))*20,(1+\m-sqrt(\a^2-((\a^2-\b^2+\c^2)/(2*\c))^2))*20,red
    text red,(1+\a+(\a^2-\b^2+\c^2)/(2*\c))*20,(0.5+\m-sqrt(\a^2-((\a^2-\b^2+\c^2)/(2*\c))^2))*20,medium,\L[3]
    segment (1+\a)*20,(1+\m)*20,(1+\a+(\a^2-\b^2+\c^2)/(2*\c))*20,(1+\m-sqrt(\a^2-((\a^2-\b^2+\c^2)/(2*\c))^2))*20,red
    segment (1+\a+\c)*20,(1+\m)*20,(1+\a+(\a^2-\b^2+\c^2)/(2*\c))*20,(1+\m-sqrt(\a^2-((\a^2-\b^2+\c^2)/(2*\c))^2))*20,red}
}

\text{dessin=draw((2+\a+\b+\c)*20,(2+2*\m)*20
fcircle (1+\a)*20,(1+\m)*20,5,blue
text blue,(0.5+\a)*20,(1+\m)*20,medium,\L[1]
fcircle (1+\a+\c)*20,(1+\m)*20,5,blue
text blue,(1.5+\a+\c)*20,(1+\m)*20,medium,\L[2]
segment (1+\a)*20,(1+\m)*20,(1+\a+\c)*20,(1+\m)*20,blue
circle (1+\a)*20,(1+\m)*20,\a*40,black
circle (1+\a+\c)*20,(1+\m)*20,\b*40,black
\C
)}

\text{liste=shuffle(texmath(\L[1]\L[2]=\a cm),texmath(\L[2]\L[3]=\b cm),texmath(\L[3]\L[1]=\c cm))}

\statement{
\name_instruction[1;] :
<ul> <li> \liste[1] cm </li>
     <li> \liste[2] cm </li>
     <li> \liste[3] cm </li>
</ul>
 \name_instruction[2;] \embed{r1,20x20} cm.
<br>\name_instruction[3;] \embed{r2,20x20} cm.
<br>\name_instruction[4;] \L[1]\L[2]\L[3] \embed{c1,20x50} \name_instruction[5;].
}

\answer{}{\c}{type=numexp}
\answer{}{\s}{type=numexp}
\choice{}{\rep}{\name_rep[1],\name_rep[2]}

\solution{\name_instruction[6;] :
<div class="wimscenter"><img src="\dessin" alt=""></div>}
