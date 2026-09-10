target=cubrt

#include "common.inc"
#include "lang_title.inc"

\integer{a=random(1..20)*random(-1,1)}
\integer{b=random(2..20)*random(-1,1)}
\complex{z1=\a+\b*i}

#include "lang.inc"

\statement{\name_statement[1] \(z=\z1), \name_statement[2].}

\answer{\(Re(w))}{\re}
\answer{\(Im(w))}{\im}

\condition{\(Re(w^3)=\a)}{(\re)^3-3*(\re)*(\im)^2=\a}
\condition{\(Im(w^3)=\b)}{3*(\re)^2*(\im)-(\im)^3=\b}

