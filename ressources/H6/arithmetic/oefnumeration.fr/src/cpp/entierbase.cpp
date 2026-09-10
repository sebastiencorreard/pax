target=entierbase

#include "header.inc"
#include "lang_titles.inc"

\title{TITLE}
\title_it{TITLE_it}
\integer{base=randint(2..10)}
\integer{b=\base-1}
\integer{n=randint(2..8)}
\integer{sol1=(\base-1)*\base^(\n-1)}
\integer{n1=\n-1}
\integer{rep1=\base^(\n)}
\integer{ch=randint(0..\b)}
\if{\ch=0}{\integer{sol2=(\n-1)*\b^(\n-1)} }
  {\integer{sol2=\b^(\n-2)*(\n*\b+1-\n)} }
\steps{reply1
reply2}

#include "lang.inc"

\statement{
<ul class="wims_nopuce"><li>
  \name_statement1
  \if{\step=1}{
  <div class="wimscenter">\embed{r1,6}</div>
  <li>
}
\if{\step=2}{
<div class="oef_indgood">
\name_statement12
</div>
</li><li>
  \name_statement2
 <div class="wimscenter">\embed{r2,6}</div>
 </li>}
 </ul>
}

\answer{1- \name_answer}{\sol1}{type=numeric}
\answer{2- \name_answer}{\sol2}{type=numeric}
\feedback{\reply1=\rep1}{
<div class="oef_indbad"> \name_feedback1
 \(\{0,...,\b\}^\n \). \name_feedback2</div>}
