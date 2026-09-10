target=sumprod
#define NUM I
#include "header.inc"
#include "lang_titles.inc"
#include "lang.inc"
\language{fr}
\options{nofloat}
\methods{ineq/addterm, ineq/mulnum, ineq/divnum, ineq/exsides,
ineq/trans, ineq/constineq, ineq/addineq, ineq/mulineq,
ineq/sqrpos}
\minsteps{7}

\integer{n=random(100..200)}
\integer{s=ceil(\n^2/4)+random(100..500)}

\text{lt1=random(<,<=)}
\text{less=random(<,<=)}
\text{less2=<}
\text{grt2=>}
\text{pos=0 \lt1 a + b}
\text{ltn=a + b \less \n}

\context{\pos
\ltn
}
\goal{a*b \less2 \s}
\text{oldgoal=\goal}
\statement{\name_enonce
\(0 \lt1 \ltn\).
\name_prove
<div class="wimscenter">\( \oldgoal \).</div>
}
