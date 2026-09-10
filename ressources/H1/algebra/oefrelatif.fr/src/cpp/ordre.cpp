target=ordre
#include "lang_titles.inc"
#include "author.inc"
\computeanswer{yes}
\precision{10000}
#include "lang.inc"
\integer{m=6}
\integer{n=6}
\text{a=0}
\text{dessin=}
\for{i=-\m to \n}{
  \integer{a=\i}
  \integer{s=\i}
\text{dessin=\dessin
text black, \s,-1, medium,\a}}

\text{liste=<,>,=}
\real{A=randint(10..10*\m-1)/10}
\real{B=randint(10..10*\m-1)/10}
\real{C=-\A}
\real{D=-\A}
\text{listeA=shuffle(\A,\B,-\A,-\B)}
\text{AA= item(1,\listeA)}
\text{AA=\AA>0 ? +\AA}
\text{BB=item(2,\listeA)}
\text{BB=\BB>0 ? +\BB}
\text{CC=item(3,\listeA)}
\text{CC=\CC>0 ? +\CC}
\text{choix=>,<,=}
\text{rep1= \AA>\BB ? >:<}
\text{rep1= \AA=\BB ? =}
\text{rep2= \CC>\BB ? >:<}
\text{rep2= \CC=\BB ? =}
\text{rep3= \AA> \CC ? >:<}
\text{rep3= \AA=\CC ? =}

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
\statement{ \instruction.
<div class="wims_question">
  <div class="wimscenter">
 \AA \embed{reply 1,40x40} \BB
 </div><div class="wimscenter">
 \CC \embed{reply 2,40x40} \BB
 </div><div class="wimscenter">
 \AA \embed{reply 3,40x40} \CC
 </div>
 </div>
<div class="wimscenter">\draw{600,50}{\dessin}
</div>}
\answer{}{\rep1;\choix}{type=clickfill}
\answer{}{\rep2;\choix}{type=clickfill}
\answer{}{\rep3;\choix}{type=clickfill}

\latex{
\begin{statement}
\instruction.
\begin{itemize}
 \item \AA \(\cdots\) \BB
 \item \CC \(\cdots\) \BB
 \item \AA \(\cdots\) \CC
\end{itemize}
\begin{center}
\dessintikz
\end{center}
\end{statement}
}
