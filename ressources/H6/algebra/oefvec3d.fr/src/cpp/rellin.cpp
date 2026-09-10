target=rellin

#include "author.inc"
#include "lang_titles.inc"

\precision{10000}
#include "lang.inc"

\integer{c11=random(2..10)*random(-1,1)}
\integer{c12=random(2..10)*random(-1,1)}
\integer{c13=random(2..10)*random(-1,1)}
\integer{c14=random(2..10)*random(-1,1)}
\integer{c21=random(2..10)*random(-1,1)}
\integer{c22=random(2..10)*random(-1,1)}
\integer{c23=random(2..10)*random(-1,1)}
\integer{c24=random(2..10)*random(-1,1)}
\integer{c31=random(2..10)*random(-1,1)}
\integer{c32=random(2..10)*random(-1,1)}
\integer{c33=random(2..10)*random(-1,1)}
\integer{c34=random(2..10)*random(-1,1)}
\statement{\name_enonce:
<div class="wimscenter">
\( v_1 = (\c11,\c21,\c31) \),
 \(v_2 = (\c12,\c22,\c32) \),
 \(v_3 = (\c13,\c23,\c33) \),
 \(v_4 = (\c14,\c24,\c34)\).
</div>
\name_question
<div class="wimscenter">
	\(a v_1 + b v_2 + c v_3 + d v_4 = 0\).
</div>
}

\answer{\(a\)}{\sx}
\answer{\(b\)}{\sy}
\answer{\(c)}{\sz}
\answer{\(d)}{\st}
\condition{\(a\), \(b\), \(c\), \(d\) \name_cond1}{
abs(\sx)+abs(\sy)+abs(\sz)+abs(\st)>0 and
abs(round(\sx)-(\sx))<=0 and
abs(round(\sy)-(\sy))<=0 and
abs(round(\sz)-(\sz))<=0 and
abs(round(\st)-(\st))<=0
}

\condition{\name_cond2}{
(\c11)*(\sx)+(\c12)*(\sy)+(\c13)*(\sz)+(\c14)*(\st)=0 and
(\c21)*(\sx)+(\c22)*(\sy)+(\c23)*(\sz)+(\c24)*(\st)=0 and
(\c31)*(\sx)+(\c32)*(\sy)+(\c33)*(\sz)+(\c34)*(\st)=0
}

