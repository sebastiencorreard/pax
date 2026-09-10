target=order3 order4 order5 order6

#include "header.inc"
#include "confparm.inc"

#if defined TARGET_order3
# define NUM 3
#endif
#if defined TARGET_order4
# define NUM 4
#endif
#if defined TARGET_order5
# define NUM 5
#endif
#if defined TARGET_order6
# define NUM 6
#endif
#include "lang_titles.inc"
#include "lang.inc"
\integer{cnt=NUM}

#include "data.inc"

\text{given=\given notitemof 2,3?randitem(2,3)}

\text{sxs=60,60,120,100}

\text{sh=item(1..\cnt,shuffle(\datacnt))}
\text{sh=wims(sort numeric items \sh)}
\text{data=row(\sh,\data)}
\text{data=column(\given,\data)}
\statement{\name_instruction
  <div class="wimscenter">
  \for{i=1 to \cnt}{
    \embed{r\i,\sxs[\given]x30}
  }
  </div>
}

\answer{\name_answer 1}{\data[1]}{type=dragfill}
\answer{\name_answer 2}{\data[2]}{type=dragfill}
\answer{\name_answer 3}{\data[3]}{type=dragfill}
#if NUM>3
 \answer{\name_answer 4}{\data[4]}{type=dragfill}
#endif
#if NUM>4
 \answer{\name_answer 5}{\data[5]}{type=dragfill}
#endif
#if NUM>5
 \answer{\name_answer 6}{\data[6]}{type=dragfill}
#endif


