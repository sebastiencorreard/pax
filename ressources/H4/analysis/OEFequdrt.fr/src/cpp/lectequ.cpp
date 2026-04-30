target=lectequ1 lectequ2 lectequ3 lectequ4 lectequ5 lectequ6
#include "author.inc"
#include "lang_titles.inc"
\text{d=randitem(d,p,D)}
\integer{a=randint(-10..10)}
\integer{b=randint(-10..10)}
#include "lang.inc"
#if defined TARGET_lectequ1
 \text{rep=\a}
 text{equation=y=maxima(expand(\a*x + \b);)}
 \text{equation=y=pari(\a*x + \b)}
#endif
#if defined TARGET_lectequ2
 \text{rep=\b}
 text{equation=y=maxima(expand(\a*x + \b);)}
 \text{equation=y=pari(\a*x + \b)}
#endif
#if defined TARGET_lectequ3
 \integer{c=randint(2..6)}
 text{equation= randitem(maxima(expand(\a*x +\c*y);) = \b,maxima(expand(\c*y+\a*x);) = \b)}
 \text{equation= randitem(pari(\a*x +\c*y) = \b,pari(\c*y+\a*x) = \b)}
 \rational{rep=-\a/\c}
#endif
#if defined TARGET_lectequ4
 \integer{c=randint(2..6)}
 text{equation= randitem(maxima(expand(\a*x +\c*y);) = \b,maxima(expand(\c*y+\a*x);) = \b)}
 \text{equation= randitem(pari(\a*x +\c*y) = \b,pari(\c*y+\a*x) = \b)}
 \rational{rep=\b/\c}
#endif
#if defined TARGET_lectequ5
  \integer{c=randint(2..6)}
 text{equation= maxima(expand(\a*x +\c*y + \b);) = 0}
 \text{equation= pari(\a*x +\c*y + \b)}
 \text{equation=simplify(\equation)=0} pour enlever les parenthèses
 \rational{rep=-\a/\c}
#endif
#if defined TARGET_lectequ6
 \integer{c=randint(2..6)}
 text{equation= maxima(expand(\a*x +\c*y + \b);) = 0}
 \text{equation= pari(\a*x +\c*y + \b)}
 \text{equation=simplify(\equation)=0}
 \rational{rep=-\b/\c}
#endif
\statement{
\name_introdroite:
<div class="wimscenter"> \(\equation\).</div>
\question ?
<h3\name_answer:</h3>
<label for="reply1">\reponse est</label> \embed{r1,5}.}

\answer{}{\rep}{type=numexp}
