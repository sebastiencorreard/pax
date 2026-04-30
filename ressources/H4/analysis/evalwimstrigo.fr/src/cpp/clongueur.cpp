target=clongueur1,clongueur2,clongueur3,clongueur4,clongueur5,clongueur6

\language{fr}
\range{-5..5}
#include "author.inc"
\computeanswer{no}
\format{html}
\precision{100}
#define TITRE Calcul de longueur

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
 \title{TITRE 1}
 \text{quest=\A\C}
 \integer{r1=randint(5..15)}
 \integer{a1=randint(30..70)}
 \text{don=<li>\B\C = \r1 cm</li><li>\(\widehat{\A\B\C} = \a1^\circ)</li>}
 \text{rep=\r1*sin(\a1*pi/180)}
 #include "triangle1.inc"
#endif

#if defined TARGET_clongueur2
 \title{TITRE 2}
 \text{quest=\A\B}
 \integer{r1=randint(5..15)}
 \integer{a1=randint(30..70)}
 \text{don=<li>\B\C = \r1 cm</li><li>\(\widehat{\A\B\C} = \a1^\circ)</li>}
 \text{rep=\r1*cos(\a1*pi/180)}
 #include "triangle1.inc"
#endif

#if defined TARGET_clongueur3
 \title{TITRE 3}
 \text{quest=\A\B}
 \integer{r1=randint(5..15)}
 \integer{a1=randint(30..70)}
 \text{don=<li>\A\C = \r1 cm</li><li>\(\widehat{\A\B\C} = \a1^\circ)</li>}
 \text{rep=\r1/tan(\a1*pi/180)}
 #include "triangle1.inc"
#endif

#if defined TARGET_clongueur4
 \title{TITRE 4}
 \text{quest=\B\C}
 \integer{r1=randint(5..15)}
 \integer{a1=randint(30..70)}
 \text{don=<li>\A\C = \r1 cm</li><li>\(\widehat{\A\B\C} = \a1^\circ)</li>}
 \text{rep=\r1/sin(\a1*pi/180)}
 #include "triangle2.inc"
#endif

#if defined TARGET_clongueur5
 \title{TITRE 5}
 \text{quest=\B\C}
 \integer{r1=randint(5..15)}
 \integer{a1=randint(30..70)}
 \text{don=<li>\A\B = \r1 cm</li><li>\(\widehat{\A\B\C} = \a1^\circ)</li>}
 \text{rep=\r1/cos(\a1*pi/180)}
 #include "triangle2.inc"
#endif

#if defined TARGET_clongueur6
 \title{TITRE 6}
 \text{quest=\A\C}
 \integer{r1=randint(5..15)}
 \integer{a1=randint(30..70)}
 \text{don=<li>\A\B = \r1 cm</li><li>\(\widehat{\A\B\C} = \a1^\circ)</li>}
 \text{rep=\r1*tan(\a1*pi/180)}
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
  Calculer la longueur du segment [\quest] arrondie \arr.
<div class="wimscenter">
 <img src="\image" alt="">
 </div>
<b>Votre réponse :</b><br>
<label for="reply1">\(\quest \simeq)</label> \embed{r1,5} cm.}

\answer{\quest}{\rep}{type=numexp}
