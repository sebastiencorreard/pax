target=twosqr threesqr foursqr tie cube house diag pizza3 pizza4

#include "header.inc"
#include "colors.inc"
#if defined TARGET_tie
# define CONDITIONS 2
# define NUMTIT 5
# define NUMTIT1
 \integer{tot=3}
 \text{posx=-1,-1,0,1,1}
 \text{posy=1,-1,0,1,-1}
 \text{first=1,3,4}
 \text{conds=2,1,3;5,3,4}
 \text{centers=-0.5,0;0.5,0}
 \integer{xstep=120}
 \integer{ystep=80}
 \integer{xrange=1}
 \integer{yrange=1}
 \text{border=0.4}
 \text{borderline=1,2,4,5,1}
 \text{circle=}
 \integer{coeff=2}
#endif
#if defined TARGET_twosqr
# define CONDITIONS 2
# define NUMTIT 6
# define NUMTIT1
 \integer{tot=4}
 \text{posx=-2,0,2,-2,0,2}
 \text{posy=1,1,1,-1,-1,-1}
 \text{first=1,2,3,4}
 \text{conds=5,1,2,4;6,2,3,5}
 \text{centers=-0.5,0;0.5,0}
 \integer{xstep=60}
 \integer{ystep=60}
 \integer{xrange=2}
 \integer{yrange=1}
 \text{border=0.5}
 \text{borderline=1,3,6,4,1,2,5}
 \text{circle=}
 \integer{coeff=3}
#endif
#if defined TARGET_threesqr
# define CONDITIONS 3
# define NUMTIT 8
# define NUMTIT1
 \integer{tot=5}
 \text{posx=-3,-1,1,3,-3,-1,1,3}
 \text{posy=1,1,1,1,-1,-1,-1,-1}
 \text{first=1,2,3,4,5}
 \text{conds=6,1,2,5;7,2,3,6;8,3,4,7}
 \text{centers=-2,0;0,0;2,0}
 \integer{xstep=60}
 \integer{ystep=60}
 \integer{xrange=3}
 \integer{yrange=1}
 \text{border=0.5}
 \text{borderline=1,4,8,5,1,2,6,7,3}
 \text{circle=}
 \integer{coeff=3}
#endif
#if defined TARGET_foursqr
# define CONDITIONS 4
# define NUMTIT 9
# define NUMTIT1
 \integer{tot=5}
 \text{posx=-1,0,1,-1,0,1,-1,0,1}
 \text{posy=1,1,1,0,0,0,-1,-1,-1}
 \text{first=1,2,3,4,7}
 \text{conds=5,1,2,4;6,2,3,5;8,4,5,7;9,5,6,8}
 \text{centers=-0.5,0.5;0.5,0.5;-0.5,-0.5;0.5,-0.5}
 \integer{xstep=120}
 \integer{ystep=100}
 \integer{xrange=1}
 \integer{yrange=1}
 \text{border=0.3}
 \text{borderline=1,3,9,7,1,2,8,7,4,6}
 \text{circle=}
 \integer{coeff=3}
#endif
#if defined TARGET_cube
# define CONDITIONS 3
# define NUMTIT 7
# define NUMTIT1
 \integer{tot=4}
 \text{posx=-2,0,2,0,-2,0,2}
 \text{posy=1,2,1,0,-1,-2,-1}
 \text{first=1,3,4,6}
 \text{conds=2,1,3,4;5,1,4,6;7,3,4,6}
 \text{centers=0,1;-1,0;1,0}
 \integer{xstep=70}
 \integer{ystep=60}
 \integer{xrange=2}
 \integer{yrange=2}
 \text{border=0.6}
 \text{borderline=1,2,3,7,6,5,1,4,3,7,6,4}
 \text{circle=}
 \integer{coeff=3}
#endif
#if defined TARGET_house
# define CONDITIONS 4
# define NUMTIT 8
# define NUMTIT1
 \integer{tot=4}
 \text{posx=-1,1,-2,0,2,-2,0,2}
 \text{posy=1.8,2,0.4,0,0.4,-1.6,-2,-1.6}
 \text{first=3,4,5,7}
 \text{conds=1,3,4;2,1,4,5;6,3,4,7;8,4,5,7}
 \text{centers=-1,1;1,1;-1,-1;1,-1}
 \integer{xstep=70}
 \integer{ystep=60}
 \integer{xrange=2}
 \integer{yrange=2}
 \text{border=0.5}
 \text{borderline=7,8,5,2,1,3,6,7,4,1,3,4,5}
 \text{circle=}
 \integer{coeff=3}
#endif
#if defined TARGET_diag
# define CONDITIONS 4
# define NUMTIT 9
# define NUMTIT1
 \integer{tot=5}
 \text{posx=-1,0,1,-1,0,1,-1,0,1}
 \text{posy=1,1,1,0,0,0,-1,-1,-1}
 \text{first=1,3,5,7,9}
 \text{conds=2,1,3,5;4,1,5,7;6,3,5,9;8,7,5,9}
 \text{centers=0,0.5;-0.5,0;0.5,0;0,-0.5}
 \integer{xstep=120}
 \integer{ystep=100}
 \integer{xrange=1}
 \integer{yrange=1}
 \text{border=0.3}
 \text{borderline=1,3,9,7,1,9,7,3}
 \text{circle=}
 \integer{coeff=3}
