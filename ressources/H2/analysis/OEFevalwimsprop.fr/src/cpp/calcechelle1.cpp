target=calcechelle1

#include "author.inc"
#include "lang_titles.inc"
#include "lang.inc"

 \text{bad=\name_bad}
 \integer{ch=randint(1..2)}
 \integer{l1=randint(10..20)}
 \integer{l2=\ch=1?randint(2..9):randint(21..30)}
 \text{unit1=randitem(cm,mm,dm)}
 \text{unit2=\unit1}
 \text{good=\bad[\ch]}

\statement{
\l1 \unit1 \name_enonce[1] \l2 \unit2 \name_enonce[2]<br>
<p>\name_question?</p> }
\choice{}{\good}{\bad}
