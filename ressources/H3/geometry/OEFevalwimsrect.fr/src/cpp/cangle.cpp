target=cangle1 cangle2 cangle3 cangle4 cangle5
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

#if defined TARGET_cangle1
 \integer{r1=randint(5..10)}
 \integer{r2=randint(11..20)}
 \text{don=<li>\B\C = \r2 cm</li><li> \A\B = \r1 cm</li>}
 \text{rep=180/pi*arccos(\r1/\r2)}
 #include "triangle1.inc"
#endif
#if defined TARGET_cangle2
 \integer{r1=randint(5..10)}
 \integer{r2=randint(11..20)}
 \text{don=<li>\B\C = \r2 cm</li><li> \A\B = \r1 cm</li>}
 \text{rep=180/pi*arccos(\r1/\r2)}
 #include "triangle2.inc"
#endif
#if defined TARGET_cangle3
 \integer{r1=randint(5..10)}
 \integer{r2=randint(11..20)}
 \text{don=<li>\B\C = \r2 cm</li><li> \A\B = \r1 cm</li>}
 \text{rep=180/pi*arccos(\r1/\r2)}
#endif
#if defined TARGET_cangle4
 \integer{r1=randint(5..10)}
 \integer{r2=randint(11..20)}
 \text{don=<li>\B\C = \r2 cm</li><li> \A\C = \r1 cm</li>}
 \text{rep=180/pi*arcsin(\r1/\r2)}
 \integer{ch=randint(1..2)}
 \if{\ch=1}{
  #include "triangle1.inc"
 }{
  #include "triangle2.inc"
 }
#endif
#if defined TARGET_cangle5
 \integer{r1=randint(5..10)}
 \integer{r2=randint(11..20)}
 \text{don=<li>\B\C = \r2 cm</li><li> \A\C = \r1 cm</li>}
 \text{rep=180/pi*arcsin(\r1/\r2)}
#endif

\integer{ch=randint(0..2)}
\text{arr=item(\ch+1,\name_precision)}
\real{rep=rint((\rep)*10^\ch)/10^\ch}

\if{\dessin!=}{\text{image=draw(240,140
\dessin)}}
\statement{
\if{\dessin!=}{
<div class="wims_columns">
 <div class="medium_size img_col"> <img src="\image" alt=""></div>
 <div class="medium_size text_col">
}
 \A\B\C \name_enonce \A.
<ul>\don</ul>
\name_question[1] \(\widehat{\A\B\C}) \name_question[2] \arr.
<div class="spacer">
<b>\name_answer</b>:
<label for="reply1">\(\widehat{\A\B\C} \simeq\)</label> \embed{r1,5}°.
</div>
\if{\dessin!=}{</div></div>}
}

\answer{\(\widehat{\A\B\C}\)}{\rep}{type=numexp}
