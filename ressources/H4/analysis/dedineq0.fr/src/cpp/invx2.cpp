target=invx2
#include "lang_titles.inc"
#include "lang.inc"

\author{Gang Xiao}
\email{xiao@unice.fr}
\language{fr}
\options{nofloat askresult}
\methods{ineq/addterm, ineq/mulexp, ineq/divexp, ineq/exsides}
\minsteps{3}

\text{x=random(a,b,c,d,p,q,r,s,t,u,v,x,y,z)}

\text{sh=shuffle(15)}
\integer{a=(item(1,\sh)+1)*random(-1,1)}
\integer{b=(item(2,\sh)+1)*random(-1,1)}
\integer{c=(item(3,\sh)+1)}
\integer{d=-(\b)}

\matrix{data=>,<,1
<,>,-1
}
\text{data=randomrow(\data)}
\text{s1=item(1,\data)}
\text{s2=item(2,\data)}
\integer{it=item(3,\data)}

\function{left=\a/(\x + \b)}
\real{tester=\a*(\it)}
\integer{c=\tester>0?\c:-\c}
\text{sign=random(<,>,<=,>=)}
\equivalence{\left \sign \c}
\context{\x \s1 \d}
\statement{
  \name_statement[1] \(\left \sign \c), \name_statement[2] \(\x \s1 \d).
<p>
\name_objectif[1] \(\x\) \name_and \name_objectif[2]
</p>
}

\text{cut=wims(translate internal <=> to , , in \equivalence)}
\text{newleft=item(1,\cut)}
\text{newright=item(2,\cut)}

\condition{\newleft issametext \x and \x notin \newright}
