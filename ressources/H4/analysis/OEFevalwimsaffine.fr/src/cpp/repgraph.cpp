target=repgraph1,repgraph2,repgraph3,repgraph4,repgraph5
#include "author.inc"
\precision{100}
#if defined TARGET_repgraph1
# define NUM 1
#endif
#if defined TARGET_repgraph2
# define NUM 2
#endif
#if defined TARGET_repgraph3
# define NUM 3
#endif
#if defined TARGET_repgraph4
# define NUM 4
#endif
#if defined TARGET_repgraph5
# define NUM 5
#endif
#include "lang_titles.inc"
\text{f=randitem(f,g,h)}
\integer{size=300}
#if defined TARGET_repgraph1
 \text{v=wims(values v for v=4 to 9)}
 \text{v=shuffle(\v)}
 \integer{a=randint(2..5)}
 \integer{b=randint(1,-1)*randint(2..5)}
 \text{fonction=\a*x+\b}
 \text{good=Oui}
#endif
#if defined TARGET_repgraph2
 \text{v=wims(values v for v=4 to 9)}
 \text{v=shuffle(\v)}
 \integer{a=0}
 \integer{b=randint(1,-1)*randint(2..5)}
 \text{fonction=\a*x+\b}
 \text{good=Oui}
#endif
#if defined TARGET_repgraph3
 \text{v=wims(values v for v=4 to 9)}
 \text{v=shuffle(\v)}
 \integer{b=randint(1,-1)*randint(2..10)}
 \text{fonction=1/\b*x^3}
 \text{good=Non}
#endif
#if defined TARGET_repgraph4
 \text{v=wims(values v for v=4 to 9)}
 \text{v=shuffle(\v)}
 \integer{b=0}
 \integer{a=randint(1,-1)*randint(2..5)}
 \text{fonction=\a*x+\b}
 \text{good=Oui}
#endif
#if defined TARGET_repgraph5
 \text{v=wims(values v for v=4 to 9)}
 \text{v=shuffle(\v)}
 \integer{b=randint(-2..2)}
 \integer{a=randint(1,-1)*randint(1..3)}
 \text{k=randitem(1/2,-1/2,2,3,4,-2,-3,-4,1/3,-1/3)}
 \text{k2=simplify(1/(\k))}
 \text{fonction=\k*(x-\a)+\b+(\k-\k2)*(x-\a)/2*(1+abs(\a-x)/(\a-x))}
 \text{good=Non}
#endif
\text{repere=slib(draw/repere \size,\size,0,-10,10,-10,10,1,1,black,grey)}
\text{repere=wims(line 3 to -1 of \repere)}
\text{dessin=}
\text{figure=draw(\size,\size
\repere
range -10,10,-10,10
plot blue,\fonction
text black,9.5,-0.3,medium,X
text black,-1.5,10,medium,\f(X)
text black,0.9,-0.3,medium,1
text black,-0.5,1.5,medium,1)}

\statement{
  Voici la représentation graphique d'une fonction :
<div class="wimscenter"><img src="\figure" alt=""></div>
  Cette fonction est-elle une fonction affine ?}

\choice{réponse}{\good}{Oui,Non}
