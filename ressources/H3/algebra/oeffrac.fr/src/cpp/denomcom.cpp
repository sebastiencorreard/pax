target=denomcom
\language{fr}
\range{-5..5}
#include "author.inc"
\computeanswer{no}
\format{html}
\precision{10000}
#include "lang_titles.inc"
#include "lang.inc"
\integer{a=random(2..20)}
\integer{b=random(2..20)}
\integer{g=randitem(1,2,3,4,5,2,3,4,5)}
\integer{c=\g*random(2..5)}
\integer{d=\g*random(1..5)}
\text{list=shuffle(29,31,37,41)}
\integer{g=maxima(gcd(\a,\c);)}
\integer{a=\g!=1?item(1,\list)}
\integer{g=maxima(gcd(\b,\d);)}
\integer{b=\g!=1?item(2,\list)}

\if{\c=\d}{
  \integer{a=11}
  \integer{b=17}
  \integer{c=12}
  \integer{d=28}
}

\text{frac1=\(\frac{\a}{\c})}
\text{frac2=\(\frac{\b}{\d})}

\integer{rep=maxima(\c*\d/gcd(\c,\d);)}

\statement{
\name_statement[1] \frac1 \name_statement[2] \frac2 ?
<div class="spacer">
<b>\name_youranswer</b> :
\name_statement[3] \embed{r1,5}.
</div>
}

\answer{\name_answer}{\rep}{type=numexp}
\hint{\name_hint[1] \(\c) \name_hint[2] \(\d).}
