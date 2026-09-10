target=product
#include "header.inc"
#include "lang_titles.inc"
#include "lang.inc"
\language{fr}
\options{nofloat}
\methods{ineq/addterm, ineq/mulexp, ineq/divexp, ineq/exsides,
ineq/trans, ineq/addineq, ineq/mulineq,
prf/contrapose}
\minsteps{3}

\matrix{vars=a,b
c,d
x,y
r,s
s,t
p,q
}
\text{vars=randomrow(\vars)}
\text{x=item(1,\vars)}
\text{y=item(2,\vars)}

\integer{a=random(3..20)}
\integer{b=random(3..20)}
\integer{prod=\a*\b}
\text{empty=}

\text{eqr=random(,=)}
\text{less=<\eqr}
\text{more=>\eqr}
\text{ctx1=\x*\y \less \prod}
\text{ctx2=\x \more \a}
\text{prv=\y \less \b}

\context{\ctx1
\ctx2}
\goal{\prv}
\text{oldgoal=\goal}

\statement{\name_enonce \(\ctx1\) \name_and \(\ctx2\).
\name_prove \( \oldgoal \).
}
