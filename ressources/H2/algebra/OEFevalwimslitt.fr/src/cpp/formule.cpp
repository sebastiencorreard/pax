target=formule1 formule2 formule3 formule4 formule5

#if defined TARGET_formule1
# define NUM 1
#endif
#if defined TARGET_formule2
# define NUM 2
#endif
#if defined TARGET_formule3
# define NUM 3
#endif
#if defined TARGET_formule4
# define NUM 4
#endif
#if defined TARGET_formule5
# define NUM 5
#endif
#include "author.inc"
#include "lang_titles.inc"
#include "lang.inc"
\text{v=shuffle(2,3,4,5,6,7,8,9)}
\text{x=randitem(x,y,a,b)}

# if defined TARGET_formule4
 \text{enonce=la somme de, et du produit de, et de}
# endif
#if defined TARGET_formule1
 \text{enonce=\enonce[1] \(\x\) \enonce[2] \v[1]}
 \text{rep=\x+\v[1],\v[1]+\x}
#endif
#if defined TARGET_formule2
 \text{enonce=\enonce[1] \(\x\) \enonce[2] \v[1]}
 \text{rep=\x-\v[1]}
#endif
#if defined TARGET_formule3
 \text{enonce=\enonce[1] \(\x\) \enonce[2] \v[1]}
 \text{rep=\x*\v[1],\v[1]*\x}
#endif
#if defined TARGET_formule4
 \text{enonce=\enonce[1] \v[1] \enonce[2] \(\x\) \enonce[3] \v[2]}
 \text{rep=\v[1]+\x*\v[2],\v[2]*\x+\v[1]}
#endif
#if defined TARGET_formule5
 \text{enonce=\enonce[1] \v[1] \enonce[2] \(\x\) \enonce[3] \v[2]}
 \text{rep=\v[1]*(\x+\v[2]),(\v[2]+\x)*\v[1],\v[1]*(\v[2]+\x),(\x+\v[2])*\v[1]}
#endif

\statement{
\name_instruction[1] \(\x\), \name_instruction[2] \enonce ?
<div>
<span class="bold">\name_answer&nbsp;: </span> \embed{r1,7}
</div>}

\answer{}{\rep}{litexp}
\latex{\begin{statement}
\name_instruction[1] \(\x\), \name_instruction[2] \enonce ?
\end{statement}
}
