target=reduire1 reduire2 reduire3 reduire4 reduire5 reduire1p reduire2p
#include "author.inc"
\precision{100000}
#if defined TARGET_reduire1
#define NUM 1
#endif
#if defined TARGET_reduire2
#define NUM 2
#endif
#if defined TARGET_reduire3
#define NUM 3
#endif
#if defined TARGET_reduire4
#define NUM 4
#endif
#if defined TARGET_reduire5
#define NUM 5
#endif
#if defined TARGET_reduire1p
#define NUM 1 positif
#endif
#if defined TARGET_reduire2p
#define NUM 2 positif
#endif
#include "lang.inc"
#include "lang_titles.inc"

\text{a=wims(values v for v=2 to 9)}
\text{a=shuffle(\a)}
\text{x=randitem(x,y,z,a,b,u,v)}
\text{sg=randitem(+,-)}
\text{sg2=randitem(+,-)}
\text{A=randitem(A,B,C,D,E,F,G)}

#if defined TARGET_reduire1
 \text{calc=\a[1]*\x+\a[2]*\x\sg\a[3]+\a[4]}
#endif
#if defined TARGET_reduire1p
 \text{calc=\a[1]*\x+\a[2]*\x+\a[3]+\a[4]}
#endif
#if defined TARGET_reduire2
 \integer{v=\a[5]+\a[1]}
 \text{calc=\a[1]*\x\sg\a[3]+\a[2]*\x+\a[4]\sg2\v*\x}
#endif
#if defined TARGET_reduire2p
 \integer{v=\a[5]+\a[1]}
 \text{calc=\a[1]*\x+\a[3]+\a[2]*\x+\a[4]+\v*\x}
#endif
#if defined TARGET_reduire3
 \text{calc=shuffle(+\a[1]*\x^2,\sg\a[3],+\a[2]*\x,+\a[4],\sg2\a[5]*\x,+\a[6]*\x^2)}
 \text{calc=wims(items2words \calc)}
#endif
#if defined TARGET_reduire4
\integer{v=\a[1]+\a[6]}
\text{l=shuffle(,*\x,*\x^2)}
\text{calc=shuffle(+\a[1]\l[1],+\a[2]\l[2],-\v\l[1],+\a[4]\l[3],\sg2\a[5]\l[2],+\a[6]\l[1])}
\text{calc=wims(items2words \calc)}
#endif
#if defined TARGET_reduire5
\integer{v=\a[1]+\a[6]}
\text{l=shuffle(,*\x,*\x^2)}
\text{calc=shuffle(+\a[1]\l[1],+\a[2]\l[2],-\v\l[1],+\a[4]\l[3],-\a[2]\l[2],+\a[6]\l[1])}
\text{calc=wims(items2words \calc)}
#endif
\text{enonce=texmath(\calc)}
\text{rep=pari(\calc)}

\statement{
  \name_question[1] \(\x\) \name_question[2] \(\A\)\name_insec:
<div class="wimscenter"> \(\A = \enonce\).</div>}

\answer{\(\A\)}{\rep}{type=litexp}
\latex{\begin{statement}
  \name_question[1] \(\x\) \name_question[2] \(\A\):
\begin{center}\(\A = \enonce\).\end{center}
\end{statement}}
