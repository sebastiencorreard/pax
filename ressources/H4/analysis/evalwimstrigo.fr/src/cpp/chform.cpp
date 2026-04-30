target=chform1,chform2,chform3,chform4,chform5,chform6

\language{fr}
\range{-5..5}
#include "author.inc"
\computeanswer{no}
\format{html}
\precision{100}
#define TITRE Choix de formule
\text{lettres=randrow(A,B,C
T,R,I
S,V,T
R,S,T
E,F,G)}
\text{lettres=shuffle(\lettres)}
\text{A=item(1,\lettres)}
\text{B=item(2,\lettres)}
\text{C=item(3,\lettres)}

#if defined TARGET_chform1
 \title{TITRE 1}
 \text{quest=\A\C}
 \integer{r1=randint(5..15)}
 \integer{a1=randint(30..70)}
 \text{don=<li>\B\C = \r1 cm</li><li>\(\widehat{\A\B\C} = \a1^\circ)</li>}
 \text{rep=1}
 #include "triangle1.inc"
#endif

#if defined TARGET_chform2
 \title{TITRE 2}
 \text{quest=\A\B}
 \integer{r1=randint(5..15)}
 \integer{a1=randint(30..70)}
 \text{don=<li>\B\C = \r1 cm</li><li>\(\widehat{\A\B\C} = \a1^\circ)</li>}
 \text{rep=2}
 #include "triangle1.inc"
#endif

#if defined TARGET_chform3
 \title{TITRE 3}
 \text{quest=\A\B}
 \integer{r1=randint(5..15)}
 \integer{a1=randint(30..70)}
 \text{don=<li>\A\C = \r1 cm</li><li>\(\widehat{\A\B\C} = \a1^\circ)</li>}
 \text{rep=3}
 #include "triangle1.inc"
#endif

#if defined TARGET_chform4
 \title{TITRE 4}
 \text{quest=la mesure de l'angle \(\widehat{\A\B\C})}
 \text{r2=randint(2..8)}
 \text{r1=randint(9..15)}
 \text{don=<li>\B\C = \r1 cm</li><li>\A\C = \r2 cm</li>}
 \text{rep=1}
 #include "triangle2.inc"
#endif

#if defined TARGET_chform5
 \title{TITRE 5}
 \text{quest=la mesure de l'angle \(\widehat{\A\B\C})}
 \text{r2=randint(2..8)}
 \text{r1=randint(9..15)}
 \text{don=<li>\B\C = \r1 cm</li><li>\A\B = \r2 cm</li>}
 \text{rep=2}
 #include "triangle2.inc"
#endif

#if defined TARGET_chform6
 \title{TITRE 6}
 \text{quest=la mesure de l'angle \(\widehat{\A\B\C})}
 \text{r=wims(values v for v=5 to 15)}
 \text{r=shuffle(\r)}
 \text{don=<li>\A\B = \r[1] cm</li><li>\A\C = \r[2] cm</li>}
 \text{rep=3}
 #include "triangle2.inc"
#endif

\text{list=Le sinus,Le cosinus,La tangente}
\text{rep=item(\rep,\list)}
\text{image=draw(240,140
\dessin)}

\statement{
 \A\B\C est un triangle rectangle en \A.
<ul>\don</ul>
<div class="wimscenter">
 <img src="\image" alt="">
</div>
  Quelle fonction trigonométrique faut-il utiliser pour déterminer directement \quest ?
\embed{r1,120x40}
}

\answer{Réponse}{\rep|\list}{type=dragfill}
