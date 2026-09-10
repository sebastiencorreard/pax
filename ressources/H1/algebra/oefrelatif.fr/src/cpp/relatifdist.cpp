target=relatifdist
#include "lang_titles.inc"
#include "author.inc"
\computeanswer{no}
\precision{10000}
\integer{m=3}
\integer{n=3}
\text{a=0}
\text{dessin=}
\for{i=-\m to \n}{
	\integer{a=\i}
	\integer{s=\i}
	\text{dessin=\dessin
text black, \s,-1, medium,\a}
}

\real{A=random(1,-1)*randint(0..10*\m-1)/10}
\real{B=random(1,-1)*randint(0..10*\m-1)/10}
\real{distance=abs(\A-(\B))}
\text{A=\A>0? +\A}
\text{B=\B>0? +\B}
\text{dessin=xrange -\m-0.1,3
yrange -2,2
hline black,0,0
arrow 2.5,0,3,0,10,black
parallel -\m,-0.8,-\m,0.4,1/2,0, 40, blue
parallel -\m,-0.3,-\m,0.3,1/10,0, 200, blue
parallel -\m,-0.8,-\m,0.6,1,0, 40, red
\dessin}
\text{dessintikz=drawtikz(600,50
\dessin)}

#include "lang.inc"
\statement{
\instruction
<div class="wimscenter">
\draw{600,50}{\dessin}
</div>
}
\answer{\name_answer \(A\) \name_and \(B\)}{\distance}{type=numeric}

\latex{
\begin{statement}
\instruction
\begin{center}
\dessintikz
\end{center}
\end{statement}
}
