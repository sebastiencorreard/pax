target=poly
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
 \c1*x^3 + \c2*random(x,x^2) + \c3,
 \c1*x^2 + \c2*x + \c3,
 \c1*x^4 + \c2*random(x^2,x^3) + random(\c3,\c3*x)
)}
\function{F=diff(\f,x)}

\statement{\name_statement \(f(x) = \f).
}

\answer{ \(f'(x))}{\F}{type=formal}
