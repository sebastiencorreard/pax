target=vocabulaire1 vocabulaire2 vocabulaire3 vocabulaire4
\language{fr}
\range{-5..5}
#include "author.inc"
#include "lang_titles.inc"
#include "lang.inc"
\computeanswer{no}
\format{html}
\precision{100}

\text{size=80x30x1}
\text{lettres=randrow(A,B,C
T,R,I
S,V,T
R,S,T
E,F,G)}
\text{lettres=shuffle(\lettres)}
\text{A=item(1,\lettres)}
\text{B=item(2,\lettres)}
\text{C=item(3,\lettres)}

#if defined TARGET_vocabulaire1
 \text{quest=\name_question}
 \text{rep=\([\B\C])}
 \integer{ch=randint(1..2)}
 \if{\ch=1}{
  #include "triangle1.inc"
 }{
  #include "triangle2.inc"
 }
#endif
#if defined TARGET_vocabulaire2
 \text{quest=\name_question \(\widehat{\A\B\C})}
 \text{rep=\([\A\B])}
 \integer{ch=randint(1..2)}
 \if{\ch=1}{
  #include "triangle1.inc"
 }{
  #include "triangle2.inc"
 }
#endif
#if defined TARGET_vocabulaire3
 \text{quest=\name_question}
 \text{rep=\([\B\C])}
 \text{dessin=}
#endif
#if defined TARGET_vocabulaire4
 \text{quest=\name_question \(\widehat{\A\B\C})}
 \text{rep=\([\A\B])}
 \text{dessin=}
#endif

\text{list=\([\B\C]),\([\A\C]),\([\A\B])}
\if{\dessin!=}{\text{image=draw(240,140
\dessin)}}

\statement{
\if{\dessin!=}{
<div class="wims_columns">
 <div class="medium_size img_col"><img src="\image" alt=""></div>
 <div class="medium_size text_col">
}
  \A\B\C \name_enonc \A.
  <p>\quest ?</p>

<b>Votre réponse</b> : \embed{r1,\size}
\if{\dessin!=}{ </div></div>}
}

\answer{Réponse}{\rep;\list}{type=dragfill}
