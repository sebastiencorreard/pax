target=operation2
#include "lang_titles.inc"
#include "author.inc"
\computeanswer{no}
#include "lang.inc"

\integer{p1=random(1..20)*randint(-1,1)}
\integer{q1=random(1..20)*randint(-1,1)}
\integer{pp1=random(1..20)*randint(-1,1)}
\integer{qq1=random(1..20)*randint(-1,1)}

\rational{ a1=\p1 / \q1}
\rational{ b1=\pp1 / \qq1}
\integer{ n1=random(1..10)*randint(-1,1)}

\rational{ quotient = pari( (\a1) / (\b1))}
\real{bon=pari((\quotient)^(\n1))}

\statement{
\name_statement:
<div class="wimscenter">
 \( (\a1)^{\n1} \div (\b1)^{\n1} = \) \embed{ reply1 ,8}<sup>\embed{reply2,3}</sup>
</div>
<div class="wims_instruction">\name_instruction \(a^p\).</div>
}
\answer{}{\rep1}
\answer{}{\rep2}
\real{H=pari((\rep1)^(\rep2))}
\condition{}{(\rep1=\quotient or \rep1=-1*\quotient or \rep1=1/\quotient or \rep1=-1/\quotient) and (\rep2=\n1 or \rep2=-1*\n1) and (\H =\bon)}
