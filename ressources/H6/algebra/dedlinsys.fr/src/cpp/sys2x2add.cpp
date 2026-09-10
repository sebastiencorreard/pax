target=sys2x2add
#include "lang_titles.inc"
#include "lang.inc"
\author{Gang Xiao}
\email{xiao@unice.fr}
\language{fr}
\environ{QQ}
\options{nofloat fixedgoal}
\minsteps{2}
\methods{eq/lincomb, eq/addnum, eq/mulnum, eq/divnum, eq/exsides, eq/addterm}

\text{x=random(a,b,c,d,r,s,t,x,y,z)}
\text{x=x}
\text{y=y}
\integer{c11=random(2..20)*random(-1,1)}
\integer{c12=random(2..20)*random(-1,1)}
\integer{c21=random(2..20)*random(-1,1)}
\integer{t=abs((\c12)*(\c21)/(\c11))}
\integer{c22=\t>21?random(2..20)*random(-1,1):random(\t+2..\t+10)*random(-1,1)}
\integer{sx=random(-20..20)}
\integer{sy=random(-20..20)}
\integer{b1=(\c11)*(\sx)+(\c12)*(\sy)}
\integer{b2=(\c21)*(\sx)+(\c22)*(\sy)}
\function{left1=\c11*\x + \c12*\y}
\function{left2=\c21*\x + \c22*\y}
\text{prv1=\x = \sx}
\text{prv2=\y = \sy}

\context{\left1 = \b1
\left2 = \b2}
\goal{\prv1
\prv2}
\text{eq_math1=texmath(\left1 = \b1)}
\text{eq_math2=texmath(\left2 = \b2)}
\text{eq_math=wims(replace internal = by &= in
  \eq_math1\\\eq_math2)}

\statement{\name_statement
<div class="wimscenter">
  \(\begin{cases} \eq_math\end{cases}\)
</div>
\name_solution \( \prv1 ), \( \prv2 ).
}
