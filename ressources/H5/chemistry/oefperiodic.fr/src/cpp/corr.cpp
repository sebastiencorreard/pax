target=corr3 corr4 corr5 corr6 corr7
#include "header.inc"
#include "confparm.inc"

#if defined TARGET_corr3
# define NUM 3
#endif
#if defined TARGET_corr4
# define NUM 4
#endif
#if defined TARGET_corr5
# define NUM 5
#endif
#if defined TARGET_corr6
# define NUM 6
#endif
#if defined TARGET_corr7
# define NUM 7
#endif
#include "lang_titles.inc"
#include "lang.inc"
\integer{cnt=NUM}

#include "data.inc"
\text{f1=\given}
\text{f2=\ask}

\text{sxs=60,60,150,100}

\text{sh=item(1..\cnt,shuffle(\datacnt))}
\text{data=row(\sh,\data)}
\text{left=column(\f1,\data)}
\text{right=column(\f2,\data)}

\statement{\name_instruction[1] \namelist[\f1]
  \name_instruction[2] \namelist[\f2] \name_instruction[3]
<div class="wimscenter">
 \embed{r1,30x\sxs[\f1]x\sxs[\f2]}
</div>
}

\answer{La correspondance}{\left;\right}{type=correspond}

