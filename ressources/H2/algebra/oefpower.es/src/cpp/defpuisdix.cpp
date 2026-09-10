target=defpuisdix

#include "lang_titles.inc"
#include "author.inc"
#include "lang.inc"
\integer{ a1=random(1..10)}
\integer{ b1=random(1..10)*(-1)}
\integer{ b2=((-1*\b1)-1)}
\text{ result1=pari( (10)^(\a1))}
\text{result1=\result1}
\text{ result2=wims(makelist 0 for i = 1 to \b2)}
\text{ result2=wims(items2words \result2)}
\text{ result2=wims(nospace 0, \result2 1)}

\integer{expos = random(\a1,\b1)}
\if{\expos=\a1}{\text{result=\result1}}
\if{\expos=\b1}{\text{result=\result2}}

\statement{
\name_statement \(A = 10^{\expos}\)
<div class="wimscenter">
<label for="reply1">\(A = \)</label> \embed{ reply1,11}
</div>
<div class="wims_instruction">\name_instruction</div>
}
\answer{\(A\) }{\result}{type=case}
