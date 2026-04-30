target=majsqr1
#include "author.inc"
#include "lang_titles.inc"
#include "lang.inc"
\language{fr}
\options{nofloat}
\methods{ineq/addterm, ineq/mulexp, ineq/exsides,
  ineq/trans, ineq/constineq, ineq/addineq, ineq/mulineq,
  ineq/sqrpos,ineq/splitineq}
\minsteps{2}

\text{x=random(a,b,c,d,r,s,t,x,y,z)}
\integer{a=random(2..100)}
\integer{sqr=\a^2}
\text{empty=}

\text{eqr=random(,=)}
\text{less=<\eqr}
\text{more=>\eqr}
\text{left=\x \more -\a}
\text{right=\x \less \a}
\context{\left
\right
}

\goal{\x^2 \less \sqr}
\text{oldgoal=\goal}


\statement{\name_statement[1] \(\x) \name_statement[2] \(-\a \less \x \less \a).
\name_statement[3]
  <div class="wimscenter">
	\( \oldgoal )
	<span style="color:grey">\(( = \a^2 ))</span>.
  </div>
}

\hint{
  \name_hint[1] \(\x), \name_hint[2]
  <p>
  \name_hint[3] \(\x^2\less\sqr) \name_hint[4] \(\sqr - \x^2 \more 0), \name_hint[5]
  \((\a + \x)(\a - \x) \more 0). \name_hint[6]?
  </p>
}

\help{
 \name_help
}
