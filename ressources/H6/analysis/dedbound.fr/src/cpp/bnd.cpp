target=fracbnd

#include "lang_titles.inc"
#include "lang.inc"

\author{Gang Xiao}
\email{xiao@unice.fr}
\language{fr}
\options{nofloat}
\text{rmeth=randitem(ineq/trans,ineq/addineq)}
\methods{ineq/rewrite, ineq/simpdeduc, ineq/mulexp, ineq/divexp,
  ineq/obvineq, \rmeth, ineq/mulineq,
  ineq/sqrpos,exp/rewrite}
\minsteps{5}
\variables{x}

\integer{a=random(1..20)*random(-1,1)}
\integer{b=random(2..20)}
\integer{c=random(2..10)*random(-1,1)}
\function{fn=(\c*x+\a)/(x^2+\b)}

\integer{orient=random(1,2)}
\text{sens=item(\orient,<,>)}
\text{osens=item(\orient,>,<)}

\text{orer=item(\orient,\name_majmin[1;])}
\text{orant=item(\orient,\name_majmin[2;])}

\statement{\orer \name_statement[1;] \(f(x) = \fn) \name_statement[2;] \(x in RR).
}

\text{cut=mathexp_cut(inequality \newobject)}
\integer{test=items(\cut)}
\if{\test=3}{
 \text{eq==}
 \text{sign=item(2,\cut)}
 \if{\sign iswordof \sens \sens\eq}{
  \text{left=item(1,\cut)}
  \text{right=item(3,\cut)}
 }
 \if{\sign iswordof \osens \osens\eq}{
  \text{left=item(3,\cut)}
  \text{right=item(1,\cut)}
 }
 \text{rtest=yacas(IsInteger(\right))}
 \text{ltest=yacas(Simplify((\fn)-(\left)))}
}

\condition{\ltest issametext 0 and \rtest issametext true}
