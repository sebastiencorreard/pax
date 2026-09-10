target=coins
#include "author.inc"
#include "lang_titles.inc"

\integer{times=random(20..50)}
\integer{faces=random(\times/3..2*\times/3)}
\real{sol=binomial(\times,\faces)/2^\times}
#include "lang.inc"
\statement{\name_statement1
  <p>\name_statement2</p>}

\answer{\name_answer}{\sol}
\solution{\name_solution}
