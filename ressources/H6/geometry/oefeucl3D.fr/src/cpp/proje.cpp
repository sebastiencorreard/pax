target=proje

\author{Bernadette, Perrin-Riou;Adeline, Grelot }

#include "author.inc"
#include "lang_title.inc"

\title{TITLE}
\title_en{TITLE_en}
\title_es{TITLE_es}
\title_ca{TITLE_ca}


\integer{n=3}

\integer{a=random(randint(-5..-1),randint(1..5))}
\integer{b=random(randint(-5..-1),randint(1..5))}
\integer{c=random(randint(-5..-1),randint(1..5))}

\text{v3=random(randint(1..2), randint(-2..-1)),random(randint(1..2), randint(-2..-1)),random(randint(1..2), randint(-2..-1))}

Calcul de la normale
\text{normale=\a,\b,\c}

Projection de v3 sur la normale

\rational{prod=simplify((item(1,\v3))*(item(1,\normale))+(item(2,\v3))*(item(2,\normale))+(item(3,\v3))*(item(3,\normale)))}
\rational{norm2=simplify((item(1,\normale))^2+(item(2,\normale))^2+(item(3,\normale))^2)}
\rational{sol1=item(1,\v3)-(\prod)/\norm2*(item(1,\normale))}
\rational{sol2=item(2,\v3)-(\prod)/\norm2*(item(2,\normale))}
\rational{sol3=item(3,\v3)-(\prod)/\norm2*(item(3,\normale))}

\text{sol=\sol1,\sol2,\sol3}
\text{equation=simplify((\a)*x + (\b)*y + (\c)*z)}

#include "lang.inc"

\statement{
\name_instruction1
<div class="wimscenter">\(\equation=0).</div>
\name_instruction2
}

\answer{\name_projorth}{\sol}{type=vector}
