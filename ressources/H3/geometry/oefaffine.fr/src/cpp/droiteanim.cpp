target=droiteanim
\language{fr}
\range{-5..5}
\computeanswer{no}
\format{html}
\precision{10000}
#include "author.inc"
#include "lang_titles.inc"
#include "lang.inc"

\text{u=random(1,1,2,2,3)}
\text{a=\u=1 or \u=3? 1-4*s: randint(-4..4)}
\text{b=\u=2 or \u=3? 2-3*s: randint(-4..4)}

\text{rep=item(\u,\choix)}

\statement{\name_enonce \(y = a*x + b\).
\name_question?
<p class="wimscenter"> \draw{200,200}{
animate 15,0.2,0
xrange -5.2,5.2
yrange -5.2,5.2
parallel -5,-5,5,-5,0,1,10, grey
parallel -5,-5,-5,5,1,0,10, grey
hline 0,0,black
vline 0,0,black
linewidth 2
plot blue,\a*x+\b
linewidth 1
}
</p>
}
\choice{\name_answer}{\rep}{\choix}
