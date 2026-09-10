target=oefmentalsoust1 oefmentalsoust2 oefmentalsoust3 oefmentalsoust4 oefmentalsoust5
#include "author.inc"

#if defined TARGET_oefmentalsoust1
#define NUM 1
\integer{nb1=randint(11..99)}
\integer{nb2=randint(4..9)}
#endif

#if defined TARGET_oefmentalsoust2
#define NUM 2
\integer{a=randint(2..9)}
\integer{nb1=\a*10+randint(0..5)}
\integer{nb2=randint(1..\a-1)*10+randint(6..9)}
#endif

#if defined TARGET_oefmentalsoust3
#define NUM 3
\integer{nb1=randint(1..9)*100+randint(1..9)*10+randint(2..9)}
\integer{nb2=randint(97..99)}
#endif

#if defined TARGET_oefmentalsoust4
#define NUM 4
\real{nb1=randint(1..7)*10+randint(2..9)}
\real{nb2=(randint(1..9)*10+randint(1..9))/10}
#endif

#if defined TARGET_oefmentalsoust5
#define NUM 5
\integer{n=randint(1..2)}
\integer{m=randint(1..2)}
\if{\n=\m}{\integer{\m=\n+1}}
\real{nb1=(randint(1..7)*10+randint(2..9))/10^\n}
\real{nb2=(randint(1..9)*10+randint(1..9))/10^\m}
\real{a=\nb1}
\if{\nb1<\nb2}
{\real{nb1=\nb2}
\real{nb2=\a}}
#endif
#include "lang_titles.inc"
#include "lang.inc"
\real{res=\nb1-\nb2}
\statement{\name_enonce:
<div class="wimscenter">
 \nb1 - \nb2 = \embed{r1}
</div>}
\answer{}{\res}{type=numeric}
