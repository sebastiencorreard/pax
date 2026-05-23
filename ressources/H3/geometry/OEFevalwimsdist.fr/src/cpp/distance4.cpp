target=distance4
\text{name_question=Chaque carreau fait 0.5 cm. Quelle est la distance entre le point \A et
la droite&nbsp;}
#include "author.inc"
#include "lang_titles.inc"
#include "lang.inc"

\text{A=randitem(A,B,C,E,F,G)}
\integer{ch=randitem(1,2,3,4)}
\real{th=item(\ch,0,pi/2,pi,3*pi/2)}
\integer{r=randint(3..7)}
\integer{min=-\r-2}
\integer{max=\r+2}
\text{dessin=range \min,\max,\min,\max
parallel \min,\min,\min,\max,1,0,2*\r+5,grey
parallel \min,\min,\max,\min,0,1,2*\r+5,grey
fcircle 0,0,5,black
text black,0,0,medium,\A
linewidth 2
line \r*cos(\th)+20*sin(\th),\r*sin(\th)-20*cos(\th),\r*cos(\th)-20*sin(\th),\r*sin(\th)+20*cos(\th),black}
\text{image=draw(300,300
\dessin)}
\text{name=slib(lang/fname fr,boy)}
\real{r=\r*0.5}
\text{question=wims(replace internal AAAA by \A in \name_question)}
\statement{
\question?
<div class="wimscenter"><img src="\image" alt=""></div>
<b>\name_answer: </b> \embed{r1,5} cm}

\answer{}{\r}{type=numexp}
