target=sum
#include "author.inc"
#include "lang_titles.inc"
#include "lang.inc"

\language{fr}
\options{nofloat}
\text{methrand=random(ineq/addterm,prf/contrapose)}
\methods{\methrand ineq/exsides,
  ineq/trans, ineq/addineq, ineq/mulineq}
\minsteps{2}

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
\integer{sum=\a + \b}
\text{empty=}

\text{eqr=random(,=)}
\text{moreless=shuffle(<,>)}
\text{less=item(1,\moreless)}
\text{more=item(2,\moreless)}
\text{ctx1=simplify(\x + \y \less\eqr \sum)}
\text{ctx2=\x \more= \a}
\text{prv=\y \less\eqr \b}

\context{\ctx1
\ctx2}
\goal{\prv}
\text{oldgoal=\goal}

\statement{\name_statement[1] \(\x) \name_statement[2] \(\y) \name_statement[3] \(\ctx1)
  \name_statement[4] \(\ctx2).
  \name_statement[5] \( \oldgoal ).
}
