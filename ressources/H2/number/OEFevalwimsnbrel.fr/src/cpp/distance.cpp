target=distance1 distance2 distance3 distance4 distance5
#include "author.inc"
#include "lang_titles.inc"
#include "lang.inc"
\text{let=shuffle(A,B,C,D,E,F,G)}
\text{A=\let[1]}
\text{B=\let[2]}
#if defined TARGET_distance1
 \integer{xmax=randint(4..5)}
 \integer{xmin=-\xmax}
 \real{grd=0.1}
 \real{x1=randint(0..\xmax-3)+0.1*randint(1..9)}
 \real{x=randint(1..9)*0.1+1}
 \real{x2=\x1+\x}
 \integer{ch=randint(1..2)}
 \if{\ch=1}{
  \real{x1=-\x1}
  \real{x2=-\x2}
 }
 \text{dessin=slib(draw/drtgraduee 1200,\xmin,\xmax,\grd,black,grey,40)}
 \text{figure=draw(1200,100
\dessin
text blue,\x1,2,medium,\A
fcircle \x1,0,8,blue
text blue,\x2,2,medium,\B
fcircle \x2,0,8,blue)}
 \text{enonce=\name_question[1] \A \name_question[2] \B \name_question[3] &#63;
<div class="wimscenter"><img src="\figure" alt=""></div>}
#endif
#if defined TARGET_distance2
 \integer{xmax=randint(4..5)}
 \integer{xmin=-\xmax}
 \real{grd=0.1}
 \real{x1=randint(0..\xmax-1)+0.1*randint(1..9)}
 \real{x2=randint(\xmin..-1)+0.1*randint(1..9)}
 \real{x=abs(\x1-\x2)}
 \text{dessin=slib(draw/drtgraduee 1200,\xmin,\xmax,\grd,black,grey,40)}
 \text{figure=draw(1200,100
\dessin
text blue,\x1,2,medium,\A
fcircle \x1,0,8,blue
text blue,\x2,2,medium,\B
fcircle \x2,0,8,blue)}
 \text{enonce=\name_question[1] \A \name_question[2] \B \name_question[3]&#63;
<div class="wimscenter"><img src="\figure" alt=""></div>}
#endif
#if defined TARGET_distance3
 \real{x1=randint(2..5)+0.1*randint(1..9)}
 \real{x2=randint(1..9)*0.1+randint(7..9)}
 \real{x=abs(\x1-\x2)}
 \integer{ch=randint(1..2)}
 \text{enonce=\name_question[1] \x1 \name_question[2] \x2 \name_question[3]&#63;}
#endif
#if defined TARGET_distance4
 \real{x1=-randint(2..5)-0.1*randint(1..9)}
 \real{x2=-randint(1..9)*0.1-randint(7..9)}
 \real{x=abs(\x1-\x2)}
 \integer{ch=randint(1..2)}
 \text{enonce=\name_question[1] \x1 \name_question[2] \x2 \name_question[3]&#63;}
#endif
#if defined TARGET_distance5
 \text{s=shuffle(1,-1)}
 \real{x1=\s[1]*randint(2..5)+\s[1]*0.1*randint(1..9)}
 \real{x2=\s[2]*randint(1..9)*0.1+\s[2]*randint(7..9)}
 \real{x=abs(\x1-\x2)}
 \integer{ch=randint(1..2)}
 \text{enonce=\name_question[1] \x1 \name_question[2] \x2 \name_question[3]&#63;}
#endif

\statement{\enonce}

\answer{\name_answer}{\x}{type=numexp}
