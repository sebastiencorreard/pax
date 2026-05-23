target=longueur4
\language{fr}
\range{-5..5}
#include "author.inc"
\computeanswer{no}
\format{html}
\precision{100000}
\keywords{length, measurement}
#include "lang_titles.inc"
#include "lang.inc"

\integer{h=random(300..400)}
\integer{l=\h}
\integer{p=\h/2+10}
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
\integer{ox=20+\e*(\p+\l)/2}
\integer{oy=20+\e*\p/2}
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
segment 20+\e*\p,20,20+\e*(\l),20+\p*\e,green
segment 20,\e*\p+20,20+\e*(\p+\l),20,green
dsegment \ox,\oy,20,20+\e*(\h+\p),green
dsegment \ox,\oy,20+\l*\e,20+\e*(\h+\p),green
dsegment \ox,\oy,20+(\l+\p)*\e,20+\e*(\h),green
dsegment \ox,\oy,20+(\p)*\e,20+\e*\h,green
text black,\ox-3,\oy-15,medium,O
text black,10,10+\p*\e,medium,\A
text black,10+\p*\e,10,medium,\B
text black,30+(\p+\l)*\e,10,medium,\C
text black,30+\l*\e,10+\p*\e,medium,\D
text black,10,10+(\p+\h)*\e,medium,\E
text black,10+\p*\e,10+\h*\e,medium,\F
text black,30+(\p+\l)*\e,10+\h*\e,medium,\G
text black,30+\l*\e,10+(\p+\h)*\e,medium,\H}

\integer{c=randint(3..9)}
\text{rep=sqrt(3/2)*\c}
\integer{ch=randint(1..3)}
\text{prec=item(\ch,\name_prec)}
\real{rep=rint((\rep)*10^(\ch-1))/10^(\ch-1)}
\text{unit=randitem(cm,dm,m)}
\text{unit=\mathrm{\unit}}

\integer{charet=randint(1..4)}
\text{arete=item(\charet,O\E,O\F,O\G,O\H)}

\statement{
<div class="wims_columns">
 <div class="medium_size img_col"> \draw{40+\e*\x,40+\e*\y}{\dessin}</div>
 <div class="medium_size text_col">
\A\B\C\D\E\F\G\H \name_enonce[1] \c \(\unit\). \name_enonce[2] \A\B\C\D.
<p>
\name_enonce[3] [\arete] \name_enonce[4] O\E\F\G\H ?
</p>
<label for="reply1"><b>\name_youranswer</b> :</label> \embed{r1,7} \(\unit\).
<div class="wims_instruction">\name_inst[1], \name_inst[2] \prec </div>
</div>
</div>
}

\answer{}{\rep}{type=numexp}
