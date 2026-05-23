target=cerclerect3
\language{fr}
\range{-5..5}
#include "author.inc"
#include "lang_titles.inc"
#include "lang.inc"

\computeanswer{no}
\format{html}
\precision{100}

\integer{sl=8}
\integer{ax=randint(1..4)}
\integer{ay=randint(1..4)}
\integer{L1=2*randint(3..7)}
\integer{L2=2*randint(2..7)+1}
\text{l=shuffle(\L1,\L2)}
\integer{ch=randint(1..4)}
\text{don=\ax*20,\ay*20,(\ax+\l[1])*20,\ay*20,\ax*20,(\ay+\l[2])*20,\ax*20,\ay*20
(20-\ax)*20,\ay*20,(20-\ax-\l[1])*20,\ay*20,(20-\ax)*20,(\ay+\l[2])*20,(20-\ax)*20-\sl,\ay*20
(20-\ax)*20,(20-\ay)*20,(20-\ax-\l[1])*20,(20-\ay)*20,(20-\ax)*20,(20-\ay-\l[2])*20,(20-\ax)*20-\sl,(20-\ay)*20-\sl
\ax*20,(20-\ay)*20,(\ax+\l[1])*20,(20-\ay)*20,\ax*20,(20-\ay-\l[2])*20,\ax*20,(20-\ay)*20-\sl}
\text{don=row(\ch,\don)}
\text{don2=item(7 to 8,\don)}
\text{don=item(1 to 6,\don)}
\text{dessin=draw(400,400
parallel 0,0,0,400,20,0,21,grey
parallel 0,0,400,0,0,20,21,grey
fsquare \don2,\sl,red
linewidth 2
triangle \don,black)}

\integer{x=(\don[3]+\don[5])/2}
\integer{y=(\don[4]+\don[6])/2}

\statement{
\name_question: <div class="wimscenter">\embed{r1}</div>}

\answer{}{\dessin;circle,\x,\y,10}{type=coord}
