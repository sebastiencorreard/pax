target=calculd2

#include "author.inc"
#include "lang_titles.inc"
#include "lang.inc"

 \text{A=randitem(A,B,C,E,F,G)}
 \text{pyth=randrow(3,4,5
6,8,10
4,3,5
8,6,10
5,12,13
12,5,13
5,12,13
12,5,13)}
 \text{th0=arctan(\pyth[1]/\pyth[2])}
 \real{th=randitem(0,pi/2,pi,3*pi/2)+\th0}
 \integer{r=\pyth[3]}
 \integer{min=-\r-2}
 \integer{max=\r+2}
\text{dessin=}
\real{b=0.8}
\text{dessin=range \min,\max,\min,\max
parallel \min,\min,\min,\max,1,0,2*\r+5,grey
parallel \min,\min,\max,\min,0,1,2*\r+5,grey
fcircle 0,0,5,black
text black,0,0,medium,\A
fpoly red,\r*cos(\th),\r*sin(\th),\r*cos(\th)+\b*sin(\th),\r*sin(\th)-\b*cos(\th),(\r-\b)*cos(\th)+\b*sin(\th),(\r-\b)*sin(\th)-\b*cos(\th),(\r-\b)*cos(\th),(\r-\b)*sin(\th)
linewidth 2
dsegment 0,0,\r*cos(\th),\r*sin(\th),black
line \r*cos(\th)+20*sin(\th),\r*sin(\th)-20*cos(\th),\r*cos(\th)-20*sin(\th),\r*sin(\th)+20*cos(\th),black}
\text{image=draw(500,500
\dessin)}
\text{name=slib(lang/fname fr,boy)}
\real{r=\r*0.5}
\text{enonce=wims(replace internal AAAA by \A in \name_enonce)}
\statement{
\enonce?
<div class="wimscenter"><img src="\image" alt=""></div>
<b>\name_answer:</b>\embed{r1,5} cm}
\answer{}{\r}{type=numexp}
