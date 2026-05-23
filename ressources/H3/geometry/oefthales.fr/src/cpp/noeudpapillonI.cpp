target=NoeudpapillonI

\language{fr}
\range{-5..5}
#include "author.inc"
\computeanswer{no}
\format{html}
\precision{10000}
#include "lang_titles.inc"
#include "lang.inc"
\matrix{volt=
8,8,10,10
10,10,12,12
12,12,14,14
15,15,17,17}
\text{va=randomrow(\volt)}
\text{v1=item(1,\va)}
\text{v2=item(2,\va)}
\text{v3=item(3,\va)}
\text{v4=item(4,\va)}
\matrix{watt=
5,10,6,12
6,12,7,14
7,14,8,16
8,16,9,18}
\text{wa=randomrow(\watt)}
\text{w1=item(1,\wa)}
\text{w2=item(2,\wa)}
\text{w3=item(3,\wa)}
\text{w4=item(4,\wa)}
\matrix{pil=
-15,5,-20,-7,-16.5,7,-22,-7,\v1,\v2,\v3,\v4
-7.5,2.5,-10,-3.5,-9,5,-12,-4,\w1,\w2,\w3,\w4
}
\text{rec=randomrow(\pil)}
\real{p1=item(1,\rec)}
\real{p2=item(2,\rec)}
\real{p3=item(3,\rec)}
\real{p4=item(4,\rec)}
\real{p5=item(5,\rec)}
\real{p6=item(6,\rec)}
\real{p7=item(7,\rec)}
\real{p8=item(8,\rec)}
\real{p9=item(9,\rec)}
\real{p10=item(10,\rec)}
\real{p11=item(11,\rec)}
\real{p12=item(12,\rec)}
\text{dessin=xrange -25,25
yrange -15,15
poly blue,\p1,\p2,\p3,\p4,20,7,15,-5
segment \p1,\p2,\p3,\p4,red
segment 20,7,15,-5,red
text black,-0.5,3,medium,O
text black,21,9,medium,G
text black,16,-5,medium,H
text black,\p5,\p6,medium,E
text black,\p7,\p8,medium,F}
\text{dessintikz=drawtikz(200,200
\dessin)}
\statement{<p class="wimscenter">
\draw{250,150}{
\dessin}
</p>
\name_enonce
<p>
\([EF] \sslash [GH]\) ; \(EF = \p9\) \(cm\) ; \(GH = \p10\) \(cm\) ; \(EO = \p11\) \(cm\).
</p>
\name_question[1] \([HO]\) (\name_question[2] \(cm\))?}

\answer{\name_answer \([HO]\)}{\p12}
\hint{\name_hint}
\latex{
\begin{statement}
\name_enonce
<p>
\([EF] \parallel [GH]\) ; \(EF = \p9\) \(cm\) ; \(GH = \p10\) \(cm\) ; \(EO = \p11\) \(cm\).
</p>
\name_question[1] \([HO]\) (\name_question[2] \(cm\))?
\par
\dessintikz
\end{statement}
}
