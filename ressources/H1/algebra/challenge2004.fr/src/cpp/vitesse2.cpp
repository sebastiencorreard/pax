target=cycliste2 automobile2 cycliste3 automobile3

#include "header.inc"

#if defined TARGET_cycliste2
 #define TWO 2
 \title{Cycliste II}
 \text{Nom=Un cycliste avance}
 \integer{minv=15}
 \integer{maxv=50}
#endif

#if defined TARGET_automobile2
 #define TWO 2
 \title{Automobile II}
 \text{Nom=Une voiture roule}
 \integer{minv=40}
 \integer{maxv=130}
#endif

#if defined TARGET_cycliste3
 \title{Cycliste III}
 \text{Nom=Un cycliste avance}
 \integer{minv=15}
 \integer{maxv=50}
#endif

#if defined TARGET_automobile3
 \title{Automobile III}
 \text{Nom=Une voiture roule}
 \integer{minv=40}
 \integer{maxv=130}
#endif

\real{ms=randint(\minv/1.8..\maxv/1.8)*0.5}
\real{kmh=\ms*3.6}
\text{textms=\(\textrm{m/s}\)}
\text{textkmh=\(\textrm{km/h}\)}
#ifdef TWO
\statement{
\Nom à une vitesse moyenne de \kmh \textkmh. Quelle est cette vitesse en
\textms&nbsp;?
\embed{r1,6} \textms
}

\reply{La vitesse en m/s}{\ms}

#else

\statement{
\Nom à une vitesse moyenne de \ms \textms. Quelle est cette vitesse en
\textkmh&nbsp;?
\embed{r1,6} \textkmh
}
\reply{La vitesse en km/h}{\kmh}

#endif
