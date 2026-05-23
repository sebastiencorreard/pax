target=deve2
#include "author.inc"
#include "lang_titles.inc"
#include "lang.inc"
\precision{10000}
\text{signe=+}
#include "confparm.inc"

\integer{size=4}
\text{size2=40x25x1}
\text{x=random(x,y,z,a,b)}
\text{lt=wims(values v,-v for v=2 to 15)}
\text{lt=shuffle(\lt)}
\integer{a=item(1,\lt)}
\integer{b=item(2,\lt)}
\integer{c=item(3,\lt)}
\integer{d=item(4,\lt)}
text{fab=\lt}

\text{lt=wims(values v for v=0 to \confparm1)}
\text{lt=shuffle(\lt)}
\text{p1=item(1,\lt)}
\text{p2=item(2,\lt)}
\text{lt=shuffle(\lt)}
\text{p3=item(1,\lt)}
\text{p4=item(2,\lt)}

\text{m1=simplify(\a*\x^\p1)}
\text{m2=simplify(\b*\x^\p2)}
\text{m3=simplify(\c*\x^\p3)}
\text{m4=simplify(\d*\x^\p4)}

\text{rep=wims(rawmath (\m1+\m2)*(\m3+\m4))}
\text{rep13=maxima(expand(\rep);)}
\text{A1=texmath(\m1)}
\text{A2=texmath(\m2)}
\text{A3=texmath(\m3)}
\text{A4=texmath(\m4)}
\text{A=\A1,\A2,\A3,\A4}
\text{enonce=texmath(\rep)}

\text{coul=red,green,blue,gray}
\text{coul=shuffle(\coul)}
\text{t1=\special{color=\coul[1]}}
\text{t0=\special{color=black}}
\text{t2=\special{color=\coul[2]}}
\text{t3=\special{color=\coul[3]}}
\text{t4=\special{color=\coul[4]}}
\text{tmp=()}
\text{po=wims(char 1 of \tmp)}
\text{pf=wims(char 2 of \tmp)}

\text{tmps=wims(char 1 of \A[4])}
\text{tmps=\tmps=-?:+}
\text{tmps2=wims(char 1 of \A[2])}
\text{tmps2=\tmps2=-?:+}
\text{enonce1=(\t1 \A[1] \t2 \tmps2 \A[2] \t0)(\t3 \A[3] \t4 \tmps\A[4] \t0)}
\text{tmp=\A[1]*(\A[3]),\A[1]*(\A[4]),\A[2]*(\A[3]),\A[2]*(\A[4]),\A[1]*(\A[3])+(\A[1]*(\A[4]))+(\A[2]*(\A[3]))+(\A[2]*(\A[4]))}
\text{tmp=wims(replace internal \x by *\x in \tmp)}
\text{repco=}
\for{i=1 to 4}{
  \text{tmp7=simplify(\tmp[\i])}
  \text{repco=wims(append item \tmp7 to \repco)}
}
\text{tmp7=maxima(\tmp[5];)}
\text{repco=\repco,\tmp7}

\text{ligne1=<td>\(\enonce1)</td>
<td>=</td>
<td>\(\t1\po \A[1] \pf\t0\times \t3\po \A[3] \pf) </td>
<td>+</td>
<td>\(\t1\po \A[1] \pf\t0 \times \t4\po \A[4] \pf) </td>
<td>+</td>
<td>\(\t2\po \A[2] \pf\t0 \times \t3\po \A[3] \pf) </td>
<td>+</td>
<td>\(\t2\po \A[2] \pf\t0 \times \t4\po \A[4] \pf) </td>}

