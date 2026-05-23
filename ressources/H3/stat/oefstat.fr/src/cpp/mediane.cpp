target=mediane
\language{fr}
\range{-5..5}
\precision{1000}
#include "author.inc"
#include "lang_titles.inc"
#include "lang.inc"
\computeanswer{no}
\format{html}

\text{n=randint(8,9,10,11,12,13)}

\text{a=slib(stat/random \n,0,30)}
\text{a=wims(declosing [\a])}
\text{b =}
\for{ i = 1 to \n}{
  \for{j = 1 to \n}{
    \real{c=160+ (\a[\i]+\a[\j])/2}
    \text{b=\b,\c}
  }
}
\text{b=wims(nonempty items \b)}

\text{tableau=<table class="wimscenter wimsborder" style="background-color:skyblue"><tr>}
\for{i=1 to \n}{
\real{u=item(\i, \a)+160}
\text{tableau= \tableau <td>\u</td>}
}
\text{tableau=\tableau </tr></table>}

\real{m=slib(stat/median [\a])+160}
\real{moy=item(1,slib(stat/arithmean [\a]) )+ 160}
\statement{<p>\name_enonce[1] \n \name_enonce[2]:
</p>
\tableau
<div class="wims_question">
\name_question
<div class="wimscenter">
<label for="reply1">\name_answer[1]:</label> \embed{reply1,5}
</div>
</div>
}
\answer{\name_answer[2]}{\m}{type=algexp}

\hint{<span class="wims_warning">
\name_hint[1;]
<br>
\name_hint[2;]</span>}
\real{test2 = 160+(\a[rint(\n/2)]+\a[rint((\n+1)/2)])/2}

\feedback{\reply1 <> \m and \reply1 = \test2}{
<p style="color:purple">\name_feed1! </p>}

\feedback{\reply1 = \moy and \reply1 <> \m}{<p style="color:purple">
\name_feed2</p>}

\feedback{\reply1 <> \m and \reply1 <> \moy and \reply1 notitemof \b}{
<p style="color:purple">\name_feed3.</p>}
