target=pyramid1 pyramid1b pyramid1c pyramid1d pyramid2 pyramid2b pyramid3

#include "header.inc"
#if defined TARGET_pyramid1
# define CONDITIONS 1
# define NUMTIT 3
# define NUMTIT1 I
 \text{stage=1}
 \text{base=1}
#endif
#if defined TARGET_pyramid1b
# define CONDITIONS 2
# define NUMTIT 5
# define NUMTIT1 Ib
 \text{stage=1}
 \text{base=2}
#endif
#if defined TARGET_pyramid1c
# define CONDITIONS 3
# define NUMTIT 7
# define NUMTIT1 Ic
 \text{stage=1}
 \text{base=3}
#endif
#if defined TARGET_pyramid1d
# define CONDITIONS 4
# define NUMTIT 9
# define NUMTIT1 Id
 \text{stage=1}
 \text{base=4}
#endif
#if defined TARGET_pyramid2
# define CONDITIONS 3
# define NUMTIT 6
# define NUMTIT1 II
 \text{stage=2}
 \text{base=2}
#endif
#if defined TARGET_pyramid2b
# define CONDITIONS 5
# define NUMTIT 9
# define NUMTIT1 IIb
 \text{stage=2}
 \text{base=3}
#endif
#if defined TARGET_pyramid3
# define CONDITIONS 6
# define NUMTIT ~10
# define NUMTIT1 III
 \text{stage=3}
 \text{base=3}
#endif
#include "lang_titles.inc"
\integer{tot=\base+1}
#include "confparm.inc"
\integer{Tot=(\stage+1)*(\stage+2)/2+(\base-\stage)*(\stage+1)}
\text{posx=}
\text{posy=}
\text{lcolor=black}
\text{py=segment 0,\stage,(\base-\stage),\stage,\lcolor}
\integer{next=1}
\text{conds=}
\for{yy=\stage..0 step -1}{
 \integer{this=\next}
 \integer{next=\next+\base-\yy+1}
 \text{py=\yy<\stage?\py
polygon \lcolor,0,\yy}
 \for{xx=0..\base-\yy}{
  \text{conds=\yy>0?\conds \this+\xx,\next+\xx,\next+\xx+1;}
  \text{py=\xx>0 and \yy<\stage?\py,\xx-1,\yy+1,\xx,\yy}
  \text{posx=\posx\xx,}
  \text{posy=\posy\yy,}
 }
 \text{py=\py
segment 0,\yy,\base-\yy,\yy}
}

\text{bb=wims(values 0 for x=1 to \Tot)}
\for{t=1..\tot}{
 \text{bb=wims(replace item number \Tot-\t+1 by \sh[\t] in \bb)}
}
\integer{condcnt=rows(\conds)}
\for{c=\condcnt to 1 step -1}{
 \if{\randtype issametext computed}{
  \real{sum=(\bb[\conds[\c;2]])+(\bb[\conds[\c;3]])}
 }{
  \text{sum=maxima(expand((\bb[\conds[\c;2]])+(\bb[\conds[\c;3]])))}
 }
 \text{bb=wims(replace item number \conds[\c;1] by \sum in \bb)}
}

#include "obj.inc"

\text{border=0.2}
\integer{xstep=150}
\integer{ystep=100}
\integer{Sizex=(\base+\border*2)*\xstep}
\integer{Sizey=(\stage+\border*2)*\ystep}
\text{bigimg=draw(\Sizex,\Sizey
 xrange -\border,\base+\border
 yrange -\border,\stage+\border
 fill 0,0,white
 linewidth 3
 linear 1,0.5,0,1
 \py
)}

\text{px=}
\for{t=1..\Tot}{\text{px=wims(append item \posx[\t]+\posy[\t]*0.5 to \px)}}
\text{posx=wims(values (x+\border)*\xstep-\sizex/2 for x in \px)}
\text{posy=wims(values (\border+\stage-y)*\ystep-\sizey/2 for y in \posy)}
\text{caselist=}
\for{i=1 to \Tot}{
 \text{caselist=\caselist
r\i,\posx[\i]x\posy[\i]}
}
#include "lang.inc"
\text{steps=item(1..\Tot,r1,r2,r3,r4,r5,r6,r7,r8,r9,r10,r11,r12,r13,r14,r15)}
\steps{\steps}

