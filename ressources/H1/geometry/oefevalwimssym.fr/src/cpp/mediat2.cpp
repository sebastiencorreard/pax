target=oefmediat2
#define NUM 2
#include "lang.inc"
#include "lang_titles.inc"
#include "author.inc"
\keywords{perpendicular_bisector}
\text{med1=draw(200,200
segment 50,100,150,100,black
segment 100,10,100,190,black
segment 122,96,126,104,red
segment 125,96,129,104,red
segment 72,96,76,104,red
segment 75,96,79,104,red
segment 50,95,50,105,black
segment 150,95,150,105,black
square 100,90,10,red
text black,80,10,medium,(d)
text black,45,110,medium,A
text black,150,110,medium,B
)}

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

\text{med6=draw(200,200
segment 50,100,150,100,black
segment 140,10,80,190,black
segment 50,95,50,105,black
segment 150,95,150,105,black
text black,110,10,medium,(d)
text black,45,110,medium,A
text black,150,110,medium,B
)}

\matrix{fig=\med1,,1
\med2,,2
\med3,,2
\med4,,2
\med5,,2
\med6,,2}

\integer{n=randint(1..6)}
\text{rep=row(\n,\fig)}

\statement{
<div class="wimscenter"><img src="\rep[1]" alt=""></div>
  \name_stat : \embed{r1}.
}

\answer{}{\rep[3];\name_choice}{type=menu}
