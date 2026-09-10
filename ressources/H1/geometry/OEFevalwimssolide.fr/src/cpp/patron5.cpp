target=oefpatron5

#include "author.inc"
#include "lang_titles.inc"
#include "lang.inc"
\integer{ha=randint(20..75)}
\integer{la=randint(30..100-\ha)}
\integer{long=randint(\la+20..270-2*\la)}
\integer{lo=\long}
\integer{x1=(400-\lo-2*\ha)/2}
\integer{y1=150+\la+\ha}

\text{patron=draw(400,300
rect \x1+\ha,\y1,\x1+\ha+\lo,\y1-\la,black
rect \x1+\ha+\lo,\y1-\la,\x1+\ha,\y1-\la-\ha,black
rect \x1+\ha,\y1-\la-\ha,\x1,\y1-\ha-2*\la,black
rect \x1+\ha,\y1-\la-\ha,\x1+\ha+\lo,\y1-\ha-2*\la,black
rect \x1+\ha+\lo,\y1-\ha-2*\la,\x1+2*\ha+\lo,\y1-\ha-\la,black
rect \x1+\ha+\lo,\y1-\ha-2*\la,\x1+\ha,\y1-2*\la-2*\ha,black
)}

\integer{hb=\ha/2}
\integer{lb=\la}
\integer{xo=\lo+\hb}
\integer{yo=\lb+\hb}

\text{pave1=draw(300,260
rect 150-\xo/2,110+\yo/2,150+\xo/2-\hb,110-\yo/2+\hb,black
segment 150+\xo/2-\lo,110-\yo/2,150+\xo/2,110-\yo/2,black
segment 150+\xo/2-\lo,110-\yo/2,150+\xo/2-\lo-\hb,110-\yo/2+\hb,black
segment 150+\xo/2,110-\yo/2,150+\xo/2-\hb,110-\yo/2+\hb,black
segment 150+\xo/2,110-\yo/2,150+\xo/2,110-\yo/2+\lb,black
segment 150+\xo/2-\hb,110-\yo/2+\hb+\lb,150+\xo/2,110-\yo/2+\lb,black
dsegment 150+\xo/2-\lo,110-\yo/2+\lb,150+\xo/2,110-\yo/2+\lb,black
dsegment 150+\xo/2-\lo,110-\yo/2+\lb,150+\xo/2-\lo-\hb,110-\yo/2+\lb+\hb,black
dsegment 150+\xo/2-\lo,110-\yo/2+\lb,150+\xo/2-\lo,110-\yo/2,black
)}

\integer{hc=\la/2}
\integer{lc=\la}
\integer{lo=\la}
\integer{xo=\lo+\hc}
\integer{yo=\lc+\hc}

\text{pave2=draw(300,260
rect 150-\xo/2,110+\yo/2,150+\xo/2-\hc,110-\yo/2+\hc,black
segment 150+\xo/2-\lo,110-\yo/2,150+\xo/2,110-\yo/2,black
segment 150+\xo/2-\lo,110-\yo/2,150+\xo/2-\lo-\hc,110-\yo/2+\hc,black
segment 150+\xo/2,110-\yo/2,150+\xo/2-\hc,110-\yo/2+\hc,black
segment 150+\xo/2,110-\yo/2,150+\xo/2,110-\yo/2+\lc,black
segment 150+\xo/2-\hc,110-\yo/2+\hc+\lc,150+\xo/2,110-\yo/2+\lc,black
dsegment 150+\xo/2-\lo,110-\yo/2+\lc,150+\xo/2,110-\yo/2+\lc,black
dsegment 150+\xo/2-\lo,110-\yo/2+\lc,150+\xo/2-\lo-\hc,110-\yo/2+\lc+\hc,black
dsegment 150+\xo/2-\lo,110-\yo/2+\lc,150+\xo/2-\lo,110-\yo/2,black
)}

\integer{lo=\long}
\integer{hd=\lo/2}
\if{\hd>\ha/2-15 and \hd<\ha/2+15}{\integer{hd=\ha/2+20}}
\integer{ld=\la}
\integer{xo=\lo+\hd}
\integer{yo=\ld+\hd}

\text{pave3=draw(300,260
rect 150-\xo/2,110+\yo/2,150+\xo/2-\hd,110-\yo/2+\hd,black
segment 150+\xo/2-\lo,110-\yo/2,150+\xo/2,110-\yo/2,black
segment 150+\xo/2-\lo,110-\yo/2,150+\xo/2-\lo-\hd,110-\yo/2+\hd,black
segment 150+\xo/2,110-\yo/2,150+\xo/2-\hd,110-\yo/2+\hd,black
segment 150+\xo/2,110-\yo/2,150+\xo/2,110-\yo/2+\ld,black
segment 150+\xo/2-\hd,110-\yo/2+\hd+\ld,150+\xo/2,110-\yo/2+\ld,black
dsegment 150+\xo/2-\lo,110-\yo/2+\ld,150+\xo/2,110-\yo/2+\ld,black
dsegment 150+\xo/2-\lo,110-\yo/2+\ld,150+\xo/2-\lo-\hd,110-\yo/2+\ld+\hd,black
dsegment 150+\xo/2-\lo,110-\yo/2+\ld,150+\xo/2-\lo,110-\yo/2,black
)}
\text{pave=\pave1,\pave2,\pave3}
\text{a=shuffle(3)}
\text{affich=<img src="\pave[\a[1]]" alt="">,<img src="\pave[\a[2]]" alt="">,
  <img src="\pave[\a[3]]" alt="">}
\for{i=1 to 3}
      {\if{\a[\i]=1}{\integer{rep=\i}}}

\statement{
\name_enonce:
<div class="wimscenter"><img src="\patron" alt=""></div>
\name_question:
<div>\embed{r1}</div>
}

\answer{}{\rep;\affich}{type=click}
