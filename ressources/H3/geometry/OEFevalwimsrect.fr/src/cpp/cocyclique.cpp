target=cocyclique2 cocyclique3
#include "author.inc"
#include "lang_titles.inc"
#include "lang.inc"

\language{fr}
\range{-5..5}
\computeanswer{no}
\format{html}
\precision{100}
\text{let=shuffle(A,B,C,D,E,F,G,H,R,S,T)}
\text{A=\let[1]}
\text{B=\let[2]}
\text{C=\let[3]}
\text{X=randitem(\B,\C)}
#if defined TARGET_cocyclique2
\matrix{name_choix=rectangle en \A
rectangle en \X,isocèle de sommet \A,isocèle de sommet \X,équilatèral}
#endif
#if defined TARGET_cocyclique3
\matrix{name_choix=isocèle de sommet principal O
isocèle de sommet principal \A,rectangle en \A,rectangle en O,équilatéral}
#endif
\statement{
Complétez la phrase suivante :
<div class="wimscenter" style="font-style:italic">
#if defined TARGET_cocyclique2
\A est un point du cercle de diamètre [\B\C] et de centre O.
Le point \A est distinct de \B et \C.
Le triangle \A\B\C est...</div>}
#endif
#if defined TARGET_cocyclique3
\A est un point du cercle de diamètre [\B\C] et de centre O.
Le point \A est distinct de \B et \C.
Le triangle O\A\B est...</div>}
#endif
\choice{}{\name_choix[1;]}{\name_choix[2;]}
