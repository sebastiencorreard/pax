target=majsqr2b
# define NUM IIb
#include "header.inc"
#include "lang_titles.inc"
#include "lang.inc"
\language{fr}
\options{nofloat}
\methods{ineq/addterm, ineq/mulexp, ineq/exsides,
ineq/trans, ineq/constineq, ineq/addineq, ineq/mulineq,
ineq/sqrpos}
\minsteps{4}

\text{x=randitem(a,b,c,d,r,s,t,x,y,z)}
\integer{a=random(2..100)}
\integer{b=random(2..100)}
\integer{c=max(\a,\b)}
\integer{sqr=\c^2}
\integer{Sqr=\sqr+random(2..200)}

\text{eqr=randitem(,=)}
\text{less=<\eqr}
\text{more=>\eqr}
\text{left=\x \more -\a}
\text{right=\x \less \b}
\text{goal=\x^2<\Sqr}
\context{\left
\right
}

\statement{\name_enonce \(-\a \less \x \less \b\).
\name_prove	\( \x^2 < \Sqr \).
}

\text{cut=wims(nospace \newobject)}

\condition{\cut issametext \goal}

