target=sumofi

#include "common.inc"
#include "lang_titles.inc"

\integer{start=random(2..20)}
\integer{end=random(100..200)}
\integer{start1=\start+1}
\integer{start2=\start+2}
\integer{sind=\start%4+1}
\integer{rem=(\end+1-\start)%4}
\real{re=\rem=0?0}
\real{im=\rem=0?0}
\real{re=\rem=1?item(\sind,1,0,-1,0)}
\real{im=\rem=1?item(\sind,0,1,0,-1)}
\real{re=\rem=2?item(\sind,1,-1,-1,1)}
\real{im=\rem=2?item(\sind,1,1, -1,-1)}
\real{re=\rem=3?item(\sind,0,-1,0,1)}
\real{im=\rem=3?item(\sind,1,0,-1,0)}

#include "lang.inc"

\statement{\name_statement
<div class="wimscenter">
\(S=i^\start +i^\start1 +i^\start2 +...+i^\end\).
</div>}

\answer{\(Re(S)\)}{\re}
\answer{\(Im(S)\)}{\im}
