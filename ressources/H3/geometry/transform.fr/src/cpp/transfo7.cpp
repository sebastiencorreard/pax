target=symax7 symcen7 trans7 rota7

#include "author.inc"
#include "lang_titles.inc"
#include "css.inc"

\text{image=transfo7.png}

#include "lang.inc"

#if defined TARGET_symax7
\matrix{data=1,3
2,2
3,1
4,7
5,6
6,5
7,4
8,10
9,9
10,8}
\text{mix=shuffle(rows(\data))}
\matrix{quest=\data[\mix[1..3];]}
\text{figdep=\quest[1;1],\quest[2;1],\quest[3;1]}
\text{good=\quest[1;2],\quest[2;2],\quest[3;2]}
\if{\figdep[1]=2 or \figdep[1]=9}{\text{sol1=\name_solhexagone \figdep[1] \name_onmeme}}
                                 {\text{sol1=\name_solhexagone \figdep[1] \name_onhexa \good[1]}}
\if{\figdep[2]=2 or \figdep[3]=9}{\text{sol2=\name_solhexagone \figdep[2] \name_onmeme}}
                                 {\text{sol2=\name_solhexagone \figdep[2] \name_onhexa \good[2]}}
\if{\figdep[3]=2 or \figdep[3]=9}{\text{sol3=\name_solhexagone \figdep[3] \name_onmeme}}
                                 {\text{sol3=\name_solhexagone \figdep[3] \name_onhexa \good[3]}}
#endif

#if defined TARGET_symcen7
\matrix{data=1,10
2,9
3,8
4,7
5,6
6,5
7,4
8,3
9,2
10,1}
\text{mix=shuffle(rows(\data))}
\matrix{quest=\data[\mix[1..3];]}
\text{figdep=\quest[1;1],\quest[2;1],\quest[3;1]}
\text{good=\quest[1;2],\quest[2;2],\quest[3;2]}
#endif

#if defined TARGET_trans7
\integer{choix=randint(6)}
\text{sens=\(E\) \name_en \(C\),\(E\) \name_en \(A\),\(A\) \name_en \(C\),\(C\) \name_en \(E\),\(A\) \name_en \(E\),\(C\) \name_en \(A\)}
\if{\choix=1 or \choix=4}{\matrix{data=4,1
5,2
6,3
8,5
9,6
10,7}}
\if{\choix=2 or \choix=5}{\matrix{data=1,2
2,3
4,5
5,6
6,7
8,9
9,10}}
\if{\choix=3 or \choix=6}{\matrix{data=5,1
6,2
7,3
8,4
9,5
10,6}}
\text{mix=shuffle(rows(\data))}
\matrix{quest=\data[\mix[1..3];]}
\if{\choix<4}{\text{figdep=\quest[1;1],\quest[2;1],\quest[3;1]}
              \text{good=\quest[1;2],\quest[2;2],\quest[3;2]}}
             {\text{figdep=\quest[1;2],\quest[2;2],\quest[3;2]}
             \text{good=\quest[1;1],\quest[2;1],\quest[3;1]}}
#endif

#if defined TARGET_rota7
\integer{choix=randint(2)}
\matrix{data=8,10,2
5,9,6
9,6,5
6,5,9
2,8,10
10,2,8}
\text{mix=shuffle(rows(\data))}
\matrix{quest=\data[\mix[1..3];]}
\text{figdep=\quest[1;1],\quest[2;1],\quest[3;1]}
\if{\choix=1}{\text{good=\quest[1;2],\quest[2;2],\quest[3;2]}
              \text{bad=\quest[1;3],\quest[2;3],\quest[3;3]}}
             {\text{good=\quest[1;3],\quest[2;3],\quest[3;3]}
              \text{bad=\quest[1;2],\quest[2;2],\quest[3;2]}}
#endif

#if defined TARGET_trans7
#include "lang2.inc"
#endif

\statement{\name_statement
<div class="wimscenter"><img src="\imagedir/\image" alt="\name_alt"></div>
\name_instruction
#if defined TARGET_symax7
<span class="nowrap">\((AB)\)...</span>
#endif
#if defined TARGET_symcen7
<span class="nowrap">\(I\)...</span>
#endif
#if defined TARGET_rota7 || defined TARGET_trans7
<span class="nowrap">\sens[\choix] ...</span>
#endif
<ul>
<li>\name_question \figdep[1]&nbsp;? <label for="reply1">\name_hexagone</label> \embed{reply1,3}.</li>
<li>\name_question \figdep[2]&nbsp;? <label for="reply2">\name_hexagone</label> \embed{reply2,3}.</li>
<li>\name_question \figdep[3]&nbsp;? <label for="reply3">\name_hexagone</label> \embed{reply3,3}.</li></ul>}

\answer{}{\good[1]}{type=case}{option=numexp}
\answer{}{\good[2]}{type=case}{option=numexp}
\answer{}{\good[3]}{type=case}{option=numexp}

#if defined TARGET_symax7
\solution{\name_solution <span class="nowrap">\((AB)\),</span>
<p>\sol1,</p>
\sol2,
<p>\sol3.</p>
\name_conclusion:
<p>\name_instruction <span class="nowrap">\((AB)\),</span>
\name_imageof \figdep[1] \name_is \good[1],
\name_imageof \figdep[2] \name_is \good[2],
\name_imageof \figdep[3] \name_is \good[3].</p>}
#endif

#if defined TARGET_symcen7
\solution{\name_solution <span class="nowrap">\(I\),</span>
<p>\name_hexagone \figdep[1] \name_onhexa \good[1],</p>
\name_hexagone \figdep[2] \name_onhexa \good[2],
<p>\name_hexagone \figdep[3] \name_onhexa \good[3].</p>
\name_conclusion:
<p>\name_instruction <span class="nowrap">\(I\),</span>
\name_imageof \figdep[1] \name_is \good[1],
\name_imageof \figdep[2] \name_is \good[2],
\name_imageof \figdep[3] \name_is \good[3].</p>}
#endif

#if defined TARGET_rota7
\feedback{\reply1 issametext \bad[1]}{<div class="macss">\name_feedback 1.</div>}
\feedback{\reply2 issametext \bad[2]}{<div class="macss">\name_feedback 2.</div>}
\feedback{\reply3 issametext \bad[3]}{<div class="macss">\name_feedback 3.</div>}
#endif
#if defined TARGET_trans7
\hint{\name_hint}
#endif
