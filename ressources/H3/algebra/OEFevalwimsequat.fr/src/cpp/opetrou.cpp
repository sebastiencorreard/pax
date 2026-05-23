target=opetrou1 opetrou2 opetrou3 opetrou4 opetrou5

#define TITRE Opération à trou
#include "author.inc"
#if defined TARGET_opetrou1
# define NUM 1
#endif
#if defined TARGET_opetrou2
# define NUM 2
#endif
#if defined TARGET_opetrou3
# define NUM 3
#endif
#if defined TARGET_opetrou4
# define NUM 4
#endif
#if defined TARGET_opetrou5
# define NUM 5
#endif
\title{TITRE NUM}
\text{ch=wims(values v for v=2 to 10)}
\text{ch=shuffle(\ch)}
\integer{a=\ch[1]}
\integer{b=\ch[2]*randitem(1,-1)}

#if defined TARGET_opetrou1
 \integer{choix=randint(1..2)}
 \if{\choix=1}{
  \text{enonce1= }
  \text{enonce2= - \a = \b }
  \text{rep=simplify(\b+\a)}
 }{
  \text{enonce1=\a + }
  \text{enonce2= = \b }
  \text{rep=simplify(\b-\a)}
 }
 \text{type=}
#endif
#if defined TARGET_opetrou2
 \text{enonce1= \a - }
 \text{enonce2= = \b }
 \text{rep=simplify(\a-\b)}
 \text{type=}
#endif
#if defined TARGET_opetrou3
 \integer{b=abs(\b)}
 \text{enonce1= \a \times }
 \text{enonce2= = \b }
 \text{rep=simplify(\b/(\a))}
 \text{type=noreduction}
#endif

#if defined TARGET_opetrou4
 \integer{b=abs(\b)}
 \text{enonce1= }
 \text{enonce2= \div \a = \b }
 \text{rep=simplify(\b*(\a))}
 \text{type=}
#endif
#if defined TARGET_opetrou5
 \integer{b=abs(\b)}
 \text{enonce1= \a \div }
 \text{enonce2= = \b }
 \text{rep=simplify(\a/(\b))}
 \text{type=noreduction}
#endif
\text{name_enonce=Compléter l'opération à trou suivante&nbsp;}
\statement{
  \name_enonce
<div class="wimscenter"><label for="reply1">\(\enonce1)</label> \embed{r1,5} \(\enonce2).</div>}

\answer{Réponse}{\rep}{type=numexp}{option=\type}
