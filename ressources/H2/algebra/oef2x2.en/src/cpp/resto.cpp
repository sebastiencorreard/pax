target=resto

#include "author.inc"
#include "lang_titles.inc"
#include "lang.inc"
\precision{10000}
\keywords{pbsolving,linear_system}

\integer{x=random(2..8)}
\integer{y=random(2..8)}
\integer{pers=\x+\y}
\integer{child=random(13..25)}
\integer{adult=random(\child*1.2..\child*1.8)}
\integer{tot=\child*\x+\adult*\y}
\statement{\pers \name_enonce
<p>
\name_enonce2[1] \child \name_enonce2[2], \name_enonce2[3] \adult
  \name_enonce2[4] \tot \name_enonce2[5].
</p><p>
\name_question[1] \pers \name_question[2], \name_question[3]?
</p>
}

\answer{\name_answer[1]}{\x}{type=default}
\answer{\name_answer[2]}{\y}{type=default}
\solution{\name_solution[1], \name_solution[2]
<div class="wimscenter">
	\(\left \lbrace
	\begin{array}{ccccc}
	x &+& y &=& \pers \\\\
	\child x &+& \adult y &=& \tot
	\end{array}\right .
	\)
</div>
 \name_solution[3] \(x=\x\), \(y=\y\).
}

