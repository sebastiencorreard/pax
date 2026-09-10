target=basic parallel serial par3 ser3 h li parser bridge

#include "xiao.inc"
#include "data.inc"

\text{A=}

#if defined TARGET_basic
# define NUM 1
  \text{ctype=5/closeser}
  \text{comp=bat _V1_,wire,iArrow @@I,,res _R_}
  \text{f_a1=v1/r}
  \text{f_v2=v1}
  \text{f_a2=a1}
#endif
#if defined TARGET_parallel
# define NUM 2
  \text{ctype=5/closeparr}
  \text{comp=bat _V1_,iArrow @@I,res _R1_,,res _R_}
  \text{f_a1=v1/r1+v1/r}
  \text{f_v2=v1}
  \text{f_a2=v1/r}
#endif
#if defined TARGET_serial
# define NUM 2
  \text{ctype=7/closeser}
  \text{comp=wire,bat _V1_,wire,iArrow @@I,chas,res _R1_,res _R_}
  \text{A=12,5.5}
  \text{f_a1=v1/(r1+r)}
  \text{f_v2=v1*r/(r1+r)}
  \text{f_a2=a1}
#endif
#if defined TARGET_par3
# define NUM 3
  \text{ctype=8/closepar3r}
  \text{comp=bat _V1_,iArrow @@I,res _R1_,chas,wire,res _R2_,wire,res _R_}
  \text{f_a1=v1/r1+v1/r2+v1/r}
  \text{f_v2=v1}
  \text{f_a2=v1/r}
#endif
#if defined TARGET_ser3
# define NUM 3
  \text{ctype=7/closeser}
  \text{comp=wire,bat _V1_,iArrow @@I,res _R1_,chas,res _R2_,res _R_}
  \text{A=12,5.5}
  \text{f_a1=v1/(r1+r2+r)}
  \text{f_v2=v1*r/(r1+r2+r)}
  \text{f_a2=a1}
#endif
#if defined TARGET_h
# define NUM 3
  \text{ctype=8/Hclose}
  \text{comp=bat _V1_,iArrow @@I,wire,,res _R_,chas,res _R1_,res _R2_}
  \text{A=14,5.5}
  \text{f_a1=v1/(r1+r2*r/(r2+r))}
  \text{f_v2=v1*(r2*r/(r2+r))/(r1+r2*r/(r2+r))}
  \text{f_a2=v1/(r1+r2*r/(r2+r))*r2/(r2+r)}
#endif
#if defined TARGET_li
# define NUM 3
  \text{ctype=8/br3closeserr}
  \text{comp=bat _V1_,iArrow @@I,wire,res _R1_,res _R_,chas,wire,res _R2_}
  \text{A=9,5.5}
  \text{f_a1=v1/(r1+r)+v1/r2}
  \text{f_v2=v1*r/(r1+r)}
  \text{f_a2=v1/(r1+r)}
#endif
#if defined TARGET_parser
# define NUM 4
  \text{ctype=8/br3closeserr}
  \text{comp=bat _V1_,iArrow @@I,wire,res _R1_,res _R2_,chas,res _R3_,res _R_}
  \text{A=14,5.5}
  \text{f_a1=v1/(r1+r2)+v1/(r3+r)}
  \text{f_v2=v1*r/(r3+r)}
  \text{f_a2=v1/(r3+r)}
#endif
#if defined TARGET_bridge
# define NUM 4
  \text{ctype=8/Hclose}
  \text{comp=bat _V1_,iArrow @@I,wire,res _R3_,res _R_,chas,res _R1_,res _R2_}
  \text{A=14,5.5}
  \text{f_a1=v1/(r1*r3/(r1+r3)+r2*r/(r2+r))}
  \text{f_v2=v1*(r2*r/(r2+r))/(r1*r3/(r1+r3)+r2*r/(r2+r))}
  \text{f_a2=v1/(r1*r3/(r1+r3)+r2*r/(r2+r))*r2/(r2+r)}
#endif
#include "lang_titles.inc"
#include "confparm.inc"
#include "lang.inc"
#include "process.inc"

\text{vide=}
\text{known=a1 isin \given?\name_known[1;] I = \a1 \Aunit:}
\text{known=a2 isin \given?wims(append item \vide \name_known[2;] \a2 \Aunit to \known)}
\text{known=v2 isin \given?wims(append item \vide \name_known[3;] \v2 V to \known)}

\statement{
<div class="float_right">
<img src="\circ" alt="" />
</div>
<div>
\if{\known notsametext }{
 \name_pre, \known.
}
</div><div>
\name_whatis <label for="reply1">\quest</label>&nbsp;?
\embed{r1,8} \qunit
</div>
<br class="clearall" />
<div class="wims_instruction">
\name_attention. \name_warning \tolerance% \name_warning2.
</div>
}

\answer{\quest}{\good}{type=range}

\feedback{(\reply1 > \good2 and \reply1<=\good4) or
(\reply1 < \good1 and \reply1 >= \good3)}{\name_feedback}

