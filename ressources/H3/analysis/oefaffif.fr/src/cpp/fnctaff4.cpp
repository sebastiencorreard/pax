target=fnctaff4
\language{fr}
\range{-5..5}
\computeanswer{no}
\format{html}
\precision{10000}
#include "author.inc"
#include "lang_titles.inc"
#include "lang.inc"

\text{nom=randitem(f,g,h)}
\integer{a=random(-1,1)*random(1..7)}
\integer{b=random(-1,1)*random(1..7)}
\function{d=\a*(x)+(\b)}
\text{listn=wims(values v,-v for v=1 to 10)}
\text{listn=shuffle(\listn)}
\integer{abs1=\listn[1]}
\integer{abs2=\listn[2]}

\integer{ord1=evalue(\d,x=\abs1)}
\integer{ord2=evalue(\d,x=\abs2)}

\text{rep1=simplify(\ord1=\abs1*(\a)+b)}
\text{rep2=simplify(\ord2=\abs2*(\a)+b)}
\matrix{don=\name_don[1] \(\nom\) \name_don[2] \(\abs1\) \name_don[3] \(\ord1\),\rep1
\name_don[1] \(\nom\) \name_don[2] \(\abs2\) \name_don[3] \(\ord2\),\rep2}
\text{don=randrow(\don)}
\text{phrase=item(1,\don)}
\text{rep=item(2,\don)}

\steps{r1
r2
r3}

\statement{\(\nom) \name_enonce[1] \(\abs1\) \name_enonce[2]
  \(\ord1\) \name_enonce[3] \(\abs2) \name_enonce[4] \(\ord2\).
  \name_aim[1] \(\nom\).
  \name_aim[2],\name_aim[3] \(\nom(x)=a x+b\) \name_aim[4] \(x\).
  <p>\name_resolv:</p>
  <div class="spacer">
  <strong>\name_quest[1] 1</strong> :
  \name_question[1] \(\nom\), \name_question[2] \(\frac{\nom(u)-\nom(v)}{u-v}),
  \name_question[3], \name_question[4] \(\nom\).
  \name_question[5]
 <div class="spacer">
 \name_quest[2] :
\if{\step=1}{
\(a =) \embed{r1}</div>
}{
\(\special{color=green}a = \a\).</div>
<strong>\name_quest[1] 2</strong> :
  \name_deduc[1] \(\nom\) \name_deduc[2] \(\nom(x)=\a x+b\).
<p>
\name_question2
</p>
<div class="wimscenter" style="font-style:italic">\phrase.</div>

<div class="spacer">\name_quest[2] :
\if{\step=2}{\embed{r2}</div>
}{
\if{\step=3}{
\(\special{color=green}\rep).</div>
<strong>\name_quest[1] 3</strong> : \name_question3
<div class="wimscenter"><label for="reply3">\(b=\)</label>
\embed{r3}</div>
}}}
</div>}

\answer{a}{\a}{type=auto}
\answer{\name_answer}{\rep}{type=auto}
\answer{b}{\b}{type=auto}
