target=oefairetri1 oefairetri2 oefairetri3 oefairetri4 oefairetri5
\keywords{area}
#include "author.inc"
#include "lang_titles.inc"
#include "lang.inc"

#if defined TARGET_oefairetri1
\integer{a=random(2,4,6,8,10)}
\integer{lo=\a*30}
\integer{la=\a*30}
\integer{xo=\lo/2}
\integer{yo=\la/2}

\integer{rep=\a*\a/2}
\integer{large=4}
\text{rect=draw(280,240
rect 140-\xo/2,110+\yo/2,140+\xo/2,110-\yo/2,black
linewidth 2
triangle 140-\xo/2,110+\yo/2,140-\xo/2,110-\yo/2,140+\xo/2,110-\yo/2,red)}
\text{enonc1=\name_enonc1[1] \a cm \name_enonc1[2]}
\text{enonc2=\(cm^2)}
#endif
#if defined TARGET_oefairetri2
\integer{a=randint(4..29)*2}
\integer{b=randint(6..\a-10)}
\integer{rep=\a*\b/2}
\integer{ar=\a*\b}
\integer{large=6}
\text{enonc1=\name_enonc1 \ar \(cm^2).}
\text{enonc2=\(cm^2)}
\text{rect=draw(150,100
rect 20,20,130,80,black
linewidth 2
triangle 20,20,20,80,130,80,red
)}
#endif
#if defined TARGET_oefairetri3
\integer{a=randint(4..29)*2}
\integer{b=randint(6..\a-10)}
\integer{rep=\a*\b/2}
\integer{large=6}
\text{enonc1=\name_enonc1[1] \a cm \name_enonc1[2] \b cm.}
\text{enonc2=\(cm^2)}
\text{rect=draw(150,100
rect 20,20,130,80,black
linewidth 2
triangle 20,20,20,80,130,80,red
)}
#endif
#if defined TARGET_oefairetri4
\integer{a=randint(4..29)*2}
\integer{b=randint(6..\a-10)}
\integer{rep=\a*\b/2}
\real{h=rint(sqrt(\a^2+\b^2)*10)/10}
\integer{large=6}
\text{enonc1=\name_enonc1
<p>\(A B\) = \b cm , \(B C\) = \a cm,  \(A C\) = \h cm.</p>}
\text{enonc2=\(cm^2)}
\text{rect=draw(150,100
triangle 20,20,20,80,130,80,black
text black,15,5,medium,A
text black,15,85,medium,B
text black,135,85,medium,C
)}
#endif
#if defined TARGET_oefairetri5
\integer{a=randint(5..19)*2}
\integer{b=randint(3..\a-6)}
\integer{ar=\a*\b/2}
\integer{rep=\a}
\integer{large=6}
\text{enonc1=\name_enonc1[1]
 \(A B\) = \b cm \name_enonc1[2] \ar \(cm^2).}
\text{enonc2=cm}
\text{rect=draw(150,100
triangle 20,20,20,80,130,80,black
text black,15,5,medium,A
text black,15,85,medium,B
text black,135,85,medium,C
)}
#endif
\statement{
<div class="wims_columns">
  <div class="medium_size img_col"><img src="\rect" alt=""></div>
  <div class="medium_size text_col">\enonc1
    <div class="spacer">
    <label for="reply1">\enonc11</label> \embed{r1,\large} \enonc2.
    </div>
  </div>
</div>
}

\answer{}{\rep}{type=numeric}
