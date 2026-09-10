target=placerpt1 placerpt2 placerpt3 placerpt4 placerpt5 placerptB1 placerptB2 placerptB3 placerptB4 placerptB5
#include "author.inc"
#include "lang_titles.inc"
#include "lang.inc"
\integer{coeffzone=1}

#if defined TARGET_placerpt1
 \integer{xmax=randint(6..8)}
 \integer{xmin=-\xmax}
 \real{grd=0.1}
 \integer{x=randint(\xmin+1..\xmax-1)}
#endif
#if defined TARGET_placerpt2
 \integer{xmax=randint(3..5)}
 \integer{xmin=-\xmax}
 \real{grd=0.1}
 \real{x=randint(1..\xmax-1)+0.1*randint(1..9)}
#endif
#if defined TARGET_placerpt3
 \integer{xmax=randint(3..5)}
 \integer{xmin=-\xmax}
 \real{grd=0.1}
 \real{x=randint(\xmin+1..0)-0.1*randint(1..9)}
#endif
#if defined TARGET_placerpt4
 \integer{xmax=1}
 \integer{xmin=-1}
 \real{grd=0.01}
 \integer{coeffzone=2}
 \real{x=-0.1*randint(1..9)}
#endif
#if defined TARGET_placerpt5
 \integer{xmin=randint(2..5)*randitem(1,-1)}
 \integer{xmax=\xmin+1}
 \real{grd=0.01}
 \real{x=\xmin+0.1*randint(1..9)+0.01*randint(1..9)}
#endif
#if defined TARGET_placerptB1
 \integer{xmax=randint(6..8)}
 \integer{xmin=0}
 \real{grd=0.1}
 \integer{x=randint(\xmin+1..\xmax-1)}
#endif
#if defined TARGET_placerptB2
 \integer{xmax=randint(3..5)}
 \integer{xmin=0}
 \real{grd=0.1}
 \real{x=randint(1..\xmax-1)+0.1*randint(1..9)}
#endif
#if defined TARGET_placerptB3
 \integer{n=randint(11..17)}
 \integer{xmax=\n+randint(3..5)}
 \integer{xmin=\n}
 \real{grd=0.1}
 \real{x=randint(\xmin+1..\xmax-1)}
#endif
#if defined TARGET_placerptB4
 \integer{xmax=2}
 \integer{xmin=-1}
 \real{grd=0.01}
 \integer{coeffzone=2}
 \real{x=randint(0..1)+0.1*randint(1..9)}
#endif
#if defined TARGET_placerptB5
 \integer{n=randint(11..17)}
 \integer{xmax=\n+2}
 \integer{xmin=\n}
 \real{grd=0.01}
 \real{x=\xmin+0.1*randint(1..9)+0.01*randint(1..9)}
#endif

\text{dessin=slib(draw/drtgraduee 1200,\xmin,\xmax,\grd,black,grey,40,0)}
\real{ex=1120/(\xmax-\xmin)}
\real{rep=40+\ex*(\x-\xmin)}

\text{figure=draw(1200,100
\dessin)}

\statement{\name_enonce[1] \x \name_enonce[2]:
<div class="wimscenter">\embed{r1}</div>}

\answer{\A}{\figure;circle,\rep,50,\ex*\grd*\coeffzone}{type=coord}
