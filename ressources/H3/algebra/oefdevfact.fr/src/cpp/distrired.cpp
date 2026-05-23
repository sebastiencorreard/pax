target= CORreduction CORdistribution distrired
#include "author.inc"
#include "lang_titles.inc"
\precision{10000}
#include "lang.inc"
\integer{confparm2=\confparm2=?2}
\integer{confparm1=\confparm1=?1}
\text{size=40x250x200}

\text{value=wims(values v,-v for v=1 to 10)}
\text{value=shuffle(\value)}
\text{x=random(x,y,z,a,b)}
\text{lt=wims(values v for v=0 to \confparm1)}
\text{lt=shuffle(\lt)}
\if{\confparm1=1}{
 \matrix{lt=0,1,0,1
1,0,0,1
0,1,1,0
1,0,1,0}
 \text{lt=randrow(\lt)}
}
\if{\confparm1=2}{
 \matrix{lt=0,1,2,0
0,2,1,0
1,0,2,0
1,0,0,2}
 \text{lt=randrow(\lt)}
}

\text{list=}
\for{i=1 to 4}{
 \integer{p=item(\i,\lt)}
 \integer{coef=item(\i,\value)}
 \text{m=simplify(\coef*\x^\p)}
 \text{list=wims(append item \m to \list)}
}
\text{m=\list}
\text{t1=-(\m[1]+\m[2]),(simplify(-\m[1])+\m[2])}
\text{f1=-\m[1]-\m[2],-\m[1]+\m[2]}
\text{t2=-(\m[3]+\m[4]),+(simplify(-\m[3])+\m[4])}
\text{f2=-\m[3]-\m[4],-\m[3]+\m[4]}
\text{enonces=(\t1[1]\t2[1];\f1[1]\f2[1]),(\t1[2]\t2[1];\f1[2]\f2[1]),(\t1[1]\t2[2];\f1[1]\f2[2]),(\t1[2]\t2[2];\f1[2]\f2[2])}
\text{enonces=shuffle(\enonces)}
#if defined TARGET_CORreduction  || defined TARGET_CORdistribution
\text{col1=}
\text{col2=}
\for{i=1 to 4}{
 \text{tmp=item(\i,\enonces)}
 \text{tmp=wims(declosing \tmp)}
 \text{tmp=wims(replace internal ; by , in \tmp)}
 \text{tmp1=item(1,\tmp)}
#if defined TARGET_CORreduction
 \text{res=maxima(expand(\tmp1);)}
#endif
#if defined TARGET_CORdistribution
 \text{res=item(2,\tmp)}
#endif
 \text{res=texmath(\res)}
 \text{res=\(\res)}
 \text{aff=texmath(\tmp1)}
 \text{aff=\(\aff)}
 \text{col1=wims(append item \aff to \col1)}
 \text{col2=wims(append item \res to \col2)}
}
\statement{
\name_enonce.
<div class="wimscenter">
\embed{r1,\size}
</div>
}
\answer{}{\col1;\col2}{type=correspond}
#else
\text{enonce=randitem(\enonces)}
\text{enonce=wims(declosing \enonce)}
\text{enonce=wims(replace internal ; by , in \enonce)}
\text{res=item(2,\enonce)}
\text{rep=maxima(expand(\res);)}
\text{enonce=item(1,\enonce)}
\text{A=randitem(A,B,C,D)}

\statement{
\name_enonce
<div class="wimscenter">\(\A = \enonce)</div>}
\reply{\(\A\)}{\rep}{type=litexp}{option=polexpand}

#endif
