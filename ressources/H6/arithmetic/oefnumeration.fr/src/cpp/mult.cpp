target=mult

#include "header.inc"
#include "lang_titles.inc"

\title{TITLE}
\title_it{TITLE_it}

 \text{s=randint(2..3)}
\text{b=randint(4..9)}
\text{Nl = wims(randint \b-1 repeat \s)}
\text{Ml= wims(randint \b-1 repeat \s)}

\text{N = wims(replace internal , by in \Nl)}
\text{M = \s=2 ? wims(replace internal , by in \Ml) :\Ml[2]\Ml[3]}

\text{h =wims(exec float_calc
obase=\b; ibase=\b;\N*\M)}

\text{h1 =wims(exec float_calc
obase=10; ibase=\b;\h)}

#include "lang.inc"

\statement{\name_statement
<div class="wimscenter">\(\N * \M = \h\) .</div>
}

\answer{\name_base}{\base}

\text{z= wims(exec float_calc
obase=\base; ibase=\base;\N*\M)}
\condition{}{\z = \h}{type=hide}
\feedback{\z = \h and \base != \b}{
<div class="reponse">\name_feedback1</div>}

\feedback{\z !=\h and
\base > \Nl[1] and \base > \Nl[2] and \base > \Ml[2]
and \base > \Nl[3] and (\base > \Ml[1] or \s = 3)
}{ <div class="reponse">
  \name_feedback2[1] \base, \name_feedback2[2] \(\N * \M = \z\).
  \name_feedback2[3] \(b = \b\).
</div>
}
\feedback{\base <= \Nl[1] or \base <= \Nl[2] or \base <= \Ml[2]
or \base <= \Nl[3] or (\base <= \Ml[1] and \s = 2)}{
<div class="reponse">
\name_feedback3 \(b = \base\).
</div>}






