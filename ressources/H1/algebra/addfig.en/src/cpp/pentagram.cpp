target=pentagram

#include "header.inc"
#include "colors.inc"

#define CONDITIONS 5
#define NUMTIT ~10
#define NUMTIT1
#include "lang_titles.inc"
\integer{tot=5}
\text{posx=wims(values sin(2*n*pi/5) for n=0 to 4),
	wims(values -sin(2*n*pi/5)*0.381966 for n=0 to 4)}
\text{posy=wims(values cos(2*n*pi/5)-0.1 for n=0 to 4),
	wims(values -cos(2*n*pi/5)*0.381966-0.1 for n=0 to 4)}
\integer{xstep=200}
\integer{ystep=200}
\integer{xrange=1}
\integer{yrange=1}
\real{border=0.07}

\integer{Tot=\tot + CONDITIONS}

#include "confparm.inc"

\text{bb=wims(values 0 for x=1 to 15)}
\for{t=1 to \tot}
{
    \text{bb=wims(replace item number \t by \sh[\t] in \bb)}
    \text{bb=wims(replace item number \t+10 by -(\sh[\t]) in \bb)}
}
\integer{sum=\smin<0?randint(\smin..\smax):\smean+randint(\smean..\smax)}
\text{conds=6,3,4,11;7,4,5,12;8,1,5,13;9,1,2,14;10,2,3,15}

#include "sum.inc"
#include "obj.inc"

\integer{sum=\sum*2}
\text{bb=\bb[1..10]}
\text{conds=1,3,9,10;3,5,6,7;2,5,8,9;2,4,6,10;1,4,7,8}
\text{bl=1,3,5,2,4,1}
\text{lines=}
\for{i=1 to 5}{
 \text{lines=\lines
segment \posx[\bl[\i]],\posy[\bl[\i]],\posx[\bl[\i+1]],\posy[\bl[\i+1]],\colorlist[\i]}
}

\integer{Sizex=2*(\xrange+\border)*\xstep}
\integer{Sizey=2*(\yrange+\border)*\ystep}
\text{bigimg=draw(\Sizex,\Sizey
 xrange -\border-\xrange,\xrange+\border
 yrange -\border-\yrange,\yrange+\border
 fill 0,0,white
 linewidth 3
 \lines
)}

\text{posx=wims(values x*\xstep+\Sizex/2-\sizex/2 for x in \posx)}
\text{posy=wims(values -y*\ystep+\Sizey/2-\sizey/2 for y in \posy)}
\text{caselist=}
\for{i=1 to \Tot}{
 \text{caselist=\caselist
r\i,\posx[\i]x\posy[\i]}
}

\text{steps=item(1..\Tot,r1,r2,r3,r4,r5,r6,r7,r8,r9,r10,r11,r12,r13,r14,r15)}
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
\answer{\txtbox 10}{\r10;\obj[10]}{type=dragfill}

\text{r=item(1..\Tot,\r1,\r2,\r3,\r4,\r5,\r6,\r7,\r8,\r9,\r10,\r11,\r12,\r13,\r14,\r15)}
\text{R=wims(replace internal \ by in \r)}

\text{t1=simplify(\sum-(\R[\conds[1;1]])-(\R[\conds[1;2]])-(\R[\conds[1;3]])-(\R[\conds[1;4]]))}
\condition{\txtsum <span style="color:\colorlist[1]">\condpre\colorname[1]\condpost</span>\txtpost
 = \sum}
 {\t1 notsametext and \t1=0}
\text{t2=simplify(\sum-(\R[\conds[2;1]])-(\R[\conds[2;2]])-(\R[\conds[2;3]])-(\R[\conds[2;4]]))}
\condition{\txtsum <span style="color:\colorlist[2]">\condpre\colorname[2]\condpost</span>\txtpost
 = \sum}
 {\t2 notsametext and \t2=0}
\text{t3=simplify(\sum-(\R[\conds[3;1]])-(\R[\conds[3;2]])-(\R[\conds[3;3]])-(\R[\conds[3;4]]))}
\condition{\txtsum <span style="color:\colorlist[3]">\condpre\colorname[3]\condpost</span>\txtpost
 = \sum}
 {\t3 notsametext and \t3=0}
\text{t4=simplify(\sum-(\R[\conds[4;1]])-(\R[\conds[4;2]])-(\R[\conds[4;3]])-(\R[\conds[4;4]]))}
\condition{\txtsum <span style="color:\colorlist[4]">\condpre\colorname[4]\condpost</span>\txtpost
 = \sum}
 {\t4 notsametext and \t4=0}
\text{t5=simplify(\sum-(\R[\conds[5;1]])-(\R[\conds[5;2]])-(\R[\conds[5;3]])-(\R[\conds[5;4]]))}
\condition{\txtsum <span style="color:\colorlist[5]">\condpre\colorname[5]\condpost</span>\txtpost
 = \sum}
 {\t5 notsametext and \t5=0}
