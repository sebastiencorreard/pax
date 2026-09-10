target=changbin

#include "header.inc"
#include "lang_titles.inc"

\title{TITLE}
\title_it{TITLE_it}


\text{a=pari(random\(100000000))}

\integer{b=randint(2..4)}
\integer{k = \b < 4 ? randint(2..3) : 2}
\integer{bb= \b^\k}
\text{N = wims(exec float_calc
obase=\b; \a)}
\text{h =wims(exec float_calc
obase=\bb; ibase=\b ; \N)}
\text{testalph = wims(text select ABCDEFGHIJKLMNOPQ in \h)}
\text{h = wims(trim \h)}
\text{test =wims(char 3 of \h)}
\text{testblanc= \test= ? 1 : 0}

\text{liste1 = 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, A, B, C, D, E, F, ...}
\text{liste1= \liste1[1..min(\bb,12)]}
\text{liste1= \bb>12 ? \liste1, ...}
\text{liste2 = 00, 01, 02, 03, 04, 05, ... , 09, 10, 11, ... }

#include "lang.inc"

\statement{\name_statement
<p class="wimscenter"> \N </p>

<div class="wims_instruction">\if{\bb > 9}{\name_instruction1
  \if{\testblanc=0}{<span style="color:green">\liste1</span> \name_instruction2}
    {<span style="min-width:300px">\liste2</span> \name_instruction3}
   }
 {\name_instruction4}
</div>}

\answer{\name_answer \(\b^\k\)}{\h}{type=nocase}

latex{\name_statement}
