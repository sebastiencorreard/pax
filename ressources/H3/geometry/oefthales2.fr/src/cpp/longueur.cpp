target= pap pap2 triangle triangle2

#define LONGEUER longeuer
\language{fr}
\range{-5..5}
#include "lang_titles.inc"
#include "author.inc"
\computeanswer{no}
\format{html}
\precision{1000}
\integer{size=50}

\integer{confparm2=\confparm2=?2}
\integer{confparm3=\confparm3=?1}

\integer{ch=random(1..2)}
\if{\confparm3=1}{
\integer{l1=random(2..9)}
\integer{l2=random(10..15)}
\integer{tmpl=random(7..19)}
}{
\integer{l1=random(20..90)}
\integer{l2=random(100..150)}
\integer{tmpl=random(70..190)}
\real{l2=\l2/10}
\real{l1=\l1/10}
\real{tmpl=\tmpl/10}
}

#if defined TARGET_pap
\integer{calcul=1}
#include "papillon.inc"
\real{l5=\l1+\l2}
#endif

#if defined TARGET_pap2
\integer{calcul=2}
#include "papillon.inc"
\real{l5=\l1+\l2}
#endif

#if defined TARGET_triangle
\integer{calcul=1}
#include "triangle.inc"
\real{l5=\l2-\l1}
#endif

#if defined TARGET_triangle2
\integer{calcul=2}
#include "triangle.inc"
\real{l5=\l2-\l1}
#endif

\integer{ch2=random(1..2)}
\text{laffl3=\X1\X4,\X4\X5}
\text{laffl4=\X1\X2,\X2\X3}
\text{affl3=item(\ch2,\laffl3)}
\text{affl4=item(\ch2,\laffl4)}

\if{\ch=1}{
\real{l3=\tmpl}
\real{l4=\l2/\l1*\l3}
\real{calc=\l4}
\text{r1=\affl3}
\text{mes=\r1 = \l3}
\text{quest=\affl4}
\text{r2=\X1\X3}
\text{r3=\X1\X5}}
{\real{l4=\tmpl}
\real{l3=\l1/\l2*\l4}
\real{calc=\l3}
\text{r1=\affl4}
\text{mes=\r1 = \l4}
\text{quest=\affl3}
\text{r2=\X1\X5}
\text{r3=\X1\X3}}

\integer{tmp=\calc*10}
\real{calc=\tmp/10}

\text{rep=\X1\X5,\X1\X3,\laffl3,\laffl4,\X4\X2,\X5\X3}

\text{mes2=\calcul=1?\X1\X5 = \l1 :\X3\X5 = \l5 }

\if{\confparm2=1}{
\matrix{stepdon=r1,r2,r3,r4}
}{
\matrix{stepdon=r4}}
\steps{\stepdon}

#include "lang.inc"

\statement{
<div class="wims_columns">
 <div class="medium_size img_col">\draw{\xrange,\yrange}{\dessin}
 <div class="wims_instruction">
  \name_instruction.
</div>
</div>
 <div class="medium_size text_col">

  \name_statement[1] \(\lbeg \X5\X3\lend\) \name_and \(\lbeg \X4\X2\lend\) \name_statement[2] \(\X1\). \name_statement[3] \(\lbeg \X2\X3\lend\) \name_and \(\lbeg \X4\X5\lend\)
  \name_statement[4]. \name_statement[5] \(\sbeg \quest\send\) \name_statement[6]:
<ul>
<li>\(\mes2\) cm </li>
<li>\(\X1\X3\) = \l2 cm </li>
<li>\(\mes\) cm </li>
</ul>
\if{\confparm2=1}{
<b>\name_question 1</b>: \name_question1 \(\lbeg \quest\lend\).
<table class="wimscenter wimsnoborder">
<tr><td>\quest</td><td></td><td>\embed{reply 2,\size}</td>
</tr><tr>
<td><hr></td><td>=</td>
<td><hr></td>
</tr><tr>
<td>\embed{reply 1,\size}</td><td></td><td> \embed{reply 3,\size}</td>
</tr></table>
<b>\name_question 2 :</b> \name_question2 \(\sbeg \quest \send\) ? <br/>
  <label for="reply4">\name_answer:</label> \embed{reply 4, 10}}
{\name_label \(\sbeg \quest \send\) ?}
</div></div>
<div class="wims_instruction spacer">\name_separator.</div>
}

\answer{den1}{\r1;\rep}{type=clickfill}
\answer{num1}{\r2;\rep}{type=clickfill}
\answer{den2}{\r3;\rep}{type=clickfill}
\answer{\name_length}{\calc cm}{type=units}
