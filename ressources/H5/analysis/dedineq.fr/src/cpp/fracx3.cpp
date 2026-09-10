target=fracx3
# define NUM III
#include "header.inc"
#include "lang_titles.inc"
#include "lang.inc"\title{Fraction simple III}

\language{fr}
\options{nofloat}
\methods{ineq/rewrite, ineq/simpdeduc, ineq/mulexp, ineq/divexp
ineq/trans, ineq/addineq, ineq/mulineq, ineq/splitineq}
\minsteps{6}

\text{x=randitem(a,b,c,d,p,q,r,s,t,u,v,x,y,z)}

\text{sh=shuffle(15)}
\integer{a=(item(1,\sh)+1)*random(-1,1)}
\integer{b=(item(2,\sh)+1)*random(-1,1)}
\integer{c=(item(3,\sh)+1)*random(-1,1)+1}
\integer{d=-(\b)}

\text{data=randomrow(\data)}
\text{s1=item(1,\data)random(,=)}
\text{s2=item(2,\data)}
\integer{it=item(3,\data)}

\function{left=(\x + \a)/(\x + \b)}
\real{tester=(\a-(\b))*(\c-1)}
\text{eqr=randitem(,=)}
\text{sign=\c>1?>\eqr:<\eqr}
\rational{mid=(\b*\c-\a)/(1-(\c))}
\text{ctx1=\x != \d}
\text{ctx2=\left \sign \c}
\if{\tester>0}{
 \text{prv1=\x > \d}
 \text{prv2=\x <\eqr \mid}
 \text{sol=\d < \x <\eqr \mid}
}{
 \text{prv1=\x < \d}
 \text{prv2=\x >\eqr \mid}
 \text{sol=\mid <\eqr \x < \d}
}
\context{\ctx1
\ctx2}
\goal{\prv1
\prv2}

\statement{
\name_enonce[1] \(\ctx2\). (\(\ctx1\))
<p>
(\name_enonce[2] \(\sol\).)
</p>
}

