target=deg1
#include "author.inc"
#include "lang_titles.inc"
#include "lang.inc"
\language{fr}
\options{nofloat askresult}
\methods{ineq/addterm, ineq/mulnum, ineq/divnum, ineq/exsides, ineq/trans}
\minsteps{2}

\text{x=random(a,b,c,d,p,q,r,s,t,u,v,x,y,z)}

\text{nn=shuffle(20)}
\integer{a=(item(1,\nn)+1)*random(-1,1)}
\integer{b=(item(2,\nn)+1)*random(-1,1)}
\integer{c=(item(3,\nn)+1)*random(-1,1)}
\integer{d=(item(4,\nn)+1)*random(-1,1)}

\function{left=\a*\x + \b}
\function{right=\c*\x + \d}
\text{sign=random(<,<=,>,>=)}
\equivalence{\left \sign \right}

\statement{
  \name_statement[1] \(\left \sign \right).
<p>
  \name_objectif[1] \(\x\), \name_objectif[2]
</p>
}

\text{cut=wims(translate internal <=> to , , in \equivalence)}
\text{newleft=item(1,\cut)}
\text{newright=item(2,\cut)}

\condition{\newleft issametext \x and \x notin \newright}
