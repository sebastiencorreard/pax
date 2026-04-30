target=possqr2
#include "author.inc"
#include "lang_titles.inc"
#include "lang.inc"
\language{fr}
\options{nofloat}
\methods{ineq/rewrite, ineq/simpdeduc, ineq/mulexp, ineq/divexp,
  ineq/trans, ineq/obvineq, ineq/addineq, ineq/mulineq,
  ineq/splitineq
}
\minsteps{6}

\text{x=random(a,b,c,d,r,s,t,x,y,z)}
\integer{a=random(2..50)*random(2,-2)}
\integer{b=random((\a)^2/4+1..(\a)^2/4+50)}
\text{empty=}

\function{left=\x^2 + \a*\x + \b}
\goal{\left > 0}
\text{oldgoal=\goal}

\statement{\name_statement[1]\(\oldgoal) \name_statement[2] \(\x in \RR\).
}
