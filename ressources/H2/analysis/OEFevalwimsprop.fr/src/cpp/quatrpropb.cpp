target=quatrprop3 quatrprop4
\language{ fr }
\author{Denis,Guicheteau}
\email{ math.42@laposte.net }
\format{ html }
#include "lang_titles.inc"
#include "lang.inc"
\text{name_answer=Votre réponse}
\integer{situ=randint(1..3)}
\integer{sit=randint(1..4)}
\integer{nb=randint(2..10)}
#if defined TARGET_quatrprop3
\integer{nb2=randitem(2,3,4,5,6,7,8,9)*\nb}
\text{ag=2,3,12}
#endif
#if defined TARGET_quatrprop4
\integer{nb2=randint(\nb+1..20)}
\text{ag=0.5,1.5,2.1}
#endif
\integer{agtot=\ag[\situ] * \nb}
#if defined TARGET_quatrprop3
\integer{r=\nb2/\nb*\agtot}
#endif
#if defined TARGET_quatrprop4
\real{r=\nb2/\nb*\agtot}
#endif
\statement{
\name_enonce[1] \lieu[\sit] \name_enonce[2] \action[\sit] \nb \objet[\situ]
\name_enonce[3] \agtot \name_enonce[4]
\personne[\situ] \name_enonce[5] \nb2. \name_enonce[6]?
}
\answer{\name_answer}{\r}

