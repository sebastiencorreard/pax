target=longueur1 longueur2 longueur3 longueur4
#define TITRE Calculer une longueur
\language{fr}
\range{-5..5}
#include "author.inc"
\computeanswer{no}
\format{html}
\precision{1000}

\integer{xmax=randint(300..350)}
\integer{ymax=200}
\integer{u=random(2..6)}
\integer{v=random(1..\u-1)}
\integer{sm=max(\u^2-\v^2,2*\u*\v)}
\integer{mn=min(\u^2-\v^2,2*\u*\v)}
\integer{sn=(\mn^2+\sm^2)^(1/2)}

#include "triangle1.inc"
\text{enonce1=Le triangle \(\A\B\C) est rectangle en \(\A)}

#if defined TARGET_longueur1
 \title{TITRE 1}
 \text{inc=\B\C}
 \text{longueur=\A\B = \mn &nbsp; ; &nbsp; \A\C = \sm}
 \integer{rep=\sn}
#endif
#if defined TARGET_longueur2
 \title{TITRE 2}
 \text{inc=\A\B}
 \text{longueur=\B\C = \sn &nbsp; ; &nbsp; \A\C = \sm}
 \integer{rep=\mn}
#endif
#if defined TARGET_longueur3
 \title{TITRE 3}
 \text{inc=\B\C}
 \text{longueur=\A\B = \mn &nbsp; ; &nbsp; \A\C = \sm}
 \integer{rep=\sn}
 \text{dessin=}
#endif
#if defined TARGET_longueur4
 \title{TITRE 4}
 \text{inc=\A\B}
 \text{longueur=\B\C = \sn &nbsp; ; &nbsp; \A\C = \sm}
 \integer{rep=\mn}
 \text{dessin=}
#endif
#if defined TARGET_longueur1 || defined TARGET_longueur2 || defined TARGET_longueur3 || defined TARGET_longueur4
\text{enonce=\enonce1.<br> Les longueurs suivantes sont connues :
  <div class="wimscenter">\longueur</div>
  Calculer la longueur du segment \([\inc]).}
#endif
#if defined TARGET_longueur5
 \title{TITRE 5}
 \text{inc=\A\B}
 \text{enonce=\enonce1.<br> Quelle est la longueur (en carreaux) du segment [\B\C].}
 \integer{rep=\mn}
 \text{dessin=parallel 0,0,\xmax,0,0,20,\ymax/20+1,grey
parallel 0,0,0,\ymax,20,0,\xmax/20+1,grey
\dessin}
#endif
\text{dessin=\dessin!= ?draw(\xmax,\ymax
\dessin)}
\statement{
\if{\dessin!=}{
<div class="wims_columns">
 <div class="medium_size img_col"><img src="\dessin" alt="">
 <div class="wims_instruction">
  Le dessin n'est pas à l'échelle.</div></div>
 <div class="medium_size text_col">
 \enonce
 </div>
</div>
}{
 \enonce
}}

\answer{\inc}{\rep}{type=numexp}
