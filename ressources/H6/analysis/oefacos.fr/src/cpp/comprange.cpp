target=comprange

#include "author.inc"
#include "lang_titles.inc"
#include "lang.inc"
\computeanswer{no}
\precision{10000}

\text{flist=arccos(cos(x)),arcsin(sin(x)),arccos(sin(x)),arcsin(cos(x)),cos(arccos(x)),
	sin(arcsin(x)),cos(arcsin(x)),sin(arccos(x)),cos(-arcsin(x)),sin(-arccos(x)),
	tg(arctg(x)),arctg(sin(x))}
\text{alist=-F,-F,-F,-F,-1,	-1,-1,-1,-1,-1,
	-F,-F,}
\text{blist=F,F,F,F,1,1,1,1,1,1,
	F,F,}
\text{clist=0,-pi/2,0,-pi/2,-1,	-1,0,0,0,-1,
	-F,-pi/4,}
\text{dlist=pi,pi/2,pi,pi/2,1,	1,1,1,1,0,
	F,pi/4,
}
\integer{fcnt=random(1..items(\flist))}
\text{f=item(\fcnt,\flist)}
\text{a=item(\fcnt,\alist)}
\text{b=item(\fcnt,\blist)}
\text{c=item(\fcnt,\clist)}
\text{d=item(\fcnt,\dlist)}

\statement{\name_enonce[1] \(f(x) = \f\). \name_enonce[2]
<div class="wims_instruction">
\name_instruction
\(\pi\), \(\infty) \name_or \(-\infty\).
</div>}

\answer{\(a\)}{\a,F}
\answer{\(b\)}{\b,F}
\answer{\(c\)}{\c,F}
\answer{\(d\)}{\d,F}
