target=mentalA1 mentalA2 mentalA4 mentalA5 mentalB1 mentalB2 mentalB3 mentalB4 mentalB5
#define TITRE Calculer mentalement des carrés
#define TITREB Calculer mentalement des racines carrées
#include "author.inc"
\text{name_enonce=Calculer mentalement&nbsp;}
#if defined TARGET_mentalA1
 \title{TITRE 1}
 \text{calc=randitem(4,5,6,7,8,9,3)}
 \text{type=A}
#endif
#if defined TARGET_mentalA2
 \title{TITRE 2}
 \text{calc=randitem(11,12,13)}
 \text{type=A}
#endif
#if defined TARGET_mentalA4
 \title{TITRE 4}
 \text{calc=randitem(0.2,0.3,0.4)}
 \text{type=A}
#endif
#if defined TARGET_mentalA5
 \title{TITRE 5}
 \text{calc=randitem(1.1,1.2,1.3)}
 \text{type=A}
#endif
#if defined TARGET_mentalB1
 \title{TITREB 1}
 \text{calc=randitem(2,5,10,3)}
 \text{type=B}
#endif
#if defined TARGET_mentalB2
 \title{TITREB 2}
 \text{calc=randitem(4,6,7,8,9)}
 \text{type=B}
#endif
#if defined TARGET_mentalB3
 \title{TITREB 3}
 \text{calc=randitem(11,12,13)}
 \text{type=B}
#endif
#if defined TARGET_mentalB4
 \title{TITREB 4}
 \text{calc=randitem(0.2,0.3,0.4)}
 \text{type=B}
#endif
#if defined TARGET_mentalB5
 \title{TITREB 5}
 \text{calc=randitem(1.1,1.2,1.3)}
 \text{type=B}
#endif

\if{A isin \type}{
 \real{good=\calc^2}
 \text{enonce=\(\calc^2)}
}{
 \real{good=\calc}
 \real{calc=\calc^2}
 \text{enonce=\(\sqrt{\calc})}
}

\statement{
  \name_enonce:
<div class="wimscenter"> \enonce </div>}

\answer{\enonce}{\good}{type=numexp}
