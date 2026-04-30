target=compter decompter

#include "header.inc"
#include "lang_titles.inc"

\title{TITLE}
\title_it{TITLE_it}

\integer{basep=row(1,\confparm4)}
\text{S=row(3,\confparm4)}
\text{S=item(1 to \basep,\S)}

\text{p=wims(values v for v=1 to \basep-1)}
\text{p=\basep=2?shuffle(\p,\p,\p):shuffle(\p,\p)}
\integer{n=randint(2..3)}
\text{p=\n=2?0,\p[1],\p[2]:\p[1],\p[2],\p[3]}
\integer{N=\basep^3*\p[1]+\basep^2*\p[2]+\basep*\p[3]}
\integer{q=randint(2..3)}
\integer{r=randint(2..3)}
\text{nombre=}
#if defined TARGET_compter
  \integer{dep=\N-\q}
  \integer{arr=\N+\r}
  \integer{s=1}
#endif
#if defined TARGET_decompter
  \integer{arr=\N-\q}
  \integer{dep=\N+\r}
  \integer{s=-1}
#endif
\for{k=\dep to \arr step \s}{
 \text{t=slib(basep \k,\S)}
 \text{nombre=wims(append item \t to \nombre)}
}


#include "lang.inc"

\statement{\txtstatement1<p>
\txtstatement2 \(\overline{\nombre[1]}^{\basep}) \txta \(\overline{\nombre[-1]}^{\basep}).</p>
<div class="wimscenter">\embed{r1,29}</div>
<div class="wims_instruction">\txtinstruction</div>}

\answer{}{\reponse}{type=text}

\integer{nb=items(\nombre)}
\integer{f=1}
\text{aff=}
\text{printaff=}
\for{k=1 to \nb}{
 \text{test=slib(char2item \nombre[\k])}
 \text{test=slib(simplify \test)}
 \text{printaff=wims(replace internal , by in \test)}
 \text{aff=\aff \(\overline{\printaff}^{\basep})}
 \text{rep=wims(word \k of \reponse)}
 \text{rep=slib(char2item \rep)}
 \text{test2=slib(simplify \rep)}
 \if{\test notsametext \test2}{\integer{f=0}}
}
\condition{\txtanalyse}{\f=1}
\feedback{\f!=1}{\txtgoodanswer \aff}
