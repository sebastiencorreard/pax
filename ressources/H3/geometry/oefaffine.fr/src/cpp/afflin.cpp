target=afflin
\language{fr}
\range{-5..5}
\computeanswer{no}
\format{html}
\precision{10000}
#include "author.inc"
#include "lang_titles.inc"
#include "lang.inc"

\integer{a=randint(1..8)*random(1,-1)}
\integer{b=randint(-8..8)}
\text{eq=pari(\a*x + (\b))}
\text{eq_tex=texmath(\eq)}
\text{eqlin=pari(\a*x)}

\statement{\name_question
<div class="wimscenter">\(f : x \mapsto \eq_tex \) ? </div>
}

\answer{\name_answer}{\eqlin,x}{type=formal}
