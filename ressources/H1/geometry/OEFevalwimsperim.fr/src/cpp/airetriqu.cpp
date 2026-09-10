target=oefairetriqu1 oefairetriqu2
\keywords{area}
#include "author.inc"
#include "lang_titles.inc"
#include "lang.inc"
#if defined TARGET_oefairetriqu1
\integer{a=randint(4..14)}
\integer{b=randint(2..7)*2}
\integer{lo1=randint(\a/2+1..\a-2)}
\integer{lo2=\a-\lo1}
\integer{la=\b}
\integer{xo1=\lo1*10}
\integer{xo2=\lo2*10}
\integer{yo=\la*10}
\integer{rep1=\lo1*\la/2}
\integer{rep2=\lo2*\la/2}
\integer{rep3=\rep1+\rep2}
\integer{large=4}
#endif
#if defined TARGET_oefairetriqu2
\integer{a=randint(40..140)}
\integer{b=randint(40..140)}
\real{lo1=randint(\a/2+10..\a-20)/10}
\real{lo2=\a/10-\lo1}
\real{la=\b/10}
\integer{xo1=\lo1*10}
\integer{xo2=\lo2*10}
\integer{yo=\la*10}
\real{rep1=\lo1*\la/2}
\real{rep2=\lo2*\la/2}
\real{rep3=\rep1+\rep2}
\integer{large=6}
#endif
\text{rect=draw(220,180
linewidth 1
triangle 140,90+\yo/2,140,90-\yo/2,140-\xo1,90+\yo/2,black
triangle 140,90+\yo/2,140,90-\yo/2,140+\xo2,90+\yo/2,black
text black,140,75-\yo/2,medium,A
text black,145+\xo2,95+\yo/2,medium,B
text black,135-\xo1,95+\yo/2,medium,C
text black,140,95+\yo/2,medium,H)}
\text{enonc1=\name_enonc1 <p>\name_enonc2
\(C H\) = \lo1 cm &#44; \(H B\) = \lo2 cm &#44; \(A H\) = \la cm.
</p>}
\text{enonc2=\enonc11 \(C H A\) :}
\text{enonc3=\enonc11 \(B H A\) :}
\text{enonc4=\enonc11 \(A B C\) :}
\text{enonc5=\(cm^2\)}
\statement{
<div class="wims_columns">
 <div class="medium_size img_col">
   <img src="\rect" alt="">
 </div>
 <div class="medium_size text_col">
 \enonc1
<ul><li>
<label for="reply1">\enonc2</label> \embed{r1,\large} \enonc5.
</li><li>
<label for="reply2">\enonc3</label> \embed{r2,\large} \enonc5.
</li><li>
<label for="reply3">\enonc4</label> \embed{r3,\large} \enonc5.
</li></ul>
</div></div>
}

\answer{}{\rep1}{type=numeric}
\answer{}{\rep2}{type=numeric}
\answer{}{\rep3}{type=numeric}
