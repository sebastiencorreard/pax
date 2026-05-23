target=puisdiv2
#include "author.inc"
#include "lang_titles.inc"
#include "lang.inc"

\precision{10000}

\text{listnom=Pierre,Jeanne,Paul,Jacques,Stéphane,Nicolas,Florian,Florence}
\text{listnom=shuffle(\listnom)}
\text{bad=wims(item 1 to 3 of \listnom)}
\integer{a=2}
\integer{b=3}

\integer{rep1=\a^\b}
\integer{rep2=\b^\a}
\integer{rep3=\a*\b}
\text{rep=shuffle(\rep1,\rep2,\rep3)}
\integer{pos=positionof(\rep1,\rep)}
\text{good=item(\pos,\bad)}

\statement{
\name_question[1] \(\a^\b). \bad[1] \name_question[2] \rep[1],
  \bad[2] \name_question[2] \rep[2] \name_question[3] \bad[3] \name_question[2] \rep[3].
\name_question[4]?
}

\choice{Réponse}{\good}{\bad}
