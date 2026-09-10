target=tester1 tester2 tester3 tester4 tester5
#if defined TARGET_tester1
# define NUM 1
#endif
#if defined TARGET_tester2
# define NUM 2
#endif
#if defined TARGET_tester3
# define NUM 3
#endif
#if defined TARGET_tester4
# define NUM 4
#endif
#if defined TARGET_tester5
# define NUM 5
#endif
#include "author.inc"
#include "lang_titles.inc"
#include "lang.inc"

\text{v=shuffle(2,3,4,5,6,7,8,9)}
\text{x=randitem(x,y,a,b)}
\text{A=randitem(A,B,C,D,E,F,G)}
\integer{good=randitem(1,2)}

#if defined TARGET_tester1
 \integer{a=\v[1]+\v[2]}
 \integer{a=\good=2?\a+\v[3]}
 \text{enonce=\x+\v[2]=\a}
 \integer{val=\v[1]}
#endif
#if defined TARGET_tester2
 \integer{a=\v[1]-\v[2]}
 \integer{a=\good=2?\a+\v[3]}
 \text{enonce=\x-\v[2]=\a}
 \integer{val=\v[1]}
#endif
#if defined TARGET_tester3
 \integer{a=-\v[1]-\v[2]}
 \integer{a=\good=2?\a+\v[3]}
 \text{enonce=\x-\v[2]=\a}
 \integer{val=-\v[1]}
#endif
#if defined TARGET_tester4
 \integer{a=\v[3]*\v[1]-\v[2]}
 \integer{a=\good=2?\a+\v[4]}
 \text{enonce=\v[3]\x-\v[2]=\a}
 \integer{val=\v[1]}
#endif
#if defined TARGET_tester5
 \integer{a=(\v[3]-1)*\v[1]-\v[2]}
 \integer{a=\good=2?\a+\v[4]}
 \text{a=simplify(\x+(\a))}
 \text{enonce=\v[3]\x-\v[2]=\a}
 \integer{val=\v[1]}
#endif

\text{good=\bad[\good]}

\statement{
\name_instruction \(\x = \val\) ?
<div class="wimscenter">\(\enonce \).</div>}

\choice{Réponse}{\good}{\bad}
\latex{\begin{statement}
\name_instruction \(\x = \val\) ?
\end{statement}
}
