target=trans2

#include "author.inc"
#include "lang_titles.inc"
\integer{nbre=randint(3)}
\if{\nbre=1}{\matrix{rep=B,C
C,D
D,E
F,G
H,I
J,K
K,L
L,M
M,N
O,P
P,Q
Q,R}
\text{pt=A,B}}
\if{\nbre=2}{\matrix{rep=B,J
C,K
D,L
E,M
G,O
I,Q}
\text{pt=H,P}}
\if{\nbre=3}{\matrix{rep=A,G
B,H
F,L
G,M
H,N
J,P
K,Q
L,R}
\text{pt=C,I}}
\text{mix=shuffle(rows(\rep))}
\matrix{quest=\rep[\mix[1..4];]}

#include "lang.inc"

\text{quest1=\(A\) \name_into \(B\) :,\(H\) \name_into \(P\) :,\(C\) \name_into \(I\) :}

#include "lang2.inc"

\statement{<div class="wimscenter"><img src="\imagedir/trans2.png" alt="\name_alt"></div>
<p>\name_statement[1].</p>
<div>\name_statement[2] <span class="nowrap">\quest1[\nbre]</span>
<ul>
\for{j = 1 to 4}{<li><label for="reply\j">\name_statement[3] \(\quest[\j;1]\) \name_statement[4]</label>\embed{reply\j,3}</li>}
</ul></div>}


\answer{}{\quest[1;2]}{type=case}
\answer{}{\quest[2;2]}{type=case}
\answer{}{\quest[3;2]}{type=case}
\answer{}{\quest[4;2]}{type=case}

\solution{\name_solution}
\hint{\name_hint}
