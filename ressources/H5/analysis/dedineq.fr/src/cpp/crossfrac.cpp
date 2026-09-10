target=crossfrac crossfrac2

#ifdef TARGET_crossfrac
# define NUM I
#endif
#ifdef TARGET_crossfrac2
# define NUM II
#endif
#include "header.inc"
#include "lang_titles.inc"
#include "lang.inc"
\language{fr}
\options{nofloat expand}
\text{methrand=randitem(trans,addineq)}
\methods{ineq/rewrite, ineq/simpdeduc, ineq/mulexp, ineq/divexp,
ineq/\methrand, ineq/mulineq, ineq/sqrpos}
\minsteps{3}
#ifdef TARGET_crossfrac
\text{kind=randitem(\name_kind)}
\matrix{vars=a,b
c,d
x,y
r,s
s,t
p,q
}
\text{vars=randomrow(\vars)}
\text{x=item(1,\vars)}
\text{y=item(2,\vars)}
\matrix{data=>,>,>=,2
<,<,>=,2
<,>,<=,-2
>,<,<=,-2
}
#endif
#ifdef TARGET_crossfrac2
\text{kind=randitem(\name_kind)}
\text{x=randitem(a,b,c,d,r,s,t,u,v,x,y,z)}
\matrix{data=>,>=,2,\name_posneg[1]
<,<=,-2,\name_posneg[2]
}
#endif
\text{data=randomrow(\data)}
\text{s1=item(1,\data)}
#ifdef TARGET_crossfrac
\text{s2=item(2,\data)}
\text{sign=item(3,\data)}
\text{right=item(4,\data)}
#endif
#ifdef TARGET_crossfrac2
\text{sign=item(2,\data)}
\text{right=item(3,\data)}
\text{posneg=item(4,\data)}
\integer{y=random(6..99)}
#endif
\text{left=maxima(\x/\y + \y/\x;)}
\text{prv=\left \sign \right}
#ifdef TARGET_crossfrac
\context{\x \s1 0
\y \s2 0
}
#endif
#ifdef TARGET_crossfrac2
\context{\x \s1 0
}
#endif
\goal{\prv}

\statement{
#ifdef TARGET_crossfrac
\name_enonce[1] \kind \name_enonce[2]
\(\x \s1 0) \name_and \(\y \s2 0).
#endif
#ifdef TARGET_crossfrac2
\name_enonce[1] \kind \name_enonce[2] \posneg.
#endif
\name_prove \( \prv \).
}

