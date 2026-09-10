target=suminv

#include "common.inc"
#include "lang_title.inc"

\integer{sign=random(1,2)}
\text{right=item(\sign,-1,1)}

\integer{power=random(100..999)}
\integer{sol=\power%3=0?2:-1}
\integer{sol=\sign=1 or \power%2=0?\sol:-(\sol)}

#include "lang.inc"

\statement{\name_statement[1] \(z+1/z=\right). \name_statement[2]
\(w=z^\power +z^(-\power )).}

\answer{\(Re(w))}{\sol}
\answer{\(Im(w))}{0}
