target=deve3 deve4 deve7 deve8
#include "author.inc"
#include "lang_titles.inc"
\precision{10000}
#include "lang.inc"
#include "confparm.inc"

#if defined TARGET_deve3 || defined TARGET_deve7
\text{signe=+}
#endif
#if defined TARGET_deve4 || defined TARGET_deve8
\text{signe=-}
#endif
#if defined TARGET_deve3 || defined TARGET_deve4 || defined TARGET_deve7 || defined TARGET_deve8
\integer{size=8}
#endif
\text{size2=40x25x1}
\text{x=random(x,y,z,a,b)}
#if defined TARGET_deve3 || defined TARGET_deve4 || defined TARGET_deve7 || defined TARGET_deve8
\text{a=random(1,-1)*randint(2..15)}
\text{a=simplify(\a)}
\text{b=randint(2..15)}
\text{lt=wims(values v for v=0 to \confparm1)}
\text{lt=shuffle(\lt)}
#endif
\integer{p1=item(1,\lt)}
\integer{p2=item(2,\lt)}
\text{m1=\a*\x^\p1}
\text{m1=simplify(\m1)}
\text{rep1=texmath(\m1)}
\text{m2=\b*\x^\p2}
\text{m2=simplify(\m2)}
\text{rep2=texmath(\m2)}

\text{rep=(\m1 \signe \m2)^2}
\text{rep8=maxima(expand(\rep);)}

\text{tmp1=texmath(\m1)}
\text{tmp2=texmath(\m2)}
\text{A=\tmp1,\tmp2}
\text{enonce=(\A[1] \signe \A[2])^2}
#if defined TARGET_deve3 || defined TARGET_deve4
\if{\confparm2=1}{
  \text{coul=red,green,blue}
  \text{coul=shuffle(\coul)}
  \text{t1=\special{color=\coul[1]}}
  \text{t0=\special{color=black}}
  \text{t2=\special{color=\coul[2]}}
}
#endif
#if defined TARGET_deve7 || defined TARGET_deve8
  \text{t1=}
  \text{t0=}
  \text{t2=}
#endif
\text{tmp=()}
\text{po=wims(char 1 of \tmp)}
\text{pf=wims(char 2 of \tmp)}
\text{enonce1=(\t1 \A[1] \t0 \signe \t2 \A[2] \t0)^2}
\text{tmp=(\m1)^2,2*(\m1)*(\m2),(\m2)^2}

\text{rep=}
\text{repco=}
\for{i=1 to 3}{
 \text{tmp7=simplify(\tmp[\i])}
 \text{rep=wims(append item \tmp7 to \rep)}
 \text{tmp7=texmath(\tmp7)}
 \text{repco=wims(append item \tmp7 to \repco)}
}
#if defined TARGET_deve3 || defined TARGET_deve4
\text{car1=wims(char 1 of \A[1])}
\text{B1=\car1=-?(\A[1]):\A[1]}
\text{car2=wims(char 1 of \A[2])}
\text{B2=\car2=-?(\A[2]):\A[2]}
#endif
#if defined TARGET_deve7 || defined TARGET_deve8
\text{B1=\A[1]}
\text{B2=\A[2]}
#endif
\text{ligne1=<td>\(\enonce1)</td>
<td>=</td>
<td>\((\t1\A[1]\t0)^2) </td>
<td>\signe</td>
<td>\(2\times \t1\B1\t0\times \t2\B2) </td>
<td>+</td>
<td>\((\t2\A[2]\t0)^2) </td>}
#if defined TARGET_deve3 || defined TARGET_deve4
\text{car1=wims(char 1 of \repco[2])}
\text{tmp1=\car1=-?(\repco[2]):\repco[2]}
\text{tmp2=\repco[3]}
#endif
#if defined TARGET_deve7 || defined TARGET_deve8
\text{tmp1=\repco[2]<0?(\repco[2]):\repco[2]}
\text{tmp2=\repco[3]<0?(\repco[3]):\repco[3]}
#endif
\text{ligne2=<td></td>
<td>=</td>
<td> \(\repco[1])</td>
<td>\signe</td>
<td> \(\tmp1\) </td>
<td>+</td>
<td> \(\tmp2\) </td>}

