target=mesure1,mesure2,mesure3

\language{fr}
\range{-5..5}
#include "author.inc"
\computeanswer{no}
\format{html}
\precision{100}

#define TITRE Mesure d'un angle
\text{lettres=randrow(A,B,C
T,R,I
S,V,T
R,S,T
E,F,G)}
\text{lettres=shuffle(\lettres)}
\text{A=item(1,\lettres)}
\text{B=item(2,\lettres)}
\text{C=item(3,\lettres)}

#if defined TARGET_mesure1
 \title{TITRE 1}
 \integer{r1=randint(5..10)}
 \integer{r2=randint(11..20)}
 \text{don=<li>\B\C = \r2 cm</li><li> \A\C = \r1 cm</li>}
 \text{rep=180/pi*arcsin(\r1/\r2)}
 #include "triangle1.inc"
#endif

#if defined TARGET_mesure2
 \title{TITRE 2}
 \integer{r1=randint(5..10)}
 \integer{r2=randint(11..20)}
 \text{don=<li>\B\C = \r2 cm</li><li> \A\B = \r1 cm</li>}
 \text{rep=180/pi*arccos(\r1/\r2)}
 #include "triangle1.inc"
#endif

#if defined TARGET_mesure3
 \title{TITRE 3}
 \integer{r1=randint(5..15)}
 \integer{r2=randint(5..15)}
 \text{don=<li>\A\B = \r2 cm</li><li> \A\C = \r1 cm</li>}
 \text{rep=180/pi*arctan(\r1/\r2)}
 #include "triangle2.inc"
#endif

\integer{ch=randint(0..2)}
\text{arr=item(\ch+1,à l'unité,au dixième,au centième)}
\real{rep=rint((\rep)*10^\ch)/10^\ch}

\text{image=draw(240,140
\dessin)}

\statement{
 \A\B\C est un triangle rectangle en \A.
<ul>\don</ul>
  Calculer la mesure de l'angle \(\widehat{\A\B\C}) arrondie \arr.
<div class="wimscenter">
 <img src="\image" alt="">
</div>
<b>Votre réponse :</b><br>
<label for="reply1">\(\widehat{\A\B\C} \simeq)</label> \embed{r1,5}°.}

\answer{\(\widehat{\A\B\C})}{\rep}{type=numexp}
