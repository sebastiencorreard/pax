target=sumprod3a
#define NUM I
#include "header.inc"
#include "lang_titles.inc"
#include "lang.inc"
\language{fr}
\options{nofloat fixedgoal}
\text{methcst=randitem(constineq,obvineq)}
\text{methtra=randitem(trans,addineq)}
\methods{ineq/rewrite, ineq/simpdeduc, ineq/mulexp, ineq/lincomb,
ineq/\methcst, ineq/\methtra, ineq/mulineq, ineq/sqrpos}
\minsteps{8}

\matrix{vars=x,y,z
a,b,c
r,s,t
l,m,n
u,v,w
}
\text{vars=randomrow(\vars)}
\text{x=item(1,\vars)}
\text{y=item(2,\vars)}
\text{z=item(3,\vars)}

\integer{n=random(8..30)}
\integer{N=\n^3}
\text{range=randitem(\name_range)}

\text{less=random(<,<=)}
\text{ctx1=\x + \y + \z \less \n}
\text{ctx2=0 <= \x}
\text{ctx3=0 <= \y}
\text{ctx4=0 <= \z}
\text{prv=\x*\y*\z \less \N}

\context{\ctx1
\ctx2
\ctx3
\ctx4
}
\goal{\prv}

\statement{\name_enonce[1] \(\x, \y, \z\) \name_enonce[2] \range \name_enonce[3] \name_enonce[4]
\( \ctx1 \).
\name_prove
<div class="wimscenter">\(\prv\).</div>
}

\if{\newobject != $empty}{
 \text{cut=wims(exec mathexp cut inequality
\newobject)}
 \text{left=item(1,\cut)}
 \text{sign=item(2,\cut)}
 \text{right=item(3,\cut)}
 \if{\sign issametext \less}{
  \text{test1=simplify(\left-(\x*\y*\z))}
  \text{test2=simplify(\right-(\N))}
 }{
  \text{test1=simplify(\right-(\x*\y*\z))}
  \text{test2=simplify(\left-(\N))}
  \text{sign=wims(translate internal <> to >< in \sign)}
 }
}

\condition{\test1 = 0 and \test2 = 0 and \sign issametext \less}