\if{\confparm2=1}{
\matrix{type=r1,r2,r3,r4
r5,r6,r7
r8}
}{
\matrix{type=r8}
}
\steps{\type}
\text{repf=texmath(item(1,\rep8))}

\statement{
  \name_enonce \(\enonce).
<div class="spacer">
\if{\confparm2=1}{
  \name_enonce0
  <div>
  \if{\step=1}{
    <b>\name_step 1 :</b>
#if defined TARGET_deve3 || defined TARGET_deve4
    \name_enonce1[1]
#endif
    \name_enonce1[2]
    \((a\signe b)^2=a^2\signe 2a b+b^2)
    \name_enonce1[3].
    <div class="wimscenter">
    \(\enonce1= \t1\po) \embed{r1,\size2} \(\t1\pf\t0^2 \signe 2\times \t1\po) \embed{r2,\size2}
    \(\t1\pf\t0 \times \t2\po) \embed{r3,\size2} \(\t2\pf\t0 + \t2\po )
    \embed{r4,\size2} \(\t2\pf\t0^2)
    </div>
    <div class="wims_instruction">\name_instruction</div>
  }{
    <table class="wimscenter wimsnoborder">
    <tr>\ligne1</tr>
    <tr>
    \if{\step=2}{
      <b>\name_step 2 :</b> \name_enonce2
      <td></td>
      <td>=</td>
      <td> \embed{r5,\size}</td>
      <td>\signe</td>
      <td> \embed{r6,\size} </td>
      <td>+</td>
      <td> \embed{r7,\size} </td>
      </tr>
    }{
      <b>\name_step 3 :</b> \name_enonce3
      <br>
      \ligne2
      </tr><tr>
      <td></td>
      <td>=</td>
      <td colspan="5"> \embed{r8,4*\size} </td>
      </tr>
    }
    </table>
  }
  </div>
}{
  <div class="wimscenter">
  <label for="reply8">\(\enonce = \)</label>\embed{r8,4*\size}.
  </div>
}
</div>
}
% réponse pour l'étape 1.
#if defined TARGET_deve3 || defined TARGET_deve4
\answer{\name_answer 1}{\rep1;\rep1,\rep2}{type=clickfill}
\answer{\name_answer 2}{\rep1;\rep1,\rep2}{type=clickfill}
\answer{\name_answer 3}{\rep2;\rep1,\rep2}{type=clickfill}
\answer{\name_answer 4}{\rep2;\rep1,\rep2}{type=clickfill}
#endif
#if defined TARGET_deve7 || defined TARGET_deve8
\answer{\name_answer 1}{\reponse1;\rep1,\rep2}{type=clickfill}
\answer{\name_answer 2}{\reponse2;\rep1,\rep2}{type=clickfill}
\answer{\name_answer 3}{\reponse3;\rep1,\rep2}{type=clickfill}
\answer{\name_answer 4}{\reponse4;\rep1,\rep2}{type=clickfill}
\text{test=simplify((\reponse1)^2+2*(\reponse2)*(\reponse3) + (\reponse4)^2-\enonce)}
\condition{Analyse}{\test=0}
#endif
% réponse pour l'étape 2.
\answer{\name_answer 5}{\rep[1]}{type=litexp}{option=polexpand}
\answer{\name_answer 6}{\rep[2]}{type=litexp}{option=polexpand}
\answer{\name_answer 7}{\rep[3]}{type=litexp}{option=polexpand}

% réponse pour étape 3 (ou unique réponse si pas guidé).
\answer{\name_answer}{\rep8}{type=litexp}{option=polexpand}

\solution{
<div class="wims_scrollable"><table class="wimsnoborder">
<tr>\ligne1</tr>
<tr>\ligne2</tr>
<tr>
   <td></td>
   <td>=</td>
   <td colspan="5"> \(\repf)</td>
</tr>
</table></div>}
