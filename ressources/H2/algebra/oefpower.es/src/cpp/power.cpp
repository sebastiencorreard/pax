target=power
#include "lang_titles.inc"
\language{fr}
\range{-5..5}
#include "author.inc"
#include "lang.inc"
\computeanswer{no}
\format{html}
\precision{10000}

\integer{n=randint(2..5)}
\real{a=randint(2,3,5,4)}
\integer{c=randint(2,3,6,5,7,11)}
\integer{b= \a*\c}
\integer{p=randint(2..5)}
\integer{sol1= \c}
\integer{sol2= \n*\p}
\text{aa=pari(\a^(\sol2))}
\text{faux=pari(\n+\p)}
\integer{afaux=\a^(\faux)}
\statement{\name_statement1 \((\frac{\b^{\n}}{\a^{\n}})^{\p}) \name_statement2:
<div class="wimscenter">\((\frac{\b^{\n}}{\a^{\n}})^\p) = \embed{reply 1, 4}<sup><sup>
\embed{reply 2,4}</sup></sup></div>
}
\answer{}{\sol1}{type=numeric}
\answer{}{\sol2}{type=numeric}
\hint{\name_hint}
\feedback{\reply2<>\sol2} {\name_feedback1: \((a^n)^m=a^(n*m)) ?}
\feedback{\reply2=\faux and \reply2 <> \sol2 }{\name_feedback2
<div class="wimscenter">\((\a^\n)^\p = \a^{\n\times \p}=\a^{\sol2} =\aa ) </div> \name_and
<div class="wimscenter">\(\a^\n) \times \(\a^\p) = \(\a^(\n+\p)) = \(\a^\faux = \afaux)
</div>}
