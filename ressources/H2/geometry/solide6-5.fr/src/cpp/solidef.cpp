target=solide10 solide11 solide12

\langage{fr}
#include "author.inc"
#include "lang_titles.inc"
#include "lang.inc"
\format{html}
\matrix{som=A,B,C,D,E,F,G,H
J,K,L,M,N,O,P,Q
R,S,T,U,V,W,X,Y}
\text{som=randrow(\som)}
\text{som=shuffle(\som)}

\text{a=shuffle(3)}

\matrix{paralls=\som[1]\som[2]\som[3]\som[4],\som[5]\som[6]\som[7]\som[8]
\som[1]\som[5]\som[8]\som[4],\som[2]\som[6]\som[7]\som[3]
\som[1]\som[2]\som[6]\som[5],\som[4]\som[3]\som[7]\som[8]}

\text{\parall1=row(item(1,\a),\paralls)}
\text{\parall2=row(item(2,\a),\paralls)}
\text{\parall3=row(item(3,\a),\paralls)}
\text{parall=shuffle(\parall1)}
\text{chpars=\parall[2],\parall2[1],
\parall2[2],\parall3[1],\parall3[2]}
\text{chpar=shuffle(\chpars)}

\integer{replp=positionof(\parall[2],\chpar)}
#if defined TARGET_solide10 || defined TARGET_solide12
\integer{rep1=positionof(\parall2[1],\chpar)}
\integer{rep2=positionof(\parall2[2],\chpar)}
\integer{rep3=positionof(\parall3[1],\chpar)}
\integer{rep4=positionof(\parall3[2],\chpar)}
#endif

\integer{lo=randint(80..200)}
\integer{la=randint(50..160)}
\integer{ha=randint(20..80)}
\integer{xo=\lo+\ha}
\integer{yo=\la+\ha}
\text{pave=draw(340,300
rect 170-\xo/2,130+\yo/2,170+\xo/2-\ha,130-\yo/2+\ha,black
segment 170+\xo/2-\lo,130-\yo/2,170+\xo/2,130-\yo/2,black
segment 170+\xo/2-\lo,130-\yo/2,170+\xo/2-\lo-\ha,130-\yo/2+\ha,black
segment 170+\xo/2,130-\yo/2,170+\xo/2-\ha,130-\yo/2+\ha,black
segment 170+\xo/2,130-\yo/2,170+\xo/2,130-\yo/2+\la,black
segment 170+\xo/2-\ha,130-\yo/2+\ha+\la,170+\xo/2,130-\yo/2+\la,black
dsegment 170+\xo/2-\lo,130-\yo/2+\la,170+\xo/2,130-\yo/2+\la,black
dsegment 170+\xo/2-\lo,130-\yo/2+\la,170+\xo/2-\lo-\ha,130-\yo/2+\la+\ha,black
dsegment 170+\xo/2-\lo,130-\yo/2+\la,170+\xo/2-\lo,130-\yo/2,black

text red,170-\xo/2-8,130+\yo/2+5,medium,\som[1]
text red,170+\xo/2-\ha,130-\yo/2+\ha+\la+5,medium,\som[2]
text red,170+\xo/2-\ha+5,130-\yo/2+\ha,medium,\som[3]
text red,170+\xo/2-\lo-\ha-10,130-\yo/2+\ha-5,medium,\som[4]
text red,170+\xo/2-\lo+3,130-\yo/2+\la+3,medium,\som[5]
text red,170+\xo/2+3,130-\yo/2+\la+3,medium,\som[6]
text red,170+\xo/2+5,130-\yo/2-10,medium,\som[7]
text red,170+\xo/2-\lo-12,130-\yo/2-10,medium,\som[8]
)}

\statement{
#if defined TARGET_solide10
<div class="float_right"><img src="\pave" alt=""></div>
<ul><li> \name_enonce[1;] \parall[1]:
<div class="wimscenter">\embed{r1}</div>
</li><li> \name_enonce[2;] \parall[1]:
<div class="wimscenter">\embed{r2}</div>
</li><li> \name_enonce[3;] \parall[1]:
<div class="wimscenter">\embed{r3}</div>
</li></ul>
#endif
#if defined TARGET_solide11
<div class="float_right"><img src="\pave" alt=""></div>
 \name_enonce[1;] \parall[1] :
<div class="wimscenter">\embed{r1}</div>
#endif
#if defined TARGET_solide12
<div class="float_right"><img src="\pave" alt=""></div>
<ul><li> \name_enonce[2;] \parall[1]:
<div class="wimscenter">\embed{r1}</div>
</li><li>
 \name_enonce[3;] \parall[1]:
<div class="wimscenter">\embed{r2}</div>
</li></ul>
#endif
}
#if defined TARGET_solide10 || defined TARGET_solide11
\answer{}{\replp;\chpar[1],\chpar[2],
\chpar[3],\chpar[4],\chpar[5]}{type=radio}
#endif
#if defined TARGET_solide10 || defined TARGET_solide12
\answer{}{\rep1,\rep2,\rep3,\rep4;\chpar[1],\chpar[2],
\chpar[3],\chpar[4],\chpar[5]}{type=radio}
\answer{}{\rep1,\rep2,\rep3,\rep4;\chpar[1],\chpar[2],
\chpar[3],\chpar[4],\chpar[5]}{type=checkbox}
#endif
