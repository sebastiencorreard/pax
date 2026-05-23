target=factoriser1 factoriser2 factoriser3 factoriser4 factoriser5
#include "author.inc"
#if defined TARGET_factoriser1
#define NUM 1
#endif
#if defined TARGET_factoriser2
#define NUM 2
#endif
#if defined TARGET_factoriser3
#define NUM 3
#endif
#if defined TARGET_factoriser4
#define NUM 4
#endif
#if defined TARGET_factoriser5
#define NUM 5
#endif
\precision{100000}
#include "lang.inc"
#include "lang_titles.inc"

\text{a=randitem(2,4,6,8)}
\text{b=\a=6?randitem(5,7,11):randitem(3,5,7,9)}
\text{c=randitem(2,3,5,9)}
\text{x=randitem(x,y,z,a,b,u,v)}
\text{A=randitem(A,B,C,D,E,F,G)}
\integer{t1=\a*\c}
\integer{t2=\b*\c}

#if defined TARGET_factoriser1
\text{m=shuffle(,*\x)}
\text{calc=\t1\m[1]+\t2\m[2]}
#endif
#if defined TARGET_factoriser2
\text{m=shuffle(,*\x)}
\text{calc=\t1\m[1]-\t2\m[2]}
#endif
#if defined TARGET_factoriser3
\integer{ch=randint(1..2)}
\if{\ch=1}{
  \text{m=*\x^2,*\x}
  \text{m2=*\x,}
}{
  \text{m=*\x,*\x^2}
  \text{m2=,*\x}
}
\text{calc=\a\m[1]+\b\m[2]}
#endif
#if defined TARGET_factoriser4
\integer{ch=randint(1..2)}
\if{\ch=1}{
  \text{m=*\x^2,*\x}
  \text{m2=*\x,}
 }{
  \text{m=*\x,*\x^2}
  \text{m2=,*\x}
 }
\text{calc=\a\m[1]-\b\m[2]}
#endif
#if defined TARGET_factoriser5
\integer{ch=randint(1..2)}
\if{\ch=1}{
  \text{m=*\x^2,*\x}
  \text{m2=*\x,}
 }{
  \text{m=*\x,*\x^2}
  \text{m2=,*\x}
 }
\text{calc=\t1\m[1]-\t2\m[2]}
#endif

\text{enonce=texmath(\calc)}
\text{rep=maxima(factor(\calc);)}

\statement{
  \name_question:
<div class="wimscenter"> \(\A = \enonce\).</div>}

\answer{\(\A\)}{\rep}{type=litexp}{option=polfactor}

\latex{\begin{statement}
  \name_question
\begin{center}\(\A = \enonce\).\end{center}
\end{statement}}
