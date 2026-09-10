target=tabouret

#include "lang_titles.inc"
#include "author.inc"
#include "lang.inc"

\text{size=250,500}
\text{b=2}
\text{mult=randint(4..6)}
\text{mult=\mult,randitem(16,18,20)}
on veut que a*mult[1] soit divisible par mult[2] autre que 2 et 5

\if{\mult[2]=18}{
  \integer{a=3*randint(2..4)}
  \integer{c=3*randint(2..3)}
  \text{mult=\c,\mult[2]}
}{
  \text{a=randint(5..10)}
}
\text{xrange=-\mult[2]/4,\mult[2]/4}
\text{yrange=-1,\mult[2]+2}
\integer{rep2=\a*5} comment faire pour que cela soit un entier ou presque !

\real{YY=\mult[2]/10}
\real{XX=10*\a*(\mult[2]-\mult[1])/\mult[2]}
\integer{HH=\mult[1]*10}
\text{enonce=wims(replace internal XXXX by \XX in \name_enonce)}
\text{enonce=wims(replace internal HHHH by \HH in \enonce)}
\text{enonce=wims(replace internal YYYY by \YY in \enonce)}
\text{dessin=xrange pari([\xrange])
yrange pari([\yrange])
fellipse 0,0,\a,\b,grey
segments orange,pari([-\a/2,0,-\a/(2*\mult[2]),\mult[2],\a/2,0,\a/(2*\mult[2]),\mult[2]])
linewidth 3
points orange, 0,\mult[2]
linewidth 1
segments black, 0,\mult[2], 0,0
fellipse 0,\mult[1],pari([\a*(\mult[2]-\mult[1])/\mult[2],\b*(\mult[2]-\mult[1])/\mult[2]]),blue
}

\statement{
<div class="wims_columns">
 <div class="medium_size img_col">\draw{\size}{\dessin}</div>
 <div class="medium_size text_col">
\enonce
<div>
<label for="reply1">\name_question[1;]</label> \embed{r1,10}
</div>
\name_enonce2
<div>
<label for="reply2">\name_question[2;]</label> \embed{r2,5}cm.
</div>
</div></div>


}

\answer{}{\rep1}{type=atext}
\answer{}{\rep2}{type=numeric}
