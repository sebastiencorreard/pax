target=oefformdisq5

#include "lang_titles.inc"
#include "author.inc"
#include "lang.inc"
\precision{10000}
\keywords{area}
\text{size=100x40}

\text{nom=\name_list[4]}
\text{list=2,\(\times),\name_list[1],\name_list[2],4,\(\pi),\name_list[3],\name_list[4]}

\text{form=\(\pi),\(\times),\name_list[4],\(\times),\name_list[4]
  |\name_list[4],\(\times),\name_list[4],\(\times),\(\pi)
  |\name_list[4],\(\times),\(\pi),\(\times),\name_list[4]}
\statement{\name_question \nom :
  <div class="wimscenter">\embed{r1,\size}</div>
}
\answer{}{\form;\list}{type=clickfill}
