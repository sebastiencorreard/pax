target=sqrt

#include "common.inc"
#include "lang_titles.inc"

\integer{a=random(1..20)*random(-1,1)}
\integer{b=random(2..20)*random(-1,1)}

#include "lang.inc"

\statement{\name_statement[1]
\(z = \a+\b*i\), \name_statement[2].
}

\answer{\(Re(w)\)}{\re}{type=numeric}
\answer{\(Im(w)\)}{\im}{type=numeric}

\condition{\(Re(w^2 )\) = \a}{(\re)^2-(\im)^2=\a}
\condition{\(Im(w^2 )\) = \b}{2*(\re)*(\im)=\b}
