target=twosidesb
#include "lang_titles.inc"
\language{fr}
\range{-5..5}
\author{Gang, XIAO}
\email{xiao@unice.fr}
\computeanswer{no}
\format{html}
\precision{10000}
\observation{Exercice demandant de la réflexion ayant une indication après une réponse fausse.}

\integer{ab=random(10..40)}
\integer{bc=random(10..40)}
\integer{max=max(\ab,\bc)}
\integer{min=min(\ab,\bc)}
\text{long=\ab>\bc?AB:BC}
\text{short=\ab>\bc?BC:AB}
\real{q1=\max^2+\min^2}
\real{q2=\max^2-\min^2}
\real{sq1=sqrt(\q1)}
\real{sq2=sqrt(\q2)}
\integer{n1=(ceil(\sq1)-1) - (floor(\sq2)+1) + 1}
\integer{n2=(\ab+\bc-1) - (floor(\sq1)+1) + 1}
\integer{n3=(ceil(\sq2)-1) - (\max-\min+1) + 1}
\integer{n3=\n3<0?0}
\integer{o=randitem(1,2)}
#include "lang.inc"
\text{type=item(\o,\name_acute)}
\integer{n=item(\o,\n1,\n2+\n3)}
\text{ans=\o=1?\ans1:\ans2}

\statement{\name_instruction[1;] \type \name_instruction[2;]
<div class="wimscenter">
  \(A B = \ab\), \(B C = \bc\)&nbsp;?
</div>}

\answer{\name_answer}{\n}{type=default}

\solution{\ans}
