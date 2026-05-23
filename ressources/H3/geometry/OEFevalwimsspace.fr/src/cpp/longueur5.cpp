target=longueur5
\language{fr}
\range{-5..5}
#include "author.inc"
\computeanswer{no}
\format{html}
\precision{100000}
#include "lang_titles.inc"
#include "lang.inc"

\keywords{length, measurement}
\integer{h=random(300..400)}
\integer{l=random(100..200)}
\integer{p=random(300..400)}
\integer{r=random(\h/3..2*\h/3)}

\integer{x=\p+\l}
\integer{y=\p+\h}
\text{lettres=shuffle(A,B,C,D,E,F,G,H,J,K,L,M,N)}
\text{A=\lettres[1]}
\text{B=\lettres[2]}
\text{C=\lettres[3]}
\text{D=\lettres[4]}
\text{E=\lettres[5]}
\text{F=\lettres[6]}
\text{G=\lettres[7]}
\text{H=\lettres[8]}
\text{I=\lettres[9]}
\text{J=\lettres[10]}
\text{K=\lettres[11]}
\text{L=\lettres[12]}

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
segment 20,20+\e*\p,20+\l*\e,(\h+\p)*\e+20,green
dsegment 20+\e*\p,20,20+(\p+\l)*\e,(\h)*\e+20,green
segment 20,20+\e*(\h-\r+\p),20+(\h-\r)/\h*\l*\e,20+\e*(\h-\r+\p),green
dsegment 20+\p*\e,20+\e*(\h-\r),20+(\h-\r)/\h*\l*\e+\p*\e,20+\e*(\h-\r),green
dsegment 20,20+\e*(\h-\r+\p),20+\p*\e,20+\e*(\h-\r),green
dsegment 20+(\h-\r)/\h*\l*\e+\p*\e,20+\e*(\h-\r),20+(\h-\r)/\h*\l*\e,20+\e*(\h-\r+\p),green
text black,10,10+\p*\e,medium,\A
text black,10+\p*\e,10,medium,\B
text black,30+(\p+\l)*\e,10,medium,\C
text black,30+\l*\e,10+\p*\e,medium,\D
text black,10,10+(\p+\h)*\e,medium,\E
text black,10+\p*\e,10+\h*\e,medium,\F
text black,30+(\p+\l)*\e,10+\h*\e,medium,\G
text black,30+\l*\e,10+(\p+\h)*\e,medium,\H
text black,10,18+\e*(\h-\r+\p),medium,\I
text black,25+(\h-\r)/\h*\l*\e,15+\e*(\h-\r+\p),medium,\J
text black,10+\p*\e,10+\e*(\h-\r),medium,\K
text black,25+(\h-\r)/\h*\l*\e+\p*\e,10+\e*(\h-\r),medium,\L
}

\integer{r2=\h-\r}
\text{rep=\r2/\h*\l}
\integer{ch=randint(1..3)}
\text{prec=item(\ch,\name_prec)}
\real{rep=rint((\rep)*10^(\ch-1))/10^(\ch-1)}
\statement{
<div class="wims_columns">
 <div class="medium_size img_col">\draw{40+\e*\x,40+\e*\y}{\dessin}</div>
 <div class="medium_size text_col">
\A\B\C\D\E\F\G\H \name_enonce[1;] :
<ul><li> \A\B=\p cm </li><li> \B\C=\l cm </li><li> \A\E=\h cm</li></ul>
<ul class="wims_nopuce">
<li>\name_enonce[2;1] \I \name_enonce[2;2] \K \name_enonce[2;3] [\A\E]
  \name_enonce[2;4] [\B\F] \name_enonce[2;5] \A\I=\B\K=\r2 cm.
</li><li>
\name_enonce[3;1] \J \name_enonce[3;2] (\A\H) \name_enonce[3;3] (\I\J)
\name_enonce[3;4] (\E\H) \name_enonce[3;5]
</li><li>
\name_enonce[4;1], \L \name_enonce[4;2] (\B\G) \name_enonce[4;3] (\K\L)
  \name_enonce[4;4] (\F\G) \name_enonce[4;5]
</li><li>
\name_enonce[5;1] \I\J\L\K \name_enonce[5;2] \A\I\J\B\K\L \name_enonce[5;3]
</li></ul>
\name_question?
<div class="spacer">
<b>\name_youranswer</b> : \embed{r1,7} cm.
</div>
<div class="wims_instruction">\name_inst[1], \name_inst[2] \prec</div>
 </div>
</div>}

\answer{}{\rep}{type=numexp}
