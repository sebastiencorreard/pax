target=oefmediat5
#include "lang.inc"
#define NUM 5
#include "lang_titles.inc"
#include "author.inc"
\keywords{perpendicular_bisector}
\text{med1=draw(300,300
segment 20,280,280,20,black
segment 100,100,200,200,black
segment 95,105,105,95,black
segment 195,205,205,195,black
segment 150,10,150,290,black
segment 10,150,290,150,black
segment 220,10,80,290,black
segment 10,220,290,80,black
segment 0,250,250,0,black
segment 50,290,290,50,black
text black,90,90,medium,A
text black,202,202,medium,B
)}

\text{rep=polygon,10,284,16,290,138,168,132,162|polygon,162,132,168,138,290,16,284,10}

\statement{
\name_stat
<div class="wimscenter">\embed{r1}</div>}

\answer{}{\med1;\rep}{type=coord}
