target=symax5 symcen5

#include "author.inc"
#include "lang_titles.inc"
#include "lang.inc"
  
\text{liste=1,2,3,4,5,6}
\text{image=transfo5.png}

#if defined TARGET_symax5
\text{axe=PL}
\matrix{data=1,4
2,5
3,6
4,1
5,2
6,3}
#endif

#if defined TARGET_symcen5
\matrix{data=1,6
2,5
3,4
4,3
5,2
6,1}
#endif
\text{K=randomrow(\data)}

#include "lang2.inc"

\statement{\name_statement1
<p>\name_statement2[1] \(SLAP\) \name_statement2[2] <span class="nowrap">\(J\).</span></p>
<p class="wimscenter"><img src="\imagedir/\image" alt="cerfs-volants"></p>
\name_instruction[1] \(\K[1]\) \name_instruction[2] 
#if defined TARGET_symax5
<span class="nowrap">\((\axe)\) ?</span>
#endif
#if defined TARGET_symcen5
<span class="nowrap">\(J\) ?</span>
#endif
}

\answer{\name_answer}{\K[2];\liste}{type=menu}
\solution{\name_solution}
