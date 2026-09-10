target=arggiven

#include "header.inc"
#include "lang_titles.inc"
#include "lang.inc"
\computeanswer{no}
\precision{1000}

\real{mod=randint(1..100)/10}
\real{a1=randint(1..100)/10*random(-1,1)}
\integer{type=random(1,2)}
\real{arg=\type=1?\a1:\a1*pi}
\text{Arg=\type=1?\a1:\a1*pi}
\real{re=cos(\arg)*\mod}
\real{im=sin(\arg)*\mod}

\statement{\name_instruction[1;] \mod \name_instruction[2;] \Arg \name_instruction[3;].}

\answer{\(Re(z))}{\re}
\answer{\(Im(z))}{\im}
