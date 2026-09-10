target=defpuisnb

#include "lang_titles.inc"
#include "author.inc"
#include "lang.inc"
\integer{ a1=random(2..6)}
\integer{ b1=randint(2..4)}
\integer{ a2=random(-6..-2)}
\integer{ b2=randint(2..4)}
\integer{ a3=random(2..6)}
\integer{ b3=randint(2..4)}
\integer{ a4=random(-6..-2)}
\integer{ b4=randint(2..4)}

\rational{ result1 = pari( \a1^\b1)}
\rational{ result2 = pari( (\a2)^\b2)}
\rational{ result3 = pari( -1*((\a3)^(\b3)))}
\rational{ result4 = pari( -1*((\a4)^(\b4)))}

\text{r1=\a1^\b1}
\text{r2=(\a2)^\b2}
\text{r3=-\a3^\b3}
\text{r4=-(\a4)^\b4}

\integer{n=random(1..4)}
\if{\n=1}{\text{r=\r1} \rational{result=\result1} }
\if{\n=2}{\text{r=\r2} \rational{result=\result2} }
\if{\n=3}{\text{r=\r3} \rational{result=\result3} }
\if{\n=4}{\text{r=\r4} \rational{result=\result4} }
\statement{
\name_statement \( A = \r\)
<div class="wimscenter">
 <label for="reply1">\(A = \)</label> \embed{ reply1 ,8}
 </div>
}
\answer{\(A\) }{\result}