#endif
#if defined TARGET_pizza3
# define CONDITIONS 3
# define NUMTIT 7
# define NUMTIT1 3
 \integer{tot=4}
 \text{posx=0,0,sqrt(3)/2,sqrt(3)/2,0,-sqrt(3)/2,-sqrt(3)/2}
 \text{posy=0,1,0.5,-0.5,-1,-0.5,0.5}
 \text{first=1,2,4,6}
 \text{conds=3,1,2,4;5,1,4,6;7,1,2,6}
 \text{centers=0.5,0;0,-0.5;-0.5,0}
 \integer{xstep=110}
 \integer{ystep=110}
 \integer{xrange=1}
 \integer{yrange=1}
 \text{border=0.2}
 \text{borderline=2,1,4,1,6}
 \text{circle=ellipse 0,0,2,2,black}
 \integer{coeff=3}
#endif
#if defined TARGET_pizza4
# define CONDITIONS 4
# define NUMTIT 9
# define NUMTIT1 4
 \integer{tot=5}
 \text{posx=0,0,0.707,1,0.707,0,-0.707,-1,-0.707}
 \text{posy=0,1,0.707,0,-0.707,-1,-0.707,0,0.707}
 \text{first=1,2,4,6,8}
 \text{conds=3,1,2,4;5,1,4,6;7,1,6,8;9,1,2,8}
 \text{centers=0.5,0.5;0.5,-0.5;-0.5,-0.5;-0.5,0.5}
 \integer{xstep=130}
 \integer{ystep=130}
 \integer{xrange=1}
 \integer{yrange=1}
 \text{border=0.2}
 \text{borderline=2,6,1,4,8}
 \text{circle=ellipse 0,0,2,2,black}
 \integer{coeff=3}
#endif
#include "lang_titles.inc"
\integer{Tot=\tot+CONDITIONS}
#include "confparm.inc"

\text{bb=wims(values 0 for x=1 to \Tot)}
\for{t=1 to \tot}
{\text{bb=wims(replace item number \first[\t] by \sh[\t] in \bb)}}

\real{sum=\smin<0?randint(\coeff*\smin..\coeff*\smax):
     (\coeff-1)*\smean+randint(2*\smean..2*\smax)}

#include "sum.inc"
#include "obj.inc"

\text{lines=lines black}
\for{i in \borderline}{
 \text{lines=\lines,\posx[\i],\posy[\i]}
}
\text{fill=}
\for{i=1 to CONDITIONS}{
 \text{fill=\fill
fill \centers[\i;],\colorlist[\i]}
}

\integer{Sizex=2*(\xrange+\border)*\xstep}
\integer{Sizey=2*(\yrange+\border)*\ystep}
\text{bigimg=draw(\Sizex,\Sizey
 xrange -\border-\xrange,\xrange+\border
 yrange -\border-\yrange,\yrange+\border
 fill 0,0,white
 linewidth 3
 \lines
 \circle
 \fill
)}

\text{posx=wims(values x*\xstep+\Sizex/2-\sizex/2 for x in \posx)}
\text{posy=wims(values -y*\ystep+\Sizey/2-\sizey/2 for y in \posy)}
\text{caselist=}
\for{i=1 to \Tot}{
 \text{caselist=\caselist
r\i,\posx[\i]x\posy[\i]}
}

\text{steps=item(1..\Tot,r1,r2,r3,r4,r5,r6,r7,r8,r9)}
\steps{\steps}

#include "lang.inc"

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

\text{r=item(1..\Tot,\r1,\r2,\r3,\r4,\r5,\r6,\r7,\r8,\r9,\r10,\r11,\r12,\r13,\r14,\r15)}
\text{R=wims(replace internal \ by in \r)}

\text{t1=\sum}
\text{t2=\sum}
\text{t3=\sum}
\text{t4=\sum}
\text{t5=\sum}
\text{t6=\sum}
\for{t=1 to 8}{
 \text{t1=\conds[1;\t] notsametext?\t1-(\R[\conds[1;\t]])}
 \text{t2=\conds[2;\t] notsametext?\t2-(\R[\conds[2;\t]])}
 \text{t3=\conds[3;\t] notsametext?\t3-(\R[\conds[3;\t]])}
 \text{t4=\conds[4;\t] notsametext?\t4-(\R[\conds[4;\t]])}
 \text{t5=\conds[5;\t] notsametext?\t5-(\R[\conds[5;\t]])}
 \text{t6=\conds[6;\t] notsametext?\t6-(\R[\conds[6;\t]])}
}
\text{t1=simplify(\t1)}
\condition{\txtsum <span style="color:\colorlist[1]">\condpre\colorname[1]\condpost</span>\txtpost
 = \sum}
 {\t1 notsametext and \t1=0}
\text{t2=simplify(\t2)}
\condition{\txtsum <span style="color:\colorlist[2]">\condpre\colorname[2]\condpost</span>\txtpost
 = \sum}
 {\t2 notsametext and \t2=0}
#if CONDITIONS > 2
\text{t3=simplify(\t3)}
\condition{\txtsum <span style="color:\colorlist[3]">\condpre\colorname[3]\condpost</span>\txtpost
 = \sum}
 {\t3 notsametext and \t3=0}
#endif
#if CONDITIONS > 3
\text{t4=simplify(\t4)}
\condition{\txtsum <span style="color:\colorlist[4]">\condpre\colorname[4]\condpost</span>\txtpost
 = \sum}
 {\t4 notsametext and \t4=0}
#endif
#if CONDITIONS > 4
\text{t5=simplify(\t5)}
\condition{\txtsum <span style="color:\colorlist[5]">\condpre\colorname[5]\condpost</span>\txtpost
 = \sum}
 {\t5 notsametext and \t5=0}
#endif
