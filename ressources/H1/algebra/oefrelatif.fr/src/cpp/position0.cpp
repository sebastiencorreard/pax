target=position0
#include "lang_titles.inc"
#include "author.inc"
\computeanswer{no}
\precision{10000}
#include "lang.inc"
\integer{A= randint(1..7)}
\text{choix=random(1,2)}
\text{droite=item(\choix,\liste)}
\text{absc=\choix=1? \A:-\A}
\text{instruction=\name_inst[1] \droite \name_inst[2]}
\text{instruction=wims(replace internal AAAA by \A in \instruction)}
\statement{\instruction?
}
\answer{\name_answer}{\absc}{type=number}

\latex{
\begin{statement}
\instruction?
\end{statement}}
