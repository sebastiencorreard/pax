target=cbrt

#include "common.inc"
#include "lang_title.inc"

\integer{sign=random(1,2)}
\text{st=item(\sign,+,-)}
\integer{power=random(100..999)}
\integer{sol=\power%3=0?2:-1}
\integer{sol=\sign=1 or \power%2=0?\sol:-(\sol)}

#include "lang.inc"

\text{style=random(\name_style[1]
	\(z^2 \st z+1=0),
	\name_style[2] \(X^2\st X+1))}

\statement{\name_statement[1] \(z) \style. \name_statement[2]
\(w = z^\power +z^(-\power) )?}

\answer{\(Re(w))}{\sol}
\answer{\(Im(w))}{0}


