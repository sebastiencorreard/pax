target=one prec next

#include "header.inc"
#include "confparm.inc"
# define NUM
#include "lang_titles.inc"
#include "lang.inc"
#if defined TARGET_one
 \integer{start=1}
 \text{cnt=0,0}
 \text{connector=}
#endif
#if defined TARGET_prec
 \integer{start=2}
 \text{cnt=0,-1}
 \text{connector=\name_connector[1]}
 \text{candouble=yes}
 \text{selective=no}
#endif
#if defined TARGET_next
 \integer{start=2}
 \text{cnt=-1,0}
 \text{connector=\name_connector[2]}
 \text{candouble=yes}
 \text{selective=no}
#endif
#include "data.inc"

\text{f1=\given}
\text{f2=\ask}

\text{pick=randint(\start..\datacnt)}
\text{data1=row(\cnt[1]+\pick,\data)}
\text{data2=row(\cnt[2]+\pick,\data)}
\text{left=column(\f1,\data1)}
\text{right=column(\f2,\data2)}

\steps{reply \f2}

\statement{\quel[\f2] \name_is \namelist[\f2] \name_instruction2[1] \connector
  \name_instruction2[2]
  \namelist[\f1] \name_is \left ?
}

\answer{\name_answer[1]}{\right}{type=number}
\answer{\name_answer[2]}{type=case}
\answer{\name_answer[3]}{\right;\totname}{type=nocase}
\answer{\name_answer[4]}{\right}{type=number}

