target=oefformrect3 oefformrect4
\text{name_formule=formule}
\keywords{area}
#include "author.inc"
\precision{1000000}
#include "lang_titles.inc"
#include "lang.inc"
#if defined TARGET_oefformrect3
\integer{lo=randint(6..29)}
\integer{la=randint(3..\lo-1)}
\integer{res=\lo*\la}
#endif
#if defined TARGET_oefformrect4
\real{lo=randint(60..290)/10}
\real{la=randint(30..\lo-10)/10}
\real{res=\lo*\la}
#endif
\text{enonc1= \name_enonc1[1] \lo cm \name_enonc1[2] \la cm.
  <p>\name_formule = \name_list[1] \(\times\) \name_list[2].</p>}

\statement{\enonc1
  <label for="reply1">\enonc11</label>:\embed{r1,7} cm²
}

\answer{}{\res}{type=numeric}
