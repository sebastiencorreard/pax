target=reconnaitre4 reconnaitre5
#include "author.inc"
#include "lang_titles.inc"
#include "lang.inc"
\text{rep2=\name_yesno[\rep[2]]}
\statement{
\name_question?
<div class="wimscenter" style="font-style:italic">\rep[1].</div>}

\choice{\name_answer}{\rep2}{\name_yesno[1],\name_yesno[2]}
