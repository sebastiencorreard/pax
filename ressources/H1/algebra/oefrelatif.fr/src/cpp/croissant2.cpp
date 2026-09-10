target=croissant2
#include "lang_titles.inc"
#include "author.inc"
\computeanswer{no}
\precision{10000}
#include "lang.inc"
\integer{m=3}
\integer{n=3}
\text{a=0}
\text{dessin=}
\for{i=-\m to \n}{
  \integer{a=\i}
  \integer{s=\i}
\text{dessin=\dessin
text black, \s,-1, medium,\a}}

\real{A=-randint(0..10*\m-1)/10}
\real{B=randint(0..10*\m-1)/10}
\real{C=-randint(10..10*\m-1)/10}
\real{D= random(1,-1)*randint(10..10*\m-1)/10}
\real{E= -randint(10..10*\m-1)/10}
\real{F= -randint(10..10*\m-1)/10}
\text{listeA=wims(listuniq \A,\B,\C,\E,\D,\F)}
\text{choix=random(1,2)}
\text{crois=item(\choix,\name_choix)}
\text{listecr=wims(sort numeric list \listeA)}
\text{listeB=shuffle(\listeA)}
\text{listeB=wims(replace , by ,&nbsp; &nbsp; in \listeB)}
\text{listedec=wims(sort reverse numeric list \listecr)}
\text{liste=\choix=1? \listecr:\listedec}
\text{dessin=xrange -\m-0.1,\n+0.1
yrange -2,2
hline black,0,0
arrow \n-0.5,0,\n,0,10,black
parallel -\m,-0.8,-\m,0.4,1/2,0,40, blue
parallel -\m,-0.3,-\m,0.3,1/10,0,200, blue
parallel -\m,-0.8,-\m,0.6,1,0,40, red
\dessin}
\text{dessintikz=drawtikz(600,50
\dessin)}
\statement{\instruction[1], \instruction[2] \crois \instruction[3]
<div class="wimscenter"> \listeB</div>
<div class="wimscenter">\draw{600,50}{
\dessin
}
</div>
}
\answer{}{\liste}{type=vector}

\latex{
\begin{statement}
\instruction[1], \instruction[2] \crois \instruction[3] \listeB
\begin{center}
\dessintikz
\end{center}
\end{statement}
}
