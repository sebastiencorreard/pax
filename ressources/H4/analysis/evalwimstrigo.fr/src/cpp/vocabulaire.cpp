target=vocabulaire1,vocabulaire2,vocabulaire3,vocabulaire4,vocabulaire5,vocabulaire6

#define TITRE Vocabulaire
\language{fr}
\range{-5..5}
#include "author.inc"
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

#if defined TARGET_vocabulaire1
 \title{Vocabulaire 1}
 \text{quest=Quelle est l'hypoténuse de ce triangle}
 \text{rep=\([\B\C])}
 #include "triangle1.inc"
#endif
#if defined TARGET_vocabulaire2
 \title{TITRE 2}
 \text{quest=Quel est le côté opposé à l'angle \(\widehat{\A\B\C})}
 \text{rep=\([\A\C])}
 #include "triangle1.inc"
#endif
#if defined TARGET_vocabulaire3
 \title{TITRE 3}
 \text{quest=Quel est le côté adjacent à l'angle \(\widehat{\A\B\C})}
 \text{rep=\([\A\B])}
 #include "triangle1.inc"
#endif
#if defined TARGET_vocabulaire4
 \title{TITRE 4}
 \text{quest=Quelle est l'hypoténuse de ce triangle}
 \text{rep=\([\B\C])}
 #include "triangle2.inc"
#endif
#if defined TARGET_vocabulaire5
 \title{TITRE 5}
 \text{quest=Quel est le côté opposé à l'angle \(\widehat{\A\B\C})}
 \text{rep=\([\A\C])}
 #include "triangle2.inc"
#endif
#if defined TARGET_vocabulaire6
 \title{TITRE 6}
 \text{quest=Quel est le côté adjacent à l'angle \(\widehat{\A\B\C})}
 \text{rep=\([\A\B])}
 #include "triangle2.inc"
#endif

\text{list=\([\B\C]),\([\A\C]),\([\A\B])}
\text{image=draw(240,140
\dessin)}

\statement{
 \A\B\C est un triangle rectangle en \A.
 <div class="wimscenter">
 <img src="\image" alt="">
</div>
 \quest ? \embed{r1,80x30}
}


\answer{Réponse}{\rep;\list}{type=dragfill}
