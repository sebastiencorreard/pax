target=Noeudpapillon
\language{fr}
\range{-5..5}
#include "author.inc"
\computeanswer{no}
\format{html}
\precision{10000}
#include "lang_titles.inc"
#include "lang.inc"
\matrix{cap=
4,2,6,3
6,3,8,4
8,4,10,5
10,5,12,6
12,6,14,7
}
\text{golf=randomrow(\cap)}
\text{c0=item(1,\golf)}
\text{c1=item(2,\golf)}
\text{c2=item(3,\golf)}
\text{c3=item(4,\golf)}
\text{dessin=xrange -25,25
yrange -15,15
poly red,-20,10,-20,-10,10,5,10,-5
text black,-0.5,2.5,medium,O
text black,-22,12,medium,A
text black,-22,-10,medium,B
text black,11,7,medium,C
text black,11,-5,medium,D}
\text{dessintikz=drawtikz(200,200
\dessin)}
\statement{<p class="wimscenter">
\draw{250,150}{\dessin}
</p>
<p>\name_enonce</p>
<p>
\([AB] \sslash [CD]\) ; \(AB = \c0\) \(cm\) ; \(CD = \c1\) \(cm\) ; \(AO = \c2\) \(cm\) .
</p>
\name_question[1] \([OD]\) (\name_question[2] \(cm\))?}

\answer{\name_answer \([OD]\)}{\c3}
\hint{\name_hint}
\latex{
\begin{statement}
<p>\name_enonce</p>
<p>
\([AB] \parallel [CD]\) ; \(AB = \c0\) \(cm\) ; \(CD = \c1\) \(cm\) ; \(AO = \c2\) \(cm\) .
</p>
\name_question[1] \([OD]\) (\name_question[2] \(cm\))?
\par
\dessintikz
\end{statement}}
