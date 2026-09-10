target=oefmentaladd1 oefmentaladd2 oefmentaladd3 oefmentaladd4 oefmentaladd5
#include "author.inc"

#if defined TARGET_oefmentaladd1
#define NUM 1
\integer{nb1=randint(11..19)}
\integer{nb2=randint(4..9)}
#endif

#if defined TARGET_oefmentaladd2
#define NUM 2
\integer{nb1=randint(15..29)}
\integer{nb2=randint(16..49)}
#endif

#if defined TARGET_oefmentaladd3
#define NUM 3
\integer{nb1=randint(2..9)*10+randint(4..9)}
\integer{nb2=randint(97..99)}
#endif

#if defined TARGET_oefmentaladd4
#define NUM 4
\real{nb1=randint(1..7)*10+randint(2..9)}
\real{nb2=(randint(1..9)*10+randint(1..9))/10}
#endif

#if defined TARGET_oefmentaladd5
#define NUM 5
\integer{n=randint(1..2)}
\integer{m=randint(1..2)}
\if{\n=\m}{\integer{\m=\n+1}}
\real{nb1=(randint(1..7)*10+randint(2..9))/10^\n}
\real{nb2=(randint(1..9)*10+randint(1..9))/10^\m}
#endif
#include "lang_titles.inc"
#include "lang.inc"
\real{res=\nb1+\nb2}
\statement{
\name_enonce :
<div class="wimscenter">
 \nb1 + \nb2 = \embed{r1}
</div>}
\answer{}{\res}{type=numeric}
