target=trans1

#include "author.inc"
#include "lang_titles.inc"

\text{image=trans1.png}

\text{dep=A,B,C,D,E,F,G,H}
\matrix{data1=A,B
E,F
H,G
D,C}
\matrix{data2=A,D
B,C
F,G
E,H}
\matrix{data3=A,E
B,F
C,G
D,H}
\integer{n=randint(3)}
\if{\n=1}{\matrix{data=\data1}}
\if{\n=2}{\matrix{data=\data2}}
\if{\n=3}{\matrix{data=\data3}}
\matrix{data=slib(data/random 2,row,\data)}
\integer{n=randint(2)}
\if{\n=2}{\matrix{data=\data[1;2],\data[1;1]
\data[2;2],\data[2;1]}}

#include "lang.inc"
#include "lang2.inc"

\statement{\name_statement[1].
<p class="wimscenter"><img src="\imagedir/\image" alt="parallélépipède"></p>
<label for="reply1">\name_statement[2] \(\data[2;1]\) \name_statement[3] \(\data[1;1]\) \name_statement[4] <span class="nowrap">\(\data[1;2]\) ?</span></label>\embed{r1,3}}

\solution{\name_solution[1] \(\data[1;1]\data[1;2]\data[2;2]\data[2;1]\) \name_solution[2].
<p>\name_solution[3] \(\data[1;1]\) \name_solution[4] \(\data[1;2]\) \name_solution[5] \(\data[2;1]\) \name_solution[4] \(\data[2;2]\).}

\answer{}{\data[2;2]}{type=case}

\hint{\name_hint}
