target=developperA1 developperA2 developperA3 developperA4 developperA5 developperB1 developperB2 developperB3 developperB4 developperB5
#include "author.inc"
\precision{100000}
#if defined TARGET_developperA1
# define NUM A1
#endif
#if defined TARGET_developperA2
# define NUM A2
#endif
#if defined TARGET_developperA3
# define NUM A3
#endif
#if defined TARGET_developperA4
# define NUM A4
#endif
#if defined TARGET_developperA5
# define NUM A5
#endif
#if defined TARGET_developperB1
# define NUM B1
#endif
#if defined TARGET_developperB2
# define NUM B2
#endif
#if defined TARGET_developperB3
# define NUM B3
#endif
#if defined TARGET_developperB4
# define NUM B4
#endif
#if defined TARGET_developperB5
# define NUM B5
#endif
#include "lang.inc"
#include "lang_titles.inc"

\text{a=wims(values v for v=2 to 9)}
\text{a=shuffle(\a)}
\text{x=randitem(x,y,z,a,b,u,v)}
\text{A=randitem(A,B,C,D,E,F,G)}

#if defined TARGET_developperA1
\text{t=shuffle(\a[2],\a[3]*\x)}
\text{calc=\a[1]*(\t[1]+\t[2])}
#endif
#if defined TARGET_developperA2
\text{t=shuffle(\a[2],\a[3]*\x)}
\text{calc=\a[1]*\x*(\t[1]+\t[2])}
#endif
#if defined TARGET_developperA3
\text{t=shuffle(\a[2],\a[3]*\x)}
\text{calc=\a[1]*\x*(\t[1]-\t[2])}
#endif
#if defined TARGET_developperA4
\text{t=shuffle(\a[2],\a[3]*\x)}
\text{calc=-\a[1]*\x*(\t[1]-\t[2])}
#endif
#if defined TARGET_developperA5
\text{t=shuffle(\a[2],\a[3]*\x)}
\text{calc=-\a[1]*\x*(-\t[1]-\t[2])}
#endif
#if defined TARGET_developperB1
\text{t=shuffle(\a[1],\a[2]*\x)}
\text{t2=shuffle(\a[3],\a[4]*\x)}
\text{calc=(\t[1]+\t[2])*(\t2[1]+\t2[2])}
#endif

#if defined TARGET_developperB2
\text{t=shuffle(\a[1],\a[2]*\x)}
\text{t2=shuffle(\a[3],\a[4]*\x)}
\text{sg=shuffle(+,-)}
\text{calc=(\t[1]\sg[1]\t[2])*(\t2[1]\sg[2]\t2[2])}
#endif
#if defined TARGET_developperB3
\text{t=shuffle(\a[1],\a[2]*\x)}
\text{t2=shuffle(\a[3],\a[4]*\x)}
\text{calc=(\t[1]-\t[2])*(\t2[1]-\t2[2])}
#endif
#if defined TARGET_developperB4
\text{t=shuffle(\a[1],\a[2]*\x)}
\text{t2=shuffle(\a[3],\a[4]*\x)}
\text{sg=shuffle(+,-)}
\text{calc=(\sg[1]\t[1]-\t[2])*(\sg[2]\t2[1]-\t2[2])}
#endif
#if defined TARGET_developperB5
\text{t=shuffle(\a[1],\a[2]*\x)}
\text{t2=shuffle(\a[3],\a[4]*\x)}
\text{calc=(-\t[1]-\t[2])*(-\t2[1]-\t2[2])}
#endif

\text{enonce=texmath(\calc)}
\text{rep=pari(\calc)}

\statement{
  \name_question \(\A\)\name_insec:
<div class="wimscenter"> \(\A = \enonce\).</div>}

\answer{\(\A\)}{\rep}{type=litexp}{option=polexpand}

\latex{\begin{statement}
  \name_question \(\A\):
\begin{center}\(\A = \enonce\).\end{center}
\end{statement}}
