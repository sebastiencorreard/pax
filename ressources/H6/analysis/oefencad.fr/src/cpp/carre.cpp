target=carre
\language{fr}
\range{-5..5}
\author{Noémie,Cochi;Olivier,Dupuy}
\email{bernadette.m.riou@orange.fr}
\computeanswer{yes}
\format{html}
\precision{10000}
#include "lang_titles.inc"
#include "lang.inc"
\real{a=randint(1..9)*randitem(-1,1)}
\real{b=randint(\a+1..10)}
\real{bb=\b*\b}
\real{aa=\a*\a}
\real{res1=\aa}
\real{res2=\bb}
\real{res1= \a<0 and \b>0 ? 0}
\real{res2= \a<0 and \b>0 ? max(\aa,\bb)}
\real{res1= \a<0 and \b<=0 ? \bb}
\real{res2= \a<0 and \b<=0 ? \aa}

\statement{\name_enonce \( \a \; \leq \; x \ \leq \; \b \).
  <label for="reply1">\name_bestappr \(x^2)</label>&nbsp;:
  <div class="wimscenter">\embed{r1,3}
  <label for="reply2">\(\; \leq \; x^2 \; \leq \; \) </label>\embed{r2,3}.</div> }

\answer{ }{\res1}{type=numeric}
\answer{ }{\res2}{type=numeric}
\feedback{(\reply1>\reply2 )}{\name_feed1 \(\reply1 > \reply2\).}
\feedback{(\reply1>0 or \reply2<0 ) and \a<=0 and \b>0}{
  Votre encadrement n'est pas bon car \(0\), par exemple, n'est
  pas compris entre \(\reply1\) \name_and \(\reply2\).
  \name_feed3
}
