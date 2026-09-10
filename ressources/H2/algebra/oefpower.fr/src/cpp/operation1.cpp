target=operation1
#include "lang_titles.inc"
#include "author.inc"
#include "lang.inc"

\integer{p1=random(1..20)*randitem(-1,1)}
\integer{q1=random(1..20)*randitem(-1,1)}
\integer{pp1=random(1..20)*randitem(-1,1)}
\integer{qq1=random(1..20)*randitem(-1,1)}
\rational{a1=\p1 / \q1}
\rational{b1=\pp1 / \qq1}
\integer{n1=random(1..10)*randitem(-1,1)}

\rational{produit = pari( \a1*\b1)}
\real{bon=pari((\produit)^(\n1))}

\statement{
\name_statement :
<div class="wimscenter">
 \( (\a1)^{\n1} \times (\b1)^{\n1} = \) \embed{ reply1 ,8}<sup>\embed{reply2,3}</sup>
</div>
<div class="wims_instruction">\name_instruction \(a^p\).</div>
}

\answer{}{\rep1}
\answer{}{\rep2}
\real{H=pari((\rep1)^(\rep2))}
\condition{}{(\rep1=\produit or \rep1=(-1)*\produit or \rep1=1/\produit or \rep1=(-1)/\produit)
and (\rep2=\n1 or \rep2=(-1)*\n1) and (\H =\bon)}
