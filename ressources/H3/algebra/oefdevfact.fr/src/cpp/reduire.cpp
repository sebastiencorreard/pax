target=reduire reduire2

#include "author.inc"
#include "lang_titles.inc"
#include "lang.inc"
\precision{10000}

\integer{confparm2=\confparm2=?2}
\integer{confparm1=\confparm1=?1}
\integer{confparm1=\confparm1>4?4}

\integer{size=\confparm1*8}
#if defined TARGET_reduire
\integer{nombremax=2}
\integer{nmin=1}
#endif
#if defined TARGET_reduire2
\integer{nombremax=3}
\integer{nmin=2}
#endif
\text{x=random(x,y,z,a,b)}

\text{lt=wims(values v for v=0 to \confparm1)}

\text{enonce=}
\for{p=0 to \confparm1}{
 \integer{nombre=random(\nmin..\nombremax)}
 \for{th=1 to \nombre}{
  \integer{a=randitem(-1,1)*randint(2..10)}
  \text{v=(simplify(\a*\x^\p))}
  \text{enonce=wims(append item \v to \enonce)}
 }
}
\text{enonce=shuffle(\enonce)}
\text{enonce=wims(replace internal , by + in \enonce)}
\text{rep=maxima(\enonce;)}
\text{rep=slib(commutesom \rep,\x)}
\text{enonce=texmath(\enonce)}

\statement{
\name_enonce \(\enonce\).
<div class="wimscenter">
<label for="reply1"> \(\enonce = \)</label> \embed{r1,\size}
</div>}

\answer{\name_answer 1}{\rep}{type=litexp}
