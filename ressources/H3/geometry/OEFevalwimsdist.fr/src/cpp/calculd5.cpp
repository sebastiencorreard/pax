target=calculd5
#include "author.inc"
#include "lang_titles.inc"
#include "lang.inc"

\text{let=shuffle(A,B,C,E,F,G)}
\text{A=\let[1]}
\text{B=\let[2]}
\text{C=\let[3]}
\text{D=\let[4]}

\text{dessin=square 50,50,200,black
text black,45,35,medium,\A
text black,245,35,medium,\B
text black,245,255,medium,\C
text black,45,255,medium,\D
segment 50,250,250,50,black}

\text{image=draw(300,300
\dessin)}
\text{long=randint(10..20)}
\real{rep=rint(sqrt(2)/2*\long*10)/10}
\text{enonce=wims(replace internal AAAA by \A in \name_enonce)}
\statement{
<div class="float_left"><img src="\image" alt=""></div>
<div class="float_left">
  \A\B\C\D \enonce[1] \long cm.<br>\enonce[2]?
</div>
<div class="clearall">
 <b>\name_answer:</b> \embed{r1,5} cm.
</div>}

\answer{}{\rep}{type=numexp}
