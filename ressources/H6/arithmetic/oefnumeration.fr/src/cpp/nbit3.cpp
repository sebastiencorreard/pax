target=nbit3

#include "header.inc"
#include "lang_titles.inc"

\title{TITLE}
\title_it{TITLE_it}

\text{a=pari(random\(100000000))}
\integer{b=randint(2..5)}
\integer{c=randint(7..20)}
\real{N=floor(log(\a)/log(\b))+1}
\real{M=floor(log(\a)/log(\c))+1}

\integer{sol = pari(ceil(\b^(\N/\M)))}

#include "lang.inc"

\statement{\name_statement}
\answer{\name_base \(b\)}{\sol}
