target=arggiven

#include "common.inc"
#include "lang_title.inc"

\real{mod=randint(1..100)/10}
\real{a1=randint(1..100)/10*random(-1,1)}
\integer{type=random(1,2)}
\real{arg=\type=1?\a1:\a1*pi}
\text{Arg=\type=1?\a1:\a1*pi}
\real{re=cos(\Arg)*\mod}
\real{im=sin(\Arg)*\mod}

#include "lang.inc"

\statement{\name_statement[1] \(\mod) \name_statement[2] \(\Arg) \name_statement[3].}

\answer{\(Re(z))}{\re}{type=numeric}
\answer{\(Im(z))}{\im}{type=numeric}

