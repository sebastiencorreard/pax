target=borne

#include "header.inc"
#include "lang_titles.inc"

\title{TITLE}
\title_it{TITLE_it}

\integer{n = randint(3..7)}
\integer{b = randint(3..9)}
\integer{ c= randint(1,2)}
\integer{sol= \c=1 ? \b^\n - 1: \b^(\n-1)}

#include "lang.inc"

\statement{\name_statement}
\answer{}{\sol}

\latex{\name_statement}
