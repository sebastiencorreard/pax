target=fnctaff3
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
\text{listn=wims(values v,-v for v=1 to 10)}
\text{listn=shuffle(\listn)}
\integer{abs1=\listn[1]}
\integer{abs2=\listn[2]}

\function{funct=\a*(x)+(\b)}

\integer{ord1=evalue(\funct,x=\abs1)}
\integer{ord2=evalue(\funct,x=\abs2)}

\text{rep1=\ord1=\abs1*a+b}
\text{rep2=\ord2=\abs2*a+b}

\steps{r1
r2
r3,r4}

\statement{\(\nom) \name_enonce[1] \(\abs1\) \name_enonce[2] \(\ord1\)
  \name_enonce[3] \(\abs2) \name_enonce[4] \(\ord2\).
<p>\name_aim[1] \(\nom). \name_aim[2], \name_aim[3]
  \(\nom(x)=a x+b) \name_aim[4] \(x\). </p>
\name_resolv.
<div class="spacer">
<strong>\name_quest[1] 1</strong> : \name_quest[3]
<div class="wimscenter" style="font-style:italic">
\name_sentence[1] \(\nom\) \name_sentence[2] \(\abs1\) \name_sentence[3]
  \(\ord1\).</div>
\name_quest[4] \(a) \name_and \(b\).</div>
<div>\name_quest[2] :
\if{\step=1}{
\embed{r1}</div>
}{
\(\special{color=green}\rep1).
</div>
<strong>\name_quest[1] 2</strong> : \name_quest[3]
<div class="wimscenter" style="font-style:italic">
\name_sentence[1] \(\nom\) \name_sentence[2] \(\abs2) \name_sentence[3]
\(\ord2).</div>
\name_quest[4] \(a\) \name_and \(b\).
<div>\name_quest[2] :
\if{\step=2}{\embed{r2}</div>
}{
\if{\step=3}{
\(\special{color=green}\rep2).</div>
<strong>\name_quest[1] 3</strong> :
\name_question
<div class="wims_instruction">\name_inst</div>
<div class="wimscenter">\(a=)\embed{r3}<br/>
<label for="reply4">\(b=\)</label>\embed{r4}
</div>
}}}
}

\answer{\name_answer[1]}{\rep1}{type=auto}
\answer{\name_answer[2]}{\rep2}{type=auto}
\answer{a}{\a}{type=auto}
\answer{b}{\b}{type=auto}
