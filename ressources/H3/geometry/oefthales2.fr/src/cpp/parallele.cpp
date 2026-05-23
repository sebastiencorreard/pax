target=parat1 parat2 parap1 parap2

#define PARALLELE parallele

\language{fr}
\range{-5..5}
#include "lang_titles.inc"
#include "author.inc"
\computeanswer{no}
\format{html}
\precision{1000}
\integer{size=50}

\integer{confparm2=1}
\integer{confparm3=\confparm3=?1}

#if defined TARGET_parat1
\integer{ch=1}
#include "triangle.inc"
#endif

#if defined TARGET_parap1
\integer{ch=1}
#include "papillon.inc"
#endif

#if defined TARGET_parat2
\integer{ch=2}
#include "triangle.inc"
#endif

#if defined TARGET_parap2
\integer{ch=2}
#include "papillon.inc"
#endif

\integer{type=randint(1..2)}

\if{\confparm3=1}{
\integer{l1=random(2..11)}
\integer{l2=random(2..11)}
\if{\type=1}{
\integer{coef=random(2,3,4)}
\integer{l3=\coef*\l1}
\integer{l4=\coef*\l2}
}{
\integer{l3=random(4..44)}
\integer{l4=random(4..44)}
\integer{l4=\l3/\l4=\l1/\l2?\l4+1}
}}{
\integer{l1=random(15..50)}
\integer{l2=random(15..50)}
\if{\type=1}{
\integer{coef=random(2..10)}
\integer{l3=\coef*\l1}
\integer{l4=\coef*\l2}
}{
\integer{l3=random(30..500)}
\integer{l4=random(30..500)}
\integer{l4=\l3/\l4=\l1/\l2?\l4+1}
}
\real{l1=\l1/10}
\real{l2=\l2/10}
\real{l3=\l3/10}
\real{l4=\l4/10}
}
\real{l5=\l1+\l2}
\real{l6=\l3+\l4}

#include "lang.inc"

\text{bad1=\name_bad[1] \(\X1, \X4, \X2\) \name_and \(\X1, \X5, \X3\) \name_bad[2],\name_bad[3],\name_bad[4]}
\if{\type=1}{
 \text{bad1=\bad1,\name_bad[5] \(\X1, \X4, \X2\) \name_and \(\X1, \X5, \X3\) \name_bad[6]}
}
\text{good1=item(\type,\bad1)}
\text{good2=item(\type,\name_bad2)}
\text{good3=item(\type,\name_bad3)}

\text{rap1=\X1\X4/\X1\X2,\X1\X5/\X1\X3}
\text{rap2=\X1\X2/\X1\X4,\X1\X3/\X1\X5}

#if defined TARGET_parap2 || defined TARGET_parap1
\text{rep=\X1\X5,\X1\X3,\X1\X4,\X1\X2,\X4\X2,\X5\X3}
\text{valrep=\l3,\l4,\l1,\l2,\l5,\l6}
\text{donnees=<li>\(\X1\X4 = \l1\) cm</li> <li> \(\X1\X5 = \l3\) cm</li>}
\text{donnees=\ch=1?\donnees <li>\(\X1\X2 = \l2\) cm </li><li> \(\X1\X3 = \l4\) cm</li>:\donnees <li>\(\X2\X4 = \l5\) cm </li><li> \(\X3\X5 = \l6\) cm</li>}
#endif

#if defined TARGET_parat2 || defined TARGET_parat1
\text{rep=\X1\X5,\X1\X3,\X1\X4,\X1\X2,\X4\X2,\X5\X3}
\text{valrep=\l3,\l6,\l1,\l5,\l2,\l4}
\text{donnees=<li>\(\X1\X4 = \l1\) cm</li> <li> \(\X1\X5 = \l3\) cm</li>}
\text{donnees=\ch=1?\donnees <li>\(\X1\X2 = \l5\) cm </li><li> \(\X1\X3 = \l6\) cm</li>:\donnees <li>\(\X2\X4 = \l2\) cm </li><li> \(\X3\X5 = \l4\) cm</li>}
#endif

\if{\confparm2=1}{
\matrix{stepdon=r1,r2,r3,r4,r5,r6,r7,r8,c1,c2,c3}
}{
\matrix{stepdon=c2,c3}}
\steps{\stepdon}

