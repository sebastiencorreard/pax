target=freeway

#include "author.inc"
#include "lang_titles.inc"

\real{min=randint(15..25)/100}
\integer{tot=random(8..15)}
\real{sol=(1-\min)^\tot}

#include "lang.inc"

\statement{\name_statement1
<p>
\name_statement2
</p>}

\answer{\name_answer}{\sol}
