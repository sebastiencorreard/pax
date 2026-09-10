target=triangle bigsquare cross stool IXI grill H M V W asterisk pentagon

#include "header.inc"
#include "colors.inc"
#if defined TARGET_triangle
# define CONDITIONS 3
# define NUMTIT 6
# define NUMTIT1
 \integer{tot=3}
 \integer{Tot=6}
 \text{posx=0,-1,1,-2,0,2}
 \text{posy=1,0,0,-1,-1,-1}
 \text{first=1,4,6}
 \text{conds=2,1,4;3,1,6;5,4,6}
 \integer{xstep=60}
 \integer{ystep=80}
 \integer{xrange=2}
 \integer{yrange=1}
#endif
#if defined TARGET_bigsquare
# define CONDITIONS 4
# define NUMTIT 8
# define NUMTIT1
 \integer{tot=4}
 \integer{Tot=8}
 \text{posx=-1,0,1,-1,1,-1,0,1}
 \text{posy=1,1,1,0,0,-1,-1,-1}
 \text{first=1,3,6,8}
 \text{conds=2,1,3;4,1,6;5,3,8;7,6,8}
 \integer{xstep=120}
 \integer{ystep=80}
 \integer{xrange=1}
 \integer{yrange=1}
#endif
#if defined TARGET_cross
# define CONDITIONS 2
# define NUMTIT 5
# define NUMTIT1
 \integer{tot=3}
 \integer{Tot=5}
 \text{posx=-1,1,0,-1,1}
 \text{posy=1,1,0,-1,-1}
 \text{first=1,2,3}
 \text{conds=5,1,3;4,2,3}
 \integer{xstep=100}
 \integer{ystep=75}
 \integer{xrange=1}
 \integer{yrange=1}
#endif
#if defined TARGET_V
# define CONDITIONS 2
# define NUMTIT 5
# define NUMTIT1
 \integer{tot=3}
 \integer{Tot=5}
 \text{posx=-2,-1,0,1,2}
 \text{posy=1,0,-1,0,1}
 \text{first=2,3,4}
 \text{conds=1,2,3;5,4,3}
 \integer{xstep=65}
 \integer{ystep=80}
 \integer{xrange=2}
 \integer{yrange=1}
#endif
#if defined TARGET_stool
# define CONDITIONS 3
# define NUMTIT 6
# define NUMTIT1
 \integer{tot=3}
 \integer{Tot=6}
 \text{posx=-1,0,1,0,-1,1}
 \text{posy=1,1,1,0,-1,-1}
 \text{first=1,3,4}
 \text{conds=2,1,3;6,1,4;5,3,4}
 \integer{xstep=110}
 \integer{ystep=75}
 \integer{xrange=1}
 \integer{yrange=1}
#endif
#if defined TARGET_IXI
# define CONDITIONS 3
# define NUMTIT 7
# define NUMTIT1
 \integer{tot=3}
 \integer{Tot=7}
 \text{posx=1,1,1,0,-1,-1,-1}
 \text{posy=-1,0,1,0,-1,0,1}
 \text{first=1,3,4}
 \text{conds=2,1,3;7,1,4;5,3,4;6,5,7}
 \integer{xstep=120}
 \integer{ystep=80}
 \integer{xrange=1}
 \integer{yrange=1}
#endif
#if defined TARGET_H
# define CONDITIONS 3
# define NUMTIT 7
# define NUMTIT1
 \integer{tot=4}
 \integer{Tot=7}
 \text{posx=-1,-1,-1,0,1,1,1}
 \text{posy=1,0,-1,0,1,0,-1}
 \text{first=1,2,4,5}
 \text{conds=3,1,2;6,2,4;7,5,6}
 \integer{xstep=120}
 \integer{ystep=100}
 \integer{xrange=1}
 \integer{yrange=1}
#endif
#if defined TARGET_M
# define CONDITIONS 4
# define NUMTIT 9
# define NUMTIT1
 \integer{tot=5}
 \integer{Tot=9}
 \text{posx=-4,-3,-2,-1,0,1,2,3,4}
 \text{posy=-1,0,1,0,-1,0,1,0,-1}
 \text{first=1,2,4,6,8}
 \text{conds=3,2,1;5,4,3;7,6,5;9,8,7}
 \integer{xstep=60}
 \integer{ystep=80}
 \real{xrange=4.2}
 \integer{yrange=1}
#endif
#if defined TARGET_W
# define CONDITIONS 4
# define NUMTIT 9
# define NUMTIT1
 \integer{tot=5}
 \integer{Tot=9}
 \text{posx=-3,-2,-1,1,0,-1,1,2,3}
 \text{posy=1,0,-1,1,0,1,-1,0,1}
 \text{first=1,2,4,6,8}
 \text{conds=3,2,1;5,4,3;7,6,5;9,8,7}
 \integer{xstep=60}
 \integer{ystep=80}
 \real{xrange=3.2}
 \integer{yrange=1}
