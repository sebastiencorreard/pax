target=clongueur1 clongueur2 clongueur3 clongueur4 clongueur5

\language{fr}
\range{-5..5}
#include "author.inc"
#include "lang_titles.inc"
#include "lang.inc"
\computeanswer{no}
\format{html}
\precision{100}

\text{lettres=randrow(A,B,C
T,R,I
S,V,T
R,S,T
E,F,G)}
\text{lettres=shuffle(\lettres)}
\text{A=item(1,\lettres)}
\text{B=item(2,\lettres)}
\text{C=item(3,\lettres)}

#if defined TARGET_clongueur1
 \text{quest=\A\B}
 \integer{r1=randint(5..15)}
 \integer{a1=randint(30..70)}
 \text{don=<li>\B\C = \r1 cm</li><li>\(\widehat{\A\B\C} = \a1^\circ)</li>}
 \text{rep=\r1*cos(\a1*pi/180)}
 #include "triangle1.inc"
#endif
#if defined TARGET_clongueur2
 \text{quest=\B\C}
 \integer{r1=randint(5..15)}
 \integer{a1=randint(30..70)}
 \text{don=<li>\A\B = \r1 cm</li><li>\(\widehat{\A\B\C} = \a1^\circ)</li>}
 \text{rep=\r1/cos(\a1*pi/180)}
 #include "triangle2.inc"
#endif
#if defined TARGET_clongueur3
 \integer{ch=randint(1..2)}
 \if{\ch=1}{
  \text{quest=\A\B}
  \integer{r1=randint(5..15)}
  \integer{a1=randint(30..70)}
  \text{don=<li>\B\C = \r1 cm</li><li>\(\widehat{\A\B\C} = \a1^\circ)</li>}
  \text{rep=\r1*cos(\a1*pi/180)}
}{
  \text{quest=\B\C}
  \integer{r1=randint(5..15)}
  \integer{a1=randint(30..70)}
  \text{don=<li>\A\B = \r1 cm</li><li>\(\widehat{\A\B\C} = \a1^\circ)</li>}
  \text{rep=\r1/cos(\a1*pi/180)}
}
#endif
#if defined TARGET_clongueur4
 \text{quest=\A\C}
 \integer{r1=randint(5..15)}
 \integer{a1=randint(30..70)}
 \text{don=<li>\B\C = \r1 cm</li><li>\(\widehat{\A\B\C} = \a1^\circ)</li>}
 \text{rep=\r1*sin(\a1*pi/180)}
 #include "triangle2.inc"
#endif
#if defined TARGET_clongueur5
 \text{quest=\B\C}
 \integer{r1=randint(5..15)}
 \integer{a1=randint(30..70)}
 \text{don=<li>\A\C = \r1 cm</li><li>\(\widehat{\A\B\C} = \a1^\circ)</li>}
 \text{rep=\r1/sin(\a1*pi/180)}
 #include "triangle1.inc"
#endif

\integer{ch=randint(0..2)}
\text{arr=item(\ch+1,\name_precision)}
\real{rep=rint((\rep)*10^\ch)/10^\ch}
\if{\dessin!=}{
 \text{image=draw(240,140
\dessin)}
}
\statement{
\if{\dessin!=}{<div class="wims_columns">
 <div class="medium_size img_col"><img src="\image" alt=""></div>
  <div class="medium_size text_col">}
\A\B\C \name_enonce \A.
<ul>\don</ul>
\name_question[1] [\quest] \name_question[2] \arr.
<div class="spacer">
<b>\name_answer</b>:
<label for="reply1">\(\quest \simeq \)</label> \embed{r1,5} cm.
</div>
\if{\dessin!=}{</div></div>}
}

\answer{\quest}{\rep}{type=numexp}
