target=twosqr

#include "header.inc"
#include "lang_titles.inc"
#include "lang.inc"

\language{fr}
\options{nofloat}
\methods{ineq/addterm, ineq/mulexp, ineq/divexp,
ineq/trans, ineq/addineq, ineq/exsides, prf/contrapose}

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
\text{more=>\eqr}
\text{less=<\eqr}
\matrix{data=\x^2 \more \y^2, \y \more 0, \x \more \y
\x^2 \more \y^2, \y \less 0, \x \less \y
\x^2 \less \y^2, \x \more 0, \x \less \y
\x^2 \less \y^2, \x \less 0, \x \more \y
}
\text{data=randomrow(\data)}
\text{prv=item(1,\data)}
\text{ctx1=item(2,\data)}
\text{ctx2=item(3,\data)}
\minsteps{4}

\context{\ctx1
\ctx2}
\goal{\prv}
\statement{\name_enonce[1] \(\x\) \name_and \(\y\) \name_enonce[2] \(\ctx1) \name_and \(\ctx2).
\name_prove \( \prv ).
}
