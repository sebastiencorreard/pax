\title{Question 0714 Angles symétrie centrale }
\keywords{symmetry,angles}
\text{cas=randomitem(1,2,3)}
\text{angle=25,72,83}
\text{points=D,E,F}
%%% Pour feedback %%%%

\if{\cas==1}{
  \text{figquestion=arc 7,4.5,2,2,260,285,red
  text black,7,3.5,medium,?}
  \text{txtfeed=D est l'image de A.}
  }
\if{\cas==2}{
  \text{figquestion=arc 8,1.3,1.3,1.3,105,170,red
  text black,7.2,2.1,medium,?}
  \text{txtfeed=E est l'image de B.}
  }
\if{\cas==3}{
  \text{figquestion=arc 6.5,1.5,1.3,1.3,-10,80,red
  text black,7,2.2,medium,?}
  \text{txtfeed=F est l'image de C.}
  }    
  
  
\text{fig714=draw(300,300
xrange 1,9
yrange 0,8
text black,3.4,2.4,medium,A
arc 3,2.4,2,2,82,108,red
text black,2.7,3.9,medium,25°

text black,1.5,5.7,medium,B
arc 2,5.7,1.4,1.4,285,350,red
text black,2.4,5.2,medium,72°

text black,3.5,6,medium,C
arc 3.5,5.5,1.3,1.3,177,263,red
text black,3,5.4,medium,83°

crosshair 5,3.5,black
text black,5,4,medium,O

text black,8.5,1.3,medium,E
text black,6,1.5,medium,F
text black,7,5,medium,D
\figquestion

segment 3,2.5,2,5.7,black
segment 2,5.7,3.5,5.5,black
segment 3.5,5.5,3,2.5,black
segment 7,4.5,8,1.3,black
segment 8,1.3,6.5,1.5,black
segment 6.5,1.5,7,4.5,black
)}

\text{fig714=<div class="wimscenter"><img src="\fig714" alt="Pavé droit"></div>}
\text{enonce=Le triangle \(DEF\) est le symétrique du triangle \(ABC\) par rapport au point \(O\). \fig714  Complète <br>&#63; \({}={}\)  }
\text{enonceb= °}

\real{rep=\angle[\cas]}
\text{feedback=Par la symétrie, \txtfeed Les angles sont donc de même mesure : \angle[\cas] °. }
