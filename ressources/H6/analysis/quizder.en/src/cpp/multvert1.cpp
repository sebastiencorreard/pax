target=multvert1
#define NUM
#include "header.inc"
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
\text{g=simplify((\f1)*f(x))}
\text{F1=simplify((diff(\f1,x))*f(x)+(\f1)*fprime)}
\text{F=wims(replace internal fprime by f'(x) in \F1)}
\text{f=texmath(\f)}

\statement{\name_statement \(g(x) = \g\).
}

\answer{\(g'(x)\)}{\F}{type=formal}

\latex{
\begin{statement}
\name_statement \(g(x) = \g\).
\end{statement}
}
