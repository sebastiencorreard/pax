target=pointsentiers

#include "header.inc"
#include "lang_titles.inc"

\keywords{linear_system}
\integer{a=random(-1,1)*randint(1..10)}
\integer{b=random(-1,1)*randint(1..10)}
\integer{c=random(-1,1)*randint(1..10)}

\integer{d=pari(gcd(\a,\b))}

\integer{a=\a/\d}
\integer{b=\b/\d}

\function{f=maxima(\a*x+\b*y+\c)}

\text{fa=texmath(\f)}

\real{t1=}
\real{t2=}
\real{t3=}



#include "lang.inc"

\statement{\name_statement[1;]
\(\fa = 0\), \name_statement[2;].
<div class="wimscenter">
\name_statement[3;] M(\embed{reply 1,10}; \embed{reply 2,10}) \name_statement[4;].
</div>
}

\answer{\(x\)}{\rep1}{type=default}
\answer{\(y\)}{\rep2}{type=default}

\real{t1=evalue(\f,x=\rep1,y=\rep2)}
\real{t2=\rep1-floor(\rep1)}
\real{t3=\rep2-floor(\rep2)}

\condition{\name_condition1}{\t1=0}
\condition{\name_condition2}{\t2=0}
\condition{\name_condition3}{\t3=0}



