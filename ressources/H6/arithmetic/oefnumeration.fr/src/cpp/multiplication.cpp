target=multiplication

#include "header.inc"
#include "lang_titles.inc"

\title{TITLE}
\title_it{TITLE_it}

 \text{b = randint( 5..14)}
 \text{n = randint (3..\b-1)}
\text{z =}
\text{zn=wims(exec float_calc
obase=\b; ibase=10; \n)}
\text{zi=}

 \for{ i = 1 to \b-1}{
 \text{z= \z, wims(exec float_calc
obase=\b; ibase=10;\n*\i)}
\text{zi=\zi, wims(exec float_calc
obase=\b; ibase=10; \i)}
}
\text{zi=wims(nonempty items \zi)}
\text{z=wims(nonempty items \z)}

\text{STEPS=wims(makelist r x for x = 1 to \b-1)}
\steps{\STEPS}

#include "lang.inc"
\text{latexoperation=\begin{enumerate}}
\for{ v = 1 to \b -1} {
\text{latexoperation=\latexoperation
\item \(\zi[\v] \times \zn\) = .......}
}
\text{latexoperation=\latexoperation \end{enumerate}}

\statement{<div class="spacer">\name_statement</div>
<ul class="wims_nopuce">
\for{ j = 1 to \b-1} {
  <li><label for="reply\j">\zi[\j] \times \zn</label> = \embed{reply \j,5}</li>}
</ul>
}

\answer{\zn \(\times\) 1}{\z[1]}{type=nocase}
\answer{\zn \(\times\) 2}{\z[2]}{type=nocase}
\answer{\zn \(\times\) 3}{\z[3]}{type=nocase}
\answer{\zn \(\times\) 4}{\z[4]}{type=nocase}
\answer{\zn \(\times\) 5}{\z[5]}{type=nocase}
\answer{\zn \(\times\) 6}{\z[6]}{type=nocase}
\answer{\zn \(\times\) 7}{\z[7]}{type=nocase}
\answer{\zn \(\times\) 8}{\z[8]}{type=nocase}
\answer{\zn \(\times\) 9}{\z[9]}{type=nocase}
\answer{\zn \(\times\) 10}{\z[10]}{type=nocase}
\answer{\zn \(\times\) 11}{\z[11]}{type=nocase}
\answer{\zn \(\times\) 12}{\z[12]}{type=nocase}
\answer{\zn \(\times\) 13}{\z[13]}{type=nocase}
\answer{\zn \(\times\) 13}{\z[14]}{type=nocase}
\answer{\zn \(\times\) 13}{\z[15]}{type=nocase}

\latex{
\begin{statement}
\name_statement
\latexoperation
\end{statement}
}
