target=calcfract1 calcfract2 calcfract3 calcfract4 calcfract5
\precision{100}
#include "author.inc"
#include "lang_titles.inc"
#include "lang.inc"

\text{v=wims(values v for v=2 to 9)}
\text{v=shuffle(\v)}
\text{sg=randitem(+,-)}

#if defined TARGET_calcfract1
 \text{calc=\v[1]/\v[2] \sg \v[3]/\v[4]}
 \text{enonce=texmath(\calc)}
#endif
#if defined TARGET_calcfract2
 \text{calc=1/\v[1] + 1/\v[2]}
 \text{enonce=\frac{1}{\v[1]} + \frac{1}{\v[2]}}
#endif
#if defined TARGET_calcfract3
 \text{calc=\v[1]/\v[2] \sg \v[3]/\v[4] * (\v[5]/\v[6])}
 \text{enonce=\frac{\v[1]}{\v[2]} \sg \frac{\v[3]}{\v[4]} \times \frac{ \v[5]}{\v[6]}}
#endif
#if defined TARGET_calcfract4
 \text{calc=(\v[1]/\v[2] \sg \v[3]/\v[4]) * \v[5]/\v[6]}
 \text{enonce=randitem((\frac{\v[1]}{\v[2]} \sg \frac{\v[3]}{\v[4]}) \times \frac{ \v[5]}{\v[6]}, \frac{ \v[5]}{\v[6]}\times(\frac{\v[1]}{\v[2]} \sg \frac{\v[3]}{\v[4]}) )}
#endif
#if defined TARGET_calcfract5
 \text{calc=\v[1]/\v[2] \sg (\v[3]/\v[4]) / (\v[5]/\v[6])}
 \text{enonce=\frac{\v[1]}{\v[2]} \sg \frac{\v[3]}{\v[4]} : \frac{ \v[5]}{\v[6]}}
#endif

\text{A=randitem(A,B,C,D,E,F)}
\text{rep=simplify(\calc)}
\statement{
  \name_question[1] \A \name_question[2]:
<div class="wimscenter">\(\A = \enonce)</div>
<div class="spacer">
<b>\name_answer:</b>
<label for="reply1">\(\A = )</label>\embed{r1,6}.
</div>
}

\answer{\A}{\rep}{type=numexp}
