target=fonctlin
#include "author.inc"
#include "lang_titles.inc"
#include "lang.inc"

\rational{a=random(1,-1)*randint(1..5)/randint(1..3)}
\rational{b=random(1,-1)*randint(2..8)}
\text{u=simplify((\b)/(\a)*x)}

\statement{\name_enonce \(f(\a) = \b\).}
\answer{\(f(x)\)}{\u,x}{type=formal}