\statement{
<div class="wims_columns">
 <div class="medium_size img_col">\draw{\xrange,\yrange}{\dessin}
<div class="wims_instruction">\name_instruction.
</div>
</div>
 <div class="medium_size text_col">
   \name_statement[1] \(\X1\), \(\X4\) \name_and \(\X2\) \name_statement[2] \(\X1\),
   \(\X5\) \name_and \(\X3\) \name_statement[3]. \name_statement[4]:
<ul>
\donnees
</ul>
<b>\name_question:</b> \name_question1[1] \(\lbeg \X4\X5\lend\) \name_and \(\lbeg \X3\X2\lend\) \name_question1[2]?

\if{\confparm2=1}{
  \name_question2:
<table class="wimscenter">
<tr><td>
<table class="wimscenter">
<tr>
<td rowspan="3">\(R_1\)</td>
<td rowspan="3">=</td>
<td>\embed{reply 1,50x20x1}</td>
</tr><tr>
<td><hr></td>
</tr><tr>
<td> \embed{reply 2,50x20x1}</td>
</tr></table>
</td><td>\name_and</td><td>
<table class="wimscenter">
<tr>
<td rowspan="3">\(R_2\)</td>
<td rowspan="3">=</td>
<td>\embed{reply 3,50x20x1}</td>
</tr><tr>
<td><hr></td>
</tr><tr>
<td> \embed{reply 4,50x20x1}</td>
</tr></table>
</td></tr></table>
   \name_question3:
<table class="wimscenter">
<tr><td>
<table>
<tr>
<td rowspan="3">\(R_1\)</td>
<td rowspan="3"> = </td>
<td>\embed{reply 5,5}</td>
</tr><tr>
<td><hr></td>
</tr><tr>
<td> \embed{reply 6,5}</td>
</tr></table>
</td><td>\name_and</td><td>
<table>
<tr>
<td rowspan="3">\(R_2\)</td>
<td rowspan="3">=</td>
<td>\embed{reply 7,5}</td>
</tr><tr>
<td><hr></td>
</tr><tr>
<td> \embed{reply 8,5}</td>
</tr></table>
</td></tr></table>
\name_question4[1] \(R_1\) \name_end \(R_2\) \embed{choice 1}. \name_question4[2],
\name_question4[3] \embed{choice 2}, \name_question4[4] \(\lbeg \X4\X5\lend\) \name_and \(\lbeg \X3\X2\lend\) \embed{choice 3}.}{
\name_yourreply: \name_reply[1] \embed{choice 2}, \name_reply[2] \(\lbeg \X4\X5\lend\) \name_and \(\lbeg \X3\X2 \lend) \embed{choice 3}.}
</div></div>
}

\answer{\name_answers[1] 1}{\r1;\rep}{type=clickfill}
\answer{\name_answers[2] 1}{\r2;\rep}{type=clickfill}
\answer{\name_answers[1] 2}{\r4;\rep}{type=clickfill}
\answer{\name_answers[2] 2}{\r5;\rep}{type=clickfill}
\answer{\name_answers[3] 1}{\r7}{type=auto}
\answer{\name_asnwers[4] 1}{\r8}{type=auto}
\answer{\name_answers[3] 2}{\r9}{type=auto}
\answer{\name_answers[4] 2}{\r10}{type=auto}
\choice{\name_answers[5]}{\good1}{\bad1}
\choice{\name_answers[6]}{\good2}{\name_bad2}
\choice{\name_answers[7]}{\good3}{\name_bad3}

\text{rap1b=\rap1,\r1/\r2,\r4/\r5}
\text{rap1b=wims(listuniq \rap1b)}
\integer{rap1b=items(\rap1b)}
\text{rap2b=\rap2,\r1/\r2,\r4/\r5}
\text{rap2b=wims(listuniq \rap2b)}
\integer{rap2b=items(\rap2b)}
\condition{\name_condition[1]}{((\rap1b=2 or \rap2b=2) and \r1/\r2 notsametext \r4/\r5)}

\real{r1p=item(positionof(\r1,\rep),\valrep)}
\real{r2p=item(positionof(\r2,\rep),\valrep)}
\real{r4p=item(positionof(\r4,\rep),\valrep)}
\real{r5p=item(positionof(\r5,\rep),\valrep)}

\condition{\name_condition[2]}{\r8==\r10}
\condition{\name_condition[3]}{(\r7)/(\r8)==(\r1p)/(\r2p)}
\condition{\name_condition[4]}{(\r9)/(\r10)==(\r4p)/(\r5p)}
