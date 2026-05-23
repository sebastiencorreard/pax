target=Thalsetcerclec
\language{fr}
\range{-5..5}
#include "author.inc"
\computeanswer{no}
\format{html}
\precision{10000}
#include "lang_titles.inc"
#include "lang.inc"
\matrix{donne=
6,3,4,8
12,6,8,16
18,9,12,24
24,12,16,32}
\text{ligne=randomrow(\donne)}
\text{FG=item(1,\ligne)}
\text{HO=item(2,\ligne)}
\text{EO=item(3,\ligne)}
\text{EG=item(4,\ligne)}
\text{dessin=xrange -25,25
yrange -25,25
circles red, 0,0,22,red
segment -22,0,22,0,blue
circles red,-11,0,11,red
polyline blue,-22,0,14,17,22,0
segment 14,17,22,0,black
segment -4.5,8.8,0,0,black
text black,-24,1,medium,E
text black,15,19,medium,F
text black,23,1,medium,G
text black,-4,12,medium,H
text black,1,3,medium,O}
\text{dessintikz=drawtikz(200,200
\dessin)}
\statement{<p class="wimscenter">
\draw{250,250}{
\dessin}
</p>
<p>\name_enonce</p>
<p>\([HO] \sslash [FG]\) ; \(FG = \FG\) \(cm\) ; \(HO = \HO\) \(cm\) ; \(EO = \EO\) \(cm\).
</p>
\name_question[1] \([EG]\) (\name_question[2] \(cm\))?}

\answer{\name_answer \([EG]\)}{\EG}{type=default}
\hint{\name_hint}

\latex{
\begin{statement}
<p>\name_enonce</p>
<p>\([HO] \parallel [FG]\) ; \(FG = \FG\) \(cm\) ; \(HO = \HO\) \(cm\) ; \(EO = \EO\) \(cm\).
</p>
\name_question[1] \([EG]\) (\name_question[2] \(cm\))?
\par
\dessintikz
\end{statement}
}
