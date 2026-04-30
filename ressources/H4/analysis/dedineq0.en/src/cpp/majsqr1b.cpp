target=majsqr1b
#include "author.inc"
#include "lang_titles.inc"
#include "lang.inc"
\language{fr}
\options{nofloat}
\methods{ineq/addterm, ineq/mulexp, ineq/exsides,
  ineq/trans, ineq/constineq, ineq/addineq, ineq/mulineq
  ineq/sqrpos}
\minsteps{4}

\text{x=random(a,b,c,d,r,s,t,x,y,z)}
\integer{a=random(2..100)}
\integer{sqr=\a^2}
\integer{Sqr=\sqr+random(2..200)}

\text{eqr=random(,=)}
\text{less=<\eqr}
\text{more=>\eqr}
\text{goal=\x^2<\Sqr}
\text{left=\x \more -\a}
\text{right=\x \less \a}
\context{\left
\right
}


\statement{\name_statement[1] \(\x) \name_statement[2] \(-\a \less \x \less \a).
\name_statement[3]	\( \x^2 < \Sqr ) .
}

\text{cut=wims(nospace \newobject)}

\condition{\cut issametext \goal}
