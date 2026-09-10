target=oefperimcercle1 oefperimcercle2 oefperimcercle3 oefperimcercle4 oefperimcercle5
\keywords{perimeter,length}

#include "author.inc"
#include "lang_titles.inc"
#include "lang.inc"
\precision{1000000}

#if defined TARGET_oefperimcercle1
\text{a=1}
\text{mot=\name_list[3]}
\integer{d=randint(16..99)}
\integer{res=\d*3}
\text{enonc1= \name_enonc1[1] \mot[\a] \d cm. \name_enonc1[2]}
#endif
#if defined TARGET_oefperimcercle2
\integer{a=randint(1..2)}
\text{mot=\name_list[3],\name_list[4]}
\integer{d=randint(6..49)}
\if{\a=1}{\integer{res=\d*3}}{\integer{res=\d*6}}
\text{enonc1= \name_enonc1[1] \mot[\a] \d cm. \name_enonc1[2]}
#endif
#if defined TARGET_oefperimcercle3
\integer{a=randint(1..2)}
\text{mot=\name_list[3],\name_list[4]}
\real{d=randint(11..99)/10}
\if{\a=1}{\real{res=\d*3.14}}{\real{res=\d*6.28}}
\text{enonc1= \name_enonc1[1] \mot[\a] \d cm. \name_enonc1[2]}
#endif
#if defined TARGET_oefperimcercle4
\text{a=1}
\text{mot=\name_list[3]}
\real{d=randint(11..99)/10}
\real{l=\d*3}
\real{res=\d}
\text{enonc1= \name_enonc1[1] \l cm. \name_enonc1[2] \mot[\a]}
#endif
#if defined TARGET_oefperimcercle5
\integer{a=randint(1..2)}
\text{mot=\name_list[3],\name_list[4]}
\real{d=randint(11..99)/10}
\if{\a=1}{\real{l=\d*3}}{\real{l=\d*6}}
\real{res=\d}
\text{enonc1= \name_enonc1[1] \l cm. \name_enonc1[2] \mot[\a]}
#endif

\statement{<label for="reply1">\enonc1:</label>
  \embed{r1,5}
  \enonc2 cm.
  <div class="wims_instruction">\instruction</div>
}
\answer{}{\res}{type=numeric}
