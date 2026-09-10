target=sumprod2
#define NUM II
#include "header.inc"
#include "lang_titles.inc"
#include "lang.inc"
\language{fr}
\options{nofloat}
\methods{ineq/rewrite, ineq/simpdeduc, ineq/lincomb,
ineq/mulnum, ineq/divnum, ineq/addineq, ineq/mulineq,
ineq/sqrpos}
\minsteps{4}

\matrix{vars=a,b
c,d
r,s
s,t
u,v
x,y
}
\text{vars=randomrow(\vars)}
\text{x=item(1,\vars)}
\text{y=item(2,\vars)}
\text{kind=random(\name_kind)}

\text{cs=shuffle(25)}
\integer{c1=item(1,\cs)+2}
\integer{c2=item(2,\cs)+2}
\integer{n=random(50..100)*2}
\rational{s=\n^2/(4*\c1*\c2)}

\text{less=random(<,<=)}
\function{sum=\c1*\x + \c2*\y}
\text{ltn=\sum \less \n}

\context{\x > 0
\y > 0
\ltn
}
\text{prv=\x*\y \less \s}
\goal{\prv}
\statement{\name_enonce[1] \(\x\) \name_and \(\y\) \name_enonce[2] \kind \name_enonce[3] \name_enonce[4]
\(\ltn\).
\name_prove
<div class="wimscenter">\( \prv \) .</div>
}
