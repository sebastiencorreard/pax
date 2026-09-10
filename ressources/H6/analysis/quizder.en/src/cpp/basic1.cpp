target=basic1

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
\function{lin=\c1*x+\c2}
\text{cos=random(sin,cos)}
\function{f=randitem(
 \c1*x^random(2,3) + \c2,
 \c1*x^random(2,3) + \c2*x,
 \a1*\cos(x+\c1),
 \a1*\cos(\c1*x),
 sqrt(\c1*x+\c2),
 (x+\c1)^2,
 \a1*exp(x+\c1),
 \a1*exp(\c1*x),
 \a1*log(x+\c1),
 \a1*log(\c1*x)
)}
\function{F=diff(\f,x)}
\text{name_answer=\(f'(x)\)}
\text{f=texmath(\f)}
\statement{\name_statement \(f(x) = \f\).
}

\answer{\(f'(x)\)}{\F}{type=formal}

\latex{
\begin{statement}
\name_statement \(f(x) = \f\).
\end{statement}

}
