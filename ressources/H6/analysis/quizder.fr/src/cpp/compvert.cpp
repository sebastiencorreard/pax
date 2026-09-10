target=compvert1a compvert1b
#include "header.inc"
#if defined TARGET_compvert1a
# define NUM Ia
#endif
#if defined TARGET_compvert1b
# define NUM Ib
#endif
#include "lang_titles.inc"
#include "lang.inc"
\integer{a1=random(2..8)*random(1,-1)}
\integer{a2=random(2..8)*random(1,-1)}
\integer{c1=random(2..8)*random(1,-1)}
\integer{c2=random(2..8)*random(1,-1)}
\integer{c3=random(2..8)*random(1,-1)}
\integer{c4=random(2..8)*random(1,-1)}
\function{f1=slib(data/randline src/simple1.data)}
\function{f1=maxima(subst(\c1,c1,subst(\c2,c2,subst(\c3,c3,subst(\c4,c4,\f1)))))}
#if defined TARGET_compvert1b
\text{g=f(\f1)}
\function{der=diff(\f1,x)}
\text{F1=simplify((\der)*fprime)}
\text{F=wims(replace internal fprime by f'(\f1) in \F1)}
#endif
#if defined TARGET_compvert1a
\text{g=maxima(subst(f(x),x,\f1))}
\function{der=diff(\f1,x)}
\text{FF=maxima(subst(f(x),x,\der))}
\text{F1=simplify((\FF)*fprime)}
\text{F=wims(replace internal fprime by f'(x) in \F1)}
#endif
\statement{\name_statement \(g(x) = \g).
\name_question
}

\answer{\(g'(x))}{\F}{type=formal}
