target=sumofj

#include "common.inc"
#include "lang_title.inc"

\integer{start=random(2..20)}
\integer{end=random(100..200)}
\integer{start1=\start+1}
\integer{start2=\start+2}
\integer{sind=\start%3+1}
\integer{rem=(\end+1-\start)%3}
\real{re=\rem=0?0}
\real{im=\rem=0?0}
\real{re=\rem=1?item(\sind,1,     -0.5,      -0.5)}
\real{im=\rem=1?item(\sind,0,sqrt(3)/2,-sqrt(3)/2)}
\real{re=\rem=2?item(\sind,      0.5,-1,       0.5)}
\real{im=\rem=2?item(\sind,sqrt(3)/2, 0,-sqrt(3)/2)}

#include "lang.inc"

\statement{\name_statement[1] \(j=\cos{2\pi\over 3}+i\sin{2\pi\over 3}).
\name_statement[2]
<div class="wimscenter"> \(S=j^{\start}+j^{\start1}+j^{\start2}+...+j^{\end}\quad.)
</div>}
\answer{\(Re(S))}{\re}
\answer{\(Im(S))}{\im}
