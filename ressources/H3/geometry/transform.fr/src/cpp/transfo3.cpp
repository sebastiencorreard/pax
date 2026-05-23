target=symax3 symcen3

#include "author.inc"
#include "lang_titles.inc"

\text{image=transfo3.png}

#if defined TARGET_symax3
\text{axe=AE,FG,CG}
\text{axe=shuffle(\axe)}
\if{\axe[1]=AE}{
\matrix{data=1,8,
2,9,
3,10,
4,11,
5,12,
6,13,
8,1,
9,2,
10,3,
11,4,
12,5,
13,6}}
\if{\axe[1]=FG}{
\matrix{data=7,14,
8,15,
9,16,
10,17,
11,18,
12,19,
13,20,
14,7,
15,8,
16,9,
17,10,
18,11,
19,12,
20,13}}
\if{\axe[1]=CG}{
\matrix{data=1,6
2,5
3,4
4,3
5,2
6,1
8,13,
9,12,
10,11,
11,10,
12,9,
13,8,
15,20,
16,19,
17,18,
18,17,
19,16,
20,15}}
\text{K=randomrow(\data)}
#endif

#if defined TARGET_symcen3
\matrix{data=9,19,
10,18,
11,17,
12,16,
16,12,
17,11,
18,10,
19,9}
\text{K=randomrow(\data)}
#endif

#include "lang.inc"
#include "lang2.inc"

\statement{\name_statement.
<p class="wimscenter"><img src="\imagedir/\image" alt="\name_alt"></p>
\name_instruction[1] \(\K[1]\) \name_instruction[2] 
#if defined TARGET_symax3
<span class="nowrap">\((\axe[1])\) ?</span>
#endif
#if defined TARGET_symcen3
<span class="nowrap">\(G\) ?</span>
#endif
}


\answer{\name_answer}{\K[2]}{type=numexp}
\solution{\name_solution}
