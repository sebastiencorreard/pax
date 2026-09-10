target=oeftrouvangltriang1 oeftrouvangltriang2 oefmesangltriang
\langage{fr}
#include "author.inc"
\format{html}
#include "lang_titles.inc"

\text{nom=shuffle(A,B,C,E,F,G,H,J,K,L,M,N,R,S,T)}
\text{n=shuffle(\nom[1],\nom[2],\nom[3])}
#include "lang.inc"


\integer{x1=randint(20..40)}
\integer{y1=randint(160..180)}
\integer{x3=randint(70..\x1+140)}
\integer{y3=\y1}
\integer{x2=randint(\x1..\x3)}
\integer{y2=randint(\y1-140..\y1-30)}
\integer{a1=rint(180*atan((\y1-\y2)/(\x2-\x1))/pi)}
\integer{a3=rint(180*atan((\y1-\y2)/(\x3-\x2))/pi)}
\integer{a2=180-\a1-\a3}
\real{l1=(\x3-\x1)/10}
\real{l2=rint(sqrt((\y1-\y2)^2+(\x2-\x1)^2))/10}
\real{l3=rint(sqrt((\y1-\y2)^2+(\x3-\x2)^2))/10}
\integer{a11=\a1-1}
\integer{a12=\a1+1}
\integer{a21=\a2-1}
\integer{a22=\a2+1}
\integer{a31=\a3-1}
\integer{a32=\a3+1}

\text{trique=draw(200,200
segment \x1,\y1,\x2,\y2,black
text black,\x1-15,\y1,medium,\nom[1]
segment \x1,\y1,\x3,\y3,black
text black,\x2,\y2-15,medium,\nom[2]
segment \x2,\y2,\x3,\y3,black
text black,\x3+10,\y3,medium,\nom[3])}


\integer{a=randint(1..2)}
\if{\a=1}{\text{rep=\n[3]}}{\text{rep=[\n[2]\n[3]]|[\n[3]\n[2]]}}
\text{quest=\quest[\a]}

\text{fig=<img src="\trique" alt="">}

\statement{
<div class="wims_columns">
<div class="medium_size img_col">\fig</div>
<div class="medium_size text_col">
\name_info \(\nom[1] \nom[2] \nom[3]\).
#if defined TARGET_oeftrouvangltriang1
<ul><li>
\(\nom[1] \nom[3]\) = \l1 cm,
\(\nom[1] \nom[2]\) = \l2 cm,
\(\nom[2] \nom[3]\) = \l3 cm,
</li><li>
\(\widehat{\nom[2] \nom[1] \nom[3]}) = \a1°
</li></ul>
<p>\name_instruc0</p>
<ul><li>
<div>\(\widehat{\nom[1] \nom[2] \nom[3]}) = \embed{r1,4}°.</div>
</li><li>
<div>\(\widehat{\nom[1] \nom[3] \nom[2]}) = \embed{r2,4}°.</div>
</li></ul>
#endif
#if defined TARGET_oeftrouvangltriang2
<ul><li>
\(\nom[1] \nom[3]\) = \l1 cm,
\(\nom[1] \nom[2]\) = \l2 cm,
\(\nom[2] \nom[3]\) = \l3 cm
</li><li>
\(\widehat{\nom[2] \nom[1] \nom[3]}) = \a1°
</li><li>
\(\widehat{\nom[1] \nom[2] \nom[3]}) = \a2°
</li></ul>
<p>\name_instruc1</p>
<div class="wimscenter">
\(\widehat{\nom[1] \nom[3] \nom[2]}) = \embed{r1,4}°.
</div>
<div class="wims_instruction">\name_instruc2</div>
#endif
#if defined TARGET_oefmesangltriang
<ul><li>
\(\nom[1] \nom[3]\) = \l1 cm
</li><li>\(\nom[1] \nom[2]\) = \l2 cm
</li><li>\(\nom[2] \nom[3]\) = \l3 cm
</li></ul>
\name_instruc0
<ul><li>
\(\widehat{\nom[2] \nom[1] \nom[3]}) = \embed{r1,4}°
</li><li>
\(\widehat{\nom[1] \nom[2] \nom[3]}) = \embed{r2,4}°
</li><li>
\(\widehat{\nom[1] \nom[3] \nom[2]}) = \embed{r3,4}°
</li></ul>
#endif
</div></div>
}


#if defined TARGET_oeftrouvangltriang1
\answer{}{\a2|\a21|\a22}{type=case}
\answer{}{\a3|\a31|\a32}{type=case}
#endif
#if defined TARGET_oeftrouvangltriang2
\answer{}{\a3|\a31|\a32}{type=case}
#endif

#if defined TARGET_oefmesangltriang
\answer{}{\a1|\a11|\a12}{type=case}
\answer{}{\a2|\a21|\a22}{type=case}
\answer{}{\a3|\a31|\a32}{type=case}
#endif
