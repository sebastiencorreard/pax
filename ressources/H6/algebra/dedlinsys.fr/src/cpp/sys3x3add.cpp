target=sys3x3add
#include "lang_titles.inc"
#include "lang.inc"
\author{Gang Xiao}
\email{xiao@unice.fr}
\language{fr}
\environ{QQ}
\options{nofloat fixedgoal}
\minsteps{6}
\methods{eq/lincomb, eq/addnum, eq/mulnum, eq/divnum, eq/exsides, eq/addterm}

\text{x=random(a,b,c,d,r,s,t,x,y,z)}
\text{x=x}
\text{y=y}
\text{z=z}
\integer{c11=random(2..10)*random(-1,1)}
\integer{c12=random(2..10)*random(-1,1)}
\integer{c13=random(2..10)*random(-1,1)}
\integer{c21=random(2..10)*random(-1,1)}
\integer{t=abs((\c12)*(\c21)/(\c11))}
\integer{c22=\t>11?random(2..10)*random(-1,1):random(\t+2..\t+6)*random(-1,1)}
\integer{c23=random(2..10)*random(-1,1)}
\integer{c31=random(2..10)*random(-1,1)}
\integer{c32=random(2..10)*random(-1,1)}
\integer{t=abs(((\c31)*(\c22)*(\c13)-(\c31)*(\c23)*(\c12)+(\c32)*(\c23)*(\c11)-(\c32)*(\c21)*(\c13))
		/((\c11)*(\c22)-(\c12)*(\c21)))}
\integer{c33=\t>11?random(2..10)*random(-1,1):random(\t+2..\t+6)*random(-1,1)}

\integer{sx=random(-20..20)}
\integer{sy=random(-20..20)}
\integer{sz=random(-20..20)}
\integer{b1=(\c11)*(\sx)+(\c12)*(\sy)+(\c13)*(\sz)}
\integer{b2=(\c21)*(\sx)+(\c22)*(\sy)+(\c23)*(\sz)}
\integer{b3=(\c31)*(\sx)+(\c32)*(\sy)+(\c33)*(\sz)}
\function{left1=\c11*\x + \c12*\y + \c13*\z}
\function{left2=\c21*\x + \c22*\y + \c23*\z}
\function{left3=\c31*\x + \c32*\y + \c33*\z}
\text{prv1=\x = \sx}
\text{prv2=\y = \sy}
\text{prv3=\z = \sz}

\context{\left1 = \b1
\left2 = \b2
\left3 = \b3}
\goal{\prv1
\prv2
\prv3
}
\text{eq_math1=texmath(\left1 = \b1)}
\text{eq_math2=texmath(\left2 = \b2)}
\text{eq_math3=texmath(\left3 = \b3)}
\text{eq_math=wims(replace internal = by &= in
  \eq_math1\\\eq_math2\\\eq_math3)}

\statement{\name_statement
<div class="wimscenter">
  \(\begin{cases} \eq_math\end{cases}\)
</div>
\name_solution \( \prv1 ), \( \prv2 ), \( \prv3 ).
}
