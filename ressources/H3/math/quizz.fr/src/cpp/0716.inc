\title{Question 0716 Nombre de faces d'un solide }
\keywords{}
\text{figA=segment 2,2.5,4,1,black
segment 4,1,6,1,black
segment 6,1,7,2,black
segment 7,2,6,3,black
segment 6,3,2,2.5,black

segment 2,2.5,2,4.5,black
segment 4,1,4,3,black
segment 6,1,6,3,black
segment 7,2,7,4,black
segment 6,3,6,5,black

segment 2,4.5,4,3,black
segment 4,3,6,3,black
segment 6,3,7,4,black
segment 7,4,6,5,black
segment 6,5,2,4.5,black

segment 2,4.5,5,8,black
segment 4,3,5,8,black
segment 6,3,5,8,black
segment 7,4,5,8,black
segment 6,5,5,8,black}
\text{figB=segment 2,2.5,4,1,black
segment 4,1,6,1,black
segment 6,1,7,2,black
segment 7,2,4,3,black
segment 4,3,2,2.5,black

segment 2,2.5,2,4.5,black
segment 4,1,4,3,black
segment 6,1,6,3,black
segment 7,2,7,4,black
segment 4,3,4,5,black

segment 2,4.5,4,3,black
segment 4,3,6,3,black
segment 6,3,7,4,black
segment 7,4,4,5,black
segment 4,5,2,4.5,black

segment 2,4.5,5,8,black
segment 4,3,5,8,black
segment 6,3,5,8,black
segment 7,4,5,8,black
segment 4,5,5,8,black}
\text{figC=segment 2,2.5,4,1,black
segment 4,1,6,1,black
segment 6,1,7,2,black
segment 7,2,2,2.5,black

segment 2,4.5,4,3,black
segment 4,3,6,3,black
segment 6,3,7,4,black
segment 7,4,2,4.5,black

segment 2,2.5,2,4.5,black
segment 4,1,4,3,black
segment 6,1,6,3,black
segment 7,2,7,4,black

segment 2,4.5,5,8,black
segment 4,3,5,8,black
segment 6,3,5,8,black
segment 7,4,5,8,black}
\text{figD=segment 2,2.5,2,1,black
segment 2,1,6,1,black
segment 6,1,7,2,black
segment 7,2,2,2.5,black

segment 2,4.5,2,3,black
segment 2,3,6,3,black
segment 6,3,7,4,black
segment 7,4,2,4.5,black

segment 2,2.5,2,4.5,black
segment 2,1,2,3,black
segment 6,1,6,3,black
segment 7,2,7,4,black

segment 2,4.5,5,8,black
segment 2,3,5,8,black
segment 6,3,5,8,black
segment 7,4,5,8,black}
\text{cas=randomitem(1,2,3,4)}
\if{\cas==1}{
  \text{fig=\figA}
  \integer{rep=11}}
\if{\cas==2}{
  \text{fig=\figB}
  \integer{rep=11}}
\if{\cas==3}{
  \text{fig=\figC}
  \integer{rep=9}}
\if{\cas==4}{
  \text{fig=\figD}
  \integer{rep=9}}


\text{fig716=draw(300,300
xrange 0,8.5
yrange 0,8.5
\fig
)}

\text{fig716=<div class="wimscenter"><img src="\fig716" alt="solide"></div>}
\text{enonce=Quel est le nombre de faces de ce solide &#63; \fig716}
\text{enonceb= faces}

\real{rep=\rep}
\text{feedback= Le solide est composé d'un pavé droit surmonté d'une pyramide.}
