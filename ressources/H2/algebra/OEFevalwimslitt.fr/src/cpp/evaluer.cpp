target=evaluer1 evaluer2 evaluer3 evaluer4 evaluer5
#if defined TARGET_evaluer1
# define NUM 1
#endif
#if defined TARGET_evaluer2
# define NUM 2
#endif
#if defined TARGET_evaluer3
# define NUM 3
#endif
#if defined TARGET_evaluer4
# define NUM 4
#endif
#if defined TARGET_evaluer5
# define NUM 5
#endif
#include "author.inc"
#include "lang_titles.inc"
#include "lang.inc"

\text{v=shuffle(2,3,4,5,6,7,8,9)}
\text{x=randitem(x,y,a,b)}

#if defined TARGET_evaluer1
 \text{enonce=\x+\v[2]}
 \text{val=\v[1]}
 \text{aff=texmath(\enonce)}
#endif
#if defined TARGET_evaluer2
 \text{enonce=\x-\v[2]}
 \text{val=\v[1]}
 \text{aff=texmath(\enonce)}
#endif
#if defined TARGET_evaluer3
 \text{enonce=\v[2]*\x}
 \text{aff=\v[2]\times \x}
 \text{val=\v[1]}
#endif
#if defined TARGET_evaluer4
 \text{enonce=-\v[2]*\x}
 \text{val=\v[1]}
 \text{aff=texmath(\enonce)}
#endif
#if defined TARGET_evaluer5
 \text{enonce=-\v[2]*\x+\v[3]}
 \text{val=\v[1]}
 \text{aff=texmath(\enonce)}
#endif

\integer{rep=evalue(\enonce,\x=\val)}

\statement{
\name_instruction[1] \(\aff\) \name_instruction[2] \(\x=\val\) ?
<p>
<b>\name_youranswer :</b> \embed{r1,7}</p>}

\answer{}{\rep}{type=numexp}
\latex{\begin{statement}
\name_instruction[1] \(\aff\) \name_instruction[2] \(\x=\val\) ?
\end{statement}
}