\statement{\txtstatement
<div class="wimscenter">
 \special{imagefill \bigimg,\Sizex \Sizey,\size
\caselist
}
</div>
}

\answer{\txtbox 1}{\r1;\obj[1]\redund}{type=dragfill}
\answer{\txtbox 2}{\r2;\obj[2]}{type=dragfill}
\answer{\txtbox 3}{\r3;\obj[3]}{type=dragfill}
\answer{\txtbox 4}{\r4;\obj[4]}{type=dragfill}
\answer{\txtbox 5}{\r5;\obj[5]}{type=dragfill}
\answer{\txtbox 6}{\r6;\obj[6]}{type=dragfill}
\answer{\txtbox 7}{\r7;\obj[7]}{type=dragfill}
\answer{\txtbox 8}{\r8;\obj[8]}{type=dragfill}
\answer{\txtbox 9}{\r9;\obj[9]}{type=dragfill}
\answer{\txtbox 10}{\r10;\obj[10]}{type=dragfill}

\text{r=item(1..\Tot,\r1,\r2,\r3,\r4,\r5,\r6,\r7,\r8,\r9,\r10,\r11,\r12,\r13,\r14,\r15)}
\text{R=wims(replace internal \ by in \r)}

\text{t1=simplify((\R[\conds[1;1]])-(\R[\conds[1;2]])-(\R[\conds[1;3]]))}
\text{p1=\r[\conds[1;3]]}
\text{p1=- isin \p1?(\p1)}
\condition{\r[\conds[1;1]] = \r[\conds[1;2]] + \p1}
 {\t1 notsametext and \t1=0}
#if CONDITIONS > 1
\text{t2=simplify((\R[\conds[2;1]])-(\R[\conds[2;2]])-(\R[\conds[2;3]]))}
\text{p2=\r[\conds[2;3]]}
\text{p2=- isin \p2?(\p2)}
\condition{\r[\conds[2;1]] = \r[\conds[2;2]] + \p2}
 {\t2 notsametext and \t2=0}
#endif
#if CONDITIONS > 2
\text{p3=\r[\conds[3;3]]}
\text{p3=- isin \p3?(\p3)}
\text{t3=simplify((\R[\conds[3;1]])-(\R[\conds[3;2]])-(\R[\conds[3;3]]))}
\condition{\r[\conds[3;1]] = \r[\conds[3;2]] + \p3}
 {\t3 notsametext and \t3=0}
#endif
#if CONDITIONS > 3
\text{p4=\r[\conds[4;3]]}
\text{p4=- isin \p4?(\p4)}
\text{t4=simplify((\R[\conds[4;1]])-(\R[\conds[4;2]])-(\R[\conds[4;3]]))}
\condition{\r[\conds[4;1]] = \r[\conds[4;2]] + \p4}
 {\t4 notsametext and \t4=0}
#endif
#if CONDITIONS > 4
\text{p5=\r[\conds[5;3]]}
\text{p5=- isin \p5?(\p5)}
\text{t5=simplify((\R[\conds[5;1]])-(\R[\conds[5;2]])-(\R[\conds[5;3]]))}
\condition{\r[\conds[5;1]] = \r[\conds[5;2]] + \p5}
 {\t5 notsametext and \t5=0}
#endif
#if CONDITIONS > 5
\text{p6=\r[\conds[6;3]]}
\text{p6=- isin \p6?(\p6)}
\text{t6=simplify((\R[\conds[6;1]])-(\R[\conds[6;2]])-(\R[\conds[6;3]]))}
\condition{\r[\conds[6;1]] = \r[\conds[6;2]] + \p6}
 {\t6 notsametext and \t6=0}
#endif
