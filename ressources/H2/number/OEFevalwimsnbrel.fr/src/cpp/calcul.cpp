target=calculA1 calculA2 calculA3 calculA4 calculA5 calculC1 calculC2 calculC3 calculC4 calculC5 calculB1 calculB2 calculB3 calculB4 calculB5
#include "author.inc"
#include "lang_titles.inc"
#include "lang.inc"
\text{v=wims(values v/10 for v=10 to 100)}
\text{v=shuffle(\v)}

#if defined TARGET_calculA1
 \text{calcul=-\v[1]+(-\v[2])}
#endif
#if defined TARGET_calculA2
 \text{calcul=\v[1]+(-\v[2])}
#endif
#if defined TARGET_calculA3
 \text{calcul=(-\v[1])+\v[2]}
#endif
#if defined TARGET_calculA4
 \text{calcul=\v[1]+\v[2]}
#endif
#if defined TARGET_calculA5
 \text{tmp=shuffle(-\v[1],\v[2],-\v[3])}
 \text{calcul=\tmp[1]}
 \for{k=2 to 3}{\text{calcul=\tmp[\k]<0?\calcul+(\tmp[\k]):\calcul+\tmp[\k]}}
#endif
#if defined TARGET_calculC1
 \text{calcul=-\v[1]-(-\v[2])}
#endif
#if defined TARGET_calculC2
 \text{calcul=\v[1]-(-\v[2])}
#endif
#if defined TARGET_calculC3
 \text{calcul=(-\v[1])-\v[2]}
#endif
#if defined TARGET_calculC4
 \text{calcul=\v[1]-\v[2]}
#endif
#if defined TARGET_calculC5
 \text{tmp=shuffle(-\v[1],\v[2],-\v[3])}
 \text{calcul=\tmp[1]}
 \for{k=2 to 3}{\text{calcul=\tmp[\k]<0?\calcul-(\tmp[\k]):\calcul+\tmp[\k]}}
#endif
#if defined TARGET_calculB1
 \text{calcul=\v[1]-\v[2]+\v[3]}
#endif
#if defined TARGET_calculB2
 \text{calcul=\v[1]-(-\v[2])-\v[3]}
#endif
#if defined TARGET_calculB3
 \text{calcul=\v[1]-(\v[2]-(-\v[3]))}
#endif
#if defined TARGET_calculB4
 \text{calcul=-\v[1]+(-\v[2])-\v[3]-(-\v[4])}
#endif
#if defined TARGET_calculB5
 \text{calcul=\v[1]-(-\v[2])+(-\v[3])-\v[4]}
#endif

\text{A=randitem(A,B,C,D,E,F,G,H)}
\real{rep=\calcul}
\statement{\name_question:
<div class="wimscenter">\(\A = \calcul)</div>}

\answer{\A}{\rep}{type=numexp}
