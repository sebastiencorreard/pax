target=ordrerelatif
#include "lang_titles.inc"
#include "author.inc"
\computeanswer{no}

\integer{n=randint(4..7)}

\text{a=wims(randint 2,30 repeat \n)}
\text{a=wims(values x/5 for x in \a)}
\text{ b=wims(randint 2,30 repeat \n)}
\text{b=wims(values -x/5 for x in \b)}

\text{liste=wims(sort numeric item \a,\b)}

\text{liste=wims(listuniq \liste)}
\text{dessin=}
\for{i=1 to 2*\n}{
	\text{ss=\i%2=0? -1:4}
	\text{dessin=\dessin
disk item(\i,\liste),0,6,blue
text black,item(\i,\liste)-0.2,\ss*0.4,medium,item(\i,\liste)}
}

\real{m=wims(itemcnt \liste)}
\integer{s=randint(2..\m-1)}
\real{u=randint(10*item(\s,\liste)+1,10*item(\s+1,\liste)-1)/10}
\real{u=\u/10}
\real{m=item(\s, \liste)}
\real{M=item(\s+1, \liste)}
\text{dessin=\dessin
arrow \u,3,\u,0,6,red
text red,\u,3,medium,\u}
\text{listemix=shuffle(\liste)}
\text{listemix=wims(replace internal , by &nbsp;;&nbsp; in \listemix)}
#include "lang.inc"
\text{dessin=xrange -6,6
yrange -2,3
hline black,0,0
arrow 0,0,1,0,10,black
parallel -6,-0.8,-6,0.4,1/2,0, 120, blue
parallel -6,-0.3,-6,0.3,1/10,0, 600, blue
parallel -6,-0.8,-6,0.6,1,0, 40, red
\dessin}
\statement{\instruction
<div class="wimscenter"> \listemix.</div>
<div class="wims_question wimscenter">
\embed{reply 1, 5}\(\leq \u \leq \) \embed{reply 2, 5} </div>
}
\answer{}{\m}{type=numeric}
\answer{}{\M}{type=numeric}
\feedback{1=1}{
<div class="wimscenter">\draw{800,50}{
\dessin}
</div>}
\latex{
\begin{statement}
\instruction
\begin{center}
\listemix.
\end{center}
\end{statement}
}

