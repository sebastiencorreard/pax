target=cocyclique4 cocyclique5
\language{fr}
\range{-5..5}
#include "author.inc"
#include "lang_titles.inc"
#include "lang.inc"
\computeanswer{no}
\format{html}
\precision{100}
\text{let=shuffle(A,B,C,D,E,F,G,H,R,S,T)}
\text{A=\let[1]}
\text{B=\let[2]}
\text{C=\let[3]}
\text{X=randitem(\B,\C)}
#if defined TARGET_cocyclique4
\text{rep=\name_rep}
\statement{
\A \name_enonce[1] [\B\C] \name_enonce[2] \B \name_enonce[3] \C.
<p>
\name_question[1] [\B\C] \name_question[2] \A\B\C ?
</p>
<label for="reply1"><b>\name_answer</b></label> : \embed{r1}.
<div class="wims_instruction">\name_instruction</div>}
\answer{}{\rep}{type=atext}
#endif
#if defined TARGET_cocyclique5
\statement{
\A \name_enonce[1] [\B\C] \name_enonce[2] \B \name_enonce[3] \C.
<p>
\name_question \(\widehat{\B\A\C}\) ?
</p>
<b>\name_answer</b>:
<label for="reply1">\(\widehat{\B\A\C} =\)</label>
\embed{r1,5}°}
\answer{}{90}{type=numexp}
#endif
