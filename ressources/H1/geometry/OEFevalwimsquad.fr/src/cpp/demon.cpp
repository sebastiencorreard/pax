target=oefdemon1 oefdemon2 oefdemon3 oefdemon4 oefdemon5

\langage{fr}
#include "author.inc"
#include "lang_titles.inc"
#include "lang.inc"
\format{html}

\text{nom=shuffle(A,B,C,E,F,G,H,J,K,L,M,N,R,S,T)}
#if defined TARGET_oefdemon1
\text{figcode=xrange -150,150
yrange -150,150
rotate 40
segment -100,60,100,60,black
segment 100,60,100,-60,black
segment 100,-60,-100,-60,black
segment -100,-60,-100,60,black
segment -100,60,100,-60,black
segment -100,-60,100,60,black
circle 0,0,234,black
text black,-115,70,medium,\nom[1]
text black,-115,-65,medium,\nom[2]
text black,110,70,medium,\nom[3]
text black,110,-65,medium,\nom[4]
text black,0,20,medium,\nom[5]}
#endif
#if defined TARGET_oefdemon2
\text{figcode=xrange -150,150
yrange -150,150
rotate 30
segment -80,80,80,80,black
segment 80,80,80,-80,black
segment 80,-80,-80,-80,black
segment -80,-80,-80,80,black
segment -80,80,80,-80,black
segment -80,-80,80,80,black
circle 0,0,227,black
text black,-95,90,medium,\nom[1]
text black,-95,-85,medium,\nom[2]
text black,90,90,medium,\nom[3]
text black,90,-85,medium,\nom[4]
text black,0,20,medium,\nom[5]}
#endif
#if defined TARGET_oefdemon3
\text{figcode=xrange -150,150
yrange -150,150
rotate 40
segment 0,120,80,0,black
segment 80,0,0,-120,black
segment 0,-120,-80,0,black
segment -80,0,0,120,black
segment -80,0,80,0,black
segment 0,-120,0,120,black
circle 0,0,240,black
circle 0,0,160,black
text black,-95,10,medium,\nom[1]
text black,-15,-125,medium,\nom[2]
text black,90,10,medium,\nom[3]
text black,-15,135,medium,\nom[4]
text black,10,20,medium,\nom[5]}
#endif
#if defined TARGET_oefdemon4
\text{figcode=xrange -150,150
yrange -150,150
rotate 20
segment 0,120,80,0,black
segment 80,0,0,-120,black
segment 0,-120,-80,0,black
segment -80,0,0,120,black
segment -80,0,80,0,black
segment 0,-120,0,120,black
segment -80,0,28,-78,black
segment 20,-70,26,-62,red
segment 26,-62,34,-69,red
segment 80,0,-28,78,black
segment -20,70,-26,62,red
segment -26,62,-34,69,red
text black,-95,10,medium,\nom[1]
text black,-15,-125,medium,\nom[2]
text black,90,10,medium,\nom[3]
text black,-15,135,medium,\nom[4]
text black,10,20,medium,\nom[5]
text black,40,-80,medium,\nom[6]
text black,-40,90,medium,\nom[7]}
#endif
#if defined TARGET_oefdemon5
\text{figcode=xrange -150,150
yrange -150,150
rotate 20
circle 0,60,180,black
circle 0,-60,180,black
segment 0,60,66,0,black
segment 66,0,0,-60,black
segment 0,-60,-66,0,black
segment -66,0,0,60,black
segment -5,65,5,55,black
segment -5,55,5,65,black
segment -5,-65,5,-55,black
segment -5,-55,5,-65,black
text black,-85,10,medium,\nom[1]
text black,-15,-75,medium,\nom[2]
text black,80,10,medium,\nom[3]
text black,-15,75,medium,\nom[4]}
#endif
\text{fig=draw(300,300
\figcode)}
\text{figurl=<img src="\fig" alt="">}
\text{figtikz=drawtikz(300,300
\figcode)}
#if defined TARGET_oefdemon1
\text{rep= 5,7}
#endif
#if defined TARGET_oefdemon2
\text{rep=5,6,7}
#endif
#if defined TARGET_oefdemon3
\text{rep=6,7}
#endif
#if defined TARGET_oefdemon4
\matrix{rep=2,3}
#endif
#if defined TARGET_oefdemon5
\matrix{rep=4}
#endif
#if defined TARGET_oefdemon1 || defined TARGET_oefdemon2
\text{enonc=\name_enonc[1] \nom[5] \name_enonc[2] [\nom[1]\nom[4]]
  \name_enonc[3] [\nom[3]\nom[2]] \name_enonc[4].}
#endif
#if defined TARGET_oefdemon3
\text{enonc=\name_enonc[1] \nom[5] \name_enonc[2] [\nom[1]\nom[4]]
  \name_enonc[3] \nom[5] \name_enonc[4] [\nom[2]\nom[4]]. \name_enonc[5]
  (\nom[1]\nom[3]) \name_enonc[6] (\nom[2]\nom[4]) \name_enonc[7]}
#endif
#if defined TARGET_oefdemon4
\text{enonc=\name_enonc[1] \nom[1]\nom[2]\nom[3]\nom[4].
\name_enonc[2] (\nom[1]\nom[6]) \name_enonc[3] (\nom[2]\nom[3]).
\name_enonc[4] (\nom[3]\nom[7]) \name_enonc[5] (\nom[1]\nom[4]).}
#endif
#if defined TARGET_oefdemon5
\text{enonc=\name_enonc[1] \nom[2] \name_enonc[2] \nom[4].
\name_enonc[3] \nom[1] \name_enonc[4] \nom[3].}
#endif
\text{latextext=}
\for{j=1 to 7}{
  \text{latextext=\latextext
  \item \prop[\j]}
}

\statement{
<div class="wims_columns">
 <div class="medium_size img_col">\figurl</div>
 <div class="medium_size text_col">
\enonc
<p>
\name_enonce[1] \nom[1]\nom[2]\nom[4]\nom[3] \name_enonce[2]
</p>
\name_question:
<ul>\for{h=1 to 7}{<li>\embed{r1,\h}</li>}</ul>
</div></div>
}

\answer{}{\rep;\prop}{type=checkbox}

\latex{
\begin{statement}
\enonc
\par
\name_enonce[1] \nom[1]\nom[2]\nom[4]\nom[3] \name_enonce[2]
\begin{center}
  \figtikz
\end{center}
\name_question:
\begin{radio}
\latextext
\end{radio}
\end{statement}
}
