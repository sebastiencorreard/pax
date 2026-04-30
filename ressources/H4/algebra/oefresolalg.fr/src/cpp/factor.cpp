target=factor1 factor2 factor3 factor4 factor5
#include "author.inc"
#include "lang_titles.inc"
#include "lang.inc"
\format{html}
#if defined TARGET_factor1
\integer{a=randint(1..10)}
\integer{b=randint(1..10)}
\text{expdev=texmath(maxima(\a^2*x^2-\b^2))}
\text{expfact=(\a*x+\b)*(\a*x-\b)}
\statement{
\name_question:
<div class="wimscenter"> \(\expdev)</div>
<div class="wimscenter">\name_answer: \embed{reply1}</div>
}
\answer{}{\expfact}{type=algexp}
#endif
#if defined TARGET_factor2
\integer{a=randint(1..10)}
\integer{b=randint(1..10)}
\text{expdev=texmath(maxima(\a^2*x^2-\b))}
\text{expfact=(\a*x+sqrt(\b))*(\a*x-sqrt(\b))}
\statement{
\name_question:
<div class="wimscenter"> \(\expdev)</div>
<div class="wimscenter"><label for="reply1">\name_answer:</label> \embed{reply1}</div>
<div class="wims_instruction">\name_inst[1]
  <span class="tt">sqrt(a)</span> \name_inst[2] \(\sqrt{a}).</div>
}
\answer{}{\expfact}{type=algexp}
#endif
#if defined TARGET_factor3
\integer{a=randint(1..10)}
\integer{b=randint(1..10)}

\text{expdev=texmath(maxima(\a*x^2-\a*\b^2))}
\text{expfact=\a*(x+\b)*(x-\b)}
\statement{
\name_question:
<div class="wimscenter"> \(\expdev)</div>
<div class="wimscenter"><label for="reply1">\name_answer:</label>
\embed{reply1}</div>
<div class="wims_instruction">\name_inst</div>}
\answer{\name_answer}{\expfact}{type=algexp}
#endif
#if defined TARGET_factor4
\integer{a=randint(1..10)}
\integer{b=randint(1..10)}
\integer{rep=randint(1,2)}
\text{sl=-,+}

\text{expdev=texmath(maxima(\a^2*x^2 \sl[\rep] \b^2))}
\text{expfact=(\a*x+\b)*(\a*x-\b)}
\text{mstep=\rep=1?r1
r2:r1}
\steps{\mstep}
\statement{
\if{\step=1}{
  \name_question0:
  <div class="wimscenter">\(\expdev)</div>
  <div class="wimscenter">\embed{reply1}</div>
}{
  \name_question:
  <div class="wimscenter">\(\expdev)</div>
  <div class="wimscenter"><label for="reply2">\name_answer:</label> \embed{reply2}</div>
}
}
\answer{\name_answer2}{\rep;\name_yesno}{type=radio}
\answer{\name_answer}{\expfact}{type=algexp}
#endif
#if defined TARGET_factor5
\integer{a=randint(1..10)}
\integer{b=randint(1..10)}
\integer{n=randint(2..6)}
\integer{nm=\n-1}
\integer{i=randint(1,2)}
\text{sl=-,+}
\text{expdev=texmath(maxima(\a*x^\n \sl[\i] \b*x^\nm))}
\text{expfact=x^\nm(\a*x \sl[\i] \b)}
\statement{
\name_question:
<div class="wimscenter">\(\expdev)</div>
<div class="wimscenter"><label for="reply1">\name_answer:</label> \embed{reply1}</div>
}
\answer{\name_answer}{\expfact}{type=algexp}
#endif
