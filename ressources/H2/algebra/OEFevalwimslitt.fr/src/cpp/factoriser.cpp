target=factoriser1 factoriser2 factoriser3 factoriser4 factoriser5
#if defined TARGET_factoriser1
# define NUM 1
#endif
#if defined TARGET_factoriser2
# define NUM 2
#endif
#if defined TARGET_factoriser3
# define NUM 3
#endif
#if defined TARGET_factoriser4
# define NUM 4
#endif
#if defined TARGET_factoriser5
# define NUM 5
#endif
#include "author.inc"
#include "lang_titles.inc"
#include "lang.inc"
\text{v=shuffle(2,3,4,5,6,7,8,9)}
\text{x=randitem(x,y,a,b)}
\text{A=randitem(A,B,C,D,E,F,G)}

#if defined TARGET_factoriser1
 \text{enonce=\v[1] \times \x+\v[1]\times\v[2]}
 \text{rep=\v[1]*(\x+\v[2])}
#endif
#if defined TARGET_factoriser2
 \text{enonce=\x\times \x-\v[1]\times \x}
 \text{rep=\x*(\x-\v[1])}
#endif
#if defined TARGET_factoriser3
 \integer{a=\v[1]*\v[2]}
 \text{enonce=\v[1] \times \x+\a}
 \text{rep=\v[1]*(\x+\v[2])}
#endif
#if defined TARGET_factoriser4
 \text{enonce=\x^2-\v[1] \times \x}
 \text{rep=\x*(\x-\v[1])}
#endif
#if defined TARGET_factoriser5
 \integer{c=randitem(2,4,6,8)}
 \integer{d=randitem(3,5,7,9)}
 \integer{a=\v[1]*\c}
 \integer{b=\v[1]*\d}
 \text{enonce=\a-\b\x}
 \text{rep=\v[1]*(-\d*\x+\c)}
#endif

\statement{
\name_instruction
<div class="wimscenter">\(\A = \enonce\).</div>}

\answer{\(\A\)}{\rep}{type=litexp}{option=polfactor}
\latex{\begin{statement}
\name_instruction
\begin{center}\(\A = \enonce\).\end{center}
\end{statement}
}
