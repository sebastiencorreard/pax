target=reim
#include "header.inc"
#include "lang_titles.inc"
#include "lang.inc"

\text{n=randint(2..8)}

\text{data=randomrow(
 i z,- y, x
 -i z, y, -x
 \n z,\n x,\n y
 z + i,x,y + 1
 z - i,x,y - 1
 i - z, - x,1 - y
 \n + z,x + \n,y
 \n - z,\n - x, - y
 z - \n,x - \n,y
 \n + i z,\n - y,x
 \n - i z,\n + y, -x
 i z - \n,-y - \n,x
 z + \n i,x,y + \n
 z - \n i,x,y - \n
 \n i - z, - x,\n - y
 conj(z),x, - y
 i conj(z),y,x
 - i conj(z), - y, - x
 \n conj(z),\n x, - \n y
 conj(z) + i,x, - y + 1
 conj(z) - i,x, - y - 1
 i - conj(z), - x,1 + y
 \n + conj(z),x + \n, - y
 \n - conj(z),\n - x,y
 conj(z) - \n,x - \n,-y
 z + \n + i,x + \n,y + 1
 z - \n + i,x - \n,y + 1
 z - \n - i,x - \n,y - 1
 z + \n - i,x + \n,y - 1
 \n + i - z,\n - x,1 - y
)}
\function{w=item(1,\data)}
\function{re=item(2,\data)}
\function{im=item(3,\data)}

\statement{\name_instruction \(\w\)?
<div class="wimscenter">
 Re(\(\w\)) = \embed{reply 1,10}, Im(\(\w\)) = \embed{reply 2,10}.
</div>
}

\reply{\name_answer[1]}{\re}{type=formal}
\reply{\name_answer[2]}{\im}{type=formal}

\latex{
\begin{statement}
\name_instruction \(\w\)?
\par
 Re(\(\w)\) =
 \par
 Im(\(\w)\) =
\end{statement}
}
