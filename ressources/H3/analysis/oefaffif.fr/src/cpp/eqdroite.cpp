target=eqdroite
\language{fr}
\range{-5..5}
\computeanswer{no}
\format{html}
\precision{10000}
#include "author.inc"
#include "lang_titles.inc"
#include "lang.inc"

\text{listn=wims(values v,-v for v=1 to 15)}
\text{listn=shuffle(\listn)}
\integer{nb1=\listn[1]}
\integer{nb2=\listn[2]}
\integer{nb3=\listn[3]}
\integer{nb4=\listn[4]}

\text{a=simplify((\nb2-\nb4)/(\nb1-\nb3))}
\text{b=simplify(\nb2-(\a)*\nb1)}
\if{\b=0}{
  \text{sol=\a*x}
}{
 \text{sol=\b>0?\a*x+\b:\a*x\b}
}
text{sol=simplify(\a*x+(\b))}
\statement{
\name_enonce[1;1] \(A(\nb1 ; \nb2)) \name_enonce[1;2] \(B(\nb3 ; \nb4)).
<p>
\name_enonce[2;1] \( \nb1\neq \nb3), \name_enonce[2;2] \(y=a x+b).</p>
\name_question \(d\) :
<div class="wimscenter">
<label for="reply1">\(y = )</label>\embed{reply1}
</div>}

\answer{\name_answer}{\sol}{type=litexp}
