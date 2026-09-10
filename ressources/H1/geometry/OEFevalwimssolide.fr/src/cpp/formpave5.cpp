target=oefformpave5

#include "author.inc"
#include "lang_titles.inc"
#include "lang.inc"
\precision{10000}

\text{size=100x40}

\text{list=2,\(\times),\name_long[1],\name_long[2],4,\(\,\pi),\name_long[3],\name_long[5],\name_long[4]}

\text{form=\name_long[1],\(\times),\name_long[2],\(\times),\name_long[3]
  |\name_long[1],\(\times),\name_long[3],\(\times),\name_long[2]
  |\name_long[2],\(\times),\name_long[1],\(\times),\name_long[3]
  |\name_long[2],\(\times),\name_long[3],\(\times),\name_long[1]
  |\name_long[3],\(\times),\name_long[2],\(\times),\name_long[1]
  |\name_long[3],\(\times),\name_long[1],\(\times),\name_long[2]
}

\statement{\name_enonce:
<div class="wimscenter">
\embed{r1,\size}
</div>
}
\answer{}{\form;\list}{type=clickfill}{option=shuffle}
