target=simplifier1 simplifier2 simplifier3 simplifier4 simplifier5 simplifier1p
#include "author.inc"
\precision{100000}
#if defined TARGET_simplifier1
# define NUM 1
#endif
#if defined TARGET_simplifier2
# define NUM 2
#endif
#if defined TARGET_simplifier3
# define NUM 3
#endif
#if defined TARGET_simplifier4
# define NUM 4
#endif
#if defined TARGET_simplifier5
# define NUM 5
#endif
#if defined TARGET_simplifier1p
# define NUM 1 positif
#endif
#include "lang.inc"
#include "lang_titles.inc"
\text{a=wims(values v for v=2 to 9)}
\text{a=shuffle(\a)}
\text{x=randitem(x,y,z,a,b,u,v)}
\text{sg=randitem(+,-)}
\text{sg2=randitem(+,-)}
\text{A=randitem(A,B,C,D,E,F,G)}

#if defined TARGET_simplifier1
 \text{calc=-\a[1]*\a[2]*\x}
 \text{enonce=randitem(\a[1]\times(-\a[2]\x),(-\a[2]\x)\times\a[1])}
#endif
#if defined TARGET_simplifier1p
 \text{calc=\a[1]*\a[2]*\x}
 \text{enonce=randitem(\a[1]\times(\a[2]\x),(\a[2]\x)\times\a[1])}
#endif
#if defined TARGET_simplifier2
 \text{calc=(\a[1]*\x)*(\a[2]*\x)}
 \text{enonce=(\a[1]\x)\times(\a[2]\x)}
#endif
#if defined TARGET_simplifier3
 \text{sg=shuffle(,-)}
 \text{calc=(-\a[1]*\x)*(\a[2]*\x)}
 \text{enonce=(\sg[1]\a[1]\x)\times(\sg[2]\a[2]\x)}
#endif
#if defined TARGET_simplifier4
 \text{calc=(-\a[1]*\x)*(-\a[2]*\x)}
 \text{enonce=(-\a[1]\x)\times(-\a[2]\x)}
#endif
#if defined TARGET_simplifier5
 \text{calc=(-\a[1]*\x^2)*(\a[2]*\x)}
 \text{enonce=(-\a[1]\x^2)\times(\a[2]\x)}
#endif
\text{rep=simplify(\calc)}
\statement{
  \name_question:
<div class="wimscenter"> \(\A = \enonce\).</div>}

\answer{\(\A\)}{\rep}{type=litexp}{option=polexpand}
\latex{\begin{statement}
  \name_question:
\begin{center}\(\A = \enonce\).
\end{center}\end{statement}}
