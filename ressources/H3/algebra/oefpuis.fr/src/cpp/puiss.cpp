target=puis1 puis2 puis3

#include "author.inc"
#include "lang_titles.inc"
#include "lang.inc"
#if defined TARGET_puis1
\text{type=puissance1}
#endif
#if defined TARGET_puis2
\text{type=puissance2}
#endif
#if defined TARGET_puis3
\text{type=puissance3}
#endif
\precision{10000}

\text{enonce=slib(expnumeric \type)}
\text{rep=maxima(\enonce;)}
\integer{confparm1=\confparm1=?1}
\integer{confparm1=\confparm1>5?5}
\text{let=randitem(A,B,C,D,E,F,G)}
#if defined TARGET_puis3
\text{rep=wims(replace internal / by , in \enonce)}
\text{den=item(2,\rep)}
\text{den=texmath(\den)}
\text{num=item(1,\rep)}
\text{num=texmath(\num)}
\text{num=wims(replace internal \left by \times\left in \num)}
\text{rep=maxima(\enonce;)}
\text{enonce=\frac{\num}{\den}}
#endif
\statement{\name_question:
  <div class="wimscenter">\(\let = \enonce\)</div>
<div class="wimscenter"><label for="reply1">\(\let\)</label> = \embed{r1,10}.</div>
<div class="wims_instruction">
\name_instruction</div>
}

\answer{\(\enonce\)}{\rep}{type=numexp}
\latex{
\begin{statement}
\name_question:
  \begin{center}\(\let = \enonce\)
  \end{center}
\end{statement}
}
