target=oppose1 oppose2 oppose3 oppose4 oppose5
#include "author.inc"
#include "lang_titles.inc"
#include "lang.inc"

\text{let=shuffle(A,B,C,D,E,F,G)}
\text{A=\let[1]}
\text{B=\let[2]}

#if defined TARGET_oppose1
 \integer{xmax=randint(4..5)}
 \integer{xmin=-\xmax}
 \real{grd=0.1}
 \real{x1=randint(0..\xmax-3)+0.1*randint(1..9)}
 \real{x2=-\x1}
 \text{dessin=slib(draw/drtgraduee 1200,\xmin,\xmax,\grd,black,grey,40)}
 \text{figure=draw(1200,100
\dessin
text blue,\x1,2,medium,\A
fcircle \x1,0,8,blue
text blue,\x2,2,medium,\B
fcircle \x2,0,8,blue)}
 \text{enonce=\name_question[1] \A \name_question[2] \B \name_question[3]&#63;
<div class="wimscenter"><img src="\figure" alt=""></div>}
 \text{good=1}
#endif
#if defined TARGET_oppose2
 \integer{xmax=randint(4..5)}
 \integer{xmin=-\xmax}
 \real{grd=0.1}
 \real{x1=randint(1..\xmax-3)+0.1*randint(1..9)}
 \real{x2=-\x1+0.1*randint(2..4)}
 \text{dessin=slib(draw/drtgraduee 1200,\xmin,\xmax,\grd,black,grey,40)}
 \text{figure=draw(1200,100
\dessin
text blue,\x1,2,medium,\A
fcircle \x1,0,8,blue
text blue,\x2,2,medium,\B
fcircle \x2,0,8,blue)}
 \text{enonce=\name_question[1] \A \name_question[2] \B \name_question[3] &#63;
<div class="wimscenter"><img src="\figure" alt=""></div>}
 \text{good=2}
#endif
#if defined TARGET_oppose3
 \real{x2=randint(1..9)*0.1+randint(7..9)}
 \real{x1=-\x2}
 \text{enonce=\name_question[1] \x1 \name_question[2] \x2 \name_question[3]&#63;}
 \text{good=1}
#endif
#if defined TARGET_oppose4
 \real{x2=randint(1..9)*0.1+randint(7..9)}
 \real{x1=-\x2+randint(1..4)}
 \text{enonce=\name_question[1] \x1 \name_question[2] \x2 \name_question[3]&#63;}
 \text{good=2}
#endif
#if defined TARGET_oppose5
 \text{x2=randint(1..5)}
 \text{x1=\frac{1}{\x2}}
 \text{enonce=\name_question[1] \(\x1) \name_question[2] \(\x2) \name_question[3]&#63;}
 \text{good=2}
#endif
\text{good=\bad[\good]}
\statement{\enonce}

\choice{}{\good}{\bad}
