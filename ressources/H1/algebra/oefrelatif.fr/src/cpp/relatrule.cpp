target=relatrule
#include "lang_titles.inc"
#include "author.inc"
\computeanswer{no}
\precision{1000}
#include "lang.inc"

\integer{m=5}
\text{a=0}
\text{dessin=}
\for{i=-\m to \m}{
\integer{a=\i*1}
\integer{s=\i}
\text{dessin=\dessin
text blue, \s,-1, medium,\a}
}
\text{liste=\m}
\for{i=1 to 10*\m}{
	\real{c= -\m+2*\i*0.1}
	\text{liste=\liste,\c}
}
\text{liste=shuffle(\liste)}
\text{A=item(1,\liste)}
\text{B=item(2,\liste)}
\text{C=item(3,\liste)}
\text{D=item(4,\liste)}
\if{\A>=0 and \B>=0 and \C>=0 and \D>=0}{
	\real{A= -\A}
	\real{D= -\D}
}
\text{dessin=xrange -\m-0.1,\m+0.1
yrange -2,2.2
hline black,0,0
arrow 2.5,0,\m,0,10,black
parallel -\m,-0.8,-\m,0.4,1/2,0, 40, blue
parallel -\m,-0.3,-\m,0.3,1/10,0, 200, blue
parallel -\m,-0.8,-\m,0.6,1,0, 40, red
\dessin
text black, \A+0.1,2.2, medium,a
text black, \B+0.1,2.2, medium,b
text black, \C+0.1,2.2, medium,c
text black, \D+0.1,2.2, medium,d
arrow \A,2,\A,0, 8, black
arrow \B,2,\B,0, 8, black
arrow \C,2,\C,0, 8, black
arrow \D,2,\D,0, 8, black}
\text{dessintikz=drawtikz(600,50
\dessin)}
\statement{\instruction
<div class="wimscenter">
\draw{600,50}{\dessin}
</div>
}
\answer{\(a\)}{\A}{type=numeric}
\answer{\(b\)}{\B}{type=numeric}
\answer{\(c\)}{\C}{type=numeric}
\answer{\(d\)}{\D}{type=numeric}

\latex{
\begin{statement}
\instruction
\begin{center}
\dessintikz
\end{center}
\end{statement}
}

