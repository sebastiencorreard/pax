target=livre

#include "header.inc"
#include "lang_titles.inc"

\title{TITLE}
\title_it{TITLE_it}

\text{limite=9,189,2889}

\text{n=items(\limite)}
\text{m=randint(2..\n)}

\integer{page = randint(10^(\m)..min(3000,10^(\m+1)-1))}

\integer{caractere= \limite[\m] + (\m+1)*(\page -10^(\m))}
\text{c = randint(1,2)}

#include "lang.inc"

\text{enonce=row(\c,\name_matrix_question)}
\text{sol = \c=1 ? \caractere : \page}
\text{question=\c=1 ? \name_characters: \name_pages}

\statement{\name_statement
<div class="spacer">
\enonce ?
</div>
}

\answer{\name_numberof \question}{\sol}
