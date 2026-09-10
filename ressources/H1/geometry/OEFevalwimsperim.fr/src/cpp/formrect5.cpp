target=oefformrect5
#include "author.inc"
\precision{10000}
\keywords{area}
\text{size=100x40}
#include "lang_titles.inc"
#include "lang.inc"
\text{nom=\name_list[4]}

\text{list=2,\(\times\),\name_list[1],\name_list[2],4,\(\pi\),\name_list[3],\name_list[4]}

\text{form=\name_list[1],\(\times\),\name_list[2]
  |\name_list[2],\(\times\),\name_list[1]
}

\statement{\name_question
  <div class="wimscenter">
  \embed{r1,\size}
  </div>
}
\answer{}{\form;\list}{type=clickfill}
