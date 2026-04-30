target=antecedentg1,antecedentg2,antecedentg3,antecedentg4,antecedentg5
#include "author.inc"
#if defined TARGET_antecedentg1
# define NUM 1
#endif
#if defined TARGET_antecedentg2
# define NUM 2
#endif
#if defined TARGET_antecedentg3
# define NUM 3
#endif
#if defined TARGET_antecedentg4
# define NUM 4
#endif
#if defined TARGET_antecedentg5
# define NUM 5
#endif
#include "lang_titles.inc"
\precision{100}
\text{f=randitem(f,g,h)}

#if defined TARGET_antecedentg1
 \text{v=wims(values v for v=1 to 8)}
 \text{v=shuffle(\v)}
 \integer{a=\v[1]}
 \integer{b=\v[2]}
 \text{k=randitem(1/2,1/4,1/3,2,3,4,5)}
 \text{fonction=\k*x+\b-\k*\a}
#endif
#if defined TARGET_antecedentg2
 \text{v=wims(values v for v=1 to 8)}
 \text{v=shuffle(\v)}
 \integer{a=\v[1]}
 \integer{b=-\v[2]}
 \text{k=-randitem(1/2,1/4,1/3,2,3,4,5)}
 \text{fonction=\k*x+\b-\k*\a}
#endif
#if defined TARGET_antecedentg3
 \text{v=wims(values v for v=1 to 5)}
 \text{v=shuffle(\v)}
 \integer{a=randitem(-1,1)*\v[2]}
 \integer{b=0}
 \text{k=randitem(1,-1)*randitem(1/2,1/3,2,3)}
 \text{fonction=\k*x+\b-\k*\a}
#endif
#if defined TARGET_antecedentg4
 \text{v=wims(values v for v=1 to 8)}
 \text{v=shuffle(\v)}
 \integer{a=-\v[1]}
 \integer{b=\v[2]}
 \text{k=-randitem(1/2,1/4,1/3,2,3,4,5)}
 \text{fonction=\k*x+\b-\k*\a}
#endif
#if defined TARGET_antecedentg5
 \text{v=wims(values v for v=1 to 8)}
 \text{v=shuffle(\v)}
 \integer{a=-\v[1]}
 \integer{b=-\v[2]}
 \text{k=randitem(1/2,1/4,1/3,2,3,4,5)}
 \text{fonction=\k*x+\b-\k*\a}
#endif
\text{dessin=slib(draw/repere 400,400,0,-10,10,-10,10,1,1,black,grey)}
\text{dessin=wims(line 3 to -1 of \dessin)}
\text{figure=draw(400,400
\dessin
range -10,10,-10,10
plot blue,\fonction
text black,9.5,-0.3,medium,X
text black,-1.5,10,medium,\f(X)
text black,0.9,-0.3,medium,1
text black,-0.6,1.5,medium,1)}
\statement{
Soit \(\f\) une fonction affine dont la représentation graphique est donnée ci-dessous.
<div class="wimscenter"><img src="\figure" alt=""></div>
  Quel nombre a pour image \b par cette fonction ?
<p><b>Votre réponse :</b></p>
  <label for="reply1">Le nombre qui a pour image \b par cette fonction est</label> \embed{r1,5}.
}
\answer{réponse}{\a}{type=numexp}
