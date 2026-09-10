target=oefperimaire5
#include "author.inc"
#include "lang_titles.inc"
#include "lang.inc"

\keywords{perimeter,area}
\text{size=100x40}
\text{list=2,\(\times\),\name_list[1],\name_list[2],4,\(\pi),diamètre,rayon,+}

\text{form1=\name_list[1],\(\times\),2,+,\name_list[2],\(\times\),2
  |\name_list[2],\(\times\),2,+,\name_list[1],\(\times\),2
  |2,\(\times\),\name_list[1],+,2,\(\times\),\name_list[2]
  |2,\(\times\),\name_list[2],+,2,\(\times\),\name_list[1]
  |\name_list[1],\(\times\),2,+,2,\(\times\),\name_list[2]
  |\name_list[2],\(\times\),2,+,2,\(\times\),\name_list[1]
}

\text{form2=\name_list[1],\(\times\),\name_list[2]
  |\name_list[2],\(\times\),\name_list[1]}

\statement{
  \enonce[1]:
  <div class="wimscenter">
  \embed{r1,\size}
  </div>
  \enonce[2]:
  <div class="wimscenter">
  \embed{r2,\size}
  </div>
}
\answer{}{\form1;\list}{type=clickfill}
\answer{}{\form2;\list}{type=clickfill}
