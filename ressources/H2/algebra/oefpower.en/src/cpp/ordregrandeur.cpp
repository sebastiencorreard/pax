target=ordregrandeur

#include "lang_titles.inc"
#include "author.inc"
#include "lang.inc"
\integer{ n1 = random(3..6)}
\integer{ p = random(randint(5..7),randint(1..3))}
\real{ a = randint(10^(\n1)..10^(\n1 + 1)-1)}
\real{ b = \a/10^(\p)}
\real{ result =\a/10^(\n1)}
\real{ expos=\n1-\p}
\real{ exposa=\expos}
\integer{ pe=\result}
\if{\pe=10}{\real{ pe=1} \real{ exposa=\exposa+1}}{}

\statement{
  \name_statement \( A = \b\).
<div class="wimscenter">
\(A = \) \embed{ reply1 ,3}\( \times 10 \) <sup>\embed{reply2,3}</sup></div>
<div class="wims_instruction">
\name_instruction
</div>
}
\answer{}{\pe}
\answer{}{\exposa}
