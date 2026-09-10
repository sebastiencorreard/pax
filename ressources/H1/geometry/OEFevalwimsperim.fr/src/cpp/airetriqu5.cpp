target=oefairetriqu5
#include "lang_titles.inc"
\keywords{area}
#include "author.inc"
#include "lang.inc"
\integer{a=randint(40..140)}
\integer{b=randint(40..140)}
\real{lo1=randint(\a/2+10..\a-20)/10}
\real{lo2=\a/10-\lo1}
\real{la=\b/10}
\integer{xo1=\lo1*10}
\integer{xo2=\lo2*10}
\integer{yo=\la*10}
\real{c1=rint(sqrt(\lo1^2+\la^2)*10)/10}
\real{c2=rint(sqrt(\lo2^2+\la^2)*10)/10}
\real{c3=\lo2+\lo1}
\real{rep3=(\c3*\la)/2}
\integer{large=6}
\text{rect=draw(220,180
linewidth 1
triangle 140,90+\yo/2,140,90-\yo/2,140-\xo1,90+\yo/2,black
triangle 140,90+\yo/2,140,90-\yo/2,140+\xo2,90+\yo/2,black
text black,140,75-\yo/2,medium,A
text black,145+\xo2,95+\yo/2,medium,B
text black,135-\xo1,95+\yo/2,medium,C
text black,140,95+\yo/2,medium,H)}
\text{enonc1=\name_enonc1 \name_enonc2
<ul><li>\(A B\) = \c2 cm </li><li>\(A C\) = \c1 cm </li>
  <li>\(C B\) = \c3 cm</li><li>
\(H B\) = \lo2 cm</li><li>\(A H\) = \la cm.</li></ul>
}
\text{enonc5=\(cm^2\)}
\statement{
<div class="wims_columns">
 <div class="medium_size img_col">
   <img src="\rect" alt="">
 </div>
 <div class="medium_size text_col">
 \enonc1
 <div class="spacer"><label for="reply1">\enonc11 \(A B C\)</label>:
 \embed{r1,\large} \enonc5.</div>
 </div></div>
}

\answer{}{\rep3}{type=numeric}
