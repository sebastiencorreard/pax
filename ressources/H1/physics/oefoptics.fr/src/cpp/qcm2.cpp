target=qcm2

#include "author.inc"
#include "lang_titles.inc"
#include "lang.inc"

\text{choix=randitem(1,2)}

\text{question=\name_question \name_choix[\choix]}
\text{rep=\choix=1? \list[1]:
  \list[2,3,4]
}
\statement{
<div class="wims_question">\name_question:

</div>
\name_choix[\choix] \embed{reply1}
}
\answer{}{\rep;\list}{type=compose}
