target=fnctaff1
\language{fr}
\range{-5..5}
\computeanswer{no}
\format{html}
\precision{10000}
#include "author.inc"
#include "lang_titles.inc"
#include "lang.inc"

\text{nom=randitem(f,g,h)}
\text{listn=wims(values v,-v for v=1 to 15)}
\text{listn=shuffle(\listn)}
\integer{nb1=\listn[1]}
\integer{nb2=\listn[2]}
\integer{nb3=\listn[3]}
\integer{nb4=\listn[4]}

\text{a=simplify((\nb2-\nb4)/(\nb1-\nb3))}
\text{b=simplify(\nb2-(\a)*\nb1)}
text{sol=simplify(\a*x+(\b))}

\if{\b=0}{
  \text{sol=\a*x}
}{
 \text{sol=\b>0?\a*x+\b:\a*x\b}
}

\statement{\name_enonce[1] \(\nb1\) \name_enonce[2] \(\nom\)
  \name_enonce[3] \(\nb2) \name_enonce[4] \(\nb3)
  \name_enonce[5] \(\nb4).
<p>
\name_enonce2[1] \(\nom\) \name_enonce2[2] \(\nom : x\mapsto a x+b\).
</p>
\name_question?
<div class="wimscenter">
<label for="reply1">\(\nom : x\mapsto\)</label>\embed{reply1}</div>}

\answer{\name_answer}{\sol}{type=litexp}
