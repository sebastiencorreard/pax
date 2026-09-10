target=stadouble

#include "header.inc"
#include "lang_titles.inc"

#include "lang.inc"

\text{one=\name_type_list[1]}
\text{double=\name_type_list[2]}
\text{double2=\name_type_list[3]}
\text{real=\name_type_list[4]}
\text{complex=\name_type_list[5]}
\text{choices=\double,\real,\complex,\one,\double2}
\integer{type=random(1,2,3)}
\integer{mm=random(2..4)*random(-1,1)}
\integer{a=random(1..6)*random(-1,1)}
\integer{b=random(1..6)*random(-1,1)}
\integer{c2=(\a)^2*(\mm)}
\integer{c1=2*(\a)*(\b)*(\mm)}
\integer{c0=(\b)^2*(\mm)}
\integer{move=random(1..10)*sign(\c2)}
\integer{c0=\type=1?\c0-(\move)}
\integer{c0=\type=2?\c0+(\move)}
\text{C1=\c1>=0?+\c1:\c1}
\text{C0=\c0>=0?+\c0:\c0}

\text{good=item(\type,\real,\complex,\double)}

\statement{\name_statement?
<div class="wimscenter">
\(\c2 X^2 \C1 X \C0\)
</div>}

\choice{\name_choice}{\good}{\choices}

