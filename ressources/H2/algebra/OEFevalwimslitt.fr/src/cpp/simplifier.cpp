target=simplifier1 simplifier2 simplifier3 simplifier4
#include "lang.inc"
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
#include "lang_titles.inc"
#include "lang.inc"
\text{v=shuffle(2,3,4,5,6,7,8,9)}
\text{x=randitem(x,y,a,b)}
#if defined TARGET_simplifier1
 \text{enonce=\v[1] \times \x \times \v[2]}
 \integer{a=\v[1]*\v[2]}
 \text{rep=\a\x}
#endif
#if defined TARGET_simplifier2
 \text{enonce=\x \times \x}
 \text{rep=\x^2}
#endif
#if defined TARGET_simplifier3
 \text{enonce=\v[1] \times \x + \v[2]}
 \text{rep=\v[1]\x+\v[2] \v[2]+\v[1]\x}
#endif
#if defined TARGET_simplifier4
 \text{enonce=\v[1] \times \v[2] + \x}
 \integer{a=\v[1]*\v[2]}
 \text{rep=\a+\x \x+\a}
#endif

\text{affsol=wims(word 1 of \rep)}
\statement{
\name_instruction:
<div class="wimscenter">
 \(\enonce = \) \embed{r1,7}.
</div>
<div class="wims_instruction">\name_warning</div>}
\answer{\name_answer}{\sol}{type=raw}

\condition{\name_cond}{\sol iswordof \rep}
\solution{\name_goodanswer \(\affsol\).<br>
\name_goodanswerremark.}

\latex{\begin{statement}
\name_instruction: \(\enonce \).
\end{statement}}
