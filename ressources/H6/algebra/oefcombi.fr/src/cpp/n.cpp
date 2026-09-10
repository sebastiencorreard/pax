target=n
#include "author.inc"
#include "lang_titles.inc"
#include "lang.inc"
\precision{1000000}

\integer{tot=random(10..30)}
\integer{first=random(2..floor(\tot/3))}
\integer{second=\tot-\first}
\text{q1=\name_question \(n\)&nbsp;}
\text{q2=\name_question \(C_n^\first\)&nbsp;}
\integer{choice=randitem(0,1)}
\text{q=\choice=0?\q1:\q2}
\integer{sol=\choice=0?\tot:binomial(\tot,\first)}

\statement{\name_enonce \(C_n^\first=C_n^\second\). \q ?}

\answer{\name_answer}{\sol}
