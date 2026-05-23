target=afflin2
\language{fr}
\range{-5..5}
\computeanswer{yes}
\format{html}
\precision{10000}
#include "author.inc"
#include "lang_titles.inc"
#include "lang.inc"

\text{A=shuffle(6)}
\integer{a=item(1,\A)}
\integer{u=randint(-2..2)}
\integer{b=\u*(\a)}
\integer{c=item(2,\A)*random(1,-1)}
\integer{n=randitem(randint(-1..1),randint(-1..1),-(\u)*(\c)+(\u)*(\a))}
\integer{d=\u*(\c) +(\n)}
\text{liste= \name_list}
\integer{m=\n=0? 1:3}
\integer{m=\b=\d? 2}
\text{m=\b=0 and \n=0? 1,2}

\statement{\name_enonce[1] \(f(\a) = \b\) \name_enonce[2] \(f(\c) = \d\).
\name_enonce[3]:
<ul><li>\embed{reply 1,1}</li>
<li>\embed{reply 1,2}</li>
<li>\embed{reply 1,3}</li>
</ul>
<div class="wims_instruction">\name_instruction</div>}
\answer{\name_enonce[3]}{\m;\liste}{type=checkbox}
