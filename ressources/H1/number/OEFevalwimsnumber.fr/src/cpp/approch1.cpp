target=oefapproch1

#include "author.inc"
#include "lang_titles.inc"
#include "lang.inc"

\language{fr}
\format{html}
\precision{10000}

\integer{a=randint(0..9)*100+randint(0..9)*10}
\integer{b=randint(1..9)}
\text{rep=}
\text{reph=}
\for{i=1 to 4}{
  \integer{f=\b+\i}
  \real{n=(\a+\b+\i)/10}
  \text{rep=wims(append item \n to \rep)}
  \if{\f<>10}{\text{n=slib(numeration/ecriturenombre \n)}}
           {\text{n=slib(numeration/ecriturenombre \n).0}}
  \text{reph=wims(append item \n to \reph)}
}

\real{nb1=\rep[2]-randint(501..999)/10000}
\text{nb1=slib(numeration/ecriturenombre \nb1)}

\real{nb2=\rep[2]-randint(1..499)/10000}
\text{nb2=slib(numeration/ecriturenombre \nb2)}

\real{nb3=\rep[4]-randint(501..999)/10000}
\text{nb3=slib(numeration/ecriturenombre \nb3)}

\real{nb4=\rep[4]-randint(1..499)/10000}
\text{nb4=slib(numeration/ecriturenombre \nb4)}


\text{list=\nb1,\nb2,\nb3,\nb4}

\statement{
\name_statement:
<div class="wimscenter"> \embed{r1}</div>
}

\answer{}{\list;\reph}{type=correspond}
