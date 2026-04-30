target=devel1 devel2 devel3
#include "author.inc"
#include "lang_titles.inc"
#include "lang.inc"
\format{html}
#if defined TARGET_devel1 || defined TARGET_devel2
# if defined TARGET_devel1
\integer{a=randint(1..10)}
\integer{b=randint(1..10)}
\integer{c=randint(1..10)}
\integer{n=randint(1..5)}
\integer{p=randint(1..5)}
\text{expfact=\a*x^\n*(\b*x^\p+\c)}
# endif
# if defined TARGET_devel2
\integer{a=randint(1..10)}
\integer{b=randint(1..10)}
\text{data=(\a*x+\b)^2,(\a*x-\b)^2,(\b+\a*x)^2,(\b-\a*x)^2,(\a*x+\b)*(\a*x-\b),(\b+\a*x)*(\b-\a*x)}
\text{expfact=randitem(\data)}
# endif
\text{expdev=maxima(expand(\expfact))}
\text{expfact=texmath(maxima(\expfact))}
\statement{
\name_question:
<div class="wimscenter">\(\expfact)</div>
<div class="wimscenter"><label for="reply1">\name_answer:</label> \embed{reply1}</div>}
\answer{}{\expdev}{type=algexp}
#endif
#if defined TARGET_devel3
\integer{c=randint(2..10)}
\integer{a=randint(0..3)*\c+randint(1..\c-1)}
\integer{b=randint(0..3)*\c+randint(1..\c-1)}
\text{exp=shuffle(6)}
\text{exp=item(1..3,\exp)}
\text{exp=wims(sort numeric list \exp)}
\integer{i=randint(2,3)}
\integer{n=\exp[\i]}
\integer{p=\exp[5-\i]}
\integer{q=\exp[1]}
\text{expsimp=(maxima(\a*x^(\n-\q)+\b*x^(\p-\q)))/\c}
\text{expnum=texmath(\a*x^\n+\b*x^\p)}
\text{expden=texmath(maxima(\c*x^\q))}
\text{expdev=\frac{\expnum}{\expden}}
\statement{
\name_question:
<div class="wimscenter"> \(\expdev)</div>
<div class="wimscenter"><label for="reply1">\name_answer:</label> \embed{reply1}</div>}
\answer{}{\expsimp}{type=algexp}
#endif
