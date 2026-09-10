target=lecturegraph1 lecturegraph2 lecturegraph3 lecturegraph4 lecturegraph5 lecturegraphB1 lecturegraphB2 lecturegraphB3 lecturegraphB4 lecturegraphB5
#include "author.inc"
#include "lang_titles.inc"
#include "lang.inc"
\text{A=randitem(A,B,C,D,E,F,G)}
#if defined TARGET_lecturegraph1
 \integer{xmax=randint(6..8)}
 \integer{xmin=-\xmax}
 \real{grd=0.1}
 \integer{x=randint(\xmin+1..\xmax-1)}
#endif
#if defined TARGET_lecturegraph2
 \integer{xmax=randint(3..5)}
 \integer{xmin=-\xmax}
 \real{grd=0.1}
 \real{x=randint(1..\xmax-1)+0.1*randint(1..9)}
#endif
#if defined TARGET_lecturegraph3
 \integer{xmax=randint(3..5)}
 \integer{xmin=-\xmax}
 \real{grd=0.1}
 \real{x=randint(\xmin+1..0)-0.1*randint(1..9)}
#endif
#if defined TARGET_lecturegraph4
 \integer{xmax=1}
 \integer{xmin=-1}
 \real{grd=0.01}
 \real{x=-0.1*randint(1..9)}
#endif
#if defined TARGET_lecturegraph5
 \integer{xmin=randint(2..5)*randitem(1,-1)}
 \integer{xmax=\xmin+1}
 \real{grd=0.01}
 \real{x=\xmin+0.1*randint(1..9)+0.01*randint(1..9)}
#endif
#if defined TARGET_lecturegraphB1
 \integer{xmax=randint(6..8)}
 \integer{xmin=0}
 \real{grd=0.1}
 \integer{x=randint(\xmin+1..\xmax-1)}
#endif
#if defined TARGET_lecturegraphB2
 \integer{xmax=randint(3..5)}
 \integer{xmin=0}
 \real{grd=0.1}
 \real{x=randint(1..\xmax-1)+0.1*randint(1..9)}
#endif
#if defined TARGET_lecturegraphB3
 \integer{n=randint(11..19)}
 \integer{xmax=\n+randint(3..8)}
 \integer{xmin=\n}
 \real{grd=0.1}
 \real{x=randint(\xmin+1..\xmax-1)}
#endif
#if defined TARGET_lecturegraphB4
 \integer{xmax=2}
 \integer{xmin=0}
 \real{grd=0.01}
 \real{x=0.1*randint(1..9)}
#endif
#if defined TARGET_lecturegraphB5
 \integer{n=randint(11..17)}
 \integer{xmax=\n+2}
 \integer{xmin=\n}
 \real{grd=0.1}
 \real{x=\xmin+0.1*randint(1..9)+0.01*randint(1..9)+randint(0..1)}
#endif

\text{dessin=slib(draw/drtgraduee 1200,\xmin,\xmax,\grd,black,grey,40,0)}

\text{figure=draw(1200,100
\dessin
text blue,\x,2,medium,\A
fcircle \x,0,8,blue )}
\statement{\name_question[1] \A \name_question[2]?
<div class="wimscenter"><img src="\figure" alt=""></div>}

\answer{\name_absord[1] \A}{\x}{type=numexp}
