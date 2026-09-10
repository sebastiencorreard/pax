target=boundedsqr1 boundedsqr2
#if defined TARGET_boundedsqr1
# define NUM I
#endif
#if defined TARGET_boundedsqr2
# define NUM II
#endif
#include "header.inc"
#include "lang_titles.inc"
#include "lang.inc"
\language{fr}
\environ{QQ}
\options{nofloat}
\text{methcst=randitem(constineq,obvineq)}
\text{methnum=randitem(mulnum, divnum)}
\text{methadd=randitem(addnum, addterm)}
\text{methsid=randitem(addineq, trans)}
\text{methoth=randitem(ineq/sqrpos, ineq/splitineq, prf/splitgoal, exp/rewrite)}
\methods{ineq/\methadd, ineq/\methnum, ineq/exsides,
ineq/\methcst, ineq/\methsid, ineq/mulineq,
\methoth,prf/contrapose}

\text{x=randitem(a,b,c,d,r,s,t,x,y,z)}
\integer{a=random(8..60)}
\integer{sqr=\a^2}
\text{empty=}

\integer{ra=randitem(1,2)}
\if{\ra=1}{\minsteps{2}}{\minsteps{3}}
\text{eqr=randitem(,=)}
\text{less=<\eqr}
\text{more=>\eqr}
#if defined TARGET_boundedsqr1
\text{prv=item(\ra,\x \less \a, \x \more -\a)}
\text{ctx=\x^2 \less \sqr}
\context{\ctx}
#endif
#if defined TARGET_boundedsqr2
\text{prv=item(\ra,\x \more \a, \x \less -\a)}
\text{ctx1=\x^2 \more \sqr}
\text{ctx2=item(\ra,\x >random(,=) 0, \x <random(,=) 0)}
\context{\ctx1
\ctx2}
#endif
\goal{\prv}
\text{oldgoal=\goal}
\statement{
\name_enonce
#if defined TARGET_boundedsqr1
\(\ctx = \a^2\).
#endif
#if defined TARGET_boundedsqr2
\(\ctx2) \name_and
\(\ctx1 = \a^2\).
#endif
\name_prove \( \oldgoal \).
}
#if defined TARGET_boundedsqr1
\hint{
\name_hint
}
#endif
