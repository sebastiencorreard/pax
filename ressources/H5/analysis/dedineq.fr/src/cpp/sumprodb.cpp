target=sumprodb
#include "header.inc"
#include "lang_titles.inc"
#include "lang.inc"
\language{fr}
\options{nofloat}
\methods{ineq/addterm, ineq/mulexp, ineq/divexp, ineq/exsides,
ineq/trans, ineq/constineq, ineq/addineq, ineq/mulineq,
ineq/sqrpos}
\minsteps{7}

\integer{n=random(100..200)}
\integer{s=ceil(\n^2/4)+random(50..200)}

\text{less=random(<,<=)}
\text{less2=<}
\text{grt2=>}
\text{pos=-\n \less a + b}
\text{ltn=a + b \less \n}

\context{\pos
\ltn
}

\statement{\name_enonce
\(-\n \less a + b \less \n\).
\name_prove
<div class="wimscenter">\( a*b \less2 \s \) .</div>
}

\text{cut=wims(nospace \newobject)}
\text{ab=a*b}
\text{ba=b*a}

\condition{\cut iswordof \ab\less2\s \ba\less2\s
	\s\grt2\ab \s\grt2\ba
}
