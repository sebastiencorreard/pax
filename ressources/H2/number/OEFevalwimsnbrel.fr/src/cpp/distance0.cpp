target=distance01 distance02 distance03 distance04 distance05
#include "author.inc"
#include "lang_titles.inc"
#include "lang.inc"
\text{A=randitem(A,B,C,D,E,F,G)}
\text{answer1=\name_answer}
#if defined TARGET_distance01
 \integer{xmax=randint(3..5)}
 \integer{xmin=-\xmax}
 \real{grd=0.1}
 \real{x=randint(1..\xmax-1)+0.1*randint(1..9)}
 \text{dessin=slib(draw/drtgraduee 1200,\xmin,\xmax,\grd,black,grey,40)}
 \text{figure=draw(1200,100
\dessin
text blue,\x,2,medium,\A
fcircle \x,0,8,blue )}
\text{answer1=\answer1 \A}
 \text{enonce=\name_question[1] \A \name_question[2]&#63;
<div class="wimscenter"><img src="\figure" alt=""></div>}
#endif
#if defined TARGET_distance02
 \integer{xmax=randint(3..5)}
 \integer{xmin=-\xmax}
 \real{grd=0.1}
 \real{x=randint(\xmin..-1)+0.1*randint(1..9)}
 \text{dessin=slib(draw/drtgraduee 1200,\xmin,\xmax,\grd,black,grey,40)}
 \text{answer1=\answer1 \A}
 \text{figure=draw(1200,100
\dessin
text blue,\x,2,medium,\A
fcircle \x,0,8,blue )}
 \text{enonce=\name_question[1] \A \name_question[2]&#63;
<div class="wimscenter"><img src="\figure" alt=""></div>}
#endif
#if defined TARGET_distance03
 \real{x=randint(10..20)+0.01*randint(1..9)}
 \text{enonce=\name_question \x&#63;}
#endif
#if defined TARGET_distance04
 \real{x=-randint(10..20)-0.01*randint(1..9)}
 \text{enonce=\name_question \x&#63;}
#endif
#if defined TARGET_distance05
 \text{x=randitem(1,-1)*randitem(1/2,1/4,3/4,5/4,1/5,2/5,3/5,4/5,6/5,7/5,8/5,3/2)}
 \text{x=simplify(\x)}
 \text{aff=texmath(\x)}
 \text{enonce=\name_question \(\aff)&#63;}
#endif

\text{x=simplify(abs(\x))}

\statement{\enonce}

\answer{\answer1}{\x}{type=numexp}
