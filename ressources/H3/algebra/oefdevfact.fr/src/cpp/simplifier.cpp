target=simplifier simplifier2 simplifier3
#include "author.inc"
#include "lang_titles.inc"
#include "lang.inc"
\precision{10000}

\integer{confparm2=\confparm2=?2}
\integer{confparm1=\confparm1=?1}

\integer{size=10}
\integer{a=random(2..10)}
\integer{b=random(2..10)}

\text{x=random(x,y,z,a,b)}

\text{lt=wims(values v for v=1 to \confparm1)}
\text{lt=shuffle(\lt)}
\integer{p1=item(1,\lt)}
\integer{p2=randitem(item(2,\lt),0)}
\text{v1=simplify(\a*\x^\p1)}
\text{V1=texmath(\v1)}
\text{v1b=simplify(\x^\p1)}
\text{V1b=texmath(\v1b)}
\text{v2=simplify(\b*\x^\p2)}
\text{V2=texmath(\v2)}
\text{v2b=simplify(\b)}
\text{V2b=texmath(\v2b)}

#if defined TARGET_simplifier
 \matrix{don=(\v1)*(\v2),\V1\times \V2
(-\v1)*(\v2),-\V1\times \V2
(\v1)*(-\v2),\V1\times(-\V2)
(-\v1)*(-\v2),(-\V1)\times(-\V2)
(\v1b)*(\v2),\V1b\times \V2
(-\v1b)*(\v2),-\V1b\times \V2
(\v1)*(-\v2b),\V1\times(-\V2b)
(-\v1)*(-\v2b),(-\V1)\times(-\V2b)}
#endif
#if defined TARGET_simplifier2
 \matrix{don=-\a*\x^3,-\a\times \x^3
(-\a*\x)^2,(-\a\times \x)^2
(-\a*\x)^3,(-\a\times \x)^3
-\a*\x^2,-\a\times \x^2
(\v1)^2,(\V1)^2
(-\v1)^2,(-\V1)^2
(\v1)^3,(\V1)^3
(-\v1)^3,(-\V1)^3}
#endif
#if defined TARGET_simplifier3
\text{t=shuffle(2,3)}
 \matrix{don=((\v1)^\t[1])^\t[2],((\V1)^\t[1])^\t[2]
(-(\v1)^\t[1])^\t[2],(-(\V1)^\t[1])^\t[2]
((-\v1)^\t[1])^\t[2],((-\V1)^\t[1])^\t[2]
((\v1)*(\v2))^\t[1],((\V1)\times(\V2))^\t[1]
((-\v1)*(\v2))^\t[1],((-\V1)\times(\V2))^\t[1]
((-\v1)*(-\v2))^\t[1],((-\V1)\times(-\V2))^\t[1]}
#endif

\text{don=randrow(\don)}
\text{enonce=item(2,\don)}
\text{rep=simplify(item(1,\don))}

\statement{
\name_enonce \(\enonce).
<div class="wimscenter">
<label for="reply1"> \(\enonce = \) </label> \embed{r1,\size}
</div>}

\answer{\(\enonce)}{\rep}{type=litexp}{option=polexpand}
