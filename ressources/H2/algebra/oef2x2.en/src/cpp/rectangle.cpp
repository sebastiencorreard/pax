target=rectangle
#include "author.inc"
#include "lang_titles.inc"
#include "lang.inc"

\precision{10000}
\keywords{pbsolving,linear_system}
\integer{y=random(20..50)}
\integer{diff=random(20..50)}
\integer{x=\y+\diff}
\integer{peri=2*(\x+\y)}

\statement{\name_enonce[1] \peri \name_enonce[2] \diff
  \name_enonce[3], \name_enonce[4]
}

\answer{\name_answer[1]}{\x}{type=default}
\answer{\name_answer[2]}{\y}{type=default}
\solution{\name_solution
<div class="wimscenter">
  \(\left\lbrace \begin{array}{ccccc}
	2x &+& 2y &=& \peri\\\\
	x &-& y &=& \diff\end{array}\right .\)
</div>
\name_solution2 \(x = \x\), \(y = \y\).
}

