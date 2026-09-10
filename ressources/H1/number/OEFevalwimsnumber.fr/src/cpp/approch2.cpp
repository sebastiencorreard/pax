target=oefapproch2

#include "author.inc"
#include "lang_titles.inc"
#include "lang.inc"

\language{fr}
\format{html}
\precision{10000}

\text{sg=random(+,-)}
\integer{v=randint(0..9)*100+randint(1..9)*10}
\integer{ap=randint(1..3)}
\integer{c=randint(10^(\ap-1)..10^\ap)}
\real{v=\v-\c/10^(\ap-1)}
\integer{e=randint(1..499)}
\real{n=\v\sg\e/10^(\ap+2)}

\text{n=slib(numeration/ecriturenombre \n)}
\text{n=wims(replace internal . by , in \n)}
\text{v=slib(numeration/ecriturenombre \v)}
\text{v=wims(replace internal . by , in \v)}

\statement{
\name_statement[1] \v \name_statement[2] \embed{r1} \name_statement[3] \name_statement[4] \n.
}

\answer{}{\ap;\mot}{type=menu}
\latex{
\begin{statement}
\name_statement[1] \v \name_statement[2] \(\cdots\) \name_statement[3] \name_statement[4] \n.
\end{statement}
}
