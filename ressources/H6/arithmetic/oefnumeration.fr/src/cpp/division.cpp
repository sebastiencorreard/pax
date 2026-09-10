target=division

#include "header.inc"
#include "lang_titles.inc"

\title{TITLE}
\title_it{TITLE_it}

\text{b = randint( 5..14)}
\text{q = randint (5..16)}
\text{N = randint(6..20)}
\text{r = randint (0..\N-1)}
\text{A = \N*\q + \r}

\text{N= wims(exec float_calc
obase=\b; ibase=10;\N)}
\text{r= wims(exec float_calc
obase=\b; ibase=10;\r)}
\text{q= wims(exec float_calc
obase=\b; ibase=10;\q)}
\text{A= wims(exec float_calc
obase=\b; ibase=10;\A)}

#include "lang.inc"

\statement{\name_statement[1]
\(\overline {\A}) \name_by \(\overline{\N})
 \name_statement[2]

<div class="wimscenter"> \(\overline {\A}\) = \embed{reply1,7} \times \(\overline {\N}\) + \embed{reply2,7}</div>
}

\answer{\name_quotient}{\q}{type=nocase}
\answer{\name_remainder}{\r}{type=nocase}

