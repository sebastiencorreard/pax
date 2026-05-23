target=distribuer1 distribuer2 distribuer3 distribuer4 distribuer5
#include "author.inc"
\precision{100000}
#if defined TARGET_distribuer1
# define NUM 1
#endif
#if defined TARGET_distribuer2
# define NUM 2
#endif
#if defined TARGET_distribuer3
# define NUM 3
#endif
#if defined TARGET_distribuer4
# define NUM 4
#endif
#if defined TARGET_distribuer5
# define NUM 5
#endif
#include "lang.inc"
#include "lang_titles.inc"

\text{a=wims(values v for v=2 to 9)}
\text{a=shuffle(\a)}
\text{x=randitem(x,y,z,a,b,u,v)}
\text{sg=randitem(+,-)}
\text{sg2=randitem(+,-)}
\text{A=randitem(A,B,C,D,E,F,G)}

#if defined TARGET_distribuer1
\text{l=shuffle(,*\x)}
\text{calc=-(\a[1]\l[1]+\a[2]\l[2])}
\text{rep=-\a[1]\l[1]-\a[2]\l[2]}
#endif
#if defined TARGET_distribuer2
\text{l=shuffle(,*\x)}
\text{calc=-(\a[1]\l[1]-\a[2]\l[2])}
#endif
#if defined TARGET_distribuer3
\text{l=shuffle(,*\x)}
\text{l2=shuffle(,*\x)}
\text{calc=-(\a[1]\l[1]-\a[2]\l[2])+(\a[3]\l2[1]-\a[4]\l2[2])}
#endif
#if defined TARGET_distribuer4
\text{l=shuffle(,*\x)}
\text{l2=shuffle(,*\x)}
\text{sg=randitem(,-)}
\text{calc=\sg(\a[1]\l[1]-\a[2]\l[2])-(\a[3]\l2[1]+\a[4]\l2[2])}
#endif
#if defined TARGET_distribuer5
\text{l2=shuffle(,*\x)}
\text{l=shuffle(*\x,*\x^2)}
\text{sg=randitem(,-)}
\text{calc=\sg(\a[1]\l[1]-\a[2]\l[2])-(\a[3]\l2[1]-\a[4]\l2[2])}
#endif
\text{enonce=texmath(\calc)}
#if defined TARGET_distribuer2 || defined TARGET_distribuer3 || defined TARGET_distribuer4 || defined TARGET_distribuer5
\text{rep=pari(\calc)}
#endif
\statement{
  \name_question[1] \(\A\) \name_question[2]:
<div class="wimscenter"> \(\A = \enonce\).</div>}

\answer{\(\A\)}{\rep}{type=litexp}{option=polexpand}

\latex{\begin{statement}
  \name_question[1] \(\A\) \name_question[2]:
\begin{center}\(\A = \enonce\).\end{center}
\end{statement}}
