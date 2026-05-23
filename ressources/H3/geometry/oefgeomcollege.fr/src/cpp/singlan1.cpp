target=singlan1

\author{Gaëlle, Singlan}
\email{gaelle.singlan@orange.fr}
#include "author.inc"
\computeanswer{no}
\range{-5..5}
\precision{10000}

#include "lang_singlan1.inc"
\title{TITLE}
\title_en{TITLE_en}

\text{l=A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P,K,R,S,T,U,V,W,X,Y,Z}
\text{L=shuffle(\l)}
\integer{angle1=randint(10..80)}
\text{n=randitem(1,2)}
\if{\n=1}{
  \integer{angle2=randint(10..80)}
  \integer{angle3=180-\angle1-\angle2}
  \text{rep=\name_rep[1]}
 }{
  \integer{angle2=randint(10..80)}
  \integer{angle3=randint((170-\angle1-\angle2)..(190-\angle1-\angle2))}
  \integer{angle3= \angle3=180-\angle1-\angle2? \angle3+2}
  \text{rep=\name_rep[2]}
}
\text{a=shuffle(\angle1,\angle2,\angle3)}
\integer{s=\angle1 + \angle2 + \angle3}

\statement{\name_instruction[1;] :
<ul>
  <li> \(\widehat{\L[1]\L[2]\L[3]} = \a[1]) ° </li>
  <li> \(\widehat{\L[2]\L[3]\L[1]} = \a[2]) ° </li>
  <li> \(\widehat{\L[3]\L[1]\L[2]} = \a[3]) ° </li>
</ul>
<br> \name_instruction[2;] :
<br> \(\widehat{\L[1]\L[2]\L[3]} + \widehat{\L[2]\L[3]\L[1]} + \widehat{\L[3]\L[1]\L[2]} =) \embed{r1,20x10}
<br> \name_instruction[3;] \L[1]\L[2]\L[3] \embed{c1,20x20} \name_instruction[4;].
}

\answer{}{\s}{type=numexp}
\choice{}{\rep}{\name_rep[1],\name_rep[2]}{options=shuffle}