#endif
#if defined TARGET_asterisk
# define CONDITIONS 3
# define NUMTIT 7
# define NUMTIT1
 \integer{tot=4}
 \integer{Tot=7}
 \text{posx=0,-1,1,-2,2,-1,1}
 \text{posy=0,1,1,0,0,-1,-1}
 \text{first=1,2,3,4}
 \text{conds=5,1,4;6,1,3;7,1,2}
 \integer{xstep=65}
 \integer{ystep=100}
 \integer{xrange=2}
 \integer{yrange=1}
#endif
#if defined TARGET_grill
# define CONDITIONS 4
# define NUMTIT 8
# define NUMTIT1
 \integer{tot=4}
 \integer{Tot=8}
 \text{posx=-2,0,2,-1,1,-2,0,2}
 \text{posy=1,1,1,0,0,-1,-1,-1}
 \text{first=2,4,5,7}
 \text{conds=1,4,7;6,4,2;8,2,5;3,5,7}
 \integer{xstep=70}
 \integer{ystep=70}
 \integer{xrange=2}
 \integer{yrange=1}
#endif
#if defined TARGET_pentagon
# define CONDITIONS 5
# define NUMTIT ~10
# define NUMTIT1
 \integer{tot=5}
 \integer{Tot=10}
 \text{posx=wims(values sin(n*pi/5)*cos((n%2)*pi/5) for n=0 to 9)}
 \text{posy=wims(values cos(n*pi/5)*cos((n%2)*pi/5) for n=0 to 9)}
 \text{first=1,3,5,7,9}
 \text{conds=2,1,3;4,3,5;6,5,7;8,7,9;10,9,1}
 \integer{xstep=150}
 \integer{ystep=150}
 \integer{xrange=1}
 \integer{yrange=1}
#endif
#include "lang_titles.inc"
#include "confparm.inc"

\text{bb=wims(values 0 for x=1 to \Tot)}
\for{t=1 to \tot}
{\text{bb=wims(replace item number \first[\t] by \sh[\t] in \bb)}}

\real{sum=\smin<0?randint(2*\smin..2*\smax):\smean+randint(2*\smean..2*\smax)}

#include "sum.inc"
#include "obj.inc"

\text{py=}
\for{t=1 to \condcnt}{
 \text{cond=\conds[\t;]}
 \text{py=\py
lines \colorlist[\t],\posx[\cond[1]],\posy[\cond[1]],\posx[\cond[2]],\posy[\cond[2]],\posx[\cond[3]],\posy[\cond[3]]
}
}

\text{border=0.3}
\integer{Sizex=2*(\xrange+\border)*\xstep}
\integer{Sizey=2*(\yrange+\border)*\ystep}
\text{bigimg=draw(\Sizex,\Sizey
 xrange -\border-\xrange,\xrange+\border
 yrange -\border-\yrange,\yrange+\border
 fill 0,0,white
 linewidth 3
 \py
)}

\text{posx=wims(values x*\xstep+\Sizex/2-\sizex/2 for x in \posx)}
\text{posy=wims(values -y*\ystep+\Sizey/2-\sizey/2 for y in \posy)}
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

\text{t1=simplify(\sum-(\R[\conds[1;1]])-(\R[\conds[1;2]])-(\R[\conds[1;3]]))}
\condition{\txtsum <span style="color:\colorlist[1]">\condpre\colorname[1]\condpost</span>
 = \sum}
 {\t1 notsametext and \t1=0}
\text{t2=simplify(\sum-(\R[\conds[2;1]])-(\R[\conds[2;2]])-(\R[\conds[2;3]]))}
\condition{\txtsum <span style="color:\colorlist[2]">\condpre\colorname[2]\condpost</span>
 = \sum}
 {\t2 notsametext and \t2=0}
#if CONDITIONS > 2
\text{t3=simplify(\sum-(\R[\conds[3;1]])-(\R[\conds[3;2]])-(\R[\conds[3;3]]))}
\condition{\txtsum <span style="color:\colorlist[3]">\condpre\colorname[3]\condpost</span>
 = \sum}
 {\t3 notsametext and \t3=0}
#endif
#if CONDITIONS > 3
\text{t4=simplify(\sum-(\R[\conds[4;1]])-(\R[\conds[4;2]])-(\R[\conds[4;3]]))}
\condition{\txtsum <span style="color:\colorlist[4]">\condpre\colorname[4]\condpost</span>
 = \sum}
 {\t4 notsametext and \t4=0}
#endif
#if CONDITIONS > 4
\text{t5=simplify(\sum-(\R[\conds[5;1]])-(\R[\conds[5;2]])-(\R[\conds[5;3]]))}
\condition{\txtsum <span style="color:\colorlist[5]">\condpre\colorname[5]\condpost</span>
 = \sum}
 {\t5 notsametext and \t5=0}
#endif
