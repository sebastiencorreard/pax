target=divisiontrou

#include "header.inc"
#include "lang_titles.inc"

\title{TITLE}
\title_it{TITLE_it}

\text{lim = 13}
\text{A = randint(50..64)}
\text{B = randint (10..16)}
\text{b =randint(3..\lim)}

\text{A= wims(exec float_calc
obase=\b; ibase=10; \A)}

\text{cnt_A=wims(charcnt \A)}
\text{i = randint(1..\cnt_A)}
\text{Atronq = wims(replace internal char number \i by x in \A)}
\text{a = wims(char \i of \A)}
\text{B= wims(exec float_calc
obase=\b; ibase=10;\B)}
\text{C= wims(exec float_calc
obase=\b; ibase=\b;\A*\B)}

\text{cnt_C=wims(charcnt \C)}
\text{j = randint(1..\cnt_C)}
\text{Ctronq = wims(replace internal char number \j by y in \C)}
\text{c = wims(char \j of \C)}

#include "lang.inc"

\statement{\name_statement

<div class="wimscenter"> \(\overline{\Atronq} \times \overline{\B} \)
 = \(\overline{\Ctronq})
 </div>
<div class="wims_instruction">\name_instruction</div>
}

\answer{La base }{\base}
\answer{\(x\) : }{\aa}{type=case}
\answer{\(y\) : }{\cc}{type=case}

\text{Aa = wims(replace internal char number \i by \aa in \A)}
\text{Cc = wims(replace internal char number \j by \cc in \C)}
\condition{base > 1}{\base>=2}
\text{test= wims(exec float_calc
obase=\base; ibase=\base; \Aa*\B - \Cc)}

\text{testa= wims(exec float_calc
obase=\base; ibase=\base; \aa - \base)}
\text{testa2=wims(charcnt \aa)}

\text{testc= wims(exec float_calc
obase=\base; ibase=\base; \cc - \base)}
\text{testb2=wims(charcnt \cc)}

\condition{\aa \name_condition \base}{base > 1 and \testa <= 0 and \testa2 =1}
\condition{\cc \name_condition \base}{base > 1 and \testc <= 0 and \testb2 =1}
\condition{\Aa \(\times\) \B = \Cc \name_inbase \base ? }{base > 1 and \test = 0}

\solution{\name_solution[1] \(\A \times \B = \C\) \name_solution[2] \(b=\b\).}

