target=developper1 developper2 developper3 developper4 developper5
#if defined TARGET_developper1
# define NUM 1
#endif
#if defined TARGET_developper2
# define NUM 2
#endif
#if defined TARGET_developper3
# define NUM 3
#endif
#if defined TARGET_developper4
# define NUM 4
#endif
#if defined TARGET_developper5
# define NUM 5
#endif
#include "author.inc"
#include "lang_titles.inc"
#include "lang.inc"

\text{v=shuffle(2,3,4,5,6,7,8,9)}
\text{x=randitem(x,y,a,b)}
\text{A=randitem(A,B,C,D,E,F,G)}
#if defined TARGET_developper1
 \text{enonce=\v[1](\x+\v[2])}
 \integer{a=\v[1]*\v[2]}
 \text{rep=\v[1]*\x+\a}
#endif
#if defined TARGET_developper2
 \text{enonce=\v[1](\x-\v[2])}
 \integer{a=\v[1]*\v[2]}
 \text{rep=\v[1]*\x-\a}
#endif
#if defined TARGET_developper3
 \text{enonce=\x(\x+\v[2])}
 \text{rep=\x^2+\v[2]*\x}
#endif
#if defined TARGET_developper4
 \text{enonce=\v[3](\v[1]\x+\v[2])}
 \integer{a=\v[3]*\v[1]}
 \integer{b=\v[3]*\v[2]}
 \text{rep=\a*\x+\b}
#endif

#if defined TARGET_developper5
 \text{enonce=\v[3]\x(\v[1]\x-\v[2])}
 \integer{a=\v[3]*\v[1]}
 \integer{b=\v[3]*\v[2]}
 \text{rep=\a*\x^2-\b*\x}
#endif

\statement{
\name_instruction :
<div class="wimscenter">\(\A = \enonce\).</div>}

\answer{\(\A\)}{\rep}{type=litexp}{option=polexpand}

\latex{\begin{statement}
\name_instruction :
\begin{center}\(\A = \enonce\).\end{center}
\end{statement}
}
