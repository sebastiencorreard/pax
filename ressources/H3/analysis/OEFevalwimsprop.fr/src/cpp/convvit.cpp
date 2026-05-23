target =convvit1 convvit2 convvit3 convvit4 convvit5
\keywords{conversion}

#include "author.inc"
#if defined TARGET_convvit1
# define NUM 1
#endif
#if defined TARGET_convvit2
# define NUM 2
#endif
#if defined TARGET_convvit3
# define NUM 3
#endif
#if defined TARGET_convvit4
# define NUM 4
#endif
#if defined TARGET_convvit5
# define NUM 5
#endif
\title{TITRE NUM}
#include "lang_titles.inc"
#include "lang.inc"
#if defined TARGET_convvit3
 \matrix{ltype=km/h,km/min
km/min,km/s
m/h,m/min,
m/min,m/s}
#endif
#if defined TARGET_convvit4
 \matrix{ltype=km/h,km/s
m/h,m/min}
#endif
#if defined TARGET_convvit1
 \matrix{ltype=km/h,m/h
km/s,m/s}
#endif
#if defined TARGET_convvit2
 \matrix{ltype=km/min,m/min}
#endif
#if defined TARGET_convvit5
 \matrix{ltype=km/h,km/min,km/s,m/h,m/s,m/min}
#endif
\text{don=randrow(\ltype)}
\text{don=shuffle(\don)}
\text{quest=item(1,\don)}
\text{rep=item(2,\don)}
\text{unite=km/h,km/min,km/s,m/h,m/s,m/min}
\text{coef=3600,60,1,3600000,1000,60000}
\real{init=randint(100..500)/100}

\integer{posquest=positionof(\quest,\unite)}
\integer{posrep=positionof(\rep,\unite)}
\real{valquest=\init*item(\posquest,\coef)}
\real{valrep=\init*item(\posrep,\coef)}

\statement{
  \name_question[1] \valquest \quest \name_question[2] \rep.
<div class="spacer">
<b>\name_youranswer</b>:
<label for="reply1">\valquest \quest =</label> \embed{r1,9} \rep.
</div>}

\answer{\(\valquest \quest)}{\valrep}{type=numexp}