\text{tmp1=- isin \repco[2]?(\repco[2]):\repco[2]}
\text{tmp2=- isin \repco[3]?(\repco[3]):\repco[3]}
\text{tmp3=- isin \repco[4]?(\repco[4]):\repco[4]}
\text{ligne2=<td></td>
<td>=</td>
<td> \(\repco[1])</td>
<td>\signe</td>
<td> \(\tmp1\) </td>
<td>+</td>
<td> \(\tmp2\) </td>
<td>+</td>
<td> \(\tmp3\) </td>
}
\if{\confparm2=1}{
  \matrix{type=r1,r2,r3,r4,r5,r7,r8
  r9,r10,r11,r12
  r13}
}{
  \matrix{type=r13}
}
\steps{\type}
\statement{
  \name_enonce \(\enonce).
  <div class="spacer">
  \if{\confparm2=1}{
    \name_enonce0
    \if{\step=1}{
      <b>\name_step 1 :</b> \name_enonce1[1],
      \name_enonce1[2]
      \((a+b)(c+d)=a c+a d+b c+b d\)
      \name_enonce1[3].
      <div class="wimscenter">
       \(\enonce1= \t1\po) \embed{r1,\size2} \(\t1\pf\t0\times \t3\po) \embed{r2,\size2}
       \(\t3\pf\t0 + \t1\po) \embed{r3,\size2} \(\t1\pf\t0 \times \t4\po)
       \embed{r4,\size2} \(\t4\pf\t0 + \t2\po) \embed{r5,\size2} \(\t2\pf\t0 \times \t3\po)
       \embed{r6,\size2} \(\t3\pf\t0 + \t2\po) \embed{r7,\size2} \(\t2\pf\t0 \times \t4\po)
       \embed{r8,\size2} \(\t4\pf)
      </div>
      <div class="wims_instruction">\name_instruction</div>
    }{
      \if{\step=2}{
        <b>\name_step 2 :</b> \name_enonce2.
        <table class="wimscenter wimsnoborder">
        <tr>\ligne1</tr>
        <tr>
        <td></td>
        <td>=</td>
        <td> \embed{r9,4*\size}</td>
        <td>+</td>
        <td> \embed{r10,4*\size} </td>
        <td>+</td>
        <td> \embed{r11,4*\size} </td>
        <td>+</td>
        <td> \embed{r12,4*\size} </td>
        </tr>
      }{
        <b>\name_step 3 :</b> \name_enonce3
        <table class="wimscenter wimsnoborder">
        <tr>\ligne1</tr>
        <tr>
        \ligne2
        </tr>
        <tr>
        <td></td>
        <td>=</td>
        <td colspan="7"> \embed{r13,8*\size} </td>
        </tr>
      }
      </table>
      </div>
    }
  }{
    <div class="wimscenter">
    <label for="reply13">\(\enonce = \)</label>\embed{r13,8*\size}.
  </div>
  }
  </div>
}
\answer{\name_answer 1}{\A[1];\A}{type=clickfill}
\answer{\name_answer 2}{\A[3];\A}{type=clickfill}
\answer{\name_answer 3}{\A[1];\A}{type=clickfill}
\answer{\name_answer 4}{\A[4];\A}{type=clickfill}
\answer{\name_answer 5}{\A[2];\A}{type=clickfill}
\answer{\name_answer 6}{\A[3];\A}{type=clickfill}
\answer{\name_answer 7}{\A[2];\A}{type=clickfill}
\answer{\name_answer 8}{\A[4];\A}{type=clickfill}
\answer{\name_answer 9}{\repco[1]}{type=litexp}{option=polexpand}
\answer{\name_answer 10}{\repco[2]}{type=litexp}{option=polexpand}
\answer{\name_answer 11}{\repco[3]}{type=litexp}{option=polexpand}
\answer{\name_answer 12}{\repco[4]}{type=litexp}{option=polexpand}
\answer{\(\enonce)}{\rep13}{type=litexp}{option=polexpand}

\solution{
<div class="wims_scrollable"><table class="wimsnoborder">
<tr>\ligne1</tr>
<tr>\ligne2</tr>
<tr>
   <td></td>
   <td>=</td>
   <td colspan="7"> \(\repco[5])</td>
</tr>
</table></div>}
