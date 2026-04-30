target=vacalcul
\language{fr}
\range{-5..5}
#include "author.inc"
#include "lang_titles.inc"
#include "lang.inc"

\computeanswer{no}
\format{html}
\precision{100}
#include "css.inc"
\text{eq=<b> = </b>}
\text{s1=random(-,-,-,+)}
\text{s2=random(+,-)}
\text{s3=random(+,-)}
\text{s4=random(+,-)}
\text{s5=random(+,-)}
\text{s6=random(-,-)}

\integer{x1=random(1..10)}
\integer{x2=random(1..10)}
\integer{x3=random(1..10)}
\integer{x4=random(1..10)}

\text{v1= | \s1 \x1| }
\text{v2= \s1 | \s2 \x1 | }
\text{v3= | \s1 \x1 \s2 \x2 | }
\text{v4= \s1 | \s2 \x1 \s3 \x2 | }
\text{v5= \s1 \x1 \s2 | \s3 \x2 \s4 \x3 | }

\text{t1=random(\v1,\v2,\v3,\v4,\v5)}
\text{q1=htmlmath(\t1)}
\text{a1=maxima(expand((\q1));)}
\text{a1=htmlmath(\a1)}

\text{l=1,2,3,4}
\text{n=!shuffle 4}
\text{as=\a1,\a2,\a3,\a4}
\text{an1=!positionof item 1 in \n}
\text{ans=!item \an1 of \l}

\text{p1=!item 1 of \n}
\text{p2=!item 2 of \n}
\text{p3=!item 3 of \n}
\text{p4=!item 4 of \n}
\text{aa1=!item \p1 of \as}
\text{b1=!item \p2 of \as}
\text{c1=!item \p3 of \as}
\text{d1=!item \p4 of \as}

\text{size=\confparm1=1 ? :x-large}
\statement{
<div class="rm">
\name_question: \t1.
</div>
}

\hint{<div class="rm hint">
<h3>Lire ces intructions</h3>
<ul><li>
Tout d'abord, réduire à un seul terme les expressions à l'intérieur des symboles de valeur absolue.
</li><li>
La valeur absolue d'un nombre positif est positive.
</li><li>
La valeur absolue d'un nombre négatif est positive.
</li></ul>
<h3> Etudier les exemples suivants</h3>
<ul><li>
| - 7 | \eq 7
</li><li>
| + 7 | \eq 7
</li><li>
- | - 7 | \eq - ( + 7 ) \eq -7
</li><li>
|3 - 7| \eq | - 4 | \eq 4
</li><li>
1 - |3 - 7| \eq 1 - | - 4 | \eq 1 - ( + 4) \eq 1 - 4 \eq -3
</li></ul>
</div>
}

\answer{Simplification}{\a1}{type=default}
