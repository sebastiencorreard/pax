target=vocabulaire5
\language{fr}
\range{-5..5}
#include "author.inc"
#include "lang_titles.inc"
#include "lang.inc"
\computeanswer{no}
\format{html}
\precision{100}

\text{lettres=randrow(A,B,C
T,R,I
S,V,T
R,S,T
E,F,G)}
\text{lettres=shuffle(\lettres)}
\text{A=item(1,\lettres)}
\text{B=item(2,\lettres)}
\text{C=item(3,\lettres)}

\integer{ch=randint(1..2)}
\if{\ch=1}{
\text{Y=shuffle(\B,\C)}
\integer{ch=randint(1..4)}
\if{\ch=1}{
\text{dessin=range -0.1,1.1,-0.2,1.2
square 0,0.1,10,red
triangle 0,0,1,0,0,1,black
text black,-0.05,0,medium,\A
text black,-0.05,1.05,medium,\Y[1]
text black,1,0,medium,\Y[2]}
}{\if{\ch=2}{
\text{dessin=range -0.1,1.1,1.2,-0.2
square 0,0,10,red
triangle 0,0,1,0,0,1,black
text black,-0.05,0,medium,\A
text black,-0.05,0.95,medium,\Y[1]
text black,1,0,medium,\Y[2]}
}{\if{\ch=3}{
\text{dessin=range 1.1,-0.1,-0.2,1.2
square 0.05,0.1,10,red
triangle 0,0,1,0,0,1,black
text black,-0.05,0,medium,\A
text black,-0.05,1.05,medium,\Y[1]
text black,1.05,0,medium,\Y[2]}
}{
\text{dessin=range 1.1,-0.1,1.2,-0.2
square 0.05,0,10,red
triangle 0,0,1,0,0,1,black
text black,-0.05,-0.05,medium,\A
text black,-0.05,0.95,medium,\Y[1]
text black,1.05,-0.05,medium,\Y[2]}
}}}
 }{

\text{Y=shuffle(\B,\C)}

\real{x=randint(4..16)/10}
\real{y=sqrt(1-(\x-1)^2)}
\real{N=sqrt(\x^2+\y^2)/0.1}
\real{N2=sqrt((2-\x)^2+\y^2)/0.1}
\real{x1=\x-\x/\N}
\real{y1=\y-\y/\N}
\real{x2=\x1+(2-\x)/\N2}
\real{y2=\y1-\y/\N2}
\real{x3=\x+(2-\x)/\N2}
\real{y3=\y-\y/\N2}
\text{dessin=range -0.2,2.2,-0.2,1.2
segment \x1,\y1,\x2,\y2,red
segment \x2,\y2,\x3,\y3,red
triangle 0,0,2,0,\x,\y,black
text black,\x,\y+0.14,medium,\A
text black,-0.05,0,medium,\Y[1]
text black,2,0,medium,\Y[2]}
 }

\text{list=\([\B\C]),\([\A\C]),\([\A\B])}
\text{image=draw(240,140
\dessin)}

\integer{angle=randint(20..70)}
\integer{rep=90-\angle}
\statement{
<div class="wims_columns">
 <div class="medium_size img_col"><img src="\image" alt=""></div>
 <div class="medium_size text_col">
  \A\B\C \name_enonce \A. \name_enonce2[1] \(\widehat{\A\B\C}\)
  \name_enonce2[2] \angle \name_enonce2[3].
  <p>
  \name_question \(\widehat{\A\C\B}\) ?
 </p>
<label for="reply1"><b>\name_answer</b>:</label> \embed{r1,7} °.
</div></div>}

\answer{\name_answer}{\rep}{type=numexp}
