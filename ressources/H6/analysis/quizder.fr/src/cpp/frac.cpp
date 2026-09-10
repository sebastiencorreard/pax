target=frac1 frac2

#if defined TARGET_frac1
# define NUM I
#else
# define NUM II
#endif
#include "lang_titles.inc"
#include "lang.inc"
#include "header.inc"
\integer{a1=random(2..8)*random(1,-1)}
\integer{a2=random(2..8)*random(1,-1)}
\integer{c1=random(2..8)*random(1,-1)}
\integer{c2=random(2..8)*random(1,-1)}
\integer{c3=random(2..8)*random(1,-1)}
\integer{c4=random(2..8)*random(1,-1)}
\function{lin=\c1*x+\c2}
\text{cos=random(sin,cos)}
#if defined TARGET_frac1
\function{f=randitem(
 \a1/(\c1*x+\c2),
 \a1/(x^randint(3..8)+\c1),
 (\c1*x+\c2)/x^randint(2..6)
)}
#endif
#if defined TARGET_frac2
\function{f=randitem(
 \a1/(x^2+\c1*x+\c2),
 (\c1*x+\c2)/(\c3*x+\c4),
 \c1*x/(x^2+\c2*x+\c3),
 (\c1*x+\c2)/(\c3*x^2+random(\c4,\c4*x)),
 (\c1*x+\c2)/x^randint(3..6)
)}
#endif
\function{F=diff(\f,x)}

\statement{\name_statement \(f(x) = \f).
}

\answer{\(f'(x))}{\F}{type=formal}

