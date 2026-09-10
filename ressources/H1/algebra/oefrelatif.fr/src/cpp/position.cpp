target=position
#include "lang_titles.inc"
#include "author.inc"
#include "lang.inc"
\computeanswer{no}
\precision{10000}
\integer{A= random(1,-1)*randint(1..7)}
\text{A=\A>0 ? +\A}
\integer{B=randint(abs(\A)+1..11)}

\text{choix=random(1,2)}
\text{droite=item(\choix,\liste)}
\integer{absc=\choix=1 and \B>\A? \B}
\integer{absc=\choix=1 and \B<\A? -\B}
\integer{absc=\choix=2 and \B>\A? -\B}
\integer{absc=\choix=1 and \B<\A? \B}
\text{absc=\absc>0? +\absc}
\text{instruction=\name_inst[1] \droite \name_inst[2]}
\text{instruction=wims(replace internal AAAA by \A in \instruction)}
\text{instruction=wims(replace internal BBBB by \B in \instruction)}

\statement{\instruction?}
\answer{\name_answer}{\absc}{type=number}

\latex{
\begin{statement}
\instruction?
\end{statement}
}
