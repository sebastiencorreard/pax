target=sollin
#include "header.inc"
#include "lang_titles.inc"
#include "lang.inc"
\language{fr}
\options{nofloat askresult}
\methods{ineq/addterm, ineq/mulnum, ineq/divnum, ineq/exsides}
\minsteps{2}

\integer{a=random(2..20)*random(-1,1)}
\integer{b=random(2..20)*random(-1,1)}
\integer{c=random(2..20)*random(-1,1)}
\integer{d=random(1..20)*random(-1,1)}

\function{left=\a*x + \d}
\text{sign=randitem(<,<=,>,>=)}
\function{right=\b*x + \c*y}
\text{rightvar=}
\equivalence{\left \sign \right}

\statement{
\name_enonce[1] \(\y\) \name_enonce[2] \(\left \sign \right\).
<p>
\name_aim[1] \(\y\), \name_aim[2] \(\x\).
</p>
}

\text{cut=wims(translate internal <=> to , , in \equivalence)}
\text{newleft=item(1,\cut)}
\text{newright=item(2,\cut)}
\text{rightvar=wims(varlist \newright)}
\text{empty=}

\condition{\newleft issametext y and
 (\rightvar issametext x or \rightvar issametext \empty)}
