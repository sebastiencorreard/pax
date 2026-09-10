target=majsqr2
# define NUM II
#include "header.inc"
#include "lang_titles.inc"
#include "lang.inc"

\language{fr}
\options{nofloat}
\methods{ineq/addterm, ineq/mulexp, ineq/exsides,
ineq/trans, ineq/constineq, ineq/addineq, ineq/mulineq,
ineq/sqrpos}
\minsteps{2}

\text{x=randitem(a,b,c,d,r,s,t,x,y,z)}
\integer{a=random(2..100)}
\integer{b=random(2..100)}
\integer{c=max(\a,\b)}
\integer{sqr=\c^2}

\text{eqr=randitem(,=)}
\text{less=<\eqr}
\text{more=>\eqr}
\text{left=\x \more -\a}
\text{right=\x \less \b}
\context{\left
\right
}

\statement{\name_enonce \(-\a \less \x \less \b\).
\name_prove	\( \x^2 \less \sqr \).
}

\text{cut=wims(nospace \newobject)}

\condition{\cut issametext \x^2\less\sqr}
