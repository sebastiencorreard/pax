target=evaluerA1 evaluerA2 evaluerA3 evaluerA4 evaluerA5 evaluerB1 evaluerB2 evaluerB3 evaluerB4 evaluerB5
#include "author.inc"
\precision{100000}
#if defined TARGET_evaluerA1
# define NUM A1
#endif
#if defined TARGET_evaluerA2
# define NUM A2
#endif
#if defined TARGET_evaluerA3
# define NUM A3
#endif
#if defined TARGET_evaluerA4
# define NUM A4
#endif
#if defined TARGET_evaluerA5
# define NUM A5
#endif
#if defined TARGET_evaluerB1
# define NUM B1
#endif
#if defined TARGET_evaluerB2
# define NUM B2
#endif
#if defined TARGET_evaluerB3
# define NUM B3
#endif
#if defined TARGET_evaluerB4
# define NUM B4
#endif
#if defined TARGET_evaluerB5
# define NUM B5
#endif
#include "lang.inc"
#include "lang_titles.inc"

\text{a=wims(values v for v=2 to 9)}
\text{a=shuffle(\a)}
\text{x=randitem(x,y,z,a,b,u,v)}
\text{sg=randitem(+,-)}
\text{sg2=randitem(+,-)}
\text{A=randitem(A,B,C,D,E,F,G)}

#if defined TARGET_evaluerA1
\text{calc=\a[1]*\x\sg\a[2]}
\text{val=\a[3]}
#endif
#if defined TARGET_evaluerA2
\text{calc=\a[1]*\x\sg\a[2]}
\text{val=-\a[3]}
#endif
#if defined TARGET_evaluerA3
\text{calc=-\a[1]*\x\sg\a[2]}
\text{val=-\a[3]}
#endif
#if defined TARGET_evaluerA4
\text{calc=\a[1]*\x\sg\a[2]}
\text{val=randitem(1/2,1/3,1/4,2/3,1/5,2/5)}
#endif
#if defined TARGET_evaluerA5
\text{val=randitem(1/2,1/3,1/4,2/3,1/5,2/5)}
\text{d=wims(replace internal / by , in \val)}
\text{d=item(2,\d)}
\integer{n=randitem(7,11,13)}
\text{calc=\a[1]*\x\sg \n/\d}
#endif
#if defined TARGET_evaluerB1
\text{calc=shuffle(+\a[1]*\x^2,\sg\a[2]*\x,+\a[3])}
\text{calc=wims(items2words \calc)}
\text{val=\a[4]}
#endif
#if defined TARGET_evaluerB2
\text{calc1=shuffle(+\a[1]*\x,\sg\a[2])}
\text{calc1=wims(items2words \calc1)}
\text{calc2=shuffle(+\a[3]*\x,\sg2\a[4])}
\text{calc2=wims(items2words \calc2)}
\text{calc=(\calc1)*(\calc2)}
\text{val=-\a[5]}
#endif
#if defined TARGET_evaluerB3
\text{calc=\x^2+\a[2]*\x+\a[3]}
\text{val=-\a[1]}
#endif
#if defined TARGET_evaluerB4
\text{calc=-\x^2-\a[2]*\x\sg\a[3]}
\text{val=-\a[1]}
#endif
#if defined TARGET_evaluerB5
\text{val=randitem(1/2,1/3,1/4,2/3,1/5,2/5)}
\text{d=wims(replace internal / by , in \val)}
\text{d=item(2,\d)}
\text{calc=\d*\x^2\sg2\a[2]*\x\sg\a[3]}
#endif

\text{enonce=texmath(\calc)}
\text{calc=wims(replace internal \x by (\x) in \calc)}
\text{rep=simplify(evalue(\calc,\x=\val))}
\text{aval=texmath(\val)}

\statement{
  \name_question[1] \(\A\) \name_question[2] \(\x = \aval\)\name_insec:
<div class="wimscenter"> \(\A = \enonce\).</div>}

\answer{\(\A\)}{\rep}{type=numexp}{option=noreduction}
\latex{\begin{statement}
  \name_question[1] \(\A\) \name_question[2] \(\x = \aval\):
\begin{center}\(\A = \enonce\).\end{center}
\end{statement}}
