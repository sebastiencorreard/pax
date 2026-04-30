target=expression1,expression2,expression3,expression4,expression5
#include "author.inc"
#if defined TARGET_expression1
# define NUM 1
#endif
#if defined TARGET_expression2
# define NUM 2
#endif
#if defined TARGET_expression3
# define NUM 3
#endif
#if defined TARGET_expression4
# define NUM 4
#endif
#if defined TARGET_expression5
# define NUM 5
#endif
#include "lang_titles.inc"
\text{f=randitem(f,g,h)}

#if defined TARGET_expression1
 \integer{a=randint(2..9)}
 \integer{b=0}
 \text{x=wims(values v for v=2 to 9)}
 \text{x=shuffle(\x)}
#endif
#if defined TARGET_expression2
 \integer{a=0}
 \integer{b=randitem(1,-1)*randint(2..9)}
 \text{x=wims(values v for v=2 to 9)}
 \text{x=shuffle(\x)}
#endif
#if defined TARGET_expression3
 \text{v=wims(values v for v=2 to 9)}
 \text{v=shuffle(\v)}
 \integer{b=\v[2]}
 \integer{a=\v[1]}
 \text{x=wims(values v for v=2 to 9)}
 \text{x=shuffle(\x)}
#endif
#if defined TARGET_expression4
 \text{v=wims(values v,-v for v=2 to 9)}
 \text{v=shuffle(\v)}
 \integer{b=\v[2]}
 \integer{a=\v[1]}
 \text{x=wims(values -v for v=2 to 9)}
 \text{x=shuffle(\x)}
#endif
#if defined TARGET_expression5
 \text{b=shuffle(1/2,1/4,1/3,2/3,3/4,1/5,2/5,3/5,4/5)}
 \text{a=\b[1]}
 \text{b=\b[2]}
 \text{x=wims(values -v for v=2 to 9)}
 \text{x=shuffle(\x)}
#endif

\text{y=texmath(simplify(\a*\x[1]+\b)),texmath(simplify(\a*\x[2]+\b))}
\text{rep=simplify(\a*x+\b)}

\statement{
Soit \(\f\) une fonction affine. Retrouver la formule de la fonction \(\f\) sachant que :
<div class="wimscenter"> \(\f(\x[1]) = \y[1] \quad\quad\quad \f(\x[2]) = \y[2])</div>
<b>Votre réponse :</b>
<div class="wimscenter">
<label for="reply1">\(\f : x \mapsto )</label> \embed{r1,9}
</div>}

\answer{Réponse}{\rep}{type=auto}
