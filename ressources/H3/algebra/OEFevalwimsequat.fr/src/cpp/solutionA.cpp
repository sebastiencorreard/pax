target=solution1 solution2 solution3
#include "author.inc"
#define TITRE Solution d'une équation
#if defined TARGET_solution1
# define NUM 1
#endif
#if defined TARGET_solution2
# define NUM 2
#endif
#if defined TARGET_solution3
# define NUM 3
#endif
\title{TITRE NUM}


\text{x=x}
\text{v=wims(values v,-v for v=2 to 5)}
\text{v=shuffle(\v)}
\text{m1=randitem(\v[1]*\x+\v[2],\v[2]+\v[1]*\x)}
\integer{nrep=randint(1..2)}

#if defined TARGET_solution1
 \integer{nombre=abs(\v[3])}
 \integer{nosol=\nombre+\v[4]}
 \text{m2=\nrep=1?\nombre:\nosol}
 \integer{m2=evalue(\m1,\x=\m2)}
#endif
#if defined TARGET_solution2
 \integer{nombre=-abs(\v[3])}
 \integer{nosol=\nombre+\v[4]}
 \text{m2=\nrep=1?\nombre:\nosol}
 \integer{m2=evalue(\m1,\x=\m2)}
#endif
#if defined TARGET_solution3
 \integer{denom=randint(2..5)}
 \text{t1=wims(values v for v=1 to 3*\denom)}
 \text{t2=wims(values v*\denom for v=1 to 3)}
 \text{n=wims(listcomplement \t2 in \t1)}
 \text{n=shuffle(\n)}
 \integer{sg=randitem(1,-1)}
 \text{nombre=simplify(\sg*\n[1]/\denom)}
 \text{nosol=simplify(\sg*\n[2]/\denom)}
 \text{m2=\nrep=1?\nombre:\nosol}
 \text{m2=evalue(\m1,\x=\m2)}
 \text{m2=simplify(\m2)}
 \text{d=wims(replace internal / by , in \m2)}
 \integer{nit=items(\d)}
 \text{dm=\nit=2?\d[2]:1}
 \integer{a=\v[1]*\dm}
 \integer{b=\v[2]*\dm}
 \text{m1=randitem(\a*\x+\b,\b+\a*\x)}
 \integer{m2=\d[1]}
 \text{nombre=texmath(\nombre)}
 \text{nombre=\(\nombre)}
#endif

\text{m1=texmath(\m1)}
\text{enonce=\m1 = \m2}
\text{ltrep=Oui&#44; \nombre est solution de l'équation,Non&#44; \nombre n'est pas solution de l'équation}

\statement{
\nombre est-il solution de l'équation :
<div class="wimscenter">\(\enonce)</div>

<b>Votre réponse :</b>
<blockquote>
 <div>\embed{r1,1}</div>
 <div>\embed{r1,2}</div>
</blockquote>}

\answer{Réponse}{\nrep;\ltrep}{type=radio}
