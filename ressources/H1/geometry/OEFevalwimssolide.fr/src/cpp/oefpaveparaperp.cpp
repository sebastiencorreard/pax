target=oefpaveparaperp1 oefpaveparaperp2 oefpaveparaperp3 oefpaveparaperp4
#include "author.inc"
#include "lang_titles.inc"
#include "lang.inc"

\matrix{som=A,B,C,D,E,F,G,H
J,K,L,M,N,O,P,Q
R,S,T,U,V,W,X,Y}
\text{som=randrow(\som)}
\text{som=shuffle(\som)}
\text{a=shuffle(3)}

#if defined TARGET_oefpaveparaperp1
\integer{b=randint(1..3)}
\integer{c=randint(1..3)}
\matrix{paralls=[\som[1]\som[4]],[\som[5]\som[8]],[\som[2]\som[3]],[\som[6]\som[7]]
[\som[1]\som[5]],[\som[2]\som[6]],[\som[4]\som[8]],[\som[3]\som[7]]
[\som[1]\som[2]],[\som[5]\som[6]],[\som[7]\som[8]],[\som[3]\som[4]]}
\text{\parall1=row(item(1,\a),\paralls)}
\text{\parall2=row(item(2,\a),\paralls)}
\text{\parall3=row(item(3,\a),\paralls)}
\text{parall=shuffle(\parall1)}
\text{chpars=\parall[2],\parall[4],
\parall2[1],\parall2[1+\b],\parall3[1],\parall3[1+\b]}
\text{chp=shuffle(\chpars)}
\integer{rep1=positionof(\parall[2],\chp)}
\integer{rep2=positionof(\parall[4],\chp)}
\text{enonc=un côté parallèle au côté}
\text{quest=\parall[1]}
#endif
#if defined TARGET_oefpaveparaperp2
\matrix{paralls=\som[1]\som[2]\som[3]\som[4],\som[5]\som[6]\som[7]\som[8]
\som[1]\som[5]\som[8]\som[4],\som[2]\som[6]\som[7]\som[3]
\som[1]\som[2]\som[6]\som[5],\som[4]\som[3]\som[7]\som[8]}

\text{\parall1=row(item(1,\a),\paralls)}
\text{\parall2=row(item(2,\a),\paralls)}
\text{\parall3=row(item(3,\a),\paralls)}
\text{parall=shuffle(\parall1)}
\text{chpars=\parall[2],\parall2[1],
\parall2[2],\parall3[1],\parall3[2]}
\text{chp=shuffle(\chpars)}
\integer{rep1=positionof(\parall[2],\chp)}
\text{enonc=une face parallèle à la face}
\text{quest=\parall[1]}
#endif
#if defined TARGET_oefpaveparaperp3
\matrix{paralls=\som[1]\som[4],\som[5]\som[8],\som[2]\som[3],\som[6]\som[7]
\som[1]\som[5],\som[2]\som[6],\som[4]\som[8],\som[3]\som[7]
\som[1]\som[2],\som[5]\som[6],\som[7]\som[8],\som[3]\som[4]}

\text{cot=}
\for{i=1 to 3}{
\text{cot=row(\i,\paralls),\cot}}
\text{cot=shuffle(\cot)}
\text{quest=\cot[1]}
\text{som1=wims(char 1 to 1 of \quest)}
\text{som2=wims(char 2 to 2 of \quest)}
\text{somp=}
\for{i=1 to 8}{
\if{\som[\i]<>\som1 and \som[\i]<>\som2}
{\text{somp=wims(append item \som[\i] to \somp)}}
}

\text{reppj=}
\text{reppf=}
\for{i=2 to 12}{
\if{\som1=wims(char 1 to 1 of \cot[\i]) or
\som1=wims(char 2 to 2 of \cot[\i]) or
\som2=wims(char 1 to 1 of \cot[\i]) or
\som2=wims(char 2 to 2 of \cot[\i])}
{\text{reppj=wims(append item \cot[\i] to \reppj)}}
{\text{reppf=wims(append item \cot[\i] to \reppf)}}
}

\text{reppj=shuffle(\reppj)}
\text{reppf=shuffle(\reppf)}

\text{chpers=\reppj[2],\reppj[3],
\reppf[2],\reppf[4],\reppf[5],\reppf[6]}
\text{chp=shuffle(\chpers)}
\integer{rep1=positionof(\reppj[2],\chp)}
\integer{rep2=positionof(\reppj[3],\chp)}
\text{enonc=un côté perpendiculaire au côté}
#endif
#if defined TARGET_oefpaveparaperp4
\matrix{paralls=\som[1]\som[2]\som[3]\som[4],\som[5]\som[6]\som[7]\som[8]
\som[1]\som[5]\som[8]\som[4],\som[2]\som[6]\som[7]\som[3]
\som[1]\som[2]\som[6]\som[5],\som[4]\som[3]\som[7]\som[8]}

\text{\parall1=row(item(1,\a),\paralls)}
\text{\parall2=row(item(2,\a),\paralls)}
\text{\parall3=row(item(3,\a),\paralls)}
\text{parall=shuffle(\parall1)}
\text{chpars=\parall[2],\parall2[1],
\parall2[2],\parall3[1],\parall3[2]}
\text{chp=shuffle(\chpars)}

\integer{rep1=positionof(\parall2[1],\chp)}
\integer{rep2=positionof(\parall2[2],\chp)}
\integer{rep3=positionof(\parall3[1],\chp)}
\integer{rep4=positionof(\parall3[2],\chp)}
\text{enonc=une face perpendiculaire à la face}
\text{quest=\parall[1]}
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

\statement{ <div class="wims_columns">
 <div class="medium_size img_col"><img src="\pave" alt=""></div>
 <div class="medium_size text_col">
 \name_give \enonc \quest:
<div>\embed{r1}</div></div></div>
}

\answer{}{\rep1,\rep2,\rep3,\rep4;\chp[1],\chp[2],\chp[3],\chp[4],\chp[5],\chp[6]}{type=radio}
