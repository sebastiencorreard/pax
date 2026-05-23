target=longueur1
\language{fr}
\range{-5..5}
#include "author.inc"
\keywords{length, measurement}
\computeanswer{no}
\format{html}
\precision{100000}
#include "lang_titles.inc"
#include "lang.inc"

\integer{h=random(300..400)}
\integer{l=random(100..200)}
\integer{p=random(300..400)}
\integer{x=\p+\l}
\integer{y=\p+\h}
\text{lettres=shuffle(A,B,C,D,E,F,G,H,J,K,L)}
\text{A=\lettres[1]}
\text{B=\lettres[2]}
\text{C=\lettres[3]}
\text{D=\lettres[4]}
\text{E=\lettres[5]}
\text{F=\lettres[6]}
\text{G=\lettres[7]}
\text{H=\lettres[8]}

\real{e=0.6}
\text{dessin=segment 20,20+\e*\p,20,(\h+\p)*\e+20,black
segment 20,(\h+\p)*\e+20,20+\l*\e,(\h+\p)*\e+20,black
segment 20+\l*\e,(\h+\p)*\e+20,20+\l*\e,20+\e*\p,black
segment 20+\l*\e,20+\e*\p,20,20+\e*\p,black
segment 20,20+\e*\p,20+\e*\p,20,black
dsegment 20,(\h+\p)*\e+20,20+\e*\p,20+\h*\e,black
segment 20+\l*\e,(\p+\h)*\e+20,(\l+\p)*\e+20,20+\h*\e,black
segment 20+\l*\e,20+\e*\p,(\l+\p)*\e+20,20,black
segment 20+\e*\p,20,(\p+\l)*\e+20,20,black
dsegment 20+\e*\p,20+\h*\e,(\l+\p)*\e+20,20+\h*\e,black
dsegment 20+\e*\p,20,20+\e*\p,20+\h*\e,black
segment (\l+\p)*\e+20,20,(\l+\p)*\e+20,20+\h*\e,black
text black,10,10+\p*\e,medium,\A
text black,10+\p*\e,10,medium,\B
text black,30+(\p+\l)*\e,10,medium,\C
text black,30+\l*\e,10+\p*\e,medium,\D
text black,10,10+(\p+\h)*\e,medium,\E
text black,10+\p*\e,10+\h*\e,medium,\F
text black,30+(\p+\l)*\e,10+\h*\e,medium,\G
text black,30+\l*\e,10+(\p+\h)*\e,medium,\H}

\text{donnees=randrow(\A\B\F\E,sqrt(\p^2+\h^2)
\D\C\G\H,sqrt(\p^2+\h^2)
\A\D\H\E,sqrt(\l^2+\h^2)
\B\C\G\F,sqrt(\l^2+\h^2)
\A\B\C\D,sqrt(\l^2+\p^2)
\F\G\H\E,sqrt(\l^2+\p^2))}
\text{rep=item(2,\donnees)}
\text{face=item(1,\donnees)}

\integer{ch=randint(1..3)}
\text{prec=item(\ch,\name_prec)}
\real{rep=rint((\rep)*10^(\ch-1))/10^(\ch-1)}

\statement{
<div class="wims_columns">
 <div class="medium_size img_col">\draw{40+\e*\x,40+\e*\y}{\dessin}</div>
 <div class="medium_size text_col">
\A\B\C\D\E\F\G\H \name_enonce[1]
<ul><li> \A\B=\p cm </li><li> \B\C=\l cm </li><li> \A\E=\h cm</li></ul>
<p>
 \name_enonce[2] \face&nbsp;?
</p>
<div class="spacer">
<label for="reply1"><b>\name_youranswer</b> :</label> \embed{r1,7} cm.
</div>
<div class="wims_instruction">\name_inst[1], \name_inst[2] \prec </div>
</div>
</div>
}

\answer{}{\rep}{type=numexp}
