target=typesb
#include "lang_titles.inc"
#include "lang.inc"
\language{fr}
\range{-5..5}
\author{Gang,XIAO}
\email{xiao@unice.fr}
\computeanswer{no}
\format{html}
\precision{10000}
\integer{type=random(1..4)}

\text{this=item(\type,\right,\acute,\obtuse,\non)}
\matrix{rdata=3,4,5
6,8,10
9,12,15
12,16,20
15,20,25
5,12,13
10,24,26
7,24,25
}
\text{rdata=randomrow(\rdata)}
\integer{a=item(\type,item(1,\rdata),random(5..15),random(4..13),
	random(3..10))}
\integer{b=item(\type,item(2,\rdata),random(5..15),random(4..13),
	random(3..10))}
\integer{c=item(\type,item(3,\rdata),
	random(max(\a,\b)..ceil(sqrt(\a^2+\b^2))-1),
	random(floor(sqrt(\a^2+\b^2))+1..\a+\b-1),
	random(\a+\b+1..\a+\b+6))}
\text{abc=shuffle(\a,\b,\c)}
\integer{aa=item(1,\abc)}
\integer{bb=item(2,\abc)}
\integer{cc=item(3,\abc)}
\integer{peri=\a+\b+\c}
\text{all=\right,\acute,\obtuse,\non}
\statement{\name_instruction
<div class="wimscenter">
	\(A B = \aa\), \(B C = \bb\), \name_peri = \peri ?
</div>}

\choice{\name_choice :}{\this}{\all}
