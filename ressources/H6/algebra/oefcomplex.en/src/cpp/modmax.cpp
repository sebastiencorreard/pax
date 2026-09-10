target=modmax

#include "common.inc"
#include "lang_titles.inc"

\integer{a=random(-20..20)}
\integer{b=random(2..20)*random(-1,1)}
\real{mod=sqrt((\a)^2+(\b)^2)}
\integer{modz=random(1..9)}
\real{re=\a*\modz/\mod}
\real{im=\b*\modz/\mod}

#include "lang.inc"

\statement{\name_statement[1] \modz,
  \name_statement[2] \(\a+\b*i+z\) \name_statement[3].}

\answer{\(Re(z)\)}{\re}
\answer{\(Im(z)\)}{\im}
