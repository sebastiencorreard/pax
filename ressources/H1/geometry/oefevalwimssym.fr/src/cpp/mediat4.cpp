target=oefmediat4
#define NUM 4
#include "lang.inc"
#include "lang_titles.inc"
#include "author.inc"
\keywords{perpendicular_bisector}
\text{med2=draw(200,200
segment 50,100,150,100,black
segment 190,10,10,190,black
segment 122,96,126,104,red
segment 125,96,129,104,red
segment 72,96,76,104,red
segment 75,96,79,104,red
segment 50,95,50,105,black
segment 150,95,150,105,black
text black,160,10,medium,(d)
text black,45,110,medium,A
text black,150,110,medium,B
)}

\text{med3=draw(200,200
segment 50,100,150,100,black
segment 110,10,90,190,black
segment 122,96,126,104,red
segment 125,96,129,104,red
segment 72,96,76,104,red
segment 75,96,79,104,red
segment 50,95,50,105,black
segment 150,95,150,105,black
text black,120,10,medium,(d)
text black,45,110,medium,A
text black,150,110,medium,B
)}

\text{med4=draw(200,200
segment 50,100,150,100,black
segment 75,10,75,190,black
segment 50,95,50,105,black
segment 150,95,150,105,black
square 75,90,10,red
text black,80,10,medium,(d)
text black,45,110,medium,A
text black,150,110,medium,B
)}

\text{med5=draw(200,200
segment 50,100,150,100,black
segment 95,10,95,190,black
segment 50,95,50,105,black
segment 150,95,150,105,black
square 95,90,10,red
text black,97,10,medium,(d)
text black,45,110,medium,A
text black,150,110,medium,B
)}

\matrix{fig=\med2,4
\med3,4
\med4,5
\med5,5}

\integer{n=randint(1..4)}
\text{rep=row(\n,\fig)}

\statement{
<div class="wimscenter"><img src="\rep[1]" alt=""></div>
\name_stat
<div class="wimscenter">\embed{r1}.</div>
}

\answer{}{\rep[2];\reps}{type=mark}
