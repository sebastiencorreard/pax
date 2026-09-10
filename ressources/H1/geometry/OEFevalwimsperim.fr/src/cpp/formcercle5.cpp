target=oefformcercle5

#include "author.inc"
\precision{10000}
\keywords{perimeter}
\text{size=100x40}
#include "lang_titles.inc"
#include "lang.inc"
\text{nom=\name_list[3],\name_list[4]}
\integer{ch=randint(1..2)}

\text{list=2,\(\times),\name_list[1],\name_list[2],4,\(\,\pi),\name_list[3],\name_list[4]}

\if{\ch=1}{
  \text{form=\(\,\pi),\(\times),\name_list[3]|\name_list[4],\(\times),\(\,\pi)}
}{
  \text{form=2,\(\times),\(\,\pi),\(\times),\name_list[4]
    |\(\,\pi),\(\times),2,\(\times),\name_list[4]
    |\(\,\pi),\(\times),\name_list[4],\(\times),2
    |2,\(\times),\name_list[4],\(\times),\(\,\pi)
    |\name_list[4],\(\times),\(\,\pi),\(\times),2
    |\name_list[4],\(\times),2,\(\times),\(\,\pi)}
}

\statement{\name_question \nom[\ch] :
  <div class="wimscenter">\embed{r1,\size}</div>
}
\answer{}{\form;\list}{type=clickfill}
