target=centre3,centre4,centre5
#define TITRE Centre de classe
#include "author.inc"

\text{m=randitem(m,M,T,t,N,S)}

#if #TARGET(centre3)
 \title{TITRE 3}
 \integer{min=randint(10..20)}
 \integer{Max=\min+1+2*randint(3..5)}
 \text{classe=\(\min \leq \m < \Max)}
 \real{res=(\min+\Max)/2}
#endif
#if #TARGET(centre4)
 \title{TITRE 4}
 \integer{min=randint(10..20)*10}
 \integer{Max=\min+20*randint(3..5)}
 \text{classe=\m est compris entre \min et \Max}
 \real{res=(\min+\Max)/2}
#endif
#if #TARGET(centre5)
 \title{TITRE 5}
 \integer{d=randitem(3,6,7)}
 \integer{e=2*randint(1..3)*\d}
 \text{min=wims(values v for v=1 to \d-1)}
 \integer{min=randitem(\min)+\d*randint(3..8)}
 \integer{Max=\min+\e}
 \text{classe=\(\frac{\min}{\d} \leq \m < \frac{\Max}{\d})}
 \text{res=simplify((\min+\Max)/(2*\d))}
#endif

\statement{
Quelle est la valeur centrale de la classe des nombres \(\m\) vérifiant :
<div class="wimscenter"> \classe ?</div>}
\answer{Réponse}{\res}{type=numexp}{option=noreduction}
