target=oefrecqua1 oefrecqua2 oefrecqua3 oefrecqua4
\langage{fr}
#include "author.inc"
\format{html}
#include "lang_titles.inc"
#include "lang.inc"
#if defined TARGET_oefrecqua3 || defined TARGET_oefrecqua4
\text{nom=shuffle(A,B,C,E,F,G,H,J,K,L,M,N,R,S,T)}
#endif
#if defined TARGET_oefrecqua1 || defined TARGET_oefrecqua2
\text{nom=O}
#endif
#if defined TARGET_oefrecqua1 || defined TARGET_oefrecqua2
\matrix{qua=square 0,0,100,black
rect 0,0,-120,100,black
poly black,0,100,100,0,0,-100,-100,0
poly black,0,140,100,0,0,-140,-100,0}
\integer{a=randint(1..4)}
\text{qua=row(\a,\qua)}
\text{enonc=\nat[\r]}
#endif
\text{n_nom=\name_nom}
#if defined TARGET_oefrecqua1 || defined TARGET_oefrecqua2
\text{figcode=xrange -150,150
yrange -150,150
circle 0,0,200,black
\qua
segment 5,5,-5,-5,black
segment 5,-5,-5,5,black
text black,-10,-10,medium,\nom}
#endif
#if defined TARGET_oefrecqua3 || defined TARGET_oefrecqua4
\text{figcode=xrange -150,150
yrange -150,150
circle 0,0,200,black
rect 0,0,-120,100,black
square 0,0,100,black
poly black,0,100,100,0,0,-100,-100,0
poly black,0,140,100,0,0,-140,-100,0
text black,5,-5,medium,\nom[1]
text black,5,115,medium,\nom[2]
text black,-125,115,medium,\nom[3]
text black,-125,-5,medium,\nom[4]
text black,105,5,medium,\nom[5]
text black,105,-100,medium,\nom[6]
text black,5,-102,medium,\nom[7]
text black,-107,-5,medium,\nom[8]
text black,10,145,medium,\nom[9]
text black,10,-137,medium,\nom[10]}
\matrix{qua=\nom[1]\nom[5]\nom[6]\nom[7]
\nom[1]\nom[2]\nom[3]\nom[4]
\nom[2]\nom[5]\nom[7]\nom[8]
\nom[9]\nom[5]\nom[10]\nom[8]}
\integer{a=randint(1..4)}
\text{qua=row(\a,\qua)}
\text{name_question=\name_question \qua}
#endif
\text{fig=draw(300,300
\figcode)}
\text{figtikz=drawtikz(300,300
\figcode)}
\text{des=<img src="\fig" alt="">}
\text{latextext=}
\for{b in \n_nom}{
  \text{latextext=\latextext
\item \b}
}
\statement{<div class="wims_columns">
 <div class="medium_size img_col">\des</div>
 <div class="medium_size text_col">
\name_enonce \nom[1].
\name_question:
<div class="wimscenter">
#if defined TARGET_oefrecqua1 || defined TARGET_oefrecqua3
\embed{r1,150x40}
#endif
#if defined TARGET_oefrecqua2 || defined TARGET_oefrecqua4
\embed{r1,20}
#endif
</div>
</div></div>
}
#if defined TARGET_oefrecqua1 || defined TARGET_oefrecqua3
\answer{}{\n_nom[\a];\n_nom}{type=clickfill}
#endif
#if defined TARGET_oefrecqua2 || defined TARGET_oefrecqua4
\answer{}{\n_nom[\a]}{type=atext}
#endif
\latex{
\begin{statement}
#if defined TARGET_oefrecqua3
\name_enonce[1] \nom[1] \name_enonce[2]
\par
#endif
\name_question:
\begin{center}
\figtikz
\end{center}
\begin{radio}
\latextext
\end{radio}
\end{statement}
}
